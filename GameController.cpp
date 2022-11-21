#include "WindowController.h"
#include "GameController.h"
#include "Shader.h"
#include "Texture.h"
#include "Font.h"
#include <chrono>
#include <thread>
#include <iostream>
#include <fstream>

GameController::GameController() {
	m_camera = {};
	m_meshes.clear();
}
GameController::~GameController(){}

void GameController::keyInputHandling() {
	vec3 cameraVelocity = vec3(0.f);
	if (glfwGetKey(m_window, GLFW_KEY_A) != GLFW_RELEASE) cameraVelocity = -m_camera.getRight();
	if (glfwGetKey(m_window, GLFW_KEY_D) != GLFW_RELEASE) cameraVelocity = m_camera.getRight();
	if (glfwGetKey(m_window, GLFW_KEY_W) != GLFW_RELEASE) cameraVelocity = m_camera.getForward();
	if (glfwGetKey(m_window, GLFW_KEY_S) != GLFW_RELEASE) cameraVelocity = -m_camera.getForward();
	if (glfwGetKey(m_window, GLFW_KEY_Q) != GLFW_RELEASE) cameraVelocity = -m_camera.getUp();
	if (glfwGetKey(m_window, GLFW_KEY_E) != GLFW_RELEASE) cameraVelocity = m_camera.getUp();

	m_camera.cameraDisplacement(cameraVelocity * 2.5f * dt);
}

void GameController::mouseInputHandling() {
	if (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE) {
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		return;
	}
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	static double old_xpos, old_ypos;

	double xpos, ypos;
	glfwGetCursorPos(m_window, &xpos, &ypos);

	double dX = (xpos - old_xpos) * .0002f;
	double dY = (ypos - old_ypos) * .0002f;
	old_xpos = xpos; old_ypos = ypos;

	if (dX == 0.f || dY == 0.f) return;

	m_camera.cameraTurn(-dX, -dY);
}

void GameController::Initialize() {
	m_window = WindowController::GetInstance().GetWindow(); // glfwInit()
	M_ASSERT(glewInit() == GLEW_OK, "Failed to initialize GLEW");
	glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GL_TRUE);
	glClearColor(.1f, .1f, .1f, 1.f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_camera = Camera(WindowController::GetInstance().GetResolution());

	srand(time(0));
}

void GameController::ShaderInit(ShaderMap& shaderMap) const {
	std::ifstream shaderConfig("Res/shaders.config");

	std::string shaderName;
	int textureCount;
	std::string textureName;

	while (shaderConfig) {
		shaderConfig >> shaderName >> textureCount;

		shaderMap[shaderName] = make_shared<Shader>();
		shaderMap[shaderName]->LoadShaders(("Res/Shaders/" + shaderName + ".vert").c_str(), ("Res/Shaders/" + shaderName + ".frag").c_str());

		for (int i = 0; i < textureCount; i++) {
			shaderConfig >> textureName;
			auto texture = make_shared<Texture>();
			texture->LoadTexture("Res/Textures/" + textureName);

			shaderMap[shaderName]->AddTexture(texture);
		}
	}
}

void GameController::Run() {
	// Shader Init
	ShaderMap shaders;
	ShaderInit(shaders);

	// Model Init
	objl::Loader loader;
	M_ASSERT(loader.LoadFile("Res/Models/teapot.obj") == true, "Failed to load mesh");

	for (unsigned int i = 0; i < loader.LoadedMeshes.size(); i++) {
		objl::Mesh& mesh = loader.LoadedMeshes[i];

		for (unsigned int i = 0; i < loader.LoadedIndices.size(); i += 3) {
			unsigned int index = loader.LoadedIndices[i];
			auto& p0 = mesh.Vertices[index];
			auto& p1 = mesh.Vertices[index + 1];
			auto& p2 = mesh.Vertices[index + 2];

			objl::Vector3 e1 = p0.Position - p1.Position;
			objl::Vector3 e2 = p0.Position - p2.Position;
			objl::Vector2 duv1 = p0.TextureCoordinate - p1.TextureCoordinate;
			objl::Vector2 duv2 = p0.TextureCoordinate - p2.TextureCoordinate;

			float f = 1.f / (duv1.X * duv2.Y - duv2.X * duv1.Y);

			objl::Vector3 tangent;
			tangent.X = f * (duv2.Y * e1.X - duv1.Y * e2.X);
			tangent.Y = f * (duv2.Y * e1.Y - duv1.Y * e2.Y);
			tangent.Z = f * (duv2.Y * e1.Z - duv1.Y * e2.Z);

			p0.Tangent = tangent;
			p1.Tangent = tangent;
			p2.Tangent = tangent;
		}
	}

	// Font Iinit
	Font f = Font();
	f.Create(shaders["font"].get(), "Arial.ttf", 100);

	// light mesh init
	vec3 lightPos = vec3(3.5f, 0.f, -.5f);
	vector<Mesh> lights;
	for (int i = 0; i < 4; i++) {
		auto mesh = Mesh();
		mesh.Create(shaders["sphere"].get(), &loader);
		mesh.SetPosition(lightPos + vec3(0.f, i / 1.5f - 1.f, 0.f));
		mesh.SetLightColor(vec3(glm::linearRand(0.f, 1.f), glm::linearRand(0.f, 1.f), glm::linearRand(0.f, 1.f)));
		lights.push_back(mesh);
	}

	//// cube mesh init
	for (int col = 0; col < 10; col++) {
		for (int count = 0; count < 10; count++) {
			auto mesh = Mesh();
			mesh.Create(shaders["crate"].get(), &loader);
			mesh.SetLightMesh(lights);
			mesh.SetScale(vec3(.5f));
			mesh.SetPosition(vec3(0.f, -.5f + count / 10.f, -.2f + col / 10.f) * 5.f);
			m_meshes.push_back(mesh);
		}
	}

	dt = 1 / FPS; // second
	float timePreviousFrame = glfwGetTime();
	do {
		// Input
		glfwPollEvents();
		keyInputHandling();
		mouseInputHandling();

		// Render
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		for (auto& mesh : lights) {
			mesh.Render(m_camera);
		}
		for (auto& mesh : m_meshes) {
			mesh.SetRotation((float)glfwGetTime(), vec3(0.f, 1.f, 0.f));
			mesh.Render(m_camera);
		}
		f.RenderText("testing", 10.f, 500.f, .5f, {1.f, 1.f, 0.f});
		glfwSwapBuffers(m_window);


		// Frame rate
		float sleepTime = MPF - (glfwGetTime() - timePreviousFrame) * 1000;
		if (sleepTime > 0) {
			std::this_thread::sleep_for(std::chrono::milliseconds((long)sleepTime));
		}
		dt = (glfwGetTime() - timePreviousFrame);
		timePreviousFrame = glfwGetTime();

	} while (glfwGetKey(m_window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(m_window) == 0);

	for (auto& mesh : m_meshes) {
		mesh.Cleanup();
	}

	for (const auto& shader : shaders) {
		shader.second->Cleanup();
	}
}
