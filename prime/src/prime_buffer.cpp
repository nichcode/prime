
#include "pch.h"

struct prime_buffer
{
    void* handle = nullptr;
    b8 dataSent = false;
    u32 type = 0;
};

prime_buffer* prime_create_buffer(prime_buffer_desc desc)
{
    prime_buffer* buffer = new prime_buffer();
    PRIME_ASSERT_MSG(buffer, "failed to create buffer");

    buffer->dataSent = false;
    buffer->type = desc.type;
    buffer->handle = s_Data.api.createBuffer(desc);
    s_Data.buffers.push_back(buffer);
    return buffer;
}

void prime_destroy_buffer(prime_buffer* buffer)
{
    PRIME_ASSERT_MSG(buffer, "buffer is null");
    auto it = std::find(s_Data.buffers.begin(), s_Data.buffers.end(), buffer);
    if (it != s_Data.buffers.end()) {
        s_Data.buffers.erase(it); 
    }
    prime_DestroyBuffer(buffer);
}

void prime_set_buffer_data(u32 type, void* data, u32 size)
{
    if (type == PRIME_VERTEX_BUFFER) {
        PRIME_ASSERT_MSG(s_Data.activeVBuffer, "no vertex buffer bound");
        s_Data.api.setBufferData(s_Data.activeVBuffer->handle, data, size);
    }

    else if (type == PRIME_INDEX_BUFFER) {
        PRIME_ASSERT_MSG(s_Data.activeIBuffer, "no index buffer bound");
        s_Data.api.setBufferData(s_Data.activeIBuffer->handle, data, size);
    }

    else if (type == PRIME_STORAGE_BUFFER) {
        PRIME_ASSERT_MSG(s_Data.activeSBuffer, "no storage buffer bound");
        s_Data.api.setBufferData(s_Data.activeSBuffer->handle, data, size);
    }

    else if (type == PRIME_UNIFORM_BUFFER) {
        PRIME_ASSERT_MSG(s_Data.activeUBuffer, "no uniform buffer bound");
        s_Data.api.setBufferData(s_Data.activeUBuffer->handle, data, size);
    }
}

void prime_bind_buffer(prime_buffer* buffer)
{
    PRIME_ASSERT_MSG(buffer, "buffer is null");
    if (buffer->type == PRIME_VERTEX_BUFFER) {
        if (s_Data.activeVBuffer != buffer) {
            s_Data.activeVBuffer = buffer;
        }
    }
    
    else if (buffer->type == PRIME_INDEX_BUFFER) {
        if (s_Data.activeIBuffer != buffer) {
            s_Data.activeIBuffer = buffer;
        }
    }
    
    else if (buffer->type == PRIME_STORAGE_BUFFER) {
        if (s_Data.activeSBuffer != buffer) {
            s_Data.activeSBuffer = buffer;
        }
    }
    
    else if (buffer->type == PRIME_VERTEX_BUFFER) {
        if (s_Data.activeUBuffer != buffer) {
            s_Data.activeUBuffer = buffer;
        }
    }

    if (!buffer->dataSent) {
        s_Data.api.bindBuffer(buffer->handle, true);
    }
    else {
        s_Data.api.bindBuffer(buffer->handle, false);
    }
}

void prime_DestroyBuffer(prime_buffer* buffer)
{
    if (buffer->type == PRIME_VERTEX_BUFFER) {
        if (s_Data.activeVBuffer == buffer) {
            s_Data.activeVBuffer = nullptr;
        }
    }

    else if (buffer->type == PRIME_INDEX_BUFFER) {
        if (s_Data.activeIBuffer == buffer) {
            s_Data.activeIBuffer = nullptr;
        }
    }

    else if (buffer->type == PRIME_STORAGE_BUFFER) {
        if (s_Data.activeSBuffer == buffer) {
            s_Data.activeSBuffer = nullptr;
        }
    }

    else if (buffer->type == PRIME_UNIFORM_BUFFER) {
        if (s_Data.activeUBuffer == buffer) {
            s_Data.activeUBuffer = nullptr;
        }
    }

    s_Data.api.destroyBuffer(buffer->handle);
    delete buffer;
    buffer = nullptr;
}