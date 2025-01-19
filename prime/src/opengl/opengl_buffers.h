#pragma once

#include "prime/prime_buffers.h"

struct prime_VertexbufferHandle;
struct prime_IndexbufferHandle;

prime_VertexbufferHandle*
gl_CreateVertexbuffer(const void* data, u32 size, prime_VertexbufferType type);

void
gl_DestroyVertexbuffer(prime_VertexbufferHandle* handle);

void
gl_BindVertexbuffer(prime_VertexbufferHandle* handle);

void
gl_UnbindVertexbuffer(prime_VertexbufferHandle* handle);

void
gl_SetVertexbufferLayout(const prime_BufferElement* element, u32 stride);

void
gl_SetVertexbufferData(prime_VertexbufferHandle* handle, const void* data, u32 size);

prime_IndexbufferHandle*
gl_CreateIndexbuffer(u32* indices, u32 count);

void
gl_DestroyIndexbuffer(prime_IndexbufferHandle* handle);

void
gl_BindIndexbuffer(prime_IndexbufferHandle* handle);

void
gl_UnbindIndexbuffer(prime_IndexbufferHandle* handle);
