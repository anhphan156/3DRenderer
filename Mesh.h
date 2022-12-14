#pragma once
#ifndef MESH_H
#define MESH_H

#include "StandardIncludes.h"
#include "Texture.h"
#include "Camera.h"
#include <OBJ_Loader.h>
#include <functional>

class Mesh {
public:
	Mesh();
	virtual ~Mesh();

	void Create(class Shader* _shader, const objl::Loader* _loader, int _instanceCount = 1);
	void Cleanup();
	void Render(const Camera&);

	void SetName(const std::string& name) { m_name = name; }

	void SetLightColor(const vec3 color) { m_lightColor = color; }
	void SetLightMesh(vector<Mesh>* lights) { m_lights = lights; }
	void SetLightStrength(float s) { m_lightStrength = s; }
	float GetLightStrength() const { return m_lightStrength; }
	void SetSpecularColor(const vec3 c) { m_specularColor = c; }
	void SetSpecularStrength(const float s) { m_specularStrength = s; }
	vec3 GetSpecularColor() const { return m_specularColor; }
	float GetSpecularStrength() const { return m_specularStrength; }

	void SetPosition(const vec3& position) { m_position = position; }
	void SetRotation(float angle, const vec3& rotationAxis) { m_angle = angle; m_rotationAxis = rotationAxis; }
	void SetScale(const vec3& scale) { m_scale = scale; }

	vec3 GetPosition() const { return m_position; }

	std::function<void(float)> OnUpdate;

	std::string concat(std::string s1, int i, std::string s2);

private:
	std::string m_name;
	GLuint m_vao;
	GLuint m_vertexBuffer;
	GLuint m_ibo;
	GLuint m_instanceBuffer;
	GLsizei m_indiciesCount;

	std::vector<float> m_iboData;
	std::vector<float> m_vertexData;
	std::vector<float> m_instanceData;

	int m_instanceCount;
	bool m_enableInstancing;
	int m_elementSize;

	class Shader* m_shader;

	vector<Mesh>* m_lights = nullptr;
	vec3 m_lightColor;
	float m_lightStrength;
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
