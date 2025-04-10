
#pragma once

#include "prime/defines.h"
#include "prime/input.h"
#include "prime/buffer.h"
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

    // buffer
    void*(*createBuffer)(prBufferDesc desc) = nullptr;
    void(*destroyBuffer)(void* handle) = nullptr;
    void(*bindBuffer)(void* handle, b8 send_data) = nullptr;
    void(*setBufferData)(void* handle, void* data, u32 size) = nullptr;
};

struct prPipeLineState
{
    prBuffer* activeVertexBuffer = nullptr;
    prBuffer* activeIndexBuffer = nullptr;
    prBuffer* activeStorageBuffer = nullptr;
    prBuffer* activeUniformBuffer = nullptr;
};

struct prDestructor
{
    std::vector<prBuffer*> buffers;
};

struct prContext
{
    prAPI api;
    prDestructor data;
    prPipeLineState state;
    void* handle;
};

struct prBuffer
{
    prContext* context = nullptr;
    void* handle = nullptr;
    u32 type = 0;
    b8 dataSent = false;
};

static prContext* s_ActiveContext = nullptr;

void _InitInput();
void _ConsoleWrite(u32 level, const char* message);