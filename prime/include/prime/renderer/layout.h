
#pragma once

#include "prime/defines.h"
#include <vector>

namespace prime::renderer {

    struct LayoutElement
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
        std::vector<LayoutElement> m_Elements;
        u32 m_Stride;

    public:
        Layout() : m_Stride(0) {}
        ~Layout() { m_Stride = 0; m_Elements.clear(); }

        void addElement(DataType type, u32 divisor = 0, b8 normalize = false)
        {
            LayoutElement element;
            element.divisor = divisor;
            element.normalize = normalize;
            element.type = type;
            element.size = getDataTypeSize(type);
            m_Elements.push_back(element);
        }

        void process()
        {
            m_Stride = 0;
            for (auto& element : m_Elements) {
                element.offset = m_Stride;
                m_Stride += element.size;
            }
        }

        u32 getStride() const { return m_Stride; }
        const std::vector<LayoutElement>& getElements() const { return m_Elements; }

        std::vector<LayoutElement>::iterator begin() { return m_Elements.begin(); }
        std::vector<LayoutElement>::iterator end() { return m_Elements.end(); }
        std::vector<LayoutElement>::const_iterator begin() const { return m_Elements.begin(); }
        std::vector<LayoutElement>::const_iterator end() const { return m_Elements.end(); }
    };
    
} // namespace prime::renderer
