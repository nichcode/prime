#pragma once

#include "prime_defines.h"

namespace prime {

	enum DriverTypes : u8
	{
		DriverTypesNone,

#ifdef PPLATFORM_WINDOWS
		DriverTypesDirectX11,
		DriverTypesOpenGL
#endif // PPLATFORM_WINDOWS
	};
}
