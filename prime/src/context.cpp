
#include "prime/context.h"
#include "pch.h"
#include "utils.h"

#include "opengl/opengl_context.h"

struct prime_buffer
{
    prime_context* context = nullptr;
    void* handle = nullptr;
    prime_buffer_type type;
    prime_buffer_usage usage;
};

struct prime_context
{
    void* handle = nullptr;
    prime_view view;

    void(*destroy_func)(void* handle) = nullptr;
    void(*present_func)(void* handle) = nullptr;
    void(*make_func)(void* handle) = nullptr;
    void(*clear_func)(void* handle) = nullptr;
    void(*vsync_func)(void* handle, b8 vsync) = nullptr;
    void(*color_func)(void* handle, f32 r, f32 g, f32 b, f32 a) = nullptr;
    void(*view_func)(void* handle, prime_view* view) = nullptr;

    // buffer
    void*(*create_buffer_func)(prime_buffer_desc desc) = nullptr;
    void(*destroy_buffer_func)(void* handle) = nullptr;
    void(*set_buffer_func)(void* handle) = nullptr;
    void(*set_buffer_data_func)(void* handle, const void* data, u32 size) = nullptr;
};

prime_context* prime_create_context(prime_window* window)
{
    prime_context* context = new prime_context();
    context->view.size = *prime_get_window_size(window);

    switch (s_init_data.type) {
        case PRIME_DEVICE_TYPE_OPENGL: {
            context->handle = gl_create_context(window);
            context->clear_func = gl_context_clear;
            context->destroy_func = gl_destroy_context;
            context->make_func = gl_context_make_active;
            context->present_func = gl_context_present;
            context->vsync_func = gl_context_set_vsync;
            context->color_func = gl_context_set_clearcolor;

            // buffer
            context->create_buffer_func = gl_create_buffer;
            context->destroy_buffer_func = gl_destroy_buffer;
            context->set_buffer_func = gl_set_buffer;
            context->set_buffer_data_func = gl_set_buffer_data;

            return context;
            break;
        }
    } // switch

    return context;
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

void prime_context_set_clearcolor(prime_context* context, const prime_vec4 color)
{
    PRIME_ASSERT_MSG(context, "context is null");
    context->color_func(context->handle, color.x, color.y, color.z, color.w);
}

void prime_context_set_clearcolori(prime_context* context, const prime_uvec4 color)
{
    PRIME_ASSERT_MSG(context, "context is null");
    f32 fr = (f32)color.x / 255.0f;
    f32 fg = (f32)color.y / 255.0f;
    f32 fb = (f32)color.z / 255.0f;
    f32 fa = (f32)color.w / 255.0f;
    context->color_func(context->handle, fr, fg, fb, fa);
}

void prime_context_setview(prime_context* context, const prime_view view)
{
    PRIME_ASSERT_MSG(context, "context is null");
    context->view =  view;
    context->view_func(context->handle, &context->view);
}

const prime_view* prime_context_getview(prime_context* context)
{
    PRIME_ASSERT_MSG(context, "context is null");
    return &context->view;
}

prime_buffer* prime_create_buffer(prime_context* context, prime_buffer_desc desc)
{
    PRIME_ASSERT_MSG(context, "context is null");
    prime_buffer* buffer = new prime_buffer();
    buffer->type = desc.type;
    buffer->usage = desc.usage;
    buffer->context = context;
    buffer->handle = context->create_buffer_func(desc);
    return buffer;
}

void prime_destroy_buffer(prime_buffer* buffer)
{
    PRIME_ASSERT_MSG(buffer, "buffer is null");
    buffer->context->destroy_buffer_func(buffer->handle);
    delete buffer;
    buffer = nullptr;
}

void prime_set_buffer(prime_buffer* buffer)
{
    PRIME_ASSERT_MSG(buffer, "buffer is null");
    buffer->context->set_buffer_func(buffer->handle);
}

void prime_set_buffer_data(prime_buffer* buffer, const void* data, u32 size)
{
    PRIME_ASSERT_MSG(buffer, "buffer is null");
    if (buffer->usage == PRIME_BUFFER_USAGE_DYNAMIC) {
        buffer->context->set_buffer_data_func(buffer->handle, data, size);
    }
}