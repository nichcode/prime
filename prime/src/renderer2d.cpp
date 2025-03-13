
#include "prime/renderer/renderer2d.h"
#include "shader_sources.h"
#include "prime/maths/maths.h"

#define MAX_SPRITES 10000
#define MAX_VERTICES MAX_SPRITES * 4
#define MAX_INDICES MAX_SPRITES * 6

namespace prime::renderer {

    Renderer2D::Renderer2D()
    {
        m_API = nullptr;
        m_SpritePtr = nullptr;
        m_SpriteBase = nullptr;

        m_SpriteIndexCount = 0;
        m_TextureIndex = 1.0f;
        m_DrawColor = Color(1.0f);
        m_TintColor = Color(1.0f);
    }

    Renderer2D::~Renderer2D()
    {
        destroy();
    }

    void Renderer2D::init(core::Scope<RendererAPI>& API)
    {
        m_API = API.get();
        
        // sprite
        Layout layout;
        layout.add(prime::DataTypeFloat2);
        layout.add(prime::DataTypeFloat4);
        layout.add(prime::DataTypeFloat2);
        layout.add(prime::DataTypeFloat);
        layout.process();

        m_Vertices[0] = { 0.0f, 0.0f, 0.0f, 1.0f };
        m_Vertices[1] = { 1.0f, 0.0f, 0.0f, 1.0f };
        m_Vertices[2] = { 1.0f, 1.0f, 0.0f, 1.0f };
        m_Vertices[3] = { 0.0f, 1.0f, 0.0f, 1.0f };

        m_TextureCoords[0] = { 0.0f, 0.0f };
        m_TextureCoords[1] = { 1.0f, 0.0f };
        m_TextureCoords[2] = { 1.0f, 1.0f };
        m_TextureCoords[3] = { 0.0f, 1.0f };

        m_TextureCoordsFlipX[0] = { 1.0f, 0.0f };
        m_TextureCoordsFlipX[1] = { 0.0f, 0.0f };
        m_TextureCoordsFlipX[2] = { 0.0f, 1.0f };
        m_TextureCoordsFlipX[3] = { 1.0f, 1.0f };

        m_TextureCoordsFlipY[0] = { 0.0f, 1.0f };
        m_TextureCoordsFlipY[1] = { 1.0f, 1.0f };
        m_TextureCoordsFlipY[2] = { 1.0f, 0.0f };
        m_TextureCoordsFlipY[3] = { 0.0f, 0.0f };

        m_TextureCoordsFlipXY[0] = { 1.0f, 1.0f };
        m_TextureCoordsFlipXY[1] = { 0.0f, 1.0f };
        m_TextureCoordsFlipXY[2] = { 0.0f, 0.0f };
        m_TextureCoordsFlipXY[3] = { 1.0f, 0.0f };

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
        m_SpriteVAO = API->createVertexArray();
        m_SpriteVBO = API->createDynamicVertexBuffer(sizeof(SpriteVertex) * MAX_VERTICES);
        m_SpriteIBO = API->createIndexBuffer(indices, MAX_INDICES);
        m_SpriteBase = new SpriteVertex[MAX_VERTICES];
        m_SpriteVAO->setLayout(layout);

        m_SpriteShader = API->createShader(s_SpriteVertexSrc, s_SpritePixelSrc, false);
        i32 samplers[PRIME_MAX_TEXTURE_SLOTS]{};
        for (u32 i = 0; i < PRIME_MAX_TEXTURE_SLOTS; i++) { samplers[i] = i; }
        m_SpriteShader->setIntArray("u_Textures", samplers, PRIME_MAX_TEXTURE_SLOTS);

        m_UBO = API->createUniformBuffer(sizeof(maths::mat4), 0);
        core::Ref<Texture> texture = API->createTexture(1, 1);
        m_Textures.push_back(texture);

        delete[] indices;
        m_SpritePtr = m_SpriteBase;
    }
    
