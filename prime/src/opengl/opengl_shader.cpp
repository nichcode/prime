
#include "opengl_shader.h"
#include "prime/filesystem.h"
#include "prime/logger.h"
#include "prime/utils.h"
#include "opengl_API.h"

#include <vector>

namespace prime {

    static GLuint createShader(i32 type, const char* source)
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
                str msg = Utils::format("Vertex shader compilation error : %s", info_log.data());
                PERROR(msg.c_str());
            }
            else if (type == GL_FRAGMENT_SHADER)
            {
                str msg = Utils::format("Fragment shader compilation error : %s", info_log.data());
                PERROR(msg.c_str());
            }
            PASSERT(false);
        }
        return shader;

    }

    static GLuint createProgram(u32 vertexShader, u32 pixelShader)
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

            str msg = Utils::format("shader link error : %s", info_log.data());
            PERROR(msg.c_str());

            glDeleteProgram(program);
            program = 0;
            PASSERT(false);
        }
        return program;
    }

    GLShader::GLShader(const ShaderDesc& desc)
    {
        if (desc.type == ShaderSourceType::GLSL) {
            if (desc.load) {
                str vertex_src = "";
                str pixel_src = "";
                if (!desc.vertex.empty()) {
                    vertex_src = Filesystem::load(desc.vertex);
                    m_Vertex = createShader(GL_VERTEX_SHADER, vertex_src.c_str());
                }

                if (!desc.pixel.empty()) {
                    pixel_src = Filesystem::load(desc.pixel);
                    m_Pixel = createShader(GL_FRAGMENT_SHADER, pixel_src.c_str());
                }      
            }
            else {
                m_Vertex = createShader(GL_VERTEX_SHADER, desc.vertex.c_str());
                m_Pixel = createShader(GL_FRAGMENT_SHADER, desc.pixel.c_str());
            }
        }
        else {
            // TODO: shader transpiler
        }

        m_Handle = new ShaderHandle();

        m_Handle->id = createProgram(m_Vertex, m_Pixel);
        glUseProgram(m_Handle->id);
        glDeleteShader(m_Vertex);
        glDeleteShader(m_Pixel);
    }
    
    GLShader::~GLShader()
    {
        glDeleteProgram(m_Handle->id);
        m_Handle->id = 0;
        delete m_Handle;
        m_Handle = nullptr;
    }
    
    void GLShader::setInt(const char* name, i32 data)
    {
        GLint location = glGetUniformLocation(m_Handle->id, name);
        glUniform1i(location, data);
    }
    
    void GLShader::setIntArray(const char* name, i32* data, u32 count)
    {
        GLint location = glGetUniformLocation(m_Handle->id, name);
        glUniform1iv(location, count, data);
    }
    
    void GLShader::setFloat(const char* name, f32 data)
    {
        GLint location = glGetUniformLocation(m_Handle->id, name);
        glUniform1f(location, data);
    }
    
    void GLShader::setFloat2(const char* name, vec2 data)
    {
        GLint location = glGetUniformLocation(m_Handle->id, name);
        glUniform2f(location, data.x, data.y);
    }

    void GLShader::setFloat3(const char* name, vec3 data)
    {
        GLint location = glGetUniformLocation(m_Handle->id, name);
        glUniform3f(location, data.x, data.y, data.z);
    }

    void GLShader::setFloat4(const char* name, vec4 data)
    {
        GLint location = glGetUniformLocation(m_Handle->id, name);
        glUniform4f(location, data.x, data.y, data.z, data.w);
    }
    
    void GLShader::setMat4(const char* name, mat4 data)
    {
        GLint location = glGetUniformLocation(m_Handle->id, name);
        glUniformMatrix4fv(location, 1, GL_FALSE, data.data);
    }

    
} // namespace prime
