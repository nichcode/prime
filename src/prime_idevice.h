#pragma once

#include "prime/prime_defines.h"
#include "prime/prime_device.h"

namespace prime {

	class Window;

	class IDevice
	{
	public:
		virtual void Init(const Window* window) = 0;
		virtual void Shutdown() = 0;

		virtual void SetClearColor(f32 r, f32 g, f32 b, f32 a) = 0;
		virtual void Clear() = 0;
		virtual void SwapBuffers() = 0;

		static IDevice* Create(DeviceType type);
	};
}
