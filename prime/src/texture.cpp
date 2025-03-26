
#include "pch.h"
#include "prime/texture.h"

#include "opengl/opengl_texture.h"

struct primeTexture
{
    void* handle = nullptr;
    primeVec2u size;
    primeTextureFlag flag;

    void(*destroy)(void* handle) = nullptr;
    void(*bind)(void* handle, u32 slot) = nullptr;
    void(*unbind)(void* handle) = nullptr;
    void(*bindTarget)(void* handle, u32 width, u32 height) = nullptr;
    void(*unbindTarget)(void* handle) = nullptr;
};

primeTexture* primeCreateTexture(primeTextureDesc desc)
{
    primeTexture* texture = new primeTexture();
    switch (s_InitData.type) {
        case primeDeviceTypes_OpenGL: {
            texture->handle = _glCreateTexture(desc);
            texture->destroy = _glDestroyTexture;
            texture->bind = _glBindTexture;
            texture->unbind = _glUnbindTexture;
            texture->bindTarget = _glBindRenderTarget;
            texture->unbindTarget = _glUnbindRenderTarget;
            break;
        } 
    } 
    s_InitData.textures.push_back(texture);
    return texture;
}

primeTexture* primeLoadTexture(const char* filepath)
{
    primeTexture* texture = new primeTexture();
    switch (s_InitData.type) {
        case primeDeviceTypes_OpenGL: {
            u32 width;
            u32 height;
            texture->handle = _glLoadTexture(filepath, &width, &height);
            texture->destroy = _glDestroyTexture;
            texture->bind = _glBindTexture;
            texture->unbind = _glUnbindTexture;
            texture->bindTarget = _glBindRenderTarget;
            texture->unbindTarget = _glUnbindRenderTarget;

            texture->size.x = width;
            texture->size.y = height;
            break;
        } 
    } 
    s_InitData.textures.push_back(texture);
    return texture;
}

void primeDestroyTexture(primeTexture* texture)
{
    PRIME_ASSERT_MSG(texture, "texture is null");
    auto it = std::find(s_InitData.textures.begin(), s_InitData.textures.end(), texture);
    if (it != s_InitData.textures.end()) {
        s_InitData.textures.erase(it); 
    }
    _primeDeleteTexture(texture);
}

void _primeDeleteTexture(primeTexture* texture)
{
    if (s_InitData.activeTexture == texture) {
        texture->unbind(texture->handle);
        s_InitData.activeTexture = nullptr;
    }
    if (s_InitData.activeRenderTarget == texture) {
        texture->unbindTarget(texture->handle);
        s_InitData.activeRenderTarget = nullptr;
    }

    texture->destroy(texture->handle);
    delete texture;
    texture = nullptr;
}

primeVec2u primeGetTextureSize(primeTexture* texture)
{
    PRIME_ASSERT_MSG(texture, "texture is null");
    return texture->size;
}

void primeBindTexture(primeTexture* texture, u32 slot)
{
    PRIME_ASSERT_MSG(texture, "texture is null");
    if (s_InitData.activeTexture == nullptr || s_InitData.activeTexture != texture) {
        if (slot >= PRIME_MAX_TEXTURE_SLOTS) {
            PRIME_WARN("texture slot out of bounds. Binding texture to first slot");
            texture->bind(texture->handle, 0);
        }
        texture->bind(texture->handle, slot);
        s_InitData.activeTexture = texture;
    }
}

void primeUnbindTexture(primeTexture* texture)
{
    PRIME_ASSERT_MSG(texture, "texture is null");
    if (s_InitData.activeTexture == texture) {
        texture->unbind(texture->handle);
        s_InitData.activeTexture = nullptr;
    }
}

void primeBindRenderTarget(primeTexture* texture)
{
    PRIME_ASSERT_MSG(texture, "texture is null");
    if (texture->flag & primeTextureFlags_Target) {
        if (s_InitData.activeRenderTarget == nullptr || s_InitData.activeRenderTarget != texture) {
            texture->bindTarget(texture->handle, texture->size.x, texture->size.y);
            s_InitData.activeRenderTarget = texture;
        }
    }
}

void primeUnbindRenderTarget(primeTexture* texture)
{
    PRIME_ASSERT_MSG(texture, "texture is null");
    if (texture->flag & primeTextureFlags_Target) {
        if (s_InitData.activeRenderTarget == texture) {
            texture->unbindTarget(texture->handle);
            s_InitData.activeRenderTarget = nullptr;
        }
    }
}