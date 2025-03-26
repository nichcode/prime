
#include "opengl_context.h"
#include "pch.h"
#include "opengl/opengl_funcs.h"
#include "prime/window.h"

#ifdef PRIME_PLATFORM_WINDOWS
#include "win32/wgl_context.h"
#endif // PRIME_PLATFORM_WINDOWS

PRIME_INLINE GLenum drawModeToGL(primeDrawMode mode)
{
    switch (mode)
    {
        case primeDrawModes_Triangles:
            return GL_TRIANGLES;
            break;

        case primeDrawModes_Lines:
            return GL_LINES;
            break;
    }
    return 0;
}

struct glContext
{
#ifdef PRIME_PLATFORM_WINDOWS
    HWND windowHandle;
    HGLRC handle;
    HDC deviceContext;
#endif // PRIME_PLATFORM_WINDOWS
    u32 vao = 0;
};

void* _glCreateContext(primeWindow* window)
{
    glContext* context = new glContext();

#ifdef PRIME_PLATFORM_WINDOWS
    context->windowHandle = (HWND)primeGetWindowHandle(window);
    context->handle = createWGLContext(context->windowHandle);
    context->deviceContext = GetDC(context->windowHandle);
#endif // PRIME_PLATFORM_WINDOWS
    
    glGenVertexArrays(1, &context->vao);
    glBindVertexArray(context->vao);
    return context;
}

void _glDestroyContext(void* context)
{
    glContext* gl_context = (glContext*)context;

#ifdef PRIME_PLATFORM_WINDOWS
    destroyWGLContext(gl_context->handle);
    ReleaseDC(gl_context->windowHandle, gl_context->deviceContext);
#endif // PRIME_PLATFORM_WINDOWS
   
    glDeleteVertexArrays(1, &gl_context->vao);
    gl_context->windowHandle = 0;
    gl_context->handle = 0;
    gl_context->deviceContext = 0;
    
    delete gl_context;
    context = nullptr;
    gl_context = nullptr;
}

void _glPresent(void* context)
{
    glContext* gl_context = (glContext*)context;
#ifdef PRIME_PLATFORM_WINDOWS
    SwapBuffers(gl_context->deviceContext);
#endif // PRIME_PLATFORM_WINDOWS
}

void _glBindContext(void* context)
{
    glContext* gl_context = (glContext*)context;
#ifdef PRIME_PLATFORM_WINDOWS
    bindWGLContextCurrent(gl_context->deviceContext, gl_context->handle);
#endif // PRIME_PLATFORM_WINDOWS
}

void _glUnbindContext(void* context)
{
    glContext* gl_context = (glContext*)context;
#ifdef PRIME_PLATFORM_WINDOWS
    unbindWGLContextCurrent(gl_context->deviceContext, gl_context->handle);
#endif // PRIME_PLATFORM_WINDOWS
}

void _glSetVsync(void* context, b8 vsync)
{
#ifdef PRIME_PLATFORM_WINDOWS
    setWGLContextVsync(vsync);
#endif // PRIME_PLATFORM_WINDOWS
}

void _glSubmit(void* context, primeDrawType type, primeDrawMode mode, u32 count)
{
    GLenum gl_type = drawModeToGL(mode);
    if (type == primeDrawTypes_Array) {
        glDrawArrays(gl_type, 0, count);
    }
    else if (type == primeDrawTypes_Element) {
        glDrawElements(gl_type, count, GL_UNSIGNED_INT, nullptr);
    }
}

void _glSubmitInstanced(void* context, primeDrawType type, primeDrawMode mode, u32 count, u32 ins_count)
{
    GLenum gl_type = drawModeToGL(mode);
    if (type == primeDrawTypes_Array) {
        glDrawArraysInstanced(gl_type, 0, count, ins_count);
    }
    else if (type == primeDrawTypes_Element) {
        glDrawElementsInstanced(gl_type, 6, GL_UNSIGNED_INT, nullptr, ins_count);
    }
}

void _glClear(void* context)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void _glSetClearColor(void* context, f32 r, f32 g, f32 b, f32 a)
{
    glClearColor(r, g, b, a);
}

void _glSetView(void* context, const primeView* view)
{
    glViewport(view->pos.x, view->pos.y, view->size.x, view->size.y);
}