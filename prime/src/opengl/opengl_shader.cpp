
#include "opengl_shader.h"
#include "pch.h"
#include "opengl_funcs.h"

struct glShader
{
    u32 id = 0;
};

GLuint generateShader(i32 type, const char* source)
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
        if (type == GL_VERTEX_SHADER) {
            PRIME_ASSERT_MSG(false, "vertex shader compilation error : %s", info_log.data());
        }
        else if (type == GL_FRAGMENT_SHADER) {
            PRIME_ASSERT_MSG(false, "pixel shader compilation error : %s", info_log.data());
        }
    }
    return shader;
}

GLuint generateProgram(u32 vertexShader, u32 pixelShader)
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

        glDeleteProgram(program);
        program = 0;
        PRIME_ASSERT_MSG(false, "shader link error : %s", info_log.data());
    }
    return program;
}

std::string readfile(const char* filepath)
{
    std::string result;
    std::ifstream file(filepath, std::ios::in | std::ios::binary);
    if (file) {
        file.seekg(0, std::ios::end);
        size_t size = file.tellg();
        if (size != -1) {
            result.resize(size);
            file.seekg(0, std::ios::beg);
            file.read(&result[0], size);
        }
        else {
            PRIME_ASSERT_MSG(false, "Could not read from file '%s'", filepath);
            return nullptr;
        }
    }
    else {
        PRIME_ASSERT_MSG(false, "Could not read from file '%s'", filepath);
        return nullptr;
    }
    return result;
}

void* _glCreateShader(primeShaderDesc desc)
{
    // TODO: transpiler
    std::string vertex_src;
    std::string pixel_src;
    if (desc.load) {
        vertex_src = readfile(desc.vertex_src);
        pixel_src = readfile(desc.pixel_src);
    }
    else {
        vertex_src = desc.vertex_src;
        pixel_src = desc.pixel_src;
    }

    u32 vertex_shader = generateShader(GL_VERTEX_SHADER, vertex_src.c_str());
    u32 pixel_shader = generateShader(GL_FRAGMENT_SHADER, pixel_src.c_str());
    
    glShader* shader = new glShader();
    shader->id = generateProgram(vertex_shader, pixel_shader);
    glDeleteShader(vertex_shader);
    glDeleteShader(pixel_shader);
    
    return shader;
}

void _glDestroyShader(void* handle)
{
    glShader* shader = (glShader*)handle;
    glDeleteProgram(shader->id);
    delete shader;
    shader = nullptr;
    shader = nullptr;
}

void _glSetInt(void* handle, const char* name, i32 data)
{
    glShader* shader = (glShader*)handle;
    GLint location = glGetUniformLocation(shader->id, name);
    glUniform1i(location, data);
}

void _glSetIntArray(void* handle, const char* name, i32* data, u32 count)
{
    glShader* shader = (glShader*)handle;
    GLint location = glGetUniformLocation(shader->id, name);
    glUniform1iv(location, count, data);
}

void _glSetFloat(void* handle, const char* name, f32 data)
{
    glShader* shader = (glShader*)handle;
    GLint location = glGetUniformLocation(shader->id, name);
    glUniform1f(location, data);
}

void _glSetFloat2(void* handle, const char* name, primeVec2 data)
{
    glShader* shader = (glShader*)handle;
    GLint location = glGetUniformLocation(shader->id, name);
    glUniform2f(location, data.x, data.y);
}

void _glSetFloat3(void* handle, const char* name, primeVec3 data)
{
    glShader* shader = (glShader*)handle;
    GLint location = glGetUniformLocation(shader->id, name);
    glUniform3f(location, data.x, data.y, data.z);
}

void _glSetFloat4(void* handle, const char* name, primeVec4 data)
{
    glShader* shader = (glShader*)handle;
    GLint location = glGetUniformLocation(shader->id, name);
    glUniform4f(location, data.x, data.y, data.z, data.w);
}

void _glSetMat2(void* handle, const char* name, primeMat2 data)
{
    glShader* shader = (glShader*)handle;
    GLint location = glGetUniformLocation(shader->id, name);
    glUniformMatrix2fv(location, 1, GL_FALSE, data.data);
}

void _glSetMat3(void* handle, const char* name, primeMat3 data)
{
    glShader* shader = (glShader*)handle;
    GLint location = glGetUniformLocation(shader->id, name);
    glUniformMatrix3fv(location, 1, GL_FALSE, data.data);
}

void _glSetMat4(void* handle, const char* name, primeMat4 data)
{
    glShader* shader = (glShader*)handle;
    GLint location = glGetUniformLocation(shader->id, name);
    glUniformMatrix4fv(location, 1, GL_FALSE, data.data);
}

void _glBindShader(void* handle)
{
    glShader* shader = (glShader*)handle;
    glUseProgram(shader->id);
}

void _glUnbindShader(void* handle)
{
    glUseProgram(0);
}