
#include "pch.h"
#include "prime/renderer.h"
#include "prime/buffer.h"
#include "prime/shader.h"
#include "prime/texture.h"
#include "prime/context.h"

#define MAX_SPRITES 10000
#define MAX_VERTICES MAX_SPRITES * 4
#define MAX_INDICES MAX_SPRITES * 6
#define TEXTURE_ID 0.0f
#define FONT_ID 1.0f

void _ResetBatch(prRenderer* renderer)
{
    renderer->sprites.clear();
    renderer->indexCount = 0;
    renderer->texIndex = 1;
}

void _CheckBatch(prRenderer* renderer)
{
    if (renderer->indexCount >= MAX_INDICES || renderer->texIndex >= PR_MAX_TEXTURE_SLOTS) {
        prRendererFlush(renderer);
    }
}

f32 _GetTextureIndex(prRenderer* renderer, prTexture* texture)
{
    u32 tex_index = 0.0f;
    for (u32 i = 1; i < renderer->texIndex; i++) {
        if (renderer->textures[i] == texture) {
            tex_index = (f32)i;
            break;
        }
    }

    if (tex_index == 0.0f) {
        tex_index = renderer->texIndex;
        renderer->textures.push_back(texture);
        renderer->texIndex++;
    }

    return tex_index;
}

prRenderer* prCreateRenderer()
{
    PR_ASSERT(s_ActiveContext, "no context bound");
    prRenderer* renderer = new prRenderer();
    PR_ASSERT(renderer, "failed to create renderer");

    renderer->vertices[0] = { 0.0f, 0.0f, 0.0f, 1.0f };
    renderer->vertices[1] = { 1.0f, 0.0f, 0.0f, 1.0f };
    renderer->vertices[2] = { 1.0f, 1.0f, 0.0f, 1.0f };
    renderer->vertices[3] = { 0.0f, 1.0f, 0.0f, 1.0f };

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

    prBindBuffer(renderer->vbo);
    prBindBuffer(renderer->ibo);
    prBindShader(renderer->shader);
    prSetBlendMode(prBlendModes_Alpha);

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

void prRendererDrawRect(prRenderer* renderer, const prRect rect, const prColor color)
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

        sprite.color = color;
        renderer->sprites.push_back(sprite);
    }
    renderer->indexCount += 6;
}

void prRendererDrawRectEx(prRenderer* renderer, const prRect rect, f32 rotation, u32 anchor, const prColor color)
{
    PR_ASSERT(renderer, "renderer is null");
    _CheckBatch(renderer);

    if (!rotation) { prRendererDrawRect(renderer, rect, color); return; }
    prMat4 transform;

    switch (anchor) {
        case prAnchors_TopLeft: {
            transform = prTranslate({ rect.x, rect.y, 0.0f }) 
                    * prRotateZ(rotation)
                    * prScale({ rect.w, rect.h, 1.0f });       
            break;
        }

        case prAnchors_Center: {
            prVec2 origin;
            origin.x = rect.w / 2.0f;
            origin.y = rect.h / 2.0f;

            transform = prTranslate({ rect.x + origin.x, rect.y + origin.y, 0.0f })
                        * prRotateZ(rotation)
                        * prTranslate({ -origin.x, -origin.y, 0.0f })
                        * prScale({ rect.w, rect.h, 1.0f });         
            break;
        }
    }

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

        sprite.color = color;
        renderer->sprites.push_back(sprite);
    }
    renderer->indexCount += 6;
}

void prRendererDrawTexture(prRenderer* renderer, const prRect rect, prTexture* texture)
{
    PR_ASSERT(renderer, "renderer is null");
    if (!texture) { // texture is null
        prRendererDrawRect(renderer, rect, { 1.0f, 1.0f, 1.0f, 1.0f });
        return;
    }

    _CheckBatch(renderer);
    prMat4 transform = prTranslate({ rect.x, rect.y, 0.0f }) 
        * prScale({ rect.w, rect.h, 1.0f });

    f32 index = _GetTextureIndex(renderer, texture);

    for (size_t i = 0; i < 4; i++) {
        prVec4 position = transform * renderer->vertices[i];
        prVertex sprite;
        sprite.position.x = position.x;
        sprite.position.y = position.y;
        sprite.position.z = 0.0f;

        sprite.texture.x = renderer->texCoords[i].x;
        sprite.texture.y = renderer->texCoords[i].y;
        sprite.texture.z = index;
        sprite.texture.w = TEXTURE_ID;

        sprite.color = { 1.0f, 1.0f, 1.0f, 1.0f };
        renderer->sprites.push_back(sprite);
    }
    renderer->indexCount += 6;
}

