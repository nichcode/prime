
#include "pch.h"

struct prime_buffer
{
    void* handle = nullptr;
    b8 dataSent = false;
};

prime_buffer* prime_create_buffer(prime_buffer_desc desc)
{
    prime_buffer* buffer = new prime_buffer();
    PRIME_ASSERT_MSG(buffer, "failed to create buffer");

    buffer->dataSent = false;
    buffer->handle = s_Data.api.createBuffer(desc);
    return buffer;
}

void prime_destroy_buffer(prime_buffer* buffer)
{
    PRIME_ASSERT_MSG(buffer, "buffer is null");
    if (s_Data.activeBuffer == buffer) {
        s_Data.activeBuffer = nullptr;
    }
    s_Data.api.destroyBuffer(buffer->handle);
    delete buffer;
    buffer = nullptr;
}

void prime_set_buffer_data(void* data, u32 size)
{
    PRIME_ASSERT_MSG(s_Data.activeBuffer, "active buffer not set");
    s_Data.api.setBufferData(s_Data.activeBuffer->handle, data, size);
}

void prime_bind_buffer(prime_buffer* buffer)
{
    PRIME_ASSERT_MSG(buffer, "buffer is null");
    s_Data.activeBuffer = buffer;
    if (!buffer->dataSent) {
        s_Data.api.bindBuffer(buffer->handle, true);
    }
    else {
        s_Data.api.bindBuffer(buffer->handle, false);
    }
    
}