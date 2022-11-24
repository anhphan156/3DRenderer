#pragma once
#ifndef SKYBOX_H
#define SKYBOX_H

#include "Mesh.h"
#include "Texture.h"
#include <OBJ_Loader.h>

class Skybox {
public:
	Skybox();
	virtual ~Skybox() = default;

	void Create(class Shader* _shader, objl::Loader* model, vector<std::string> _faces);
	void Cleanup();
	void Render(glm::mat4 _pv);

private:
	void SetShaderVariables(glm::mat4 _pv);
	void BindAttributes();

	class Shader* m_shader;
	objl::Loader* m_model;
	Texture m_texture;
	GLuint m_vertexBuffer;
	GLuint m_ibo;
	std::vector<GLfloat> m_vertexData;
};

#endif
