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

	GLuint GetAttrVertices() { return m_attrVertices; };
	GLuint GetAttrColor() { return m_attrColor; };
	GLuint GetAttrTexCoords() { return m_attrTexCoords; }

	GLuint GetUniWVP() { return m_uniWVP; };
	GLuint GetUniSampler1() { return m_uniSampler1; }
	GLuint GetUniSampler2() { return m_uniSampler2; }

	void LoadShaders(const char* _vertexFilePath, const char* _fragmentFilePath);
	void Cleanup();

	void SetUniformVec3(const char* _name, const vec3& _value);
	void SetUniformFloat(const char* _name, float);

private:
	void CreateShaderProgram(const char* _vertexFilePath, const char* _fragmentFilePath);
	GLuint LoadShaderFile(const char* _filePath, GLenum _type);
	void LoadAttributes();
	void EvaluateShader(int _infoLength, GLuint _id);

	GLuint m_programID;
	GLint m_result = GL_FALSE;
	int m_infoLogLength;
	
	GLuint m_attrVertices;
	GLuint m_attrColor;
	GLuint m_attrTexCoords;

	GLuint m_uniWVP;
	GLuint m_uniSampler1;
	GLuint m_uniSampler2;
};

#endif // !SHADER_H

