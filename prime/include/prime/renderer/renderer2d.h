
#include "prime/renderer/renderer_API.h"
#include "prime/renderer/camera2d.h"

namespace prime::renderer {

    class Renderer2D
    {
    private:
        RendererAPI* m_API;
        VertexArray* m_SpriteVAO;
        VertexBuffer* m_SpriteVBO;
        IndexBuffer* m_SpriteIBO;
        Shader* m_SpriteShader;
        Layout* m_SpriteLayout;
        UniformBuffer* m_UBO;

        u32 m_SpriteCount;
        maths::mat4 m_Projection;

    public:
        Renderer2D();
        ~Renderer2D();

        void init(RendererAPI* rendererAPI);
        void destroy();

        void draw(const maths::vec2& position);

        void flush(const Camera2D& camera);
    };
    
} // namespace prime::renderer
