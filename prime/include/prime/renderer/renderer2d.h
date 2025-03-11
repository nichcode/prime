
#include "prime/renderer/renderer_API.h"
#include "prime/renderer/camera2d.h"

namespace prime::renderer {

    class Renderer2D
    {
    private:
        struct Sprite
        {
            maths::vec2 position;
            Color color;
        };

    private:
        RendererAPI* m_API;
        VertexArray* m_SpriteVAO;
        VertexBuffer* m_SpriteVBO;
        IndexBuffer* m_SpriteIBO;
        Shader* m_SpriteShader;
        Layout* m_SpriteLayout;
        UniformBuffer* m_UBO;

        maths::vec4 m_Vertices[4];
        Sprite* m_SpritePtr;
        Sprite* m_SpriteBase;

        u32 m_SpriteIndexCount;
        maths::mat4 m_Projection;

        Color m_DrawColor;

    public:
        Renderer2D();
        ~Renderer2D();

        void init(RendererAPI* rendererAPI);
        void destroy();

        void setDrawColor(const Color& color) { m_DrawColor = color; }

        void draw(const maths::vec2& pos);
        void draw(const maths::vec2& pos, const maths::vec2& size);

        void flush(const Camera2D& camera);

    private:
        void reset();
    };
    
} // namespace prime::renderer
