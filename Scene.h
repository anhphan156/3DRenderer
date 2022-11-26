#pragma once
#ifndef SCENE_H
#define SCENE_H

#include "Mesh.h"
#include <vector>

struct Scene {
	std::vector<Mesh> m_lights;
	std::vector<Mesh> m_objects;
	std::vector<Mesh> m_transluscentObjects;
};

#endif
