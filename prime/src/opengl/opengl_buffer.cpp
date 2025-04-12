
#include "pch.h"
#include "opengl_buffer.h"
#include "opengl_funcs.h"

inline u32 bufferTypeToGL(u32 type)
{
    switch (type) {
        case prBufferTypes_Vertex: {
            return GL_ARRAY_BUFFER;
            break;
        }
        case prBufferTypes_Index: {
            return GL_ELEMENT_ARRAY_BUFFER;  
            break;
        }

        case prBufferTypes_Storage: {
            return GL_SHADER_STORAGE_BUFFER;
            break;
        }

        case prBufferTypes_Uniform: {
            return GL_UNIFORM_BUFFER;
            break;
        }
    }

    PR_ASSERT(false, "invalid buffer type");
    return 0;
}

inline u32 bufferUsageToGL(u32 usage)
{
    switch (usage) {
        case prBufferUsages_Static: {
            return GL_STATIC_DRAW;
            break;
        }
        case prBufferUsages_Dynamic: {
            return GL_DYNAMIC_DRAW;  
            break;
        }
    }

    PR_ASSERT(false, "invalid buffer type");
    return 0;
}

struct glBuffer
{
    u32 id = 0;
    u32 type = 0;
};

void* _GLCreateBuffer(prBufferDesc desc)
{
    glBuffer* buffer = new glBuffer();
    PR_ASSERT(buffer, "failed to create opengl buffer handle");
    buffer->type = bufferTypeToGL(desc.type);
    u32 usage = bufferUsageToGL(desc.usage);
    glGenBuffers(1, &buffer->id);

    switch (buffer->type) {
        case GL_ARRAY_BUFFER: 
        case GL_ELEMENT_ARRAY_BUFFER: {
            glBindBuffer(buffer->type, buffer->id);
            glBufferData(buffer->type, desc.size, desc.data, usage);
            break;
        }
        case GL_UNIFORM_BUFFER:
        case GL_SHADER_STORAGE_BUFFER: {
            glBindBuffer(buffer->type, buffer->id);
            glBufferData(buffer->type, desc.size, desc.data, usage);
            glBindBufferBase(buffer->type, desc.binding, buffer->id);
            break;
        }
    }

    glBindBuffer(buffer->type, 0);
    return buffer;
}

void _GLDestroyBuffer(void* handle)
{
    glBuffer* buffer = (glBuffer*)handle;
    glDeleteBuffers(1, &buffer->id);
    delete buffer;
    handle = nullptr;
}

void _GLBindBuffer(void* handle)
{
    glBuffer* buffer = (glBuffer*)handle;
    glBindBuffer(buffer->type, buffer->id);
}

void _GLSetBufferData(void* handle, void* data, u32 size)
{
    glBuffer* buffer = (glBuffer*)handle;
    glBufferSubData(buffer->type, 0, size, data);
}