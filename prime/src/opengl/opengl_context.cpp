
#include "opengl_context.h"
#include "pch.h"
#include "opengl/opengl_funcs.h"
#include "prime/window.h"

#ifdef PRIME_PLATFORM_WINDOWS

#include "win32/wgl_context.h"

struct gl_buffer
{
    u32 id = 0;
    u32 type;
    u32 usage;
};

struct gl_context
{
    HWND window_handle;
    HGLRC handle;
    HDC device_context;
    u32 vao = 0;
};

PRIME_INLINE u32 bufferTypeToGL(prime_buffer_type type)
{
    switch (type) {
        case PRIME_BUFFER_TYPE_VERTEX: {
            return GL_ARRAY_BUFFER;
            break;
        }
        case PRIME_BUFFER_TYPE_INDEX: {
            GL_ELEMENT_ARRAY_BUFFER;  
            break;
        }
        case PRIME_BUFFER_TYPE_UNIFORM: {
            return GL_UNIFORM_BUFFER;
            break;
        }
        case PRIME_BUFFER_TYPE_STORAGE: {
            return GL_SHADER_STORAGE_BUFFER;
            break;
        }
    } // switch
    PRIME_ASSERT_MSG(false, "invalid buffer type");
    return 0;
}

PRIME_INLINE u32 bufferUsageToGL(prime_buffer_usage usage)
{
    switch (usage) {
        case PRIME_BUFFER_USAGE_STATIC: {
            return GL_STATIC_DRAW;
            break;
        }
        case PRIME_BUFFER_USAGE_DYNAMIC: {
            return GL_DYNAMIC_DRAW;  
            break;
        }
    } // switch
    PRIME_ASSERT_MSG(false, "invalid buffer usage");
    return 0;
}

void* gl_create_context(prime_window* window)
{
    gl_context* gl_con = new gl_context();
    gl_con->window_handle = (HWND)prime_get_window_handle(window);
    gl_con->handle = createWGLContext(gl_con->window_handle);
    gl_con->device_context = GetDC(gl_con->window_handle);

    glGenVertexArrays(1, &gl_con->vao);
    glBindVertexArray(gl_con->vao);
    return gl_con;
}

void gl_destroy_context(void* context)
{
    gl_context* gl_con = (gl_context*)context;
    destroyWGLContext(gl_con->handle);
    ReleaseDC(gl_con->window_handle, gl_con->device_context);
    glDeleteVertexArrays(1, &gl_con->vao);
    gl_con->window_handle = 0;
    gl_con->handle = 0;
    gl_con->device_context = 0;
    
    delete gl_con;
    context = nullptr;
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

void* gl_create_buffer(prime_buffer_desc desc)
{
    gl_buffer* buffer = new gl_buffer();
    buffer->type = bufferTypeToGL(desc.type);
    buffer->usage = bufferUsageToGL(desc.usage);
    glGenBuffers(1, &buffer->id);
    switch (desc.type) {
        case PRIME_BUFFER_TYPE_VERTEX: {
            glBindBuffer(GL_ARRAY_BUFFER, buffer->id);
            glBufferData(GL_ARRAY_BUFFER, desc.size, desc.data, buffer->usage);
            break;
        }

        case PRIME_BUFFER_TYPE_INDEX: {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->id);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, desc.size, desc.data, buffer->usage);
            break;
        }

        case PRIME_BUFFER_TYPE_UNIFORM: {
            glBindBuffer(GL_UNIFORM_BUFFER, buffer->id);
            glBufferData(GL_UNIFORM_BUFFER, desc.size, desc.data, buffer->usage);
            glBindBufferBase(GL_UNIFORM_BUFFER, 0, buffer->id);
            break;
        }

        case PRIME_BUFFER_TYPE_STORAGE: {
            glBindBuffer(GL_SHADER_STORAGE_BUFFER, buffer->id);
            glBufferData(GL_SHADER_STORAGE_BUFFER, desc.size, desc.data, buffer->usage);
            glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, buffer->id);
            break;
        }     
    } // switch

    return buffer;
}

void gl_destroy_buffer(void* buffer)
{
    gl_buffer* gl_buf = (gl_buffer*)buffer;
    glDeleteBuffers(1, &gl_buf->id);
    delete gl_buf;
    gl_buf = nullptr;
    buffer = nullptr;
}

void gl_set_buffer(void* buffer)
{
    gl_buffer* gl_buf = (gl_buffer*)buffer;
    glBindBuffer(gl_buf->type, gl_buf->id);
}

void gl_set_buffer_data(void* buffer, const void* data, u32 size)
{
    gl_buffer* gl_buf = (gl_buffer*)buffer;
    glBufferSubData(gl_buf->type, 0, size, data);
}