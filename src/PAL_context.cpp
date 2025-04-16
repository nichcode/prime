
#include "PAL_pch.h"
#include "PAL/PAL_context.h"
#include "PAL/PAL_window.h"

#include "opengl/PAL_gl_context.h"
#include "opengl/PAL_gl_buffer.h"
#include "opengl/PAL_gl_shader.h"
#include "opengl/PAL_gl_texture.h"

void _InitAPI(PAL_Context* context, u32 type)
{
    switch (type) {
        case PAL_ContextTypes_OpenGL: {
            // context
            context->api.createContext = _GLCreateContext;
            context->api.clear = _GLClear;
            context->api.destroyContext = _GLDestroyContext;
            context->api.makeActive = _GLMakeActive;
            context->api.swapBuffers = _GLSwapBuffers;
            context->api.setVsync = _GLSetVsync;
            context->api.drawArrays = _GLDrawArrays;
            context->api.drawElements = _GLDrawElements;
            context->api.drawArraysInstanced = _GLDrawArraysInstanced;
            context->api.drawElementsInstanced = _GLDrawElementsInstanced;
            context->api.setView = _GLSetView;
            context->api.setBlend = _GLSetBlendMode;

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

            // texture
            context->api.createTexture = _GLCreateTexture;
            context->api.loadTexture = _GLLoadTexture;
            context->api.bindTexture = _GLBindTexture;
            context->api.destroyTexture = _GLDestroyTexture;
            context->api.bindTarget = _GLBindRenderTarget;
            context->api.unbindTarget = _GLUnbindRenderTarget;

            break;
        }
    }
}

void _ShutdownAPI(PAL_Context* context)
{
    // context
    context->api.createContext = nullptr;
    context->api.clear = nullptr;
    context->api.destroyContext = nullptr;
    context->api.makeActive = nullptr;
    context->api.swapBuffers = nullptr;
    context->api.setVsync = nullptr;
    context->api.drawArrays = nullptr;
    context->api.drawElements = nullptr;
    context->api.drawArraysInstanced = nullptr;
    context->api.drawElementsInstanced = nullptr;
    context->api.setView = nullptr;
    context->api.setBlend = nullptr;

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

    // texture
    context->api.createTexture = nullptr;
    context->api.loadTexture = nullptr;
    context->api.bindTexture = nullptr;
    context->api.destroyTexture = nullptr;
    context->api.bindTarget = nullptr;
    context->api.unbindTarget = nullptr;
}

PAL_Context* PAL_CreateContext(PAL_Window* window, PAL_ContextDesc desc)
{
    PAL_ASSERT(window, "window is nullptr");
    PAL_ASSERT(!window->context, "window already has context");

    PAL_Context* context = new PAL_Context();
    PAL_ASSERT(context, "failed to create context");
    _InitAPI(context, desc.type);

    context->handle = context->api.createContext(PAL_GetWindowHandle(window), desc.major, desc.minor);
    PAL_ASSERT(context, "failed to create context");

    window->context = context;
    context->view.x = 0.0f;
    context->view.y = 0.0f;
    context->view.width = (f32)window->width;
    context->view.height = (f32)window->height;
    return context;
}

void PAL_DestroyContext(PAL_Context* context)
{
    PAL_ASSERT(context, "context is null");
    if (s_ActiveContext == context) {
        s_ActiveContext = nullptr;
    }
    
    // buffers
    for (PAL_Buffer* buffer : context->data.buffers) {
        context->api.destroyBuffer(buffer->handle);
        delete buffer;
        buffer = nullptr;
    }

    // shaders
    for (PAL_Shader* shader : context->data.shaders) {
        context->api.destroyShader(shader->handle);
        delete shader;
        shader = nullptr;
    }

    // textures
    for (PAL_Texture* texture : context->data.textures) {
        context->api.destroyShader(texture->handle);
        delete texture;
        texture = nullptr;
    }

    // fonts
    for (PAL_Font* font : context->data.fonts) {
        font->glyphs.clear();
        delete font;
        font = nullptr;
    }

    context->data.buffers.clear();
    context->data.shaders.clear();
    context->data.textures.clear();
    context->data.fonts.clear();

    // reset states
    context->state.activeVertexBuffer = nullptr;
    context->state.activeIndexBuffer = nullptr;
    context->state.activeStorageBuffer = nullptr;
    context->state.activeUniformBuffer = nullptr;
    context->state.activeShader = nullptr;
    context->state.activeTexture = nullptr;
    context->state.activeTarget = nullptr;

    context->api.destroyContext(context->handle);
    _ShutdownAPI(context);
    delete context;
    context = nullptr;
}

void PAL_SwapBuffers()
{
    PAL_ASSERT(s_ActiveContext, "no context bound");
    s_ActiveContext->api.swapBuffers(s_ActiveContext->handle);
}

void PAL_Clear(const PAL_Color color)
{
    PAL_ASSERT(s_ActiveContext, "no context bound");
    s_ActiveContext->api.clear(s_ActiveContext->handle, color);
}

void PAL_MakeActive(PAL_Context* context)
{
    PAL_ASSERT(context, "context is null");
    if (s_ActiveContext != context) {
        s_ActiveContext = context;
        context->api.makeActive(context->handle);
    }
}

void PAL_SetVsync(b8 vsync)
{
    PAL_ASSERT(s_ActiveContext, "no context bound");
    s_ActiveContext->api.setVsync(s_ActiveContext->handle, vsync);
}

void PAL_SetViewport(PAL_Viewport viewport)
{
    PAL_ASSERT(s_ActiveContext, "no context bound");
    s_ActiveContext->view = viewport;
    s_ActiveContext->api.setView(s_ActiveContext->handle, viewport);
}

void PAL_SetBlendMode(u32 blend_mode)
{
    PAL_ASSERT(s_ActiveContext, "no context bound");
    s_ActiveContext->api.setBlend(s_ActiveContext->handle, blend_mode);
}

void PAL_DrawArrays(u32 mode, u32 count)
{
    PAL_ASSERT(s_ActiveContext, "no context bound");
    s_ActiveContext->api.drawArrays(s_ActiveContext->handle, mode, count);
}

void PAL_DrawElements(u32 mode, u32 count)
{
    PAL_ASSERT(s_ActiveContext, "no context bound");
    s_ActiveContext->api.drawElements(s_ActiveContext->handle, mode, count);
}

void PAL_DrawElementsInstanced(u32 mode, u32 count, u32 instance_count)
{
    PAL_ASSERT(s_ActiveContext, "no context bound");
    s_ActiveContext->api.drawElementsInstanced(s_ActiveContext->handle, mode, count, instance_count);
}

void PAL_DrawArraysInstanced(u32 mode, u32 count, u32 instance_count)
{
    PAL_ASSERT(s_ActiveContext, "no context bound");
    s_ActiveContext->api.drawArraysInstanced(s_ActiveContext->handle, mode, count, instance_count);
}

PAL_Viewport PAL_GetView()
{
    PAL_ASSERT(s_ActiveContext, "no context bound");
    return s_ActiveContext->view;
}