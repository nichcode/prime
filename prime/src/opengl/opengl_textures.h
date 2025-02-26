
#pragma once

#include "prime/textures.h"

namespace prime {

    class GLTexture : public Texture
    {
    private:
        u32 m_Width, m_Height, m_Depth;
        str m_Path;
        TextureUsage m_Usage;
        TextureHandle* m_Handle;

    public:
        GLTexture(u32 width, u32 height, const TextureUsage usage);
        GLTexture(const str& filepath);

        virtual ~GLTexture() override;

        virtual void
        resize(u32 width, u32 height) override;

        virtual u32 
        getWidth() const override { return m_Width; }

        virtual u32 
        getHeight() const override { return m_Height; }

        virtual TextureUsage 
        getUsage() const override { return m_Usage; }

        virtual str 
        getPath() const override { return m_Path; }

        virtual TextureHandle* 
        getHandle() const override { return m_Handle; }

    private:
        void create(b8 reset);
    };
    
} // namespace prime
