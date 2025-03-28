
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
    void(*set)(void* handle, u32 x, u32 y, u32 width, u32 height, void* data) = nullptr;
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
            texture->set = _glSetTextureData;
            break;
        } 
    } 
    texture->size = desc.size;
    texture->flag = desc.flag;
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

void primeSetTextureData(primeTexture* texture, u32 x, u32 y, u32 width, u32 height, void* data)
{
    PRIME_ASSERT_MSG(texture, "texture is null");
    texture->set(texture->handle, x, y, width, height, data);
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

void primeDestroySubTexture(primeSubTexture* sub_texture)
{
    PRIME_ASSERT_MSG(sub_texture, "sub_texture is null");
    delete sub_texture;
    sub_texture = nullptr;
}

primeSubTexture* primeGetSubTexture(primeTexture* texture, u32 x, u32 y, u32 w, u32 h)
{
    PRIME_ASSERT_MSG(texture, "texture is null");
    f32 size = (f32)primeGetTextureSize(texture).x;
    primeSubTexture* sub_texture = new primeSubTexture();
    sub_texture->size.x = (f32)w;
    sub_texture->size.y = (f32)h;

    f32 left = (f32)x / size;
    f32 top = (f32)y / size;
    f32 right = (f32)(x + w) / size;
    f32 bottom = (f32)(y + h) / size;

    sub_texture->coords[0] = { left, top };
    sub_texture->coords[1] = { right, top };
    sub_texture->coords[2] = { right, bottom };
    sub_texture->coords[3] = { left, bottom };

    s_InitData.subTextures.push_back(sub_texture);
    return sub_texture;
}