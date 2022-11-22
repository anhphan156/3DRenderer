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
	void ShaderInit(ShaderMap& shaderMap) const;
	void ModelInit(objl::Loader& loader, const char* filename) const;

	void Run();

	void keyInputHandling();
	void mouseInputHandling();

	void SpawnCube();
	void CubeMovement();

private:
	Camera m_camera;
	GLFWwindow* m_window;

	Mesh m_sphere;
	Mesh m_teapot;

	vector<Mesh> m_cubes;
	vector<Mesh> m_lights;
	ShaderMap m_shaders;

	objl::Loader m_teapotModel; 
	objl::Loader m_sphereModel;
	objl::Loader m_cubeModel;

	float dt = 0.f;
};

#endif // !GAME_CONTROLLER_H

