
#pragma once

#include "device.h"

#include <array>

namespace prime {

    enum class Layer
    {
        One,
        Two,
        Three,
        Four,
        Five,
        Six,
        Seven,
        Eight,
        Nine,
        Ten
    };

    class Renderer2D
    {
    private:
        struct SpriteVertex
        {
            vec3 pos;
            Color color;
            vec2 texCoords;
            f32 texIndex;
        };

    private:
        Ref<Device> m_Device;
        Layer m_Layer;
        Ref<UniformBuffer> m_UniformBuffer;

        Ref<VertexArray> m_SpriteVAO;
        Ref<VertexBuffer> m_SpriteVBO;
        Ref<IndexBuffer> m_SpriteIBO;
        Ref<Shader> m_SpriteShader;

        vec4 m_Vertices[4];
        vec2 m_TexCoords[4];
        b8 m_Init, m_NDC;

        std::array<Ref<Texture>, PMAX_TEXTURE_SLOTS> m_TexSlots{};
        u32 m_TexIndex = 1, m_SpriteCount;

        SpriteVertex* m_SpritePtr;
        SpriteVertex* m_SpriteBase;

    public:
        Renderer2D() {}
        ~Renderer2D() { destroy(); }

        void 
        init(Ref<Device>& device, b8 ndc = false);

        void
        destroy();

        void
        setLayer(Layer layer = Layer::One);

        void
        drawRect(const Rect& rect);

        void
        drawRect(const Rect& rect, const Color& color);

        void
        drawSprite(const Rect& rect, const Ref<Texture>& texture);

        void
        begin();

        void
        end();

    private:
        void 
        initSprite();

        void 
        setProjectionMatrix(const mat4& projection);

        f32
        getTextureIndex(const Ref<Texture>& texture);

        void
        checkSpriteMax();
    };
    
} // namespace prime
