
#pragma once

#include "prime/buffer.h"

void* _glCreateBuffer(primeBufferDesc desc);
void _glDestroyBuffer(void* handle);

void _glSetBufferData(void* handle, const void* data, u32 size);

void _glBindBuffer(void* handle);
void _glUnbindBuffer(void* handle);