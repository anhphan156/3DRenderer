#include "Mesh.h"
#include "shader.h"
#include "Resolution.h"
#include "WindowController.h"
#include "Camera.h"

Mesh::Mesh() {
	m_vao = 0;
	m_vertexBuffer = 0;
	m_instanceBuffer = 0;
	m_ibo = 0;
	m_indiciesCount = 0;
	m_shader = nullptr;
	m_elementSize = 0;
	m_enableInstancing = false;

	m_instanceCount = 1;

	m_scale = vec3(1.f);
	m_position = vec3(1.f);
	m_angle = 0.f;
	m_rotationAxis = vec3(1.f);
	m_world = glm::mat4(1.f);

	m_lightColor = vec3(1.f);
	m_specularColor = vec3(3.f);
	m_specularStrength = 8.f;

	OnUpdate = [](float) {};
}

Mesh::~Mesh() {
}

void Mesh::Create(Shader* _shader, const objl::Loader* _loader, int _instanceCount) {
	m_shader = _shader;
	m_instanceCount = _instanceCount;
	m_enableInstancing = m_instanceCount > 1;

	if (m_enableInstancing) {
		glGenBuffers(1, &m_instanceBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_instanceBuffer);

		srand(glfwGetTime());
		for (unsigned int i = 0; i < m_instanceCount; ++i) {
			mat4 scale = glm::scale(mat4(1.f), vec3(glm::linearRand(1.f, 1.5f)));
			mat4 rotation = glm::rotate(mat4(1.f), (float)(rand() % 7), vec3(1.f));

			vec3 randomTranslation = (vec3(rand() % 350, rand() % 250, rand() % 350) + vec3(40.f));
			randomTranslation.x *= (rand() % 2 == 0 ? -1.f : 1.f);
			randomTranslation.y *= (rand() % 2 == 0 ? -1.f : 1.f);
			randomTranslation.z *= (rand() % 2 == 0 ? -1.f : 1.f);
			mat4 translation = glm::translate(mat4(1.f), randomTranslation);

			mat4 modelToWorld = translation * rotation * scale;

			for (int x = 0; x < 4; ++x)
				for (int y = 0; y < 4; y++)
					m_instanceData.push_back(modelToWorld[x][y]);
		}
			 
		glBufferData(GL_ARRAY_BUFFER, m_instanceCount * sizeof(mat4), m_instanceData.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

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

	// Instancing Attribute
	if (m_enableInstancing) {
		glBindBuffer(GL_ARRAY_BUFFER, m_instanceBuffer);

		for (unsigned int i = 0; i < 4; ++i) {
			glEnableVertexAttribArray(m_shader->GetAttrInstanceMatrix() + i);
			glVertexAttribPointer(m_shader->GetAttrInstanceMatrix() + i, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), (void*)(i * sizeof(glm::vec4)));
			
			glVertexAttribDivisor(m_shader->GetAttrInstanceMatrix() + i, 1);
		}
	}

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
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glUseProgram(m_shader->GetProgramID());

	// Bind Textures
	m_shader->BindTextures();

	// Uniform
	glUniformMatrix4fv(m_shader->GetUniWVP(), 1, GL_FALSE, &wvp[0][0]);
	m_shader->SetUniformFloat("u_normalEnabled", m_shader->GetNormalEnabled());
	m_shader->SetUniformFloat("u_specularEnabled", m_shader->GetSpecularEnabled());
	m_shader->SetUniformInt("u_instanceEnabled", m_enableInstancing);
	m_shader->SetUniformFloat("u_time", glfwGetTime());
	m_shader->SetUniformMat4("u_modelToWorld", m_world);
	m_shader->SetUniformVec3("u_cameraWorldPos", _camera.getWSCamera());
	if (m_lights != nullptr) {
		for (int i = 0; i < m_lights->size(); i++) {
			auto light = (*m_lights)[i];
			m_shader->SetUniformVec3(concat("u_light[", i, "].position").c_str(), light.GetPosition());
			m_shader->SetUniformFloat(concat("u_light[", i, "].strength").c_str(), light.GetLightStrength());
			m_shader->SetUniformVec3(concat("u_light[", i, "].ambientColor").c_str(), {.1f, .1f, .1f});
			m_shader->SetUniformVec3(concat("u_light[", i, "].lambertianColor").c_str(), light.m_lightColor);
			m_shader->SetUniformVec3(concat("u_light[", i, "].specularColor").c_str(), light.m_specularColor);
			m_shader->SetUniformFloat(concat("u_light[", i, "].specularConcentration").c_str(), light.m_specularStrength);
			m_shader->SetUniformVec3(concat("u_light[", i, "].attenuationFactor").c_str(), vec3(.032f, .09f, 1.f));
			m_shader->SetUniformVec3(concat("u_light[", i, "].spotlightDirection").c_str(), vec3(0.f, cos(glfwGetTime() * 2.f + i), sin(glfwGetTime() * 2.f + i) * 2.f + 1.5f) - light.GetPosition());
			m_shader->SetUniformFloat(concat("u_light[", i, "].spotlightAngle").c_str(), 3.14f / 12.f);
			m_shader->SetUniformFloat(concat("u_light[", i, "].spotlightFalloff").c_str(), 100.f);
		}
	}

	// Draw
	unsigned int attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
	GLCALL(glDrawBuffers(2, attachments));
	if (m_enableInstancing) {
		GLCALL(glDrawElementsInstanced(GL_TRIANGLES, m_indiciesCount, GL_UNSIGNED_INT, nullptr, m_instanceCount));
	} else {
		GLCALL(glDrawElements(GL_TRIANGLES, m_indiciesCount, GL_UNSIGNED_INT, nullptr));
	}

	// Unbind
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glUseProgram(0);
}

std::string Mesh::concat(std::string s1, int i, std::string s2) {
	return s1 + std::to_string(i) + s2;
}