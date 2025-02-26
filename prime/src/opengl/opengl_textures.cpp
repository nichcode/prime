
#include "opengl_textures.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif // STB_IMAGE_IMPLEMENTATION

#include "stb_image/stb_image.h"
#include "glad/glad.h"

#include "prime/logger.h"
#include "prime/utils.h"

namespace prime {

    static u32 s_Data = 0xffffffff;

    GLTexture2D::GLTexture2D(u32 width, u32 height)
    {
        glGenTextures(1, &m_ID);
        glBindTexture(GL_TEXTURE_2D, m_ID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &s_Data);
        glGenerateMipmap(GL_TEXTURE_2D);

        m_Unused = &m_ID;
        m_Width = width;
        m_Height = height;
        m_Path = "";
    }
    
    GLTexture2D::GLTexture2D(const str& filepath)
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

            glGenTextures(1, &m_ID);
            glBindTexture(GL_TEXTURE_2D, m_ID);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glTexImage2D( GL_TEXTURE_2D, 0, int_fmt, w, h, 0, data_fmt, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            m_Unused = &m_ID;
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
    
    GLTexture2D::~GLTexture2D()
    {
        glDeleteTextures(1, &m_ID);
        m_ID = 0;
        m_Unused = nullptr;
        m_Width = 0;
        m_Height = 0;
        m_Path = "";
    }
    
} // namespace prime
