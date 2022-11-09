#include "WindowController.h"
#include "GameController.h"
#include "Shape.h"
#include <chrono>
#include <thread>
#include <iostream>

GameController::GameController() {
	m_camera = {};
}
GameController::~GameController(){}

void GameController::keyInputHandling() {
	glfwPollEvents();

	vec3 cameraVelocity = vec3(0.f, 0.f, 0.f);
	if (glfwGetKey(m_window, GLFW_KEY_A) != GLFW_RELEASE) cameraVelocity.x = -1.f;
	if (glfwGetKey(m_window, GLFW_KEY_D) != GLFW_RELEASE) cameraVelocity.x = 1.f;
	if (glfwGetKey(m_window, GLFW_KEY_W) != GLFW_RELEASE) cameraVelocity.z = -1.f;
	if (glfwGetKey(m_window, GLFW_KEY_S) != GLFW_RELEASE) cameraVelocity.z = 1.f;
	if (glfwGetKey(m_window, GLFW_KEY_Q) != GLFW_RELEASE) cameraVelocity.y = -1.f;
	if (glfwGetKey(m_window, GLFW_KEY_E) != GLFW_RELEASE) cameraVelocity.y = 1.f;

	m_camera.cameraDisplacement(cameraVelocity * dt);
}

void GameController::mouseInputHandling(float xVec, float yVec) {
	m_camera.cameraTurn(vec3(xVec, yVec * -1, 0.f));
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE) return;

	static double oldXPos;
	static double oldYPos;

	float xVec = (xpos - oldXPos > 0.f) ? .1f : -.1f;
	float yVec = (ypos - oldYPos > 0.f) ? .1f : -.1f;

	GameController::GetInstance().mouseInputHandling(xVec, yVec);

	oldXPos = xpos;
	oldYPos = ypos;
}

void GameController::Initialize() {
	m_window = WindowController::GetInstance().GetWindow(); // glfwInit()
	M_ASSERT(glewInit() == GLEW_OK, "Failed to initialize GLEW");
	glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GL_TRUE);
	glClearColor(0.f, 0.f, .4f, 1.f);

	glEnable(GL_DEPTH_TEST);

	m_camera = Camera(WindowController::GetInstance().GetResolution());
}

void GameController::Run() {
	Shader crateShader = Shader();
	crateShader.LoadShaders("crate.vert", "crate.frag");

	Shader sphereShader = Shader();
	sphereShader.LoadShaders("sphere.vert", "sphere.frag");

	Shape unwrappedCube = UnWrappedCube();

	vec3 lightPos = vec3(2.f, 2.f, 2.f);

	m_meshes[0] = Mesh(unwrappedCube);
	m_meshes[0].Create(&crateShader);
	m_meshes[0].SetPosition(vec3(0.f, 0.f, 0.f));
	m_meshes[0].SetLightPos(lightPos);

	m_meshes[1] = Mesh(unwrappedCube);
	m_meshes[1].Create(&sphereShader);
	m_meshes[1].SetPosition(lightPos);
	m_meshes[1].SetScale(vec3(.3f));

	int framecount = 0;
	dt = 1 / FPS; // second
	float timePreviousFrame = glfwGetTime();
	do {
		//m_meshes[0].Render(m_camera.getView(), m_camera.getProjection());
		m_meshes[1].SetScale(vec3(cos((float)glfwGetTime())/3.f));

		// Render
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		for (auto& mesh : m_meshes) {
			mesh.SetRotation((float)glfwGetTime(), vec3(0.f, 1.f, 0.f));
			mesh.Render(m_camera.getView(), m_camera.getProjection());
		}
		glfwSwapBuffers(m_window);

		// Input
		keyInputHandling();
		glfwSetCursorPosCallback(m_window, cursor_position_callback);

		// Frame rate
		float sleepTime = MPF - (glfwGetTime() - timePreviousFrame) * 1000;
		if (sleepTime > 0) {
			std::this_thread::sleep_for(std::chrono::milliseconds((long)sleepTime));
		}
		dt = (glfwGetTime() - timePreviousFrame);
		//std::cout << dt << std::endl;
		//std::cout << ++framecount << " " << glfwGetTime() <<  std::endl;
		timePreviousFrame = glfwGetTime();

	} while (glfwGetKey(m_window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(m_window) == 0);
}
