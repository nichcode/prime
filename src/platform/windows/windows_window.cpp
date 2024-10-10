
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

	static HINSTANCE s_hInstance = NULL;
	wstr s_className = L"PrimeWindowClass";
	wstr s_windowPropName = L"PrimeWindow";
	wstr s_dataPropName = L"PrimeData";

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
		s_hInstance = GetModuleHandle(nullptr);

		WNDCLASSEX wc;
		memset(&wc, 0, sizeof(wc));
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_OWNDC;// | CS_VREDRAW | CS_HREDRAW;
		wc.lpfnWndProc = WindowProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = s_hInstance;
		wc.hIcon = LoadIcon(s_hInstance, IDI_WINLOGO);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = nullptr;
		wc.lpszClassName = s_className.c_str();

		auto result = RegisterClassEx(&wc);
		PASSERT_MSG(result, "Window registration failed");
	}

	static void UneegisterWindowClass()
	{
		UnregisterClass(s_className.c_str(), s_hInstance);
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
		data.keycodes[0x01E] = Key_A;
		data.keycodes[0x030] = Key_B;
		data.keycodes[0x02E] = Key_C;
		data.keycodes[0x020] = Key_D;
		data.keycodes[0x012] = Key_E;
		data.keycodes[0x021] = Key_F;
		data.keycodes[0x022] = Key_G;
		data.keycodes[0x023] = Key_H;
		data.keycodes[0x017] = Key_I;
		data.keycodes[0x024] = Key_J;
		data.keycodes[0x025] = Key_K;
		data.keycodes[0x026] = Key_L;
		data.keycodes[0x032] = Key_M;
		data.keycodes[0x031] = Key_N;
		data.keycodes[0x018] = Key_O;
		data.keycodes[0x019] = Key_P;
		data.keycodes[0x010] = Key_Q;
		data.keycodes[0x013] = Key_R;
		data.keycodes[0x01F] = Key_S;
		data.keycodes[0x014] = Key_T;
		data.keycodes[0x016] = Key_U;
		data.keycodes[0x02F] = Key_V;
		data.keycodes[0x011] = Key_W;
		data.keycodes[0x02D] = Key_X;
		data.keycodes[0x015] = Key_Y;
		data.keycodes[0x02C] = Key_Z;

		data.keycodes[0x00B] = Key_0;
		data.keycodes[0x002] = Key_1;
		data.keycodes[0x003] = Key_2;
		data.keycodes[0x004] = Key_3;
		data.keycodes[0x005] = Key_4;
		data.keycodes[0x006] = Key_5;
		data.keycodes[0x007] = Key_6;
		data.keycodes[0x008] = Key_7;
		data.keycodes[0x009] = Key_8;
		data.keycodes[0x00A] = Key_9;

		data.keycodes[0x028] = Key_Apostrophe;
		data.keycodes[0x02B] = Key_Backslash;
		data.keycodes[0x033] = Key_Comma;
		data.keycodes[0x00D] = Key_Equal;
		data.keycodes[0x029] = Key_GraveAccent;
		data.keycodes[0x01A] = Key_LeftBracket;
		data.keycodes[0x00C] = Key_Minus;
		data.keycodes[0x034] = Key_Period;
		data.keycodes[0x01B] = Key_RightBracket;
		data.keycodes[0x027] = Key_SemiColon;
		data.keycodes[0x035] = Key_Slash;

		data.keycodes[0x00E] = Key_Backspace;
		data.keycodes[0x153] = Key_Delete;
		data.keycodes[0x14F] = Key_End;
		data.keycodes[0x01C] = Key_Enter;
		data.keycodes[0x001] = Key_Escape;
		data.keycodes[0x147] = Key_Home;
		data.keycodes[0x152] = Key_Insert;
		data.keycodes[0x15D] = Key_Menu;
		data.keycodes[0x151] = Key_PageDown;
		data.keycodes[0x149] = Key_PageUp;
		data.keycodes[0x045] = Key_Pause;
		data.keycodes[0x039] = Key_Space;
		data.keycodes[0x00F] = Key_Tab;
		data.keycodes[0x03A] = Key_CapsLock;
		data.keycodes[0x145] = Key_NumLock;
		data.keycodes[0x046] = Key_ScrollLock;
		data.keycodes[0x03B] = Key_F1;
		data.keycodes[0x03C] = Key_F2;
		data.keycodes[0x03D] = Key_F3;
		data.keycodes[0x03E] = Key_F4;
		data.keycodes[0x03F] = Key_F5;
		data.keycodes[0x040] = Key_F6;
		data.keycodes[0x041] = Key_F7;
		data.keycodes[0x042] = Key_F8;
		data.keycodes[0x043] = Key_F9;
		data.keycodes[0x044] = Key_F10;
		data.keycodes[0x057] = Key_F11;
		data.keycodes[0x058] = Key_F12;

		data.keycodes[0x038] = Key_LeftAlt;
		data.keycodes[0x01D] = Key_LeftControl;
		data.keycodes[0x02A] = Key_LeftShift;
		data.keycodes[0x15B] = Key_LeftSuper;
		data.keycodes[0x137] = Key_PrintScreen;
		data.keycodes[0x138] = Key_RightAlt;
		data.keycodes[0x11D] = Key_RightControl;
		data.keycodes[0x036] = Key_RightShift;
		data.keycodes[0x15C] = Key_RightSuper;
		data.keycodes[0x150] = Key_Down;
		data.keycodes[0x14B] = Key_Left;
		data.keycodes[0x14D] = Key_Right;
		data.keycodes[0x148] = Key_Up;

		data.keycodes[0x052] = Key_P0;
		data.keycodes[0x04F] = Key_P1;
		data.keycodes[0x050] = Key_P2;
		data.keycodes[0x051] = Key_P3;
		data.keycodes[0x04B] = Key_P4;
		data.keycodes[0x04C] = Key_P5;
		data.keycodes[0x04D] = Key_P6;
		data.keycodes[0x047] = Key_P7;
		data.keycodes[0x048] = Key_P8;
		data.keycodes[0x049] = Key_P9;
		data.keycodes[0x04E] = Key_PAdd;
		data.keycodes[0x053] = Key_PDecimal;
		data.keycodes[0x135] = Key_PDivide;
		data.keycodes[0x11C] = Key_PEnter;
		data.keycodes[0x059] = Key_PEqual;
		data.keycodes[0x037] = Key_PMultiply;
		data.keycodes[0x04A] = Key_PSubtract;

		/*i32 scancode = 0;
		for (scancode = 0; scancode < 512; scancode++) {
			if (data.keycodes[scancode] > 0) {
				data.keycodes[scancode] = scancode;
				data.scancodes[data.keycodes[scancode]] = scancode;
			}
		}*/
	}

	static void MapKeysNames(WindowData& data)
	{
		data.keynames[Key_A] = "Key A";
		data.keynames[Key_B] = "Key B";
		data.keynames[Key_C] = "Key C";
		data.keynames[Key_D] = "Key D";
		data.keynames[Key_E] = "Key E";
		data.keynames[Key_F] = "Key F";
		data.keynames[Key_G] = "Key G";
		data.keynames[Key_H] = "Key H";
		data.keynames[Key_I] = "Key I";
		data.keynames[Key_J] = "Key J";
		data.keynames[Key_K] = "Key K";
		data.keynames[Key_L] = "Key L";
		data.keynames[Key_M] = "Key M";
		data.keynames[Key_N] = "Key N";
		data.keynames[Key_O] = "Key O";
		data.keynames[Key_P] = "Key P";
		data.keynames[Key_Q] = "Key Q";
		data.keynames[Key_R] = "Key R";
		data.keynames[Key_S] = "Key S";
		data.keynames[Key_T] = "Key T";
		data.keynames[Key_U] = "Key U";
		data.keynames[Key_V] = "Key V";
		data.keynames[Key_W] = "Key W";
		data.keynames[Key_X] = "Key X";
		data.keynames[Key_Y] = "Key Y";
		data.keynames[Key_Z] = "Key Z";

		data.keynames[Key_Escape] = "Key Escape";
		data.keynames[Key_Enter] = "Key Enter";
		data.keynames[Key_Tab] = "Key Tab";
		data.keynames[Key_Backspace] = "Key Backspace";
		data.keynames[Key_Insert] = "Key Insert";
		data.keynames[Key_Delete] = "Key Delete";
		data.keynames[Key_Right] = "Key Right";
		data.keynames[Key_Left] = "Key Left";
		data.keynames[Key_Down] = "Key Down";
		data.keynames[Key_Up] = "Key Up";
		data.keynames[Key_PageUp] = "Key PageUp";
		data.keynames[Key_PageDown] = "Key PageDown";
		data.keynames[Key_Home] = "Key Home";
		data.keynames[Key_End] = "Key End";
		data.keynames[Key_CapsLock] = "Key CapsLock";
		data.keynames[Key_ScrollLock] = "Key ScrollLock";
		data.keynames[Key_NumLock] = "Key NumLock";
		data.keynames[Key_PrintScreen] = "Key Pru16Screen";
		data.keynames[Key_Pause] = "Key Pause";
		data.keynames[Key_F1] = "Key F1";
		data.keynames[Key_F2] = "Key F2";
		data.keynames[Key_F3] = "Key F3";
		data.keynames[Key_F4] = "Key F4";
		data.keynames[Key_F5] = "Key F5";
		data.keynames[Key_F6] = "Key F6";
		data.keynames[Key_F7] = "Key F7";
		data.keynames[Key_F8] = "Key F8";
		data.keynames[Key_F9] = "Key F9";
		data.keynames[Key_F10] = "Key F10";
		data.keynames[Key_F11] = "Key F11";
		data.keynames[Key_F12] = "Key F12";

		data.keynames[Key_LeftShift] = "Key LeftShift";
		data.keynames[Key_LeftControl] = "Key LeftControl";
		data.keynames[Key_LeftAlt] = "Key LeftAlt";
		data.keynames[Key_LeftSuper] = "Key LeftSuper";
		data.keynames[Key_LeftBracket] = "Key LeftBracket";
		data.keynames[Key_RightShift] = "Key RightShift";
		data.keynames[Key_RightControl] = "Key RightControl";
		data.keynames[Key_RightAlt] = "Key RightAlt";
		data.keynames[Key_RightSuper] = "Key RightSuper";
		data.keynames[Key_RightBracket] = "Key RightBracket";

		data.keynames[Key_Menu] = "Key Menu";
		data.keynames[Key_Backslash] = "Key Backslash";
		data.keynames[Key_GraveAccent] = "Key GraveAccent";
		data.keynames[Key_SemiColon] = "Key SemiColon";
		data.keynames[Key_Equal] = "Key Equal";

		data.keynames[Key_Space] = "Key Space";
		data.keynames[Key_Apostrophe] = "Key Apostrophe";
		data.keynames[Key_Comma] = "Key Comma";
		data.keynames[Key_Minus] = "Key Minus";
		data.keynames[Key_Period] = "Key Period";
		data.keynames[Key_Slash] = "Key Slash";

		data.keynames[Key_0] = "Key 0";
		data.keynames[Key_1] = "Key 1";
		data.keynames[Key_2] = "Key 2";
		data.keynames[Key_3] = "Key 3";
		data.keynames[Key_4] = "Key 4";
		data.keynames[Key_5] = "Key 5";
		data.keynames[Key_6] = "Key 6";
		data.keynames[Key_7] = "Key 7";
		data.keynames[Key_8] = "Key 8";
		data.keynames[Key_9] = "Key 9";

		data.keynames[Key_P0] = "Key P0";
		data.keynames[Key_P1] = "Key P1";
		data.keynames[Key_P2] = "Key P2";
		data.keynames[Key_P3] = "Key P3";
		data.keynames[Key_P4] = "Key P4";
		data.keynames[Key_P5] = "Key P5";
		data.keynames[Key_P6] = "Key P6";
		data.keynames[Key_P7] = "Key P7";
		data.keynames[Key_P8] = "Key P8";
		data.keynames[Key_P9] = "Key P9";
		data.keynames[Key_PDecimal] = "Key PDecimal";
		data.keynames[Key_PDivide] = "Key PDivide";
		data.keynames[Key_PMultiply] = "Key PMultiply";
		data.keynames[Key_PSubtract] = "Key PSubtract";
		data.keynames[Key_PAdd] = "Key PAdd";
		data.keynames[Key_PEnter] = "Key PEnter";
		data.keynames[Key_PEqual] = "Key PEqual";
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

	static void ProcessMouse(Window* window, WindowData* data, u16 button, u8 action)
	{
		PASSERT_MSG(button >= 0 && button < Mouse_Max, "Invalid Key");
		PASSERT_MSG(action == PRELEASE || action == PPRESS, "Invalid action");

		if (action == PPRESS && data->mouse[button] == PRELEASE) {
			data->mouse[button] = PPRESS;
		}
		else {
			data->mouse[button] = action;
		}

		if (s_Callbacks.Mouse) {
			s_Callbacks.Mouse(window, button, action);
		}
	}

	static void ProcessMouseMoved(Window* window, WindowData* data, i32 x, i32 y)
	{
		data->mousePos[0] = x;
		data->mousePos[1] = y;

		if (s_Callbacks.MouseMoved) {
			s_Callbacks.MouseMoved(window, x, y);
		}
	}

	static void ProcessWindowFocus(Window* window, WindowData* data, b8 focused)
	{
		data->isFocused = focused;
		if (s_Callbacks.WindowFocus) {
			s_Callbacks.WindowFocus(window, focused);
		}

		if (focused == false) {
			u16 key, button;

			// process keys
			for (key = 0; key <= Key_Max; key++) {
				if (data->keys[key] == PPRESS) {
					const i32 scancode = data->scancodes[key];
					ProcessKey(window, data, key, scancode, PRELEASE);
				}
			}

			// proces mouse buttons
			for (button = 0; button <= Mouse_Max; button++) {
				if (data->mouse[button] == PPRESS) {
					ProcessMouse(window, data, button, PRELEASE);
				}
			}
		}
	}

	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		prime::Window* window = (prime::Window*)GetPropW(hWnd, s_windowPropName.c_str());
		prime::WindowData* data = (prime::WindowData*)GetPropW(hWnd, s_dataPropName.c_str());

		if (!window) {
			// no window created
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}

		switch (uMsg)
		{
		case WM_CLOSE: {
			data->shouldClose = true;
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

			key = data->keycodes[scancode];

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
				button = Mouse_ButtonLeft;
			}
				
			else if (uMsg == WM_RBUTTONDOWN || uMsg == WM_RBUTTONUP) {
				button = Mouse_ButtonRight;
			}
				
			else if (uMsg == WM_MBUTTONDOWN || uMsg == WM_MBUTTONUP) {
				button = Mouse_ButtonMiddle;
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
			data->props.xPos = x;
			data->props.yPos = y;

			if (s_Callbacks.WindowPos) {
				s_Callbacks.WindowPos(window, x, y);
			}

			return 0;
			break;
		}

		case WM_SIZE: {
			const u32 width = (u32)LOWORD(lParam);
			const u32 height = (u32)HIWORD(lParam);

			if (width != data->props.width || height != data->props.height) {
				data->props.width = width;
				data->props.height = height;

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

		m_data.props = props;
		u32 style = WS_OVERLAPPEDWINDOW;
		u32 exStyle = WS_EX_OVERLAPPEDWINDOW;

		RECT rect = { 0, 0, 0, 0 };
		rect.right = props.width;
		rect.bottom = props.height;
		AdjustWindowRectEx(&rect, style, 0, exStyle);

		wstr title = StringToWideString(props.title);

		HWND window = CreateWindowEx(
			exStyle,
			s_className.c_str(),
			title.c_str(),
			style,
			props.xPos,
			props.yPos,
			rect.right - rect.left,
			rect.bottom - rect.top,
			0,
			0,
			s_hInstance,
			0);

		PASSERT_MSG(window, "Window creation failed");

		if (window) {
			SetPropW(window, s_dataPropName.c_str(), &m_data);
			SetPropW(window, s_windowPropName.c_str(), this);

			u8 flags = 0;
			if (props.hidden) {
				flags = SW_HIDE;
			}
			else if (!props.hidden) {

				if (props.maximize) {
					flags = SW_SHOWMAXIMIZED;
				}
				else {
					flags = SW_SHOW;
				}
			}

			if (props.center) {
				CenterWindow(window, &m_data.props.xPos, &m_data.props.yPos, props.width, props.height);
			}
			ShowWindow(window, flags);
			
			MapKeys(m_data);
			MapKeysNames(m_data);
			m_handle = window;
			++s_WindowCount;
		}
	}

	void Window::Destroy()
	{
		DestroyWindow((HWND)m_handle);
		m_handle = nullptr;
		m_userData = nullptr;
		--s_WindowCount;
		if (s_WindowCount == 0) {
			UneegisterWindowClass();
		}
	}

	void Window::Hide()
	{
		m_data.props.hidden = true;
		ShowWindow((HWND)m_handle, SW_HIDE);
	}

	void Window::Show()
	{
		m_data.props.hidden = false;
		ShowWindow((HWND)m_handle, SW_SHOW);
	}

	void Window::SetTitle(const str& title)
	{
		m_data.props.title = title;
		wstr windowtitle = StringToWideString(title);
		SetWindowText((HWND)m_handle, windowtitle.c_str());
	}

	void Window::SetPos(i32 xPos, i32 yPos)
	{
		RECT rect = { 0, 0, 0, 0 };
		rect.left = xPos;
		rect.right = xPos;
		rect.top = yPos;
		rect.bottom = yPos;
		AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, 0, WS_EX_OVERLAPPEDWINDOW);

		m_data.props.xPos = xPos;
		m_data.props.yPos = yPos;
		SetWindowPos((HWND)m_handle, NULL, rect.left, rect.top, 0, 0,
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

		m_data.props.width = width;
		m_data.props.height = height;
		SetWindowPos((HWND)m_handle, HWND_TOP,
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
			prime::WindowData* data = (prime::WindowData*)GetPropW(handle, s_dataPropName.c_str());
			prime::Window* window = (prime::Window*)GetPropW(handle, s_windowPropName.c_str());
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
					const int scancode = data->scancodes[key];

					if ((GetKeyState(vk) & 0x8000)) { continue; }
					if (data->keycodes[key] != PPRESS) { continue; }

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