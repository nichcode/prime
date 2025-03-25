
#pragma once

#include "API.h"

PRIME_API primeContext* primeCreateContext(primeWindow* window);
PRIME_API void primeDestroyContext(primeContext* context);

PRIME_API void primeClear(primeContext* context);
PRIME_API void primePresent(primeContext* context);

PRIME_API void primeSubmit(primeContext* context, primeDrawType type, primeDrawMode mode, u32 count);
PRIME_API void primeSubmitInstanced(primeContext* context, primeDrawType type, primeDrawMode mode, u32 count, u32 instance_count);

PRIME_API void primeSetVsync(primeContext* context, b8 vsync);
PRIME_API void primeSetClearColor(primeContext* context, const primeVec4 color);
PRIME_API void primeSetClearColori(primeContext* context, const primeVec4u color);

PRIME_API void primeSetView(primeContext* context, const primeView view);
PRIME_API const primeView* primeGetView(primeContext* context);

PRIME_API primeBuffer* primeCreateBuffer(primeContext* context, primeBufferDesc desc);
PRIME_API void primeDestroyBuffer(primeBuffer* buffer);

PRIME_API primeShader* primeCreateShader(primeContext* context, primeShaderDesc desc);
PRIME_API void primeDestroyShader(primeShader* shader);

PRIME_API primeLayout* primeCreateLayout(primeContext* context);
PRIME_API void primeDestroyLayout(primeLayout* layout);

PRIME_API void primeSetData(primeBuffer* buffer, const void* data, u32 size);
PRIME_API void primeAddAttrib(primeLayout* layout, primeDataType type, u32 divisor, b8 normalize);

PRIME_API void primeSetInt(primeShader* shader, const char* name, i32 data);
PRIME_API void primeSetIntArray(primeShader* shader, const char* name, i32* data, u32 count);
PRIME_API void primeSetFloat(primeShader* shader, const char* name, f32 data);
PRIME_API void primeSetFloat2(primeShader* shader, const char* name, primeVec2 data);
PRIME_API void primeSetFloat3(primeShader* shader, const char* name, primeVec3 data);
PRIME_API void primeSetFloat4(primeShader* shader, const char* name, primeVec4 data);
PRIME_API void primeSetMat2(primeShader* shader, const char* name, primeMat2 data);
PRIME_API void primeSetMat3(primeShader* shader, const char* name, primeMat3 data);
PRIME_API void primeSetMat4(primeShader* shader, const char* name, primeMat4 data);

PRIME_API void primeSetBuffer(primeBuffer* buffer);
PRIME_API void primeSetShader(primeShader* shader);
PRIME_API void primeSetLayout(primeLayout* layout);