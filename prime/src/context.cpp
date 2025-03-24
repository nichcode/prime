
#include "prime/context.h"
#include "pch.h"
#include "utils.h"

#include "opengl/opengl_context.h"

struct prime_context
{
    void* handle = nullptr;

    void(*destroy_func)(void* handle) = nullptr;
    void(*present_func)(void* handle) = nullptr;
    void(*make_func)(void* handle) = nullptr;
    void(*clear_func)(void* handle) = nullptr;
    void(*vsync_func)(void* handle, b8 vsync) = nullptr;
    void(*color_func)(void* handle, f32 r, f32 g, f32 b, f32 a) = nullptr;
};

prime_context* prime_create_context(prime_window* window)
{
    switch (s_init_data.type) {
        case PRIME_DEVICE_TYPE_OPENGL: {
            prime_context* context = new prime_context();
            context->handle = gl_create_context(window);
            context->clear_func = gl_context_clear;
            context->destroy_func = gl_destroy_context;
            context->make_func = gl_context_make_active;
            context->present_func = gl_context_present;
            context->vsync_func = gl_context_set_vsync;
            context->color_func = gl_context_set_clearcolor;
            return context;
            break;
        }
    } // switch
    PRIME_ASSERT_MSG(false, "invalid device type");
    return nullptr;
}

void prime_destroy_context(prime_context* context)
{
    PRIME_ASSERT_MSG(context, "context is null");
    context->destroy_func(context->handle);
}

void prime_context_clear(prime_context* context)
{
    PRIME_ASSERT_MSG(context, "context is null");
    context->clear_func(context->handle);
}

void prime_context_present(prime_context* context)
{
    PRIME_ASSERT_MSG(context, "context is null");
    context->present_func(context->handle);
}

void prime_context_set_vsync(prime_context* context, b8 vsync)
{
    PRIME_ASSERT_MSG(context, "context is null");
    context->vsync_func(context->handle, vsync);
}

void prime_context_set_clearcolor(prime_context* context, f32 r, f32 g, f32 b, f32 a)
{
    PRIME_ASSERT_MSG(context, "context is null");
    context->color_func(context->handle, r, g, b, a);
}

void prime_context_set_clearcolori(prime_context* context, u32 r, u32 g, u32 b, u32 a)
{
    PRIME_ASSERT_MSG(context, "context is null");
    f32 fr = (f32)r / 255.0f;
    f32 fg = (f32)g / 255.0f;
    f32 fb = (f32)b / 255.0f;
    f32 fa = (f32)a / 255.0f;
    context->color_func(context->handle, fr, fg, fb, fa);
}

