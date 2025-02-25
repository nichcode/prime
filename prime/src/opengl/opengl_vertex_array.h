
#pragma once

#include "prime/vertex_array.h"

namespace prime {

    class GLVertexArray : public VertexArray
    {
    private:
        u32 m_ID, m_Index;

    public:
        GLVertexArray();
        virtual ~GLVertexArray() override;

        virtual void
        submit(const VertexBuffer* vertex_buffer) override;

        virtual u32
        getID() const override {return m_ID; }
    };
 
} // namespace prime
