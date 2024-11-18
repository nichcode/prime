
#include "opengl_uniformbuffer.h"
#include "platform/glad/glad.h"

namespace prime {

	OpenGLUniformbuffer::OpenGLUniformbuffer(u32 size, u32 binding)
	{
		glGenBuffers(1, &m_id);
		glBindBuffer(GL_UNIFORM_BUFFER, m_id);
		glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
		glBindBufferBase(GL_UNIFORM_BUFFER, binding, m_id);
	}

	OpenGLUniformbuffer::~OpenGLUniformbuffer()
	{
		glDeleteBuffers(1, &m_id);
		m_id = 0;
	}

	void OpenGLUniformbuffer::bind()
	{
		glBindBuffer(GL_UNIFORM_BUFFER, m_id);
	}

	void OpenGLUniformbuffer::unbind()
	{
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	void OpenGLUniformbuffer::set_data(u32 size, void* data)
	{
		glBufferSubData(GL_UNIFORM_BUFFER, 0, size, data);
	}
}