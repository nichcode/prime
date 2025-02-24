
#pragma once

#include "defines.h"

#include <vector>

namespace prime {

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
        b8 normalized = false;
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
        add(Type type, u32 divisor = PDIVISOR_DEFAULT, b8 normalize = false) = 0;

        virtual void
        submit() = 0;

        virtual u32
        getStride() const = 0;

        virtual const std::vector<Element>&
        get() const = 0;

        virtual u32 getID() const = 0;
        virtual void* getHandle() const = 0;
    };
    
} // namespace prime
