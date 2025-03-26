
#pragma once

#include "defines.h"

struct primeLayout;

enum primeDataType
{
    PRIME_DATA_TYPE_INT,
    PRIME_DATA_TYPE_INT2,
    PRIME_DATA_TYPE_INT3,
    PRIME_DATA_TYPE_INT4,
    PRIME_DATA_TYPE_FLOAT,
    PRIME_DATA_TYPE_FLOAT2,
    PRIME_DATA_TYPE_FLOAT3,
    PRIME_DATA_TYPE_FLOAT4,
    PRIME_DATA_TYPE_BOOL
};

PRIME_API primeLayout* primeCreateLayout();
PRIME_API void primeDestroyLayout(primeLayout* layout);

PRIME_API void primeAddAttrib(primeLayout* layout, primeDataType type, u32 divisor, b8 normalize);
PRIME_API void primeBindLayout(primeLayout* layout);
PRIME_API void primeUnbindLayout(primeLayout* layout);