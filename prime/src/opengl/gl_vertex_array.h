
#pragma once

#include "prime/renderer/vertex_array.h"

namespace prime::renderer {

    class GLVertexArray : public VertexArray
    {
    private:
        u32 m_ID, m_Index;

    public:
        GLVertexArray();
        virtual ~GLVertexArray() override;

        GLVertexArray (GLVertexArray& other) = delete;
        GLVertexArray (const GLVertexArray& other) = delete;
        GLVertexArray& operator=(GLVertexArray& other) = delete;
        GLVertexArray& operator=(const GLVertexArray& other) = delete;

        virtual void setLayout(const Layout& layout) override;
        
        virtual void bind() const override;
        virtual void unBind() const override;
    };
    
} // namespace prime::renderer
