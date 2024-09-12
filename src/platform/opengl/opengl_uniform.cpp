
#include "opengl_uniform.h"
#include "platform/glad/glad.h"
#include "prime/prime_device.h"

namespace prime {

	OpenGLUniformbuffer::OpenGLUniformbuffer(Device* device, u32 size, u32 binding)
	{
		glGenBuffers(1, &m_ID);
		glBindBuffer(GL_UNIFORM_BUFFER, m_ID);
		glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
		glBindBufferBase(GL_UNIFORM_BUFFER, binding, m_ID);

		m_Handle.Ptr = &m_ID;
		m_Device = device;
	}

	OpenGLUniformbuffer::~OpenGLUniformbuffer()
	{
		if (m_Handle.Ptr) {
			if (m_Device->IsActiveUniformbuffer(m_Handle)) {
				m_Device->SetActiveUniformbuffer(&m_Handle);
			}
			glDeleteBuffers(1, &m_ID);
			m_ID = 0;
			m_Handle.Ptr = nullptr;
		}
	}

	void OpenGLUniformbuffer::Bind()
	{
		if (!m_Device->IsActiveUniformbuffer(m_Handle)) {
			glBindBuffer(GL_UNIFORM_BUFFER, m_ID);
			m_Device->SetActiveUniformbuffer(&m_Handle);
		}
	}

	void OpenGLUniformbuffer::Unbind()
	{
		m_Device->SetActiveUniformbuffer(nullptr);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	void OpenGLUniformbuffer::SetData(u32 size, void* data)
	{
		glBufferSubData(GL_UNIFORM_BUFFER, 0, size, data);
	}
}