#pragma once

#ifndef STANDARD_INCLUDES_H
#define STANDARD_INCLUDES_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#ifdef _WIN32
#include <Windows.h>
#define M_ASSERT(_cond, _msg) \
	if(!(_cond)) { OutputDebugStringA(_msg); std::abort(); glfwTerminate(); }
#endif

#include <string>
#include <fstream>

const int FPS = 60;
const float MPF = 1000 / FPS;

#include "Resolution.h"

using glm::vec3;
using glm::mat4;

#endif // !STANDARD_INCLUDES_H
