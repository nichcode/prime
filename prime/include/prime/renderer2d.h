
#pragma once

#include "prime/rect.h"
#include "prime/maths.h"

struct primeContext;
struct primeRenderer2D;

PRIME_API primeRenderer2D* primeCreateRenderer2D(primeContext* context);
PRIME_API void primeDestroyRenderer2D(primeRenderer2D* renderer);

PRIME_API void primeDrawRect(primeRenderer2D* renderer, const primeRect rect);
PRIME_API void primeRenderer2DFlush(primeRenderer2D* renderer);

PRIME_API void primeSetDrawColor(primeRenderer2D* renderer, const primeVec4 color);
PRIME_API void primeSetDrawColori(primeRenderer2D* renderer, const primeVec4u color);
