#include "Skybox.h"
#include "Shader.h"

Skybox::Skybox()
{
	m_shader = nullptr;
	m_texture = {};
	m_vertexBuffer = 0;
	m_vertexData.clear();
}

void Skybox::Create(Shader* _shader, objl::Loader* model, vector<std::string> _faces)
{
	m_shader = _shader;
	m_model = model;

	for (unsigned int i = 0; i < model->LoadedMeshes.size(); ++i) {
		objl::Mesh mesh = model->LoadedMeshes[i];

		for (unsigned int j = 0; j < model->LoadedVertices.size(); ++j) {
			m_vertexData.push_back(mesh.Vertices[j].Position.X);
			m_vertexData.push_back(mesh.Vertices[j].Position.Y);
			m_vertexData.push_back(mesh.Vertices[j].Position.Z);
		}
	}

	m_texture = Texture();
	m_texture.LoadCubemap(_faces);

	GLCALL(glGenBuffers(1, &m_vertexBuffer));
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer));
	GLCALL(glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(float), m_vertexData.data(), GL_STATIC_DRAW));

	//GLCALL(glGenBuffers(1, &m_ibo));
	//GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo));
	//GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_model->LoadedIndices.size() * sizeof(float), m_model->LoadedIndices.data(), GL_STATIC_DRAW));
}

void Skybox::Cleanup()
{
	m_shader->ClearTexture();
	m_shader->Cleanup();
	glDeleteBuffers(1, &m_vertexBuffer);
}

void Skybox::Render(glm::mat4 _pv)
{
	GLCALL(glDisable(GL_CULL_FACE));
	GLCALL(glDisable(GL_DEPTH_TEST));

	SetShaderVariables(_pv);
	BindAttributes();
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer));
	GLCALL(glDrawArrays(GL_TRIANGLES, 0, m_vertexData.size()));

	//GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo));
	//GLCALL(glDrawElements(GL_TRIANGLES, m_model->LoadedIndices.size(), GL_UNSIGNED_INT, nullptr));

	GLCALL(glEnable(GL_DEPTH_TEST));
	GLCALL(glEnable(GL_CULL_FACE));
}

void Skybox::SetShaderVariables(glm::mat4 _pv)
{
	glUseProgram(m_shader->GetProgramID());
	m_shader->SetUniformMat4("u_pv", _pv);
	GLCALL(glActiveTexture(GL_TEXTURE_CUBE_MAP));
	GLCALL(glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture.GetCubemapTexture()));
	GLint textureLoc = glGetUniformLocation(m_shader->GetProgramID(), "u_texture");
	if (textureLoc != -1) GLCALL(glUniform1i(textureLoc, 0));
}

void Skybox::BindAttributes()
{
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer));

	GLCALL(glEnableVertexAttribArray(m_shader->GetAttriVertices()));
	GLCALL(glVertexAttribPointer(m_shader->GetAttriVertices(), 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
}
