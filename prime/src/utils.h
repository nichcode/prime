
#pragma once

#include "prime/defines.h"
#include "prime/logger.h"
#include "prime/prime.h"

PRIME_INLINE u32 getDataTypeSize(primeDataType type)
{
    switch (type)
    {
        case PRIME_DATA_TYPE_INT:
        case PRIME_DATA_TYPE_FLOAT: {
            return 4;
        }

        case PRIME_DATA_TYPE_INT2:
        case PRIME_DATA_TYPE_FLOAT2: {
            return 8;
        }

        case PRIME_DATA_TYPE_INT3:
        case PRIME_DATA_TYPE_FLOAT3: {
            return 12;
        }

        case PRIME_DATA_TYPE_INT4:
        case PRIME_DATA_TYPE_FLOAT4: {
            return 16;
        }
        case PRIME_DATA_TYPE_BOOL:     return 1;
    }
    return 0;
}

PRIME_INLINE u32 getDataTypeCount(primeDataType type)
{
    switch (type)
    {
        case PRIME_DATA_TYPE_FLOAT:
        case PRIME_DATA_TYPE_INT:
        case PRIME_DATA_TYPE_BOOL: {
            return 1;
        }

        case PRIME_DATA_TYPE_FLOAT2:
        case PRIME_DATA_TYPE_INT2: {
            return 2;
        }

        case PRIME_DATA_TYPE_FLOAT3:
        case PRIME_DATA_TYPE_INT3: {
            return 3;
        }

        case PRIME_DATA_TYPE_FLOAT4:
        case PRIME_DATA_TYPE_INT4: {
            return 4;
        }
    }
    return 0;
}

struct primeInitData
{
    primeDeviceType type;
};

struct primeElement
{
    primeDataType type = PRIME_DATA_TYPE_FLOAT3;
    b8 normalize = false;
    u64 offset = 0;
    u32 size = 0;
    u32 divisor = 0;
};

static primeInitData s_InitData;

i32 multibyteToWchar(const char* str, u32 str_len, wchar_t* wstr);
i32 wcharToMultibyte(const wchar_t* wstr, u32 wstr_len, char* str);

void consoleWrite(primeLogLevel level, const char* msg);
void initInput();