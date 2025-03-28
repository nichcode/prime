
#pragma once

#include "prime/defines.h"

struct primeSubTexture;
struct primeSpriteSheet;

PRIME_API primeSpriteSheet* primeLoadSpriteSheet(const char* filepath);
PRIME_API void primeDestroySpriteSheet(primeSpriteSheet* sheet);
PRIME_API void primeDestroySubTexture(primeSubTexture* sub_texture);

PRIME_API primeSubTexture* primeGetSubTexture(primeSpriteSheet* sheet, f32 x, f32 y, f32 w, f32 h);