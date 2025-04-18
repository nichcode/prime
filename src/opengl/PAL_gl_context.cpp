
#include "PAL_pch.h"
#include "PAL_gl_context.h"
#include "PAL_gl_funcs.h"

#ifdef PAL_PLATFORM_WINDOWS
#include "win32/PAL_wgl_context.h"
#endif // PAL_PLATFORM_WINDOWS

inline GLenum drawModeToGL(u32 mode)
{
    switch (mode) {
        case PAL_DrawModes_Triangles: {
            return GL_TRIANGLES;
            break;
        }
    }
    return 0;
}

struct glContext
{
    u32 vao = 0;
#ifdef PAL_PLATFORM_WINDOWS
    HWND window;
    HGLRC handle;
    HDC deviceContext;
#endif // PAL_PLATFORM_WINDOWS
};

void* _GLCreateContext(void* window_handle, i32 major, i32 minor)
{
    glContext* context = new glContext();
    if (!context) { return nullptr; }

#ifdef PAL_PLATFORM_WINDOWS
    context->window = (HWND)window_handle;
    context->handle = _WGLCreateContext(context->window, major, minor);
    context->deviceContext = GetDC(context->window);
#endif // PAL_PLATFORM_WINDOWS

    return context;
}

void _GLDestroyContext(void* handle)
{
    glContext* context = (glContext*)handle;
#ifdef PAL_PLATFORM_WINDOWS
    wglDeleteContext(context->handle);
    ReleaseDC(context->window, context->deviceContext);
#endif // PAL_PLATFORM_WINDOWS

    glDeleteVertexArrays(1, &context->vao);
    delete context;
    context = nullptr;
}

void _GLSwapBuffers(void* handle)
{
    glContext* context = (glContext*)handle;
#ifdef PAL_PLATFORM_WINDOWS
    SwapBuffers(context->deviceContext);
#endif // PAL_PLATFORM_WINDOWS
}

void _GLMakeActive(void* handle)
{
    glContext* context = (glContext*)handle;
#ifdef PAL_PLATFORM_WINDOWS
    wglMakeCurrent(context->deviceContext, context->handle);
#endif // PAL_PLATFORM_WINDOWS

    if (!context->vao) { glGenVertexArrays(1, &context->vao); }
    glBindVertexArray(context->vao);
}

void _GLSetVsync(void* handle, b8 vsync)
{
    glContext* context = (glContext*)handle;
#ifdef PAL_PLATFORM_WINDOWS
    wglSwapIntervalEXT(vsync);
#endif // PAL_PLATFORM_WINDOWS
}

void _GLClear(void* handle, const PAL_Color color)
{
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void _GLDrawArrays(void* handle, u32 mode, u32 count)
{
    GLenum gl_mode = drawModeToGL(mode);
    glDrawArrays(gl_mode, 0, count);
}

void _GLDrawElements(void* handle, u32 mode, u32 count)
{
    GLenum gl_mode = drawModeToGL(mode);
    glDrawElements(gl_mode, count, GL_UNSIGNED_INT, nullptr);
}

void _GLDrawArraysInstanced(void* handle, u32 mode, u32 count, u32 instance_count)
{
    GLenum gl_mode = drawModeToGL(mode);
    glDrawArraysInstanced(gl_mode, 0, count, instance_count);
}

void _GLDrawElementsInstanced(void* handle, u32 mode, u32 count, u32 instance_count)
{
    GLenum gl_mode = drawModeToGL(mode);
    glDrawElementsInstanced(gl_mode, count, GL_UNSIGNED_INT, nullptr, instance_count);
}

void _GLSetView(void* handle, PAL_Viewport view)
{
    glViewport((u32)view.x, (u32)view.y, (u32)view.width, (u32)view.height);
}

void _GLSetBlendMode(void* handle, u32 blend_mode)
{
    switch (blend_mode) {
        case PAL_BlendModes_None: {
            glDisable(GL_BLEND);
            break;
        }
        case PAL_BlendModes_Alpha: {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            break;
        }
    }
}