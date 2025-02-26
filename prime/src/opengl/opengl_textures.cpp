
#include "opengl_textures.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif // STB_IMAGE_IMPLEMENTATION

#include "stb_image/stb_image.h"
#include "opengl_API.h"

#include "prime/logger.h"
#include "prime/utils.h"

namespace prime {

    static u32 s_Data = 0xffffffff;

    GLTexture::GLTexture(u32 width, u32 height, const TextureUsage usage)
    {
        m_Handle = new TextureHandle();

        m_Width = width;
        m_Height = height;
        m_Usage = usage;
        create(false);    
    }
    
    GLTexture::GLTexture(const str& filepath)
    {
        int w = 0, h = 0, channels = 0;
        stbi_uc* data = stbi_load(filepath.c_str(), &w, &h, &channels, 0);
        if (data) {
            GLenum int_fmt = 0, data_fmt = 0;
            if (channels == 4) {
                int_fmt = GL_RGBA8;
                data_fmt = GL_RGBA;
            }
            else if (channels == 3) {
                int_fmt = GL_RGB8;
                data_fmt = GL_RGB;
            }

            PASSERT_MSG(int_fmt & data_fmt, "Format not supported!");

            m_Handle = new TextureHandle();

            glGenTextures(1, &m_Handle->id);
            glBindTexture(GL_TEXTURE_2D, m_Handle->id);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glTexImage2D( GL_TEXTURE_2D, 0, int_fmt, w, h, 0, data_fmt, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            m_Width = w;
            m_Height = h;
            m_Path = filepath;
            stbi_image_free(data);
        }
        else {
            str msg = Utils::format("Could not load texture2d - %s", filepath.c_str());
            PASSERT_MSG(false, msg.c_str());
        }
    }
    
    GLTexture::~GLTexture()
    {
        glDeleteTextures(1, &m_Handle->id);
        if (m_Usage == TextureUsage::RenderTarget) {
            glDeleteRenderbuffers(1, &m_Depth);
            glDeleteFramebuffers(1, &m_Handle->buffer);
        }
        
        m_Handle->id = 0;
        delete m_Handle;
        m_Width = 0;
        m_Height = 0;
        m_Path = "";
        m_Handle->buffer = 0;
        m_Depth = 0;
    }

    void 
    GLTexture::resize(u32 width, u32 height)
    {
        if (width == 0 || height == 0 || width > PMAX_TEXTURE_SIZE || height > PMAX_TEXTURE_SIZE) {
            str msg = Utils::format("Attempted to rezize render target to (%i, %i)", width, height);
            PINFO(msg.c_str());
            return;
        }
        if (m_Usage == TextureUsage::RenderTarget) {
            m_Width = width;
            m_Height = height;
            create(true);
        }
        else {
            PWARN("You can only resize render_target textures");
        }
        
    }

    void GLTexture::create(b8 reset)
    {
        if (m_Usage == TextureUsage::None) {
            if (reset) {
                glDeleteTextures(1, &m_Handle->id);
                m_Handle->id = 0;
            }

            glGenTextures(1, &m_Handle->id);
            glBindTexture(GL_TEXTURE_2D, m_Handle->id);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &s_Data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }

        else if (m_Usage == TextureUsage::RenderTarget) {
            if (reset) {
                glDeleteRenderbuffers(1, &m_Depth);
                glDeleteTextures(1, &m_Handle->id);
                glDeleteFramebuffers(1, &m_Handle->buffer);

                m_Handle->id = 0;
                m_Depth = 0;
                m_Handle->id = 0;
            }

            glGenFramebuffers(1, &m_Handle->buffer);
            glBindFramebuffer(GL_FRAMEBUFFER, m_Handle->buffer);

            // texture
            glGenTextures(1, &m_Handle->id);
            glBindTexture(GL_TEXTURE_2D, m_Handle->id);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
            glGenerateMipmap(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, 0);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_Handle->id, 0);

            // Create depth/stencil renderbuffer
            glGenRenderbuffers(1, &m_Depth);
            glBindRenderbuffer(GL_RENDERBUFFER, m_Depth);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Width, m_Height);
            glBindRenderbuffer(GL_RENDERBUFFER, 0);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_Depth);

            // Check for completeness
            i32 complete_status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
            if (complete_status != GL_FRAMEBUFFER_COMPLETE) {
                str msg = Utils::format("Failure to create render target texture. Complete status: %i", complete_status);
                PINFO(msg.c_str());
            }
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }
        
    }
    
} // namespace prime
