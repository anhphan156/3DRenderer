#include "WindowController.h"
#include "GameController.h"
#include "Shader.h"
#include "Texture.h"
#include "Font.h"
#include <chrono>
#include <thread>
#include <iostream>
#include <fstream>
#include "TopMostTool.h"

using OpenGLLearning2::TopMostTool;

GameController::GameController() {
	m_camera = {};
	m_cubes.clear();
}
GameController::~GameController(){}

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

void GameController::Run() {
	// Shader Init
	ShaderInit(m_shaders);

	// Model Init
	ModelInit(m_teapotModel, "Res/Models/teapot.obj");
	ModelInit(m_sphereModel, "Res/Models/sphere.obj");
	ModelInit(m_cubeModel, "Res/Models/cube.obj");

	// Font Init
	Font f = Font();
	f.Create(m_shaders["font"].get(), "Arial.ttf", 100);

	// light mesh init
	vec3 lightPos = vec3(0.f, 2.f, 3.f);
	for (int i = 0; i < 1; i++) {
		auto mesh = Mesh();
		mesh.Create(m_shaders["lightbulb"].get(), &m_sphereModel);
		mesh.SetPosition(lightPos + vec3(2.f, i / 1.5f - 1.5f, -1.5f));
		mesh.SetLightColor(vec3(1.f));
		mesh.SetScale(vec3(.2f));
		m_lights.push_back(mesh);
	}

	// part 1 + 2 center teapot
	m_teapot = Mesh();
	m_teapot.Create(m_shaders["teapot"].get(), &m_teapotModel);
	m_teapot.SetLightMesh(m_lights);
	m_teapot.SetScale(vec3(.5f));
	m_teapot.SetPosition(vec3(0.f));

	// part 3 center sphere
	m_sphere = Mesh();
	m_sphere.Create(m_shaders["teapot"].get(), &m_sphereModel);
	m_sphere.SetLightMesh(m_lights);
	m_sphere.SetScale(vec3(.7f));
	m_sphere.SetPosition(vec3(0.f));

	// Top most tool init
	TopMostTool^ topMostTool = gcnew TopMostTool();
	topMostTool->Show();

	// Frame rate init
	dt = 1 / FPS; // second
	float timePreviousFrame = glfwGetTime();
	float framecount = 0;
	do {
		// top most tool
		System::Windows::Forms::Application::DoEvents();

		// Input
		glfwPollEvents();
		SpawnCube();
		CubeMovement();

		// Render
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		m_sphere.SetRotation((float)glfwGetTime(), vec3(1.f, 0.f, 0.f));
		m_sphere.Render(m_camera);
		for (auto& mesh : m_lights) {
			mesh.Render(m_camera);
		}
		for (auto& mesh : m_cubes) {
			mesh.SetRotation((float)glfwGetTime(), vec3(1.f, 0.f, 0.f));
			mesh.Render(m_camera);
		}
		f.RenderText("fps: " + std::to_string(framecount / timePreviousFrame), 10.f, 200.f, .25f, {1.f, 1.f, 1.f});
		f.RenderText("Cube count: " + std::to_string(m_cubes.size()), 10.f, 230.f, .25f, vec3(1.f));
		glfwSwapBuffers(m_window);

		// Frame rate
		float sleepTime = MPF - (glfwGetTime() - timePreviousFrame) * 1000;
		if (sleepTime > 0) {
			std::this_thread::sleep_for(std::chrono::milliseconds((long)sleepTime));
		}
		dt = (glfwGetTime() - timePreviousFrame);
		timePreviousFrame = glfwGetTime();
		framecount++;
	} while (glfwGetKey(m_window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(m_window) == 0);

	for (auto& mesh : m_cubes)	mesh.Cleanup();
	for (auto& light : m_lights) light.Cleanup();
	for (const auto& shader : m_shaders) shader.second->Cleanup();
}

void GameController::CubeMovement() {
	for (auto it = m_cubes.begin(); it != m_cubes.end();) {
		auto& cube = *it;
		vec3 cubePos = cube.GetPosition();
		vec3 cubeToSphere = m_sphere.GetPosition() - cubePos;
		if (dot(cubeToSphere, cubeToSphere) < .1f) {
			cube.Cleanup();
			it = m_cubes.erase(it);
		}
		else {
			vec3 velocity = glm::normalize(cubeToSphere) * .5f;
			cube.SetPosition(cubePos + velocity * dt);
			++it;
		}
	}
}

void GameController::SpawnCube() {
	static int old_state = GLFW_RELEASE;
	int new_state = glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT);
	if (new_state == GLFW_RELEASE && old_state == GLFW_PRESS) {
		auto mesh = Mesh();
		mesh.Create(m_shaders["box"].get(), &m_cubeModel);
		mesh.SetLightMesh(m_lights);
		mesh.SetLightColor(vec3(1.f));
		mesh.SetPosition(vec3(glm::linearRand(-3.f, 3.f), glm::linearRand(-3.f, 3.f), glm::linearRand(-3.f, 3.f)));
		mesh.SetScale(vec3(.2f));
		m_cubes.push_back(mesh);
	}
	old_state = new_state;
}

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

void GameController::ShaderInit(ShaderMap& shaderMap) const {
	std::ifstream shaderConfig("Res/shaders.config");

	std::string shaderName;
	std::string shaderFileName;
	int textureCount;
	std::string textureName;

	while (shaderConfig) {
		shaderConfig >> shaderName >> shaderFileName >> textureCount;

		shaderMap[shaderName] = make_shared<Shader>();
		shaderMap[shaderName]->LoadShaders(("Res/Shaders/" + shaderFileName + ".vert").c_str(), ("Res/Shaders/" + shaderFileName + ".frag").c_str());

		for (int i = 0; i < textureCount; i++) {
			shaderConfig >> textureName;
			auto texture = make_shared<Texture>();
			texture->LoadTexture("Res/Textures/" + textureName);

			shaderMap[shaderName]->AddTexture(texture);
		}
	}
}

void GameController::ModelInit(objl::Loader& loader, const char* filename) const {
	M_ASSERT(loader.LoadFile(filename) == true, "Failed to load mesh");

	// Calculating tangent space for normal map
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
}
