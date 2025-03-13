
#include "gl_texture.h"
#include "opengl_API.h"

namespace prime::renderer {

    GLTexture::GLTexture(u32 width, u32 height, b8 target, TextureFormat format)
    {
        generateTexture( m_ID, width, height, target, m_Buffer, m_Depth, format); 
        m_Width = width;
        m_Height = height;
        m_Target = target;
    }
    
    GLTexture::GLTexture(const str& filepath)
    {
        generateTexture(m_ID, filepath, &m_Width, &m_Height);
        m_Path = filepath;
        m_Target = false;
    }
    
    GLTexture::~GLTexture()
    {
        glDeleteTextures(1, &m_ID);
        m_ID = 0;
        m_Width = 0;
        m_Height = 0;
        if (m_Target) {
            glDeleteFramebuffers(1, &m_Buffer);
            m_Buffer = 0;

            glDeleteRenderbuffers(1, &m_Depth);
            m_Depth = 0;
        }
    }
    
    void GLTexture::bind(u32 slot) const 
    {
        if (slot >= PRIME_MAX_TEXTURE_SLOTS) {
            glActiveTexture(GL_TEXTURE0);
            PRIME_WARN("texture slot out of bounds. Setting texture to first slot");
        }
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_ID);
    }
    
    void GLTexture::unBind() const 
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    
    void GLTexture::bindTarget() const 
    {
        if (m_Target) {
            glBindFramebuffer(GL_FRAMEBUFFER, m_Buffer);
            glViewport(0, 0, m_Width, m_Height);
        }
        else {
            PRIME_INFO("Texture is not a render target");
        }        
    }
    
    void GLTexture::unBindTarget() const 
    {   
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

} // namespace prime::renderer
