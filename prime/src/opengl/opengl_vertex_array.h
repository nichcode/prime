
#pragma once

#include "prime/vertex_array.h"

namespace prime {

    class GLVertexArray : public VertexArray
    {
    private:
        u32 m_Index;
        VertexArrayHandle* m_Handle;

    public:
        GLVertexArray();
        virtual ~GLVertexArray() override;

        virtual void
        submit(const Ref<VertexBuffer>& vertex_buffer) override;

        virtual VertexArrayHandle*
        getHandle() const override { return m_Handle; }
    };
 
} // namespace prime
