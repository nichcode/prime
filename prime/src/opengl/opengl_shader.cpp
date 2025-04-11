
#include "pch.h"
#include "opengl_shader.h"
#include "opengl_funcs.h"

inline u32 dataTypeSize(u32 type)
{
    switch (type)
    {
        case prShaderDataTypes_Int:
        case prShaderDataTypes_Float: {
            return 4;
        }

        case prShaderDataTypes_Int2:
        case prShaderDataTypes_Float2: {
            return 8;
        }

        case prShaderDataTypes_Int3:
        case prShaderDataTypes_Float3: {
            return 12;
        }

        case prShaderDataTypes_Int4:
        case prShaderDataTypes_Float4: {
            return 16;
        }
    }
    return 0;
}

inline u32 dataTypeCount(u32 type)
{
    switch (type)
    {
        case prShaderDataTypes_Float:
        case prShaderDataTypes_Int: {
            return 1;
        }

        case prShaderDataTypes_Float2:
        case prShaderDataTypes_Int2: {
            return 2;
        }

        case prShaderDataTypes_Float3:
        case prShaderDataTypes_Int3: {
            return 3;
        }

        case prShaderDataTypes_Float4:
        case prShaderDataTypes_Int4: {
            return 4;
        }
    }
    return 0;
}

inline GLenum typeToGLType(u32 type)
{
    switch (type)
    {
        case prShaderDataTypes_Int:
        case prShaderDataTypes_Int2:
        case prShaderDataTypes_Int3:
        case prShaderDataTypes_Int4:
            return GL_INT;

        case prShaderDataTypes_Float:
        case prShaderDataTypes_Float2:
        case prShaderDataTypes_Float3:
        case prShaderDataTypes_Float4:
            return GL_FLOAT;
    }
    return 0;
}

struct glShader
{
    u32 id = 0;
};

GLuint _GenShader(i32 type, const char* source)
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
            PR_ASSERT(false, "vertex shader compilation error : %s", info_log.data());
        }
        else if (type == GL_FRAGMENT_SHADER) {
            PR_ASSERT(false, "pixel shader compilation error : %s", info_log.data());
        }
    }
    return shader;
}

GLuint _GenProgram(u32 vertexShader, u32 pixelShader)
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
        PR_ASSERT(false, "shader link error : %s", info_log.data());
    }
    return program;
}

std::string _Readfile(const char* filepath)
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
            PR_ASSERT(false, "Could not read from file '%s'", filepath);
            return nullptr;
        }
    }
    else {
        PR_ASSERT(false, "Could not read from file '%s'", filepath);
        return nullptr;
    }
    return result;
}

void* _GLCreateShader(prShaderDesc desc)
{
    // TODO: transpiler
    std::string vertex_src;
    std::string pixel_src;
    if (desc.load) {
        vertex_src = _Readfile(desc.vertex_src);
        pixel_src = _Readfile(desc.pixel_src);
    }
    else {
        vertex_src = desc.vertex_src;
        pixel_src = desc.pixel_src;
    }

    u32 vertex_shader = _GenShader(GL_VERTEX_SHADER, vertex_src.c_str());
    u32 pixel_shader = _GenShader(GL_FRAGMENT_SHADER, pixel_src.c_str());
    
    glShader* shader = new glShader();
    PR_ASSERT(shader, "failed to create opengl shader handle");

    shader->id = _GenProgram(vertex_shader, pixel_shader);
    glDeleteShader(vertex_shader);
    glDeleteShader(pixel_shader);
    
    return shader;
}

void _GLDestroyShader(void* handle)
{
    glShader* shader = (glShader*)handle;
    glDeleteProgram(shader->id);
    delete shader;
    handle = nullptr;
}

void _GLBindShader(void* handle)
{
    glShader* shader = (glShader*)handle;
    glUseProgram(shader->id);
}

void _GLSetInt(void* handle, const char* name, i32 data)
{
    glShader* shader = (glShader*)handle;
    GLint location = glGetUniformLocation(shader->id, name);
    glUniform1i(location, data);
}

void _GLSetIntArray(void* handle, const char* name, i32* data, u32 count)
{
    glShader* shader = (glShader*)handle;
    GLint location = glGetUniformLocation(shader->id, name);
    glUniform1iv(location, count, data);
}

void _GLSetFloat(void* handle, const char* name, f32 data)
{
    glShader* shader = (glShader*)handle;
    GLint location = glGetUniformLocation(shader->id, name);
    glUniform1f(location, data);
}

void _GLSetFloat2(void* handle, const char* name, f32 data, f32 data2)
{
    glShader* shader = (glShader*)handle;
    GLint location = glGetUniformLocation(shader->id, name);
    glUniform2f(location, data, data2);
}

void _GLSetFloat3(void* handle, const char* name, f32 data, f32 data2, f32 data3)
{
    glShader* shader = (glShader*)handle;
    GLint location = glGetUniformLocation(shader->id, name);
    glUniform3f(location, data, data2, data3);
}

void _GLSetFloat4(void* handle, const char* name, f32 data, f32 data2, f32 data3, f32 data4)
{
    glShader* shader = (glShader*)handle;
    GLint location = glGetUniformLocation(shader->id, name);
    glUniform4f(location, data, data2, data3, data4);
}

void _GLSetMat4(void* handle, const char* name, f32* data)
{
    glShader* shader = (glShader*)handle;
    GLint location = glGetUniformLocation(shader->id, name);
    glUniformMatrix4fv(location, 1, GL_FALSE, data);
}

void _GLSetLayout(void* handle, prShaderLayout* layout)
{
    u32 index = 0;
    u32 stride = 0;
    u64 offsets[layout->count];
    for (u32 i = 0; i < layout->count; i++) {
        offsets[i] = stride;
        stride += dataTypeSize(layout->attribs[i].type);
    }

    for (u32 i = 0; i < layout->count; i++) {
        u32 count = dataTypeCount(layout->attribs[i].type);
        u32 type = typeToGLType(layout->attribs[i].type);
        u32 divisor = layout->attribs[i].divisor;
        b8 normalize = layout->attribs[i].normalize;
        const void* offset = (const void*)offsets[i];

        switch (type) {
            case GL_FLOAT: {
                glVertexAttribPointer(index, count, type, normalize, stride, offset);
                glEnableVertexAttribArray(index);
                glVertexAttribDivisor(index, divisor);
                break;
            }

            case GL_INT: {
                glVertexAttribIPointer(index, count, type, stride, offset);
                glEnableVertexAttribArray(index);
                glVertexAttribDivisor(index, divisor);
                break;
            }
        }
        index++;
    }
}

