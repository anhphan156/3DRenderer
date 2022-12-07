#pragma once
#ifndef POSTPROCESSOR_H
#define POSTPROCESSOR_H

#include "StandardIncludes.h"
#include "Texture.h"

class PostProcessor {
public:
	PostProcessor();
	virtual ~PostProcessor();

	void Create(class Shader* _postShader);
	void Cleanup();
	void Start();
	void End();

private:
	GLuint m_framebuffer;
	GLuint m_textureColorbuffer;
	GLuint m_textureNormalbuffer;
	GLuint m_renderBufferObject;
	GLuint m_vertexBuffer;
	class Shader* m_postShader;

	void CreateVertices();
	void CreateBuffers();
	void BindVertices();
};

#endif // !POSTPROCESSOR_H

