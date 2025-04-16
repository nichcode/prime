
#pragma once

#include "PAL/PAL_shader.h"

void* _GLCreateShader(PAL_ShaderDesc desc);
void _GLDestroyShader(void* handle);
void _GLBindShader(void* handle);

void _GLSetInt(void* handle, const char* name, i32 data);
void _GLSetIntArray(void* handle, const char* name, i32* data, u32 count);
void _GLSetFloat(void* handle, const char* name, f32 data);
void _GLSetFloat2(void* handle, const char* name, f32 data, f32 data2);
void _GLSetFloat3(void* handle, const char* name, f32 data, f32 data2, f32 data3);
void _GLSetFloat4(void* handle, const char* name, f32 data, f32 data2, f32 data3, f32 data4);
void _GLSetMat4(void* handle, const char* name, f32* data);

void _GLSetLayout(void* handle, PAL_ShaderLayout* layout);
