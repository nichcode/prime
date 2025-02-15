#pragma once

#include "prime/prime_layout.h"

void*
primeGLLayoutCreate(primeVertexbufferDesc vb0, primeIndexbufferDesc ibo);

void
primeGLLayoutDestroy(void* layout);

void
primeGLLayoutBind(void* layout);

void
primeGLLayoutUnbind(void* layout);

void
primeGLLayoutSetData(void* layout, const void* data, u32 size);

void
primeGLLayoutPush(void* layout, u32 index, u32 count, primeType type, u64 offset, u32 stride);