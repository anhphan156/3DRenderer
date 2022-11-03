#include "Mesh.h"
#include "shader.h"
#include "Resolution.h"
#include "WindowController.h"

Mesh::Mesh() {
	m_vao = 0;
	m_vertexBuffer = 0;
	m_ib = 0;
	m_vertexData = {};
	m_indexData = {};
	m_shader = nullptr;
	m_world = glm::mat4(1.f);
}

Mesh::~Mesh() {
	m_vertexBuffer = 0;
	m_vertexData = {};
}

void Mesh::Create(Shader* _shader) {
	m_shader = _shader;

	m_textures[0] = Texture();
	m_textures[0].LoadTexture("Res/wood.png");
	m_textures[1] = Texture();
	m_textures[1].LoadTexture("Res/grunge.png");
	m_textures[2] = Texture();
	m_textures[2].LoadTexture("Res/box-alpha.png");

	//vao
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	// Vertex array
	m_vertexData = {
		 /* Position    *//* Normal    *//* TexCoords */
		 // Up
		 -1.f,  1.f,  1.f, 0.f, 1.f, 0.f, 0.33f, 0.33f,
		 -1.f,  1.f, -1.f, 0.f, 1.f, 0.f, 0.33f, 0.66f,
		  1.f,  1.f, -1.f, 0.f, 1.f, 0.f, 0.66f, 0.66f,
		  1.f,  1.f,  1.f, 0.f, 1.f, 0.f, 0.66f, 0.33f,

		 // Down
		 -1.f, -1.f,  1.f, 0.f, -1.f, 0.f, 0.f, 0.f,
		 -1.f, -1.f, -1.f, 0.f, -1.f, 0.f, 0.f, 0.33f,
		  1.f, -1.f, -1.f, 0.f, -1.f, 0.f, 0.33f, 0.33f,
		  1.f, -1.f,  1.f, 0.f, -1.f, 0.f, 0.33f, 0.f,

		 // Front
		 -1.f, -1.f,  1.f, 0.f, 0.f, 1.f, 0.33f, 0.f,
		 -1.f,  1.f,  1.f, 0.f, 0.f, 1.f, 0.33f, 0.33f,
		  1.f,  1.f,  1.f, 0.f, 0.f, 1.f, 0.66f, 0.33f,
		  1.f, -1.f,  1.f, 0.f, 0.f, 1.f, 0.66f, 0.f,

		  // Back
		 -1.f, -1.f, -1.f, 0.f, 0.f, -1.f, 0.33f, 0.66f,
		 -1.f,  1.f, -1.f, 0.f, 0.f, -1.f, 0.33f, 1.f,
		  1.f,  1.f, -1.f, 0.f, 0.f, -1.f, 0.66f, 1.f,
		  1.f, -1.f, -1.f, 0.f, 0.f, -1.f, 0.66f, 0.66f,

		 // Left
		  -1.f, -1.f, -1.f, -1.f, 0.f, 0.f, 0.f, 0.33f,
		  -1.f,  1.f, -1.f, -1.f, 0.f, 0.f, 0.f, 0.66f,
		  -1.f,  1.f,  1.f, -1.f, 0.f, 0.f, .33f, .66f,
		  -1.f, -1.f,  1.f, -1.f, 0.f, 0.f, .33f, .33f,

		  // Right
		  1.f, -1.f, -1.f, 1.f, 0.f, 0.f, .66f, .33f,
		  1.f,  1.f, -1.f, 1.f, 0.f, 0.f, .66f, .66f,
		  1.f,  1.f,  1.f, 1.f, 0.f, 0.f, 1.f, .66f,
		  1.f, -1.f,  1.f, 1.f, 0.f, 0.f, 1.f, .33f,
	};
	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(float), m_vertexData.data(), GL_STATIC_DRAW);

	// ibo
	m_indexData = {
		0, 1, 2,
		2, 3, 0,

		0 + 4, 1 + 4, 2 + 4,
		2 + 4, 3 + 4, 0 + 4,

		0 + 8, 1 + 8, 2 + 8,
		2 + 8, 3 + 8, 0 + 8,

		0 + 12, 1 + 12, 2 + 12,
		2 + 12, 3 + 12, 0 + 12,

		0 + 16, 1 + 16, 2 + 16,
		2 + 16, 3 + 16, 0 + 16,

		0 + 20, 1 + 20, 2 + 20,
		2 + 20, 3 + 20, 0 + 20
	};
	glGenBuffers(1, &m_ib);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ib);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexData.size() * sizeof(GLuint), m_indexData.data(), GL_STATIC_DRAW);

	// Attribute	
	glEnableVertexAttribArray(m_shader->GetAttriVertices());
	glVertexAttribPointer(m_shader->GetAttriVertices(), 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(m_shader->GetAttrNormal());
	glVertexAttribPointer(m_shader->GetAttrNormal(), 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));

	glEnableVertexAttribArray(m_shader->GetAttrTexCoords());
	glVertexAttribPointer(m_shader->GetAttrTexCoords(), 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	// Uniform
	glUseProgram(m_shader->GetProgramID());
	Resolution res = WindowController::GetInstance().GetResolution();
	glUniform2f(m_shader->GetUniResolution(), res.m_width, res.m_height);

	// Unbind buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

void Mesh::Cleanup() {
	glDeleteBuffers(1, &m_vertexBuffer);
	glDeleteBuffers(1, &m_ib);
	glDeleteVertexArrays(1, &m_vao);

	for (auto& texture : m_textures) {
		texture.CleanUp();
	}
}

void Mesh::Render(glm::mat4 view, glm::mat4 projection) 
{
	// Transformation
	mat4 rotate = glm::rotate(mat4(1.f), (float)glfwGetTime(), glm::vec3(0.f, 1.f, 0.f)); 
	mat4 translate = glm::translate(mat4(1.f), vec3(0.f, 0.f, sin((float)glfwGetTime()) * 10.f - 10.f));
	m_world = translate * rotate;
	glm::mat4 wvp = projection * view * m_world;

	// Binding buffers
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ib);

	// Bind Textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_textures[0].GetTexture());
	glUniform1i(m_shader->GetUniSampler1(), 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_textures[1].GetTexture());
	glUniform1i(m_shader->GetUniSampler2(), 1);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, m_textures[2].GetTexture());
	glUniform1i(m_shader->GetUniSampler3(), 2);

	// Uniform
	glUseProgram(m_shader->GetProgramID());
	glUniform1f(m_shader->GetUniTime(), glfwGetTime());
	glUniformMatrix4fv(m_shader->GetUniWVP(), 1, GL_FALSE, &wvp[0][0]);
	m_shader->SetUniformMat4("u_modelToWorld", m_world);
	m_shader->SetUniformVec3("u_normalizedLightDir", glm::normalize(vec3(2.f, 1.f, 0.f)));
	m_shader->SetUniformVec3("u_lightColor", {.9f, .7f, .8f});
	m_shader->SetUniformVec3("u_ambientLight", {.1f, .1f, .1f});

	// Draw
	glDrawElements(GL_TRIANGLES, m_indexData.size(), GL_UNSIGNED_INT, nullptr);
}