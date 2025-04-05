
#include "pch.h"
#include "opengl_buffer.h"
#include "opengl_funcs.h"

PRIME_INLINE u32 bufferTypeToGL(u32 type)
{
    switch (type) {
        case PRIME_VERTEX_BUFFER: {
            return GL_ARRAY_BUFFER;
            break;
        }
        case PRIME_INDEX_BUFFER: {
            return GL_ELEMENT_ARRAY_BUFFER;  
            break;
        }
        case PRIME_UNIFORM_BUFFER: {
            return GL_UNIFORM_BUFFER;
            break;
        }
        case PRIME_STORAGE_BUFFER: {
            return GL_SHADER_STORAGE_BUFFER;
            break;
        }
    }

    PRIME_ASSERT_MSG(false, "invalid buffer type");
    return 0;
}

u32 bufferUsageToGL(u32 usage)
{
    switch (usage) {
        case PRIME_STATIC: {
            return GL_STATIC_DRAW;
            break;
        }
        case PRIME_DYNAMIC: {
            return GL_DYNAMIC_DRAW;  
            break;
        }
    }

    PRIME_ASSERT_MSG(false, "invalid buffer type");
    return 0;
}

struct gl_buffer
{
    u32 id = 0;
    prime_buffer_desc desc;
};

void* gl_CreateBuffer(prime_buffer_desc desc)
{
    gl_buffer* buffer = new gl_buffer();
    PRIME_ASSERT_MSG(buffer, "failed to create opengl buffer handle");
    buffer->desc.type = bufferTypeToGL(desc.type);
    buffer->desc.binding = desc.binding;
    buffer->desc.data = desc.data;
    buffer->desc.size = desc.size;
    buffer->desc.usage = bufferUsageToGL(desc.usage);
    glGenBuffers(1, &buffer->id);
    return buffer;
}

void gl_DestroyBuffer(void* handle)
{
    gl_buffer* buffer = (gl_buffer*)handle;
    glDeleteBuffers(1, &buffer->id);
    delete buffer;
}

void gl_BindBuffer(void* handle, b8 send_data)
{
    gl_buffer* buffer = (gl_buffer*)handle;
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

void gl_SetBufferData(void* handle, void* data, u32 size)
{
    gl_buffer* buffer = (gl_buffer*)handle;
    glBufferSubData(buffer->desc.type, 0, size, data);
}