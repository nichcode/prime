
#pragma once

#include "prime/renderer/renderer_API.h"
#include "prime/renderer/camera2d.h"
#include <vector>

namespace prime::renderer {

    class Renderer2D
    {
    private:
        struct SpriteVertex
        {
            maths::vec2 position;
            Color color;
            maths::vec2 texture;
            f32 index = 0.0f;
        };

    private:
        RendererAPI* m_API;
        core::Ref<VertexArray> m_SpriteVAO;
        core::Ref<VertexBuffer> m_SpriteVBO;
        core::Ref<IndexBuffer> m_SpriteIBO;
        core::Ref<Shader> m_SpriteShader;
        core::Ref<UniformBuffer> m_UBO;

        maths::vec4 m_Vertices[4];
        maths::vec2 m_TextureCoords[4];
        maths::vec2 m_TextureCoordsFlipX[4];
        maths::vec2 m_TextureCoordsFlipY[4];
        maths::vec2 m_TextureCoordsFlipXY[4];
        SpriteVertex* m_SpritePtr;
        SpriteVertex* m_SpriteBase;

        u32 m_SpriteIndexCount;
        maths::mat4 m_Projection;

        Color m_DrawColor;
        Color m_TintColor;

        std::vector<core::Ref<Texture>> m_Textures;
        f32 m_TextureIndex;

    public:
        Renderer2D();
        ~Renderer2D();

        void init(core::Scope<RendererAPI>& API);
        void destroy();

        void setDrawColor(const Color& color) { m_DrawColor = color; }
        void setTintColor(const Color& color) { m_TintColor = color; }
        void setCamera(const Camera2D& camera);

        void draw(const maths::vec2& pos);
        void draw(const maths::vec2& pos, const maths::vec2& size);
        void draw(const maths::vec2& pos, const maths::vec2& size, f32 rotation, Anchor anchor = AnchorCenter);

        void draw(const maths::vec2& pos, const maths::vec2& size, core::Ref<Texture>& Texture);
        void draw(const maths::vec2& pos, const maths::vec2& size, core::Ref<Texture>& Texture, f32 rotation, Anchor anchor = AnchorCenter);
        void draw(const maths::vec2& pos, const maths::vec2& size, core::Ref<Texture>& Texture, b8 flip_x, b8 flip_y);
        void draw(const maths::vec2& pos, const maths::vec2& size, core::Ref<Texture>& Texture, b8 flip_x, b8 flip_y, f32 rotation, Anchor anchor = AnchorCenter);

        void flush();

    private:
        void reset();
        f32 getIndex(core::Ref<Texture>& texture);
        void nextBatch();
    };
    
} // namespace prime::renderer
