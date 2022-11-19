#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "StandardIncludes.h"

class Camera {
public:
	Camera();
	Camera(Resolution);
	virtual ~Camera();

	mat4 getProjection() const { return m_projection; };
	mat4 getView() const { return m_view; };
	vec3 getLookAt() const { return m_lookAt; }
	vec3 getForward() const { return m_forward; };
	vec3 getRight() const { return m_right; };
	vec3 getUp() const { return m_up; };
	vec3 getLocation() { return m_location; };
	vec3 getWSCamera() const;

	void cameraDisplacement(vec3 displacement);
	void cameraTurn(float yaw, float pitch);

private:

	mat4 m_projection;
	mat4 m_view;

	vec3 m_location;
	vec3 m_lookAt;
	vec3 m_forward;
	vec3 m_up;
	vec3 m_right;
};

#endif
