
#pragma once

#include "PAL/PAL_buffer.h"

void* _GLCreateBuffer(PAL_BufferDesc desc);
void _GLDestroyBuffer(void* handle);

void _GLBindBuffer(void* handle);
void _GLSetBufferData(void* handle, void* data, u32 size);