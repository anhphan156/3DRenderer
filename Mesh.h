#pragma once
#ifndef MESH_H
#define MESH_H

#include <vector>
#include "StandardIncludes.h"
#include "Texture.h"
#include "Shape.h"

class Mesh {
public:
	Mesh();
	Mesh(const Shape&);
	virtual ~Mesh();

	void Create(class Shader* _shader);
	void Cleanup();
	void Render(const mat4&, const mat4&);

	void SetLightPos(const vec3& lightPos) { m_lightPos = lightPos; }

	void SetPosition(const vec3& position) { m_position = position; }
	void SetRotation(float angle, const vec3& rotationAxis) { m_angle = angle; m_rotationAxis = rotationAxis; }
	void SetScale(const vec3& scale) { m_scale = scale; }

	void SetShape(const Shape& shape) { m_shape = shape; }

private:
	GLuint m_vao;
	GLuint m_ib;
	GLuint m_vertexBuffer;
	std::vector<GLuint> m_indexData;
	std::vector<GLfloat> m_vertexData;

	Shape m_shape;

	class Shader* m_shader;
	Texture m_textures[3];

	vec3 m_lightPos;

	// Transform
	vec3 m_position;
	float m_angle;
	vec3 m_rotationAxis;
	vec3 m_scale;

	mat4 m_world;
};

#endif
