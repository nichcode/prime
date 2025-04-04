
#pragma once

#include "prime/prime.h"

struct API
{
    // context
    void*(*createContext)(void* window_handle) = nullptr;
    void(*destroyContext)(void* handle) = nullptr;
    void(*swapBuffers)(void* handle) = nullptr;
    void(*setClearColor)(void* handle, prime_vec4 color) = nullptr;
    void(*setVsync)(void* handle, b8 vsync) = nullptr;
    void(*makeActive)(void* handle) = nullptr;
    void(*clear)(void* handle) = nullptr;
    void(*submitArrays)(void* handle, u32 mode, u32 count) = nullptr;
    void(*submitElements)(void* handle, u32 mode, u32 count) = nullptr;
    void(*submitLayout)(void* handle, prime_layout* layout) = nullptr;

    // buffer
    void*(*createBuffer)(prime_buffer_desc desc) = nullptr;
    void(*destroyBuffer)(void* handle) = nullptr;
    void(*bindBuffer)(void* handle, b8 send_data) = nullptr;
    void(*setBufferData)(void* handle, void* data, u32 size) = nullptr;

    // shader
    void*(*createShader)(prime_shader_desc desc) = nullptr;
    void(*destroyShader)(void* handle) = nullptr;
    void(*bindShader)(void* handle) = nullptr;
    void(*setInt)(void* handle, const char* name, i32 data) = nullptr;
    void(*setIntArray)(void* handle, const char* name, i32* data, u32 count) = nullptr;
    void(*setFloat)(void* handle, const char* name, f32 data) = nullptr;
    void(*setFloat2)(void* handle, const char* name, prime_vec2 data) = nullptr;
    void(*setFloat3)(void* handle, const char* name, prime_vec3 data) = nullptr;
    void(*setFloat4)(void* handle, const char* name, prime_vec4 data) = nullptr;
    void(*setMat4)(void* handle, const char* name, prime_mat4 data) = nullptr;
};

void prime_InitAPI();
void prime_ShutdownAPI();