#pragma once
#ifndef SCENE_H
#define SCENE_H

#include "Mesh.h"
#include <vector>
#include <memory>
#include "Skybox.h"
#include "Camera.h"
#include "PostProcessor.h"

struct Scene {
	std::vector<Mesh> m_lights; 
	std::vector<Mesh> m_objects;
	std::vector<Mesh> m_transluscentObjects;
	Camera m_camera;
	std::shared_ptr<Skybox> m_skybox = nullptr;
	std::shared_ptr<PostProcessor> m_postProcessor = nullptr;
};

#endif
