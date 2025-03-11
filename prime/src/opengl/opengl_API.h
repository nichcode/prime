
#pragma once

#include "prime/defines.h"
#include "prime/core/fmt.h"
#include "prime/core/logger.h"
#include "glad/glad.h"
#include <vector>

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif // STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

namespace prime::renderer {

    static u32 s_Data = 0xffffffff;

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

    static GLenum dataFormatToGL(TextureFormat format)
    {
        switch (format)
        {
        case TextureFormatR8:
            return GL_R8;
            break;

        case TextureFormatRGB8:
            return GL_RGB;
            break;

        case TextureFormatRGBA8:
            return GL_RGBA;
            break;

        case TextureFormatRGBA32F:
            return GL_RGBA32F;
            break;
        }
        return 0;
    }

    static GLenum formatToGL(TextureFormat format)
    {
        switch (format)
        {
        case TextureFormatR8:
            return GL_R8;
            break;

        case TextureFormatRGB8:
            return GL_RGB8;
            break;

        case TextureFormatRGBA8:
            return GL_RGBA8;
            break;

        case TextureFormatRGBA32F:
            return GL_RGBA32F;
            break;
        }
        return 0;
    }

    static void generateTexture(u32& id, u32 width, u32 height, b8 target, u32& frame_buffer, u32& depth, TextureFormat format)
    {
        u32 gl_data_format = dataFormatToGL(format);
        u32 gl_format = formatToGL(format);
        if (target) {
            glGenFramebuffers(1, &frame_buffer);
            glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer);

            // texture
            glGenTextures(1, &id);
            glBindTexture(GL_TEXTURE_2D, id);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
            glGenerateMipmap(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, 0);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, id, 0);

            // Create depth/stencil renderbuffer
            glGenRenderbuffers(1, &depth);
            glBindRenderbuffer(GL_RENDERBUFFER, depth);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
            glBindRenderbuffer(GL_RENDERBUFFER, 0);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depth);

            // Check for completeness
            i32 complete_status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
            if (complete_status != GL_FRAMEBUFFER_COMPLETE) {
                str msg = core::format("Failure to create render target texture. Complete status: %i", complete_status);
                PRIME_ASSERT_MSG(false, msg);
            }
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }
        else {
            glGenTextures(1, &id);
            glBindTexture(GL_TEXTURE_2D, id);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glTexImage2D( GL_TEXTURE_2D, 0, gl_format, width, height, 0, gl_data_format, GL_UNSIGNED_BYTE, &s_Data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
    }

    static void generateTexture(u32& id, const str& filepath, u32* width, u32* height)
    {
        int w = 0, h = 0, channels = 0;
        stbi_uc* data = stbi_load(filepath.c_str(), &w, &h, &channels, 0);
        if (data) {
            GLenum int_fmt = 0, data_fmt = 0;
            if (channels == 4) {
                int_fmt = GL_RGBA8;
                data_fmt = GL_RGBA;
            }
            else if (channels == 3) {
                int_fmt = GL_RGB8;
                data_fmt = GL_RGB;
            }

            PRIME_ASSERT_MSG(int_fmt & data_fmt, "Format not supported!");

            glGenTextures(1, &id);
            glBindTexture(GL_TEXTURE_2D, id);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glTexImage2D( GL_TEXTURE_2D, 0, int_fmt, w, h, 0, data_fmt, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            *width = w;
            *height = h;
            stbi_image_free(data);
        }
        else {
            str msg = core::format("Could not load texture2d - %s", filepath.c_str());
            PRIME_ASSERT_MSG(false, msg.c_str());
        }
    }
    
} // namespace prime::renderer
