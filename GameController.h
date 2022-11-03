#pragma once
#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "Singleton.h"
#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"

class GameController : public Singleton<GameController> {
public:
	GameController();
	virtual ~GameController();

	void Initialize();
	void Run();

	void keyInputHandling();
	void mouseInputHandling(float xVec, float yVec);

private:
	Mesh m_mesh;
	Shader m_shader;
	Camera m_camera;
	GLFWwindow* m_window;

	float dt = 0.f;
};

#endif // !GAME_CONTROLLER_H