    void Renderer2D::destroy()
    {
        if (m_SpriteBase) {
            delete[] m_SpriteBase;
            m_SpriteBase = nullptr;
        }
        m_Textures.clear();
    }

    void Renderer2D::setCamera(const Camera2D& camera)
    {
        m_UBO->bind();
        m_Projection = camera.getProjectionMatrix();
        m_UBO->setData(&m_Projection, sizeof(maths::mat4));
    }
    
    void Renderer2D::draw(const maths::vec2& pos)
    {
        draw(pos, { 50.0f, 50.0f });
    }

    void Renderer2D::draw(const maths::vec2& pos, const maths::vec2& size)
    {
        nextBatch();

        maths::mat4 transform = maths::mat4::translate({ pos.x, pos.y, 0.0f }) * 
            maths::mat4::scale({ size.x, size.y, 1.0f });

        for (size_t i = 0; i < 4; i++)
		{
            maths::vec4 position = transform * m_Vertices[i];
			m_SpritePtr->position.x = position.x;
			m_SpritePtr->position.y = position.y;

            m_SpritePtr->color = m_DrawColor;
            m_SpritePtr->texture = m_TextureCoords[i];
            m_SpritePtr->index = 0.0f;

			m_SpritePtr++;
		}
        m_SpriteIndexCount += 6;
    }

    void Renderer2D::draw(const maths::vec2& pos, const maths::vec2& size, f32 rotation, Anchor anchor)
    {
        if (rotation) {
            nextBatch();
            maths::vec2 origin;
            maths::mat4 transform;

            switch (anchor)
            {
            case AnchorCenter: {
                origin.x = size.x / 2.0f;
                origin.y = size.y / 2.0f;

                transform = maths::mat4::translate({ pos.x + origin.x, pos.y + origin.y, 0.0f }) *
                    maths::mat4::rotateZ(maths::toRadians(rotation)) *
                    maths::mat4::translate({ -origin.x, -origin.y, 0.0f }) *
                    maths::mat4::scale({ size.x, size.y, 1.0f });
                break;
            }             

            case AnchorTopLeft: {
                origin.x = 0.0f;
                origin.y = 0.0f;

                transform = maths::mat4::translate({ pos.x, pos.y, 0.0f }) *
                    maths::mat4::rotateZ(maths::toRadians(rotation)) *
                    maths::mat4::scale({ size.x, size.y, 1.0f });
                break;
            }

            } // end of swicth

            for (size_t i = 0; i < 4; i++)
            {
                maths::vec4 position = transform * m_Vertices[i];
                m_SpritePtr->position.x = position.x;
                m_SpritePtr->position.y = position.y;

                m_SpritePtr->color = m_DrawColor;
                m_SpritePtr->texture = m_TextureCoords[i];
                m_SpritePtr->index = 0.0f;

                m_SpritePtr++;
            }
            m_SpriteIndexCount += 6;
        }
        else {
            draw(pos, size);
        }
    }

    void Renderer2D::draw(const maths::vec2& pos, const maths::vec2& size, core::Ref<Texture>& Texture)
    {
        if (Texture) {
            nextBatch();

            maths::mat4 transform = maths::mat4::translate({ pos.x, pos.y, 0.0f }) * 
            maths::mat4::scale({ size.x, size.y, 1.0f });

            f32 index = getIndex(Texture);

            for (size_t i = 0; i < 4; i++)
            {
                maths::vec4 position = transform * m_Vertices[i];
                m_SpritePtr->position.x = position.x;
                m_SpritePtr->position.y = position.y;

                m_SpritePtr->color = m_TintColor;
                m_SpritePtr->texture = m_TextureCoords[i];
                m_SpritePtr->index = index;

                m_SpritePtr++;
            }
            m_SpriteIndexCount += 6;
        }
        else {
            draw(pos, size);
        }
    }

