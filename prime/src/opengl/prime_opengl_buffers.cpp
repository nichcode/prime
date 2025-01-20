
#include "prime_opengl_buffers.h"
#include "prime/prime_memory.h"
#include "prime/prime_log.h"

#include "glad/glad.h"

struct gl_Vertexbuffer
{
	GLuint vertexarray = 0;
	GLuint id = 0;
};

struct gl_Indexbuffer
{
	GLuint id = 0;
};

static GLenum
dataTypeToGLType(prime_DataType type)
{
	switch (type)
	{
	case prime_DataTypeInt:
	case prime_DataTypeInt2:
	case prime_DataTypeInt3:
	case prime_DataTypeInt4:
		return GL_INT;

	case prime_DataTypeFloat:
	case prime_DataTypeFloat2:
	case prime_DataTypeFloat3:
	case prime_DataTypeFloat4:
	case prime_DataTypeMat3:
	case prime_DataTypeMat4:
		return GL_FLOAT;

	case prime_DataTypeBool:
		return GL_BOOL;
	}
	return 0;
}

void*
gl_CreateVertexbuffer(const void* data, u32 size, prime_VertexbufferType type)
{
	gl_Vertexbuffer* handle = nullptr;
	handle = (gl_Vertexbuffer*)prime_MemAlloc(sizeof(gl_Vertexbuffer));

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
gl_DestroyVertexbuffer(void* handle)
{
	gl_Vertexbuffer* buffer = (gl_Vertexbuffer*)handle;

	glDeleteVertexArrays(1, &buffer->vertexarray);
	glDeleteBuffers(1, &buffer->id);

	buffer->id = 0;
	buffer->vertexarray = 0;
	prime_MemFree(handle, sizeof(gl_Vertexbuffer));
}

void
gl_BindVertexbuffer(void* handle)
{
	gl_Vertexbuffer* buffer = (gl_Vertexbuffer*)handle;

	glBindVertexArray(buffer->vertexarray);
	glBindBuffer(GL_ARRAY_BUFFER, buffer->id);
}

void
gl_UnbindVertexbuffer(void* handle)
{
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void 
gl_SetVertexbufferLayout(void* handle, const prime_BufferElement* element, u32 stride)
{
	GLuint index = 0;
	switch (element->type) {
	case prime_DataTypeFloat:
	case prime_DataTypeFloat2:
	case prime_DataTypeFloat3:
	case prime_DataTypeFloat4:
	{
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index,
			prime_DataTypeGetCount(element->type),
			dataTypeToGLType(element->type),
			GL_FALSE,
			stride,
			(const void*)element->offset);
		index++;
		break;
	}
	case prime_DataTypeInt:
	case prime_DataTypeInt2:
	case prime_DataTypeInt3:
	case prime_DataTypeInt4:
	case prime_DataTypeBool:
	{
		glEnableVertexAttribArray(index);
		glVertexAttribIPointer(index,
			prime_DataTypeGetCount(element->type),
			dataTypeToGLType(element->type),
			stride,
			(const void*)element->offset);
		index++;
		break;
	}
	case prime_DataTypeMat3:
	case prime_DataTypeMat4:
	{
		u8 count = prime_DataTypeGetCount(element->type);
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
gl_SetVertexbufferData(void* handle, const void* data, u32 size)
{
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

void* 
gl_CreateIndexbuffer(u32* indices, u32 count)
{
	gl_Indexbuffer* handle = nullptr;
	handle = (gl_Indexbuffer*)prime_MemAlloc(sizeof(gl_Indexbuffer));

	glGenBuffers(1, &handle->id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle->id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(u32), indices, GL_STATIC_DRAW);

	return handle;
}

void
gl_DestroyIndexbuffer(void* handle)
{
	gl_Vertexbuffer* buffer = (gl_Vertexbuffer*)handle;

	glDeleteBuffers(1, &buffer->id);
	buffer->id = 0;
	prime_MemFree(buffer, sizeof(gl_Indexbuffer));
}

void 
gl_BindIndexbuffer(void* handle)
{
	gl_Vertexbuffer* buffer = (gl_Vertexbuffer*)handle;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->id);
}

void 
gl_UnbindIndexbuffer(void* handle)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
