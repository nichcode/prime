
#pragma once

#include "defines.h"

struct primeLayout;

using primeDataType = u32;

enum primeDataTypes_
{
    primeDataTypes_Int,
    primeDataTypes_Int2,
    primeDataTypes_Int3,
    primeDataTypes_Int4,
    primeDataTypes_Float,
    primeDataTypes_Float2,
    primeDataTypes_Float3,
    primeDataTypes_Float4,
    primeDataTypes_Bool
};

PRIME_API primeLayout* primeCreateLayout();
PRIME_API void primeDestroyLayout(primeLayout* layout);

PRIME_API void primeAddAttrib(primeLayout* layout, primeDataType type, u32 divisor, b8 normalize);
PRIME_API void primeBindLayout(primeLayout* layout);
PRIME_API void primeUnbindLayout(primeLayout* layout);