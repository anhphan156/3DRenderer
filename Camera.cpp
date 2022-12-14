#include "Camera.h"
#include <iostream>

Camera::Camera() {
	m_projection = glm::mat4(1.f);
	m_view = glm::mat4(1.f);
	m_position = glm::vec3(0.f);
	m_lookAt = glm::vec3(0.f);
	m_up = vec3(0.f, 1.f, 0.f);
}

Camera::Camera(Resolution _resolution, const vec3& position, const vec3& lookAt) {
	m_position = position;
	m_lookAt = lookAt;
	m_up = vec3(0.f, 1.f, 0.f);
	m_forward = glm::normalize(m_lookAt - m_position);
	m_right = glm::cross(m_forward, m_up);

	m_view = glm::lookAt(
		m_position,
		m_lookAt,
		m_up
	);
	
	m_projection = glm::perspective(
		3.14f / 4.f,
		(float)_resolution.m_width / (float)_resolution.m_height,
		0.1f,
		100.f
	);
}

vec3 Camera::getWSCamera() const
{
	//glm::vec4 wsCameraHomo = glm::inverse(m_projection * m_view) * glm::vec4(0.f, 0.f, -1.f, 0.f);
	//vec3 wsCamera = vec3(wsCameraHomo)/ wsCameraHomo.w;

	//return wsCamera;

	return m_position;
}

void Camera::cameraDisplacement(vec3 velocity) {
	m_position += velocity;
	m_lookAt += velocity;
	m_view = glm::lookAt(
		m_position,
		m_lookAt,
		glm::vec3(0.f, 1.f, 0.f)
	);
}

void Camera::cameraTurn(float yaw, float pitch) {
	m_forward = glm::rotate(mat4(1.f), pitch, m_right) * glm::rotate(mat4(1.f), yaw, m_up) * glm::vec4(m_forward, 0.f);
	m_right = cross(m_forward, m_up);
	m_lookAt = m_position + m_forward;
	m_view = glm::lookAt(
		m_position,
		m_lookAt,
		m_up
	);
}

Camera::~Camera() {}
