#pragma once

#ifndef STANDARD_INCLUDES_H
#define STANDARD_INCLUDES_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/random.hpp>

#ifdef _WIN32
#include <Windows.h>
#define M_ASSERT(_cond, _msg) \
	if(!(_cond)) { OutputDebugStringA(_msg); std::abort(); glfwTerminate(); }
#endif

#include <string>
#include <vector>
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

namespace Utils {
	inline float lerp(float a, float b, float n) {
		n = glm::clamp(n, 0.f, 1.f);
		return (1 - n) * a + n * b;
	}
	inline float invLerp(float a, float b, float n) {
		n = glm::clamp(n, a, b);
		return (a - n) / (a - b);
	}
	inline float remap(float a, float b, float c, float d, float n) {
		return lerp(c, d, invLerp(a, b, n));
	}
}

#endif // !STANDARD_INCLUDES_H
