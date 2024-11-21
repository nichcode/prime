
#include "prime/window.h"
#include "prime/assert.h"
#include "prime/utils.h"

#ifdef PPLATFORM_WINDOWS
#include <Windows.h>
#include <windowsx.h>

namespace prime {

	static HINSTANCE s_instance = NULL;
	wstr s_class_name = L"PrimeWindowClass";
	wstr s_window_prop_name = L"PrimeWindow";
	wstr s_data_prop_name = L"PrimeData";
	static WINDOWPLACEMENT s_wnd_placement;

	struct Callbacks
	{
		CloseFunc close = nullptr;
		KeyFunc key = nullptr;
		MouseButtonFunc mouse = nullptr;
		MouseMovedFunc mouse_moved = nullptr;
		MouseScrolledFunc mouse_scrolled = nullptr;
		WindowPosFunc window_pos = nullptr;
		WindowResizeFunc window_resize = nullptr;
		WindowFocusFunc window_focus = nullptr;
	};

	static i32 s_window_count = 0;
	static Callbacks s_callbacks;

	static LRESULT CALLBACK window_proc(HWND h_wnd, UINT u_msg, WPARAM w_param, LPARAM l_param);

	static void register_window_class()
	{
		s_instance = GetModuleHandle(nullptr);

		WNDCLASSEX wc;
		memset(&wc, 0, sizeof(wc));
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_OWNDC;
		wc.lpfnWndProc = window_proc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = s_instance;
		wc.hIcon = LoadIcon(s_instance, IDI_WINLOGO);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = nullptr;
		wc.lpszClassName = s_class_name.c_str();

		auto result = RegisterClassEx(&wc);
		PASSERT_MSG(result, "Window registration failed");
	}

	static void unregister_window_class()
	{
		UnregisterClass(s_class_name.c_str(), s_instance);
	}

	static void center_window(HWND window, int *x_pos, int *y_pos, u32 width, u32 height)
	{
		MONITORINFO monitor_info;
		monitor_info.cbSize = sizeof(MONITORINFO);
		GetMonitorInfo(MonitorFromWindow(window, MONITOR_DEFAULTTONEAREST), &monitor_info);
		u32 max_width = monitor_info.rcMonitor.right;
		u32 max_height = monitor_info.rcMonitor.bottom;

		int x = (max_width - width) / 2;
		int y = (max_height - height) / 2;

		*x_pos = x;
		*y_pos = y;
		SetWindowPos(window, 0, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_SHOWWINDOW);
	}

	static void map_keys(WindowData& data)
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

	static void map_key_names(WindowData& data)
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

	static void process_key(Window* window, WindowData* data, u16 key, i32 scancode, u8 action)
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

