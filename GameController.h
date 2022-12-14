#pragma once
#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "Singleton.h"
#include "Mesh.h"
#include "Camera.h"
#include <string>
#include <memory>
#include "PostProcessor.h"
#include "ResourceLoader.h"

class GameController : public Singleton<GameController> {
public:
	GameController();
	virtual ~GameController();

	void Initialize();
	void Run();

	void keyInputHandling();
	void mouseInputHandling();

	void Framerate();
	void Render();
	vec3 MouseMovement();

private:
	GLFWwindow* m_window;
	ResourceLoader m_resourceLoader;
	shared_ptr<Scene> m_activeScene;
	std::map<float, Mesh*> sorted;

	float dt = 1 / FPS;
	float framecount = 0.f;
	float timePreviousFrame = 0.f;
	double xpos, ypos;
	std::string leftBtn, middleBtn;
};

#endif // !GAME_CONTROLLER_H

