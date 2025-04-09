
#include "pch.h"
#include "opengl_context.h"
#include "opengl_funcs.h"

#ifdef PR_PLATFORM_WINDOWS
#include "win32/wgl_context.h"
#endif // PR_PLATFORM_WINDOWS

struct glContext
{
    u32 vao = 0;
#ifdef PR_PLATFORM_WINDOWS
    HWND window;
    HGLRC handle;
    HDC deviceContext;
#endif // PR_PLATFORM_WINDOWS
};

void* _GLCreateContext(void* window_handle, i32 major, i32 minor)
{
    glContext* context = new glContext();
    PR_ASSERT(context, "failed to create opengl context handle");

#ifdef PR_PLATFORM_WINDOWS
    context->window = (HWND)window_handle;
    context->handle = _WGLCreateContext(context->window, major, minor);
    context->deviceContext = GetDC(context->window);
#endif // PR_PLATFORM_WINDOWS

    PR_ASSERT(context->handle, "failed to create opengl context handle");
    glGenVertexArrays(1, &context->vao);
    glBindVertexArray(context->vao);
    return context;
}

void _GLDestroyContext(void* handle)
{
    glContext* context = (glContext*)handle;
#ifdef PR_PLATFORM_WINDOWS
    s_WGLDeleteContext(context->handle);
    ReleaseDC(context->window, context->deviceContext);
#endif // PR_PLATFORM_WINDOWS

    glDeleteVertexArrays(1, &context->vao);
    delete context;
    context = nullptr;
}

void _GLSwapBuffers(void* handle)
{
    glContext* context = (glContext*)handle;
#ifdef PR_PLATFORM_WINDOWS
    s_SwapBuffers(context->deviceContext);
#endif // PR_PLATFORM_WINDOWS
}

void _GLMakeActive(void* handle)
{
    glContext* context = (glContext*)handle;
#ifdef PR_PLATFORM_WINDOWS
    s_WGLMakeCurrent(context->deviceContext, context->handle);
#endif // PR_PLATFORM_WINDOWS
}

void _GLSetVsync(void* handle, b8 vsync)
{
    glContext* context = (glContext*)handle;
#ifdef PR_PLATFORM_WINDOWS
    s_WGLSwapIntervalEXT(vsync);
#endif // PR_PLATFORM_WINDOWS
}

void _GLSetClearColor(void* handle, f32 r, f32 g, f32 b, f32 a)
{
    glClearColor(r, g, b, a);
}

void _GLClear(void* handle)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}