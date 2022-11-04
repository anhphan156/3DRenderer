#include "Camera.h"
#include <iostream>

Camera::Camera() {
	m_projection = glm::mat4(1.f);
	m_view = glm::mat4(1.f);
	m_location = glm::vec3(0.f);
}

Camera::Camera(Resolution _resolution) {
	m_location = glm::vec3(0.f, 5.f, 10.f);
	m_lookAt = glm::vec3(0.f, 0.f, 0.f);

	m_view = glm::lookAt(
		m_location,
		m_lookAt,
		glm::vec3(0.f, 1.f, 0.f)
	);
	
	m_projection = glm::perspective(
		3.14f / 4.f,
		(float)_resolution.m_width / (float)_resolution.m_height,
		0.1f,
		100.f
	);
}

vec3 Camera::getWSCamera()
{
	glm::vec4 wsCameraHomo = glm::inverse(m_projection * m_view) * glm::vec4(0.f, 0.f, -1.f, 0.f);
	vec3 wsCamera = vec3(wsCameraHomo)/ wsCameraHomo.w;

	return wsCamera;
}

void Camera::cameraDisplacement(vec3 velocity) {
	m_location += velocity;
	m_lookAt += velocity;
	m_view = glm::lookAt(
		m_location,
		m_lookAt,
		glm::vec3(0.f, 1.f, 0.f)
	);
}

void Camera::cameraTurn(vec3 lookAt) {
	m_lookAt += lookAt;
	m_view = glm::lookAt(
		m_location,
		m_lookAt,
		glm::vec3(0.f, 1.f, 0.f)
	);
}

Camera::~Camera() {}
