
#include "prime/device.h"
#include "prime/logger.h"

#include "opengl/opengl_context.h"
#include "opengl/opengl_buffers.h"
#include "opengl/opengl_vertex_array.h"
#include "opengl/opengl_shader.h"
#include "opengl/opengl_textures.h"

namespace prime {

    void 
    Device::init(DeviceType type)
    {
        m_Type = type;
    }

    Ref<Context> 
    Device::createContext(const Window& window)
    {
        switch (m_Type)
        {
            case DeviceType::OpenGL: {
                return createRef<GLContext>(window);
            }
            break;
        }
        return nullptr;
    }

    Ref<VertexArray> 
    Device::createVertexArray()
    {
        switch (m_Type)
        {
            case DeviceType::OpenGL: {
                return createRef<GLVertexArray>();
            }
            break;
        }
        return nullptr;
    }

    Ref<VertexBuffer> 
    Device::createDynamicVertexBuffer(u32 size)
    {
        switch (m_Type)
        {
            case DeviceType::OpenGL: {
                return createRef<GLVertexBuffer>(size);
            }
            break;
        }
        return nullptr;   
    }

    Ref<VertexBuffer> 
    Device::createStaticVertexBuffer(f32* vertices, u32 size)
    {
        switch (m_Type)
        {
            case DeviceType::OpenGL: {
                return createRef<GLVertexBuffer>(vertices, size);
            }
            break;
        }
        return nullptr;   
    }

    Ref<IndexBuffer> 
    Device::createIndexBuffer(u32* indices, u32 count)
    {
        switch (m_Type)
        {
            case DeviceType::OpenGL: {
                return createRef<GLIndexBuffer>(indices, count);
            }
            break;
        }
        return nullptr;   
    }

    Ref<Shader> 
    Device::createShader(const ShaderDesc& desc)
    {
        switch (m_Type)
        {
            case DeviceType::OpenGL: {
                return createRef<GLShader>(desc);
            }
            break;
        }
        return nullptr;  
    }
    
    Ref<Texture> 
    Device::createTexture(u32 width, u32 height, TextureUsage usage)
    {
        switch (m_Type)
        {
            case DeviceType::OpenGL: {
                return createRef<GLTexture>(width, height, usage);
            }
            break;
        }
        return nullptr;  
        
    }
    
    Ref<Texture> 
    Device::createTexture(const str& filepath)
    {
        switch (m_Type)
        {
            case DeviceType::OpenGL: {
                return createRef<GLTexture>(filepath);
            }
            break;
        }
        return nullptr;  
    }
    
} // namespace prime
