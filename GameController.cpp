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

void GameController::keyInputHandling(int key, int action) {
	if (key == GLFW_KEY_A) {
		m_camera.cameraDisplacement(glm::vec3(-.1f, 0.f, 0.f));
	}

	if (key == GLFW_KEY_D) {
		m_camera.cameraDisplacement(glm::vec3(.1f, 0.f, 0.f));
	}

	if (key == GLFW_KEY_W) {
		m_camera.cameraDisplacement(glm::vec3(0.f, 0.f, -.1f));
	}

	if (key == GLFW_KEY_S) {
		m_camera.cameraDisplacement(glm::vec3(0.f, 0.f, .1f));
	}

	if (key == GLFW_KEY_E) {
		m_camera.cameraDisplacement(glm::vec3(0.f, .1f, 0.f));
	}

	if (key == GLFW_KEY_Q) {
		m_camera.cameraDisplacement(glm::vec3(0.f, -.1f, .1f));
	}
}

void GameController::mouseInputHandling(float xVec, float yVec) {
	m_camera.cameraTurn(vec3(xVec, yVec * -1, 0.f));
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	GameController::GetInstance().keyInputHandling(key, action);
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
	GLFWwindow* window = WindowController::GetInstance().GetWindow(); // glfwInit()
	M_ASSERT(glewInit() == GLEW_OK, "Failed to initialize GLEW");
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glClearColor(0.f, 0.f, .4f, 1.f);

	m_camera = Camera(WindowController::GetInstance().GetResolution());
}

void GameController::Run() {
	m_shader = Shader();
	m_shader.LoadShaders("VertexShader.vert", "FragmentShader.frag");

	m_mesh = Mesh();
	m_mesh.Create(&m_shader);

	GLFWwindow* window = WindowController::GetInstance().GetWindow(); // glfwInit()

	int framecount = 0;
	float dt = 1 / FPS; // second
	float timePreviousFrame = glfwGetTime();
	do {

		glClear(GL_COLOR_BUFFER_BIT);
		m_mesh.Render(m_camera.getView(), m_camera.getProjection());
		glfwSwapBuffers(window);

		glfwSetKeyCallback(window, keyCallback);
		glfwSetCursorPosCallback(window, cursor_position_callback);

		glfwPollEvents();

		// Time
		float sleepTime = MPF - (glfwGetTime() - timePreviousFrame) * 1000;
		if (sleepTime > 0) {
			std::this_thread::sleep_for(std::chrono::milliseconds((long)sleepTime));
		}
		dt = (glfwGetTime() - timePreviousFrame);
		//std::cout << dt << std::endl;
		//std::cout << ++framecount << " " << glfwGetTime() <<  std::endl;
		timePreviousFrame = glfwGetTime();

	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
}
