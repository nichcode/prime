
#include "gl_shader.h"
#include "opengl_API.h"
#include "prime/core/filesystem.h"

namespace prime::renderer {

    GLShader::GLShader(const str& vertex, const str& pixel, b8 load, SourceType type)
    {
        if (type == SourceTypeGLSL) {
            if (load) {
                str vertex_src = "";
                str pixel_src = "";
                if (!vertex.empty()) {
                    vertex_src = core::Filesystem::load(vertex);
                    m_Vertex = generateShader(GL_VERTEX_SHADER, vertex_src.c_str());
                }

                if (!pixel.empty()) {
                    pixel_src = core::Filesystem::load(pixel);
                    m_Frag = generateShader(GL_FRAGMENT_SHADER, pixel_src.c_str());
                }      
            }
            else {
                m_Vertex = generateShader(GL_VERTEX_SHADER, vertex.c_str());
                m_Frag = generateShader(GL_FRAGMENT_SHADER, pixel.c_str());
            }

            m_ID = generateProgram(m_Vertex, m_Frag);
            glUseProgram(m_ID);
            glDeleteShader(m_Vertex);
            glDeleteShader(m_Frag);
        }
        else {
            // TODO: shader transpiler
            PRIME_WARN("Shader Transpiler not implememted yet");
        }
    }
    
    GLShader::~GLShader()
    {
        glDeleteProgram(m_ID);
        m_ID = 0;
    }

    void GLShader::setInt(const char* name, i32 data)
    {
        GLint location = glGetUniformLocation(m_ID, name);
        glUniform1i(location, data);
    }

    void GLShader::setIntArray(const char* name, i32* data, u32 count)
    {
        GLint location = glGetUniformLocation(m_ID, name);
        glUniform1iv(location, count, data);
    }

    void GLShader::setFloat(const char* name, f32 data)
    {
        GLint location = glGetUniformLocation(m_ID, name);
        glUniform1f(location, data);
    }

    void GLShader::setFloat2(const char* name, maths::vec2 data)
    {
        GLint location = glGetUniformLocation(m_ID, name);
        glUniform2f(location, data.x, data.y);
    }

    void GLShader::setFloat3(const char* name, maths::vec3 data)
    {
        GLint location = glGetUniformLocation(m_ID, name);
        glUniform3f(location, data.x, data.y, data.z);
    }

    void GLShader::setFloat4(const char* name, maths::vec4 data)
    {
        GLint location = glGetUniformLocation(m_ID, name);
        glUniform4f(location, data.x, data.y, data.z, data.w);
    }

    void GLShader::setMat4(const char* name, maths::mat4 data)
    {
        GLint location = glGetUniformLocation(m_ID, name);
        glUniformMatrix4fv(location, 1, GL_FALSE, data.data);
    }

    void GLShader::bind() const
    {
        glUseProgram(m_ID);
    }

    void GLShader::unBind() const
    {
        glUseProgram(0);
    }

} // namespace prime::renderer
