
#include "pch.h"
#include "prime/texture.h"

prTexture* prCreateTexture(prTextureDesc desc)
{
    PR_ASSERT(s_ActiveContext, "no context bound");
    prTexture* texture = new prTexture();
    PR_ASSERT(texture, "failed to create texture");

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

prTexture* prLoadTexture(const char* filepath)
{
    PR_ASSERT(s_ActiveContext, "no context bound");
    prTexture* texture = new prTexture();
    PR_ASSERT(texture, "failed to create texture");

    texture->flag = 0;
    texture->path = filepath;

    u32 width, height;
    texture->handle = s_ActiveContext->api.loadTexture(filepath, &width, &height);
    texture->width = width;
    texture->height = height;

    s_ActiveContext->data.textures.push_back(texture); 
    return texture;
}

void prDestroyTexture(prTexture* texture)
{
    PR_ASSERT(texture, "texture is null");
    PR_ASSERT(s_ActiveContext, "no context bound");
    prContext* context = s_ActiveContext;

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

void prBindTexture(prTexture* texture, u32 slot)
{
    PR_ASSERT(texture, "texture is null");
    PR_ASSERT(s_ActiveContext, "no context bound");
    prContext* context = s_ActiveContext;

    if (context->state.activeTexture != texture) {
        context->state.activeTexture = texture;

        if (slot >= PR_MAX_TEXTURE_SLOTS) {
            PR_WARN("texture slot out of bounds. Binding texture to first slot");
            context->api.bindTexture(texture->handle, 0);
        }
        context->api.bindTexture(texture->handle, slot);
    }
}

void prBindTarget(prTexture* texture)
{
    PR_ASSERT(texture, "texture is null");
    PR_ASSERT(s_ActiveContext, "no context bound");
    prContext* context = s_ActiveContext;

    if (context->state.activeTarget != texture) {
        context->state.activeTarget = texture;

        if (texture->flag & prTextureFlags_Target) {
            context->api.bindTarget(texture->handle, texture->width, texture->height);
        }
    }
}

void prUnbindTarget(prTexture* texture)
{
    PR_ASSERT(texture, "texture is null");
    PR_ASSERT(s_ActiveContext, "no context bound");
    prContext* context = s_ActiveContext;

    if (texture->flag & prTextureFlags_Target) {
        context->api.unbindTarget(texture->handle);
        context->state.activeTarget = nullptr;
    }
}

u32 prGetTextureWidth(prTexture* texture)
{
    PR_ASSERT(texture, "texture is null");
    return texture->width;
}

u32 prGetTextureHeight(prTexture* texture)
{
    PR_ASSERT(texture, "texture is null");
    return texture->height;
}

const char* prGetTexturePath(prTexture* texture)
{
    PR_ASSERT(texture, "texture is null");
    return texture->path;
}

prRect prGetTextureRect(prTexture* texture)
{
    prRect rect;
    rect.x = 0.0f;
    rect.y = 0.0f;
    rect.w = texture->width;
    rect.h = texture->height;
    return rect;
}