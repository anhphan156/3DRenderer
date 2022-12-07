#include "Font.h"
#include "Shader.h"
#include "WindowController.h"

Font::Font()
{
	m_shader = nullptr;
	m_library = 0;
	m_face = 0;
	m_vertexBuffer = 0;
	m_orthoProj = mat4(1.f);
}

void Font::Create(Shader* _shader, std::string _name, FT_UInt _size)
{
	m_shader = _shader;

	AllocateBuffers();
	Initialize(_name, _size);
}

void Font::Cleanup() {
	glDeleteBuffers(1, &m_vertexBuffer);
	//for (auto it = m_characters.begin(); it != m_characters.end(), ++it) glDeleteTextures(1, &it->second.TextureID);
}

void Font::RenderText(std::string _text, float _x, float _y, float _scale, vec3 _color)
{
	_y = WindowController::GetInstance().GetResolution().m_height - _y;
	glUseProgram(m_shader->GetProgramID());
	m_shader->SetUniformVec3("u_textColor", _color);
	m_shader->SetUniformMat4("u_projection", m_orthoProj);

	std::string::const_iterator c;
	for (c = _text.begin(); c != _text.end(); c++) {
		Character ch = m_characters[*c];
		float xpos = _x + ch.Bearing.x * _scale;
		float ypos = _y - (ch.Size.y - ch.Bearing.y) * _scale;
		float w = ch.Size.x * _scale;
		float h = ch.Size.y * _scale;

		float vertices[6][4] = {
			{xpos,     ypos + h, 0.f, 0.f},
			{xpos,     ypos,     0.f, 1.f},
			{xpos + w, ypos,     1.f, 1.f},

			{xpos,     ypos + h, 0.f, 0.f},
			{xpos + w, ypos,     1.f, 1.f},
			{xpos + w, ypos + h, 1.f, 0.f},
		};

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		GLint uniSamplerLoc = glGetUniformLocation(m_shader->GetProgramID(), "u_texture.sampler1");
		glUniform1i(uniSamplerLoc, 0);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
		glEnableVertexAttribArray(m_shader->GetAttriVertices());
		glVertexAttribPointer(m_shader->GetAttriVertices(), 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		_x += (ch.Advance >> 6) * _scale;
	}

	glDisableVertexAttribArray(m_shader->GetAttriVertices());
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Font::Initialize(std::string _name, FT_UInt _size)
{
	std::string fileName = "Res/Fonts/" + _name;
	Resolution r = WindowController::GetInstance().GetResolution();
	m_orthoProj = glm::ortho(0.f, (float)r.m_width, 0.f, (float)r.m_height);

	M_ASSERT(FT_Init_FreeType(&m_library) == false, "Failed to init FreeType lib");
	M_ASSERT(FT_New_Face(m_library, fileName.c_str(), 0, &m_face) == false, "Failed to load font");

	M_ASSERT(FT_Set_Pixel_Sizes(m_face, 0, _size) == false, "Failed to set character size");

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	CreateCharacters();

	FT_Done_Face(m_face);
	FT_Done_FreeType(m_library);
}

void Font::CreateCharacters()
{
	for (unsigned char c = 0; c < 128; c++) {
		M_ASSERT(FT_Load_Char(m_face, c, FT_LOAD_RENDER) == false, "Failed to load Glyph");

		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_face->glyph->bitmap.width, m_face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, m_face->glyph->bitmap.buffer);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		Character character = {};
		character.TextureID = texture;
		character.Size = glm::ivec2(m_face->glyph->bitmap.width, m_face->glyph->bitmap.rows);
		character.Bearing = glm::ivec2(m_face->glyph->bitmap_left, m_face->glyph->bitmap_top);
		character.Advance = (unsigned int)m_face->glyph->advance.x;
		m_characters[c] = character;
	}
}

void Font::AllocateBuffers()
{
	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
}
