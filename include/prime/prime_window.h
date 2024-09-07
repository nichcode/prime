#pragma once

#include "prime_defines.h"
#include "prime_keycodes.h"

namespace prime {

	class Window;
	struct WindowHandle 
	{
		void* Ptr = nullptr;
	};

	struct WindowProperties 
	{
		u32 Width = 640, Height = 480;
		str Title = "PrimeWindow";
		b8 Center = false, Maximize = false, Hidden = false;
		i32 XPos = 100, YPos = 100;
	};

	using CloseFunc = void(*)(const Window* window);
	using KeyFunc = void(*)(const Window* window, u16 key, i32 scancode, u8 action);

	struct Callbacks
	{
		CloseFunc Close = nullptr;
		KeyFunc Key = nullptr;
	};

	struct WindowData 
	{
		WindowProperties Props;
		Callbacks Callbacks;
		b8 ShouldClose = false;

		u16 Keycodes[512] = {};
		u16 Scancodes[(u16)Keys::KeyMax + 1] = {};
		str Keynames[(u16)Keys::KeyMax + 1] = {};

		WindowData()
		{
			memset(Keycodes, 0, sizeof(Keycodes));
			memset(Scancodes, 0, sizeof(Scancodes));
		}
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

		// keys
		PINLINE str GetKeyName(u16 key) const
		{ 
			if (key >= 0 && key < (u16)Keys::KeyMax) { 
				return m_Data.Keynames[key]; 
			}
			return "";
		}

		void SetCloseCallback(CloseFunc func);
		void SetKeyCallback(KeyFunc func);

		PINLINE b8 operator==(const Window& window)
		{
			return m_Handle.Ptr == window.GetHandle().Ptr;
		}

		PINLINE b8 operator==(const Window* window)
		{
			return m_Handle.Ptr == window->GetHandle().Ptr;
		}
	};

	void PullEvents();
}
