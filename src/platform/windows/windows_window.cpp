
#include "prime/prime_window.h"
#include "prime/prime_assert.h"
#include "prime/prime_utils.h"

#ifdef PPLATFORM_WINDOWS
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // !WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <windowsx.h>

namespace prime {

	static HINSTANCE s_Instance = NULL;
	wstr s_ClassName = L"PrimeWindowClass";
	wstr s_WindowPropName = L"PrimeWindow";
	wstr s_DataPropName = L"PrimeData";

	struct Callbacks
	{
		CloseFunc Close = nullptr;
		KeyFunc Key = nullptr;
		MouseButtonFunc Mouse = nullptr;
		MouseMovedFunc MouseMoved = nullptr;
		MouseScrolledFunc MouseScrolled = nullptr;
		WindowPosFunc WindowPos = nullptr;
		WindowResizeFunc WindowResize = nullptr;
		WindowFocusFunc WindowFocus = nullptr;
	};

	static i32 s_WindowCount = 0;
	static Callbacks s_Callbacks;

	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static void RegisterWindowClass()
	{
		s_Instance = GetModuleHandle(nullptr);

		WNDCLASSEX wc;
		memset(&wc, 0, sizeof(wc));
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_OWNDC;// | CS_VREDRAW | CS_HREDRAW;
		wc.lpfnWndProc = WindowProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = s_Instance;
		wc.hIcon = LoadIcon(s_Instance, IDI_WINLOGO);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = nullptr;
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
		data.Keycodes[0x01E] = Key_A;
		data.Keycodes[0x030] = Key_B;
		data.Keycodes[0x02E] = Key_C;
		data.Keycodes[0x020] = Key_D;
		data.Keycodes[0x012] = Key_E;
		data.Keycodes[0x021] = Key_F;
		data.Keycodes[0x022] = Key_G;
		data.Keycodes[0x023] = Key_H;
		data.Keycodes[0x017] = Key_I;
		data.Keycodes[0x024] = Key_J;
		data.Keycodes[0x025] = Key_K;
		data.Keycodes[0x026] = Key_L;
		data.Keycodes[0x032] = Key_M;
		data.Keycodes[0x031] = Key_N;
		data.Keycodes[0x018] = Key_O;
		data.Keycodes[0x019] = Key_P;
		data.Keycodes[0x010] = Key_Q;
		data.Keycodes[0x013] = Key_R;
		data.Keycodes[0x01F] = Key_S;
		data.Keycodes[0x014] = Key_T;
		data.Keycodes[0x016] = Key_U;
		data.Keycodes[0x02F] = Key_V;
		data.Keycodes[0x011] = Key_W;
		data.Keycodes[0x02D] = Key_X;
		data.Keycodes[0x015] = Key_Y;
		data.Keycodes[0x02C] = Key_Z;

		data.Keycodes[0x00B] = Key_0;
		data.Keycodes[0x002] = Key_1;
		data.Keycodes[0x003] = Key_2;
		data.Keycodes[0x004] = Key_3;
		data.Keycodes[0x005] = Key_4;
		data.Keycodes[0x006] = Key_5;
		data.Keycodes[0x007] = Key_6;
		data.Keycodes[0x008] = Key_7;
		data.Keycodes[0x009] = Key_8;
		data.Keycodes[0x00A] = Key_9;

		data.Keycodes[0x028] = Key_Apostrophe;
		data.Keycodes[0x02B] = Key_Backslash;
		data.Keycodes[0x033] = Key_Comma;
		data.Keycodes[0x00D] = Key_Equal;
		data.Keycodes[0x029] = Key_GraveAccent;
		data.Keycodes[0x01A] = Key_LeftBracket;
		data.Keycodes[0x00C] = Key_Minus;
		data.Keycodes[0x034] = Key_Period;
		data.Keycodes[0x01B] = Key_RightBracket;
		data.Keycodes[0x027] = Key_SemiColon;
		data.Keycodes[0x035] = Key_Slash;

		data.Keycodes[0x00E] = Key_Backspace;
		data.Keycodes[0x153] = Key_Delete;
		data.Keycodes[0x14F] = Key_End;
		data.Keycodes[0x01C] = Key_Enter;
		data.Keycodes[0x001] = Key_Escape;
		data.Keycodes[0x147] = Key_Home;
		data.Keycodes[0x152] = Key_Insert;
		data.Keycodes[0x15D] = Key_Menu;
		data.Keycodes[0x151] = Key_PageDown;
		data.Keycodes[0x149] = Key_PageUp;
		data.Keycodes[0x045] = Key_Pause;
		data.Keycodes[0x039] = Key_Space;
		data.Keycodes[0x00F] = Key_Tab;
		data.Keycodes[0x03A] = Key_CapsLock;
		data.Keycodes[0x145] = Key_NumLock;
		data.Keycodes[0x046] = Key_ScrollLock;
		data.Keycodes[0x03B] = Key_F1;
		data.Keycodes[0x03C] = Key_F2;
		data.Keycodes[0x03D] = Key_F3;
		data.Keycodes[0x03E] = Key_F4;
		data.Keycodes[0x03F] = Key_F5;
		data.Keycodes[0x040] = Key_F6;
		data.Keycodes[0x041] = Key_F7;
		data.Keycodes[0x042] = Key_F8;
		data.Keycodes[0x043] = Key_F9;
		data.Keycodes[0x044] = Key_F10;
		data.Keycodes[0x057] = Key_F11;
		data.Keycodes[0x058] = Key_F12;

		data.Keycodes[0x038] = Key_LeftAlt;
		data.Keycodes[0x01D] = Key_LeftControl;
		data.Keycodes[0x02A] = Key_LeftShift;
		data.Keycodes[0x15B] = Key_LeftSuper;
		data.Keycodes[0x137] = Key_PrintScreen;
		data.Keycodes[0x138] = Key_RightAlt;
		data.Keycodes[0x11D] = Key_RightControl;
		data.Keycodes[0x036] = Key_RightShift;
		data.Keycodes[0x15C] = Key_RightSuper;
		data.Keycodes[0x150] = Key_Down;
		data.Keycodes[0x14B] = Key_Left;
		data.Keycodes[0x14D] = Key_Right;
		data.Keycodes[0x148] = Key_Up;

		data.Keycodes[0x052] = Key_P0;
		data.Keycodes[0x04F] = Key_P1;
		data.Keycodes[0x050] = Key_P2;
		data.Keycodes[0x051] = Key_P3;
		data.Keycodes[0x04B] = Key_P4;
		data.Keycodes[0x04C] = Key_P5;
		data.Keycodes[0x04D] = Key_P6;
		data.Keycodes[0x047] = Key_P7;
		data.Keycodes[0x048] = Key_P8;
		data.Keycodes[0x049] = Key_P9;
		data.Keycodes[0x04E] = Key_PAdd;
		data.Keycodes[0x053] = Key_PDecimal;
		data.Keycodes[0x135] = Key_PDivide;
		data.Keycodes[0x11C] = Key_PEnter;
		data.Keycodes[0x059] = Key_PEqual;
		data.Keycodes[0x037] = Key_PMultiply;
		data.Keycodes[0x04A] = Key_PSubtract;

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
		data.Keynames[Key_A] = str("Key A");
		data.Keynames[Key_B] = "Key B";
		data.Keynames[Key_C] = "Key C";
		data.Keynames[Key_D] = "Key D";
		data.Keynames[Key_E] = "Key E";
		data.Keynames[Key_F] = "Key F";
		data.Keynames[Key_G] = "Key G";
		data.Keynames[Key_H] = "Key H";
		data.Keynames[Key_I] = "Key I";
		data.Keynames[Key_J] = "Key J";
		data.Keynames[Key_K] = "Key K";
		data.Keynames[Key_L] = "Key L";
		data.Keynames[Key_M] = "Key M";
		data.Keynames[Key_N] = "Key N";
		data.Keynames[Key_O] = "Key O";
		data.Keynames[Key_P] = "Key P";
		data.Keynames[Key_Q] = "Key Q";
		data.Keynames[Key_R] = "Key R";
		data.Keynames[Key_S] = "Key S";
		data.Keynames[Key_T] = "Key T";
		data.Keynames[Key_U] = "Key U";
		data.Keynames[Key_V] = "Key V";
		data.Keynames[Key_W] = "Key W";
		data.Keynames[Key_X] = "Key X";
		data.Keynames[Key_Y] = "Key Y";
		data.Keynames[Key_Z] = "Key Z";

		data.Keynames[Key_Escape] = "Key Escape";
		data.Keynames[Key_Enter] = "Key Enter";
		data.Keynames[Key_Tab] = "Key Tab";
		data.Keynames[Key_Backspace] = "Key Backspace";
		data.Keynames[Key_Insert] = "Key Insert";
		data.Keynames[Key_Delete] = "Key Delete";
		data.Keynames[Key_Right] = "Key Right";
		data.Keynames[Key_Left] = "Key Left";
		data.Keynames[Key_Down] = "Key Down";
		data.Keynames[Key_Up] = "Key Up";
		data.Keynames[Key_PageUp] = "Key PageUp";
		data.Keynames[Key_PageDown] = "Key PageDown";
		data.Keynames[Key_Home] = "Key Home";
		data.Keynames[Key_End] = "Key End";
		data.Keynames[Key_CapsLock] = "Key CapsLock";
		data.Keynames[Key_ScrollLock] = "Key ScrollLock";
		data.Keynames[Key_NumLock] = "Key NumLock";
		data.Keynames[Key_PrintScreen] = "Key Pru16Screen";
		data.Keynames[Key_Pause] = "Key Pause";
		data.Keynames[Key_F1] = "Key F1";
		data.Keynames[Key_F2] = "Key F2";
		data.Keynames[Key_F3] = "Key F3";
		data.Keynames[Key_F4] = "Key F4";
		data.Keynames[Key_F5] = "Key F5";
		data.Keynames[Key_F6] = "Key F6";
		data.Keynames[Key_F7] = "Key F7";
		data.Keynames[Key_F8] = "Key F8";
		data.Keynames[Key_F9] = "Key F9";
		data.Keynames[Key_F10] = "Key F10";
		data.Keynames[Key_F11] = "Key F11";
		data.Keynames[Key_F12] = "Key F12";

		data.Keynames[Key_LeftShift] = "Key LeftShift";
		data.Keynames[Key_LeftControl] = "Key LeftControl";
		data.Keynames[Key_LeftAlt] = "Key LeftAlt";
		data.Keynames[Key_LeftSuper] = "Key LeftSuper";
		data.Keynames[Key_LeftBracket] = "Key LeftBracket";
		data.Keynames[Key_RightShift] = "Key RightShift";
		data.Keynames[Key_RightControl] = "Key RightControl";
		data.Keynames[Key_RightAlt] = "Key RightAlt";
		data.Keynames[Key_RightSuper] = "Key RightSuper";
		data.Keynames[Key_RightBracket] = "Key RightBracket";

		data.Keynames[Key_Menu] = "Key Menu";
		data.Keynames[Key_Backslash] = "Key Backslash";
		data.Keynames[Key_GraveAccent] = "Key GraveAccent";
		data.Keynames[Key_SemiColon] = "Key SemiColon";
		data.Keynames[Key_Equal] = "Key Equal";

		data.Keynames[Key_Space] = "Key Space";
		data.Keynames[Key_Apostrophe] = "Key Apostrophe";
		data.Keynames[Key_Comma] = "Key Comma";
		data.Keynames[Key_Minus] = "Key Minus";
		data.Keynames[Key_Period] = "Key Period";
		data.Keynames[Key_Slash] = "Key Slash";

		data.Keynames[Key_0] = "Key 0";
		data.Keynames[Key_1] = "Key 1";
		data.Keynames[Key_2] = "Key 2";
		data.Keynames[Key_3] = "Key 3";
		data.Keynames[Key_4] = "Key 4";
		data.Keynames[Key_5] = "Key 5";
		data.Keynames[Key_6] = "Key 6";
		data.Keynames[Key_7] = "Key 7";
		data.Keynames[Key_8] = "Key 8";
		data.Keynames[Key_9] = "Key 9";

		data.Keynames[Key_P0] = "Key P0";
		data.Keynames[Key_P1] = "Key P1";
		data.Keynames[Key_P2] = "Key P2";
		data.Keynames[Key_P3] = "Key P3";
		data.Keynames[Key_P4] = "Key P4";
		data.Keynames[Key_P5] = "Key P5";
		data.Keynames[Key_P6] = "Key P6";
		data.Keynames[Key_P7] = "Key P7";
		data.Keynames[Key_P8] = "Key P8";
		data.Keynames[Key_P9] = "Key P9";
		data.Keynames[Key_PDecimal] = "Key PDecimal";
		data.Keynames[Key_PDivide] = "Key PDivide";
		data.Keynames[Key_PMultiply] = "Key PMultiply";
		data.Keynames[Key_PSubtract] = "Key PSubtract";
		data.Keynames[Key_PAdd] = "Key PAdd";
		data.Keynames[Key_PEnter] = "Key PEnter";
		data.Keynames[Key_PEqual] = "Key PEqual";
	}

