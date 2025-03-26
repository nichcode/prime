
#include "pch.h"
#include "prime/renderer2d.h"
#include "prime/context.h"
#include "prime/layout.h"
#include "prime/shader.h"
#include "prime/buffer.h"
#include "prime/texture.h"
#include "shader_sources.h"

#define MAX_RENDERABLES 1000
#define MAX_VERTICES MAX_RENDERABLES * 4
#define MAX_INDICES MAX_RENDERABLES * 6

struct SpriteVertex
{
    primeVec4 vertex;
    primeVec4 color;
    f32 index;
};

struct primeRenderer2D
{
    primeContext* context = nullptr;
    primeBuffer* ubo = nullptr;
    primeMat4 projection;
    primeVec4 color;
    primeVec4 tintColor;

    // sprite
    primeBuffer* spriteVbo = nullptr;
    primeBuffer* spriteIbo = nullptr;
    primeShader* spriteShader = nullptr;
    primeLayout* spriteLayout = nullptr;
    SpriteVertex* spriteBase = nullptr;
    SpriteVertex* spritePtr = nullptr;
    u32 spriteIndexCount = 0;

    std::vector<primeTexture*> textures;
    primeVec2 coords[4]{};
    f32 textureIndex = 1;
};

void setProjection(primeRenderer2D* renderer, primeView view)
{
    f32 x = (f32)view.pos.x;
    f32 y = (f32)view.pos.y;
    f32 width = (f32)view.size.x;
    f32 height = (f32)view.size.y;
    renderer->projection = primeOrtho(x, width, height, y, -1.0f, 1.0f);
    primeSetBufferData(renderer->ubo, &renderer->projection, sizeof(primeMat4));
}

f32 getTextureIndex(primeRenderer2D* renderer, primeTexture* texture)
{
    f32 tex_index = 0.0f;
    for (u32 i = 1; i < renderer->textureIndex; i++) {
        if (renderer->textures[i] == texture) {
            tex_index = (f32)i;
            break;
        }
    }

    if (tex_index == 0.0f) {
        tex_index = renderer->textureIndex;
        renderer->textures.push_back(texture);
        renderer->textureIndex++;
    }
    return tex_index;
}

void initSprites(primeRenderer2D* renderer)
{
    renderer->spriteLayout = primeCreateLayout();
    primeAddAttrib(renderer->spriteLayout, primeDataTypes_Float4, 0, false);
    primeAddAttrib(renderer->spriteLayout, primeDataTypes_Float4, 0, false);
    primeAddAttrib(renderer->spriteLayout, primeDataTypes_Float, 0, false);

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
    buffer_desc.size = sizeof(SpriteVertex) * MAX_VERTICES;
    buffer_desc.type = primeBufferTypes_Vertex;
    buffer_desc.usage = primeBufferUsages_Dynamic;
    renderer->spriteVbo = primeCreateBuffer(buffer_desc);

    buffer_desc.data = indices;
    buffer_desc.size = sizeof(u32) * MAX_INDICES;
    buffer_desc.type = primeBufferTypes_Index;
    buffer_desc.usage = primeBufferUsages_Static;
    renderer->spriteIbo = primeCreateBuffer(buffer_desc);

    primeShaderDesc shader_desc;
    shader_desc.load = false;
    shader_desc.vertex_src = s_SpriteVertexSource;
    shader_desc.pixel_src = s_SpritePixelSource;
    shader_desc.source_type = primeShaderSourceTypes_GLSL;
    renderer->spriteShader = primeCreateShader(shader_desc);

    primeBindLayout(renderer->spriteLayout);
    primeBindShader(renderer->spriteShader);
    i32 samplers[PRIME_MAX_TEXTURE_SLOTS]{};
    for (u32 i = 0; i < PRIME_MAX_TEXTURE_SLOTS; i++) { samplers[i] = i; }
    primeSetIntArray(renderer->spriteShader, "u_Textures", samplers, PRIME_MAX_TEXTURE_SLOTS);

    renderer->spriteBase = new SpriteVertex[MAX_VERTICES];
    renderer->spritePtr = renderer->spriteBase;
    renderer->color = { 0.0f, 0.0f, 0.0f, 1.0f };
    renderer->tintColor = { 1.0f, 1.0f, 1.0f, 1.0f };

    delete[] indices;
}

