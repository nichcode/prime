
#include "opengl_indexbuffer.h"
#include "prime/prime_device.h"
#include "platform/glad/glad.h"

namespace prime {

	OpenGLIndexbuffer::OpenGLIndexbuffer(u32* indices, u32 count)
	{
		glGenBuffers(1, &m_id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);

		m_count = count;
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	OpenGLIndexbuffer::~OpenGLIndexbuffer()
	{
		glDeleteBuffers(1, &m_id);
		m_id = 0;
	}

	void OpenGLIndexbuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
	}

	void OpenGLIndexbuffer::Unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}
