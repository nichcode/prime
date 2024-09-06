#pragma once

#include "prime_defines.h"

namespace prime {

	struct WindowHandle 
	{
		void* m_ptr = nullptr;

		b8 operator==(WindowHandle& handle)
		{
			return m_ptr == handle.m_ptr;
		}
	};

	struct WindowProperties 
	{
		u32 Width = 640, Height = 480;
		str Title = "PrimeWindow";
		b8 Center = false, Maximize = false;
		i32 XPos = 100, YPos = 100;
	};

	class Window
	{
	private:
		WindowHandle m_Handle;
		WindowProperties m_Props;

	public:
		void Init(const WindowProperties& props);
		void Destroy();
	};

	void PullEvents();
}
