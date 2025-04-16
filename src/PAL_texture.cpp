
#include "PAL_pch.h"
#include "PAL/PAL_texture.h"

PAL_Texture* PAL_CreateTexture(PAL_TextureDesc desc)
{
    PAL_ASSERT(s_ActiveContext, "no context bound");
    PAL_Texture* texture = new PAL_Texture();
    PAL_ASSERT(texture, "failed to create texture");

    texture->flag = desc.flag;
    texture->width = desc.width;
    texture->height = desc.height;
    texture->path = nullptr;
    texture->handle = s_ActiveContext->api.createTexture(desc);

    // rebind the previous active texture
    if (s_ActiveContext->state.activeTexture) {
        s_ActiveContext->api.bindBuffer(s_ActiveContext->state.activeTexture->handle);
    }

    s_ActiveContext->data.textures.push_back(texture); 
    return texture;
}

PAL_Texture* PAL_LoadTexture(const char* filepath)
{
    PAL_ASSERT(s_ActiveContext, "no context bound");
    PAL_Texture* texture = new PAL_Texture();
    PAL_ASSERT(texture, "failed to create texture");

    texture->flag = 0;
    texture->path = filepath;

    u32 width, height;
    texture->handle = s_ActiveContext->api.loadTexture(filepath, &width, &height);
    texture->width = width;
    texture->height = height;

    s_ActiveContext->data.textures.push_back(texture); 
    return texture;
}

void PAL_DestroyTexture(PAL_Texture* texture)
{
    PAL_ASSERT(texture, "texture is null");
    PAL_ASSERT(s_ActiveContext, "no context bound");
    PAL_Context* context = s_ActiveContext;

    auto it = std::find(context->data.textures.begin(), context->data.textures.end(), texture);
    if (it != context->data.textures.end()) {
        context->data.textures.erase(it); 
    }

    if (context->state.activeTexture == texture) {
        context->state.activeTexture = nullptr;
    }

    if (context->state.activeTarget == texture) {
        context->state.activeTarget = nullptr;
    }

    context->api.destroyTexture(texture->handle);
    delete texture;
    texture = nullptr;
}

void PAL_BindTexture(PAL_Texture* texture, u32 slot)
{
    PAL_ASSERT(texture, "texture is null");
    PAL_ASSERT(s_ActiveContext, "no context bound");
    PAL_Context* context = s_ActiveContext;

    if (context->state.activeTexture != texture) {
        context->state.activeTexture = texture;

        if (slot >= PAL_MAX_TEXTURE_SLOTS) {
            PAL_WARN("texture slot out of bounds. Binding texture to first slot");
            context->api.bindTexture(texture->handle, 0);
        }
        context->api.bindTexture(texture->handle, slot);
    }
}

void PAL_BindTarget(PAL_Texture* texture)
{
    PAL_ASSERT(texture, "texture is null");
    PAL_ASSERT(s_ActiveContext, "no context bound");
    PAL_Context* context = s_ActiveContext;

    if (context->state.activeTarget != texture) {
        context->state.activeTarget = texture;

        if (texture->flag & PAL_TextureFlags_Target) {
            context->api.bindTarget(texture->handle, texture->width, texture->height);
        }
    }
}

void PAL_UnbindTarget(PAL_Texture* texture)
{
    PAL_ASSERT(texture, "texture is null");
    PAL_ASSERT(s_ActiveContext, "no context bound");
    PAL_Context* context = s_ActiveContext;

    if (texture->flag & PAL_TextureFlags_Target) {
        context->api.unbindTarget(texture->handle);
        context->state.activeTarget = nullptr;
    }
}

u32 PAL_GetTextureWidth(PAL_Texture* texture)
{
    PAL_ASSERT(texture, "texture is null");
    return texture->width;
}

u32 PAL_GetTextureHeight(PAL_Texture* texture)
{
    PAL_ASSERT(texture, "texture is null");
    return texture->height;
}

const char* PAL_GetTexturePath(PAL_Texture* texture)
{
    PAL_ASSERT(texture, "texture is null");
    return texture->path;
}

PAL_Rect PAL_GetTextureRect(PAL_Texture* texture)
{
    PAL_Rect rect;
    rect.x = 0.0f;
    rect.y = 0.0f;
    rect.w = texture->width;
    rect.h = texture->height;
    return rect;
}