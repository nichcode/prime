
#include "prime/prime_window.h"
#include "prime/prime_assert.h"
#include "prime/prime_utils.h"

#ifdef PPLATFORM_WINDOWS
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // !WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace prime {

	static HINSTANCE s_Instance = NULL;
	wstr s_ClassName = L"PrimeWindowClass";
	wstr s_WindowPropName = L"PrimeWindow";
	wstr s_DataPropName = L"PrimeData";

	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static void RegisterWindowClass()
	{
		WNDCLASSEX wc;
		memset(&wc, 0, sizeof(wc));
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_DBLCLKS | CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
		wc.lpfnWndProc = WindowProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = s_Instance;
		wc.hIcon = LoadIcon(s_Instance, IDI_WINLOGO);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = NULL;
		wc.lpszClassName = s_ClassName.c_str();

		auto result = RegisterClassEx(&wc);
		PASSERT_MSG(result, "Window registration failed");
	}

	static void UneegisterWindowClass()
	{
		UnregisterClass(s_ClassName.c_str(), s_Instance);
	}

	static void CenterWindow(HWND handle, i32 *xPos, i32* yPos, u32 width, u32 height)
	{
		MONITORINFO monitorInfo = {};
		monitorInfo.cbSize = sizeof(MONITORINFO);

		GetMonitorInfo(MonitorFromWindow(handle, MONITOR_DEFAULTTONEAREST), &monitorInfo);
		int x = (monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left - width) / 2;
		int y = (monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top - height) / 2;

		*xPos = x;
		*yPos = y;;
		SetWindowPos(handle, 0, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_SHOWWINDOW);
	}

	static void MapKeys(WindowData& data)
	{
		data.Keycodes[0x01E] = (u16)Keys::Key_A;
		data.Keycodes[0x030] = (u16)Keys::Key_B;
		data.Keycodes[0x02E] = (u16)Keys::Key_C;
		data.Keycodes[0x020] = (u16)Keys::Key_D;
		data.Keycodes[0x012] = (u16)Keys::Key_E;
		data.Keycodes[0x021] = (u16)Keys::Key_F;
		data.Keycodes[0x022] = (u16)Keys::Key_G;
		data.Keycodes[0x023] = (u16)Keys::Key_H;
		data.Keycodes[0x017] = (u16)Keys::Key_I;
		data.Keycodes[0x024] = (u16)Keys::Key_J;
		data.Keycodes[0x025] = (u16)Keys::Key_K;
		data.Keycodes[0x026] = (u16)Keys::Key_L;
		data.Keycodes[0x032] = (u16)Keys::Key_M;
		data.Keycodes[0x031] = (u16)Keys::Key_N;
		data.Keycodes[0x018] = (u16)Keys::Key_O;
		data.Keycodes[0x019] = (u16)Keys::Key_P;
		data.Keycodes[0x010] = (u16)Keys::Key_Q;
		data.Keycodes[0x013] = (u16)Keys::Key_R;
		data.Keycodes[0x01F] = (u16)Keys::Key_S;
		data.Keycodes[0x014] = (u16)Keys::Key_T;
		data.Keycodes[0x016] = (u16)Keys::Key_U;
		data.Keycodes[0x02F] = (u16)Keys::Key_V;
		data.Keycodes[0x011] = (u16)Keys::Key_W;
		data.Keycodes[0x02D] = (u16)Keys::Key_X;
		data.Keycodes[0x015] = (u16)Keys::Key_Y;
		data.Keycodes[0x02C] = (u16)Keys::Key_Z;

		data.Keycodes[0x00B] = (u16)Keys::Key_0;
		data.Keycodes[0x002] = (u16)Keys::Key_1;
		data.Keycodes[0x003] = (u16)Keys::Key_2;
		data.Keycodes[0x004] = (u16)Keys::Key_3;
		data.Keycodes[0x005] = (u16)Keys::Key_4;
		data.Keycodes[0x006] = (u16)Keys::Key_5;
		data.Keycodes[0x007] = (u16)Keys::Key_6;
		data.Keycodes[0x008] = (u16)Keys::Key_7;
		data.Keycodes[0x009] = (u16)Keys::Key_8;
		data.Keycodes[0x00A] = (u16)Keys::Key_9;

		data.Keycodes[0x028] = (u16)Keys::Key_Apostrophe;
		data.Keycodes[0x02B] = (u16)Keys::Key_Backslash;
		data.Keycodes[0x033] = (u16)Keys::Key_Comma;
		data.Keycodes[0x00D] = (u16)Keys::Key_Equal;
		data.Keycodes[0x029] = (u16)Keys::Key_GraveAccent;
		data.Keycodes[0x01A] = (u16)Keys::Key_LeftBracket;
		data.Keycodes[0x00C] = (u16)Keys::Key_Minus;
		data.Keycodes[0x034] = (u16)Keys::Key_Period;
		data.Keycodes[0x01B] = (u16)Keys::Key_RightBracket;
		data.Keycodes[0x027] = (u16)Keys::Key_SemiColon;
		data.Keycodes[0x035] = (u16)Keys::Key_Slash;

		data.Keycodes[0x00E] = (u16)Keys::Key_Backspace;
		data.Keycodes[0x153] = (u16)Keys::Key_Delete;
		data.Keycodes[0x14F] = (u16)Keys::Key_End;
		data.Keycodes[0x01C] = (u16)Keys::Key_Enter;
		data.Keycodes[0x001] = (u16)Keys::Key_Escape;
		data.Keycodes[0x147] = (u16)Keys::Key_Home;
		data.Keycodes[0x152] = (u16)Keys::Key_Insert;
		data.Keycodes[0x15D] = (u16)Keys::Key_Menu;
		data.Keycodes[0x151] = (u16)Keys::Key_PageDown;
		data.Keycodes[0x149] = (u16)Keys::Key_PageUp;
		data.Keycodes[0x045] = (u16)Keys::Key_Pause;
		data.Keycodes[0x039] = (u16)Keys::Key_Space;
		data.Keycodes[0x00F] = (u16)Keys::Key_Tab;
		data.Keycodes[0x03A] = (u16)Keys::Key_CapsLock;
		data.Keycodes[0x145] = (u16)Keys::Key_NumLock;
		data.Keycodes[0x046] = (u16)Keys::Key_ScrollLock;
		data.Keycodes[0x03B] = (u16)Keys::Key_F1;
		data.Keycodes[0x03C] = (u16)Keys::Key_F2;
		data.Keycodes[0x03D] = (u16)Keys::Key_F3;
		data.Keycodes[0x03E] = (u16)Keys::Key_F4;
		data.Keycodes[0x03F] = (u16)Keys::Key_F5;
		data.Keycodes[0x040] = (u16)Keys::Key_F6;
		data.Keycodes[0x041] = (u16)Keys::Key_F7;
		data.Keycodes[0x042] = (u16)Keys::Key_F8;
		data.Keycodes[0x043] = (u16)Keys::Key_F9;
		data.Keycodes[0x044] = (u16)Keys::Key_F10;
		data.Keycodes[0x057] = (u16)Keys::Key_F11;
		data.Keycodes[0x058] = (u16)Keys::Key_F12;

		data.Keycodes[0x038] = (u16)Keys::Key_LeftAlt;
		data.Keycodes[0x01D] = (u16)Keys::Key_LeftControl;
		data.Keycodes[0x02A] = (u16)Keys::Key_LeftShift;
		data.Keycodes[0x15B] = (u16)Keys::Key_LeftSuper;
		data.Keycodes[0x137] = (u16)Keys::Key_PrintScreen;
		data.Keycodes[0x138] = (u16)Keys::Key_RightAlt;
		data.Keycodes[0x11D] = (u16)Keys::Key_RightControl;
		data.Keycodes[0x036] = (u16)Keys::Key_RightShift;
		data.Keycodes[0x15C] = (u16)Keys::Key_RightSuper;
		data.Keycodes[0x150] = (u16)Keys::Key_Down;
		data.Keycodes[0x14B] = (u16)Keys::Key_Left;
		data.Keycodes[0x14D] = (u16)Keys::Key_Right;
		data.Keycodes[0x148] = (u16)Keys::Key_Up;

		data.Keycodes[0x052] = (u16)Keys::Key_P0;
		data.Keycodes[0x04F] = (u16)Keys::Key_P1;
		data.Keycodes[0x050] = (u16)Keys::Key_P2;
		data.Keycodes[0x051] = (u16)Keys::Key_P3;
		data.Keycodes[0x04B] = (u16)Keys::Key_P4;
		data.Keycodes[0x04C] = (u16)Keys::Key_P5;
		data.Keycodes[0x04D] = (u16)Keys::Key_P6;
		data.Keycodes[0x047] = (u16)Keys::Key_P7;
		data.Keycodes[0x048] = (u16)Keys::Key_P8;
		data.Keycodes[0x049] = (u16)Keys::Key_P9;
		data.Keycodes[0x04E] = (u16)Keys::Key_PAdd;
		data.Keycodes[0x053] = (u16)Keys::Key_PDecimal;
		data.Keycodes[0x135] = (u16)Keys::Key_PDivide;
		data.Keycodes[0x11C] = (u16)Keys::Key_PEnter;
		data.Keycodes[0x059] = (u16)Keys::Key_PEqual;
		data.Keycodes[0x037] = (u16)Keys::Key_PMultiply;
		data.Keycodes[0x04A] = (u16)Keys::Key_PSubtract;

		/*i32 scancode = 0;
		for (scancode = 0; scancode < 512; scancode++) {
			if (data.Keycodes[scancode] > 0) {
				data.Keycodes[scancode] = scancode;
				data.Scancodes[data.Keycodes[scancode]] = scancode;
			}
		}*/
	}

	static void MapKeysNames(WindowData& data)
	{
		//data.Keynames.reserve((u64)Keys::KeyMax);

		data.Keynames[(u16)Keys::Key_A] = str("Key A");
		data.Keynames[(u16)Keys::Key_B] = "Key B";
		data.Keynames[(u16)Keys::Key_C] = "Key C";
		data.Keynames[(u16)Keys::Key_D] = "Key D";
		data.Keynames[(u16)Keys::Key_E] = "Key E";
		data.Keynames[(u16)Keys::Key_F] = "Key F";
		data.Keynames[(u16)Keys::Key_G] = "Key G";
		data.Keynames[(u16)Keys::Key_H] = "Key H";
		data.Keynames[(u16)Keys::Key_I] = "Key I";
		data.Keynames[(u16)Keys::Key_J] = "Key J";
		data.Keynames[(u16)Keys::Key_K] = "Key K";
		data.Keynames[(u16)Keys::Key_L] = "Key L";
		data.Keynames[(u16)Keys::Key_M] = "Key M";
		data.Keynames[(u16)Keys::Key_N] = "Key N";
		data.Keynames[(u16)Keys::Key_O] = "Key O";
		data.Keynames[(u16)Keys::Key_P] = "Key P";
		data.Keynames[(u16)Keys::Key_Q] = "Key Q";
		data.Keynames[(u16)Keys::Key_R] = "Key R";
		data.Keynames[(u16)Keys::Key_S] = "Key S";
		data.Keynames[(u16)Keys::Key_T] = "Key T";
		data.Keynames[(u16)Keys::Key_U] = "Key U";
		data.Keynames[(u16)Keys::Key_V] = "Key V";
		data.Keynames[(u16)Keys::Key_W] = "Key W";
		data.Keynames[(u16)Keys::Key_X] = "Key X";
		data.Keynames[(u16)Keys::Key_Y] = "Key Y";
		data.Keynames[(u16)Keys::Key_Z] = "Key Z";

		data.Keynames[(u16)Keys::Key_Escape] = "Key Escape";
		data.Keynames[(u16)Keys::Key_Enter] = "Key Enter";
		data.Keynames[(u16)Keys::Key_Tab] = "Key Tab";
		data.Keynames[(u16)Keys::Key_Backspace] = "Key Backspace";
		data.Keynames[(u16)Keys::Key_Insert] = "Key Insert";
		data.Keynames[(u16)Keys::Key_Delete] = "Key Delete";
		data.Keynames[(u16)Keys::Key_Right] = "Key Right";
		data.Keynames[(u16)Keys::Key_Left] = "Key Left";
		data.Keynames[(u16)Keys::Key_Down] = "Key Down";
		data.Keynames[(u16)Keys::Key_Up] = "Key Up";
		data.Keynames[(u16)Keys::Key_PageUp] = "Key PageUp";
		data.Keynames[(u16)Keys::Key_PageDown] = "Key PageDown";
		data.Keynames[(u16)Keys::Key_Home] = "Key Home";
		data.Keynames[(u16)Keys::Key_End] = "Key End";
		data.Keynames[(u16)Keys::Key_CapsLock] = "Key CapsLock";
		data.Keynames[(u16)Keys::Key_ScrollLock] = "Key ScrollLock";
		data.Keynames[(u16)Keys::Key_NumLock] = "Key NumLock";
		data.Keynames[(u16)Keys::Key_PrintScreen] = "Key Pru16Screen";
		data.Keynames[(u16)Keys::Key_Pause] = "Key Pause";
		data.Keynames[(u16)Keys::Key_F1] = "Key F1";
		data.Keynames[(u16)Keys::Key_F2] = "Key F2";
		data.Keynames[(u16)Keys::Key_F3] = "Key F3";
		data.Keynames[(u16)Keys::Key_F4] = "Key F4";
		data.Keynames[(u16)Keys::Key_F5] = "Key F5";
		data.Keynames[(u16)Keys::Key_F6] = "Key F6";
		data.Keynames[(u16)Keys::Key_F7] = "Key F7";
		data.Keynames[(u16)Keys::Key_F8] = "Key F8";
		data.Keynames[(u16)Keys::Key_F9] = "Key F9";
		data.Keynames[(u16)Keys::Key_F10] = "Key F10";
		data.Keynames[(u16)Keys::Key_F11] = "Key F11";
		data.Keynames[(u16)Keys::Key_F12] = "Key F12";

		data.Keynames[(u16)Keys::Key_LeftShift] = "Key LeftShift";
		data.Keynames[(u16)Keys::Key_LeftControl] = "Key LeftControl";
		data.Keynames[(u16)Keys::Key_LeftAlt] = "Key LeftAlt";
		data.Keynames[(u16)Keys::Key_LeftSuper] = "Key LeftSuper";
		data.Keynames[(u16)Keys::Key_LeftBracket] = "Key LeftBracket";
		data.Keynames[(u16)Keys::Key_RightShift] = "Key RightShift";
		data.Keynames[(u16)Keys::Key_RightControl] = "Key RightControl";
		data.Keynames[(u16)Keys::Key_RightAlt] = "Key RightAlt";
		data.Keynames[(u16)Keys::Key_RightSuper] = "Key RightSuper";
		data.Keynames[(u16)Keys::Key_RightBracket] = "Key RightBracket";

		data.Keynames[(u16)Keys::Key_Menu] = "Key Menu";
		data.Keynames[(u16)Keys::Key_Backslash] = "Key Backslash";
		data.Keynames[(u16)Keys::Key_GraveAccent] = "Key GraveAccent";
		data.Keynames[(u16)Keys::Key_SemiColon] = "Key SemiColon";
		data.Keynames[(u16)Keys::Key_Equal] = "Key Equal";

		data.Keynames[(u16)Keys::Key_Space] = "Key Space";
		data.Keynames[(u16)Keys::Key_Apostrophe] = "Key Apostrophe";
		data.Keynames[(u16)Keys::Key_Comma] = "Key Comma";
		data.Keynames[(u16)Keys::Key_Minus] = "Key Minus";
		data.Keynames[(u16)Keys::Key_Period] = "Key Period";
		data.Keynames[(u16)Keys::Key_Slash] = "Key Slash";

		data.Keynames[(u16)Keys::Key_0] = "Key 0";
		data.Keynames[(u16)Keys::Key_1] = "Key 1";
		data.Keynames[(u16)Keys::Key_2] = "Key 2";
		data.Keynames[(u16)Keys::Key_3] = "Key 3";
		data.Keynames[(u16)Keys::Key_4] = "Key 4";
		data.Keynames[(u16)Keys::Key_5] = "Key 5";
		data.Keynames[(u16)Keys::Key_6] = "Key 6";
		data.Keynames[(u16)Keys::Key_7] = "Key 7";
		data.Keynames[(u16)Keys::Key_8] = "Key 8";
		data.Keynames[(u16)Keys::Key_9] = "Key 9";

		data.Keynames[(u16)Keys::Key_P0] = "Key P0";
		data.Keynames[(u16)Keys::Key_P1] = "Key P1";
		data.Keynames[(u16)Keys::Key_P2] = "Key P2";
		data.Keynames[(u16)Keys::Key_P3] = "Key P3";
		data.Keynames[(u16)Keys::Key_P4] = "Key P4";
		data.Keynames[(u16)Keys::Key_P5] = "Key P5";
		data.Keynames[(u16)Keys::Key_P6] = "Key P6";
		data.Keynames[(u16)Keys::Key_P7] = "Key P7";
		data.Keynames[(u16)Keys::Key_P8] = "Key P8";
		data.Keynames[(u16)Keys::Key_P9] = "Key P9";
		data.Keynames[(u16)Keys::Key_PDecimal] = "Key PDecimal";
		data.Keynames[(u16)Keys::Key_PDivide] = "Key PDivide";
		data.Keynames[(u16)Keys::Key_PMultiply] = "Key PMultiply";
		data.Keynames[(u16)Keys::Key_PSubtract] = "Key PSubtract";
		data.Keynames[(u16)Keys::Key_PAdd] = "Key PAdd";
		data.Keynames[(u16)Keys::Key_PEnter] = "Key PEnter";
		data.Keynames[(u16)Keys::Key_PEqual] = "Key PEqual";
	}

	static void ProcessKey(Window* window, WindowData* data, u16 key, i32 scancode, u8 action)
	{
		PASSERT_MSG(key >= 0 && key < (u16)Keys::KeyMax, "Invalid Key");
		PASSERT_MSG(action == PRELEASE || action == PPRESS, "Invalid action");

		b8 repeated = false;
		if (action == PRELEASE && data->keys[key] == PRELEASE) {
			return;
		}

		if (action == PPRESS && data->keys[key] == PPRESS) {
			repeated = true;
		}

		if (action == PPRESS && data->keys[key] == PRELEASE) {
			data->keys[key] = (u16)PPRESS;
		}
		else {
			data->keys[key] = (u16)action;
		}

		if (repeated) {
			action = PREPEAT;
		}

		if (data->Callbacks.Key) {
			data->Callbacks.Key(window, key, scancode, action);
		}
	}

	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		prime::WindowData* data = (prime::WindowData*)GetPropW(hWnd, s_DataPropName.c_str());
		prime::Window* window = (prime::Window*)GetPropW(hWnd, s_WindowPropName.c_str());

		if (!data) {
			// no window created
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}

		switch (uMsg)
		{
		case WM_DESTROY:
		case WM_CLOSE: {
			data->ShouldClose = true;
			WindowHandle handle;
			handle.Ptr = hWnd;
			if (data->Callbacks.Close) {
				data->Callbacks.Close(window);
			}	
		}break;
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
		case WM_KEYUP:
		case WM_SYSKEYUP: {
			i32 key, scancode;

			// from GLFW
			const u8 action = (HIWORD(lParam) & KF_UP) ? PRELEASE : PPRESS;
			scancode = (HIWORD(lParam) & (KF_EXTENDED | 0xff));
			if (!scancode)
			{
				// NOTE: Some synthetic key messages have a scancode of zero
				// HACK: Map the virtual key back to a usable scancode
				scancode = MapVirtualKeyW((UINT)wParam, MAPVK_VK_TO_VSC);
			}

			// HACK: Alt+PrtSc has a different scancode than just PrtSc
			if (scancode == 0x54) { scancode = 0x137; }

			// HACK: Ctrl+Pause has a different scancode than just Pause
			if (scancode == 0x146) { scancode = 0x45; }

			// HACK: CJK IME sets the extended bit for right Shift
			if (scancode == 0x136) { scancode = 0x36; }

			key = data->Keycodes[scancode];
			WindowHandle handle;
			handle.Ptr = hWnd;

			// The Ctrl keys require special handling
			if (wParam == VK_CONTROL)
			{
				if (HIWORD(lParam) & KF_EXTENDED)
				{
					// Right side keys have the extended key bit set
					key = (u16)Keys::Key_RightControl;
				}
				else
				{
					// NOTE: Alt Gr sends Left Ctrl followed by Right Alt
					// HACK: We only want one event for Alt Gr, so if we detect
					//       this sequence we discard this Left Ctrl message now
					//       and later report Right Alt normally
					MSG next;
					const DWORD time = GetMessageTime();

					if (PeekMessageW(&next, NULL, 0, 0, PM_NOREMOVE))
					{
						if (next.message == WM_KEYDOWN ||
							next.message == WM_SYSKEYDOWN ||
							next.message == WM_KEYUP ||
							next.message == WM_SYSKEYUP)
						{
							if (next.wParam == VK_MENU &&
								(HIWORD(next.lParam) & KF_EXTENDED) &&
								next.time == time)
							{
								// Next message is Right Alt down so discard this
								break;
							}
						}
					}

					// This is a regular Left Ctrl message
					key = (u16)Keys::Key_LeftControl;
				}
			}
			else if (wParam == VK_PROCESSKEY)
			{
				// IME notifies that keys have been filtered by setting the
				// virtual key-code to VK_PROCESSKEY
				break;
			}

			if (action == PRELEASE && wParam == VK_SHIFT)
			{
				// HACK: Release both Shift keys on Shift up event, as when both
				//       are pressed the first release does not emit any event
				// NOTE: The other half of this is in _glfwPollEventsWin32
				ProcessKey(window, data, (u16)Keys::Key_LeftShift, scancode, action);
				ProcessKey(window, data, (u16)Keys::Key_RightShift, scancode, action);
			}
			else if (wParam == VK_SNAPSHOT)
			{
				// HACK: Key down is not reported for the Print Screen key
				ProcessKey(window, data, key, scancode, PPRESS);
				ProcessKey(window, data, key, scancode, PRELEASE);
			}
			else {
				ProcessKey(window, data, key, scancode, action);
			}

		}break;

		}
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	void Window::Init(const WindowProperties& props)
	{
		if (!s_Instance) {
			s_Instance = GetModuleHandle(nullptr);
			RegisterWindowClass();
			MapKeys(m_Data);
			MapKeysNames(m_Data);
		}

		m_Data.Props = props;

		u32 style = WS_OVERLAPPEDWINDOW;
		u32 exStyle = WS_EX_OVERLAPPEDWINDOW;

		RECT rect = { 0, 0, 0, 0 };
		rect.right = props.Width;
		rect.bottom = props.Height;
		AdjustWindowRectEx(&rect, style, 0, exStyle);

		wstr title = StringToWideString(props.Title);

		HWND window = CreateWindowEx(
			exStyle,
			s_ClassName.c_str(),
			title.c_str(),
			style,
			props.XPos,
			props.YPos,
			rect.right - rect.left,
			rect.bottom - rect.top,
			0,
			0,
			s_Instance,
			0);

		PASSERT_MSG(window, "Window creation failed");

		if (window) {
			SetPropW(window, s_DataPropName.c_str(), &m_Data);
			SetPropW(window, s_WindowPropName.c_str(), this);

			u8 flags = 0;
			if (props.Hidden) {
				flags = SW_HIDE;
			}
			else if (!props.Hidden) {

				if (props.Maximize) {
					flags = SW_SHOWMAXIMIZED;
				}
				else {
					flags = SW_SHOW;
				}
			}

			if (props.Center) {
				CenterWindow(window, &m_Data.Props.XPos, &m_Data.Props.YPos, props.Width, props.Height);
			}
			ShowWindow(window, flags);
			UpdateWindow(window);
			m_Handle.Ptr = window;
		}
	}

	void Window::Destroy()
	{
		if (s_Instance) {
			UneegisterWindowClass();
		}

		DestroyWindow((HWND)m_Handle.Ptr);
		m_Handle.Ptr = nullptr;
	}

	void Window::Hide()
	{
		m_Data.Props.Hidden = true;
		ShowWindow((HWND)m_Handle.Ptr, SW_HIDE);
	}

	void Window::Show()
	{
		m_Data.Props.Hidden = false;
		ShowWindow((HWND)m_Handle.Ptr, SW_SHOW);
	}

	void Window::SetTitle(const str& title)
	{
		m_Data.Props.Title = title;
		wstr windowTitle = StringToWideString(title);
		SetWindowText((HWND)m_Handle.Ptr, windowTitle.c_str());
	}

	void Window::SetPos(i32 xPos, i32 yPos)
	{
		RECT rect = { 0, 0, 0, 0 };
		rect.left = xPos;
		rect.right = xPos;
		rect.top = yPos;
		rect.bottom = yPos;
		AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, 0, WS_EX_OVERLAPPEDWINDOW);

		m_Data.Props.XPos = xPos;
		m_Data.Props.YPos = yPos;
		SetWindowPos((HWND)m_Handle.Ptr, NULL, rect.left, rect.top, 0, 0,
			SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOSIZE);
	}

	void Window::SetSize(u32 width, u32 height)
	{
		b8 valid = width > 0 && height > 0;
		PASSERT_MSG(valid, "invalid Parameter");
		// TODO: make sure we dont exceed window size limits

		RECT rect = { 0, 0, 0, 0 };
		rect.right = width;
		rect.bottom = height;
		AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, 0, WS_EX_OVERLAPPEDWINDOW);

		m_Data.Props.Width = width;
		m_Data.Props.Height = height;
		SetWindowPos((HWND)m_Handle.Ptr, HWND_TOP,
			0, 0, rect.right - rect.left, rect.bottom - rect.top,
			SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOMOVE | SWP_NOZORDER);
	}

	void Window::SetCloseCallback(CloseFunc func)
	{
		if (func) {
			m_Data.Callbacks.Close = func;
		}
	}

	void Window::SetKeyCallback(KeyFunc func)
	{
		if (func) {
			m_Data.Callbacks.Key = func;
		}
	}

	void PollEvents()
	{
		MSG msg;
		while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
		}

		// from GLFW
		HWND handle = GetActiveWindow();
		if (handle) {
			prime::WindowData* data = (prime::WindowData*)GetPropW(handle, s_DataPropName.c_str());
			prime::Window* window = (prime::Window*)GetPropW(handle, s_WindowPropName.c_str());
			if (data) {
				int i;
				const int keys[4][2] = {
					{ VK_LSHIFT, (u16)Keys::Key_LeftShift },
					{ VK_RSHIFT, (u16)Keys::Key_RightShift },
					{ VK_LWIN, (u16)Keys::Key_LeftSuper },
					{ VK_RWIN, (u16)Keys::Key_RightSuper }
				};

				for (i = 0; i < 4; i++) {
					const int vk = keys[i][0];
					const int key = keys[i][1];
					const int scancode = data->Scancodes[key];

					if ((GetKeyState(vk) & 0x8000)) { continue; }
					if (data->Keycodes[key] != PPRESS) { continue; }

					ProcessKey(window, data, key, scancode, PRELEASE);
				}
			}
		}

	}

	wstr StringToWideString(const str& string)
	{
		if (string.empty()) { return wstr(); }
		int len = MultiByteToWideChar(CP_UTF8, 0, string.c_str(), -1, 0, 0);
		if (len == 0) { return wstr(); }

		wchar_t* wideStr = new wchar_t[len];
		MultiByteToWideChar(CP_UTF8, 0, string.c_str(), -1, wideStr, len);

		wstr wideString(wideStr);
		return wideString;
	}

	str WideStringToString(const wstr& wideString)
	{
		if (wideString.empty()) { return str(); }
		int len = WideCharToMultiByte(CP_UTF8, 0, wideString.c_str(), -1, NULL, 0, NULL, NULL);
		if (len == 0) { return str(); }

		char* charStr = new char[len];
		WideCharToMultiByte(CP_UTF8, 0, wideString.c_str(), -1, charStr, len, NULL, NULL);
		return charStr;
	}
}

#endif // PPLATFORM_WINDOWS