#pragma once

#include "prime_defines.h"
#include "prime_keycodes.h"
#include "prime_mousecodes.h"

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
	using MouseButtonFunc = void(*)(const Window* window, u16 mouse, u8 action);
	using MouseMovedFunc = void(*)(const Window* window, i32 x, i32 y);
	using MouseScrolledFunc = void(*)(const Window* window, f32 xOffset, f32 yOffset);
	using WindowPosFunc = void(*)(const Window* window, i32 x, i32 y);
	using WindowResizeFunc = void(*)(const Window* window, u32 width, u32 height);
	using WindowFocusFunc = void(*)(const Window* window, b8 focused);

	struct WindowData 
	{
		WindowProperties Props;
		b8 ShouldClose = false, IsFocused = false;

		u16 Keycodes[512] = {};
		u16 Scancodes[Key_Max + 1] = {};
		str Keynames[Key_Max + 1] = {};

		u8 keys[Key_Max + 1] = {};
		u8 Mouse[Mouse_Max + 1] = {};

		i32 MousePos[2] = {};

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
		void* m_UserData;

	public:
		Window() :m_UserData(nullptr) {}

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
		
		void SetUserData(void* userDataPtr) { m_UserData = userDataPtr; }
		PINLINE void* GetUserData() { return m_UserData; }

		PINLINE b8 GetKeyState(u16 key) const {
			return m_Data.keys[key] == PPRESS;
		}

		PINLINE str GetKeyName(u16 key) const
		{ 
			if (key >= 0 && key < (u16)Keys::Key_Max) { 
				return m_Data.Keynames[key];
			}
			return "";
		}

		PINLINE str GetMouseName(u16 mouse) const
		{
			switch (mouse)
			{
			case 0:
				return "Mouse_Left";
				break;
			case 1:
				return "Mouse_Right";
				break;
			case 2:
				return "Mouse_Middle";
				break;
			}
			return "";
		}

		PINLINE str GetActionName(u8 action) const
		{
			if (action == PRELEASE) {
				return "Release";
			}
			else if (action == PPRESS) {
				return "Press";
			}
			else if (action == PREPEAT) {
				return "Repeat";
			}
			return "";
		}

		PINLINE b8 operator==(const Window& window)
		{
			return m_Handle.Ptr == window.GetHandle().Ptr;
		}

		PINLINE b8 operator==(const Window* window)
		{
			return m_Handle.Ptr == window->GetHandle().Ptr;
		}
	};

	void PollEvents();

	void SetWindowCloseCallback(CloseFunc func);
	void SetWindowKeyCallback(KeyFunc func);
	void SetWindowMouseButtonCallback(MouseButtonFunc func);
	void SetWindowMouseMovedCallback(MouseMovedFunc func);
	void SetWindowMouseScrolledCallback(MouseScrolledFunc func);
	void SetWindowPosCallback(WindowPosFunc func);
	void SetWindowResizeCallback(WindowResizeFunc func);
	void SetWindowFocusCallback(WindowFocusFunc func);
}
