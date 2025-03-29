
#include "pch.h"
#include "prime/renderer2d.h"
#include "prime/context.h"
#include "prime/layout.h"
#include "prime/shader.h"
#include "prime/buffer.h"
#include "prime/texture.h"
#include "prime/font.h"
#include "shader_sources.h"

#define MAX_RENDERABLES 1000
#define MAX_VERTICES MAX_RENDERABLES * 4
#define MAX_INDICES MAX_RENDERABLES * 6
#define TEXTURE_ID 0.0f
#define FONT_ID 1.0f

struct SpriteVertex
{
    primeVec2 pos;
    primeVec4 color;
    primeVec2 coords;
    primeVec2 index;
};

struct primeRenderer2D
{
    primeContext* context = nullptr;
    primeBuffer* ubo = nullptr;
    primeMat4 projection;
    primeVec4 color;
    primeVec4 tintColor;
    primeVec4 textColor;
    primeFont* font = nullptr;
    primeTexture* texture = nullptr;
    f32 fontScale = 1.0f;
    f32 textureScale = 1.0f;
    primeAnchor anchor;

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
    primeVec4 vertices[4]{};
    f32 textureIndex = 1;
};

void setProjection(primeRenderer2D* renderer, primeView view, f32 scale)
{
    f32 x = (f32)view.pos.x;
    f32 y = (f32)view.pos.y;
    f32 width = (f32)view.size.x / scale;
    f32 height = (f32)view.size.y / scale;
    renderer->projection = primeOrtho(x, width, height, y, -1.0f, 1.0f);
    primeBindBuffer(renderer->ubo);
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
    primeAddAttrib(renderer->spriteLayout, primeDataTypes_Float2, 0, false);
    primeAddAttrib(renderer->spriteLayout, primeDataTypes_Float4, 0, false);
    primeAddAttrib(renderer->spriteLayout, primeDataTypes_Float2, 0, false);
    primeAddAttrib(renderer->spriteLayout, primeDataTypes_Float2, 0, false);

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
    renderer->textColor = { 1.0f, 0.0f, 0.0f, 1.0f };

    renderer->vertices[0] = { 0.0f, 0.0f, 0.0f, 1.0f };
    renderer->vertices[1] = { 1.0f, 0.0f, 0.0f, 1.0f };
    renderer->vertices[2] = { 1.0f, 1.0f, 0.0f, 1.0f };
    renderer->vertices[3] = { 0.0f, 1.0f, 0.0f, 1.0f };

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

    setProjection(renderer, view, 1.0f);
    initSprites(renderer);
    primeSetBlendMode(context, primeBlendModes_Alpha);
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

    primeVec2 position[4];
    position[0] = { rect.x, rect.y };
    position[1] = { rect.x + rect.width, rect.y };
    position[2] = { rect.x + rect.width, rect.y + rect.height };
    position[3] = { rect.x, rect.y + rect.height };

    for (size_t i = 0; i < 4; i++) {
        renderer->spritePtr->pos = position[i];
        renderer->spritePtr->coords = renderer->coords[i];
        renderer->spritePtr->color = renderer->color;
        renderer->spritePtr->index.x = 0.0f;
        renderer->spritePtr->index.y =TEXTURE_ID;
        renderer->spritePtr++;
    }
    renderer->spriteIndexCount += 6;
}

