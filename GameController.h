#pragma once
#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "Singleton.h"
#include "Mesh.h"
#include "Camera.h"
#include "Scene.h"
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
	void mouseInputHandling();

	void ShaderInit(ShaderMap& shaderMap) const;
	void ModelInit(objl::Loader& loader) const;
	void SceneInit();

private:
	vector<Mesh> m_meshes;
	Camera m_camera;
	GLFWwindow* m_window;
	Scene m_scene;

	float dt = 0.f;
};

#endif // !GAME_CONTROLLER_H

