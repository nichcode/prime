#pragma once

#include "prime/prime_buffers.h"

void*
gl_CreateVertexbuffer(const void* data, u32 size, prime_VertexbufferType type);

void
gl_DestroyVertexbuffer(void* handle);

void
gl_BindVertexbuffer(void* handle);

void
gl_UnbindVertexbuffer(void* handle);

void
gl_SetVertexbufferLayout(void* handle, const prime_BufferElement* element, u32 stride);

void
gl_SetVertexbufferData(void* handle, const void* data, u32 size);

void*
gl_CreateIndexbuffer(u32* indices, u32 count);

void
gl_DestroyIndexbuffer(void* handle);

void
gl_BindIndexbuffer(void* handle);

void
gl_UnbindIndexbuffer(void* handle);
