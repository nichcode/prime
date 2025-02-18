
#include "prime_glconstantbuffer.h"
#include "prime/prime_memory.h"

#include "glad/glad.h"

struct glConstantbuffer
{
	GLuint id = 0;
};

void*
primeGLConstantbufferCreate(u32 size, u32 binding)
{
    glConstantbuffer* buffer = nullptr;
	buffer = (glConstantbuffer*)primeMemoryAlloc(sizeof(glConstantbuffer));

	glGenBuffers(1, &buffer->id);
	glBindBuffer(GL_UNIFORM_BUFFER, buffer->id);
	glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, binding, buffer->id);

	return buffer;
}

void
primeGLConstantbufferDestroy(void* handle)
{
    glConstantbuffer* buffer = (glConstantbuffer*)handle;
	glDeleteBuffers(1, &buffer->id);
	buffer->id = 0;
	primeMemoryFree(handle, sizeof(glConstantbuffer));
}

void
primeGLConstantbufferBind(void* handle)
{
    glConstantbuffer* buffer = (glConstantbuffer*)handle;
	glBindBuffer(GL_UNIFORM_BUFFER, buffer->id);
}

void
primeGLConstantbufferUnbind(void* handle)
{
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void
primeGLConstantbufferSetData(void* handle, const void* data, u32 size)
{
    glBufferSubData(GL_UNIFORM_BUFFER, 0, size, data);
}