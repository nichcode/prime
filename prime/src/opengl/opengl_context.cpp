
#include "pch.h"
#include "opengl_context.h"
#include "opengl_funcs.h"

#ifdef PRIME_PLATFORM_WINDOWS
#include "windows/wgl_context.h"
#endif // PRIME_PLATFORM_WINDOWS

struct gl_context
{
    u32 vao = 0;
#ifdef PRIME_PLATFORM_WINDOWS
    HWND window;
    HGLRC handle;
    HDC deviceContext;
#endif // PRIME_PLATFORM_WINDOWS
};

void* gl_CreateContext(void* window_handle)
{
    gl_context* context = new gl_context();
#ifdef PRIME_PLATFORM_WINDOWS
    context->window = (HWND)window_handle;
    context->handle = wgl_CreateContext(context->window);
    context->deviceContext = GetDC(context->window);
#endif // PRIME_PLATFORM_WINDOWS

    PRIME_ASSERT_MSG(context->handle, "failed to create context handle");

    glGenVertexArrays(1, &context->vao);
    glBindVertexArray(context->vao);
    return context;
}

void gl_DestroyContext(void* handle)
{
    gl_context* context = (gl_context*)handle;
#ifdef PRIME_PLATFORM_WINDOWS
    wgl_DestroyContext(context->handle);
    ReleaseDC(context->window, context->deviceContext);
#endif // PRIME_PLATFORM_WINDOWS

    glDeleteVertexArrays(1, &context->vao);
    delete context;
    context = nullptr;
}

void gl_SwapBuffers(void* handle)
{
    gl_context* context = (gl_context*)handle;
#ifdef PRIME_PLATFORM_WINDOWS
    SwapBuffers(context->deviceContext);
#endif // PRIME_PLATFORM_WINDOWS
}

void gl_Clear(void* handle)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void gl_MakeActive(void* handle)
{
    gl_context* context = (gl_context*)handle;
#ifdef PRIME_PLATFORM_WINDOWS
    wgl_MakeActive(context->deviceContext, context->handle);
#endif // PRIME_PLATFORM_WINDOWS
}

void gl_SetVsync(void* handle, b8 vsync)
{
    gl_context* context = (gl_context*)handle;
#ifdef PRIME_PLATFORM_WINDOWS
    wgl_SetSetVsync(vsync);
#endif // PRIME_PLATFORM_WINDOWS
}

void gl_SetClearColor(void* handle, prime_vec4 color)
{
    glClearColor(color.x, color.y, color.z, color.w);
}