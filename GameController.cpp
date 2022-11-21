#include "WindowController.h"
#include "GameController.h"
#include "Shader.h"
#include "Texture.h"
#include "Font.h"
#include <chrono>
#include <thread>
#include <iostream>
#include <fstream>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

GameController::GameController() {
	m_camera = {};
	m_meshes.clear();
}
GameController::~GameController(){}

void GameController::keyInputHandling() {
	glfwPollEvents();

	vec3 cameraVelocity = vec3(0.f);
	if (glfwGetKey(m_window, GLFW_KEY_A) != GLFW_RELEASE) cameraVelocity = -m_camera.getRight();
	if (glfwGetKey(m_window, GLFW_KEY_D) != GLFW_RELEASE) cameraVelocity = m_camera.getRight();
	if (glfwGetKey(m_window, GLFW_KEY_W) != GLFW_RELEASE) cameraVelocity = m_camera.getForward();
	if (glfwGetKey(m_window, GLFW_KEY_S) != GLFW_RELEASE) cameraVelocity = -m_camera.getForward();
	if (glfwGetKey(m_window, GLFW_KEY_Q) != GLFW_RELEASE) cameraVelocity = -m_camera.getUp();
	if (glfwGetKey(m_window, GLFW_KEY_E) != GLFW_RELEASE) cameraVelocity = m_camera.getUp();

	if (glfwGetKey(m_window, GLFW_KEY_R) != GLFW_RELEASE) normalmap = 1.f - normalmap;

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

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile("Res/Models/teapot.obj", aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	// Font Iinit
	Font f = Font();
	f.Create(shaders["font"].get(), "Arial.ttf", 100);

	// light mesh init
	vec3 lightPos = vec3(0.f, 0.f, 2.f);
	vector<Mesh> lights;
	for (int i = 0; i < 1; i++) {
		auto mesh = Mesh();
		mesh.Create(shaders["sphere"].get(), scene);
		mesh.SetPosition(lightPos);
		mesh.SetScale(vec3(.1f));
		//mesh.SetLightColor(vec3(glm::linearRand(0.f, 1.f), glm::linearRand(0.f, 1.f), glm::linearRand(0.f, 1.f)));
		mesh.SetLightColor(vec3(1.f));
		lights.push_back(mesh);
	}

	//// cube mesh init
	//for (int col = 0; col < 10; col++) {
	//	for (int count = 0; count < 10; count++) {
	//		auto mesh = Mesh();
	//		mesh.Create(shaders["crate"].get(), &loader);
	//		mesh.SetLightMesh(lights);
	//		mesh.SetScale(vec3(.5f));
	//		mesh.SetPosition(vec3(0.f, -.5f + count / 10.f, -.2f + col / 10.f) * 5.f);
	//		m_meshes.push_back(mesh);
	//	}
	//}
	auto mesh = Mesh();
	mesh.Create(shaders["crate"].get(), scene);
	mesh.SetLightMesh(lights);
	mesh.SetPosition(vec3(0.f, -1.f, 0.f));
	m_meshes.push_back(mesh);

	dt = 1 / FPS; // second
	float timePreviousFrame = glfwGetTime();
	do {
		// Input
		keyInputHandling();
		mouseInputHandling();

		// Render
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		for (auto& mesh : lights) {
			mesh.Render(m_camera);
		}
		for (auto& mesh : m_meshes) {
			//mesh.SetRotation((float)glfwGetTime(), vec3(1.f, 0.f, 0.f));
			mesh.Render(m_camera);
		}
		glUseProgram(shaders["crate"]->GetProgramID());
		shaders["crate"]->SetUniformFloat("u_nm", normalmap);
		f.RenderText((normalmap == 1.f ? "normal map"  : "vertex normal") + std::to_string(normalmap), 10.f, 500.f, .5f, vec3(.8f));
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
