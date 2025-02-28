
#include "prime/renderer2d.h"
#include "prime/math.h"
#include "prime/logger.h"
#include "shader_sources.h"
#include "prime/platform.h"

#define MAX_SPRITES 10000
#define MAX_VERTICES MAX_SPRITES * 4
#define MAX_INDICES MAX_SPRITES * 6

namespace prime {

    PINLINE f32 
    getLayer(Layer& layer)
    {
        switch (layer)
        {
            case Layer::One: {
                return 0.0f;
                break;
            }

            case Layer::Two: {
                return -0.1f;
                break;
            }

            case Layer::Three: {
                return -0.2f;
                break;
            }

            case Layer::Four: {
                return -0.3f;
                break;
            }

            case Layer::Five: {
                return -0.4f;
                break;
            }

            case Layer::Six: {
                return -0.5f;
                break;
            }

            case Layer::Seven: {
                return -0.6f;
                break;
            }

            case Layer::Eight: {
                return -0.7f;
                break;
            }

            case Layer::Nine: {
                return -0.8f;
                break;
            }

            case Layer::Ten: {
                return -0.9f;
                break;
            }
        }
        return 0.0f;
    }

    void 
    Renderer2D::init(Ref<Device>& device, b8 ndc)
    {
        PASSERT_MSG(device.get(), "device is null");
        m_Device = device;
        m_NDC = ndc;
        initSprite();

        m_UniformBuffer = m_Device->createUniformBuffer(sizeof(mat4), 0);
        m_Init = true;
        m_Layer = Layer::One;
    }

    void 
    Renderer2D::destroy()
    {
        if (m_Init) {
            delete[] m_SpriteBase;
            m_Init = false;
        }
    }

    void
    Renderer2D::setLayer(Layer layer)
    {
        m_Layer = layer;
    }

    void 
    Renderer2D::begin()
    {
        m_SpritePtr = m_SpriteBase;
        m_SpriteCount = 0;
        m_TexIndex = 1;

        mat4 matrix = mat4::identity();
        if (m_NDC == false) {
            const Rect view = m_Device->getViewport();
            matrix = mat4::orthographic(view.x, view.width, view.height, view.y, -1.0f, 1.0f);
        }
        setProjectionMatrix(matrix);
    }

    void 
    Renderer2D::end()
    {
        if (m_SpriteCount) {
            u32 size = (u32)((u8*)m_SpritePtr - (u8*)m_SpriteBase);
            m_Device->setVertexBuffer(m_SpriteVBO);
            m_SpriteVBO->setData(m_SpriteBase, size);

            for (u32 i = 0; i < m_TexIndex; i++) {
                m_Device->setTexture(m_TexSlots[i], i);
            }

            m_Device->setShader(m_SpriteShader);
            m_Device->drawElements(DrawMode::Triangles, m_SpriteCount);
        }   
    }

    void 
    Renderer2D::drawRect(const Rect& rect)
    {
        drawRect(rect, { 1.0f, 1.0f, 1.0f, 1.0f });
    }

    void
    Renderer2D::drawRect(const Rect& rect, const Color& color)
    {
        checkSpriteMax();

        mat4 translation = mat4::translate({ rect.x, rect.y, 0.0f });
        mat4 scale = mat4::scale({ rect.width, rect.height, 1.0f });
        mat4 transform = translation * scale;

        for (size_t i = 0; i < 4; i++)
		{
            vec4 pos = transform * m_Vertices[i];
			m_SpritePtr->pos.x = pos.x;
			m_SpritePtr->pos.y = pos.y;

            m_SpritePtr->pos.z = getLayer(m_Layer);
            m_SpritePtr->color = color;

            m_SpritePtr->texCoords = m_TexCoords[i];
            m_SpritePtr->texIndex = 0.0f;

			m_SpritePtr++;
		}
        m_SpriteCount += 6;
    }

    void 
    Renderer2D::drawSprite(const Rect& rect, const Ref<Texture>& texture)
    {
        checkSpriteMax();

        mat4 translation = mat4::translate({ rect.x, rect.y, 0.0f });
        mat4 scale = mat4::scale({ rect.width, rect.height, 1.0f });
        mat4 transform = translation * scale;

        f32 tex_index = 0.0f;
        if (texture.get()) {
            tex_index = getTextureIndex(texture);
        }

        for (size_t i = 0; i < 4; i++)
		{
            vec4 pos = transform * m_Vertices[i];
			m_SpritePtr->pos.x = pos.x;
			m_SpritePtr->pos.y = pos.y;

            m_SpritePtr->pos.z = getLayer(m_Layer);
            m_SpritePtr->color = { 1.0f, 1.0f, 1.0f, 1.0f };

            m_SpritePtr->texCoords = m_TexCoords[i];
            m_SpritePtr->texIndex = tex_index;

			m_SpritePtr++;
		}
        m_SpriteCount += 6;
    }

