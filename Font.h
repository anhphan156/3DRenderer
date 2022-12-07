#pragma once
#ifndef FONT_H
#define FONT_H

#include "StandardIncludes.h"

struct Character {
	unsigned int TextureID;
	glm::ivec2 Size;
	glm::ivec2 Bearing;
	unsigned int Advance;
};

class Font {
public:
	Font();

	void Create(class Shader* _shader, std::string _name, FT_UInt _size);
	void RenderText(std::string _text, float _x, float _y, float _scale, vec3 _color);
	void Cleanup();

private:
	class Shader* m_shader;
	FT_Library m_library;
	FT_Face m_face;
	std::map<char, Character> m_characters;
	GLuint m_vertexBuffer;
	glm::mat4 m_orthoProj;

	void Initialize(std::string _name, FT_UInt _size);
	void CreateCharacters();
	void AllocateBuffers();
};

#endif
