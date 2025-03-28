
#include "prime/shader.h"
#include "pch.h"

#include "opengl/opengl_shader.h"

struct primeShader
{
    void* handle = nullptr;
    primeShaderSourceType source_type = primeShaderSourceTypes_GLSL;

    void(*destroy)(void* handle) = nullptr;
    void(*bind)(void* handle) = nullptr;
    void(*unbind)(void* handle) = nullptr;
    void(*setInt)(void* handle, const char* name, i32 data) = nullptr;
    void(*setIntArray)(void* handle, const char* name, i32* data, u32 count) = nullptr;
    void(*setFloat)(void* handle, const char* name, f32 data) = nullptr;
    void(*setFloat2)(void* handle, const char* name, primeVec2 data) = nullptr;
    void(*setFloat3)(void* handle, const char* name, primeVec3 data) = nullptr;
    void(*setFloat4)(void* handle, const char* name, primeVec4 data) = nullptr;
    void(*setMat4)(void* handle, const char* name, primeMat4 data) = nullptr;
};

primeShader* primeCreateShader(primeShaderDesc desc)
{
    primeShader* shader = new primeShader();
    shader->source_type = desc.source_type;
    switch (s_InitData.type) {
        case primeDeviceTypes_OpenGL: {
            shader->handle = _glCreateShader(desc);
            shader->destroy = _glDestroyShader;
            shader->bind = _glBindShader;
            shader->unbind = _glUnbindShader;
            shader->setInt = _glSetInt;
            shader->setIntArray = _glSetIntArray;
            shader->setFloat = _glSetFloat;
            shader->setFloat2 = _glSetFloat2;
            shader->setFloat3 = _glSetFloat3;
            shader->setFloat4 = _glSetFloat4;
            shader->setMat4 = _glSetMat4;
            break;
        } 
    } 
    s_InitData.shaders.push_back(shader);
    return shader;
}

void primeDestroyShader(primeShader* shader)
{
    PRIME_ASSERT_MSG(shader, "shader is null");
    auto it = std::find(s_InitData.shaders.begin(), s_InitData.shaders.end(), shader);
    if (it != s_InitData.shaders.end()) {
        s_InitData.shaders.erase(it); 
    }
    _primeDeleteShader(shader);
}

void _primeDeleteShader(primeShader* shader)
{
    if (s_InitData.activeShader == shader) {
        shader->unbind(shader->handle);
        s_InitData.activeShader = nullptr;
    }
    shader->destroy(shader->handle);
    delete shader;
    shader = nullptr;
}

void primeSetInt(primeShader* shader, const char* name, i32 data)
{
    PRIME_ASSERT_MSG(shader, "shader is null");
    shader->setInt(shader->handle, name, data);
}

void primeSetIntArray(primeShader* shader, const char* name, i32* data, u32 count)
{
    PRIME_ASSERT_MSG(shader, "shader is null");
    shader->setIntArray(shader->handle, name, data, count);
}

void primeSetFloat(primeShader* shader, const char* name, f32 data)
{
    PRIME_ASSERT_MSG(shader, "shader is null");
    shader->setFloat(shader->handle, name, data);
}

void primeSetFloat2(primeShader* shader, const char* name, primeVec2 data)
{
    PRIME_ASSERT_MSG(shader, "shader is null");
    shader->setFloat2(shader->handle, name, data);
}

void primeSetFloat3(primeShader* shader, const char* name, primeVec3 data)
{
    PRIME_ASSERT_MSG(shader, "shader is null");
    shader->setFloat3(shader->handle, name, data);
}

void primeSetFloat4(primeShader* shader, const char* name, primeVec4 data)
{
    PRIME_ASSERT_MSG(shader, "shader is null");
    shader->setFloat4(shader->handle, name, data);
}

void primeSetMat4(primeShader* shader, const char* name, primeMat4 data)
{
    PRIME_ASSERT_MSG(shader, "shader is null");
    shader->setMat4(shader->handle, name, data);
}

void primeBindShader(primeShader* shader)
{
    PRIME_ASSERT_MSG(shader, "shader is null");
    if (s_InitData.activeShader == nullptr || s_InitData.activeShader != shader) {
        shader->bind(shader->handle);
        s_InitData.activeShader = shader;
    }
}

void primeUnbindShader(primeShader* shader)
{
    PRIME_ASSERT_MSG(shader, "shader is null");
    if (s_InitData.activeShader == shader) {
        shader->unbind(shader->handle);
        s_InitData.activeShader = nullptr;
    }
}

