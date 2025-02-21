#pragma once

#include "prime_defines.h"
#include "prime_math.h"

enum primeType
{
	primeTypeInt,
	primeTypeInt2,
	primeTypeInt3,
	primeTypeInt4,
	primeTypeFloat,
	primeTypeFloat2,
	primeTypeFloat3,
	primeTypeFloat4,
	primeTypeMat3,
	primeTypeMat4,
	primeTypeBool
};

enum primeBufferType
{
	primeBufferTypeStatic,
	primeBufferTypeDynamic
};

enum primeShaderType
{
	primeShaderTypeGLSL
};

struct primeVertexbufferDesc
{
	void* data = nullptr;
	u32 size = 0;
	primeBufferType type = primeBufferTypeDynamic;
};

struct primeIndexbufferDesc
{
	u32* indices = nullptr;
	u32 count = 0;
};

struct primeShaderDesc
{
	const char* vertex = nullptr;
	const char* pixel = nullptr;
	b8 load = true;
	primeShaderType type = primeShaderTypeGLSL;
};

struct primeLayoutDesc
{
	primeVertexbufferDesc vbo;
	primeShaderDesc shader;
	primeIndexbufferDesc ibo;
};

PAPI primeLayout*
primeLayoutCreate(primeDevice* device, const primeLayoutDesc* desc);

PAPI void
primeLayoutDestroy(primeLayout* layout);

PAPI void
primeLayoutAdd(primeLayout* layout, primeType type, u32 divisor);

PAPI void
primeLayoutBind(primeLayout* layout);

PAPI void
primeLayoutUnbind(primeLayout* layout);

PAPI void
primeLayoutSetData(primeLayout* layout, const void* data, u32 size);

PAPI u32
primeLayoutGetCount(primeLayout* layout);

PAPI void
primeLayoutSubmit(primeLayout* layout);

PAPI void
primeLayoutSetInt(primeLayout* layout, const char* name, i32 data);

PAPI void
primeLayoutSetIntArray(primeLayout* layout, const char* name, i32* data, u32 count);

PAPI void
primeLayoutSetFloat(primeLayout* layout, const char* name, f32 data);

PAPI void
primeLayoutSetFloat2(primeLayout* layout, const char* name, primeVec2 data);

PAPI void
primeLayoutSetFloat3(primeLayout* layout, const char* name, primeVec3 data);

PAPI void
primeLayoutSetFloat4(primeLayout* layout, const char* name, primeVec4 data);

PAPI void
primeLayoutSetMat4(primeLayout* layout, const char* name, primeMat4 data);