void primeDrawRectEx(primeRenderer2D* renderer, const primeRect rect, f32 rotation)
{
    PRIME_ASSERT_MSG(renderer, "renderer is null");

    if (rotation) {
        primeMat4 transform;

        switch (renderer->anchor) {
            case primeAnchors_Center: {
                primeVec2 origin;
                origin.x = rect.width / 2.0f;
                origin.y = rect.height / 2.0f;

                transform = primeTranslate({ rect.x + origin.x, rect.y + origin.y, 0.0f })
                            * primeRotateZ(rotation)
                            * primeTranslate({ -origin.x, -origin.y, 0.0f })
                            * primeScale({ rect.width, rect.height, 1.0f });
                            
                break;
            }
        
            case primeAnchors_TopLeft: {
                transform = primeTranslate({ rect.x, rect.y, 0.0f })
                    * primeRotateZ(rotation) 
                    * primeScale({ rect.width, rect.height, 1.0f });
                
                break;
            }
        } // switch

        for (size_t i = 0; i < 4; i++) {
            primeVec4 position = transform * renderer->vertices[i];
            renderer->spritePtr->pos.x = position.x;
            renderer->spritePtr->pos.y = position.y;

            renderer->spritePtr->coords = renderer->coords[i];
            renderer->spritePtr->color = renderer->color;
            renderer->spritePtr->index.x = 0.0f;
            renderer->spritePtr->index.y = TEXTURE_ID;
            renderer->spritePtr++;
        }
        renderer->spriteIndexCount += 6;
    }
    else {
        primeDrawRect(renderer, rect);
    }
}

void primeDrawTexture(primeRenderer2D* renderer, const primeVec2 pos)
{
    PRIME_ASSERT_MSG(renderer, "renderer is null");
    PRIME_ASSERT_MSG(renderer->texture, "no texture set to renderer");

    if (renderer->texture) {
        primeVec2i size = primeGetTextureSize(renderer->texture);
        size.x *= renderer->textureScale;
        size.y *= renderer->textureScale;
        f32 index = getTextureIndex(renderer, renderer->texture);

        primeVec2 position[4];
        position[0] = { pos.x, pos.y };
        position[1] = { pos.x + (f32)size.x, pos.y };
        position[2] = { pos.x + (f32)size.x, pos.y + (f32)size.y };
        position[3] = { pos.x, pos.y + (f32)size.y };

        for (size_t i = 0; i < 4; i++) {
            renderer->spritePtr->pos = position[i];
            renderer->spritePtr->coords = renderer->coords[i];
            renderer->spritePtr->color = renderer->tintColor;
            renderer->spritePtr->index.x = index;
            renderer->spritePtr->index.y =TEXTURE_ID;
            renderer->spritePtr++;
        }
        renderer->spriteIndexCount += 6;
    }
    else {
        primeDrawRect(renderer, { pos.x, pos.y, 50.0f, 50.0f });
    }
}

void primeDrawTextureEx(primeRenderer2D* renderer, const primeVec2 pos, f32 rotation, primeFlip flip)
{
    PRIME_ASSERT_MSG(renderer, "renderer is null");
    PRIME_ASSERT_MSG(renderer->texture, "no texture set to renderer");

    if (rotation || flip != primeFlips_None) {
        primeMat4 transform;
        primeVec2i size = primeGetTextureSize(renderer->texture);
        f32 width = (f32)size.x * renderer->textureScale;
        f32 height = (f32)size.y * renderer->textureScale;
        f32 index = getTextureIndex(renderer, renderer->texture);

        f32 left = 0.0f;
        f32 top = 0.0f;
        f32 right = 1.0f;
        f32 bottom = 1.0f;

        if (flip & primeFlips_X) {
            f32 temp = right;
            right = left;
            left = temp;
        }
        if (flip & primeFlips_Y) {
            f32 temp = top;
            top = bottom;
            bottom = temp;
        }

        primeVec2 coords[4];
        coords[0] = { left, top };
        coords[1] = { right, top };
        coords[2] = { right, bottom };
        coords[3] = { left, bottom };
        
        switch (renderer->anchor) {
            case primeAnchors_Center: {
                primeVec2 origin;
                origin.x = width / 2.0f;
                origin.y = height / 2.0f;

                transform = primeTranslate({ pos.x + origin.x, pos.y + origin.y, 0.0f })
                            * primeRotateZ(rotation)
                            * primeTranslate({ -origin.x, -origin.y, 0.0f })
                            * primeScale({ width, height, 1.0f });
                            
                break;
            }
        
            case primeAnchors_TopLeft: {
                transform = primeTranslate({ pos.x, pos.y, 0.0f })
                    * primeRotateZ(rotation) 
                    * primeScale({ width, height, 1.0f });
                
                break;
            }
        } // switch

        for (size_t i = 0; i < 4; i++) {
            primeVec4 position = transform * renderer->vertices[i];
            renderer->spritePtr->pos.x = position.x;
            renderer->spritePtr->pos.y = position.y;
            renderer->spritePtr->coords = coords[i];
            renderer->spritePtr->color = renderer->tintColor;
            renderer->spritePtr->index.x = index;
            renderer->spritePtr->index.y = TEXTURE_ID;
            renderer->spritePtr++;
        }
        renderer->spriteIndexCount += 6;
    }
    else {
        primeDrawTexture(renderer, pos);
    }
}

