
#include "pch.h"
#include "opengl_texture.h"
#include "opengl_funcs.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif // STB_IMAGE_IMPLEMENTATION
#include "vendor/stb_image.h"

static u32 s_TextureData = 0xffffffff;

PRIME_INLINE GLenum dataFormatToGL(primeTextureFormat format)
{
    switch (format) {
        case primeTextureFormat_Red:
            return GL_RED;
            break;

        case primeTextureFormat_RGB8:
        case primeTextureFormat_RGB16:
            return GL_RGB;
            break;

        case primeTextureFormat_RGB16F:
            return GL_RGB16F;
            break;

        case primeTextureFormat_RGB32F:
            return GL_RGB32F;
            break;

        case primeTextureFormat_RGBA8:
        case primeTextureFormat_RGBA16:
            return GL_RGBA;
            break;

        case primeTextureFormat_RGBA16F:
            return GL_RGBA16F;
            break;

        case primeTextureFormat_RGBA32F:
            return GL_RGBA32F;
            break;
    }
    return 0;
}

PRIME_INLINE GLenum intFormatToGL(primeTextureFormat format)
{
    switch (format) {
        case primeTextureFormat_Red:
            return GL_RED;
            break;

        case primeTextureFormat_RGB8:
            return GL_RGB8;
            break;

        case primeTextureFormat_RGB16:
            return GL_RGB16;
            break;

        case primeTextureFormat_RGB16F:
            return GL_RGB16F;
            break;

        case primeTextureFormat_RGB32F:
            return GL_RGB32F;
            break;

        case primeTextureFormat_RGBA8:
            return GL_RGBA8;
            break;

        case primeTextureFormat_RGBA16:
            return GL_RGBA16;
            break;

        case primeTextureFormat_RGBA16F:
            return GL_RGBA16F;
            break;

        case primeTextureFormat_RGBA32F:
            return GL_RGBA32F;
            break;
    }
    return 0;
}

struct glTexture
{
    u32 id = 0;
    u32 buffer = 0;
    u32 depth = 0;
};

void* _glCreateTexture(primeTextureDesc desc)
{
    glTexture* texture = new glTexture();
    u32 data_format = dataFormatToGL(desc.format);
    u32 int_format = intFormatToGL(desc.format);

    if (desc.flag & primeTextureFlags_Target) {
        glGenFramebuffers(1, &texture->buffer);
        glBindFramebuffer(GL_FRAMEBUFFER, texture->buffer);

        // texture
        glGenTextures(1, &texture->id);
        glBindTexture(GL_TEXTURE_2D, texture->id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D( GL_TEXTURE_2D, 0, int_format, desc.size.x, desc.size.y,
                      0, data_format, GL_UNSIGNED_BYTE, nullptr);
        
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture->id, 0);

        // Create depth/stencil renderbuffer
        glGenRenderbuffers(1, &texture->depth);
        glBindRenderbuffer(GL_RENDERBUFFER, texture->depth);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, desc.size.x, desc.size.y);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, texture->depth);

        // Check for completeness
        i32 status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if (status != GL_FRAMEBUFFER_COMPLETE) {
            PRIME_ASSERT_MSG(false, "Failure to create render target texture. Complete status: %i", status);
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        return texture;
    }

    glGenTextures(1, &texture->id);
    glBindTexture(GL_TEXTURE_2D, texture->id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (desc.flag & primeTextureFlags_Storage) {
        glTexImage2D( GL_TEXTURE_2D, 0, int_format, desc.size.x, desc.size.y,
                    0, data_format, GL_UNSIGNED_BYTE, nullptr);
    }
    glTexImage2D( GL_TEXTURE_2D, 0, int_format, desc.size.x, desc.size.y,
                    0, data_format, GL_UNSIGNED_BYTE, &s_TextureData);

    return texture;
}

void* _glLoadTexture(const char* filepath, u32* width, u32* height)
{
    int w = 0, h = 0, channels = 0;
    stbi_uc* data = stbi_load(filepath, &w, &h, &channels, 0);
    if (data) {
        glTexture* texture = new glTexture();

        GLenum int_fmt = 0, data_fmt = 0;
        if (channels == 4) {
            int_fmt = GL_RGBA8;
            data_fmt = GL_RGBA;
        }
        else if (channels == 3) {
            int_fmt = GL_RGB8;
            data_fmt = GL_RGB;
        }

        PRIME_ASSERT_MSG(int_fmt & data_fmt, "Format not supported!");

        glGenTextures(1, &texture->id);
        glBindTexture(GL_TEXTURE_2D, texture->id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D( GL_TEXTURE_2D, 0, int_fmt, w, h, 0, data_fmt, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        *width = w;
        *height = h;
        stbi_image_free(data);
        return texture;
    }
    PRIME_ASSERT_MSG(false, "Could not load texture2d - %s", filepath);
    return nullptr;
}

void _glDestroyTexture(void* handle)
{
    glTexture* texture = (glTexture*)handle;
    glDeleteTextures(1, &texture->id);
    if (texture->buffer) {
        glDeleteFramebuffers(1, &texture->buffer);
        glDeleteRenderbuffers(1, &texture->depth);
    }
    delete texture;
}

void _glBindTexture(void* handle, u32 slot)
{
    glTexture* texture = (glTexture*)handle;
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, texture->id);
}

void _glUnbindTexture(void* handle)
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void _glBindRenderTarget(void* handle, u32 width, u32 height)
{
    glTexture* texture = (glTexture*)handle;
    if (texture->buffer) {
        glBindFramebuffer(GL_FRAMEBUFFER, texture->buffer);
        glViewport(0, 0, width, height);
    }
}

void _glUnbindRenderTarget(void* handle)
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}