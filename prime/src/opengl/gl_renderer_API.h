
#pragma once

#include "prime/renderer/renderer_API.h"
#include "context_API.h"

#include <vector>

namespace prime::renderer {

    class GLRendererAPI : public RendererAPI
    {
    private:
        core::Scope<ContextAPI> m_Context;

        std::vector<VertexArray*> m_VertexArrays;
        std::vector<VertexBuffer*> m_VertexBuffers;
        std::vector<IndexBuffer*> m_IndexBuffers;
        std::vector<Layout*> m_Layouts;
        std::vector<Shader*> m_Shaders;
        std::vector<Texture*> m_Textures;

        u32 m_Index;
        Viewport m_Viewport;

    public:
        GLRendererAPI(const core::Scope<core::Window>& window);
        virtual ~GLRendererAPI() override;

        virtual VertexArray* createVertexArray() override;
        virtual void deleteVertexArray(VertexArray* vertex_array) override;

        virtual VertexBuffer* createStaticVertexBuffer(f32* vertices, u32 size) override;
        virtual VertexBuffer* createDynamicVertexBuffer(u32 size) override; 
        virtual void deleteVertexBuffer(VertexBuffer* vertex_buffer) override;

        virtual IndexBuffer* createIndexBuffer(u32* indices, u32 count) override;
        virtual void deleteIndexBuffer(IndexBuffer* index_buffer) override;

        virtual Layout* createLayout() override;
        virtual void deleteLayout(Layout* layout) override;
        virtual void AddElement(Layout* layout, DataType type, u32 divisor, b8 normalize) override;

        virtual Shader* createShader(const str& vertex, const str& pixel, b8 load, SourceType type) override;
        virtual void deleteShader(Shader* shader) override;

        virtual Texture* loadTexture(const str& filepath) override;
        virtual Texture* createTexture(u32 width, u32 height, b8 target, TextureFormat format) override;
        virtual void deleteTexture(Texture* texture) override;

        virtual void makeActive() override;
        virtual void clear() override;
        virtual void present() override;

        virtual void submit(DrawType type, DrawMode mode, u32 count) override;

        virtual void setClearColor(const Color& color) override;
        virtual void setVertexBufferData(const VertexBuffer* vertex_buffer, const void* data, u32 size) override;
        virtual void setVsync(b8 vsync = true) override;
        virtual void setViewport(const Viewport& viewport) override;

        virtual void setVertexArray(const VertexArray* vertex_array) override;
        virtual void setVertexBuffer(const VertexBuffer* vertex_buffer) override;
        virtual void setIndexBuffer(const IndexBuffer* index_buffer) override;
        virtual void setLayout(Layout* layout) override;
        virtual void setShader(Shader* shader) override;
        virtual void setTexture(Texture* texture, u32 slot) override;

        virtual void setRenderTarget(Texture* texture) override;

        virtual void upload(const Shader* shader, const char* name, i32 data) override;
        virtual void upload(const Shader* shader, const char* name, i32* data, u32 count) override;
        virtual void upload(const Shader* shader, const char* name, f32 data) override;
        virtual void upload(const Shader* shader, const char* name, maths::vec2 data) override;
        virtual void upload(const Shader* shader, const char* name, maths::vec3 data) override;
        virtual void upload(const Shader* shader, const char* name, maths::vec4 data) override;
        virtual void upload(const Shader* shader, const char* name, maths::mat4 data) override;

        virtual GraphicsAPI getAPI() const override { return GraphicsAPIGL; }
        virtual const Viewport& getViewport() const override { return m_Viewport; }
        virtual u32 getIndexBufferCount(const IndexBuffer* index_buffer) const override;
    };
    
} // namespace prime::renderer