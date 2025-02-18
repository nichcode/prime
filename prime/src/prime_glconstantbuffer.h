
#pragma once

#include "prime/prime_constantbuffer.h"

void*
primeGLConstantbufferCreate(u32 size, u32 binding);

void
primeGLConstantbufferDestroy(void* handle);

void
primeGLConstantbufferBind(void* handle);

void
primeGLConstantbufferUnbind(void* handle);

void
primeGLConstantbufferSetData(void* handle, const void* data, u32 size);