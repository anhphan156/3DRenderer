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
	vec3 getLocation() { return m_location; };

	void cameraDisplacement(vec3 displacement);
	void cameraTurn(vec3 lookAt);

private:

	mat4 m_projection;
	mat4 m_view;

	vec3 m_location;
	vec3 m_lookAt;
};

#endif
