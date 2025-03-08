
#pragma once

#include "prime/defines.h"
#include "glad/glad.h"

namespace prime::renderer {

    PRIME_INLINE static GLenum drawModeToGL(DrawMode mode)
    {
        switch (mode)
        {
        case DrawModeTriangles:
            return GL_TRIANGLES;
            break;

        case DrawModeLines:
            return GL_LINES;
            break;
        }
        return 0;
    }

    PRIME_INLINE static GLenum typeToGLType(DataType type)
    {
        switch (type)
        {
        case DataTypeInt:
        case DataTypeInt2:
        case DataTypeInt3:
        case DataTypeInt4:
            return GL_INT;

        case DataTypeFloat:
        case DataTypeFloat2:
        case DataTypeFloat3:
        case DataTypeFloat4:
            return GL_FLOAT;

        case DataTypeBool:
            return GL_BOOL;
        }
        return 0;
    }
    
} // namespace prime::renderer
