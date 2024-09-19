#pragma once

#include "prime/prime_defines.h"
#include <Windows.h>

namespace prime {

	void DummyWglContext();

	HGLRC CreateWglContext(HWND window);
	void DeleteWglContext(HGLRC context);
	void UpdateWglContext(HWND window);

	void SetWGLVSync(int interval);
}
