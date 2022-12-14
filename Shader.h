#pragma once
#ifndef SHADER_H
#define SHADER_H

#include "StandardIncludes.h"

class Shader
{
public:
	Shader();
	virtual ~Shader() {};

	GLuint GetProgramID() { return m_programID; };

	GLuint GetAttriVertices() { return m_attrVertices; };
	GLuint GetAttrNormal() { return m_attrNormal; }
	GLuint GetAttrTangent() { return m_attrTangent; }
	GLuint GetAttrTexCoords() { return m_attrTexCoords; }
	GLuint GetAttrInstanceMatrix() { return m_attrInstanceMatrix; }

	GLuint GetUniResolution() { return m_uniResolution; };
	GLuint GetUniWVP() { return m_uniWVP; };

	void LoadShaders(const char* _vertexFilePath, const char* _fragmentFilePath);
	void Cleanup();

	void SetUniformFloat(const char* _name, float _value) const;
	void SetUniformInt(const char* _name, int _value) const;
	void SetUniformVec3(const char* _name, const vec3& _value) const;
	void SetUniformMat4(const char* _name, const mat4& _value) const;

	void SetNormalEnabled(float normalEnabled) { m_normalEnabled = normalEnabled; }
	void SetSpecularEnabled(float specularEnabled) { m_specularEnabled = specularEnabled; }
	float GetNormalEnabled() { return m_normalEnabled; }
	float GetSpecularEnabled() { return m_specularEnabled; }

	void AddTexture(const shared_ptr<class Texture>);
	void ClearTexture();
	void BindTextures() const;
	void SetTextureSampler(const std::string& uniform, GLenum texture, int value, GLuint texture_id) const;

private:
	void CreateShaderProgram(const char* _vertexFilePath, const char* _fragmentFilePath);
	GLuint LoadShaderFile(const char* _filePath, GLenum _type);
	void LoadAttributes();
	void EvaluateShader(int _infoLength, GLuint _id);

	GLuint m_programID;
	GLint m_result = GL_FALSE;
	int m_infoLogLength;
	
	GLuint m_attrVertices;
	GLuint m_attrNormal;
	GLuint m_attrTangent;
	GLuint m_attrTexCoords;
	GLuint m_attrInstanceMatrix;

	GLuint m_uniResolution;
	GLuint m_uniWVP;

	float m_normalEnabled;
	float m_specularEnabled;

	vector<shared_ptr<class Texture>> m_textures;
};

#endif // !SHADER_H

