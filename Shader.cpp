#include "Shader.h"
#include <vector>

Shader::Shader() {
	m_programID = 0;
	m_attrVertices = 0;
	m_attrNormal = 0;
	m_attrTexCoords = 0;

	m_result = GL_FALSE;
	m_infoLogLength = 0;
}

void Shader::Cleanup() {
	glDeleteProgram(m_programID);
}

void Shader::SetUniformVec3(const char* _name, vec3 _value) {
	GLint loc = glGetUniformLocation(m_programID, _name);
	if (loc != -1) {
		glUniform3fv(loc, 1, &_value[0]);
	}
}

void Shader::LoadAttributes() {
	m_attrVertices = glGetAttribLocation(m_programID, "vertices");
	m_attrNormal = glGetAttribLocation(m_programID, "normal");
	m_attrTexCoords = glGetAttribLocation(m_programID, "texCoords");

	m_uniResolution = glGetUniformLocation(m_programID, "u_resolution");
	m_uniTime = glGetUniformLocation(m_programID, "u_time");
	m_uniWVP = glGetUniformLocation(m_programID, "u_wvp");
	m_uniSampler1 = glGetUniformLocation(m_programID, "u_sampler1");
	m_uniSampler2 = glGetUniformLocation(m_programID, "u_sampler2");
}

void Shader::LoadShaders(const char* _vertexFilePath, const char* _fragmentFilePath)
{
	CreateShaderProgram(_vertexFilePath, _fragmentFilePath);
	LoadAttributes();
}

GLuint Shader::LoadShaderFile(const char* _filePath, GLenum _type) {
	GLuint shaderID = glCreateShader(_type);

	std::string shaderCode;
	std::ifstream shaderStream(_filePath, std::ios::in);
	M_ASSERT(shaderStream.is_open(), "Can't open shader file");

	std::string line = "";

	while (getline(shaderStream, line)) {
		shaderCode += "\n" + line;
	}

	shaderStream.close();

	// Compile
	char const* sourcePointer = shaderCode.c_str();
	glShaderSource(shaderID, 1, &sourcePointer, NULL);
	glCompileShader(shaderID);

	// Check Shader
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &m_result);
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &m_infoLogLength);
	EvaluateShader(m_infoLogLength, shaderID);

	glAttachShader(m_programID, shaderID);

	return shaderID;
}

void Shader::EvaluateShader(int _infoLength, GLuint _id) {
	if (_infoLength > 0) {
		std::vector<char> errorMessage(_infoLength + 1);
		glGetShaderInfoLog(_id, _infoLength, NULL, &errorMessage[0]);
		M_ASSERT(0, ("%s\n", &errorMessage[0]));
	}
}

void Shader::CreateShaderProgram(const char* _vertexFilePath, const char* _fragmentFilePath) {
	m_programID = glCreateProgram();
	GLuint vertexShaderID = LoadShaderFile(_vertexFilePath, GL_VERTEX_SHADER);
	GLuint fragmentShaderID = LoadShaderFile(_fragmentFilePath, GL_FRAGMENT_SHADER);
	glLinkProgram(m_programID);
	
	glGetShaderiv(m_programID, GL_COMPILE_STATUS, &m_result);
	glGetShaderiv(m_programID, GL_INFO_LOG_LENGTH, &m_infoLogLength);
	EvaluateShader(m_infoLogLength, m_programID);

	// Free resources
	glDetachShader(m_programID, vertexShaderID);
	glDetachShader(m_programID, fragmentShaderID);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
}
