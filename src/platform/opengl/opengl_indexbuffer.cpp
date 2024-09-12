
#include "opengl_indexbuffer.h"
#include "prime/prime_device.h"
#include "platform/glad/glad.h"

namespace prime {

	OpenGLIndexbuffer::OpenGLIndexbuffer(Device* device, u32* indices, u32 count)
	{
		glGenBuffers(1, &m_ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);

		m_Device = device;
		m_Count = count;
		m_Handle.Ptr = &m_ID;

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	OpenGLIndexbuffer::~OpenGLIndexbuffer()
	{
		if (m_Handle.Ptr) {
			if (m_Device->IsActiveIndexbuffer(m_Handle)) {
				m_Device->SetActiveIndexbuffer(&m_Handle);
			}
			glDeleteBuffers(1, &m_ID);
			m_ID = 0;
			m_Handle.Ptr = nullptr;
		}
	}

	void OpenGLIndexbuffer::Bind()
	{
		if (!m_Device->IsActiveIndexbuffer(m_Handle)) {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
			m_Device->SetActiveIndexbuffer(&m_Handle);
		}
	}
}