	static void ProcessKey(Window* window, WindowData* data, u16 key, i32 scancode, u8 action)
	{
		PASSERT_MSG(key >= 0 && key < Key_Max, "Invalid Key");
		PASSERT_MSG(action == PRELEASE || action == PPRESS, "Invalid action");

		b8 repeated = false;
		if (action == PRELEASE && data->keys[key] == PRELEASE) {
			return;
		}

		if (action == PPRESS && data->keys[key] == PPRESS) {
			repeated = true;
		}

		if (action == PPRESS && data->keys[key] == PRELEASE) {
			data->keys[key] = PPRESS;
		}
		else {
			data->keys[key] = action;
		}

		if (repeated) {
			action = PREPEAT;
		}

		if (s_Callbacks.Key) {
			s_Callbacks.Key(window, key, scancode, action);
		}
	}

	static void ProcessMouse(Window* window, WindowData* data, u16 mouse, u8 action)
	{
		PASSERT_MSG(mouse >= 0 && mouse < Mouse_Max, "Invalid Key");
		PASSERT_MSG(action == PRELEASE || action == PPRESS, "Invalid action");

		if (action == PPRESS && data->Mouse[mouse] == PRELEASE) {
			data->Mouse[mouse] = PPRESS;
		}
		else {
			data->Mouse[mouse] = action;
		}

		if (s_Callbacks.Mouse) {
			s_Callbacks.Mouse(window, mouse, action);
		}
	}

