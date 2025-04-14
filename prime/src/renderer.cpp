
#include "pch.h"
#include "prime/renderer.h"
#include "prime/buffer.h"
#include "prime/shader.h"
#include "prime/context.h"

#define MAX_SPRITES 10000
#define MAX_VERTICES MAX_SPRITES * 4
#define MAX_INDICES MAX_SPRITES * 6
#define TEXTURE_ID 0.0f
#define FONT_ID 0.0f

void _ResetBatch(prRenderer* renderer)
{
    renderer->sprites.clear();
    renderer->textures.clear();
    renderer->indexCount = 0;
    renderer->texIndex = 1;
    renderer->activeTexIndex = 0;
}

void _CheckBatch(prRenderer* renderer)
{
    if (renderer->indexCount >= MAX_INDICES || renderer->texIndex >= PR_MAX_TEXTURE_SLOTS) {
        prRendererFlush(renderer);
    }
}

prRenderer* prCreateRenderer()
{
    PR_ASSERT(s_ActiveContext, "no context bound");
    prRenderer* renderer = new prRenderer();
    PR_ASSERT(renderer, "failed to create renderer");

    renderer->vertices[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
    renderer->vertices[1] = {  0.5f, -0.5f, 0.0f, 1.0f };
    renderer->vertices[2] = {  0.5f,  0.5f, 0.0f, 1.0f };
    renderer->vertices[3] = { -0.5f,  0.5f, 0.0f, 1.0f };

    renderer->texCoords[0] = { 0.0f, 0.0f };
    renderer->texCoords[1] = { 1.0f, 0.0f };
    renderer->texCoords[2] = { 1.0f, 1.0f };
    renderer->texCoords[3] = { 0.0f, 1.0f };

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
    prShaderAttrib texture_attrib;
    position_attrib.type = prShaderDataTypes_Float3;
    color_attrib.type = prShaderDataTypes_Float4;
    texture_attrib.type = prShaderDataTypes_Float4;
    layout.attribs[0] = position_attrib;
    layout.attribs[1] = color_attrib;
    layout.attribs[2] = texture_attrib;
    layout.count = 3;

    prBufferDesc buffer_desc;
    buffer_desc.type = prBufferTypes_Vertex;
    buffer_desc.data = nullptr;
    buffer_desc.size = sizeof(prVertex) * MAX_VERTICES;
    buffer_desc.usage = prBufferUsages_Dynamic;
    renderer->vbo = prCreateBuffer(buffer_desc);

    buffer_desc.type = prBufferTypes_Index;
    buffer_desc.data = indices;
    buffer_desc.size = sizeof(u32) * MAX_INDICES;
    buffer_desc.usage = prBufferUsages_Static;
    renderer->ibo = prCreateBuffer(buffer_desc);

    prShaderDesc shader_desc;
    shader_desc.load = true;
    shader_desc.type = prShaderSourceTypes_GLSL;
    shader_desc.vertex_src = "shaders/renderer_vertex.glsl";
    shader_desc.pixel_src = "shaders/renderer_pixel.glsl";
    shader_desc.layout = layout;
    renderer->shader = prCreateShader(shader_desc);

    prTextureDesc desc;
    desc.format = prTextureFormats_RGBA16;
    desc.flag = prTextureFlags_None;
    desc.width = 1;
    desc.height = 1;
    prTexture* texture = prCreateTexture(desc);
    renderer->textures.push_back(texture);
    renderer->tintColor = { 1.0f, 1.0f, 1.0f, 1.0f };
    renderer->activeTexIndex = 0;

    prBindBuffer(renderer->vbo);
    prBindBuffer(renderer->ibo);
    prBindShader(renderer->shader);

    i32 samplers[PR_MAX_TEXTURE_SLOTS];
    for (u32 i = 0; i < PR_MAX_TEXTURE_SLOTS; i++) { samplers[i] = i; }
    prSetIntArray("u_Textures", samplers, PR_MAX_TEXTURE_SLOTS);

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
    renderer->textures.clear();

    delete renderer;
    renderer = nullptr;
}

void prRendererDrawRect(prRenderer* renderer, const prRect rect)
{
    PR_ASSERT(renderer, "renderer is null");
    _CheckBatch(renderer);
    
    prMat4 transform = prTranslate({ rect.x, rect.y, 0.0f }) 
        * prScale({ rect.w, rect.h, 1.0f });

    for (size_t i = 0; i < 4; i++) {
        prVec4 position = transform * renderer->vertices[i];
        prVertex sprite;
        sprite.position.x = position.x;
        sprite.position.y = position.y;
        sprite.position.z = 0.0f;

        sprite.texture.x = renderer->texCoords[i].x;
        sprite.texture.y = renderer->texCoords[i].y;
        sprite.texture.z = 0.0f; // texture index
        sprite.texture.w = TEXTURE_ID;

        sprite.color = renderer->drawColor;
        renderer->sprites.push_back(sprite);
    }
    renderer->indexCount += 6;
}

void prRendererDrawTexture(prRenderer* renderer, const prRect rect)
{
    PR_ASSERT(renderer, "renderer is null");
    if (!renderer->activeTexIndex) { // no active texture
        prRendererDrawRect(renderer, rect);
        return;
    }

    _CheckBatch(renderer);
    prMat4 transform = prTranslate({ rect.x, rect.y, 0.0f }) 
        * prScale({ rect.w, rect.h, 1.0f });

    for (size_t i = 0; i < 4; i++) {
        prVec4 position = transform * renderer->vertices[i];
        prVertex sprite;
        sprite.position.x = position.x;
        sprite.position.y = position.y;
        sprite.position.z = 0.0f;

        sprite.texture.x = renderer->texCoords[i].x;
        sprite.texture.y = renderer->texCoords[i].y;
        sprite.texture.z = (f32)renderer->activeTexIndex; // texture index
        sprite.texture.w = TEXTURE_ID;

        sprite.color = renderer->tintColor;
        renderer->sprites.push_back(sprite);
    }
    renderer->indexCount += 6;
}

void prRendererFlush(prRenderer* renderer)
{
    PR_ASSERT(renderer, "renderer is null");
    if (renderer->indexCount) {
        prBindBuffer(renderer->vbo);
        prBindBuffer(renderer->ibo);
        prBindShader(renderer->shader);

        u32 size = sizeof(prVertex) * renderer->indexCount;
        prSetBufferData(prBufferTypes_Vertex, renderer->sprites.data(), size);
        prSetMat4("u_ViewProjection", renderer->projection.data);

        for (u32 i = 0; i < renderer->texIndex; i++) {
            prBindTexture(renderer->textures[i], i);
        }
        
        prDrawElements(prDrawModes_Triangles, renderer->indexCount);
        _ResetBatch(renderer);
    }
}

void prSetRendererDrawColor(prRenderer* renderer, f32 r, f32 g, f32 b, f32 a)
{
    PR_ASSERT(renderer, "renderer is null");
    renderer->drawColor = { r, g, b, a };
}

void prSetRendererDrawColori(prRenderer* renderer, u8 r, u8 g, u8 b, u8 a)
{
    PR_ASSERT(renderer, "renderer is null");
    f32 fr = (f32)r / 255.0f;
    f32 fg = (f32)g / 255.0f;
    f32 fb = (f32)b / 255.0f;
    f32 fa = (f32)a / 255.0f;
    renderer->drawColor = { fr, fg, fb, fa };
}

void prSetRendererTintColor(prRenderer* renderer, f32 r, f32 g, f32 b, f32 a)
{
    PR_ASSERT(renderer, "renderer is null");
    renderer->tintColor = { r, g, b, a };
}

void prSetRendererTintColori(prRenderer* renderer, u8 r, u8 g, u8 b, u8 a)
{
    PR_ASSERT(renderer, "renderer is null");
    f32 fr = (f32)r / 255.0f;
    f32 fg = (f32)g / 255.0f;
    f32 fb = (f32)b / 255.0f;
    f32 fa = (f32)a / 255.0f;
    renderer->tintColor = { fr, fg, fb, fa };
}

void prSetRendererCamera(prRenderer* renderer, prCamera camera)
{
    PR_ASSERT(renderer, "renderer is null");
    prMat4 transform;
    if (camera.rotation) {
        transform = prTranslate({ camera.x, camera.y, 0.0f }) 
            * prRotateZ(camera.rotation);
    }
    else {
        transform = prTranslate({ camera.x, camera.y, 0.0f });
    }

    f32 size = camera.zoom;
    f32 aspect_ratio = camera.aspect_ratio;
    f32 left = -size * aspect_ratio * 0.5f;
    f32 right = size * aspect_ratio * 0.5f;
    f32 bottom = size * 0.5f;
    f32 top = -size * 0.5f;

    prMat4 projection = prOrtho(left, right, bottom, top, -1.0f, 1.0f);
    renderer->projection = projection * prInverse(transform);
}

void prSetRendererTexture(prRenderer* renderer, prTexture* texture)
{
    PR_ASSERT(renderer, "renderer is null");
    PR_ASSERT(texture, "texture is null");

    u32 tex_index = 0.0f;
    for (u32 i = 1; i < renderer->texIndex; i++) {
        if (renderer->textures[i] == texture) {
            tex_index = i;
            break;
        }
    }

    if (tex_index == 0) {
        tex_index = renderer->texIndex;
        renderer->textures.push_back(texture);
        renderer->texIndex++;
    }

    renderer->activeTexIndex = tex_index;
}