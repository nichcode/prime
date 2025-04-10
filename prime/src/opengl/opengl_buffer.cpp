
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
    prBufferDesc desc;
};

void* _GLCreateBuffer(prBufferDesc desc)
{
    glBuffer* buffer = new glBuffer();
    PR_ASSERT(buffer, "failed to create opengl buffer handle");
    buffer->desc.type = bufferTypeToGL(desc.type);
    buffer->desc.binding = desc.binding;
    buffer->desc.data = desc.data;
    buffer->desc.size = desc.size;
    buffer->desc.usage = bufferUsageToGL(desc.usage);
    glGenBuffers(1, &buffer->id);
    return buffer;
}

void _GLDestroyBuffer(void* handle)
{
    glBuffer* buffer = (glBuffer*)handle;
    glDeleteBuffers(1, &buffer->id);
    delete buffer;
    handle = nullptr;
}

void _GLBindBuffer(void* handle, b8 send_data)
{
    glBuffer* buffer = (glBuffer*)handle;
    if (send_data) {
        switch (buffer->desc.type) {
            case GL_ARRAY_BUFFER: 
            case GL_ELEMENT_ARRAY_BUFFER: {
                glBindBuffer(buffer->desc.type, buffer->id);
                glBufferData(buffer->desc.type, buffer->desc.size, buffer->desc.data, buffer->desc.usage);
                break;
            }
            case GL_UNIFORM_BUFFER:
            case GL_SHADER_STORAGE_BUFFER: {
                glBindBuffer(buffer->desc.type, buffer->id);
                glBufferData(buffer->desc.type, buffer->desc.size, buffer->desc.data, buffer->desc.usage);
                glBindBufferBase(buffer->desc.type, buffer->desc.binding, buffer->id);
                break;
            }
        }
    }
    else {
        glBindBuffer(buffer->desc.type, buffer->id);
    }
}

void _GLSetBufferData(void* handle, void* data, u32 size)
{
    glBuffer* buffer = (glBuffer*)handle;
    glBufferSubData(buffer->desc.type, 0, size, data);
}