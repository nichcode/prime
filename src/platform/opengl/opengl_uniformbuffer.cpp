
#include "opengl_uniformbuffer.h"
#include "platform/glad/glad.h"
#include "prime/prime_device.h"

namespace prime {

	OpenGLUniformbuffer::OpenGLUniformbuffer(u32 size, u32 binding)
	{
		glGenBuffers(1, &m_ID);
		glBindBuffer(GL_UNIFORM_BUFFER, m_ID);
		glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
		glBindBufferBase(GL_UNIFORM_BUFFER, binding, m_ID);
	}

	OpenGLUniformbuffer::~OpenGLUniformbuffer()
	{
		glDeleteBuffers(1, &m_ID);
		m_ID = 0;
	}

	void OpenGLUniformbuffer::Bind()
	{
		glBindBuffer(GL_UNIFORM_BUFFER, m_ID);
	}

	void OpenGLUniformbuffer::Unbind()
	{
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	void OpenGLUniformbuffer::SetData(u32 size, void* data)
	{
		glBufferSubData(GL_UNIFORM_BUFFER, 0, size, data);
	}
}