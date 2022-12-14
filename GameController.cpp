#include "WindowController.h"
#include "GameController.h"
#include "Shader.h"
#include "Font.h"
#include "Scripting.h"
#include <chrono>
#include <thread>
#include <iostream>
#include <fstream>
#include "ToolWindow.h"

using OpenGLTechniques::ToolWindow;

GameController::GameController() {}
GameController::~GameController(){}

void GameController::keyInputHandling() {
	vec3 cameraVelocity = vec3(0.f);
	if (glfwGetKey(m_window, GLFW_KEY_A) != GLFW_RELEASE) cameraVelocity = -m_activeScene->m_camera.getRight();
	if (glfwGetKey(m_window, GLFW_KEY_D) != GLFW_RELEASE) cameraVelocity = m_activeScene->m_camera.getRight();
	if (glfwGetKey(m_window, GLFW_KEY_W) != GLFW_RELEASE) cameraVelocity = m_activeScene->m_camera.getForward();
	if (glfwGetKey(m_window, GLFW_KEY_S) != GLFW_RELEASE) cameraVelocity = -m_activeScene->m_camera.getForward();
	if (glfwGetKey(m_window, GLFW_KEY_Q) != GLFW_RELEASE) cameraVelocity = -m_activeScene->m_camera.getUp();
	if (glfwGetKey(m_window, GLFW_KEY_E) != GLFW_RELEASE) cameraVelocity = m_activeScene->m_camera.getUp();

	m_activeScene->m_camera.cameraDisplacement(cameraVelocity * 10.f * dt);
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

	m_activeScene->m_camera.cameraTurn(-dX, -dY);
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

	auto resolution = WindowController::GetInstance().GetResolution();
	glViewport(0, 0, resolution.m_width, resolution.m_height);

	srand(time(0));
}

void GameController::Run() {
	// Resource Loading
	ResourceLoader::GetInstance().Load();

	// Tool window
	ToolWindow^ toolWindow = gcnew ToolWindow();
	toolWindow->Show();

	// scripts
	Scripting::GetInstance().AttachScripts();
	
	do {
		// Set active scene
		m_activeScene = ResourceLoader::GetInstance().GetScene(toolWindow->gameMode);

		// Input
		glfwPollEvents();
		glfwGetCursorPos(m_window, &xpos, &ypos);
		keyInputHandling();
		mouseInputHandling();
		System::Windows::Forms::Application::DoEvents();

		Scripting::GetInstance().S1SetSpecularValues(vec3(toolWindow->specularR, toolWindow->specularG, toolWindow->specularB), toolWindow->specularStrength);
		Scripting::GetInstance().SetMouseVelocity(MouseMovement());
		Scripting::GetInstance().SetFrequency(toolWindow->frequency);
		Scripting::GetInstance().SetAmplitude(toolWindow->amplitude);
		Scripting::GetInstance().SetTint(toolWindow->tintblue);
		Scripting::GetInstance().SetTransform(toolWindow->translate, toolWindow->rotate, toolWindow->scale);

		// Render
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		Render();
		glfwSwapBuffers(m_window);

		// Frame rate
		Framerate();

	} while (glfwGetKey(m_window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(m_window) == 0);

	ResourceLoader::GetInstance().Cleanup();
}

void GameController::Framerate() {
	float sleepTime = MPF - (glfwGetTime() - timePreviousFrame) * 1000;
	if (sleepTime > 0) {
		//std::this_thread::sleep_for(std::chrono::milliseconds((long)sleepTime));
	}
	dt = (glfwGetTime() - timePreviousFrame);
	timePreviousFrame = glfwGetTime();
	framecount++;
}

void GameController::Render() {
	if (m_activeScene->m_postProcessor) m_activeScene->m_postProcessor->Start();
	
	m_activeScene->m_camera.OnUpdate(dt);

	if(m_activeScene->m_skybox) m_activeScene->m_skybox->Render(m_activeScene->m_camera.getProjection() * mat4(glm::mat3(m_activeScene->m_camera.getView())));

	for (auto& light : m_activeScene->m_lights) {
		light.OnUpdate(dt);
		light.Render(m_activeScene->m_camera);
	}
	for (auto& mesh : m_activeScene->m_objects) {
		mesh.OnUpdate(dt);
		mesh.Render(m_activeScene->m_camera);
	}
	for (auto& mesh : m_activeScene->m_transluscentObjects) mesh.Render(m_activeScene->m_camera);

	auto font = ResourceLoader::GetInstance().GetFont();
	font->RenderText("FPS: " + std::to_string(framecount / timePreviousFrame), 10.f, 50.f, .2f, {1.f, 1.f, 0.f});
	font->RenderText("Mouse Pos: " + std::to_string(xpos) + " " + std::to_string(ypos), 10.f, 100.f, .2f, {1.f, 1.f, 0.f});
	font->RenderText("Left Button: " + leftBtn, 10.f, 150.f, .2f, {1.f, 1.f, 0.f});
	font->RenderText("Middle Button: " + middleBtn, 10.f, 200.f, .2f, {1.f, 1.f, 0.f});

	const auto& object = m_activeScene->m_objects[0];
	font->RenderText(object.GetName() + " Position: " + glm::to_string(object.GetPosition()), 10.f, 250.f, .2f, {1.f, 1.f, 0.f});
	font->RenderText(object.GetName() + " Scale: " + glm::to_string(object.GetScale()), 10.f, 300.f, .2f, {1.f, 1.f, 0.f});
	font->RenderText(object.GetName() + " Rotation: " + glm::to_string(object.GetRotation()), 10.f, 350.f, .2f, {1.f, 1.f, 0.f});

	if (m_activeScene->m_postProcessor) m_activeScene->m_postProcessor->End();
}

vec3 GameController::MouseMovement() 
{
	auto res = WindowController::GetInstance().GetResolution();
	if (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT)) {
		leftBtn = "Down";
		double xvec = xpos - res.m_width / 2.f; 
		double yvec = ypos - res.m_height / 2.f;
		return vec3(xvec, yvec * -1, 0.f) / 150.f;
	}

	if (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_MIDDLE)) {
		middleBtn = "Down";
		double yvec = ypos - res.m_height / 2.f;
		return vec3(0.f, 0.f, yvec) / 20.f;
	}

	leftBtn = "Up";
	middleBtn = "Up";

	return vec3(0.f);
}

