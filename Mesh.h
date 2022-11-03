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
	void Render(glm::mat4, glm::mat4);

private:
	GLuint m_vao;
	GLuint m_ib;
	GLuint m_vertexBuffer;
	std::vector<GLuint> m_indexData;
	std::vector<GLfloat> m_vertexData;

	class Shader* m_shader;
	Texture m_texture;

	glm::mat4 m_world;
};

#endif