void shutdownSprites(primeRenderer2D* renderer)
{
    delete[] renderer->spriteBase;
    primeDestroyLayout(renderer->spriteLayout);
    primeDestroyBuffer(renderer->spriteVbo);
    primeDestroyBuffer(renderer->spriteIbo);
    primeDestroyShader(renderer->spriteShader);
}

primeRenderer2D* primeCreateRenderer2D(primeContext* context)
{
    primeRenderer2D* renderer = new primeRenderer2D();
    renderer->context = context;
    primeView view = primeGetView(context);

    primeBufferDesc buffer_desc;
    buffer_desc.data = nullptr;
    buffer_desc.size = sizeof(primeMat4);
    buffer_desc.type = primeBufferTypes_Uniform;
    buffer_desc.usage = primeBufferUsages_Dynamic;
    renderer->ubo = primeCreateBuffer(buffer_desc);

    renderer->coords[0] = { 0.0f, 0.0f };
    renderer->coords[1] = { 1.0f, 0.0f };
    renderer->coords[2] = { 1.0f, 1.0f };
    renderer->coords[3] = { 0.0f, 1.0f };

    primeTextureDesc desc;
    primeTexture* texture = primeCreateTexture(desc);
    renderer->textures.push_back(texture);

    setProjection(renderer, view);
    initSprites(renderer);
    return renderer;
}

void primeDestroyRenderer2D(primeRenderer2D* renderer)
{
    PRIME_ASSERT_MSG(renderer, "renderer is null");
    renderer->textures.clear();
    primeDestroyBuffer(renderer->ubo);
    shutdownSprites(renderer);
    delete renderer;
    renderer = nullptr;
}

void primeDrawRect(primeRenderer2D* renderer, const primeRect rect)
{
    PRIME_ASSERT_MSG(renderer, "renderer is null");
    renderer->spritePtr->vertex.x = rect.x;
    renderer->spritePtr->vertex.y = rect.y;
    renderer->spritePtr->vertex.z = renderer->coords[0].x;
    renderer->spritePtr->vertex.w = renderer->coords[0].y;
    renderer->spritePtr->color = renderer->color;
    renderer->spritePtr->index = 0.0f;
    renderer->spritePtr++;

    renderer->spritePtr->vertex.x = rect.x + rect.width;
    renderer->spritePtr->vertex.y = rect.y;
    renderer->spritePtr->vertex.z = renderer->coords[1].x;
    renderer->spritePtr->vertex.w = renderer->coords[1].y;
    renderer->spritePtr->color = renderer->color;
    renderer->spritePtr->index = 0.0f;
    renderer->spritePtr++;

    renderer->spritePtr->vertex.x = rect.x + rect.width;
    renderer->spritePtr->vertex.y = rect.y + rect.height;
    renderer->spritePtr->vertex.z = renderer->coords[2].x;
    renderer->spritePtr->vertex.w = renderer->coords[2].y;
    renderer->spritePtr->color = renderer->color;
    renderer->spritePtr->index = 0.0f;
    renderer->spritePtr++;

    renderer->spritePtr->vertex.x = rect.x;
    renderer->spritePtr->vertex.y = rect.y + rect.height;
    renderer->spritePtr->vertex.z = renderer->coords[3].x;
    renderer->spritePtr->vertex.w = renderer->coords[3].y;
    renderer->spritePtr->color = renderer->color;
    renderer->spritePtr->index = 0.0f;
    renderer->spritePtr++;

    renderer->spriteIndexCount += 6;
}

