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

	m_camera.cameraDisplacement(cameraVelocity * 10.f * dt);
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

	std::string shaderName, shaderFileName, textureName;
	int textureCount;
	float normalEnabled;

	while (shaderConfig) {
		shaderConfig >> shaderName >> shaderFileName >> textureCount >> normalEnabled;

		shaderMap[shaderName] = make_shared<Shader>();
		shaderMap[shaderName]->LoadShaders(("Res/Shaders/" + shaderFileName + ".vert").c_str(), ("Res/Shaders/" + shaderFileName + ".frag").c_str());
		shaderMap[shaderName]->SetNormalEnabled(normalEnabled);

		for (int i = 0; i < textureCount; i++) {
			shaderConfig >> textureName;
			auto texture = make_shared<Texture>();
			texture->LoadTexture("Res/Textures/" + textureName);

			shaderMap[shaderName]->AddTexture(texture);
		}
	}
}

void GameController::ModelInit(std::string fileName) {
	objl::Loader loader;
	M_ASSERT(loader.LoadFile("Res/Models/" + fileName) == true, "Failed to load mesh");
	m_models[fileName] = loader;

	for (unsigned int i = 0; i < loader.LoadedMeshes.size(); i++) {
		objl::Mesh& mesh = m_models[fileName].LoadedMeshes[i];

		for (unsigned int i = 0; i < m_models[fileName].LoadedIndices.size(); i += 3) {
			unsigned int index = m_models[fileName].LoadedIndices[i];
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

void GameController::Initialize() {
	m_window = WindowController::GetInstance().GetWindow(); // glfwInit()
	M_ASSERT(glewInit() == GLEW_OK, "Failed to initialize GLEW");
	glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GL_TRUE);
	glClearColor(0,0,0,1);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	auto r = WindowController::GetInstance().GetResolution();
	glViewport(0, 0, r.m_width, r.m_height);
	m_camera = Camera(r);

	srand(time(0));
}

void GameController::Run() {
	// Shader Init
	ShaderInit(m_shaders);

	// Model Init
	ModelInit("sphere.obj");
	ModelInit("cube.obj");
	ModelInit("skybox.obj");
	ModelInit("window.obj");
	ModelInit("teapot.obj");

	// Font Iinit
	Font f = Font();
	f.Create(m_shaders["font"].get(), "Arial.ttf", 100);

	 //Scene Init
	SceneInit();

	// Postprocessing
	m_postProcessor = PostProcessor();
	m_postProcessor.Create(m_shaders["postprocessor"].get());

	// instancing test
	//auto cube = Mesh();
	//cube.Create(m_shaders["brickwall"].get(), &m_models["cube.obj"], 1000);
	//cube.SetLightMesh(m_scene.m_lights);
	//m_scene.m_objects.push_back(cube);

	Skybox skybox;
	skybox.Create(m_shaders["skybox"].get(), &m_models["skybox.obj"], {
		"Res/Textures/cm1/right.jpg",
		"Res/Textures/cm1/left.jpg",
		"Res/Textures/cm1/top.jpg",
		"Res/Textures/cm1/bottom.jpg",
		"Res/Textures/cm1/front.jpg",
		"Res/Textures/cm1/back.jpg",
	});

	dt = 1 / FPS; // second
	float framecount = 0;
	float timePreviousFrame = glfwGetTime();
	do {
		// Input
		glfwPollEvents();
		keyInputHandling();
		mouseInputHandling();

		// Render
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		m_postProcessor.Start();
		mat4 v = mat4(glm::mat3(m_camera.getView()));
		skybox.Render(m_camera.getProjection() * v);
		for (auto& mesh : m_scene.m_lights) {
			mesh.Render(m_camera);
		}
		for (auto& mesh : m_scene.m_objects) {
			//mesh.SetRotation((float)glfwGetTime(), vec3(0.f, 1.f, 0.f));
			mesh.Render(m_camera);
		}
		for (auto& mesh : m_scene.m_transluscentObjects) mesh.Render(m_camera);

		m_postProcessor.End();

		f.RenderText("fps: " + std::to_string(framecount / timePreviousFrame), 10.f, 500.f, .2f, {1.f, 1.f, 0.f});
		f.RenderText("dt: " + std::to_string(dt), 10.f, 550.f, .2f, {1.f, 1.f, 0.f});
		glfwSwapBuffers(m_window);

		// Frame rate
		float sleepTime = MPF - (glfwGetTime() - timePreviousFrame) * 1000;
		if (sleepTime > 0) {
			//std::this_thread::sleep_for(std::chrono::milliseconds((long)sleepTime));
		}
		dt = (glfwGetTime() - timePreviousFrame);
		timePreviousFrame = glfwGetTime();
		framecount++;

	} while (glfwGetKey(m_window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(m_window) == 0);

	for (auto& m : m_scene.m_lights) m.Cleanup();
	for (auto& m : m_scene.m_objects) m.Cleanup();
	for (auto& m : m_scene.m_transluscentObjects) m.Cleanup();
	for (const auto& shader : m_shaders) shader.second->Cleanup();
	m_postProcessor.Cleanup();
	f.Cleanup();
	skybox.Cleanup();
}

void GameController::SceneInit() {
	std::ifstream sceneFile("Res/Scenes/Scene.txt");

	std::string type, name, model, shader, lightType;
	float lightStrength;
	vec3 position, scale;
	glm::vec4 rotation;

	while (sceneFile) { // fix to read til the end
		sceneFile >> type;

		if (type == "l") {
			sceneFile >> name >> model >> shader >> lightType >> lightStrength >>
			position.x >> position.y >> position.z >>
			scale.x >> scale.y >> scale.z >>
			rotation.x >> rotation.y >> rotation.z, rotation.w;

			Mesh mesh;
			mesh.Create(m_shaders[shader].get(), &m_models[model]);
			mesh.SetPosition(position);
			mesh.SetScale(scale);
			mesh.SetLightStrength(lightStrength);
			m_scene.m_lights.push_back(mesh);
		}

		if (type == "o" || type == "to") {
			sceneFile >> name >> model >> shader >> 
			position.x >> position.y >> position.z >> 
			scale.x >> scale.y >> scale.z >>
			rotation.x >> rotation.y >> rotation.z >> rotation.w;

			Mesh mesh;
			mesh.SetName(name);
			mesh.Create(m_shaders[shader].get(), &m_models[model]);
			mesh.SetPosition(position);
			mesh.SetScale(scale);
			mesh.SetLightMesh(m_scene.m_lights);

			if (type == "o") {
				m_scene.m_objects.push_back(mesh);
			}
			else if (type == "to") {
				m_scene.m_transluscentObjects.push_back(mesh);
			}
		}
	}
}
