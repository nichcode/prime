
#pragma once

#include "prime/defines.h"
#include "prime/core/fmt.h"
#include "prime/core/logger.h"
#include "glad/glad.h"
#include <vector>

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

    static GLuint generateShader(i32 type, const char* source)
    {
        int status = GL_FALSE;
        int max_length = 0;

        GLuint shader = glCreateShader(type);
        const char* gl_source = source;
        glShaderSource(shader, 1, &gl_source, 0);
        glCompileShader(shader);
        glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &max_length);

        if (status != GL_TRUE) {
            std::vector<GLchar> info_log(max_length);
            glGetShaderInfoLog(shader, max_length, &max_length, info_log.data());

            if (type == GL_VERTEX_SHADER)
            {
                str msg = core::format("Vertex shader compilation error : %s", info_log.data());
                PRIME_ERROR(msg.c_str());
            }
            else if (type == GL_FRAGMENT_SHADER)
            {
                str msg = core::format("Fragment shader compilation error : %s", info_log.data());
                PRIME_ERROR(msg.c_str());
            }
            PRIME_ASSERT(false);
        }
        return shader;
    }

    static GLuint generateProgram(u32 vertexShader, u32 pixelShader)
    {
        int status = GL_FALSE;
        int max_length = 0;

        u32 program = glCreateProgram();
        glAttachShader(program, vertexShader);
        glAttachShader(program, pixelShader);
        glLinkProgram(program);

        glValidateProgram(program);
        glGetProgramiv(program, GL_LINK_STATUS, &status);
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &max_length);
        if (status != GL_TRUE) {
            std::vector<GLchar> info_log(max_length);
            glGetProgramInfoLog(program, max_length, &max_length, info_log.data());

            str msg = core::format("shader link error : %s", info_log.data());
            PRIME_ERROR(msg.c_str());

            glDeleteProgram(program);
            program = 0;
            PRIME_ASSERT(false);
        }
        return program;
    }
    
} // namespace prime::renderer
