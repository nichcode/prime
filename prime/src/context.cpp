
#include "pch.h"
#include "prime/context.h"
#include "prime/window.h"

#include "opengl/opengl_context.h"
#include "opengl/opengl_buffer.h"
#include "opengl/opengl_shader.h"

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
            context->api.drawArrays = _GLDrawArrays;
            context->api.drawElements = _GLDrawElements;
            context->api.drawArraysInstanced = _GLDrawArraysInstanced;
            context->api.drawElementsInstanced = _GLDrawElementsInstanced;
            context->api.setView = _GLSetView;

            // buffer
            context->api.createBuffer = _GLCreateBuffer;
            context->api.destroyBuffer = _GLDestroyBuffer;
            context->api.bindBuffer = _GLBindBuffer;
            context->api.setBufferData = _GLSetBufferData;

            // shader
            context->api.createShader = _GLCreateShader;
            context->api.destroyShader = _GLDestroyShader;
            context->api.bindShader = _GLBindShader;
            context->api.setInt = _GLSetInt;
            context->api.setIntArray = _GLSetIntArray;
            context->api.setFloat = _GLSetFloat;
            context->api.setFloat2 = _GLSetFloat2;
            context->api.setFloat3 = _GLSetFloat3;
            context->api.setFloat4 = _GLSetFloat4;
            context->api.setMat4 = _GLSetMat4;
            context->api.setLayout = _GLSetLayout;

            break;
        }
    }
}

void _ShutdownAPI(prContext* context)
{
    // context
    context->api.createContext = nullptr;
    context->api.clear = nullptr;
    context->api.destroyContext = nullptr;
    context->api.makeActive = nullptr;
    context->api.swapBuffers = nullptr;
    context->api.setVsync = nullptr;
    context->api.setClearColor = nullptr;
    context->api.drawArrays = nullptr;
    context->api.drawElements = nullptr;
    context->api.drawArraysInstanced = nullptr;
    context->api.drawElementsInstanced = nullptr;
    context->api.setView = nullptr;

    // buffer
    context->api.createBuffer = nullptr;
    context->api.destroyBuffer = nullptr;
    context->api.bindBuffer = nullptr;
    context->api.setBufferData = nullptr;

    // shader
    context->api.createShader = nullptr;
    context->api.destroyShader = nullptr;
    context->api.bindShader = nullptr;
    context->api.setInt = nullptr;
    context->api.setIntArray = nullptr;
    context->api.setFloat = nullptr;
    context->api.setFloat2 = nullptr;
    context->api.setFloat3 = nullptr;
    context->api.setFloat4 = nullptr;
    context->api.setMat4 = nullptr;
    context->api.setLayout = nullptr;
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
    context->view.x = 0.0f;
    context->view.y = 0.0f;
    context->view.width = (f32)window->width;
    context->view.height = (f32)window->height;
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

    // shaders
    for (prShader* shader : context->data.shaders) {
        context->api.destroyShader(shader->handle);
        delete shader;
        shader = nullptr;
    }

    context->data.buffers.clear();
    context->data.shaders.clear();

    // reset states
    context->state.activeVertexBuffer = nullptr;
    context->state.activeIndexBuffer = nullptr;
    context->state.activeStorageBuffer = nullptr;
    context->state.activeUniformBuffer = nullptr;
    context->state.activeShader = nullptr;

    context->api.destroyContext(context->handle);
    _ShutdownAPI(context);
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
    if (s_ActiveContext != context) {
        s_ActiveContext = context;
        context->api.makeActive(context->handle);
        
        if (bind_pipeline) {
            if (context->state.activeVertexBuffer) {
                context->api.bindBuffer(context->state.activeVertexBuffer->handle);
            }

            if (context->state.activeIndexBuffer) {
                context->api.bindBuffer(context->state.activeIndexBuffer->handle);
            }

            if (context->state.activeStorageBuffer) {
                context->api.bindBuffer(context->state.activeStorageBuffer->handle);
            }

            if (context->state.activeUniformBuffer) {
                context->api.bindBuffer(context->state.activeUniformBuffer->handle);
            }
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

void prSetClearColori(u8 r, u8 g, u8 b, u8 a)
{
    PR_ASSERT(s_ActiveContext, "no context bound");
    f32 fr = (f32)r / 255.0f;
    f32 fg = (f32)g / 255.0f;
    f32 fb = (f32)b / 255.0f;
    f32 fa = (f32)a / 255.0f;
    s_ActiveContext->api.setClearColor(s_ActiveContext->handle, fr, fg, fb, fa);
}

void prSetView(prViewport viewport)
{
    PR_ASSERT(s_ActiveContext, "no context bound");
    s_ActiveContext->view = viewport;
    s_ActiveContext->api.setView(s_ActiveContext->handle, viewport);
}

void prDrawArrays(u32 mode, u32 count)
{
    PR_ASSERT(s_ActiveContext, "no context bound");
    s_ActiveContext->api.drawArrays(s_ActiveContext->handle, mode, count);
}

void prDrawElements(u32 mode, u32 count)
{
    PR_ASSERT(s_ActiveContext, "no context bound");
    s_ActiveContext->api.drawElements(s_ActiveContext->handle, mode, count);
}

void prDrawElementsInstanced(u32 mode, u32 count, u32 instance_count)
{
    PR_ASSERT(s_ActiveContext, "no context bound");
    s_ActiveContext->api.drawElementsInstanced(s_ActiveContext->handle, mode, count, instance_count);
}

void prDrawArraysInstanced(u32 mode, u32 count, u32 instance_count)
{
    PR_ASSERT(s_ActiveContext, "no context bound");
    s_ActiveContext->api.drawArraysInstanced(s_ActiveContext->handle, mode, count, instance_count);
}

prViewport prGetView()
{
    PR_ASSERT(s_ActiveContext, "no context bound");
    return s_ActiveContext->view;
}