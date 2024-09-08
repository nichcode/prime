#pragma once

#include "prime_defines.h"

namespace prime {

	class IDevice;
	class Window;

	enum DeviceType : u8
	{
		DeviceTypeNone,
		DeviceTypeDirectX11,
		DeviceTypeOpenGL
	};

	class Device
	{
	private:
		IDevice* m_Driver;
		DeviceType m_Type;
		Window* m_Window;

	public:
		Device() : m_Driver(nullptr), m_Type(DeviceTypeNone), m_Window(nullptr) {}
		Device(const Device&) = delete;
		Device& operator=(const Device&) = delete;

		void Init(DeviceType type, const Window* window);
		void Shutdown();

		void SetClearColor(f32 r, f32 g, f32 b, f32 a);
		void Clear();
		void SwapBuffers();
	};
}
