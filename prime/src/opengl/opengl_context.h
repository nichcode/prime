
#pragma once

#include "prime/context.h"

#ifdef PPLATFORM_WINDOWS
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif // PPLATFORM_WINDOWS

#include <vector>

namespace prime {

    class GLBuffer : public Buffer
    {
    private:
        u32 m_ID;
        BufferType m_Type;
        BufferUsage m_Usage;

        friend GLContext;

    public:
        GLBuffer(const BufferDesc& desc);
        virtual ~GLBuffer() override;

        virtual void
        setData(const void* data, u32 size) override;

        virtual BufferType
        getType() override { return m_Type; }

        virtual BufferUsage
        getUsage() override { return m_Usage; }

    private:
        virtual u32 getID() override { return m_ID; }
        virtual void* getHandle() override {return &m_ID;}
    };

    class GLLayout : public Layout
    {
    private:
        u32 m_ID, m_Stride;
        std::vector<Element> m_Elements;

    public:
        GLLayout();
        virtual ~GLLayout() override;

        virtual void
        add(Type type, u32 divisor) override;

        virtual u32
        getStride() { return m_Stride; }

        virtual std::vector<Element>&
        get() override { return m_Elements; }

    private:
        virtual void
        setStride(u32 stride) override { m_Stride = stride; }

        virtual u32 getID() override { return m_ID; }
        virtual void* getHandle() override { return &m_ID; }
    };

    class GLContext : public Context
    {
    private:
#ifdef PPLATFORM_WINDOWS
        HWND m_Window;
        HGLRC m_Context;
        HDC m_Hdc;
#endif // PPLATFORM_WINDOWS

        std::vector<Buffer*> m_Buffers;
        std::vector<Layout*> m_Layouts;

    public:
        GLContext(const Window& window);
        ~GLContext() override;

        virtual void
        swapbuffers() override;    
        
        virtual void
        makeActive() override;

        virtual void
        setClearColor(const Color& color) override;

        virtual void
        clear() override;

        virtual Buffer*
        createBuffer(const BufferDesc& desc) override;

        virtual void
        destroyBuffer(Buffer* buffer) override;

        virtual Layout*
        createLayout() override;

        virtual void
        destroyLayout(Layout* layout) override;

        virtual void
        setLayout(Layout* layout, b8 submit) override;

        virtual void
        setBuffer(Buffer* buffer) override;

        virtual void
        drawElements(DrawMode mode, u32 count) = 0;
    };
    
} // namespace prime