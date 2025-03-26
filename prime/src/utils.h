
#pragma once

#include "prime/logger.h"
#include "prime/platform.h"
#include <vector>

struct primeContext;
struct primeBuffer;
struct primeShader;
struct primeLayout;

struct primeInitData
{
    primeDeviceType type;
    std::vector<primeContext*> contexts;
    std::vector<primeBuffer*> buffers;
    std::vector<primeShader*> shaders;
    std::vector<primeLayout*> layouts;

    primeContext* activeContext = nullptr;
    primeBuffer* activeBuffer = nullptr;
    primeShader* activeShader = nullptr;
    primeLayout* activeLayout = nullptr;
};

static primeInitData s_InitData;

i32 multibyteToWchar(const char* str, u32 str_len, wchar_t* wstr);
i32 wcharToMultibyte(const wchar_t* wstr, u32 wstr_len, char* str);

void consoleWrite(primeLogLevel level, const char* msg);
void initInput();

void _primeDeleteContext(primeContext* context);
void _primeDeleteBuffer(primeBuffer* buffer);
void _primeDeleteShader(primeShader* shader);
void _primeDeleteLayout(primeLayout* layout);