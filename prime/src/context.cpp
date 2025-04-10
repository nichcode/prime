
#include "pch.h"
#include "prime/context.h"
#include "prime/window.h"

#include "opengl/opengl_context.h"
#include "opengl/opengl_buffer.h"

void _InitAPI(prContext* context, u32 type)
{
    switch (type) {
        case prContextTypes_OpenGL: {
            // context
            context->api.createContext = _GLCreateContext;
            context->api.clear = _GLClear;
            context->api.destroyContext = _GLDestroyContext;
            context->api.makeActive = _GLMakeActive;
            context->api.swapBuffers = _GLSwapBuffers;
            context->api.setVsync = _GLSetVsync;
            context->api.setClearColor = _GLSetClearColor;

            // buffer
            context->api.createBuffer = _GLCreateBuffer;
            context->api.destroyBuffer = _GLDestroyBuffer;
            context->api.bindBuffer = _GLBindBuffer;
            context->api.setBufferData = _GLSetBufferData;

            break;
        }
    }
}

prContext* prCreateContext(prWindow* window, prContextDesc desc)
{
    PR_ASSERT(window, "window is nullptr");
    PR_ASSERT(!window->context, "window already has context");

    prContext* context = new prContext();
    PR_ASSERT(context, "failed to create context");
    _InitAPI(context, desc.type);

    context->handle = context->api.createContext(prGetWindowHandle(window), desc.major, desc.minor);
    PR_ASSERT(context, "failed to create context");

    window->context = context;
    return context;
}

void prDestroyContext(prContext* context)
{
    PR_ASSERT(context, "context is null");
    if (s_ActiveContext == context) {
        s_ActiveContext = nullptr;
    }
    
    // buffers
    for (prBuffer* buffer : context->data.buffers) {
        context->api.destroyBuffer(buffer->handle);
        delete buffer;
        buffer = nullptr;
    }

    context->data.buffers.clear();

    // reset states
    context->state.activeVertexBuffer = nullptr;
    context->state.activeIndexBuffer = nullptr;
    context->state.activeStorageBuffer = nullptr;
    context->state.activeUniformBuffer = nullptr;

    context->api.destroyContext(context->handle);
    delete context;
    context = nullptr;
}

void prSwapBuffers()
{
    PR_ASSERT(s_ActiveContext, "no context bound");
    s_ActiveContext->api.swapBuffers(s_ActiveContext->handle);
}

void prClear()
{
    PR_ASSERT(s_ActiveContext, "no context bound");
    s_ActiveContext->api.clear(s_ActiveContext->handle);
}

void prMakeActive(prContext* context, b8 bind_pipeline)
{
    PR_ASSERT(context, "context is null");
    s_ActiveContext = context;
    context->api.makeActive(context->handle);
    if (bind_pipeline) {
        if (context->state.activeVertexBuffer) {
            context->api.bindBuffer(context->state.activeVertexBuffer->handle, false);
        }

        if (context->state.activeIndexBuffer) {
            context->api.bindBuffer(context->state.activeIndexBuffer->handle, false);
        }

        if (context->state.activeStorageBuffer) {
            context->api.bindBuffer(context->state.activeStorageBuffer->handle, false);
        }

        if (context->state.activeUniformBuffer) {
            context->api.bindBuffer(context->state.activeUniformBuffer->handle, false);
        }
    }
}

void prSetVsync(b8 vsync)
{
    PR_ASSERT(s_ActiveContext, "no context bound");
    s_ActiveContext->api.setVsync(s_ActiveContext->handle, vsync);
}

void prSetClearColor(f32 r, f32 g, f32 b, f32 a)
{
    PR_ASSERT(s_ActiveContext, "no context bound");
    s_ActiveContext->api.setClearColor(s_ActiveContext->handle, r, g, b, a);
}