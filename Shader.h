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
	GLuint GetUniResolution() { return m_uniResolution; };
	GLuint GetUniTime() { return m_uniTime; };
	GLuint GetUniWVP() { return m_uniWVP; };

	void LoadShaders(const char* _vertexFilePath, const char* _fragmentFilePath);
	void Cleanup();

private:
	void CreateShaderProgram(const char* _vertexFilePath, const char* _fragmentFilePath);
	GLuint LoadShaderFile(const char* _filePath, GLenum _type);
	void LoadAttributes();
	void EvaluateShader(int _infoLength, GLuint _id);

	GLuint m_programID;
	GLint m_result = GL_FALSE;
	int m_infoLogLength;
	
	GLuint m_attrVertices;
	GLuint m_uniResolution;
	GLuint m_uniTime;
	GLuint m_uniWVP;
};

#endif // !SHADER_H

