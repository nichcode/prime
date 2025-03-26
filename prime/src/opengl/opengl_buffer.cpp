
#include "opengl_buffer.h"
#include "pch.h"
#include "opengl_funcs.h"

PRIME_INLINE u32 bufferTypeToGL(primeBufferType type)
{
    switch (type) {
        case primeBufferTypes_Vertex: {
            return GL_ARRAY_BUFFER;
            break;
        }
        case primeBufferTypes_Index: {
            return GL_ELEMENT_ARRAY_BUFFER;  
            break;
        }
        case primeBufferTypes_Uniform: {
            return GL_UNIFORM_BUFFER;
            break;
        }
        case primeBufferTypes_Storage: {
            return GL_SHADER_STORAGE_BUFFER;
            break;
        }
    } // switch
    PRIME_ASSERT_MSG(false, "invalid buffer type");
    return 0;
}

PRIME_INLINE u32 bufferUsageToGL(primeBufferUsage usage)
{
    switch (usage) {
        case primeBufferUsages_Static: {
            return GL_STATIC_DRAW;
            break;
        }
        case primeBufferUsages_Dynamic: {
            return GL_DYNAMIC_DRAW;  
            break;
        }
    } // switch
    PRIME_ASSERT_MSG(false, "invalid buffer usage");
    return 0;
}

struct glBuffer
{
    u32 id = 0;
    u32 type;
    u32 usage;
};

void* _glCreateBuffer(primeBufferDesc desc)
{
    glBuffer* buffer = new glBuffer();
    buffer->type = bufferTypeToGL(desc.type);
    buffer->usage = bufferUsageToGL(desc.usage);
    glGenBuffers(1, &buffer->id);
    switch (desc.type) {
        case primeBufferTypes_Vertex: {
            glBindBuffer(GL_ARRAY_BUFFER, buffer->id);
            glBufferData(GL_ARRAY_BUFFER, desc.size, desc.data, buffer->usage);
            break;
        }

        case primeBufferTypes_Index: {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->id);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, desc.size, desc.data, buffer->usage);
            break;
        }

        case primeBufferTypes_Uniform: {
            glBindBuffer(GL_UNIFORM_BUFFER, buffer->id);
            glBufferData(GL_UNIFORM_BUFFER, desc.size, desc.data, buffer->usage);
            glBindBufferBase(GL_UNIFORM_BUFFER, 0, buffer->id);
            break;
        }

        case primeBufferTypes_Storage: {
            glBindBuffer(GL_SHADER_STORAGE_BUFFER, buffer->id);
            glBufferData(GL_SHADER_STORAGE_BUFFER, desc.size, desc.data, buffer->usage);
            glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, buffer->id);
            break;
        }     
    } // switch

    return buffer;
}

void _glDestroyBuffer(void* handle)
{
    glBuffer* buffer = (glBuffer*)handle;
    glDeleteBuffers(1, &buffer->id);
    delete buffer;
}

void _glSetBufferData(void* handle, const void* data, u32 size)
{
    glBuffer* buffer = (glBuffer*)handle;
    glBufferSubData(buffer->type, 0, size, data);
}

void _glBindBuffer(void* handle)
{
    glBuffer* buffer = (glBuffer*)handle;
    glBindBuffer(buffer->type, buffer->id);
}

void _glUnbindBuffer(void* handle)
{
    glBuffer* buffer = (glBuffer*)handle;
    glBindBuffer(buffer->type, 0);
}