    void Renderer2D::draw(const maths::vec2& pos, const maths::vec2& size, core::Ref<Texture>& Texture, f32 rotation, Anchor anchor)
    {
        if (rotation) {
            nextBatch();
            maths::vec2 origin;
            maths::mat4 transform;

            switch (anchor)
            {
            case AnchorCenter: {
                origin.x = size.x / 2.0f;
                origin.y = size.y / 2.0f;

                transform = maths::mat4::translate({ pos.x + origin.x, pos.y + origin.y, 0.0f }) *
                    maths::mat4::rotateZ(maths::toRadians(rotation)) *
                    maths::mat4::translate({ -origin.x, -origin.y, 0.0f }) *
                    maths::mat4::scale({ size.x, size.y, 1.0f });
                break;
            }             

            case AnchorTopLeft: {
                origin.x = 0.0f;
                origin.y = 0.0f;

                transform = maths::mat4::translate({ pos.x, pos.y, 0.0f }) *
                    maths::mat4::rotateZ(maths::toRadians(rotation)) *
                    maths::mat4::scale({ size.x, size.y, 1.0f });
                break;
            }

            } // end of swicth

            if (Texture) {
                f32 index = getIndex(Texture);

                for (size_t i = 0; i < 4; i++)
                {
                    maths::vec4 position = transform * m_Vertices[i];
                    m_SpritePtr->position.x = position.x;
                    m_SpritePtr->position.y = position.y;

                    m_SpritePtr->color = m_TintColor;
                    m_SpritePtr->texture = m_TextureCoords[i];
                    m_SpritePtr->index = index;

                    m_SpritePtr++;
                }
                m_SpriteIndexCount += 6;
            }
            else {
                for (size_t i = 0; i < 4; i++)
                {
                    maths::vec4 position = transform * m_Vertices[i];
                    m_SpritePtr->position.x = position.x;
                    m_SpritePtr->position.y = position.y;

                    m_SpritePtr->color = m_DrawColor;
                    m_SpritePtr->texture = m_TextureCoords[i];
                    m_SpritePtr->index = 0.0f;

                    m_SpritePtr++;
                }
                m_SpriteIndexCount += 6;
            }
        }
        else {
            if (Texture) {
                draw(pos, size, Texture);
            }
            else {
                draw(pos, size);
            }
        }
    }

    void Renderer2D::draw(const maths::vec2& pos, const maths::vec2& size, core::Ref<Texture>& Texture, b8 flip_x, b8 flip_y)
    {
        if (Texture) {
            nextBatch();

            maths::mat4 transform = maths::mat4::translate({ pos.x, pos.y, 0.0f }) * 
            maths::mat4::scale({ size.x, size.y, 1.0f });

            f32 index = getIndex(Texture);

            for (size_t i = 0; i < 4; i++)
            {
                maths::vec4 position = transform * m_Vertices[i];
                m_SpritePtr->position.x = position.x;
                m_SpritePtr->position.y = position.y;
                m_SpritePtr->color = m_TintColor;

                if (flip_x && flip_y) {
                    m_SpritePtr->texture = m_TextureCoordsFlipXY[i];
                }
                else if (flip_x) {
                    m_SpritePtr->texture = m_TextureCoordsFlipX[i];
                }
                else if (flip_y) {
                    m_SpritePtr->texture = m_TextureCoordsFlipY[i];
                }
                else {
                    m_SpritePtr->texture = m_TextureCoords[i];
                }
                m_SpritePtr->index = index;
                m_SpritePtr++;
            }
            m_SpriteIndexCount += 6;
        }
        else {
            draw(pos, size);
        }
    }
    
