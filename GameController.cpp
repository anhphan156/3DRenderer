#include "WindowController.h"
#include "GameController.h"
#include "ToolWindow.h"
#include <chrono>
#include <thread>
#include <iostream>

using Exercise2::ToolWindow;

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
	glClearColor(0.f, 0.f, .0f, 1.f);

	m_camera = Camera(WindowController::GetInstance().GetResolution());
}

void GameController::Run() {
	ToolWindow^ window = gcnew Exercise2::ToolWindow();
	window->Show();

	Shader woodShader = Shader();
	woodShader.LoadShaders("wood.vert", "wood.frag");

	m_mesh = Mesh();
	m_mesh.Create(&woodShader);
	m_mesh.SetPosition(vec3(0.f, 0.f, 0.f));
	m_mesh.SetRotation(-3.14f / 4.f, vec3(0.f, 1.f, 0.f));

	int framecount = 0;
	dt = 1 / FPS; // second
	float timePreviousFrame = glfwGetTime();
	do {
		System::Windows::Forms::Application::DoEvents();
		m_mesh.SetColors(vec3(ToolWindow::Y, ToolWindow::U, ToolWindow::V) / 100.f, ToolWindow::InvertColors);
		// Render
		glClear(GL_COLOR_BUFFER_BIT);
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
		timePreviousFrame = glfwGetTime();

	} while (glfwGetKey(m_window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(m_window) == 0);
}