		if (s_callbacks.key) {
			s_callbacks.key(window, key, scancode, action);
		}
	}

	static void process_mouse(Window* window, WindowData* data, u16 button, u8 action)
	{
		PASSERT_MSG(button >= 0 && button < Mouse_Max, "Invalid Key");
		PASSERT_MSG(action == PRELEASE || action == PPRESS, "Invalid action");

		if (action == PPRESS && data->mouse[button] == PRELEASE) {
			data->mouse[button] = PPRESS;
		}
		else {
			data->mouse[button] = action;
		}

		if (s_callbacks.mouse) {
			s_callbacks.mouse(window, button, action);
		}
	}

	static void process_mouse_moved(Window* window, WindowData* data, i32 x, i32 y)
	{
		data->mouse_pos[0] = x;
		data->mouse_pos[1] = y;

		if (s_callbacks.mouse_moved) {
			s_callbacks.mouse_moved(window, x, y);
		}
	}

	static void process_window_focus(Window* window, WindowData* data, b8 focused)
	{
		data->is_focused = focused;
		if (s_callbacks.window_focus) {
			s_callbacks.window_focus(window, focused);
		}

		if (focused == false) {
			u16 key, button;

			// process keys
			for (key = 0; key <= Key_Max; key++) {
				if (data->keys[key] == PPRESS) {
					const i32 scancode = data->scancodes[key];
					process_key(window, data, key, scancode, PRELEASE);
				}
			}

			// proces mouse buttons
			for (button = 0; button <= Mouse_Max; button++) {
				if (data->mouse[button] == PPRESS) {
					process_mouse(window, data, button, PRELEASE);
				}
			}
		}
	}

	static LRESULT CALLBACK window_proc(HWND h_wnd, UINT u_msg, WPARAM w_param, LPARAM l_param)
	{
		prime::Window* window = (prime::Window*)GetPropW(h_wnd, s_window_prop_name.c_str());
		prime::WindowData* data = (prime::WindowData*)GetPropW(h_wnd, s_data_prop_name.c_str());

		if (!window) {
			// no window created
			return DefWindowProc(h_wnd, u_msg, w_param, l_param);
		}

		switch (u_msg)
		{
		case WM_CLOSE: {
			data->should_close = true;
			if (s_callbacks.close) {
				s_callbacks.close(window);
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
			const u8 action = (HIWORD(l_param) & KF_UP) ? PRELEASE : PPRESS;
			scancode = (HIWORD(l_param) & (KF_EXTENDED | 0xff));
			if (!scancode)
			{
				// NOTE: Some synthetic key messages have a scancode of zero
				// HACK: Map the virtual key back to a usable scancode
				scancode = MapVirtualKeyW((UINT)w_param, MAPVK_VK_TO_VSC);
			}

			// HACK: Alt+PrtSc has a different scancode than just PrtSc
			if (scancode == 0x54) { scancode = 0x137; }

			// HACK: Ctrl+Pause has a different scancode than just Pause
			if (scancode == 0x146) { scancode = 0x45; }

			// HACK: CJK IME sets the extended bit for right Shift
			if (scancode == 0x136) { scancode = 0x36; }

			key = data->keycodes[scancode];

			// The Ctrl keys require special handling
			if (w_param == VK_CONTROL)
			{
				if (HIWORD(l_param) & KF_EXTENDED)
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
			else if (w_param == VK_PROCESSKEY)
			{
				// IME notifies that keys have been filtered by setting the
				// virtual key-code to VK_PROCESSKEY
				break;
			}

			if (action == PRELEASE && w_param == VK_SHIFT)
			{
				// HACK: Release both Shift keys on Shift up event, as when both
				//       are pressed the first release does not emit any event
				// NOTE: The other half of this is in _glfwPollEventsWin32
				process_key(window, data, Key_LeftShift, scancode, action);
				process_key(window, data, Key_RightShift, scancode, action);
			}
			else if (w_param == VK_SNAPSHOT)
			{
				// HACK: Key down is not reported for the Print Screen key
				process_key(window, data, key, scancode, PPRESS);
				process_key(window, data, key, scancode, PRELEASE);
			}
			else {
				process_key(window, data, key, scancode, action);
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

			if (u_msg == WM_LBUTTONDOWN || u_msg == WM_LBUTTONUP) {
				button = Mouse_ButtonLeft;
			}
				
			else if (u_msg == WM_RBUTTONDOWN || u_msg == WM_RBUTTONUP) {
				button = Mouse_ButtonRight;
			}
				
			else if (u_msg == WM_MBUTTONDOWN || u_msg == WM_MBUTTONUP) {
				button = Mouse_ButtonMiddle;
			}

			if (u_msg == WM_LBUTTONDOWN || u_msg == WM_RBUTTONDOWN ||
				u_msg == WM_MBUTTONDOWN || u_msg == WM_XBUTTONDOWN) {
				action = PPRESS;
			}
			else {
				action = PRELEASE;
			}

			if (u_msg == WM_LBUTTONDOWN) {
				SetCapture(h_wnd);
			}
			else if (u_msg == WM_LBUTTONUP) {
				ReleaseCapture();
			}

			process_mouse(window, data, button, action);
			if (u_msg == WM_XBUTTONDOWN || u_msg == WM_XBUTTONUP) { return true; }

			return 0;
			break;
		}

		case WM_MOUSEMOVE: {
			const int x = GET_X_LPARAM(l_param);
			const int y = GET_Y_LPARAM(l_param);

			if (data->is_focused) { process_mouse_moved(window, data, x, y); }

			return 0;
			break;
		}

		case WM_MOUSEWHEEL: {
			if (s_callbacks.mouse_scrolled) {
				s_callbacks.mouse_scrolled(window, 0.0, (f32)HIWORD(w_param) / (f32)WHEEL_DELTA);
			}

			return 0;
			break;
		}

		case WM_MOVE: {
			i32 x = GET_X_LPARAM(l_param);
			i32 y = GET_Y_LPARAM(l_param);
			data->props.x_pos = x;
			data->props.y_pos = y;

			if (s_callbacks.window_pos) {
				s_callbacks.window_pos(window, x, y);
			}

			return 0;
			break;
		}

		case WM_SIZE: {
			const u32 width = (u32)LOWORD(l_param);
			const u32 height = (u32)HIWORD(l_param);

			if (width != data->props.width || height != data->props.height) {
				data->props.width = width;
				data->props.height = height;

				if (s_callbacks.window_resize) {
					s_callbacks.window_resize(window, width, height);
				}
			}
			return 0;
			break;
		}

		case WM_SETFOCUS: {
			process_window_focus(window, data, true);

			return 0;
			break;
		}

		case WM_KILLFOCUS: {
			process_window_focus(window, data, false);

			return 0;
			break;
		}

		case WM_PAINT: {
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(h_wnd, &ps);
			HBRUSH brush = CreateSolidBrush(0);
			FillRect(hdc, &ps.rcPaint, brush);
			EndPaint(h_wnd, &ps);
			DeleteObject(brush);
		}

		}
		return DefWindowProc(h_wnd, u_msg, w_param, l_param);
	}

	void Window::init(const WindowProperties& props)
	{
		if (s_window_count == 0) {
			register_window_class();
			m_data.is_focused = true;
		}

		m_data.props = props;
		u32 style = WS_OVERLAPPEDWINDOW;
		u32 ex_style = WS_EX_OVERLAPPEDWINDOW;

		RECT rect = { 0, 0, 0, 0 };
		rect.right = props.width;
		rect.bottom = props.height;
		AdjustWindowRectEx(&rect, style, 0, ex_style);

		wstr title = str_to_wstr(props.title);

		HWND window = CreateWindowEx(
			ex_style,
			s_class_name.c_str(),
			title.c_str(),
			style,
			props.x_pos,
			props.y_pos,
			rect.right - rect.left,
			rect.bottom - rect.top,
			0,
			0,
			s_instance,
			0);

		PASSERT_MSG(window, "Window creation failed");

		if (window) {
			SetPropW(window, s_data_prop_name.c_str(), &m_data);
			SetPropW(window, s_window_prop_name.c_str(), this);

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
				center_window(window, &m_data.props.x_pos, &m_data.props.y_pos, props.width, props.height);
			}
			ShowWindow(window, flags);
			
			map_keys(m_data);
			map_key_names(m_data);
			m_handle = window;
			++s_window_count;
		}
	}

	void Window::destroy()
	{
		DestroyWindow((HWND)m_handle);
		m_handle = nullptr;
		m_user_data = nullptr;
		--s_window_count;
		if (s_window_count == 0) {
			unregister_window_class();
		}
	}

	b8 Window::is_maximized() const
	{
		GetWindowPlacement((HWND)m_handle, &s_wnd_placement);
		if (s_wnd_placement.showCmd == SW_SHOWMAXIMIZED) {
			return true;
		}
		return false;
	}

	void Window::hide()
	{
		m_data.props.hidden = true;
		ShowWindow((HWND)m_handle, SW_HIDE);
	}

	void Window::show()
	{
		m_data.props.hidden = false;
		ShowWindow((HWND)m_handle, SW_SHOW);
	}

	void Window::set_title(const str& title)
	{
		m_data.props.title = title;
		wstr window_title = str_to_wstr(title);
		SetWindowText((HWND)m_handle, window_title.c_str());
	}

	void Window::set_pos(i32 x_pos, i32 y_pos)
	{
		RECT rect = { 0, 0, 0, 0 };
		rect.left = x_pos;
		rect.right = x_pos;
		rect.top = y_pos;
		rect.bottom = y_pos;
		AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, 0, WS_EX_OVERLAPPEDWINDOW);

		m_data.props.x_pos = x_pos;
		m_data.props.y_pos = y_pos;
		SetWindowPos((HWND)m_handle, NULL, rect.left, rect.top, 0, 0,
			SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOSIZE);
	}

	void Window::set_size(u32 width, u32 height)
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

	void poll_events()
	{
		MSG msg;
		while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
		}

		// from GLFW
		HWND handle = GetActiveWindow();
		if (handle) {
			prime::WindowData* data = (prime::WindowData*)GetPropW(handle, s_data_prop_name.c_str());
			prime::Window* window = (prime::Window*)GetPropW(handle, s_window_prop_name.c_str());
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

					process_key(window, data, key, scancode, PRELEASE);
				}
			}
		}

	}

	wstr str_to_wstr(const str& string)
	{
		if (string.empty()) { return wstr(); }
		int len = MultiByteToWideChar(CP_UTF8, 0, string.c_str(), -1, 0, 0);
		if (len == 0) { return wstr(); }

		wchar_t* wide_str = new wchar_t[len];
		MultiByteToWideChar(CP_UTF8, 0, string.c_str(), -1, wide_str, len);

		wstr wide_string(wide_str);
		return wide_string;
	}

	str wstr_to_str(const wstr& wide_string)
	{
		if (wide_string.empty()) { return str(); }
		int len = WideCharToMultiByte(CP_UTF8, 0, wide_string.c_str(), -1, NULL, 0, NULL, NULL);
		if (len == 0) { return str(); }

		char* char_str = new char[len];
		WideCharToMultiByte(CP_UTF8, 0, wide_string.c_str(), -1, char_str, len, NULL, NULL);
		return char_str;
	}

	void set_window_close_callback(CloseFunc func)
	{
		if (func) {
			s_callbacks.close = func;
		}
	}

	void set_window_key_callback(KeyFunc func)
	{
		if (func) {
			s_callbacks.key = func;
		}
	}

	void set_window_mouse_button_callback(MouseButtonFunc func)
	{
		if (func) {
			s_callbacks.mouse = func;
		}
	}

	void set_window_mouse_moved_callback(MouseMovedFunc func)
	{
		if (func) {
			s_callbacks.mouse_moved = func;
		}
	}
	
	void set_window_mouse_scrolled_callback(MouseScrolledFunc func)
	{
		if (func) {
			s_callbacks.mouse_scrolled = func;
		}
	}
	
	void set_window_pos_callback(WindowPosFunc func)
	{
		if (func) {
			s_callbacks.window_pos = func;
		}
	}
	
	void set_window_resize_callback(WindowResizeFunc func)
	{
		if (func) {
			s_callbacks.window_resize = func;
		}
	}
	
	void set_window_focus_callback(WindowFocusFunc func)
	{
		if (func) {
			s_callbacks.window_focus = func;
		}
	}
}

#endif // PPLATFORM_WINDOWS