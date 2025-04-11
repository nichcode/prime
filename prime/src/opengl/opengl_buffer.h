
#pragma once

#include "prime/buffer.h"

void* _GLCreateBuffer(prBufferDesc desc);
void _GLDestroyBuffer(void* handle);

void _GLBindBuffer(void* handle);
void _GLSetBufferData(void* handle, void* data, u32 size);