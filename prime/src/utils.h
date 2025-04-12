
#pragma once

#include "prime/defines.h"
#include "prime/input.h"
#include "prime/buffer.h"
#include "prime/shader.h"
#include "prime/viewport.h"
#include "maths.h"
#include <vector>

// declarations
struct prContext;

// definitions
struct prWindow
{
    void* handle;
    prContext* context;
    u32 width, height;
    i32 x, y;
    const char* title;
    b8 shouldClose, focused;

    u32 keycodes[512];
    u32 scancodes[prKeys_Max + 1];
    u32 keys[prKeys_Max + 1];
    u32 buttons[prButtons_Max + 1];
    i32 mousePos[2];
};

struct prAPI
{
    // context
    void*(*createContext)(void* window_handle, i32 major, i32 minor) = nullptr;
    void(*destroyContext)(void* handle) = nullptr;
    void(*swapBuffers)(void* handle) = nullptr;
    void(*setVsync)(void* handle, b8 vsync) = nullptr;
    void(*makeActive)(void* handle) = nullptr;
    void(*clear)(void* handle) = nullptr;
    void(*setClearColor)(void* handle, f32 r, f32 g, f32 b, f32 a) = nullptr;
    void(*drawArrays)(void* handle, u32 mode, u32 count) = nullptr;
    void(*drawElements)(void* handle, u32 mode, u32 count) = nullptr;
    void(*drawArraysInstanced)(void* handle, u32 mode, u32 count, u32 instance_count) = nullptr;
    void(*drawElementsInstanced)(void* handle, u32 mode, u32 count, u32 instance_count) = nullptr;
    void(*setView)(void* handle, prViewport view) = nullptr;

    // buffer
    void*(*createBuffer)(prBufferDesc desc) = nullptr;
    void(*destroyBuffer)(void* handle) = nullptr;
    void(*bindBuffer)(void* handle) = nullptr;
    void(*setBufferData)(void* handle, void* data, u32 size) = nullptr;

    // shader
    void*(*createShader)(prShaderDesc desc) = nullptr;
    void(*destroyShader)(void* handle) = nullptr;
    void(*bindShader)(void* handle) = nullptr;
    void(*setInt)(void* handle, const char* name, i32 data) = nullptr;
    void(*setIntArray)(void* handle, const char* name, i32* data, u32 count) = nullptr;
    void(*setFloat)(void* handle, const char* name, f32 data) = nullptr;
    void(*setFloat2)(void* handle, const char* name, f32 data, f32 data2) = nullptr;
    void(*setFloat3)(void* handle, const char* name, f32 data, f32 data2, f32 data3) = nullptr;
    void(*setFloat4)(void* handle, const char* name, f32 data, f32 data2, f32 data3, f32 data4) = nullptr;
    void(*setMat4)(void* handle, const char* name, f32* data) = nullptr;
    void(*setLayout)(void* handle, prShaderLayout* layout) = nullptr;
};

struct prPipeLineState
{
    prBuffer* activeVertexBuffer = nullptr;
    prBuffer* activeIndexBuffer = nullptr;
    prBuffer* activeStorageBuffer = nullptr;
    prBuffer* activeUniformBuffer = nullptr;
    prShader* activeShader = nullptr;
};

struct prDestructor
{
    std::vector<prBuffer*> buffers;
    std::vector<prShader*> shaders;
};

struct prContext
{
    prAPI api;
    prDestructor data;
    prPipeLineState state;
    prViewport view;
    void* handle;
};

struct prBuffer
{
    prContext* context = nullptr;
    void* handle = nullptr;
    u32 type = 0;
    b8 dataSent = false;
};

struct prShader
{
    prContext* context = nullptr;
    void* handle = nullptr;
    prShaderLayout layout;
    b8 layoutSent = false;
};

struct prVertex
{
    prVec3 position;
    prVec4 color;
};

struct prRenderer
{
    u32 count = 0;
    prMat4 projection;
    prContext* context;

    prBuffer* vbo = nullptr;
    prBuffer* ibo = nullptr;
    prShader* shader = nullptr;

    prVec4 drawColor;

    prVec4 vertices[4];
    std::vector<prVertex> sprites;
};

static prContext* s_ActiveContext = nullptr;
static void* s_UserData = nullptr;

void _InitInput();
void _ConsoleWrite(u32 level, const char* message);