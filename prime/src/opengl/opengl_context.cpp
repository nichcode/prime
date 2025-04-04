
#include "pch.h"
#include "opengl_context.h"
#include "opengl_funcs.h"

#ifdef PRIME_PLATFORM_WINDOWS
#include "windows/wgl_context.h"
#endif // PRIME_PLATFORM_WINDOWS

PRIME_INLINE GLenum drawModeToGL(u32 mode)
{
    switch (mode)
    {
        case PRIME_TRIANGLES:
            return GL_TRIANGLES;
            break;
    }
    return 0;
}

PRIME_INLINE u32 dataTypeSize(u32 type)
{
    switch (type)
    {
        case PRIME_INT:
        case PRIME_FLOAT: {
            return 4;
        }

        case PRIME_INT2:
        case PRIME_FLOAT2: {
            return 8;
        }

        case PRIME_INT3:
        case PRIME_FLOAT3: {
            return 12;
        }

        case PRIME_INT4:
        case PRIME_FLOAT4: {
            return 16;
        }
        case PRIME_BOOL:     return 1;
    }
    return 0;
}

PRIME_INLINE u32 dataTypeCount(u32 type)
{
    switch (type)
    {
        case PRIME_FLOAT:
        case PRIME_INT:
        case PRIME_BOOL: {
            return 1;
        }

        case PRIME_FLOAT2:
        case PRIME_INT2: {
            return 2;
        }

        case PRIME_FLOAT3:
        case PRIME_INT3: {
            return 3;
        }

        case PRIME_FLOAT4:
        case PRIME_INT4: {
            return 4;
        }
    }
    return 0;
}

PRIME_INLINE GLenum typeToGLType(u32 type)
{
    switch (type)
    {
        case PRIME_INT:
        case PRIME_INT2:
        case PRIME_INT3:
        case PRIME_INT4:
            return GL_INT;

        case PRIME_FLOAT:
        case PRIME_FLOAT2:
        case PRIME_FLOAT3:
        case PRIME_FLOAT4:
            return GL_FLOAT;

        case PRIME_BOOL:
            return GL_BOOL;
    }
    return 0;
}

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

void _glSubmitArrays(void* handle, u32 mode, u32 count)
{
    GLenum gl_mode = drawModeToGL(mode);
    glDrawArrays(gl_mode, 0, count);
}

void _glSubmitElements(void* handle, u32 mode, u32 count)
{
    GLenum gl_mode = drawModeToGL(mode);
    glDrawElements(gl_mode, count, GL_UNSIGNED_INT, nullptr);
}

void _glSubmitLayout(void* handle, prime_layout* layout)
{
    u32 stride = 0;
    u32 index = 0;
    u64 offsets[layout->count];
    for (u32 i = 0; i < layout->count; i++) {
        offsets[i] = stride;
        stride += dataTypeSize(layout->attribs[i].type);
    }

    for (u32 i = 0; i < layout->count; i++) {
        u32 count = dataTypeCount(layout->attribs[i].type);
        u32 type = typeToGLType(layout->attribs[i].type);
        u32 divisor = layout->attribs[i].divisor;
        b8 normalize = layout->attribs[i].normalize;
        const void* offset = (const void*)offsets[i];

        switch (type) {
            case GL_FLOAT: {
                glVertexAttribPointer(index, count, type, normalize, stride, offset);
                glEnableVertexAttribArray(index);
                glVertexAttribDivisor(index, divisor);
                break;
            }

            case GL_BOOL:
            case GL_INT: {
                glVertexAttribIPointer(index, count, type, stride, offset);
                glEnableVertexAttribArray(index);
                glVertexAttribDivisor(index, divisor);
                break;
            }
        }
        index++;
    }
}