	static void ProcessMouseMoved(Window* window, WindowData* data, i32 x, i32 y)
	{
		data->MousePos[0] = x;
		data->MousePos[1] = y;

		if (s_Callbacks.MouseMoved) {
			s_Callbacks.MouseMoved(window, x, y);
		}
	}

	static void ProcessWindowFocus(Window* window, WindowData* data, b8 focused)
	{
		data->IsFocused = focused;
		if (s_Callbacks.WindowFocus) {
			s_Callbacks.WindowFocus(window, focused);
		}

		if (focused == false) {
			u16 key, button;

			// process keys
			for (key = 0; key <= Key_Max; key++) {
				if (data->keys[key] == PPRESS) {
					const i32 scancode = data->Scancodes[key];
					ProcessKey(window, data, key, scancode, PRELEASE);
				}
			}

			// proces mouse buttons
			for (button = 0; button <= Mouse_Max; button++) {
				if (data->Mouse[button] == PPRESS) {
					ProcessMouse(window, data, button, PRELEASE);
				}
			}
		}
	}

	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		prime::Window* window = (prime::Window*)GetPropW(hWnd, s_WindowPropName.c_str());
		prime::WindowData* data = (prime::WindowData*)GetPropW(hWnd, s_DataPropName.c_str());

		if (!window) {
			// no window created
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}

