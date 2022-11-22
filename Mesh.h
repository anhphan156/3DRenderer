#pragma once
#ifndef MESH_H
#define MESH_H

#include "StandardIncludes.h"
#include "Texture.h"
#include "Camera.h"
#include <OBJ_Loader.h>

class Mesh {
public:
	Mesh();
	virtual ~Mesh();

	void Create(class Shader* _shader, const objl::Loader* _loader);
	void Cleanup();
	void Render(const Camera&);

	void SetLightColor(const vec3& color) { m_lightColor = color; }
	void SetLightMesh(const vector<Mesh>& lights) { m_lights = lights; }
	void SetSpecularColor(const vec3& color) { m_specularColor = color; }
	void SetSpecularStrength(const float strength) { m_specularStrength = strength; }

	void SetPosition(const vec3& position) { m_position = position; }
	void SetRotation(float angle, const vec3& rotationAxis) { m_angle = angle; m_rotationAxis = rotationAxis; }
	void SetScale(const vec3& scale) { m_scale = scale; }

	void SetShader(class Shader* shader) { m_shader = shader; }

	vec3 GetPosition() const { return m_position; }

	std::string concat(std::string s1, int i, std::string s2);

private:
	GLuint m_vao;
	GLuint m_vertexBuffer;
	GLuint m_ibo;
	std::vector<float> m_iboData;
	GLsizei m_indiciesCount;
	std::vector<float> m_vertexData;

	class Shader* m_shader;

	vector<Mesh> m_lights;
	vec3 m_lightColor;
	vec3 m_specularColor;
	float m_specularStrength;

	// Transform
	vec3 m_position;
	float m_angle;
	vec3 m_rotationAxis;
	vec3 m_scale;

	mat4 m_world;
};

#endif
