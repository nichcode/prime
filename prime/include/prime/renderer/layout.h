
#pragma once

#include "prime/defines.h"
#include <vector>

namespace prime::renderer {

    struct Element
    {
        DataType type = DataTypeFloat3;
        b8 normalize = false;
        u64 offset = 0;
        u32 size = 0;
        u32 divisor = 0;
    };

    class Layout
    {
    private:
        std::vector<Element> m_Elements;
        u32 m_Stride;

    public:
        void add(DataType type, u32 divisor = 0, b8 normalize = false)
        {
            Element element;
            element.divisor = divisor;
            element.normalize = normalize;
            element.type = type;
            element.size = getDataTypeSize(type);
            m_Elements.push_back(element);
        }

        void process()
        {
            m_Stride = 0;
            for (Element& element : m_Elements) {
                element.offset = m_Stride;
                m_Stride += element.size;
            }
        }

        PRIME_INLINE u32 getStride() const { return m_Stride; }
        PRIME_INLINE const std::vector<Element>& getElements() const { return m_Elements; }
    };
    
} // namespace prime::renderer
