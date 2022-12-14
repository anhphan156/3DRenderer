#include "PostProcessor.h"
#include "Shader.h"
#include "WindowController.h"

PostProcessor::PostProcessor()
{
	m_framebuffer = 0;
	m_textureColorbuffer = 0;
	m_textureNormalbuffer = 0;
	m_renderBufferObject = 0;
	m_vertexBuffer = 0;
	m_postShader = nullptr;

	OnUpdate = []() {};
}

PostProcessor::~PostProcessor()
{
}

void PostProcessor::Create(Shader* _postShader)
{
	m_postShader = _postShader;
	CreateBuffers();
	CreateVertices();
}

void PostProcessor::Cleanup()
{
	glDeleteFramebuffers(1, &m_framebuffer);
	glDeleteTextures(1, &m_textureColorbuffer);
	glDeleteRenderbuffers(1, &m_renderBufferObject);
}

void PostProcessor::Start()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
}

void PostProcessor::End()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST);

	glUseProgram(m_postShader->GetProgramID());
	m_postShader->SetUniformFloat("u_time", glfwGetTime());
	m_postShader->SetTextureSampler("u_textures.sampler0", GL_TEXTURE0, 0, m_textureColorbuffer);
	m_postShader->SetTextureSampler("u_textures.sampler1", GL_TEXTURE1, 1, m_textureNormalbuffer);

	OnUpdate();

	BindVertices();
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void PostProcessor::CreateVertices()
{
	float vertexData[] = {
		-1.f, 1.f, 0.f, 1.f,
		-1.f, -1.f, 0.f, 0.f,
		1.f, -1.f, 1.f, 0.f,

		-1.f, 1.f, 0.f, 1.f,
		1.f, -1.f, 1.f, 0.f,
		1.f, 1.f, 1.f, 1.f
	};

	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), &vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void PostProcessor::CreateBuffers()
{
	glGenFramebuffers(1, &m_framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);

	// color
	glGenTextures(1, &m_textureColorbuffer);
	glBindTexture(GL_TEXTURE_2D, m_textureColorbuffer);
	auto r = WindowController::GetInstance().GetResolution();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, r.m_width, r.m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textureColorbuffer, 0);

	// normal
	glGenTextures(1, &m_textureNormalbuffer);
	glBindTexture(GL_TEXTURE_2D, m_textureNormalbuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, r.m_width, r.m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, m_textureNormalbuffer, 0);

	glGenRenderbuffers(1, &m_renderBufferObject);
	glBindRenderbuffer(GL_RENDERBUFFER, m_renderBufferObject);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, r.m_width, r.m_height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderBufferObject);

	M_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "framebuffer is not complete");
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void PostProcessor::BindVertices()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);

	glEnableVertexAttribArray(m_postShader->GetAttriVertices());
	glVertexAttribPointer(m_postShader->GetAttriVertices(), 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(m_postShader->GetAttrTexCoords());
	glVertexAttribPointer(m_postShader->GetAttrTexCoords(), 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
}