    void Renderer2D::draw(const maths::vec2& pos, const maths::vec2& size, core::Ref<Texture>& Texture, b8 flip_x, b8 flip_y, f32 rotation, Anchor anchor)
    {
        if (rotation) {
            nextBatch();
            maths::vec2 origin;
            maths::mat4 transform;

            switch (anchor)
            {
            case AnchorCenter: {
                origin.x = size.x / 2.0f;
                origin.y = size.y / 2.0f;

                transform = maths::mat4::translate({ pos.x + origin.x, pos.y + origin.y, 0.0f }) *
                    maths::mat4::rotateZ(maths::toRadians(rotation)) *
                    maths::mat4::translate({ -origin.x, -origin.y, 0.0f }) *
                    maths::mat4::scale({ size.x, size.y, 1.0f });
                break;
            }             

            case AnchorTopLeft: {
                origin.x = 0.0f;
                origin.y = 0.0f;

                transform = maths::mat4::translate({ pos.x, pos.y, 0.0f }) *
                    maths::mat4::rotateZ(maths::toRadians(rotation)) *
                    maths::mat4::scale({ size.x, size.y, 1.0f });
                break;
            }

            } // end of swicth

            if (Texture) {
                f32 index = getIndex(Texture);

                for (size_t i = 0; i < 4; i++)
                {
                    maths::vec4 position = transform * m_Vertices[i];
                    m_SpritePtr->position.x = position.x;
                    m_SpritePtr->position.y = position.y;
                    m_SpritePtr->color = m_TintColor;

                    if (flip_x && flip_y) {
                        m_SpritePtr->texture = m_TextureCoordsFlipXY[i];
                    }
                    else if (flip_x) {
                        m_SpritePtr->texture = m_TextureCoordsFlipX[i];
                    }
                    else if (flip_y) {
                        m_SpritePtr->texture = m_TextureCoordsFlipY[i];
                    }
                    else {
                        m_SpritePtr->texture = m_TextureCoords[i];
                    }
                    m_SpritePtr->index = index;
                    m_SpritePtr++;
                }
                m_SpriteIndexCount += 6;
            }
            else {
                for (size_t i = 0; i < 4; i++)
                {
                    maths::vec4 position = transform * m_Vertices[i];
                    m_SpritePtr->position.x = position.x;
                    m_SpritePtr->position.y = position.y;

                    m_SpritePtr->color = m_DrawColor;
                    m_SpritePtr->texture = m_TextureCoords[i];
                    m_SpritePtr->index = 0.0f;

                    m_SpritePtr++;
                }
                m_SpriteIndexCount += 6;
            }
        }
        else {
            if (Texture) {
                draw(pos, size, Texture, flip_x, flip_y);
            }
            else {
                draw(pos, size);
            }
        }
    }
    
    void Renderer2D::flush()
    {
        if (m_SpriteIndexCount) {
            u32 size = (u32)((u8*)m_SpritePtr - (u8*)m_SpriteBase);
            m_SpriteVBO->bind();
            m_SpriteVBO->setData(m_SpriteBase, size);

            for (u32 i = 0; i < m_TextureIndex; i++) {
                m_Textures[i]->bind(i);
            }

            m_SpriteShader->bind();
            m_API->submit(prime::DrawTypeElements, prime::DrawModeTriangles, m_SpriteIndexCount);
        }

        reset();
    }

    void Renderer2D::reset()
    {
        m_SpritePtr = m_SpriteBase;
        m_SpriteIndexCount = 0;
        m_TextureIndex = 1.0f;
    }

    f32 Renderer2D::getIndex(core::Ref<Texture>& texture)
    {
        f32 tex_index = 0.0f;
        for (u32 i = 1; i < m_TextureIndex; i++) {
            if (m_Textures[i] == texture) {
                tex_index = (f32)i;
                break;
            }
        }

        if (tex_index == 0.0f) {
            tex_index = m_TextureIndex;
            m_Textures.push_back(texture);
            m_TextureIndex++;
        }

        return tex_index;
    }

    void Renderer2D::nextBatch()
    {
        if (m_SpriteIndexCount >= MAX_INDICES) {
            flush();
            reset();
        }
    }
      
} // namespace prime::renderer
