
#pragma once

#include "prime/context.h"

void* glCreateContext(primeWindow* window);
void glDestroyContext(void* context);

void _glClear(void* context);
void glPresent(void* context);

void glSubmit(void* context, primeDrawType type, primeDrawMode mode, u32 count);
void glSubmitInstanced(void* context, primeDrawType type, primeDrawMode mode, u32 count, u32 ins_count);

void glMakeActive(void* context);
void glSetVsync(void* context, b8 vsync);
void glSetClearColor(void* context, f32 r, f32 g, f32 b, f32 a);
void glSetView(void* context, const primeView* view);

void* glCreateBuffer(primeBufferDesc desc);
void glDestroyBuffer(void* buffer);

void* _glCreateShader(primeShaderDesc desc);
void glDestroyShader(void* shader);

void* glCreateLayout();
void glDestroyLayout(void* layout);

void glSetData(void* buffer, const void* data, u32 size);
void glAddAttrib(void* layout, primeDataType type, u32 divisor, b8 normalize);

void glSetInt(void* shader, const char* name, i32 data);
void glSetIntArray(void* shader, const char* name, i32* data, u32 count);
void glSetFloat(void* shader, const char* name, f32 data);
void glSetFloat2(void* shader, const char* name, primeVec2 data);
void glSetFloat3(void* shader, const char* name, primeVec3 data);
void glSetFloat4(void* shader, const char* name, primeVec4 data);
void glSetMat2(void* shader, const char* name, primeMat2 data);
void glSetMat3(void* shader, const char* name, primeMat3 data);
void glSetMat4(void* shader, const char* name, primeMat4 data);

void glSetBuffer(void* buffer);
void glSetShader(void* shader);
void glSetLayout(void* layout);