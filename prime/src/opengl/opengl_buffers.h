
#pragma once

#include "prime/buffers.h"

namespace prime {

    class GLVertexBuffer : public VertexBuffer
    {
    private:
        u32 m_ID;
        b8 m_Dynamic;
        void* m_Handle;
        Layout m_Layout;

    public:
        GLVertexBuffer(f32* vertices, u32 size);
        GLVertexBuffer(u32 size);

        virtual ~GLVertexBuffer() override;

        virtual void
        setData(const void* data, u32 size) override;

        virtual void 
        setLayout(const Layout& layout) override { m_Layout = layout; }

        virtual void* 
        getHandle() const override {return m_Handle; }

        virtual u32
        getID() const override {return m_ID; }

		virtual const 
        Layout& getLayout() const override { return m_Layout; }
    };

    class GLIndexBuffer : public IndexBuffer
    {
    private:
        u32 m_ID, m_Count;
        void* m_Handle;

    public:
        GLIndexBuffer(u32* indices, u32 count);
        virtual ~GLIndexBuffer() override;

        virtual void* 
        getHandle() const override {return m_Handle; }

        virtual u32
        getID() const override {return m_ID; }

        virtual u32 
        getCount() const override {return m_Count; }
    };
    
} // namespace prime
