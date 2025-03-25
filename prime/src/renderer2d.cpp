
#include "prime/renderer2d.h"
#include "pch.h"
#include "prime/context.h"
#include "shader_sources.h"

#define MAX_RENDERABLES 1000
#define MAX_VERTICES MAX_RENDERABLES * 4
#define MAX_INDICES MAX_RENDERABLES * 6

#define SPRITE_ID 0.0f
#define FONT_ID 1.0f

struct Vertex
{
    primeVec2 pos;
    primeVec4 color;
    f32 id = 0.0f;
};

struct primeRenderer2D
{
    primeContext* context = nullptr;
    primeBuffer* vbo = nullptr;
    primeBuffer* ibo = nullptr;
    primeBuffer* ubo = nullptr;
    primeShader* shader = nullptr;
    primeLayout* layout = nullptr;

    Vertex* base = nullptr;
    Vertex* ptr = nullptr;

    u32 indexCount = 0;
    primeMat4 projection;
    primeVec4 color;
};

void setProjection(primeRenderer2D* renderer, f32 x, f32 y, f32 width, f32 height)
{
    renderer->projection = primeOrtho(x, width, height, y, -1.0f, 1.0f);
}

primeRenderer2D* primeCreateRenderer2D(primeContext* context)
{
    primeRenderer2D* renderer = new primeRenderer2D();
    renderer->context = context;
    const primeView* view = primeGetView(context);
    setProjection(renderer, (f32)view->pos.x, (f32)view->pos.y, (f32)view->size.x, (f32)view->size.y);

    renderer->layout = primeCreateLayout(context);
    primeAddAttrib(renderer->layout, PRIME_DATA_TYPE_FLOAT2, 0, false);
    primeAddAttrib(renderer->layout, PRIME_DATA_TYPE_FLOAT4, 0, false);
    primeAddAttrib(renderer->layout, PRIME_DATA_TYPE_FLOAT, 0, false);

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

    primeBufferDesc buffer_desc;
    buffer_desc.data = nullptr;
    buffer_desc.size = sizeof(Vertex) * MAX_VERTICES;
    buffer_desc.type = PRIME_BUFFER_TYPE_VERTEX;
    buffer_desc.usage = PRIME_BUFFER_USAGE_DYNAMIC;
    renderer->vbo = primeCreateBuffer(context, buffer_desc);

    buffer_desc.data = indices;
    buffer_desc.size = sizeof(u32) * MAX_INDICES;
    buffer_desc.type = PRIME_BUFFER_TYPE_INDEX;
    buffer_desc.usage = PRIME_BUFFER_USAGE_STATIC;
    renderer->ibo = primeCreateBuffer(context, buffer_desc);

    buffer_desc.data = nullptr;
    buffer_desc.size = sizeof(primeMat4);
    buffer_desc.type = PRIME_BUFFER_TYPE_UNIFORM;
    buffer_desc.usage = PRIME_BUFFER_USAGE_DYNAMIC;
    renderer->ubo = primeCreateBuffer(context, buffer_desc);

    primeShaderDesc shader_desc;
    shader_desc.load = false;
    shader_desc.vertex_src = s_VertexSource;
    shader_desc.pixel_src = s_PixelSource;
    shader_desc.source_type = PRIME_SHADER_SOURCE_TYPE_GLSL;
    renderer->shader = primeCreateShader(context, shader_desc);

    primeSetLayout(renderer->layout);

    renderer->base = new Vertex[MAX_VERTICES];
    renderer->ptr = renderer->base;
    renderer->color.x = 0.0f;
    renderer->color.y = 0.0f;
    renderer->color.z = 0.0f;
    renderer->color.w = 1.0f;
    delete[] indices;
    return renderer;
}

void primeDestroyRenderer2D(primeRenderer2D* renderer)
{
    PRIME_ASSERT_MSG(renderer, "renderer is null");
    delete[] renderer->base;
    primeDestroyLayout(renderer->layout);
    primeDestroyBuffer(renderer->vbo);
    primeDestroyBuffer(renderer->ibo);
    primeDestroyBuffer(renderer->ubo);
    primeDestroyShader(renderer->shader);
    delete renderer;
    renderer = nullptr;
}

void primeDrawRect(primeRenderer2D* renderer, const primeRect rect)
{
    PRIME_ASSERT_MSG(renderer, "renderer is null");
    renderer->ptr->pos = { rect.x, rect.y };
    renderer->ptr->color = renderer->color;
    renderer->ptr->id = SPRITE_ID;
    renderer->ptr++;

    renderer->ptr->pos = { rect.x + rect.width, rect.y };
    renderer->ptr->color = renderer->color;
    renderer->ptr->id = SPRITE_ID;
    renderer->ptr++;

    renderer->ptr->pos = { rect.x + rect.width, rect.y + rect.height };
    renderer->ptr->color = renderer->color;
    renderer->ptr->id = SPRITE_ID;
    renderer->ptr++;

    renderer->ptr->pos = { rect.x, rect.y + rect.height };
    renderer->ptr->color = renderer->color;
    renderer->ptr->id = SPRITE_ID;
    renderer->ptr++;
    renderer->indexCount += 6;
}

void primeRenderer2DFlush(primeRenderer2D* renderer)
{
    PRIME_ASSERT_MSG(renderer, "renderer is null");
    if (renderer->indexCount) {
        primeSetBuffer(renderer->vbo);
        u32 size = (u32)((u8*)renderer->ptr - (u8*)renderer->base);
        primeSetData(renderer->vbo, renderer->base, size);

        primeSetBuffer(renderer->ubo);
        primeSetData(renderer->ubo, &renderer->projection, sizeof(primeMat4));

        primeSetShader(renderer->shader);
        primeSubmit(renderer->context, PRIME_DRAW_TYPE_ELEMENTS, 
                    PRIME_DRAW_MODE_TRIANGLES, renderer->indexCount);
    }

    renderer->ptr = renderer->base;
    renderer->indexCount = 0;
}

void primeSetDrawColor(primeRenderer2D* renderer, const primeVec4 color)
{
    PRIME_ASSERT_MSG(renderer, "renderer is null");
    renderer->color = color;
}

void primeSetDrawColori(primeRenderer2D* renderer, const primeVec4u color)
{
    PRIME_ASSERT_MSG(renderer, "renderer is null");
    renderer->color.x = (f32)color.x / 255.0f;
    renderer->color.y = (f32)color.y / 255.0f;
    renderer->color.z = (f32)color.z / 255.0f;
    renderer->color.w = (f32)color.w / 255.0f;
}