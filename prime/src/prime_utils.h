
#pragma once

#include "prime/prime.h"
#include "prime_API.h"

struct InitData
{
    u32 type;
    API api;
    void* userData;
    prime_window* activeWindow;
    prime_context* activeContext;
    prime_buffer* activeBuffer;
    prime_shader* activeShader;
};

static InitData s_Data;

i32 prime_MultibyteToWchar(const char* str, u32 str_len, wchar_t* wstr);
i32 prime_WcharToMultibyte(const wchar_t* wstr, u32 wstr_len, char* str);

void prime_ConsoleWrite(u32 level, const char* msg);
void prime_InitInput();

void prime_SetContext(prime_window* window, prime_context* context);
b8 prime_HasContext(prime_window* window);