void primeDrawTexture(primeRenderer2D* renderer, const primeVec2 pos, 
                                primeTexture* texture, const primeVec2 scale)
{
    PRIME_ASSERT_MSG(renderer, "renderer is null");

    if (texture) {
        primeVec2u texture_size = primeGetTextureSize(texture);
        primeVec2 size;
        size.x = (f32)texture_size.x * scale.x;
        size.y = (f32)texture_size.y * scale.y;
        f32 index = getTextureIndex(renderer, texture);

        renderer->spritePtr->vertex.x = pos.x;
        renderer->spritePtr->vertex.y = pos.y;
        renderer->spritePtr->vertex.z = renderer->coords[0].x;
        renderer->spritePtr->vertex.w = renderer->coords[0].y;
        renderer->spritePtr->color = renderer->tintColor;
        renderer->spritePtr->index = index;
        renderer->spritePtr++;

        renderer->spritePtr->vertex.x = pos.x + size.x;
        renderer->spritePtr->vertex.y = pos.y;
        renderer->spritePtr->vertex.z = renderer->coords[1].x;
        renderer->spritePtr->vertex.w = renderer->coords[1].y;
        renderer->spritePtr->color = renderer->tintColor;
        renderer->spritePtr->index = index;
        renderer->spritePtr++;

        renderer->spritePtr->vertex.x = pos.x + size.x;
        renderer->spritePtr->vertex.y = pos.y + size.y;
        renderer->spritePtr->vertex.z = renderer->coords[2].x;
        renderer->spritePtr->vertex.w = renderer->coords[2].y;
        renderer->spritePtr->color = renderer->tintColor;
        renderer->spritePtr->index = index;
        renderer->spritePtr++;

        renderer->spritePtr->vertex.x = pos.x;
        renderer->spritePtr->vertex.y = pos.y + size.y;
        renderer->spritePtr->vertex.z = renderer->coords[3].x;
        renderer->spritePtr->vertex.w = renderer->coords[3].y;
        renderer->spritePtr->color = renderer->tintColor;
        renderer->spritePtr->index = index;
        renderer->spritePtr++;

        renderer->spriteIndexCount += 6;
    }
    else {
        primeDrawRect(renderer, { pos.x, pos.y, 50.0f, 50.0f });
    }
}

void primeRenderer2DFlush(primeRenderer2D* renderer)
{
    PRIME_ASSERT_MSG(renderer, "renderer is null");
    if (renderer->spriteIndexCount) {
        u32 size = (u32)((u8*)renderer->spritePtr - (u8*)renderer->spriteBase);
        primeBindBuffer(renderer->spriteVbo);
        primeSetBufferData(renderer->spriteVbo, renderer->spriteBase, size);

        for (u32 i = 0; i < renderer->textureIndex; i++) {
            primeBindTexture(renderer->textures[i], i);
        }

        primeBindShader(renderer->spriteShader);
        primeSubmit(renderer->context, primeDrawTypes_Element, 
                    primeDrawModes_Triangles, renderer->spriteIndexCount);
    }

    renderer->spritePtr = renderer->spriteBase;
    renderer->spriteIndexCount = 0;
    renderer->textureIndex = 1;
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

void primeSetTintColor(primeRenderer2D* renderer, const primeVec4 color)
{
    PRIME_ASSERT_MSG(renderer, "renderer is null");
    renderer->tintColor = color;
}

void primeSetTintColori(primeRenderer2D* renderer, const primeVec4u color)
{
    PRIME_ASSERT_MSG(renderer, "renderer is null");
    renderer->tintColor.x = (f32)color.x / 255.0f;
    renderer->tintColor.y = (f32)color.y / 255.0f;
    renderer->tintColor.z = (f32)color.z / 255.0f;
    renderer->tintColor.w = (f32)color.w / 255.0f;
}