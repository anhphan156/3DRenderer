#include "WindowController.h"
#include "GameController.h"
#include <chrono>
#include <thread>
#include <iostream>

GameController::GameController() {
	m_mesh = {};
	m_shader = {};
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
	m_shader = Shader();
	m_shader.LoadShaders("VertexShader.vert", "FragmentShader.frag");

	m_mesh = Mesh();
	m_mesh.Create(&m_shader);


	int framecount = 0;
	dt = 1 / FPS; // second
	float timePreviousFrame = glfwGetTime();
	do {

		// Render
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		m_mesh.Render(m_camera.getView(), m_camera.getProjection());
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
