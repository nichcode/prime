
#include "pch.h"
#include "prime/context.h"
#include "prime/window.h"

#include "opengl/opengl_context.h"

struct prAPI
{
    // context
    void*(*createContext)(void* window_handle, i32 major, i32 minor) = nullptr;
    void(*destroyContext)(void* handle) = nullptr;
    void(*swapBuffers)(void* handle) = nullptr;
    void(*setVsync)(void* handle, b8 vsync) = nullptr;
    void(*makeActive)(void* handle) = nullptr;
    void(*clear)(void* handle) = nullptr;
    void(*setClearColor)(void* handle, f32 r, f32 g, f32 b, f32 a) = nullptr;
};

struct prContext
{
    prAPI api;
    prWindow* window;
    void* handle;
};

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
            break;
        }
    }
}

prContext* prCreateContext(prWindow* window, prContextDesc desc)
{
    PR_ASSERT(window, "window is nullptr");
    PR_ASSERT(!_WindowHasContext(window), "window already has context");

    prContext* context = new prContext();
    PR_ASSERT(context, "failed to create context");
    _InitAPI(context, desc.type);

    context->handle = context->api.createContext(prGetWindowHandle(window), desc.major, desc.minor);
    PR_ASSERT(context, "failed to create context");

    _SetWindowContext(window, context);
    return context;
}

void prDestroyContext(prContext* context)
{
    PR_ASSERT(context, "context is null");
    if (s_State.activeContext == context) {
        s_State.activeContext = nullptr;
    }
    context->api.destroyContext(context->handle);
    delete context;
    context = nullptr;
}

void prSwapBuffers()
{
    PR_ASSERT(s_State.activeContext, "no context bound");
    s_State.activeContext->api.swapBuffers(s_State.activeContext->handle);
}

void prClear()
{
    PR_ASSERT(s_State.activeContext, "no context bound");
    s_State.activeContext->api.clear(s_State.activeContext->handle);
}

void prMakeActive(prContext* context)
{
    PR_ASSERT(context, "context is null");
    s_State.activeContext = context;
    context->api.makeActive(context->handle);
}

void prSetVsync(b8 vsync)
{
    PR_ASSERT(s_State.activeContext, "no context bound");
    s_State.activeContext->api.setVsync(s_State.activeContext->handle, vsync);
}

void prSetClearColor(f32 r, f32 g, f32 b, f32 a)
{
    PR_ASSERT(s_State.activeContext, "no context bound");
    s_State.activeContext->api.setClearColor(s_State.activeContext->handle, r, g, b, a);
}