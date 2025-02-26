
#pragma once

#include "prime/textures.h"

namespace prime {

    class GLTexture2D : public Texture2D
    {
    private:
        u32 m_ID, m_Width, m_Height;
        str m_Path;
        void* m_Unused;

    public:
        GLTexture2D(u32 width, u32 height);
        GLTexture2D(const str& filepath);

        virtual ~GLTexture2D() override;

        virtual u32 
        getWidth() const override { return m_Width; }

        virtual u32 
        getHeight() const override { return m_Height; }

        virtual u32 
        getID() const override { return m_ID; }

        virtual str 
        getPath() const override { return m_Path; }

        virtual void* 
        getHandle() const override { return m_Unused; }
    };
    
} // namespace prime
