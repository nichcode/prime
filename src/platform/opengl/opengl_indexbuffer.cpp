
#include "opengl_indexbuffer.h"
#include "prime/prime_device.h"
#include "platform/glad/glad.h"

namespace prime {

	OpenGLIndexbuffer::OpenGLIndexbuffer(Device* device, u32* indices, u32 count)
	{
		GLuint handle = 0;
		glGenBuffers(1, &handle);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);

		m_Device = device;
		m_Count = count;
		m_Handle.Ptr = &handle;

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	OpenGLIndexbuffer::~OpenGLIndexbuffer()
	{
		if (m_Handle.Ptr) {
			GLuint* handle = static_cast<GLuint*>(m_Handle.Ptr);
			glDeleteBuffers(1, handle);
			m_Handle.Ptr = nullptr;
		}
	}

	void OpenGLIndexbuffer::Bind()
	{
		if (!m_Device->IsActiveIndexbuffer(m_Handle)) {
			GLuint* handle = static_cast<GLuint*>(m_Handle.Ptr);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *handle);
			m_Device->SetActiveIndexbuffer(&m_Handle);
		}
	}

	void OpenGLIndexbuffer::Unbind()
	{
		m_Device->SetActiveIndexbuffer(nullptr);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}
