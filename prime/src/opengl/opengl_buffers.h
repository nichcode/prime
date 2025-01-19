#pragma once

#include "prime/prime_buffers.h"

struct prime_VertexbufferHandle;

prime_VertexbufferHandle*
prime_GLCreateVertexbufferHandle(const void* data, u32 size, prime_VertexbufferType type);

void
prime_GLDestroyVertexbufferHandle(prime_VertexbufferHandle* handle);

void
prime_GLBindVertexbufferHandle(prime_VertexbufferHandle* handle);

void
prime_GLUnbindVertexbufferHandle(prime_VertexbufferHandle* handle);

void
prime_GLSetVertexbufferLayout(const prime_BufferElement* element, u32 stride);

void
prime_GLSetVertexbufferHandleData(prime_VertexbufferHandle* handle, const void* data, u32 size);