#pragma once

#include "prime/prime_layout.h"

void*
primeGLLayoutCreate();

void
primeGLLayoutDestroy(void* layout);

void
primeGLLayoutBind(void* layout);

void
primeGLLayoutUnbind(void* layout);

void
primeGLLayoutPush(void* layout, u32 index, u32 count, primeType type, u64 offset, u32 stride);