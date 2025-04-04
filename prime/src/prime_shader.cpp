
#include "pch.h"
#include "prime/prime.h"

struct prime_shader
{
    void* handle = nullptr;
};

prime_shader* prime_create_shader(prime_shader_desc desc)
{
    prime_shader* shader = new prime_shader();
    PRIME_ASSERT_MSG(shader, "failed to create shader");
    shader->handle = s_Data.api.createShader(desc);
    return shader;
}

void prime_destroy_shader(prime_shader* shader)
{
    PRIME_ASSERT_MSG(shader, "shader is null");
    if (s_Data.activeShader == shader) {
        s_Data.activeShader = nullptr;
    }
    s_Data.api.destroyShader(shader->handle);
    delete shader;
    shader = nullptr;
}

void prime_set_int(const char* name, i32 data)
{
    PRIME_ASSERT_MSG(s_Data.activeShader, "active shader not set");
    s_Data.api.setInt(s_Data.activeShader->handle, name, data);
}

void prime_set_int_array(const char* name, i32* data, u32 count)
{
    PRIME_ASSERT_MSG(s_Data.activeShader, "active shader not set");
    s_Data.api.setIntArray(s_Data.activeShader->handle, name, data, count);
}

void prime_set_float(const char* name, f32 data)
{
    PRIME_ASSERT_MSG(s_Data.activeShader, "active shader not set");
    s_Data.api.setFloat(s_Data.activeShader->handle, name, data);
}

void prime_set_float2(const char* name, prime_vec2 data)
{
    PRIME_ASSERT_MSG(s_Data.activeShader, "active shader not set");
    s_Data.api.setFloat2(s_Data.activeShader->handle, name, data);
}

void prime_set_float3(const char* name, prime_vec3 data)
{
    PRIME_ASSERT_MSG(s_Data.activeShader, "active shader not set");
    s_Data.api.setFloat3(s_Data.activeShader->handle, name, data);
}

void prime_set_float4(const char* name, prime_vec4 data)
{
    PRIME_ASSERT_MSG(s_Data.activeShader, "active shader not set");
    s_Data.api.setFloat4(s_Data.activeShader->handle, name, data);
}

void prime_set_mat4(const char* name, prime_mat4 data)
{
    PRIME_ASSERT_MSG(s_Data.activeShader, "active shader not set");
    s_Data.api.setMat4(s_Data.activeShader->handle, name, data);
}

void prime_bind_shader(prime_shader* shader)
{
    PRIME_ASSERT_MSG(shader, "shader is null");
    s_Data.api.bindShader(shader->handle);
    s_Data.activeShader = shader;
}