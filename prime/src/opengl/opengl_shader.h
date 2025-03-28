
#pragma once

#include "prime/shader.h"

void* _glCreateShader(primeShaderDesc desc);
void _glDestroyShader(void* handle);

void _glSetInt(void* handle, const char* name, i32 data);
void _glSetIntArray(void* handle, const char* name, i32* data, u32 count);
void _glSetFloat(void* handle, const char* name, f32 data);
void _glSetFloat2(void* handle, const char* name, primeVec2 data);
void _glSetFloat3(void* handle, const char* name, primeVec3 data);
void _glSetFloat4(void* handle, const char* name, primeVec4 data);
void _glSetMat4(void* handle, const char* name, primeMat4 data);

void _glBindShader(void* handle);
void _glUnbindShader(void* handle);
