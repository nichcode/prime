
#include "prime/renderer/renderer2d.h"
#include "shader_sources.h"

#define MAX_SPRITES 10000
#define MAX_VERTICES MAX_SPRITES * 4
#define MAX_INDICES MAX_SPRITES * 6

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

        m_SpritePtr = nullptr;
        m_SpriteBase = nullptr;

        m_SpriteIndexCount = 0;
        m_DrawColor = Color(1.0f);
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
        rendererAPI->AddElement(m_SpriteLayout, prime::DataTypeFloat4);

        m_Vertices[0] = { 0.0f, 0.0f, 0.0f, 1.0f };
        m_Vertices[1] = { 1.0f, 0.0f, 0.0f, 1.0f };
        m_Vertices[2] = { 1.0f, 1.0f, 0.0f, 1.0f };
        m_Vertices[3] = { 0.0f, 1.0f, 0.0f, 1.0f };

        u32* indices = new u32[MAX_INDICES];
        u32 offset = 0;
        for (u32 i = 0; i < MAX_INDICES; i += 6)
        {
            indices[i + 0] = offset + 0;
            indices[i + 1] = offset + 1;
            indices[i + 2] = offset + 2;

            indices[i + 3] = offset + 2;
            indices[i + 4] = offset + 3;
            indices[i + 5] = offset + 0;

            offset += 4;
        }
        m_SpriteVAO = rendererAPI->createVertexArray();
        m_SpriteVBO = rendererAPI->createDynamicVertexBuffer(sizeof(Sprite) * MAX_VERTICES);
        m_SpriteIBO = rendererAPI->createIndexBuffer(indices, MAX_INDICES);
        m_SpriteBase = new Sprite[MAX_VERTICES];

        rendererAPI->setLayout(m_SpriteLayout);
        m_SpriteShader = rendererAPI->createShader(s_SpriteVertexSrc, s_SpritePixelSrc, false);
        m_UBO = rendererAPI->createUniformBuffer(sizeof(maths::mat4), 0);

        delete[] indices;
        m_SpritePtr = m_SpriteBase;
    }
    
    void Renderer2D::destroy()
    {
        if (m_SpriteBase) {
            delete[] m_SpriteBase;
            m_SpriteBase = nullptr;
        }
        
    }
    
    void Renderer2D::draw(const maths::vec2& pos)
    {
        draw(pos, { 50.0f, 50.0f });
    }

    void Renderer2D::draw(const maths::vec2& pos, const maths::vec2& size)
    {
        maths::mat4 transform = maths::mat4::translate({ pos.x, pos.y, 0.0f }) * 
            maths::mat4::scale({ size.x, size.y, 1.0f });

        for (size_t i = 0; i < 4; i++)
		{
            maths::vec4 position = transform * m_Vertices[i];
			m_SpritePtr->position.x = position.x;
			m_SpritePtr->position.y = position.y;

            m_SpritePtr->color = m_DrawColor;

			m_SpritePtr++;
		}
        m_SpriteIndexCount += 6;
    }
    
    void Renderer2D::flush(const Camera2D& camera)
    {
        m_API->setUniformBuffer(m_UBO);
        m_Projection = camera.getProjectionMatrix();
        m_API->setUniformBufferData(m_UBO, &m_Projection, sizeof(maths::mat4));

        if (m_SpriteIndexCount) {
            u32 size = (u32)((u8*)m_SpritePtr - (u8*)m_SpriteBase);
            m_API->setVertexBuffer(m_SpriteVBO);
            m_API->setVertexBufferData(m_SpriteVBO, m_SpriteBase, size);

            m_API->setShader(m_SpriteShader);
            m_API->submit(prime::DrawTypeElements, prime::DrawModeTriangles, m_SpriteIndexCount);
        }

        reset();
    }

    void Renderer2D::reset()
    {
        m_SpritePtr = m_SpriteBase;
        m_SpriteIndexCount = 0;
    }
      
} // namespace prime::renderer