void primeDrawSubTexture(primeRenderer2D* renderer, f32 x, f32 y, f32 w, f32 h, const primeVec2 pos)
{
    PRIME_ASSERT_MSG(renderer, "renderer is null");
    PRIME_ASSERT_MSG(renderer->texture, "no texture set to renderer");

    primeVec2i size = primeGetTextureSize(renderer->texture);
    f32 index = getTextureIndex(renderer, renderer->texture); 

    f32 left = (f32)x / (f32)size.x;
    f32 top = (f32)y / (f32)size.y;
    f32 right = (f32)(x + w) / (f32)size.x;
    f32 bottom = (f32)(y + h) / (f32)size.y;

    primeVec2 coords[4];
    coords[0] = { left, top };
    coords[1] = { right, top };
    coords[2] = { right, bottom };
    coords[3] = { left, bottom };

    primeVec2 position[4];
    position[0] = { pos.x, pos.y };
    position[1] = { pos.x + w, pos.y };
    position[2] = { pos.x + w, pos.y + h };
    position[3] = { pos.x, pos.y + h };

    for (size_t i = 0; i < 4; i++) {
        renderer->spritePtr->pos = position[i];
        renderer->spritePtr->coords = coords[i];
        renderer->spritePtr->color = renderer->tintColor;
        renderer->spritePtr->index.x = index;
        renderer->spritePtr->index.y =TEXTURE_ID;
        renderer->spritePtr++;
    }
    renderer->spriteIndexCount += 6;
}

void primeDrawSubTextureEx(primeRenderer2D* renderer, f32 x, f32 y, f32 w, f32 h, const primeVec2 pos, f32 rotation, primeFlip flip)
{
    PRIME_ASSERT_MSG(renderer, "renderer is null");
    PRIME_ASSERT_MSG(renderer->texture, "no texture set to renderer");

    if (rotation || flip != primeFlips_None) {
        primeMat4 transform;
        f32 index = getTextureIndex(renderer, renderer->texture);
        primeVec2i size = primeGetTextureSize(renderer->texture);

        f32 left = (f32)x / (f32)size.x;
        f32 top = (f32)y / (f32)size.y;
        f32 right = (f32)(x + w) / (f32)size.x;
        f32 bottom = (f32)(y + h) / (f32)size.y;

        if (flip & primeFlips_X) {
            f32 temp = right;
            right = left;
            left = temp;
        }
        if (flip & primeFlips_Y) {
            f32 temp = top;
            top = bottom;
            bottom = temp;
        }

        primeVec2 coords[4];
        coords[0] = { left, top };
        coords[1] = { right, top };
        coords[2] = { right, bottom };
        coords[3] = { left, bottom };

        switch (renderer->anchor) {
            case primeAnchors_Center: {
                primeVec2 origin;
                origin.x = w / 2.0f;
                origin.y = h / 2.0f;

                transform = primeTranslate({ pos.x + origin.x, pos.y + origin.y, 0.0f })
                            * primeRotateZ(rotation)
                            * primeTranslate({ -origin.x, -origin.y, 0.0f })
                            * primeScale({ w, h, 1.0f });
                            
                break;
            }
        
            case primeAnchors_TopLeft: {
                transform = primeTranslate({ pos.x, pos.y, 0.0f })
                    * primeRotateZ(rotation) 
                    * primeScale({ w, h, 1.0f });
                
                break;
            }
        } // switch

        for (size_t i = 0; i < 4; i++) {
            primeVec4 position = transform * renderer->vertices[i];
            renderer->spritePtr->pos.x = position.x;
            renderer->spritePtr->pos.y = position.y;

            renderer->spritePtr->coords = coords[i];
            renderer->spritePtr->color = renderer->tintColor;
            renderer->spritePtr->index.x = index;
            renderer->spritePtr->index.y = TEXTURE_ID;
            renderer->spritePtr++;
        }
        renderer->spriteIndexCount += 6;
    }
    else {
        primeDrawSubTexture(renderer, x, y, w, h, pos);
    }
}

