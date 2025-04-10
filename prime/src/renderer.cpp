
#include "pch.h"
#include "prime/renderer.h"
#include "prime/buffer.h"
#include "prime/shader.h"
#include "prime/context.h"

#define MAX_SPRITES 10000
#define MAX_VERTICES MAX_SPRITES * 4
#define MAX_INDICES MAX_SPRITES * 6

prRenderer* prCreateRenderer(prContext* context, b8 use_ndc)
{
    PR_ASSERT(context, "context is null");
    prRenderer* renderer = new prRenderer();
    PR_ASSERT(renderer, "failed to create renderer");

    renderer->context = context;
    renderer->useNdc = use_ndc;

    if (use_ndc) {
        renderer->vertices[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
        renderer->vertices[1] = {  0.5f, -0.5f, 0.0f, 1.0f };
        renderer->vertices[2] = {  0.5f,  0.5f, 0.0f, 1.0f };
        renderer->vertices[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
    }
    else {
        renderer->vertices[0] = { 0.0f, 0.0f, 0.0f, 1.0f };
        renderer->vertices[1] = { 1.0f, 0.0f, 0.0f, 1.0f };
        renderer->vertices[2] = { 1.0f, 1.0f, 0.0f, 1.0f };
        renderer->vertices[3] = { 0.0f, 1.0f, 0.0f, 1.0f };
    }

    u32* indices = new u32[MAX_INDICES];
    u32 offset = 0;
    for (u32 i = 0; i < MAX_INDICES; i += 6)
    {
        indices[i + 0] = offset + 0;
        indices[i + 1] = offset + 1;
        indices[i + 2] = offset + 2;

        indices[i + 3] = offset + 2;
        indices[i + 4] = offset + 3;
        indices[i + 5] = offset + 0;

        offset += 4;
    }

    prShaderLayout layout;
    prShaderAttrib position_attrib;
    prShaderAttrib color_attrib;
    position_attrib.type = prShaderDataTypes_Float3;
    color_attrib.type = prShaderDataTypes_Float4;
    layout.attribs[0] = position_attrib;
    layout.attribs[1] = color_attrib;
    layout.count = 2;

    prBufferDesc buffer_desc;
    buffer_desc.type = prBufferTypes_Vertex;
    buffer_desc.data = nullptr;
    buffer_desc.size = sizeof(prVertex) * MAX_VERTICES;
    buffer_desc.usage = prBufferUsages_Dynamic;
    renderer->vbo = prCreateBuffer(context, buffer_desc);

    buffer_desc.type = prBufferTypes_Index;
    buffer_desc.data = indices;
    buffer_desc.size = sizeof(u32) * MAX_INDICES;
    buffer_desc.usage = prBufferUsages_Static;
    renderer->ibo = prCreateBuffer(context, buffer_desc);

    prShaderDesc shader_desc;
    shader_desc.load = true;
    shader_desc.type = prShaderSourceTypes_GLSL;
    shader_desc.vertex_src = "shaders/renderer_vertex.glsl";
    shader_desc.pixel_src = "shaders/renderer_pixel.glsl";
    shader_desc.layout = layout;
    renderer->shader = prCreateShader(context, shader_desc);

    prBindBuffer(renderer->vbo);
    prBindBuffer(renderer->ibo);
    prBindShader(renderer->shader);

    delete[] indices;
    return renderer;
}

void prDestroyRenderer(prRenderer* renderer)
{
    PR_ASSERT(renderer, "renderer is null");
    prDestroyBuffer(renderer->vbo);
    prDestroyBuffer(renderer->ibo);
    prDestroyShader(renderer->shader);
    renderer->sprites.clear();

    delete renderer;
    renderer = nullptr;
}

void prDrawRect(prRenderer* renderer, const prRect rect)
{
    PR_ASSERT(renderer, "renderer is null");

    prMat4 transform = prTranslate({ rect.x, rect.y, 0.0f }) 
        * prScale({ rect.w, rect.h, 1.0f });

    for (size_t i = 0; i < 4; i++) {
        prVec4 position = transform * renderer->vertices[i];
        prVertex sprite;
        sprite.position.x = position.x;
        sprite.position.y = position.y;
        sprite.position.z = 0.0f;

        sprite.color = { 1.0f, 0.0f, 0.0f, 1.0f };
        renderer->sprites.push_back(sprite);
    }
    renderer->count += 6;
}

void prFlush(prRenderer* renderer)
{
    PR_ASSERT(renderer, "renderer is null");
    if (renderer->count) {
        u32 size = sizeof(prVertex) * renderer->count;
        prSetBufferData(prBufferTypes_Vertex, renderer->sprites.data(), size);
        
        prDrawElements(prDrawModes_Triangles, renderer->count);
        renderer->sprites.clear();
        renderer->count = 0;
    }
}