#include "Mesh.h"
#include "shader.h"
#include "Resolution.h"
#include "WindowController.h"
#include "Camera.h"

Mesh::Mesh(const Shape& shape) {
	m_shape = shape;

	m_vao = 0;
	m_vertexBuffer = 0;
	m_ib = 0;
	m_shader = nullptr;
	m_lightPos = vec3(1.f);

	m_scale = vec3(1.f);
	m_position = vec3(1.f);
	m_angle = 0.f;
	m_rotationAxis = vec3(1.f);
	m_world = glm::mat4(1.f);
}

Mesh::~Mesh() {
}

void Mesh::Create(Shader* _shader) {
	m_shader = _shader;

	//vao
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	// Vertex array
	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_shape.m_vertexData.size() * sizeof(float), m_shape.m_vertexData.data(), GL_STATIC_DRAW);

	// ibo
	glGenBuffers(1, &m_ib);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ib);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_shape.m_indexData.size() * sizeof(GLuint), m_shape.m_indexData.data(), GL_STATIC_DRAW);

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
	m_shader->ClearTexture();
}

void Mesh::Render(const Camera& _camera) 
{
	// Transformation
	mat4 scale = glm::scale(mat4(1.f), m_scale);
	mat4 rotate = glm::rotate(mat4(1.f), m_angle, m_rotationAxis); 
	mat4 translate = glm::translate(mat4(1.f), m_position);
	m_world = translate * rotate * scale;
	glm::mat4 wvp = _camera.getProjection() * _camera.getView() * m_world;

	// Binding buffers
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ib);
	glUseProgram(m_shader->GetProgramID());

	// Bind Textures
	m_shader->BindTextures();

	// Uniform
	glUniformMatrix4fv(m_shader->GetUniWVP(), 1, GL_FALSE, &wvp[0][0]);
	m_shader->SetUniformFloat("u_time", glfwGetTime());
	m_shader->SetUniformMat4("u_modelToWorld", m_world);
	m_shader->SetUniformVec3("u_cameraWorldPos", _camera.getWSCamera());
	m_shader->SetUniformFloat("u_light.specularConcentration", 8.f);
	m_shader->SetUniformVec3("u_light.position", m_lightPos);
	m_shader->SetUniformVec3("u_light.ambientColor", {.1f, .1f, .1f});
	m_shader->SetUniformVec3("u_light.lambertianColor", {.9f, .7f, .8f});
	m_shader->SetUniformVec3("u_light.specularColor", vec3(3.f));

	// Draw
	glDrawElements(GL_TRIANGLES, m_shape.m_indexData.size(), GL_UNSIGNED_INT, nullptr);

	// Unbind
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glUseProgram(0);
}