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

	void SetLightColor(const vec3 color) { m_lightColor = color; }
	void SetLightMesh(const vector<Mesh>& lights) { m_lights = lights; }

	void SetPosition(const vec3& position) { m_position = position; }
	void SetRotation(float angle, const vec3& rotationAxis) { m_angle = angle; m_rotationAxis = rotationAxis; }
	void SetScale(const vec3& scale) { m_scale = scale; }

	vec3 GetPosition() const { return m_position; }

	std::string concat(std::string s1, int i, std::string s2);

private:
	GLuint m_vao;
	GLuint m_ib;
	GLuint m_vertexBuffer;

	Shape m_shape;

	class Shader* m_shader;

	vector<Mesh> m_lights;
	vec3 m_lightColor;

	// Transform
	vec3 m_position;
	float m_angle;
	vec3 m_rotationAxis;
	vec3 m_scale;

	mat4 m_world;
};

#endif
