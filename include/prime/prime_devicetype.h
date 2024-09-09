#pragma once

#include "prime_defines.h"

namespace prime {

	enum DeviceType : u8
	{
		DeviceTypeNone,

#ifdef PPLATFORM_WINDOWS
		DeviceTypeDirectX11,
		DeviceTypeOpenGL
#endif // PPLATFORM_WINDOWS
	};
}