    void 
    Renderer2D::initSprite()
    {
        if (m_NDC) {
            m_Vertices[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
            m_Vertices[1] = {  0.5f, -0.5f, 0.0f, 1.0f };
            m_Vertices[2] = {  0.5f,  0.5f, 0.0f, 1.0f };
            m_Vertices[3] = { -0.5f,  0.5f, 0.0f, 1.0f };

            m_TexCoords[0] = { 0.0f, 1.0f };
            m_TexCoords[1] = { 1.0f, 1.0f };
            m_TexCoords[2] = { 1.0f, 0.0f };
            m_TexCoords[3] = { 0.0f, 0.0f };
        }
        else {
            m_Vertices[0] = { 0.0f, 0.0f, 0.0f, 1.0f };
            m_Vertices[1] = { 1.0f, 0.0f, 0.0f, 1.0f };
            m_Vertices[2] = { 1.0f, 1.0f, 0.0f, 1.0f };
            m_Vertices[3] = { 0.0f, 1.0f, 0.0f, 1.0f };

            m_TexCoords[0] = { 0.0f, 0.0f };
            m_TexCoords[1] = { 1.0f, 0.0f };
            m_TexCoords[2] = { 1.0f, 1.0f };
            m_TexCoords[3] = { 0.0f, 1.0f };
        }
        
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

        Layout layout;
        layout.addElement(Type::Float3);
        layout.addElement(Type::Float4);
        layout.addElement(Type::Float2);
        layout.addElement(Type::Float);
        layout.process();

        m_SpriteVAO = m_Device->createVertexArray();

        m_SpriteVBO = m_Device->createDynamicVertexBuffer(MAX_VERTICES * sizeof(SpriteVertex));
        m_SpriteVBO->setLayout(layout);
        m_SpriteBase = new SpriteVertex[MAX_VERTICES];

        m_SpriteIBO = m_Device->createIndexBuffer(indices, MAX_INDICES);

        m_Device->setVertexBuffer(m_SpriteVBO);
        m_SpriteVAO->submit(m_SpriteVBO);

        ShaderDesc shader_desc;
        shader_desc.load = false;
        shader_desc.vertex = s_SpriteVertexSource;
        shader_desc.pixel = s_SpritePixelSource;
        shader_desc.type = ShaderSourceType::GLSL;

        m_SpriteShader = m_Device->createShader(shader_desc);
        m_TexSlots[0] = m_Device->createTexture(1, 1, TextureUsage::None);

        m_Device->setShader(m_SpriteShader);
        i32 samplers[PMAX_TEXTURE_SLOTS]{};
        for (u32 i = 0; i < PMAX_TEXTURE_SLOTS; i++) { samplers[i] = i; }
        m_SpriteShader->setIntArray("u_Textures", samplers, PMAX_TEXTURE_SLOTS);
            
            delete[] indices;
        }

    void 
    Renderer2D::setProjectionMatrix(const mat4& projection)
    {
        m_Device->setUniformBuffer(m_UniformBuffer);
        m_UniformBuffer->setData(&projection, sizeof(mat4));
    }

    f32 
    Renderer2D::getTextureIndex(const Ref<Texture>& texture)
    {
        f32 tex_index = 0.0f;
        for (u32 i = 1; i < m_TexIndex; i++) {
            if (m_TexSlots[i]->getHandle() == texture->getHandle()) {
                tex_index = (f32)i;
                break;
            }
        }

        if (tex_index == 0.0f) {
            tex_index = (f32)m_TexIndex;
            m_TexSlots[m_TexIndex] = texture;
            m_TexIndex++;
        }

        return tex_index;
    }

    void 
    Renderer2D::checkSpriteMax()
    {
        if (m_SpriteCount >= MAX_INDICES) {
            end();
            m_SpritePtr = m_SpriteBase;
            m_SpriteCount = 0;
        }
    }
    
    
} // namespace prime
