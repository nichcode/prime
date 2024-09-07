
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
		data.Keycodes[0x01E] = (u16)Keys::KeyA;
		data.Keycodes[0x030] = (u16)Keys::KeyB;
		data.Keycodes[0x02E] = (u16)Keys::KeyC;
		data.Keycodes[0x020] = (u16)Keys::KeyD;
		data.Keycodes[0x012] = (u16)Keys::KeyE;
		data.Keycodes[0x021] = (u16)Keys::KeyF;
		data.Keycodes[0x022] = (u16)Keys::KeyG;
		data.Keycodes[0x023] = (u16)Keys::KeyH;
		data.Keycodes[0x017] = (u16)Keys::KeyI;
		data.Keycodes[0x024] = (u16)Keys::KeyJ;
		data.Keycodes[0x025] = (u16)Keys::KeyK;
		data.Keycodes[0x026] = (u16)Keys::KeyL;
		data.Keycodes[0x032] = (u16)Keys::KeyM;
		data.Keycodes[0x031] = (u16)Keys::KeyN;
		data.Keycodes[0x018] = (u16)Keys::KeyO;
		data.Keycodes[0x019] = (u16)Keys::KeyP;
		data.Keycodes[0x010] = (u16)Keys::KeyQ;
		data.Keycodes[0x013] = (u16)Keys::KeyR;
		data.Keycodes[0x01F] = (u16)Keys::KeyS;
		data.Keycodes[0x014] = (u16)Keys::KeyT;
		data.Keycodes[0x016] = (u16)Keys::KeyU;
		data.Keycodes[0x02F] = (u16)Keys::KeyV;
		data.Keycodes[0x011] = (u16)Keys::KeyW;
		data.Keycodes[0x02D] = (u16)Keys::KeyX;
		data.Keycodes[0x015] = (u16)Keys::KeyY;
		data.Keycodes[0x02C] = (u16)Keys::KeyZ;
	}

	static void MapKeysNames(WindowData& data)
	{
		data.Keynames[(u16)Keys::KeyA] = "Key A";
		data.Keynames[(u16)Keys::KeyB] = "Key B";
		data.Keynames[(u16)Keys::KeyC] = "Key C";
		data.Keynames[(u16)Keys::KeyD] = "Key D";
		data.Keynames[(u16)Keys::KeyE] = "Key E";
		data.Keynames[(u16)Keys::KeyF] = "Key F";
		data.Keynames[(u16)Keys::KeyG] = "Key G";
		data.Keynames[(u16)Keys::KeyH] = "Key H";
		data.Keynames[(u16)Keys::KeyI] = "Key I";
		data.Keynames[(u16)Keys::KeyJ] = "Key J";
		data.Keynames[(u16)Keys::KeyK] = "Key K";
		data.Keynames[(u16)Keys::KeyL] = "Key L";
		data.Keynames[(u16)Keys::KeyM] = "Key M";
		data.Keynames[(u16)Keys::KeyN] = "Key N";
		data.Keynames[(u16)Keys::KeyO] = "Key O";
		data.Keynames[(u16)Keys::KeyP] = "Key P";
		data.Keynames[(u16)Keys::KeyQ] = "Key Q";
		data.Keynames[(u16)Keys::KeyR] = "Key R";
		data.Keynames[(u16)Keys::KeyS] = "Key S";
		data.Keynames[(u16)Keys::KeyT] = "Key T";
		data.Keynames[(u16)Keys::KeyU] = "Key U";
		data.Keynames[(u16)Keys::KeyV] = "Key V";
		data.Keynames[(u16)Keys::KeyW] = "Key W";
		data.Keynames[(u16)Keys::KeyX] = "Key X";
		data.Keynames[(u16)Keys::KeyY] = "Key Y";
		data.Keynames[(u16)Keys::KeyZ] = "Key Z";
	}

	static void ProcessKey(Window* window, WindowData* data, u16 key, i32 scancode, u8 action)
	{
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

			const u8 action = (HIWORD(lParam) & KF_UP) ? 0 : 1; // 0 for release 1 for pressed
			scancode = (HIWORD(lParam) & (KF_EXTENDED | 0xff));
			if (!scancode)
			{
				// NOTE: Some synthetic key messages have a scancode of zero
				// HACK: Map the virtual key back to a usable scancode
				scancode = MapVirtualKeyW((UINT)wParam, MAPVK_VK_TO_VSC);
			}

			key = data->Keycodes[scancode];
			WindowHandle handle;
			handle.Ptr = hWnd;

			ProcessKey(window, data, key, scancode, action);

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

	void PullEvents()
	{
		MSG msg;
		while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
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