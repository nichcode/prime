
#include "pch.h"
#include "prime/prime.h"
#include "prime_sources.h"

#define MAX_INSTANCES 1000

struct InstancedData
{
    prime_vec4 color;
};

static std::vector<InstancedData> s_InstancedData;

void prime_InitSprites()
{
    prime_layout layout;
    prime_layout instanced_layout;

    prime_attrib pos_attrib;
    pos_attrib.type = PRIME_FLOAT3;
    
    prime_attrib color_attrib;
    color_attrib.type = PRIME_FLOAT4;
    color_attrib.divisor = 1;
    
    layout.attribs[0] = pos_attrib;
    layout.count = 1;

    instanced_layout.attribs[0] = color_attrib;
    instanced_layout.count = 1;

    f32* vertices_ptr = nullptr;
    if (s_Data.useNDC) {
        f32 vertices[] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.5f,  0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f
        };
        vertices_ptr = vertices;
    }

    u32 indices[] = { 0, 1, 2, 2, 3, 0 };

    prime_buffer_desc buffer_desc;
    buffer_desc.type = PRIME_VERTEX_BUFFER;
    buffer_desc.data = vertices_ptr;
    buffer_desc.size = sizeof(f32) * 12;
    buffer_desc.usage = PRIME_STATIC;
    s_RendererData.vbo = prime_create_buffer(buffer_desc);

    buffer_desc.type = PRIME_INDEX_BUFFER;
    buffer_desc.data = indices;
    buffer_desc.size = sizeof(indices);
    buffer_desc.usage = PRIME_STATIC;
    s_RendererData.ibo = prime_create_buffer(buffer_desc);

    buffer_desc.type = PRIME_VERTEX_BUFFER;
    buffer_desc.data = nullptr;
    buffer_desc.size = sizeof(InstancedData) * MAX_INSTANCES;
    buffer_desc.usage = PRIME_DYNAMIC;
    s_RendererData.instancedbo = prime_create_buffer(buffer_desc);

    prime_shader_desc shader_desc;
    shader_desc.load = false;
    shader_desc.vertex_src = s_VertexSrc;
    shader_desc.pixel_src = s_PixelSrc;
    shader_desc.type = PRIME_GLSL;
    s_RendererData.shader = prime_create_shader(shader_desc);

    prime_bind_buffer(s_RendererData.vbo);
    prime_submit_layout(&layout);

    prime_bind_buffer(s_RendererData.instancedbo);
    prime_submit_layout(&instanced_layout);

    prime_bind_buffer(s_RendererData.ibo);
    prime_bind_shader(s_RendererData.shader);
}

void prime_ShutdownSprites()
{
    prime_destroy_shader(s_RendererData.shader);
    prime_destroy_buffer(s_RendererData.vbo);
    prime_destroy_buffer(s_RendererData.ibo);
    prime_destroy_buffer(s_RendererData.instancedbo);
}

void prime_set_draw_color(prime_vec4 color)
{
    s_RendererData.drawColor = color;

}

void prime_set_draw_colori(prime_vec4i color)
{
    f32 fr = (f32)color.x / 255.0f;
    f32 fg = (f32)color.y / 255.0f;
    f32 fb = (f32)color.z / 255.0f;
    f32 fa = (f32)color.w / 255.0f;
    prime_vec4 fcolor = { fr, fg, fb, fa };
    s_RendererData.drawColor = fcolor;
}

void prime_draw_rect(prime_rect rect)
{
    InstancedData data;
    data.color = s_RendererData.drawColor;
    s_InstancedData.push_back(data);
    s_RendererData.count++;
}

void prime_flush()
{
    if (s_RendererData.count) {
        prime_bind_buffer(s_RendererData.instancedbo);
        prime_set_buffer_data(
            PRIME_VERTEX_BUFFER, 
            s_InstancedData.data(), 
            sizeof(InstancedData) * s_RendererData.count
        );

        prime_submit_elements_instanced(PRIME_TRIANGLES, 6, s_RendererData.count);
    }
}
