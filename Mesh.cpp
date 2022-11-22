#include "Mesh.h"
#include "shader.h"
#include "Resolution.h"
#include "WindowController.h"
#include "Camera.h"

Mesh::Mesh() {
	m_vao = 0;
	m_vertexBuffer = 0;
	m_ibo = 0;
	m_indiciesCount = 0;
	m_shader = nullptr;

	m_scale = vec3(1.f);
	m_position = vec3(1.f);
	m_angle = 0.f;
	m_rotationAxis = vec3(1.f);
	m_world = glm::mat4(1.f);

	m_lights.clear();
	m_lightColor = vec3(1.f);
	m_specularColor = vec3(3.f);
	m_specularStrength = 8.f;
}

Mesh::~Mesh() {
}

void Mesh::Create(Shader* _shader, const objl::Loader* _loader) {
	m_shader = _shader;

	for (unsigned int i = 0; i < _loader->LoadedMeshes.size(); i++) {
		const objl::Mesh& mesh = _loader->LoadedMeshes[i];
		for (unsigned int j = 0; j < mesh.Vertices.size(); j++) {
			m_vertexData.push_back(mesh.Vertices[j].Position.X);
			m_vertexData.push_back(mesh.Vertices[j].Position.Y);
			m_vertexData.push_back(mesh.Vertices[j].Position.Z);
			m_vertexData.push_back(mesh.Vertices[j].Normal.X);
			m_vertexData.push_back(mesh.Vertices[j].Normal.Y);
			m_vertexData.push_back(mesh.Vertices[j].Normal.Z);
			m_vertexData.push_back(mesh.Vertices[j].Tangent.X);
			m_vertexData.push_back(mesh.Vertices[j].Tangent.Y);
			m_vertexData.push_back(mesh.Vertices[j].Tangent.Z);
			m_vertexData.push_back(mesh.Vertices[j].TextureCoordinate.X);
			m_vertexData.push_back(mesh.Vertices[j].TextureCoordinate.Y);
		}
	}

	m_indiciesCount = _loader->LoadedIndices.size();

	//vao
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	// Vertex array
	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(float), m_vertexData.data(), GL_STATIC_DRAW);

	// ibo
	glGenBuffers(1, &m_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _loader->LoadedIndices.size() * sizeof(float), _loader->LoadedIndices.data(), GL_STATIC_DRAW);

	// Attribute	
	glEnableVertexAttribArray(m_shader->GetAttriVertices());
	glVertexAttribPointer(m_shader->GetAttriVertices(), 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(m_shader->GetAttrNormal());
	glVertexAttribPointer(m_shader->GetAttrNormal(), 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));

	glEnableVertexAttribArray(m_shader->GetAttrTangent());
	glVertexAttribPointer(m_shader->GetAttrTangent(), 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));

	glEnableVertexAttribArray(m_shader->GetAttrTexCoords());
	glVertexAttribPointer(m_shader->GetAttrTexCoords(), 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(9 * sizeof(float)));

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
	glDeleteBuffers(1, &m_ibo);
	glDeleteVertexArrays(1, &m_vao);
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
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glUseProgram(m_shader->GetProgramID());

	// Bind Textures
	m_shader->BindTextures();

	// Uniform
	glUniformMatrix4fv(m_shader->GetUniWVP(), 1, GL_FALSE, &wvp[0][0]);
	m_shader->SetUniformFloat("u_time", glfwGetTime());
	m_shader->SetUniformMat4("u_modelToWorld", m_world);
	m_shader->SetUniformVec3("u_cameraWorldPos", _camera.getWSCamera());
	for (int i = 0; i < m_lights.size(); i++) {
		m_shader->SetUniformVec3(concat("u_light[", i, "].position").c_str(), m_lights[i].GetPosition());
		m_shader->SetUniformVec3(concat("u_light[", i, "].ambientColor").c_str(), {.1f, .1f, .1f});
		m_shader->SetUniformVec3(concat("u_light[", i, "].lambertianColor").c_str(), m_lights[i].m_lightColor);
		m_shader->SetUniformVec3(concat("u_light[", i, "].specularColor").c_str(), m_lights[i].m_specularColor);
		m_shader->SetUniformFloat(concat("u_light[", i, "].specularConcentration").c_str(), m_lights[i].m_specularStrength);
		m_shader->SetUniformVec3(concat("u_light[", i, "].attenuationFactor").c_str(), vec3(.032f, .09f, 1.f));
		m_shader->SetUniformVec3(concat("u_light[", i, "].spotlightDirection").c_str(), vec3(0.f, cos(glfwGetTime() * 2.f + i), sin(glfwGetTime() * 2.f + i) * 2.f + 1.5f) - m_lights[i].GetPosition());
		m_shader->SetUniformFloat(concat("u_light[", i, "].spotlightAngle").c_str(), 3.14f / 12.f);
		m_shader->SetUniformFloat(concat("u_light[", i, "].spotlightFalloff").c_str(), 100.f);
	}

	// Draw
	glDrawElements(GL_TRIANGLES, m_indiciesCount, GL_UNSIGNED_INT, nullptr);

	// Unbind
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glUseProgram(0);
}

std::string Mesh::concat(std::string s1, int i, std::string s2) {
	return s1 + std::to_string(i) + s2;
}