#pragma once

#include "prime/defines.h"
#include <Windows.h>

namespace prime {

	void dummy_wgl_context();

	HGLRC create_wgl_context(HWND window);
	void delete_wgl_context(HGLRC context);
	void update_wgl_context(HWND window);

	void set_wgl_vsync(int interval);
}
