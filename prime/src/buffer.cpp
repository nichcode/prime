
#include "prime/buffer.h"
#include "pch.h"

#include "opengl/opengl_buffer.h"

struct primeBuffer
{
    primeBufferType type;
    primeBufferUsage usage;
    void* handle = nullptr;

    void(*destroy)(void* handle) = nullptr;
    void(*bind)(void* handle) = nullptr;
    void(*unbind)(void* handle) = nullptr;
    void(*set)(void* handle, const void* data, u32 size) = nullptr;
};

primeBuffer* primeCreateBuffer(primeBufferDesc desc)
{
    primeBuffer* buffer = new primeBuffer();
    buffer->type = desc.type;
    buffer->usage = desc.usage;
    switch (s_InitData.type) {
        case primeDeviceTypes_OpenGL: {
            buffer->handle = _glCreateBuffer(desc);
            buffer->destroy = _glDestroyBuffer;
            buffer->bind = _glBindBuffer;
            buffer->unbind = _glUnbindBuffer;
            buffer->set = _glSetBufferData;
            break;
        } 
    } 
    s_InitData.buffers.push_back(buffer);
    return buffer;
}

void primeDestroyBuffer(primeBuffer* buffer)
{
    PRIME_ASSERT_MSG(buffer, "buffer is null");
    auto it = std::find(s_InitData.buffers.begin(), s_InitData.buffers.end(), buffer);
    if (it != s_InitData.buffers.end()) {
        s_InitData.buffers.erase(it); 
    }
    _primeDeleteBuffer(buffer);
}

void _primeDeleteBuffer(primeBuffer* buffer)
{
    if (s_InitData.activeBuffer == buffer) {
        buffer->unbind(buffer->handle);
        s_InitData.activeBuffer = nullptr;
    }
    buffer->destroy(buffer->handle);
    delete buffer;
    buffer = nullptr;
}

void primeSetBufferData(primeBuffer* buffer, const void* data, u32 size)
{
    PRIME_ASSERT_MSG(buffer, "buffer is null");
    if (buffer->usage == primeBufferUsages_Dynamic) {
        buffer->set(buffer->handle, data, size);
    }
}

void primeBindBuffer(primeBuffer* buffer)
{
    PRIME_ASSERT_MSG(buffer, "buffer is null");
    if (s_InitData.activeBuffer == nullptr || s_InitData.activeBuffer != buffer) {
        buffer->bind(buffer->handle);
        s_InitData.activeBuffer = buffer;
    }
}

void primeUnbindBuffer(primeBuffer* buffer)
{
    PRIME_ASSERT_MSG(buffer, "buffer is null");
    if (s_InitData.activeBuffer == buffer) {
        buffer->unbind(buffer->handle);
        s_InitData.activeBuffer = nullptr;
    }
}
