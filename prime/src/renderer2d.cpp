
#include "prime/renderer/renderer2d.h"
#include "shader_sources.h"

namespace prime::renderer {

    Renderer2D::Renderer2D()
    {
        m_API = nullptr;
        m_SpriteVAO = nullptr;
        m_SpriteVBO = nullptr;
        m_SpriteIBO = nullptr;
        m_SpriteShader = nullptr;
        m_SpriteLayout = nullptr;
        m_UBO = nullptr;

        m_SpriteCount = 0;
    }

    Renderer2D::~Renderer2D()
    {
        destroy();
    }

    void Renderer2D::init(RendererAPI* rendererAPI)
    {
        m_API = rendererAPI;

        // sprite
        m_SpriteLayout = rendererAPI->createLayout();
        rendererAPI->AddElement(m_SpriteLayout, prime::DataTypeFloat2);

        f32 vertices[] = {
            0.0f, 0.0f,
            50.0f, 0.0f,
            50.0f, 50.0f,
            0.0f, 50.0f
        };

        u32 indices[] = { 0, 1, 2, 2, 3, 0 };

        m_SpriteVAO = rendererAPI->createVertexArray();
        m_SpriteVBO = rendererAPI->createStaticVertexBuffer(vertices, sizeof(vertices));
        m_SpriteIBO = rendererAPI->createIndexBuffer(indices, 6);

        rendererAPI->setLayout(m_SpriteLayout);
        m_SpriteShader = rendererAPI->createShader(s_SpriteVertexSrc, s_SpritePixelSrc, false);
        m_UBO = rendererAPI->createUniformBuffer(sizeof(maths::mat4), 0);
    }
    
    void Renderer2D::destroy()
    {
        
    }
    
    void Renderer2D::draw(const maths::vec2& position)
    {
        m_SpriteCount++;
    }
    
    void Renderer2D::flush(const Camera2D& camera)
    {
        m_API->setUniformBuffer(m_UBO);
        m_Projection = camera.getProjectionMatrix();
        m_API->setUniformBufferData(m_UBO, &m_Projection, sizeof(maths::mat4));

        //camera.getProjectionMatrix();
        if (m_SpriteCount) {
            m_API->setShader(m_SpriteShader);
            m_API->submit(prime::DrawTypeElements, prime::DrawModeTriangles, 6);
        }
    }
    
} // namespace prime::renderer
