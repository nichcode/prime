
#include "opengl_buffers.h"
#include "prime/prime_memory.h"
#include "prime/prime_log.h"

#include "glad/glad.h"

struct prime_VertexbufferHandle
{
	GLuint vertexarray = 0;
	GLuint id = 0;
};

struct prime_IndexbufferHandle
{
	GLuint id = 0;
};

static GLenum
dataTypeToGLType(prime_BufferDataType type)
{
	switch (type)
	{
	case prime_BufferDataTypeInt:
	case prime_BufferDataTypeInt2:
	case prime_BufferDataTypeInt3:
	case prime_BufferDataTypeInt4:
		return GL_INT;

	case prime_BufferDataTypeFloat:
	case prime_BufferDataTypeFloat2:
	case prime_BufferDataTypeFloat3:
	case prime_BufferDataTypeFloat4:
	case prime_BufferDataTypeMat3:
	case prime_BufferDataTypeMat4:
		return GL_FLOAT;

	case prime_BufferDataTypeBool:
		return GL_BOOL;
	}
	PRIME_ASSERT_MSG(type, "Invalid Datatype");
	return 0;
}

prime_VertexbufferHandle*
gl_CreateVertexbuffer(const void* data, u32 size, prime_VertexbufferType type)
{
	prime_VertexbufferHandle* handle = nullptr;	
	handle = (prime_VertexbufferHandle*)prime_MemAlloc(sizeof(prime_VertexbufferHandle));

	GLenum gl_type = 0;
	if (type == prime_VertexbufferTypeStatic) {
		gl_type = GL_STATIC_DRAW;
	}
	else {
		gl_type = GL_DYNAMIC_DRAW;
	}

	glGenVertexArrays(1, &handle->vertexarray);
	glBindVertexArray(handle->vertexarray);

	glGenBuffers(1, &handle->id);
	glBindBuffer(GL_ARRAY_BUFFER, handle->id);
	glBufferData(GL_ARRAY_BUFFER, size, data, gl_type);

	return handle;
}

void 
gl_DestroyVertexbuffer(prime_VertexbufferHandle* handle)
{
	glDeleteVertexArrays(1, &handle->vertexarray);
	glDeleteBuffers(1, &handle->id);

	handle->id = 0;
	handle->vertexarray = 0;
	prime_MemFree(handle, sizeof(prime_VertexbufferHandle));
}

void
gl_BindVertexbuffer(prime_VertexbufferHandle* handle)
{
	glBindVertexArray(handle->vertexarray);
	glBindBuffer(GL_ARRAY_BUFFER, handle->id);
}

void
gl_UnbindVertexbuffer(prime_VertexbufferHandle* handle)
{
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void 
gl_SetVertexbufferLayout(const prime_BufferElement* element, u32 stride)
{
	GLuint index = 0;
	switch (element->type) {
	case prime_BufferDataTypeFloat:
	case prime_BufferDataTypeFloat2:
	case prime_BufferDataTypeFloat3:
	case prime_BufferDataTypeFloat4:
	{
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index,
			prime_GetDataTypeCount(element->type),
			dataTypeToGLType(element->type),
			GL_FALSE,
			stride,
			(const void*)element->offset);
		index++;
		break;
	}
	case prime_BufferDataTypeInt:
	case prime_BufferDataTypeInt2:
	case prime_BufferDataTypeInt3:
	case prime_BufferDataTypeInt4:
	case prime_BufferDataTypeBool:
	{
		glEnableVertexAttribArray(index);
		glVertexAttribIPointer(index,
			prime_GetDataTypeCount(element->type),
			dataTypeToGLType(element->type),
			stride,
			(const void*)element->offset);
		index++;
		break;
	}
	case prime_BufferDataTypeMat3:
	case prime_BufferDataTypeMat4:
	{
		u8 count = prime_GetDataTypeCount(element->type);
		for (u8 i = 0; i < count; i++)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				count,
				dataTypeToGLType(element->type),
				GL_FALSE,
				stride,
				(const void*)(element->offset + sizeof(f32) * count * i));
			glVertexAttribDivisor(index, 1);
			index++;
		}
		break;
	}

	}
}

void 
gl_SetVertexbufferData(prime_VertexbufferHandle* handle, const void* data, u32 size)
{
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

prime_IndexbufferHandle* 
gl_CreateIndexbuffer(u32* indices, u32 count)
{
	prime_IndexbufferHandle* handle = nullptr;
	handle = (prime_IndexbufferHandle*)prime_MemAlloc(sizeof(prime_IndexbufferHandle));

	glGenBuffers(1, &handle->id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle->id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(u32), indices, GL_STATIC_DRAW);

	return handle;
}

void
gl_DestroyIndexbuffer(prime_IndexbufferHandle* handle)
{
	glDeleteBuffers(1, &handle->id);

	handle->id = 0;
	prime_MemFree(handle, sizeof(prime_IndexbufferHandle));
}

void 
gl_BindIndexbuffer(prime_IndexbufferHandle* handle)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle->id);
}

void 
gl_UnbindIndexbuffer(prime_IndexbufferHandle* handle)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