void primeDrawText(primeRenderer2D* renderer, const char* text, const primeVec2 pos)
{
    PRIME_ASSERT_MSG(renderer, "renderer is null");
    PRIME_ASSERT_MSG(renderer->font, "no font set to renderer");
    if(!text) { return; }

    primeTexture* texture = primeGetFontTexture(renderer->font);
    f32 index = getTextureIndex(renderer, texture);
    f32 size = (f32)primeGetTextureSize(texture).x;
    primeVec2 origin = pos;

    f32 base = primeGetFontBaseLine(renderer->font);
    while(char c = *(text++)) {
        auto glyph = primeGetFontGlyph(renderer->font, c);
        f32 x = origin.x + glyph.offset.x * renderer->fontScale;
        f32 y = origin.y + (base - glyph.offset.y) * renderer->fontScale;
        
        f32 width = (f32)glyph.size.x * renderer->fontScale;
        f32 height = (f32)glyph.size.y * renderer->fontScale;
        
        f32 left = (f32)glyph.index.x / size;
        f32 top = (f32)glyph.index.y / size;
        f32 right = (f32)(glyph.index.x + glyph.size.x) / size;
        f32 bottom = (f32)(glyph.index.y + glyph.size.y) / size;

        primeVec2 coords[4];
        coords[0] = { left, top };
        coords[1] = { right, top };
        coords[2] = { right, bottom };
        coords[3] = { left, bottom };

        primeVec2 position[4];
        position[0] = { x, y };
        position[1] = { x + width, y };
        position[2] = { x + width, y + height };
        position[3] = { x, y + height };

        for (size_t i = 0; i < 4; i++) {
            renderer->spritePtr->pos = position[i];
            renderer->spritePtr->coords = coords[i];
            renderer->spritePtr->color = renderer->textColor;
            renderer->spritePtr->index.x = index;
            renderer->spritePtr->index.y = FONT_ID;
            renderer->spritePtr++;
        }
        renderer->spriteIndexCount += 6;
        origin.x += glyph.advance.x * renderer->fontScale; 
    }
}

