
#include "opengl_vertexarray.h"
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

	OpenGLVertexarray::OpenGLVertexarray(Device* device)
	{
		GLuint handle = 0;
		glGenVertexArrays(1, &handle);
		m_Handle.Ptr = &handle;
		m_Device = device;
		m_Index = 0;
	}

	OpenGLVertexarray::~OpenGLVertexarray()
	{
		if (m_Handle.Ptr) {
			GLuint* handle = static_cast<GLuint*>(m_Handle.Ptr);
			glDeleteVertexArrays(1, handle);
			m_Handle.Ptr = nullptr;
		}
	}

	void OpenGLVertexarray::Bind()
	{
		if (!m_Device->IsActiveVertexarray(m_Handle)) {
			GLuint* handle = static_cast<GLuint*>(m_Handle.Ptr);
			glBindVertexArray(*handle);
			m_Device->SetActiveVertexarray(&m_Handle);
		}
	}

	void OpenGLVertexarray::Unbind()
	{
		m_Device->SetActiveVertexarray(nullptr);
		glBindVertexArray(0);
	}

	void OpenGLVertexarray::SetVertexBuffer(const Ref<Vertexbuffer>& vertexBuffer)
	{
		PASSERT_MSG(vertexBuffer->GetLayout().GetElements().size(),
			"Vertexbuffer has no layout");

		Bind();
		vertexBuffer->Bind();

		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			switch (element.Type)
			{
			case DataTypeFloat:
			case DataTypeFloat2:
			case DataTypeFloat3:
			case DataTypeFloat4:
			{
				glEnableVertexAttribArray(m_Index);
				glVertexAttribPointer(m_Index,
					GetDataTypeCount(element.Type),
					DataTypeToOpenGLType(element.Type),
					GL_FALSE,
					layout.GetStride(),
					(const void*)element.Offset);
				m_Index++;
				break;
			}
			case DataTypeInt:
			case DataTypeInt2:
			case DataTypeInt3:
			case DataTypeInt4:
			case DataTypeBool:
			{
				glEnableVertexAttribArray(m_Index);
				glVertexAttribIPointer(m_Index,
					GetDataTypeCount(element.Type),
					DataTypeToOpenGLType(element.Type),
					layout.GetStride(),
					(const void*)element.Offset);
				m_Index++;
				break;
			}
			case DataTypeMat3:
			case DataTypeMat4:
			{
				u8 count = GetDataTypeCount(element.Type);
				for (u8 i = 0; i < count; i++)
				{
					glEnableVertexAttribArray(m_Index);
					glVertexAttribPointer(m_Index,
						count,
						DataTypeToOpenGLType(element.Type),
						GL_FALSE,
						layout.GetStride(),
						(const void*)(element.Offset + sizeof(f32) * count * i));
					glVertexAttribDivisor(m_Index, 1);
					m_Index++;
				}
				break;
			}
			}
		}

		m_Vertexbuffer = vertexBuffer;
	}

	void OpenGLVertexarray::SetIndexBuffer(const Ref<Indexbuffer>& indexBuffer)
	{
		Bind();
		indexBuffer->Bind();
		m_Indexbuffer = indexBuffer;
	}
}