
#pragma once

#include "prime/layout.h"

namespace prime {

    class GLLayout : public Layout
    {
    private:
        u32 m_ID, m_Stride;
        void* m_Unused;
        std::vector<Element> m_Elements;

    public:
        GLLayout();
        virtual ~GLLayout() override;

        virtual void
        add(Type type, u32 divisor, b8 normalize) override;

        virtual void
        submit() override;

        virtual u32
        getStride() const { return m_Stride; }

        virtual const std::vector<Element>&
        get() const override { return m_Elements; }

        virtual u32 getID() const override { return m_ID; }
        virtual void* getHandle() const override { return m_Unused; }

        std::vector<Element>::iterator begin() { return m_Elements.begin(); }
		std::vector<Element>::iterator end() { return m_Elements.end(); }
		std::vector<Element>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<Element>::const_iterator end() const { return m_Elements.end(); }
    };
    
} // namespace prime
