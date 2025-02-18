#pragma once

#include "prime/prime_layout.h"

void*
primeGLLayoutCreate(const primeLayoutDesc* desc, b8 shader_empty);

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

void
primeGLLayoutSetInt(void* layout, const char* name, i32 data);

void
primeGLLayoutSetIntArray(void* layout, const char* name, i32* data, u32 count);

void
primeGLLayoutSetFloat(void* layout, const char* name, f32 data);

void
primeGLLayoutSetFloat2(void* layout, const char* name, primeVec2 data);

void
primeGLLayoutSetFloat3(void* layout, const char* name, primeVec3 data);

void
primeGLLayoutSetFloat4(void* layout, const char* name, primeVec4 data);

void
primeGLLayoutSetMat4(void* layout, const char* name, primeMat4 data);