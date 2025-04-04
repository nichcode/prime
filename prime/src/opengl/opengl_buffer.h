
#include "prime/prime.h"

void* gl_CreateBuffer(prime_buffer_desc desc);
void gl_DestroyBuffer(void* handle);

void gl_BindBuffer(void* handle, b8 send_data);
void gl_SetBufferData(void* handle, void* data, u32 size);