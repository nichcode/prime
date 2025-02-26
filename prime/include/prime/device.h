
#pragma once

#include "context.h"

namespace prime {

    enum class DeviceType
    {
        OpenGL
    };

    class Device
    {
    private:
        DeviceType m_Type;

    public:
        void 
        init(DeviceType type);

        Ref<Context> 
        createContext(const Window& window);

        Ref<VertexArray>
        createVertexArray();

        Ref<VertexBuffer>
        createDynamicVertexBuffer(u32 size);

        Ref<VertexBuffer>
        createStaticVertexBuffer(f32* vertices, u32 size);

        Ref<IndexBuffer>
        createIndexBuffer(u32* indices, u32 count);

        Ref<Shader>
        createShader(const ShaderDesc& desc);

        Ref<Texture>
        createTexture(u32 width, u32 height, TextureUsage usage);

        Ref<Texture>
        createTexture(const str& filepath);
    };
    
} // namespace prime
