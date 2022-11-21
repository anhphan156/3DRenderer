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

	GLuint GetUniResolution() { return m_uniResolution; };
	GLuint GetUniWVP() { return m_uniWVP; };

	void LoadShaders(const char* _vertexFilePath, const char* _fragmentFilePath);
	void Cleanup();

	void SetUniformFloat(const char* _name, float _value) const;
	void SetUniformVec3(const char* _name, const vec3& _value) const;
	void SetUniformMat4(const char* _name, const mat4& _value) const;

	void AddTexture(const shared_ptr<class Texture>);
	void ClearTexture();
	void BindTextures() const;

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

	GLuint m_uniResolution;
	GLuint m_uniWVP;

	vector<shared_ptr<class Texture>> m_textures;
};

#endif // !SHADER_H

