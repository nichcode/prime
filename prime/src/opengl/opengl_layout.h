
#pragma once

#include "prime/layout.h"

void* _glCreateLayout();
void _glDestroyLayout(void* handle);

void _glAddAttrib(void* handle, primeDataType type, u32 divisor, b8 normalize);
void _glBindLayout(void* handle);
void _glUnbindLayout(void* handle);
