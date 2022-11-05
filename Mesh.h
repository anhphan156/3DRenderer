#pragma once
#ifndef MESH_H
#define MESH_H

#include <vector>
#include "StandardIncludes.h"
#include "Texture.h"

class Mesh {
public:
	Mesh();
	virtual ~Mesh();

	void Create(class Shader* _shader);
	void Cleanup();
	void Render(const mat4&, const mat4&);

	void SetPosition(const vec3& position) { m_position = position; }
	void SetRotation(float angle, const vec3& rotationAxis) { m_angle = angle; m_rotationAxis = rotationAxis; }
	void SetScale(const vec3& scale) { m_scale = scale; }

	void SetColors(const vec3& yuv, bool inverted);

private:
	GLuint m_vao;
	GLuint m_ib;
	GLuint m_vertexBuffer;
	std::vector<GLuint> m_indexData;
	std::vector<GLfloat> m_vertexData;

	class Shader* m_shader;
	Texture m_textures[2];

	// Transform
	vec3 m_position;
	float m_angle;
	vec3 m_rotationAxis;
	vec3 m_scale;

	mat4 m_world;
};

#endif