		switch (uMsg)
		{
		case WM_CLOSE: {
			data->ShouldClose = true;
			if (s_Callbacks.Close) {
				s_Callbacks.Close(window);
			}

			return 0;
			break;
		}

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

			// The Ctrl keys require special handling
			if (wParam == VK_CONTROL)
			{
				if (HIWORD(lParam) & KF_EXTENDED)
				{
					// Right side keys have the extended key bit set
					key = Key_RightControl;
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
					key = Key_LeftControl;
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
				ProcessKey(window, data, Key_LeftShift, scancode, action);
				ProcessKey(window, data, Key_RightShift, scancode, action);
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

			break;
		}

		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_MBUTTONDOWN:
		case WM_XBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_RBUTTONUP:
		case WM_MBUTTONUP:
		case WM_XBUTTONUP: {
			i32 button, action;

			if (uMsg == WM_LBUTTONDOWN || uMsg == WM_LBUTTONUP) {
				button = Mouse_Left;
			}
				
			else if (uMsg == WM_RBUTTONDOWN || uMsg == WM_RBUTTONUP) {
				button = Mouse_Right;
			}
				
			else if (uMsg == WM_MBUTTONDOWN || uMsg == WM_MBUTTONUP) {
				button = Mouse_Middle;
			}

			if (uMsg == WM_LBUTTONDOWN || uMsg == WM_RBUTTONDOWN ||
				uMsg == WM_MBUTTONDOWN || uMsg == WM_XBUTTONDOWN) {
				action = PPRESS;
			}
			else {
				action = PRELEASE;
			}

			if (uMsg == WM_LBUTTONDOWN) {
				SetCapture(hWnd);
			}
			else if (uMsg == WM_LBUTTONUP) {
				ReleaseCapture();
			}

			ProcessMouse(window, data, button, action);
			if (uMsg == WM_XBUTTONDOWN || uMsg == WM_XBUTTONUP) { return true; }

			return 0;
			break;
		}

		case WM_MOUSEMOVE: {
			const int x = GET_X_LPARAM(lParam);
			const int y = GET_Y_LPARAM(lParam);

			ProcessMouseMoved(window, data, x, y);

			return 0;
			break;
		}

		case WM_MOUSEWHEEL: {
			if (s_Callbacks.MouseScrolled) {
				s_Callbacks.MouseScrolled(window, 0.0, (f32)HIWORD(wParam) / (f32)WHEEL_DELTA);
			}

			return 0;
			break;
		}

		case WM_MOVE: {
			i32 x = GET_X_LPARAM(lParam);
			i32 y = GET_Y_LPARAM(lParam);
			data->Props.XPos = x;
			data->Props.YPos = y;

			if (s_Callbacks.WindowPos) {
				s_Callbacks.WindowPos(window, x, y);
			}

			return 0;
			break;
		}

		case WM_SIZE: {
			const u32 width = (u32)LOWORD(lParam);
			const u32 height = (u32)HIWORD(lParam);

			if (width != data->Props.Width || height != data->Props.Height) {
				data->Props.Width = width;
				data->Props.Height = height;

				if (s_Callbacks.WindowResize) {
					s_Callbacks.WindowResize(window, width, height);
				}
			}
			return 0;
			break;
		}

		case WM_SETFOCUS: {
			ProcessWindowFocus(window, data, true);

			return 0;
			break;
		}

		case WM_KILLFOCUS: {
			ProcessWindowFocus(window, data, false);

			return 0;
			break;
		}

		case WM_PAINT: {
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			HBRUSH brush = CreateSolidBrush(0);
			FillRect(hdc, &ps.rcPaint, brush);
			EndPaint(hWnd, &ps);
			DeleteObject(brush);
		}

		}
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	void Window::Init(const WindowProperties& props)
	{
		if (s_WindowCount == 0) {
			RegisterWindowClass();
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
			
			MapKeys(m_Data);
			MapKeysNames(m_Data);
			m_Handle = window;
			++s_WindowCount;
		}
	}

	void Window::Destroy()
	{
		DestroyWindow((HWND)m_Handle);
		m_Handle = nullptr;
		m_UserData = nullptr;
		--s_WindowCount;
		if (s_WindowCount == 0) {
			UneegisterWindowClass();
		}
	}

	void Window::Hide()
	{
		m_Data.Props.Hidden = true;
		ShowWindow((HWND)m_Handle, SW_HIDE);
	}

	void Window::Show()
	{
		m_Data.Props.Hidden = false;
		ShowWindow((HWND)m_Handle, SW_SHOW);
	}

	void Window::SetTitle(const str& title)
	{
		m_Data.Props.Title = title;
		wstr windowTitle = StringToWideString(title);
		SetWindowText((HWND)m_Handle, windowTitle.c_str());
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
		SetWindowPos((HWND)m_Handle, NULL, rect.left, rect.top, 0, 0,
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
		SetWindowPos((HWND)m_Handle, HWND_TOP,
			0, 0, rect.right - rect.left, rect.bottom - rect.top,
			SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOMOVE | SWP_NOZORDER);
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
					{ VK_LSHIFT, Key_LeftShift },
					{ VK_RSHIFT, Key_RightShift },
					{ VK_LWIN, Key_LeftSuper },
					{ VK_RWIN, Key_RightSuper }
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

	void SetWindowCloseCallback(CloseFunc func)
	{
		if (func) {
			s_Callbacks.Close = func;
		}
	}

	void SetWindowKeyCallback(KeyFunc func)
	{
		if (func) {
			s_Callbacks.Key = func;
		}
	}

	void SetWindowMouseButtonCallback(MouseButtonFunc func)
	{
		if (func) {
			s_Callbacks.Mouse = func;
		}
	}

	void SetWindowMouseMovedCallback(MouseMovedFunc func)
	{
		if (func) {
			s_Callbacks.MouseMoved = func;
		}
	}
	
	void SetWindowMouseScrolledCallback(MouseScrolledFunc func)
	{
		if (func) {
			s_Callbacks.MouseScrolled = func;
		}
	}
	
	void SetWindowPosCallback(WindowPosFunc func)
	{
		if (func) {
			s_Callbacks.WindowPos = func;
		}
	}
	
	void SetWindowResizeCallback(WindowResizeFunc func)
	{
		if (func) {
			s_Callbacks.WindowResize = func;
		}
	}
	
	void SetWindowFocusCallback(WindowFocusFunc func)
	{
		if (func) {
			s_Callbacks.WindowFocus = func;
		}
	}
}

#endif // PPLATFORM_WINDOWS