
#include "prime/renderer/renderer_API.h"
#include "prime/renderer/camera2d.h"
#include <vector>

namespace prime::renderer {

    class Renderer2D
    {
    private:
        struct Sprite
        {
            maths::vec2 position;
            Color color;
            maths::vec2 texture;
            f32 index = 0.0f;
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
        maths::vec2 m_TextureCoords[4];
        maths::vec2 m_TextureCoordsFlipX[4];
        maths::vec2 m_TextureCoordsFlipY[4];
        maths::vec2 m_TextureCoordsFlipXY[4];
        Sprite* m_SpritePtr;
        Sprite* m_SpriteBase;

        u32 m_SpriteIndexCount;
        maths::mat4 m_Projection;

        Color m_DrawColor;
        Color m_TintColor;

        std::vector<Texture*> m_Textures;
        f32 m_TextureIndex;

    public:
        Renderer2D();
        ~Renderer2D();

        void init(RendererAPI* rendererAPI);
        void destroy();

        void setDrawColor(const Color& color) { m_DrawColor = color; }
        void setTintColor(const Color& color) { m_TintColor = color; }
        void setCamera(const Camera2D& camera);

        void draw(const maths::vec2& pos);
        void draw(const maths::vec2& pos, const maths::vec2& size);
        void draw(const maths::vec2& pos, const maths::vec2& size, f32 rotation, Anchor anchor = AnchorCenter);

        void draw(const maths::vec2& pos, const maths::vec2& size, Texture* Texture);
        void draw(const maths::vec2& pos, const maths::vec2& size, Texture* Texture, f32 rotation, Anchor anchor = AnchorCenter);
        void draw(const maths::vec2& pos, const maths::vec2& size, Texture* Texture, b8 flip_x, b8 flip_y);
        void draw(const maths::vec2& pos, const maths::vec2& size, Texture* Texture, b8 flip_x, b8 flip_y, f32 rotation, Anchor anchor = AnchorCenter);

        void flush();

    private:
        void reset();
        f32 getIndex(Texture* texture);
        void nextBatch();
    };
    
} // namespace prime::renderer
