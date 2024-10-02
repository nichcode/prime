
#include "opengl_vertexbuffer.h"
#include "prime/prime_device.h"
#include "platform/glad/glad.h"

namespace prime {

	PINLINE static GLenum DataTypeToOpenGLType(DataType type)
	{
		switch (type)
		{
		case DataTypeInt:
		case DataTypeInt2:
		case DataTypeInt3:
		case DataTypeInt4:
			return GL_INT;

		case DataTypeFloat:
		case DataTypeFloat2:
		case DataTypeFloat3:
		case DataTypeFloat4:
		case DataTypeMat3:
		case DataTypeMat4:
			return GL_FLOAT;

		case DataTypeBool:
			return GL_BOOL;
		}
		PASSERT_MSG(type, "Invalid Datatype");
		return 0;
	}

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
		PASSERT_MSG(false, "Invalid VertexBufferType");
		return 0;
	}

	OpenGLVertexbuffer::OpenGLVertexbuffer(const void* data, u32 size, VertexbufferType type)
	{
		GLenum glType = VertexbufferTypeToOpenGLType(type);
		m_type = type;

		glGenBuffers(1, &m_id);
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
		glBufferData(GL_ARRAY_BUFFER, size, data, glType);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glGenVertexArrays(1, &m_vertexarray);
	}

	OpenGLVertexbuffer::~OpenGLVertexbuffer()
	{
		glDeleteBuffers(1, &m_id);
		glDeleteVertexArrays(1, &m_vertexarray);
		m_id = 0;
		m_vertexarray = 0;
	}

	void OpenGLVertexbuffer::Bind()
	{
		glBindVertexArray(m_vertexarray);
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
	}

	void OpenGLVertexbuffer::Unbind()
	{
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexbuffer::SetLayout(const VertexbufferLayout& vertexbufferlayout)
	{
		PASSERT_MSG(vertexbufferlayout.GetElements().size(),
			"VertexbufferLayout has no layout");

		m_layout = vertexbufferlayout;
		GLuint index = 0;

		const auto& layout = vertexbufferlayout;
		for (const auto& element : layout)
		{
			switch (element.type)
			{
			case DataTypeFloat:
			case DataTypeFloat2:
			case DataTypeFloat3:
			case DataTypeFloat4:
			{
				glEnableVertexAttribArray(index);
				glVertexAttribPointer(index,
					GetDataTypeCount(element.type),
					DataTypeToOpenGLType(element.type),
					GL_FALSE,
					layout.GetStride(),
					(const void*)element.offset);
				index++;
				break;
			}
			case DataTypeInt:
			case DataTypeInt2:
			case DataTypeInt3:
			case DataTypeInt4:
			case DataTypeBool:
			{
				glEnableVertexAttribArray(index);
				glVertexAttribIPointer(index,
					GetDataTypeCount(element.type),
					DataTypeToOpenGLType(element.type),
					layout.GetStride(),
					(const void*)element.offset);
				index++;
				break;
			}
			case DataTypeMat3:
			case DataTypeMat4:
			{
				u8 count = GetDataTypeCount(element.type);
				for (u8 i = 0; i < count; i++)
				{
					glEnableVertexAttribArray(index);
					glVertexAttribPointer(index,
						count,
						DataTypeToOpenGLType(element.type),
						GL_FALSE,
						layout.GetStride(),
						(const void*)(element.offset + sizeof(f32) * count * i));
					glVertexAttribDivisor(index, 1);
					index++;
				}
				break;
			}
			}
		}
	}

	void OpenGLVertexbuffer::SetData(const void* data, u32 size)
	{
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}
}