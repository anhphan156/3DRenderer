#include "Texture.h"
#include <stb_image.h>

Texture::Texture()
{
	m_width = 0;
	m_texture = 0;
	m_channels = 0;
	m_texture = 0;
}

Texture::~Texture()
{

}

void Texture::LoadTexture(std::string _name)
{
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	// Texture wrapping + filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Load and generate texture
	stbi_set_flip_vertically_on_load(true);
	GLubyte* data = stbi_load(_name.c_str(), &m_width, &m_height, &m_channels, 0);
	M_ASSERT(data != nullptr, "Failed to load texture");
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(data);
}

void Texture::LoadCubemap(vector<std::string> _faces)
{
	GLCALL(glGenTextures(1, &m_cubemapTexture));
	GLCALL(glBindTexture(GL_TEXTURE_CUBE_MAP, m_cubemapTexture));

	GLCALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	GLCALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));

	//GLCALL(glEnable(GL_TEXTURE_CUBE_MAP));

	for (unsigned int i = 0; i < _faces.size(); ++i) {
		stbi_set_flip_vertically_on_load(false);
		GLubyte* data = stbi_load(_faces[i].c_str(), &m_width, &m_height, &m_channels, 0);
		M_ASSERT(data != nullptr, "Texture.cpp: failed to load cubemap");
		GLCALL(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data));
		stbi_image_free(data);
	}
}

void Texture::CleanUp()
{
	glDeleteTextures(1, &m_texture);
}
