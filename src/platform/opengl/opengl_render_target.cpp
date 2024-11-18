
#include "opengl_render_target.h"
#include "prime/assert.h"
#include "platform/glad/glad.h"

#include <format>

namespace prime {

	OpenGLRenderTarget::OpenGLRenderTarget(u32 width, u32 height, const Viewport* viewport)
	{
		glGenFramebuffers(1, &m_id);
		glBindFramebuffer(GL_FRAMEBUFFER, m_id);

		// Create colour texture
		glGenTextures(1, &m_textureHandle);
		glBindTexture(GL_TEXTURE_2D, m_textureHandle);
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
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textureHandle, 0);

		// Create depth/stencil renderbuffer
		glGenRenderbuffers(1, &m_depthHandle);
		glBindRenderbuffer(GL_RENDERBUFFER, m_depthHandle);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_depthHandle);

		// Check for completeness
		i32 completeStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (completeStatus != GL_FRAMEBUFFER_COMPLETE)
		{
			str msg = std::format("Failure to create render target. Complete status: {}", completeStatus);
			PERROR(msg);
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		m_width = width;
		m_height = height;
		m_view = viewport;
	}

	OpenGLRenderTarget::~OpenGLRenderTarget()
	{
		glDeleteFramebuffers(1, &m_id);
		m_id = 0;
		m_depthHandle = 0;
		m_textureHandle = 0;
	}

	void OpenGLRenderTarget::bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_id);
		glViewport(0, 0, m_width, m_height);
	}

	void OpenGLRenderTarget::unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport((i32)m_view->x, (i32)m_view->y, m_view->width, m_view->height);
	}
}