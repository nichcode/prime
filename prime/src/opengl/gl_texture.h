
#pragma once

#include "prime/renderer/texture.h"

namespace prime::renderer {

    class GLTexture : public Texture
    {
    private:
        u32 m_ID, m_Width, m_Height;
        str m_Path;
        u32 m_Buffer, m_Depth;
        b8 m_Target;

    public:
        GLTexture(u32 width, u32 height, b8 target, TextureFormat format); 
        GLTexture(const str& filepath);

        virtual ~GLTexture() override; 

        virtual void bind(u32 slot) const override;
        virtual void unBind() const override;

        virtual void bindTarget() const override;
        virtual void unBindTarget() const override;

        virtual u32 getWidth() const  override { return m_Width; }
        virtual u32 getHeight() const override { return m_Height; }
        virtual const str& getPath() const override { return m_Path; }
    };
    
} // namespace prime::renderer
