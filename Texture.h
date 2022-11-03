#pragma once
#ifndef TEXTURE_H
#include "StandardIncludes.h"

class Texture {
public:
	Texture();
	virtual ~Texture();

	GLuint GetTexture() { return m_texture; }

	void LoadTexture(std::string);
	void CleanUp();

private:
	int m_width;
	int m_height;
	int m_channels;
	GLuint m_texture;
};

#endif // !TEXTURE_H

