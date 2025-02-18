
#pragma once

#include "prime_defines.h"

PAPI primeConstantbuffer*
primeConstantbufferCreate(primeDevice* device, u32 size, u32 binding);

PAPI void
primeConstantbufferDestroy(primeConstantbuffer* buffer);

PAPI void
primeConstantbufferBind(primeConstantbuffer* buffer);

PAPI void
primeConstantbufferUnbind(primeConstantbuffer* buffer);

PAPI void
primeConstantbufferSetData(primeConstantbuffer* buffer, const void* data, u32 size);