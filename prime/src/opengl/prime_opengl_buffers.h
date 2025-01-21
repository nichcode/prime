#pragma once

#include "prime/prime_buffers.h"

void*
gl_VertexbufferCreate(const void* data, u32 size, prime_VertexbufferType type);

void
gl_VertexbufferDestroy(void* handle);

void
gl_VertexbufferBind(void* handle);

void
gl_VertexbufferUnbind(void* handle);

void
gl_VertexbufferSetLayout(void* handle, const prime_BufferElement* element, u32 stride, u32 index);

void
gl_VertexbufferSetData(void* handle, const void* data, u32 size);

void*
gl_IndexbufferCreate(u32* indices, u32 count);

void
gl_IndexbufferDestroy(void* handle);

void
gl_IndexbufferBind(void* handle);

void
gl_IndexbufferUnbind(void* handle);

void*
gl_UniformbufferCreate(u32 size, u32 binding);

void
gl_UniformbufferDestroy(void* handle);

void
gl_UniformbufferBind(void* handle);

void
gl_UniformbufferUnbind(void* handle);

void
gl_UniformbufferSetData(void* handle, const void* data, u32 size);
