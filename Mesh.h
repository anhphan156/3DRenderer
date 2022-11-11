#pragma once
#ifndef MESH_H
#define MESH_H

#include <vector>
#include "StandardIncludes.h"
#include "Texture.h"
#include "Camera.h"
#include "Shape.h"

class Mesh {
public:
	Mesh(const Shape&);
	virtual ~Mesh();

	void Create(class Shader* _shader);
	void Cleanup();
	void Render(const Camera&);

	void SetLightPos(const vec3& lightPos) { m_lightPos = lightPos; }

	void SetPosition(const vec3& position) { m_position = position; }
	void SetRotation(float angle, const vec3& rotationAxis) { m_angle = angle; m_rotationAxis = rotationAxis; }
	void SetScale(const vec3& scale) { m_scale = scale; }

	void SetShape(const Shape& shape) { m_shape = shape; }

private:
	GLuint m_vao;
	GLuint m_ib;
	GLuint m_vertexBuffer;

	Shape m_shape;

	class Shader* m_shader;

	vec3 m_lightPos;

	// Transform
	vec3 m_position;
	float m_angle;
	vec3 m_rotationAxis;
	vec3 m_scale;

	mat4 m_world;
};

#endif
