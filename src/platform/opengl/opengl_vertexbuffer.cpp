
#include "opengl_vertexbuffer.h"
#include "platform/glad/glad.h"

namespace prime {

	PINLINE static GLenum data_type_to_gl_type(DataType type)
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

	PINLINE GLenum vertexbuffer_type_to_gl_type(VertexbufferType type)
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
		GLenum gl_type = vertexbuffer_type_to_gl_type(type);
		m_type = type;

		glGenBuffers(1, &m_id);
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
		glBufferData(GL_ARRAY_BUFFER, size, data, gl_type);

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

	void OpenGLVertexbuffer::bind()
	{
		glBindVertexArray(m_vertexarray);
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
	}

	void OpenGLVertexbuffer::unbind()
	{
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexbuffer::set_layout(const VertexbufferLayout& v_layout)
	{
		PASSERT_MSG(v_layout.get_elements().size(),
			"VertexbufferLayout has no layout");

		m_layout = v_layout;
		GLuint index = 0;

		const auto& layout = v_layout;
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
					get_data_type_count(element.type),
					data_type_to_gl_type(element.type),
					GL_FALSE,
					layout.get_stride(),
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
					get_data_type_count(element.type),
					data_type_to_gl_type(element.type),
					layout.get_stride(),
					(const void*)element.offset);
				index++;
				break;
			}
			case DataTypeMat3:
			case DataTypeMat4:
			{
				u8 count = get_data_type_count(element.type);
				for (u8 i = 0; i < count; i++)
				{
					glEnableVertexAttribArray(index);
					glVertexAttribPointer(index,
						count,
						data_type_to_gl_type(element.type),
						GL_FALSE,
						layout.get_stride(),
						(const void*)(element.offset + sizeof(f32) * count * i));
					glVertexAttribDivisor(index, 1);
					index++;
				}
				break;
			}
			}
		}
	}

	void OpenGLVertexbuffer::set_data(const void* data, u32 size)
	{
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}
}