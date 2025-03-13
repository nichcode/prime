
#pragma once

#include "prime/core/scope.h"
#include "prime/core/window.h"
#include "color.h"
#include "viewport.h"
#include "prime/core/ref.h"

#include "vertex_array.h"
#include "buffers.h"
#include "shader.h"
#include "texture.h"

namespace prime::renderer {

    class RendererAPI
    {
    public:
        virtual ~RendererAPI() = default;

        virtual core::Ref<VertexArray> createVertexArray() = 0;

        virtual core::Ref<VertexBuffer> createStaticVertexBuffer(f32* vertices, u32 size) = 0;
        virtual core::Ref<VertexBuffer> createDynamicVertexBuffer(u32 size) = 0;
        virtual core::Ref<IndexBuffer> createIndexBuffer(u32* indices, u32 count) = 0;
        virtual core::Ref<UniformBuffer> createUniformBuffer(u32 size, u32 binding = 0) = 0;

        virtual core::Ref<Shader> createShader(const str& vertex, const str& pixel, b8 load = true, SourceType type = SourceTypeGLSL) = 0;
        virtual core::Ref<Texture> createTexture(u32 width, u32 height, b8 target = false, TextureFormat format = TextureFormatRGBA8) = 0;
        virtual core::Ref<Texture> loadTexture(const str& filepath) = 0;

        virtual void makeActive() = 0;
        virtual void clear() = 0;
        virtual void present() = 0;

        virtual void submit(DrawType type, DrawMode mode, u32 count) = 0;

        virtual void setClearColor(const Color& color) = 0;
        virtual void setVsync(b8 vsync = true) = 0;
        virtual void setViewport(const Viewport& viewport) = 0;

        virtual GraphicsAPI getAPI() const = 0;
        virtual const Viewport& getViewport() const = 0;
    };
    
} // namespace prime::renderer