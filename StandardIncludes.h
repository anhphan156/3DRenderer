#pragma once

#ifndef STANDARD_INCLUDES_H
#define STANDARD_INCLUDES_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#ifdef _WIN32
#include <Windows.h>
#define M_ASSERT(_cond, _msg) \
	if(!(_cond)) { OutputDebugStringA(_msg); std::abort(); glfwTerminate(); }
#endif

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <memory>
#include <random>

using std::shared_ptr;
using std::make_shared;
using std::vector;

const int FPS = 60;
const float MPF = 1000 / FPS;

#include "Resolution.h"

using glm::vec3;
using glm::mat4;

#endif // !STANDARD_INCLUDES_H
