#pragma once

#include "prime_defines.h"

namespace prime {

	struct WindowHandle 
	{
		void* Ptr = nullptr;

		b8 operator==(WindowHandle& handle)
		{
			return Ptr == handle.Ptr;
		}
	};

	struct WindowProperties 
	{
		u32 Width = 640, Height = 480;
		str Title = "PrimeWindow";
		b8 Center = false, Maximize = false, Hidden = false;
		i32 XPos = 100, YPos = 100;
	};

	using WindowCloseFunc = void(*)(const WindowHandle);
	struct Callbacks
	{
		WindowCloseFunc CloseCallback;
	};

	struct WindowData 
	{
		WindowProperties Props;
		Callbacks Callbacks;
		b8 ShouldClose = false;
	};

	class Window
	{
	private:
		WindowHandle m_Handle;
		WindowData m_Data;

	public:
		void Init(const WindowProperties& props);
		void Destroy();

		PINLINE WindowHandle GetHandle() const { return m_Handle; }
		PINLINE u32 GetWidth() const { return m_Data.Props.Width; }
		PINLINE u32 GetHeight() const { return m_Data.Props.Height; }

		PINLINE i32 GetXPos() const { return m_Data.Props.XPos; }
		PINLINE i32 GetYPos() const { return m_Data.Props.YPos; }
		PINLINE str GetTitle() const { return m_Data.Props.Title; }

		PINLINE b8 IsHidden() const { return m_Data.Props.Hidden; }
		PINLINE b8 ShouldClose() const { return m_Data.ShouldClose; }

		void Hide();
		void Show();

		void SetTitle(const str& title);
		void SetPos(i32 xPos, i32 yPos);
		void SetSize(u32 width, u32 height);

		void SetCloseCallback(WindowCloseFunc func);
	};

	void PullEvents();
}
