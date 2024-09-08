#pragma once

#include "prime/prime_defines.h"
#include <Windows.h>

namespace prime {

	void DummyWglContext(i32* versionMajor, i32* versionMinor);

	HGLRC CreateWglContext(HWND window, i32 versionMajor, i32 versionMinor);
	void DeleteWglContext(HGLRC context);
	void UpdateWglContext(HWND window);
}
