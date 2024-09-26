
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
		m_Type = type;

		glGenBuffers(1, &m_ID);
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
		glBufferData(GL_ARRAY_BUFFER, size, data, glType);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glGenVertexArrays(1, &m_Vertexarray);
	}

	OpenGLVertexbuffer::~OpenGLVertexbuffer()
	{
		glDeleteBuffers(1, &m_ID);
		glDeleteVertexArrays(1, &m_Vertexarray);
		m_ID = 0;
		m_Vertexarray = 0;
	}

	void OpenGLVertexbuffer::Bind()
	{
		glBindVertexArray(m_Vertexarray);
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
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

		m_Layout = vertexbufferlayout;
		GLuint index = 0;
		Bind();

		const auto& layout = vertexbufferlayout;
		for (const auto& element : layout)
		{
			switch (element.Type)
			{
			case DataTypeFloat:
			case DataTypeFloat2:
			case DataTypeFloat3:
			case DataTypeFloat4:
			{
				glEnableVertexAttribArray(index);
				glVertexAttribPointer(index,
					GetDataTypeCount(element.Type),
					DataTypeToOpenGLType(element.Type),
					GL_FALSE,
					layout.GetStride(),
					(const void*)element.Offset);
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
					GetDataTypeCount(element.Type),
					DataTypeToOpenGLType(element.Type),
					layout.GetStride(),
					(const void*)element.Offset);
				index++;
				break;
			}
			case DataTypeMat3:
			case DataTypeMat4:
			{
				u8 count = GetDataTypeCount(element.Type);
				for (u8 i = 0; i < count; i++)
				{
					glEnableVertexAttribArray(index);
					glVertexAttribPointer(index,
						count,
						DataTypeToOpenGLType(element.Type),
						GL_FALSE,
						layout.GetStride(),
						(const void*)(element.Offset + sizeof(f32) * count * i));
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