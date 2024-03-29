#include "Shader.h"
#include "Texture.h"

Shader::Shader() {
	m_programID = 0;
	m_attrVertices = 0;
	m_attrNormal = 0;
	m_attrTexCoords = 0;

	m_result = GL_FALSE;
	m_infoLogLength = 0;

	m_textures = {};
}

void Shader::Cleanup() {
	glDeleteProgram(m_programID);
}

void Shader::AddTexture(const shared_ptr<class Texture> _texture) {
	m_textures.push_back(_texture);
}

void Shader::ClearTexture()
{
	for (auto& texture : m_textures) {
		texture->CleanUp();
	}
}

void Shader::BindTextures() const {
	for (int i = 0; i < m_textures.size() && i < 32; i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, m_textures[i]->GetTexture());
		GLuint m_uniSamplerLoc = glGetUniformLocation(m_programID, ("u_textures.sampler" + std::to_string(i)).c_str());
		glUniform1i(m_uniSamplerLoc, i);
	}
}
void Shader::SetUniformFloat(const char* _name, float _value) const {
	GLint loc = glGetUniformLocation(m_programID, _name);
	if (loc != -1) glUniform1f(loc, _value);
}

void Shader::SetUniformVec3(const char* _name, const vec3& _value) const {
	GLint loc = glGetUniformLocation(m_programID, _name);
	if (loc != -1) {
		glUniform3fv(loc, 1, &_value[0]);
	}
}

void Shader::SetUniformMat4(const char* _name, const mat4& _value) const {
	GLint loc = glGetUniformLocation(m_programID, _name);
	if (loc != -1) {
		glUniformMatrix4fv(loc, 1, GL_FALSE, &_value[0][0]);
	}
}

void Shader::LoadAttributes() {
	m_attrVertices = glGetAttribLocation(m_programID, "vertices");
	m_attrNormal = glGetAttribLocation(m_programID, "normal");
	m_attrTexCoords = glGetAttribLocation(m_programID, "texCoords");

	m_uniResolution = glGetUniformLocation(m_programID, "u_resolution");
	m_uniWVP = glGetUniformLocation(m_programID, "u_wvp");
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
