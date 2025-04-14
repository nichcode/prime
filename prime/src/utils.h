
#pragma once

#include "prime/defines.h"
#include "prime/input.h"
#include "prime/buffer.h"
#include "prime/shader.h"
#include "prime/viewport.h"
#include "prime/texture.h"
#include "maths.h"
#include <vector>

#include "ft2build.h"
#include FT_FREETYPE_H

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
    void(*destroyContext)(void* context_handle) = nullptr;
    void(*swapBuffers)(void* context_handle) = nullptr;
    void(*setVsync)(void* context_handle, b8 vsync) = nullptr;
    void(*makeActive)(void* context_handle) = nullptr;
    void(*clear)(void* context_handle) = nullptr;
    void(*setClearColor)(void* context_handle, f32 r, f32 g, f32 b, f32 a) = nullptr;
    void(*drawArrays)(void* context_handle, u32 mode, u32 count) = nullptr;
    void(*drawElements)(void* context_handle, u32 mode, u32 count) = nullptr;
    void(*drawArraysInstanced)(void* context_handle, u32 mode, u32 count, u32 instance_count) = nullptr;
    void(*drawElementsInstanced)(void* context_handle, u32 mode, u32 count, u32 instance_count) = nullptr;
    void(*setView)(void* context_handle, prViewport view) = nullptr;

    // buffer
    void*(*createBuffer)(prBufferDesc desc) = nullptr;
    void(*destroyBuffer)(void* buffer_handle) = nullptr;
    void(*bindBuffer)(void* buffer_handle) = nullptr;
    void(*setBufferData)(void* buffer_handle, void* data, u32 size) = nullptr;

    // shader
    void*(*createShader)(prShaderDesc desc) = nullptr;
    void(*destroyShader)(void* shader_handle) = nullptr;
    void(*bindShader)(void* shader_handle) = nullptr;
    void(*setInt)(void* shader_handle, const char* name, i32 data) = nullptr;
    void(*setIntArray)(void* shader_handle, const char* name, i32* data, u32 count) = nullptr;
    void(*setFloat)(void* shader_handle, const char* name, f32 data) = nullptr;
    void(*setFloat2)(void* shader_handle, const char* name, f32 data, f32 data2) = nullptr;
    void(*setFloat3)(void* shader_handle, const char* name, f32 data, f32 data2, f32 data3) = nullptr;
    void(*setFloat4)(void* shader_handle, const char* name, f32 data, f32 data2, f32 data3, f32 data4) = nullptr;
    void(*setMat4)(void* shader_handle, const char* name, f32* data) = nullptr;
    void(*setLayout)(void* shader_handle, prShaderLayout* layout) = nullptr;

    // texture 
    void*(*createTexture)(prTextureDesc desc) = nullptr;
    void*(*loadTexture)(const char* filepath, u32* width, u32* height) = nullptr;
    void(*destroyTexture)(void* texture_handle) = nullptr;
    void(*bindTexture)(void* texture_handle, u32 slot) = nullptr;
    void(*bindTarget)(void* texture_handle, u32 width, u32 height) = nullptr;
    void(*unbindTarget)(void* texture_handle) = nullptr;
};

struct prPipeLineState
{
    prBuffer* activeVertexBuffer = nullptr;
    prBuffer* activeIndexBuffer = nullptr;
    prBuffer* activeStorageBuffer = nullptr;
    prBuffer* activeUniformBuffer = nullptr;
    prShader* activeShader = nullptr;
    prTexture* activeTexture = nullptr;
    prTexture* activeTarget = nullptr;
};

struct prDestructor
{
    std::vector<prBuffer*> buffers;
    std::vector<prShader*> shaders;
    std::vector<prTexture*> textures;
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
    void* handle = nullptr;
    u32 type = 0;
    b8 dataSent = false;
};

struct prShader
{
    void* handle = nullptr;
    prShaderLayout layout;
    b8 layoutSent = false;
};

struct prTexture
{
    void* handle = nullptr;
    u32 width = 0;
    u32 height = 0;
    u32 flag = 0;
    const char* path = nullptr;
};

struct prVertex
{
    prVec3 position;
    prVec4 color;
    prVec4 texture;
};

struct prRenderer
{
    u32 indexCount = 0;
    u32 texIndex = 1;
    u32 activeTexIndex = 0;
    u32 drawCalls;
    
    prMat4 projection;
    prBuffer* vbo = nullptr;
    prBuffer* ibo = nullptr;
    prShader* shader = nullptr;

    prVec4 drawColor;
    prVec4 tintColor;

    prVec4 vertices[4];
    prVec2 texCoords[4];
    std::vector<prVertex> sprites;
    std::vector<prTexture*> textures;
};

static prContext* s_ActiveContext = nullptr;
static void* s_UserData = nullptr;
static FT_Library s_Library;

void _InitInput();
void _ConsoleWrite(u32 level, const char* message);