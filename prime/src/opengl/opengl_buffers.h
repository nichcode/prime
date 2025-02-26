
#pragma once

#include "prime/buffers.h"

namespace prime {

    class GLVertexBuffer : public VertexBuffer
    {
    private:
        b8 m_Dynamic;
        VertexBufferHandle* m_Handle;
        Layout m_Layout;

    public:
        GLVertexBuffer(f32* vertices, u32 size);
        GLVertexBuffer(u32 size);

        virtual ~GLVertexBuffer() override;

        virtual void
        setData(const void* data, u32 size) override;

        virtual void 
        setLayout(const Layout& layout) override { m_Layout = layout; }

        virtual VertexBufferHandle*
        getHandle() const override {return m_Handle; }

		virtual const 
        Layout& getLayout() const override { return m_Layout; }
    };

    class GLIndexBuffer : public IndexBuffer
    {
    private:
        u32 m_Count;
        IndexBufferHandle* m_Handle;

    public:
        GLIndexBuffer(u32* indices, u32 count);
        virtual ~GLIndexBuffer() override;

        virtual IndexBufferHandle*
        getHandle() const override {return m_Handle; }

        virtual u32 
        getCount() const override {return m_Count; }
    };
    
} // namespace prime
