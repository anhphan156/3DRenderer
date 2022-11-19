#pragma once
#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "Singleton.h"
#include "Mesh.h"
#include "Camera.h"
#include <string>
#include <memory>
#include <map>
#include <OBJ_Loader.h>

using std::shared_ptr;
using std::make_shared;

typedef std::map<std::string, shared_ptr<class Shader>> ShaderMap;
typedef std::map<std::string, shared_ptr<class Texture>> TextureMap;

class GameController : public Singleton<GameController> {
public:
	GameController();
	virtual ~GameController();

	void Initialize();
	void Run();

	void keyInputHandling();
	void mouseInputHandling(float xVec, float yVec);

	void ShaderInit(ShaderMap& shaderMap) const;

private:
	vector<Mesh> m_meshes;
	Camera m_camera;
	GLFWwindow* m_window;

	float dt = 0.f;
};

#endif // !GAME_CONTROLLER_H

