
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

struct prime_shader
{
    prime_context* context = nullptr;
    void* handle = nullptr;
    prime_shader_source_type source_type = PRIME_SHADER_SOURCE_TYPE_GLSL;
};

struct prime_layout
{
    prime_context* context = nullptr;
    void* handle = nullptr;
};

struct prime_context
{
    void* handle = nullptr;
    prime_view view;

    std::vector<prime_buffer*> buffers;
    std::vector<prime_shader*> shaders;
    std::vector<prime_layout*> layouts;

    void(*destroy_func)(void* handle) = nullptr;
    void(*present_func)(void* handle) = nullptr;
    void(*make_func)(void* handle) = nullptr;
    void(*clear_func)(void* handle) = nullptr;
    void(*vsync_func)(void* handle, b8 vsync) = nullptr;
    void(*color_func)(void* handle, f32 r, f32 g, f32 b, f32 a) = nullptr;
    void(*view_func)(void* handle, prime_view* view) = nullptr;
    void(*submit_func)(void* handle, prime_draw_type type, prime_draw_mode mode, u32 count) = nullptr;

    // buffer
    void*(*create_buffer_func)(prime_buffer_desc desc) = nullptr;
    void(*destroy_buffer_func)(void* handle) = nullptr;
    void(*set_buffer_func)(void* handle) = nullptr;
    void(*set_buffer_data_func)(void* handle, const void* data, u32 size) = nullptr;

    // shader
    void*(*create_shader_func)(prime_shader_desc desc) = nullptr;
    void(*destroy_shader_func)(void* handle) = nullptr;
    void(*set_shader_func)(void* handle) = nullptr;
    void(*set_shader_int_func)(void* handle, const char* name, i32 data) = nullptr;
    void(*set_shader_int_array_func)(void* handle, const char* name, i32* data, u32 count) = nullptr;
    void(*set_shader_float_func)(void* handle, const char* name, f32 data) = nullptr;
    void(*set_shader_float2_func)(void* handle, const char* name, prime_vec2 data) = nullptr;
    void(*set_shader_float3_func)(void* handle, const char* name, prime_vec3 data) = nullptr;
    void(*set_shader_float4_func)(void* handle, const char* name, prime_vec4 data) = nullptr;
    void(*set_shader_mat2_func)(void* handle, const char* name, prime_mat2 data) = nullptr;
    void(*set_shader_mat3_func)(void* handle, const char* name, prime_mat3 data) = nullptr;
    void(*set_shader_mat4_func)(void* handle, const char* name, prime_mat4 data) = nullptr;

    // layouts
    void*(*create_layout_func)() = nullptr;
    void(*destroy_layout_func)(void* handle) = nullptr;
    void(*layout_add_func)(void* handle, prime_data_type type, u32 divisor, b8 normalize) = nullptr;
    void(*set_layout_func)(void* handle) = nullptr;
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
            context->submit_func = gl_context_submit;

            // shader
            context->create_shader_func = gl_create_shader;
            context->destroy_shader_func = gl_destroy_shader;
            context->set_shader_func = gl_set_shader;
            context->set_shader_int_func = gl_set_shader_int;
            context->set_shader_int_array_func = gl_set_shader_int_array;
            context->set_shader_float_func = gl_set_shader_float;
            context->set_shader_float2_func = gl_set_shader_float2;
            context->set_shader_float3_func = gl_set_shader_float3;
            context->set_shader_float4_func = gl_set_shader_float4;
            context->set_shader_mat2_func = gl_set_shader_mat2;
            context->set_shader_mat3_func = gl_set_shader_mat3;
            context->set_shader_mat4_func = gl_set_shader_mat4;

            // layout
            context->create_layout_func = gl_create_layout;
            context->destroy_layout_func = gl_destroy_layout;
            context->layout_add_func = gl_add_attrib;
            context->set_layout_func = gl_set_layout;

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

    // buffers
    for (prime_buffer* buffer : context->buffers) {
        context->destroy_buffer_func(buffer->handle);
        delete buffer;
        buffer = nullptr;
    }

    // shaders
    for (prime_shader* shader : context->shaders) {
        context->destroy_shader_func(shader->handle);
        delete shader;
        shader = nullptr;
    }

    // layouts
    for (prime_layout* layout : context->layouts) {
        delete layout;
        layout = nullptr;
    }

