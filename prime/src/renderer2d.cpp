
#include "prime/renderer2d.h"
#include "prime/math.h"
#include "prime/logger.h"
#include "shader_sources.h"

#define MAX_SPRITES 10000
#define MAX_VERTICES MAX_SPRITES * 4
#define MAX_INDICES MAX_SPRITES * 6

#include <array>

namespace prime {

    struct Sprite
    {
        vec3 pos;
        Color color;
    };

    struct SpriteData
    {
        Ref<VertexArray> vAO;
        Ref<VertexBuffer> vBO;
        Ref<IndexBuffer> iBO;
        Ref<Shader> shader;

        vec4 vertices[4];

        std::array<Ref<Texture>, PMAX_TEXTURE_SLOTS> texSlots{};
        u32 texIndex = 1, count;

        Sprite* ptr;
        Sprite* base;
    };

    struct Renderer2DData
    {
        Ref<Device> device;
        SpriteData sprite;
    };

    static Renderer2DData s_Ren2DData;

    static void
    initSprites(Ref<Device>& device)
    {
        PASSERT_MSG(device.get(), "device is null");

        s_Ren2DData.sprite.vertices[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
        s_Ren2DData.sprite.vertices[1] = {  0.5f, -0.5f, 0.0f, 1.0f };
        s_Ren2DData.sprite.vertices[2] = {  0.5f,  0.5f, 0.0f, 1.0f };
        s_Ren2DData.sprite.vertices[3] = { -0.5f,  0.5f, 0.0f, 1.0f };

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
        layout.process();

        s_Ren2DData.sprite.vAO = device->createVertexArray();

        s_Ren2DData.sprite.vBO = device->createDynamicVertexBuffer(MAX_VERTICES * sizeof(Sprite));
        s_Ren2DData.sprite.vBO->setLayout(layout);
        s_Ren2DData.sprite.base = new Sprite[MAX_VERTICES];

        s_Ren2DData.sprite.iBO = device->createIndexBuffer(indices, MAX_INDICES);

        device->setVertexBuffer(s_Ren2DData.sprite.vBO);
        s_Ren2DData.sprite.vAO->submit(s_Ren2DData.sprite.vBO);

        ShaderDesc shader_desc;
        shader_desc.load = false;
        shader_desc.vertex = s_SpriteVertexSource;
        shader_desc.pixel = s_SpritePixelSource;
        shader_desc.type = ShaderSourceType::GLSL;

        s_Ren2DData.sprite.shader = device->createShader(shader_desc);
        s_Ren2DData.sprite.texSlots[0] = device->createTexture(1, 1, TextureUsage::None);
        
        delete[] indices;
    }

    void 
    Renderer2D::init(Ref<Device>& device)
    {
        s_Ren2DData.device = device;
        initSprites(device);
    }

    void 
    Renderer2D::destroy()
    {
        delete[] s_Ren2DData.sprite.base;
    }

    void 
    Renderer2D::begin()
    {
        s_Ren2DData.sprite.ptr = s_Ren2DData.sprite.base;
        s_Ren2DData.sprite.count = 0;
        s_Ren2DData.sprite.texIndex = 1;
    }

    void 
    Renderer2D::end()
    {
        if (s_Ren2DData.sprite.count) {
            u32 size = (u32)((u8*)s_Ren2DData.sprite.ptr - (u8*)s_Ren2DData.sprite.base);
            s_Ren2DData.device->setVertexBuffer(s_Ren2DData.sprite.vBO);
            s_Ren2DData.sprite.vBO->setData(s_Ren2DData.sprite.base, size);

            s_Ren2DData.device->setShader(s_Ren2DData.sprite.shader);
            s_Ren2DData.device->drawElements(DrawMode::Triangles, s_Ren2DData.sprite.count);
        }   
    }

    void 
    Renderer2D::drawRect(const Rect& rect, f32 layer)
    {
        drawRect(rect, { 1.0f, 1.0f, 1.0f, 1.0f }, layer);
    }

    void
    Renderer2D::drawRect(const Rect& rect, const Color& color, f32 layer)
    {
        mat4 translation = mat4::translate({ rect.x, rect.y, 0.0f });
        mat4 scale = mat4::scale({ rect.width, rect.height, 1.0f });
        mat4 transform = translation * scale;

        for (size_t i = 0; i < 4; i++)
		{
            vec4 pos = transform * s_Ren2DData.sprite.vertices[i];
			s_Ren2DData.sprite.ptr->pos.x = pos.x;
			s_Ren2DData.sprite.ptr->pos.y = pos.y;

            s_Ren2DData.sprite.ptr->pos.z = -layer / 10.0f;

            s_Ren2DData.sprite.ptr->color = color;

			s_Ren2DData.sprite.ptr++;
		}
        s_Ren2DData.sprite.count += 6;
    }
    
} // namespace prime
