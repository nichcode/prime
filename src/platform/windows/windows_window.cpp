
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
	wstr s_PropName = L"Prime";

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

	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		prime::WindowData* data = (prime::WindowData*)GetPropW(hWnd, s_PropName.c_str());
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
			if (data->Callbacks.CloseCallback) {
				data->Callbacks.CloseCallback(handle);
			}	
		}
		break;

		}
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	void Window::Init(const WindowProperties& props)
	{
		if (!s_Instance) {
			s_Instance = GetModuleHandle(nullptr);
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
			SetPropW(window, s_PropName.c_str(), &m_Data);

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

	void Window::SetCloseCallback(WindowCloseFunc func)
	{
		if (func) {
			m_Data.Callbacks.CloseCallback = func;
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