void prRendererDrawTextureEx(prRenderer* renderer, const prRect rect, f32 rotation, 
                            u32 anchor, prTexture* texture, const prColor tint_color, u32 flip)
{
    PR_ASSERT(renderer, "renderer is null");
    if (!texture) {
        prRendererDrawRectEx(renderer, rect, rotation, anchor, { 1.0f, 1.0f, 1.0f, 1.0f });
        return;
    }
    _CheckBatch(renderer);

    prMat4 transform;
    switch (anchor) {
        case prAnchors_TopLeft: {
            transform = prTranslate({ rect.x, rect.y, 0.0f }) 
                    * prRotateZ(rotation)
                    * prScale({ rect.w, rect.h, 1.0f });       
            break;
        }

        case prAnchors_Center: {
            prVec2 origin;
            origin.x = rect.w / 2.0f;
            origin.y = rect.h / 2.0f;

            transform = prTranslate({ rect.x + origin.x, rect.y + origin.y, 0.0f })
                        * prRotateZ(rotation)
                        * prTranslate({ -origin.x, -origin.y, 0.0f })
                        * prScale({ rect.w, rect.h, 1.0f });         
            break;
        }
    }

    f32 index = _GetTextureIndex(renderer, texture);

    f32 left = 0.0f;
    f32 top = 0.0f;
    f32 right = 1.0f;
    f32 bottom = 1.0f;

    if (flip & prFlips_Horizontal) {
        f32 temp = right;
        right = left;
        left = temp;
    }
    if (flip & prFlips_Vertical) {
        f32 temp = top;
        top = bottom;
        bottom = temp;
    }

    prVec2 coords[4];
    coords[0] = { left, top };
    coords[1] = { right, top };
    coords[2] = { right, bottom };
    coords[3] = { left, bottom };

    for (size_t i = 0; i < 4; i++) {
        prVec4 position = transform * renderer->vertices[i];
        prVertex sprite;
        sprite.position.x = position.x;
        sprite.position.y = position.y;
        sprite.position.z = 0.0f;

        sprite.texture.x = coords[i].x;
        sprite.texture.y = coords[i].y;
        sprite.texture.z = index;
        sprite.texture.w = TEXTURE_ID;

        sprite.color = tint_color;
        renderer->sprites.push_back(sprite);
    }
    renderer->indexCount += 6;
}

void prRendererDrawText(prRenderer* renderer, f32 x, f32 y, f32 scale, const char* text, prFont* font, const prColor color)
{
    PR_ASSERT(renderer, "renderer is null");
    PR_ASSERT(font, "font is null");
    if(!text) { return; }

    prTexture* texture = font->texture;
    if (!texture) { return; }

    f32 index = _GetTextureIndex(renderer, texture);
    f32 size = texture->width;
    f32 base = font->baseline;
    prVec2 origin = { x, y };

    while(char c = *(text++)) {
        auto glyph = font->glyphs.at(c);
        f32 xpos = origin.x + glyph.offset_x;
        f32 ypos = origin.y + (base - glyph.offset_y) * scale;

        f32 width = glyph.size_x * scale;
        f32 height = glyph.size_y * scale;

        f32 left = glyph.index_x / size;
        f32 top = glyph.index_y / size;
        f32 right = (glyph.index_x + glyph.size_x) / size;
        f32 bottom = (glyph.index_y + glyph.size_y) / size;

        prVec2 coords[4];
        coords[0] = { left, top };
        coords[1] = { right, top };
        coords[2] = { right, bottom };
        coords[3] = { left, bottom };

        prVec2 position[4];
        position[0] = { xpos, ypos };
        position[1] = { xpos + width, ypos };
        position[2] = { xpos + width, ypos + height };
        position[3] = { xpos, ypos + height };

        for (size_t i = 0; i < 4; i++) {
            prVertex sprite;
            sprite.position.x = position[i].x;
            sprite.position.y = position[i].y;
            sprite.position.z = 0.0f;

            sprite.texture.x = coords[i].x;
            sprite.texture.y = coords[i].y;
            sprite.texture.z = index;
            sprite.texture.w = FONT_ID;

            sprite.color = color;
            renderer->sprites.push_back(sprite);
        }
        renderer->indexCount += 6;
        origin.x += glyph.advance_x * scale; 
    }
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

        for (u32 i = 0; i < renderer->texIndex; i++) {
            prBindTexture(renderer->textures[i], i);
        }
        
        prDrawElements(prDrawModes_Triangles, renderer->indexCount);
        _ResetBatch(renderer);
    }
}

void prSetRendererCamera(prRenderer* renderer, prCamera camera)
{
    PR_ASSERT(renderer, "renderer is null");
    //prMat4 transform;
    // if (camera.rotation) {
    //     transform = prTranslate({ camera.x, camera.y, 0.0f }) 
    //         * prRotateZ(camera.rotation);
    // }
    // else {
    //     transform = prTranslate({ camera.x, camera.y, 0.0f });
    // }

    // f32 size = camera.zoom;
    // f32 aspect_ratio = camera.aspect_ratio;
    // f32 left = -size * aspect_ratio * 0.5f;
    // f32 right = size * aspect_ratio * 0.5f;
    // f32 bottom = size * 0.5f;
    // f32 top = -size * 0.5f;

    prMat4 projection = prOrtho(
        camera.view.x, 
        camera.view.width,
        camera.view.height, 
        camera.view.y,
        -1.0f, 1.0f);

    renderer->projection = projection;
    prSetMat4("u_ViewProjection", renderer->projection.data);
}