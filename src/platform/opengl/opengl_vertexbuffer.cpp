
#include "opengl_vertexbuffer.h"
#include "prime/prime_device.h"
#include "platform/glad/glad.h"

namespace prime {

	PINLINE GLenum VertexbufferTypeToOpenGLType(VertexbufferType type)
	{
		switch (type)
		{
		case prime::VertexbufferTypeStatic:
			return GL_STATIC_DRAW;
			break;

		case prime::VertexbufferTypeDynamic:
			return GL_DYNAMIC_DRAW;
			break;
		}
		PASSERT_MSG(false, "Invalid VertexBufferType")
		return 0;
	}

	OpenGLVertexbuffer::OpenGLVertexbuffer(Device* device, f32* vertices, u32 size, VertexbufferType type)
	{
		GLenum glType = VertexbufferTypeToOpenGLType(type);
		m_Type = type;

		GLuint handle = 0;
		glGenBuffers(1, &handle);
		glBindBuffer(GL_ARRAY_BUFFER, handle);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, glType);

		m_Handle.Ptr = &handle;
		m_Device = device;

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	OpenGLVertexbuffer::OpenGLVertexbuffer(Device* device, u32 size, VertexbufferType type)
	{
		GLenum glType = VertexbufferTypeToOpenGLType(type);
		m_Type = type;

		GLuint handle = 0;
		glGenBuffers(1, &handle);
		glBindBuffer(GL_ARRAY_BUFFER, handle);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, glType);

		m_Handle.Ptr = &handle;
		m_Device = device;
	}

	OpenGLVertexbuffer::~OpenGLVertexbuffer()
	{
		if (m_Handle.Ptr) {
			GLuint* handle = static_cast<GLuint*>(m_Handle.Ptr);
			glDeleteBuffers(1, handle);
			m_Handle.Ptr = nullptr;
		}
	}
	
	void OpenGLVertexbuffer::Bind()
	{
		if (!m_Device->IsActiveVertexbuffer(m_Handle)) {
			GLuint* handle = static_cast<GLuint*>(m_Handle.Ptr);
			glBindBuffer(GL_ARRAY_BUFFER, *handle);
			m_Device->SetActiveVertexbuffer(&m_Handle);
		}
	}

	void OpenGLVertexbuffer::Unbind()
	{
		m_Device->SetActiveVertexbuffer(nullptr);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexbuffer::SetData(const void* data, u32 size)
	{
		if (!m_Device->IsActiveVertexbuffer(m_Handle)) {
			GLuint* handle = static_cast<GLuint*>(m_Handle.Ptr);
			glBindBuffer(GL_ARRAY_BUFFER, *handle);
			m_Device->SetActiveVertexbuffer(&m_Handle);
		}
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}
}