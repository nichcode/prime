#pragma once

#include "prime_defines.h"

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

PAPI primeLayout*
primeLayoutCreate(primeDevice* device, primeVertexbufferDesc vbo, primeIndexbufferDesc ibo);

PAPI void
primeLayoutDestroy(primeLayout* layout);

PAPI void
primeLayoutAdd(primeLayout* layout, primeType type);

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