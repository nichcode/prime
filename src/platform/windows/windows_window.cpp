
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

	static void RegisterWindowClass()
	{
		WNDCLASSEX wc;
		memset(&wc, 0, sizeof(wc));
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_DBLCLKS | CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
		wc.lpfnWndProc = DefWindowProc;
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

	void Window::Init(const WindowProperties& props)
	{
		if (!s_Instance) {
			s_Instance = GetModuleHandle(nullptr);
			RegisterWindowClass();
		}

		m_Props.Center = props.Center;
		m_Props.Height = props.Height;
		m_Props.Maximize = props.Maximize;
		m_Props.Title = props.Title;
		m_Props.Width = props.Width;
		m_Props.XPos = props.XPos;
		m_Props.YPos = props.YPos;

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

			if (props.Center) {
				CenterWindow(window, &m_Props.XPos, &m_Props.YPos, props.Width, props.Height);
			}

			if (props.Maximize) {
				ShowWindow(window, SW_SHOWMAXIMIZED);
			}
			else {
				ShowWindow(window, SW_SHOW);
			}
			UpdateWindow(window);
			m_Handle.m_ptr = window;
		}
	}

	void Window::Destroy()
	{
		if (s_Instance) {
			UneegisterWindowClass();
		}

		DestroyWindow((HWND)m_Handle.m_ptr);
		m_Handle.m_ptr = nullptr;
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