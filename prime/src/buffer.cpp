
#include "pch.h"
#include "prime/buffer.h"

prBuffer* prCreateBuffer(prBufferDesc desc)
{
    PR_ASSERT(s_ActiveContext, "no context bound");
    prBuffer* buffer = new prBuffer();
    PR_ASSERT(buffer, "failed to create buffer");

    buffer->dataSent = false;
    buffer->type = desc.type;
    buffer->handle = s_ActiveContext->api.createBuffer(desc);

    // rebind the previous active buffer
    if (buffer->type == prBufferTypes_Vertex) {
        if (s_ActiveContext->state.activeVertexBuffer) {
            s_ActiveContext->api.bindBuffer(s_ActiveContext->state.activeVertexBuffer->handle);
        }
    }

    else if (buffer->type == prBufferTypes_Index) {
        if (s_ActiveContext->state.activeIndexBuffer) {
            s_ActiveContext->api.bindBuffer(s_ActiveContext->state.activeIndexBuffer->handle);
        }
    }

    else if (buffer->type == prBufferTypes_Storage) {
        if (s_ActiveContext->state.activeStorageBuffer) {
            s_ActiveContext->api.bindBuffer(s_ActiveContext->state.activeStorageBuffer->handle);
        }
    }

    else if (buffer->type == prBufferTypes_Uniform) {
        if (s_ActiveContext->state.activeUniformBuffer) {
            s_ActiveContext->api.bindBuffer(s_ActiveContext->state.activeUniformBuffer->handle);
        }
    }

    s_ActiveContext->data.buffers.push_back(buffer);
    return buffer;
}

void prDestroyBuffer(prBuffer* buffer)
{
    PR_ASSERT(buffer, "buffer is null");
    PR_ASSERT(s_ActiveContext, "no context bound");
    prContext* context = s_ActiveContext;

    auto it = std::find(context->data.buffers.begin(), context->data.buffers.end(), buffer);
    if (it != context->data.buffers.end()) {
        context->data.buffers.erase(it); 
    }

    if (buffer->type == prBufferTypes_Vertex) {
        if (context->state.activeVertexBuffer == buffer) {
            context->state.activeVertexBuffer = nullptr;
        }
    }

    else if (buffer->type == prBufferTypes_Index) {
        if (context->state.activeIndexBuffer == buffer) {
            context->state.activeIndexBuffer = nullptr;
        }
    }

    else if (buffer->type == prBufferTypes_Storage) {
        if (context->state.activeStorageBuffer == buffer) {
            context->state.activeStorageBuffer = nullptr;
        }
    }

    else if (buffer->type == prBufferTypes_Uniform) {
        if (context->state.activeUniformBuffer == buffer) {
            context->state.activeUniformBuffer = nullptr;
        }
    }

    context->api.destroyBuffer(buffer->handle);
    delete buffer;
    buffer = nullptr;
}

void prBindBuffer(prBuffer* buffer)
{
    PR_ASSERT(buffer, "buffer is null");
    PR_ASSERT(s_ActiveContext, "no context bound");
    prContext* context = s_ActiveContext;

    if (buffer->type == prBufferTypes_Vertex) {
        if (context->state.activeVertexBuffer != buffer) {
            context->state.activeVertexBuffer = buffer;
            context->api.bindBuffer(buffer->handle);
        }
    }

    else if (buffer->type == prBufferTypes_Index) {
        if (context->state.activeIndexBuffer != buffer) {
            context->state.activeIndexBuffer = buffer;
            context->api.bindBuffer(buffer->handle);
        }
    }

    else if (buffer->type == prBufferTypes_Storage) {
        if (context->state.activeStorageBuffer != buffer) {
            context->state.activeStorageBuffer = buffer;
            context->api.bindBuffer(buffer->handle);
        }
    }

    else if (buffer->type == prBufferTypes_Uniform) {
        if (context->state.activeUniformBuffer != buffer) {
            context->state.activeUniformBuffer = buffer;
            context->api.bindBuffer(buffer->handle);
        }
    }
}

void prSetBufferData(u32 type, void* data, u32 size)
{
    PR_ASSERT(s_ActiveContext, "no context bound");
    prContext* context = s_ActiveContext;

    if (type == prBufferTypes_Vertex) {
        PR_ASSERT(context->state.activeVertexBuffer, "no vertex buffer bound");
        context->api.setBufferData(context->state.activeVertexBuffer->handle, data, size);
    }

    else if (type == prBufferTypes_Index) {
        PR_ASSERT(context->state.activeIndexBuffer, "no index buffer bound");
        context->api.setBufferData(context->state.activeIndexBuffer->handle, data, size);
    }

    else if (type == prBufferTypes_Storage) {
        PR_ASSERT(context->state.activeStorageBuffer, "no Storage buffer bound");
        context->api.setBufferData(context->state.activeStorageBuffer->handle, data, size);
    }

    else if (type == prBufferTypes_Uniform) {
        PR_ASSERT(context->state.activeUniformBuffer, "no Uniform buffer bound");
        context->api.setBufferData(context->state.activeUniformBuffer->handle, data, size);
    }
}