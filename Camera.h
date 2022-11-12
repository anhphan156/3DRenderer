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
	vec3 getLookAt() { return m_lookAt; };
	vec3 getUp() { return m_up; }
	vec3 getWSCamera() const;

	void cameraDisplacement(vec3 displacement);
	void cameraTurn(vec3 lookAt);
	vec3 getCameraFoward() const { return m_cameraForward; }

private:

	mat4 m_projection;
	mat4 m_view;

	vec3 m_location;
	vec3 m_lookAt;
	vec3 m_up;

	vec3 m_cameraForward;
};

#endif
