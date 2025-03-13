
#include "gl_vertex_array.h"
#include "opengl_API.h"

namespace prime::renderer {

    GLVertexArray::GLVertexArray()
    {
        glGenVertexArrays(1, &m_ID);
        glBindVertexArray(m_ID);
        m_Index = 0;
    }
    
    void GLVertexArray::setLayout(const Layout& layout)
    {
        for (const Element& element : layout.getElements()) {
            u32 count = getDataTypeCount(element.type);
            u32 type = typeToGLType(element.type);
            u32 stride = layout.getStride();

            switch (element.type) {
                case DataTypeFloat:
                case DataTypeFloat2:
                case DataTypeFloat3:
                case DataTypeFloat4: {
                    glVertexAttribPointer(
                        m_Index,
                        count,
                        type,
                        element.normalize,
                        stride,
                        (const void*)element.offset);

                    glEnableVertexAttribArray(m_Index);
                    glVertexAttribDivisor(m_Index, element.divisor);
                    break;
                }

                case DataTypeInt:
                case DataTypeInt2:
                case DataTypeInt3:
                case DataTypeInt4:
                case DataTypeBool: {
                    glVertexAttribIPointer(
                        m_Index,
                        count,
                        type,
                        stride,
                        (const void*)element.offset);

                    glEnableVertexAttribArray(m_Index);
                    glVertexAttribDivisor(m_Index, element.divisor);
                    break;
                }

            } // switch

            m_Index++;
        }
    }

    GLVertexArray::~GLVertexArray()
    {
        glDeleteBuffers(1, &m_ID);
        m_ID = 0;
    }
    
    void GLVertexArray::bind() const 
    {
        glBindVertexArray(m_ID);
    }
    
    void GLVertexArray::unBind() const 
    {
        glBindVertexArray(0);
    }
    
} // namespace prime::renderer
