
#pragma once

#include "prime/prime.h"
#include "prime_API.h"

#include <vector>

struct InitData
{
    u32 type;
    API api;
    void* userData;
    prime_window* activeWindow;
    prime_context* activeContext;
    prime_buffer* activeBuffer;
    prime_shader* activeShader;

    std::vector<prime_window*> windows;
    std::vector<prime_context*> contexts;
    std::vector<prime_buffer*> buffers;
    std::vector<prime_shader*> shaders;
};

static InitData s_Data;

i32 prime_MultibyteToWchar(const char* str, u32 str_len, wchar_t* wstr);
i32 prime_WcharToMultibyte(const wchar_t* wstr, u32 wstr_len, char* str);

void prime_ConsoleWrite(u32 level, const char* msg);
void prime_InitInput();

void prime_SetContext(prime_window* window, prime_context* context);
b8 prime_HasContext(prime_window* window);

void prime_DestroyWindow(prime_window* window);
void prime_DestroyContext(prime_context* context);
void prime_DestroyBuffer(prime_buffer* buffer);
void prime_DestroyShader(prime_shader* shader);