    context->buffers.clear();
    context->shaders.clear();
    context->layouts.clear();
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

void prime_context_submit(prime_context* context, prime_draw_type type, prime_draw_mode mode, u32 count)
{
    PRIME_ASSERT_MSG(context, "context is null");
    context->submit_func(context->handle, type, mode, count);
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
    context->buffers.push_back(buffer);
    return buffer;
}

void prime_destroy_buffer(prime_buffer* buffer)
{
    PRIME_ASSERT_MSG(buffer, "buffer is null");

    auto it = std::find(buffer->context->buffers.begin(), buffer->context->buffers.end(), buffer);
    if (it != buffer->context->buffers.end()) {
        buffer->context->buffers.erase(it); 
    }

    buffer->context->destroy_buffer_func(buffer->handle);
    delete buffer;
    buffer = nullptr;
}

prime_shader* prime_create_shader(prime_context* context, prime_shader_desc desc)
{
    PRIME_ASSERT_MSG(context, "context is null");
    prime_shader* shader = new prime_shader();
    shader->source_type = desc.source_type;
    shader->context = context;
    shader->handle = context->create_shader_func(desc);
    context->shaders.push_back(shader);
    return shader;
}

void prime_destroy_shader(prime_shader* shader)
{
    PRIME_ASSERT_MSG(shader, "shader is null");

    auto it = std::find(shader->context->shaders.begin(), shader->context->shaders.end(), shader);
    if (it != shader->context->shaders.end()) {
        shader->context->shaders.erase(it); 
    }

    shader->context->destroy_shader_func(shader->handle);
    delete shader;
    shader = nullptr;
}

prime_layout* prime_create_layout(prime_context* context)
{
    prime_layout* layout = new prime_layout();
    layout->context = context;
    layout->handle = context->create_layout_func();
    context->layouts.push_back(layout);
    return layout;
}

void prime_destroy_layout(prime_layout* layout)
{
    PRIME_ASSERT_MSG(layout, "layout is null");

    auto it = std::find(layout->context->layouts.begin(), layout->context->layouts.end(), layout);
    if (it != layout->context->layouts.end()) {
        layout->context->layouts.erase(it); 
    }

    delete layout;
    layout = nullptr;
}

void prime_set_buffer_data(prime_buffer* buffer, const void* data, u32 size)
{
    PRIME_ASSERT_MSG(buffer, "buffer is null");
    if (buffer->usage == PRIME_BUFFER_USAGE_DYNAMIC) {
        buffer->context->set_buffer_data_func(buffer->handle, data, size);
    }
}

void prime_add_attrib(prime_layout* layout, prime_data_type type, u32 divisor, b8 normalize)
{
    PRIME_ASSERT_MSG(layout, "layout is null");
    layout->context->layout_add_func(layout->handle, type, divisor, normalize);
}

void prime_set_shader_int(prime_shader* shader, const char* name, i32 data)
{
    PRIME_ASSERT_MSG(shader, "shader is null");
    shader->context->set_shader_int_func(shader->handle, name, data);
}

void prime_set_shader_int_array(prime_shader* shader, const char* name, i32* data, u32 count)
{
    PRIME_ASSERT_MSG(shader, "shader is null");
    shader->context->set_shader_int_array_func(shader->handle, name, data, count);
}

void prime_set_shader_float(prime_shader* shader, const char* name, f32 data)
{
    PRIME_ASSERT_MSG(shader, "shader is null");
    shader->context->set_shader_float_func(shader->handle, name, data);
}

void prime_set_shader_float2(prime_shader* shader, const char* name, prime_vec2 data)
{
    PRIME_ASSERT_MSG(shader, "shader is null");
    shader->context->set_shader_float2_func(shader->handle, name, data);
}

void prime_set_shader_float3(prime_shader* shader, const char* name, prime_vec3 data)
{
    PRIME_ASSERT_MSG(shader, "shader is null");
    shader->context->set_shader_float3_func(shader->handle, name, data);
}

void prime_set_shader_float4(prime_shader* shader, const char* name, prime_vec4 data)
{
    PRIME_ASSERT_MSG(shader, "shader is null");
    shader->context->set_shader_float4_func(shader->handle, name, data);
}

void prime_set_shader_mat2(prime_shader* shader, const char* name, prime_mat2 data)
{
    PRIME_ASSERT_MSG(shader, "shader is null");
    shader->context->set_shader_mat2_func(shader->handle, name, data);
}

void prime_set_shader_mat3(prime_shader* shader, const char* name, prime_mat3 data)
{
    PRIME_ASSERT_MSG(shader, "shader is null");
    shader->context->set_shader_mat3_func(shader->handle, name, data);
}

void prime_set_shader_mat4(prime_shader* shader, const char* name, prime_mat4 data)
{
    PRIME_ASSERT_MSG(shader, "shader is null");
    shader->context->set_shader_mat4_func(shader->handle, name, data);
}

void prime_set_buffer(prime_buffer* buffer)
{
    PRIME_ASSERT_MSG(buffer, "buffer is null");
    buffer->context->set_buffer_func(buffer->handle);
}

void prime_set_shader(prime_shader* shader)
{
    PRIME_ASSERT_MSG(shader, "shader is null");
    shader->context->set_shader_func(shader->handle);
}

void prime_set_layout(prime_layout* layout)
{
    PRIME_ASSERT_MSG(layout, "layout is null");
    layout->context->set_layout_func(layout->handle);
}