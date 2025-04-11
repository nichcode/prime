
#include "pch.h"
#include "prime/buffer.h"

prBuffer* prCreateBuffer(prContext* context, prBufferDesc desc)
{
    PR_ASSERT(context, "context is null");
    prBuffer* buffer = new prBuffer();
    PR_ASSERT(buffer, "failed to create buffer");

    buffer->dataSent = false;
    buffer->type = desc.type;
    buffer->context = context;
    buffer->handle = context->api.createBuffer(desc);

    // rebind the previous active buffer
    if (buffer->type == prBufferTypes_Vertex) {
        if (context->state.activeVertexBuffer) {
            context->api.bindBuffer(context->state.activeVertexBuffer->handle);
        }
    }

    else if (buffer->type == prBufferTypes_Index) {
        if (context->state.activeIndexBuffer) {
            context->api.bindBuffer(context->state.activeIndexBuffer->handle);
        }
    }

    else if (buffer->type == prBufferTypes_Storage) {
        if (context->state.activeStorageBuffer) {
            context->api.bindBuffer(context->state.activeStorageBuffer->handle);
        }
    }

    else if (buffer->type == prBufferTypes_Uniform) {
        if (context->state.activeUniformBuffer) {
            context->api.bindBuffer(context->state.activeUniformBuffer->handle);
        }
    }

    context->data.buffers.push_back(buffer);
    return buffer;
}

void prDestroyBuffer(prBuffer* buffer)
{
    PR_ASSERT(buffer, "buffer is null");
    prContext* context = buffer->context;

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
    prContext* context = buffer->context;

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
    if (type == prBufferTypes_Vertex) {
        PR_ASSERT(s_ActiveContext->state.activeVertexBuffer, "no vertex buffer bound");
        s_ActiveContext->api.setBufferData(s_ActiveContext->state.activeVertexBuffer->handle, data, size);
    }

    else if (type == prBufferTypes_Index) {
        PR_ASSERT(s_ActiveContext->state.activeIndexBuffer, "no index buffer bound");
        s_ActiveContext->api.setBufferData(s_ActiveContext->state.activeIndexBuffer->handle, data, size);
    }

    else if (type == prBufferTypes_Storage) {
        PR_ASSERT(s_ActiveContext->state.activeStorageBuffer, "no Storage buffer bound");
        s_ActiveContext->api.setBufferData(s_ActiveContext->state.activeStorageBuffer->handle, data, size);
    }

    else if (type == prBufferTypes_Uniform) {
        PR_ASSERT(s_ActiveContext->state.activeUniformBuffer, "no Uniform buffer bound");
        s_ActiveContext->api.setBufferData(s_ActiveContext->state.activeUniformBuffer->handle, data, size);
    }
}