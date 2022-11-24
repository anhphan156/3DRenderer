#pragma once
#ifndef TEXTURE_H
#include "StandardIncludes.h"

class Texture {
public:
	Texture();
	virtual ~Texture();

	GLuint GetTexture() { return m_texture; }
	GLuint GetCubemapTexture() { return m_cubemapTexture; }

	void LoadTexture(std::string);
	void LoadCubemap(vector<std::string> _faces);
	void CleanUp();

private:
	int m_width;
	int m_height;
	int m_channels;
	GLuint m_texture;
	GLuint m_cubemapTexture;
};

#endif // !TEXTURE_H

