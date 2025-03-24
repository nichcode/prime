
#include "opengl_context.h"
#include "pch.h"
#include "opengl/opengl_funcs.h"
#include "prime/window.h"

#ifdef PRIME_PLATFORM_WINDOWS

#include "win32/wgl_context.h"

struct gl_context
{
    HWND window_handle;
    HGLRC handle;
    HDC device_context;
};

void* gl_create_context(prime_window* window)
{
    gl_context* gl_con = new gl_context();
    gl_con->window_handle = (HWND)prime_get_window_handle(window);
    gl_con->handle = createWGLContext(gl_con->window_handle);
    gl_con->device_context = GetDC(gl_con->window_handle);
    return gl_con;
}

void gl_destroy_context(void* context)
{
    gl_context* gl_con = (gl_context*)context;
    destroyWGLContext(gl_con->handle);
    ReleaseDC(gl_con->window_handle, gl_con->device_context);
    gl_con->window_handle = 0;
    gl_con->handle = 0;
    gl_con->device_context = 0;
    
    delete gl_con;
    gl_con = nullptr;
}

void gl_context_present(void* context)
{
    gl_context* gl_con = (gl_context*)context;
    SwapBuffers(gl_con->device_context);
}

void gl_context_make_active(void* context)
{
    gl_context* gl_con = (gl_context*)context;
    makeWGLContextCurrent(gl_con->window_handle, gl_con->handle);
}

void gl_context_set_vsync(void* context, b8 vsync)
{
    setWGLContextVsync(vsync);
}

#endif // PRIME_PLATFORM_WINDOWS

void gl_context_clear(void* context)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void gl_context_set_clearcolor(void* context, f32 r, f32 g, f32 b, f32 a)
{
    glClearColor(r, g, b, a);
}

void gl_context_set_clearcolor(void* context, const prime_view* view)
{
    glViewport(view->pos.x, view->pos.y, view->size.x, view->size.y);
}