
#pragma once

#include "window.h"
#include "color.h"

#include <vector>

namespace prime {

    enum class BufferType
    {
        Vertex,
        Index
    };

    enum class BufferUsage
    {
        DynamicDraw,
        StaticDraw
    };

    enum DrawMode
    {
        Triangles,
        Lines
    };

    struct BufferDesc
    {
        BufferType type = BufferType::Vertex;
        BufferUsage usage = BufferUsage::StaticDraw;
        void* data = nullptr;
        u32 size = 0;
    };

    class Buffer
    {
    public:
        virtual ~Buffer() {};

        virtual void
        setData(const void* data, u32 size) = 0;

        virtual BufferType
        getType() = 0;

        virtual BufferUsage
        getUsage() = 0;

    private:
        virtual u32 getID() = 0;
        virtual void* getHandle() = 0;

        friend class GLContext;
    };

    enum Type
    {
        Int,
        Int2,
        Int3,
        Int4,
        Float,
        Float2,
        Float3,
        Float4,
        Mat3,
        Mat4,
        Bool
    };

    struct Element
    {
        Type type = Type::Float3;
        u32 size = 0;
        u64 offset = 0;
        u32 divisor = 0;
    };

    PINLINE u32
    typeGetSize(Type type)
    {
        switch (type)
        {
        case Type::Int:
        case Type::Float: {
            return 4;
            break;
        }

        case Type::Int2:
        case Type::Float2: {
            return 8;
            break;
        }

        case Type::Int3:
        case Type::Float3: {
            return 12;
            break;
        }

        case Type::Int4:
        case Type::Float4: {
            return 16;
            break;
        }

        case Type::Mat3: {
            return 4 * 3 * 3;
            break;
        }    

        case Type::Mat4:     {
            return 4 * 4 * 4; 
            break;
        }

        case Type::Bool: {
                return 1;
                break;
        }

        }
        return 0;
    }

    PINLINE u32
    typeGetCount(Type type)
    {
        switch (type)
        {
        case Type::Float:
        case Type::Int:
        case Type::Bool: {
            return 1;
        }

        case Type::Float2:
        case Type::Int2: {
            return 2;
        }

        case Type::Float3:
        case Type::Int3: {
            return 3;
        }

        case Type::Float4:
        case Type::Int4: {
            return 4;
        }


        case Type::Mat3: {
                return 9;
                break;
        }

        case Type::Mat4:   {
            return 16;
            break;
        }  

        }
        return 0;
    }

    class Layout
    {
    public:
        virtual ~Layout() {};

        virtual void
        add(Type type, u32 divisor = PDIVISOR_DEFAULT) = 0;

        virtual void
        submit() = 0;

        virtual u32
        getStride() = 0;

        virtual std::vector<Element>&
        get() = 0;

    private:
        virtual void
        setStride(u32 stride) = 0;

        virtual u32 getID() = 0;
        virtual void* getHandle() = 0;

        friend class GLContext;
    };

    class Context
    {
    public:
        virtual ~Context() {};

        virtual void
        swapbuffers() = 0;    
        
        virtual void
        makeActive() = 0;

        virtual void
        setClearColor(const Color& color) = 0;

        virtual void
        clear() = 0;

        virtual Buffer*
        createBuffer(const BufferDesc& desc) = 0;

        virtual void
        destroyBuffer(Buffer* buffer) = 0;

        virtual Layout*
        createLayout() = 0;

        virtual void
        destroyLayout(Layout* layout) = 0;

        virtual void
        setLayout(Layout* layout, b8 submit) = 0;

        virtual void
        setBuffer(Buffer* buffer) = 0;

        virtual void
        drawElements(DrawMode mode, u32 count) = 0;
    };
    
} // namespace prime
