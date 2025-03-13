
#pragma once

#include "prime/renderer/buffers.h"

namespace prime::renderer {

    class GLVertexBuffer : public VertexBuffer
    {
    private:
        u32 m_ID;
        b8 m_Dynamic;

    public:
        GLVertexBuffer(f32* vertices, u32 size);
        GLVertexBuffer(u32 size);

        virtual ~GLVertexBuffer() override;

        GLVertexBuffer(GLVertexBuffer& other) = delete;
        GLVertexBuffer(const GLVertexBuffer& other) = delete;
        GLVertexBuffer& operator=(GLVertexBuffer& other) = delete;
        GLVertexBuffer& operator=(const GLVertexBuffer& other) = delete;

        virtual void setData(const void* data, u32 size) override;
    
        virtual void bind() const override;
        virtual void unBind() const override;
    };

    class GLIndexBuffer : public IndexBuffer
    {
    private:
        u32 m_ID, m_Count;

    public:
        GLIndexBuffer(u32* indices, u32 count);
        virtual ~GLIndexBuffer() override;

        GLIndexBuffer(GLIndexBuffer& other) = delete;
        GLIndexBuffer(const GLIndexBuffer& other) = delete;
        GLIndexBuffer& operator=(GLIndexBuffer& other) = delete;
        GLIndexBuffer& operator=(const GLIndexBuffer& other) = delete;

        virtual u32 getCount() const override { return m_Count; }

        virtual void bind() const override;
        virtual void unBind() const override;
    };

    class GLUniformBuffer : public UniformBuffer
    {
    private:
        u32 m_ID;

    public:
        GLUniformBuffer(u32 size, u32 binding);

        virtual ~GLUniformBuffer() override;

        GLUniformBuffer(GLUniformBuffer& other) = delete;
        GLUniformBuffer(const GLUniformBuffer& other) = delete;
        GLUniformBuffer& operator=(GLUniformBuffer& other) = delete;
        GLUniformBuffer& operator=(const GLUniformBuffer& other) = delete;

        virtual void setData(const void* data, u32 size) override;

        virtual void bind() const override;
        virtual void unBind() const override;
    };
    
} // namespace prime::renderer
