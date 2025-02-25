
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

    PINLINE u32
    getTypeSize(Type type)
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
    getTypeCount(Type type)
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

    struct Element
    {
        Type type = Type::Float3;
        b8 normalize = false;
        u64 offset = 0;
        u32 size = 0;
        u32 divisor = PDIVISOR_DEFAULT;
    };

    class Layout
    {
    private:
        std::vector<Element> m_Elements;
        u32 m_Stride = 0;

    public:
        void
        addElement(Type type, u32 divisor = PDIVISOR_DEFAULT, b8 normalize = false)
        {
            Element element;
            element.divisor = divisor;
            element.normalize = normalize;
            element.type = type;
            element.size = getTypeSize(type);
            m_Elements.push_back(element);
        }

        void
        process()
        {
            u64 offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements)
			{
				element.offset = offset;
				offset += element.size;
				m_Stride += element.size;
			}
        }

        u32
        getStride() const { return m_Stride; }

        std::vector<Element>::iterator begin() { return m_Elements.begin(); }
		std::vector<Element>::iterator end() { return m_Elements.end(); }
		std::vector<Element>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<Element>::const_iterator end() const { return m_Elements.end(); }

        const std::vector<Element>& getElements() const { return m_Elements; }
    };
     
} // namespace prime
