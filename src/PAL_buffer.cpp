
#include "PAL_pch.h"
#include "PAL/PAL_buffer.h"

PAL_Buffer* PAL_CreateBuffer(PAL_BufferDesc desc)
{
    PAL_ASSERT(s_ActiveContext, "no active context");
    PAL_Buffer* buffer = new PAL_Buffer();
    PAL_ASSERT(buffer, "failed to create buffer");

    buffer->dataSent = false;
    buffer->type = desc.type;
    buffer->handle = s_ActiveContext->api.createBuffer(desc);

    // rebind the previous active buffer
    if (buffer->type == PAL_BufferTypes_Vertex) {
        if (s_ActiveContext->state.activeVertexBuffer) {
            s_ActiveContext->api.bindBuffer(s_ActiveContext->state.activeVertexBuffer->handle);
        }
    }

    else if (buffer->type == PAL_BufferTypes_Index) {
        if (s_ActiveContext->state.activeIndexBuffer) {
            s_ActiveContext->api.bindBuffer(s_ActiveContext->state.activeIndexBuffer->handle);
        }
    }

    else if (buffer->type == PAL_BufferTypes_Storage) {
        if (s_ActiveContext->state.activeStorageBuffer) {
            s_ActiveContext->api.bindBuffer(s_ActiveContext->state.activeStorageBuffer->handle);
        }
    }

    else if (buffer->type == PAL_BufferTypes_Uniform) {
        if (s_ActiveContext->state.activeUniformBuffer) {
            s_ActiveContext->api.bindBuffer(s_ActiveContext->state.activeUniformBuffer->handle);
        }
    }

    s_ActiveContext->data.buffers.push_back(buffer);
    return buffer;
}

void PAL_DestroyBuffer(PAL_Buffer* buffer)
{
    PAL_ASSERT(buffer, "buffer is null");
    PAL_ASSERT(s_ActiveContext, "no active context");
    PAL_Context* context = s_ActiveContext;

    auto it = std::find(context->data.buffers.begin(), context->data.buffers.end(), buffer);
    if (it != context->data.buffers.end()) {
        context->data.buffers.erase(it); 
    }

    if (buffer->type == PAL_BufferTypes_Vertex) {
        if (context->state.activeVertexBuffer == buffer) {
            context->state.activeVertexBuffer = nullptr;
        }
    }

    else if (buffer->type == PAL_BufferTypes_Index) {
        if (context->state.activeIndexBuffer == buffer) {
            context->state.activeIndexBuffer = nullptr;
        }
    }

    else if (buffer->type == PAL_BufferTypes_Storage) {
        if (context->state.activeStorageBuffer == buffer) {
            context->state.activeStorageBuffer = nullptr;
        }
    }

    else if (buffer->type == PAL_BufferTypes_Uniform) {
        if (context->state.activeUniformBuffer == buffer) {
            context->state.activeUniformBuffer = nullptr;
        }
    }

    context->api.destroyBuffer(buffer->handle);
    delete buffer;
    buffer = nullptr;
}

void PAL_BindBuffer(PAL_Buffer* buffer)
{
    PAL_ASSERT(buffer, "buffer is null");
    PAL_ASSERT(s_ActiveContext, "no active context");
    PAL_Context* context = s_ActiveContext;

    if (buffer->type == PAL_BufferTypes_Vertex) {
        if (context->state.activeVertexBuffer != buffer) {
            context->state.activeVertexBuffer = buffer;
            context->api.bindBuffer(buffer->handle);
        }
    }

    else if (buffer->type == PAL_BufferTypes_Index) {
        if (context->state.activeIndexBuffer != buffer) {
            context->state.activeIndexBuffer = buffer;
            context->api.bindBuffer(buffer->handle);
        }
    }

    else if (buffer->type == PAL_BufferTypes_Storage) {
        if (context->state.activeStorageBuffer != buffer) {
            context->state.activeStorageBuffer = buffer;
            context->api.bindBuffer(buffer->handle);
        }
    }

    else if (buffer->type == PAL_BufferTypes_Uniform) {
        if (context->state.activeUniformBuffer != buffer) {
            context->state.activeUniformBuffer = buffer;
            context->api.bindBuffer(buffer->handle);
        }
    }
}

void PAL_SetBufferData(u32 type, void* data, u32 size)
{
    PAL_ASSERT(s_ActiveContext, "no active context");
    PAL_Context* context = s_ActiveContext;

    if (type == PAL_BufferTypes_Vertex) {
        PAL_ASSERT(context->state.activeVertexBuffer, "no vertex buffer bound");
        context->api.setBufferData(context->state.activeVertexBuffer->handle, data, size);
    }

    else if (type == PAL_BufferTypes_Index) {
        PAL_ASSERT(context->state.activeIndexBuffer, "no index buffer bound");
        context->api.setBufferData(context->state.activeIndexBuffer->handle, data, size);
    }

    else if (type == PAL_BufferTypes_Storage) {
        PAL_ASSERT(context->state.activeStorageBuffer, "no Storage buffer bound");
        context->api.setBufferData(context->state.activeStorageBuffer->handle, data, size);
    }

    else if (type == PAL_BufferTypes_Uniform) {
        PAL_ASSERT(context->state.activeUniformBuffer, "no Uniform buffer bound");
        context->api.setBufferData(context->state.activeUniformBuffer->handle, data, size);
    }
}