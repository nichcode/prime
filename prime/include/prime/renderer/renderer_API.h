
#pragma once

#include "prime/core/scope.h"
#include "prime/core/window.h"
#include "color.h"
#include "prime/maths/mat4.h"

namespace prime::renderer {

    PRIME_HANDLE(VertexArray);
    PRIME_HANDLE(VertexBuffer);
    PRIME_HANDLE(IndexBuffer);
    PRIME_HANDLE(Layout);
    PRIME_HANDLE(Shader);
    PRIME_HANDLE(Texture);

    struct Viewport
    {
        i32 x = 0;
        i32 y = 0;
        u32 width = 0;
        u32 height = 0;
    };

    class RendererAPI
    {
    public:
        virtual ~RendererAPI() = default;

        virtual VertexArray* createVertexArray() = 0;
        virtual void deleteVertexArray(VertexArray* vertex_array) = 0;

        virtual VertexBuffer* createStaticVertexBuffer(f32* vertices, u32 size) = 0;
        virtual VertexBuffer* createDynamicVertexBuffer(u32 size) = 0; 
        virtual void deleteVertexBuffer(VertexBuffer* vertex_buffer) = 0;

        virtual IndexBuffer* createIndexBuffer(u32* indices, u32 count) = 0;
        virtual void deleteIndexBuffer(IndexBuffer* index_buffer) = 0;

        virtual Layout* createLayout() = 0;
        virtual void deleteLayout(Layout* layout) = 0;
        virtual void AddElement(Layout* layout, DataType type, u32 divisor = 0, b8 normalize = false) = 0;

        virtual Shader* createShader(const str& vertex, const str& pixel, b8 load = true, SourceType type = SourceTypeGLSL) = 0;
        virtual void deleteShader(Shader* shader) = 0;

        virtual Texture* loadTexture(const str& filepath) = 0;
        virtual Texture* createTexture(u32 width, u32 height, b8 target = false, TextureFormat format = TextureFormatRGBA8) = 0;
        virtual void deleteTexture(Texture* texture) = 0;

        virtual void makeActive() = 0;
        virtual void clear() = 0;
        virtual void present() = 0;

        virtual void submit(DrawType type, DrawMode mode, u32 count) = 0;

        virtual void setClearColor(const Color& color) = 0;
        virtual void setVertexBufferData(const VertexBuffer* vertex_buffer, const void* data, u32 size) = 0;
        virtual void setVsync(b8 vsync = true) = 0;
        virtual void setViewport(const Viewport& viewport) = 0;

        virtual void setVertexArray(const VertexArray* vertex_array) = 0;
        virtual void setVertexBuffer(const VertexBuffer* vertex_buffer) = 0;
        virtual void setIndexBuffer(const IndexBuffer* index_buffer) = 0;
        virtual void setLayout(Layout* layout) = 0;
        virtual void setShader(Shader* shader) = 0;
        virtual void setTexture(Texture* texture, u32 slot = 0) = 0;
        
        virtual void setRenderTarget(Texture* texture) = 0;

        virtual void upload(const Shader* shader, const char* name, i32 data) = 0;
        virtual void upload(const Shader* shader, const char* name, i32* data, u32 count) = 0;
        virtual void upload(const Shader* shader, const char* name, f32 data) = 0;
        virtual void upload(const Shader* shader, const char* name, maths::vec2 data) = 0;
        virtual void upload(const Shader* shader, const char* name, maths::vec3 data) = 0;
        virtual void upload(const Shader* shader, const char* name, maths::vec4 data) = 0;
        virtual void upload(const Shader* shader, const char* name, maths::mat4 data) = 0;

        virtual GraphicsAPI getAPI() const = 0;
        virtual const Viewport& getViewport() const = 0;
        virtual u32 getIndexBufferCount(const IndexBuffer* index_buffer) const = 0;
    };
    
} // namespace prime::renderer