void primeDrawTextEx(primeRenderer2D* renderer, const char* text, const primeVec2 pos, primeFlip flip)
{
    PRIME_ASSERT_MSG(renderer, "renderer is null");
    PRIME_ASSERT_MSG(renderer->font, "no font set to renderer");
    if(!text) { return; }

    primeTexture* texture = primeGetFontTexture(renderer->font);
    f32 index = getTextureIndex(renderer, texture);
    f32 size = (f32)primeGetTextureSize(texture).x;
    primeVec2 origin = pos;

    f32 base = primeGetFontBaseLine(renderer->font);
    while(char c = *(text++)) {
        auto glyph = primeGetFontGlyph(renderer->font, c);
        f32 x = origin.x + glyph.offset.x * renderer->fontScale;
        f32 y = origin.y + (base - glyph.offset.y) * renderer->fontScale;
        
        f32 width = (f32)glyph.size.x * renderer->fontScale;
        f32 height = (f32)glyph.size.y * renderer->fontScale;
        
        f32 left = (f32)glyph.index.x / size;
        f32 top = (f32)glyph.index.y / size;
        f32 right = (f32)(glyph.index.x + glyph.size.x) / size;
        f32 bottom = (f32)(glyph.index.y + glyph.size.y) / size;

        if (flip & primeFlips_X) {
            f32 temp = right;
            right = left;
            left = temp;
        }
        if (flip & primeFlips_Y) {
            f32 temp = top;
            top = bottom;
            bottom = temp;
        }

        primeVec2 coords[4];
        coords[0] = { left, top };
        coords[1] = { right, top };
        coords[2] = { right, bottom };
        coords[3] = { left, bottom };

        primeVec2 position[4];
        position[0] = { x, y };
        position[1] = { x + width, y };
        position[2] = { x + width, y + height };
        position[3] = { x, y + height };

        for (size_t i = 0; i < 4; i++) {
            renderer->spritePtr->pos = position[i];
            renderer->spritePtr->coords = coords[i];
            renderer->spritePtr->color = renderer->textColor;
            renderer->spritePtr->index.x = index;
            renderer->spritePtr->index.y = FONT_ID;
            renderer->spritePtr++;
        }
        renderer->spriteIndexCount += 6;
        origin.x += glyph.advance.x * renderer->fontScale; 
    }
}

void primeRenderSetView(primeRenderer2D* renderer, primeView view, f32 scale)
{
    PRIME_ASSERT_MSG(renderer, "renderer is null");
    setProjection(renderer, view, scale);
}

void primeSetAnchor(primeRenderer2D* renderer, primeAnchor anchor)
{
    PRIME_ASSERT_MSG(renderer, "renderer is nullptr");
    renderer->anchor = anchor;
}

void primeSetTexture(primeRenderer2D* renderer, primeTexture* texture)
{
    PRIME_ASSERT_MSG(renderer, "renderer is nullptr");
    PRIME_ASSERT_MSG(texture, "font is nullptr");
    renderer->texture = texture;
}

void primeSetFont(primeRenderer2D* renderer, primeFont* font)
{
    PRIME_ASSERT_MSG(renderer, "renderer is nullptr");
    PRIME_ASSERT_MSG(font, "font is nullptr");
    renderer->font = font;
}

void primeFlush(primeRenderer2D* renderer)
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

void primeSetFontScale(primeRenderer2D* renderer, f32 scale)
{
    PRIME_ASSERT_MSG(renderer, "renderer is null");
    renderer->fontScale = scale;
}

void primeSetTextureScale(primeRenderer2D* renderer, f32 scale)
{
    PRIME_ASSERT_MSG(renderer, "renderer is null");
    renderer->textureScale = scale;
}

void primeSetDrawColor(primeRenderer2D* renderer, const primeVec4 color)
{
    PRIME_ASSERT_MSG(renderer, "renderer is null");
    renderer->color = color;
}

void primeSetDrawColori(primeRenderer2D* renderer, const primeVec4i color)
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

void primeSetTintColori(primeRenderer2D* renderer, const primeVec4i color)
{
    PRIME_ASSERT_MSG(renderer, "renderer is null");
    renderer->tintColor.x = (f32)color.x / 255.0f;
    renderer->tintColor.y = (f32)color.y / 255.0f;
    renderer->tintColor.z = (f32)color.z / 255.0f;
    renderer->tintColor.w = (f32)color.w / 255.0f;
}

void primeSetTextColor(primeRenderer2D* renderer, const primeVec4 color)
{
    PRIME_ASSERT_MSG(renderer, "renderer is null");
    renderer->textColor = color;
}

void primeSetTextColori(primeRenderer2D* renderer, const primeVec4i color)
{
    PRIME_ASSERT_MSG(renderer, "renderer is null");
    renderer->textColor.x = (f32)color.x / 255.0f;
    renderer->textColor.y = (f32)color.y / 255.0f;
    renderer->textColor.z = (f32)color.z / 255.0f;
    renderer->textColor.w = (f32)color.w / 255.0f;
}