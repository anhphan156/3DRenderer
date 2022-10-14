#include "Mesh.h"
#include "shader.h"
#include "Resolution.h"
#include "WindowController.h"

Mesh::Mesh() {
	m_vertexBuffer = 0;
	m_vertexData = {};
	m_shader = nullptr;
	m_world = glm::mat4(1.f);
}

Mesh::~Mesh() {
	m_vertexBuffer = 0;
	m_vertexData = {};
}

void Mesh::Create(Shader* _shader) {
	m_shader = _shader;

	m_vertexData = { -1.f, -1.f, 0.f,
					  0.f,  1.f, 0.f, 
		              1.f, -1.f, 0.f };
	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(float), m_vertexData.data(), GL_STATIC_DRAW);

	glUseProgram(m_shader->GetProgramID());

	Resolution res = WindowController::GetInstance().GetResolution();
	glUniform2f(m_shader->GetUniResolution(), res.m_width, res.m_height);

	
	glEnableVertexAttribArray(m_shader->GetAttriVertices());
	glVertexAttribPointer(m_shader->GetAttriVertices(), 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
}

void Mesh::Cleanup() {
	glDeleteBuffers(1, &m_vertexBuffer);
}

void Mesh::Render(glm::mat4 view, glm::mat4 projection) {

	m_world = glm::translate(glm::mat4(1.f), glm::vec3(glm::sin(glfwGetTime()), 0.f, 0.f)) * glm::rotate(glm::mat4(1.f), (float)glfwGetTime(), glm::vec3(0.f, 1.f, 0.f)); 
	//m_world = glm::rotate(glm::mat4(1.f), (float)glfwGetTime(), glm::vec3(0.f, 1.f, 0.f)); 

	glm::mat4 wvp = projection * view * m_world;

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);

	glUniform1f(m_shader->GetUniTime(), glfwGetTime());
	glUniformMatrix4fv(m_shader->GetUniWVP(), 1, GL_FALSE, &wvp[0][0]);


	glDrawArrays(GL_TRIANGLES, 0, 3);
	//glDisableVertexAttribArray(m_shader->GetAttriVertices());
}