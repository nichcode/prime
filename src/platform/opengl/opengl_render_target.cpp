
#include "opengl_render_target.h"
#include "prime/prime_assert.h"
#include "prime/prime_device.h"
#include "platform/glad/glad.h"

#include <format>

namespace prime {

	OpenGLRenderTarget::OpenGLRenderTarget(u32 width, u32 height, const Viewport* viewport)
	{
		glGenFramebuffers(1, &m_ID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_ID);

		// Create colour texture
		glGenTextures(1, &m_TextureHandle);
		glBindTexture(GL_TEXTURE_2D, m_TextureHandle);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RGBA,
			width,
			height,
			0,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			nullptr);

		glBindTexture(GL_TEXTURE_2D, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_TextureHandle, 0);

		// Create depth/stencil renderbuffer
		glGenRenderbuffers(1, &m_DepthHandle);
		glBindRenderbuffer(GL_RENDERBUFFER, m_DepthHandle);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_DepthHandle);

		// Check for completeness
		i32 completeStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (completeStatus != GL_FRAMEBUFFER_COMPLETE)
		{
			str msg = std::format("Failure to create render target. Complete status: {}", completeStatus);
			PERROR(msg);
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		m_Width = width;
		m_Height = height;
		m_View = viewport;
	}

	OpenGLRenderTarget::~OpenGLRenderTarget()
	{
		glDeleteFramebuffers(1, &m_ID);
		m_ID = 0;
		m_DepthHandle = 0;
		m_TextureHandle = 0;
	}

	void OpenGLRenderTarget::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_ID);
		glViewport(0, 0, m_Width, m_Height);
	}

	void OpenGLRenderTarget::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport((i32)m_View->X, (i32)m_View->Y, m_View->Width, m_View->Height);
	}
}