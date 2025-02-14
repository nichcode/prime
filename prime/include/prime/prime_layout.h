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

PAPI primeLayout*
primeLayoutCreate(primeDevice* device);

PAPI void
primeLayoutDestroy(primeLayout* layout);

PAPI void
primeLayoutAdd(primeLayout* layout, primeType type);

PAPI void
primeLayoutBind(primeLayout* layout);

PAPI void
primeLayoutUnbind(primeLayout* layout);

PAPI void
primeLayoutSubmit(primeLayout* layout, primeVertexbuffer* buffer);