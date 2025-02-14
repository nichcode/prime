

#include "prime/prime_window.h"
#include "prime_utils.h"
#include "prime/prime_keys.h"
#include "prime/prime_buttons.h"
#include "prime/prime_actions.h"
#include "prime/prime_memory.h"
#include "prime/prime_string.h"

struct primeWindow
{
	HWND handle = 0;
	u32 width = 0;
	u32 height = 0;
	char* title = nullptr;
	b8 shouldClose = false, isFocused = false;
	b8 isHidden = false;

	u16 keycodes[512] = {};
	u16 scancodes[primeKeyMax + 1] = {};

	u8 keys[primeKeyMax + 1] = {};
	u8 buttons[primeButtonMax + 1] = {};

	i32 mousePos[2] = {};
	u32 minWidth = 0, maxWidth = 0;
	u32 minHeight = 0, maxHeight = 0;

	void* userData = nullptr;
	i32 posX = 0;
	i32 posY = 0;
};

struct Callbacks
{
	primeWindowCloseFunc close = nullptr;
	primeWindowKeyFunc key = nullptr;
	primeWindowButtonFunc button = nullptr;
	primeWindowMouseMovedFunc mouseMoved = nullptr;
	primeWindowMouseScrolledFunc mouseScrolled = nullptr;
	primeWindowMovedFunc windowMoved = nullptr;
	primeWindowResizeFunc windowResize = nullptr;
	primeWindowFocusedFunc windowFocused = nullptr;
};

static Callbacks s_Callbacks;

static void
mapKeys(primeWindow* window)
{
	PASSERT_MSG(window, "Window is null");

	window->keycodes[0x01E] = primeKeyA;
	window->keycodes[0x030] = primeKeyB;
	window->keycodes[0x02E] = primeKeyC;
	window->keycodes[0x020] = primeKeyD;
	window->keycodes[0x012] = primeKeyE;
	window->keycodes[0x021] = primeKeyF;
	window->keycodes[0x022] = primeKeyG;
	window->keycodes[0x023] = primeKeyH;
	window->keycodes[0x017] = primeKeyI;
	window->keycodes[0x024] = primeKeyJ;
	window->keycodes[0x025] = primeKeyK;
	window->keycodes[0x026] = primeKeyL;
	window->keycodes[0x032] = primeKeyM;
	window->keycodes[0x031] = primeKeyN;
	window->keycodes[0x018] = primeKeyO;
	window->keycodes[0x019] = primeKeyP;
	window->keycodes[0x010] = primeKeyQ;
	window->keycodes[0x013] = primeKeyR;
	window->keycodes[0x01F] = primeKeyS;
	window->keycodes[0x014] = primeKeyT;
	window->keycodes[0x016] = primeKeyU;
	window->keycodes[0x02F] = primeKeyV;
	window->keycodes[0x011] = primeKeyW;
	window->keycodes[0x02D] = primeKeyX;
	window->keycodes[0x015] = primeKeyY;
	window->keycodes[0x02C] = primeKeyZ;

	window->keycodes[0x00B] = primeKey0;
	window->keycodes[0x002] = primeKey1;
	window->keycodes[0x003] = primeKey2;
	window->keycodes[0x004] = primeKey3;
	window->keycodes[0x005] = primeKey4;
	window->keycodes[0x006] = primeKey5;
	window->keycodes[0x007] = primeKey6;
	window->keycodes[0x008] = primeKey7;
	window->keycodes[0x009] = primeKey8;
	window->keycodes[0x00A] = primeKey9;

	window->keycodes[0x028] = primeKeyApostrophe;
	window->keycodes[0x02B] = primeKeyBackslash;
	window->keycodes[0x033] = primeKeyComma;
	window->keycodes[0x00D] = primeKeyEqual;
	window->keycodes[0x029] = primeKeyGraveAccent;
	window->keycodes[0x01A] = primeKeyLeftBracket;
	window->keycodes[0x00C] = primeKeyMinus;
	window->keycodes[0x034] = primeKeyPeriod;
	window->keycodes[0x01B] = primeKeyRightBracket;
	window->keycodes[0x027] = primeKeySemiColon;
	window->keycodes[0x035] = primeKeySlash;

	window->keycodes[0x00E] = primeKeyBackspace;
	window->keycodes[0x153] = primeKeyDelete;
	window->keycodes[0x14F] = primeKeyEnd;
	window->keycodes[0x01C] = primeKeyEnter;
	window->keycodes[0x001] = primeKeyEscape;
	window->keycodes[0x147] = primeKeyHome;
	window->keycodes[0x152] = primeKeyInsert;
	window->keycodes[0x15D] = primeKeyMenu;
	window->keycodes[0x151] = primeKeyPageDown;
	window->keycodes[0x149] = primeKeyPageUp;
	window->keycodes[0x045] = primeKeyPause;
	window->keycodes[0x039] = primeKeySpace;
	window->keycodes[0x00F] = primeKeyTab;
	window->keycodes[0x03A] = primeKeyCapsLock;
	window->keycodes[0x145] = primeKeyNumLock;
	window->keycodes[0x046] = primeKeyScrollLock;
	window->keycodes[0x03B] = primeKeyF1;
	window->keycodes[0x03C] = primeKeyF2;
	window->keycodes[0x03D] = primeKeyF3;
	window->keycodes[0x03E] = primeKeyF4;
	window->keycodes[0x03F] = primeKeyF5;
	window->keycodes[0x040] = primeKeyF6;
	window->keycodes[0x041] = primeKeyF7;
	window->keycodes[0x042] = primeKeyF8;
	window->keycodes[0x043] = primeKeyF9;
	window->keycodes[0x044] = primeKeyF10;
	window->keycodes[0x057] = primeKeyF11;
	window->keycodes[0x058] = primeKeyF12;

	window->keycodes[0x038] = primeKeyLeftAlt;
	window->keycodes[0x01D] = primeKeyLeftControl;
	window->keycodes[0x02A] = primeKeyLeftShift;
	window->keycodes[0x15B] = primeKeyLeftSuper;
	window->keycodes[0x137] = primeKeyPrintScreen;
	window->keycodes[0x138] = primeKeyRightAlt;
	window->keycodes[0x11D] = primeKeyRightControl;
	window->keycodes[0x036] = primeKeyRightShift;
	window->keycodes[0x15C] = primeKeyRightSuper;
	window->keycodes[0x150] = primeKeyDown;
	window->keycodes[0x14B] = primeKeyLeft;
	window->keycodes[0x14D] = primeKeyRight;
	window->keycodes[0x148] = primeKeyUp;

	window->keycodes[0x052] = primeKeyP0;
	window->keycodes[0x04F] = primeKeyP1;
	window->keycodes[0x050] = primeKeyP2;
	window->keycodes[0x051] = primeKeyP3;
	window->keycodes[0x04B] = primeKeyP4;
	window->keycodes[0x04C] = primeKeyP5;
	window->keycodes[0x04D] = primeKeyP6;
	window->keycodes[0x047] = primeKeyP7;
	window->keycodes[0x048] = primeKeyP8;
	window->keycodes[0x049] = primeKeyP9;
	window->keycodes[0x04E] = primeKeyPAdd;
	window->keycodes[0x053] = primeKeyPDecimal;
	window->keycodes[0x135] = primeKeyPDivide;
	window->keycodes[0x11C] = primeKeyPEnter;
	window->keycodes[0x059] = primeKeyPEqual;
	window->keycodes[0x037] = primeKeyPMultiply;
	window->keycodes[0x04A] = primeKeyPSubtract;
}

static void
processKey(primeWindow* window, u16 key, i32 scancode, u8 action)
{
	PASSERT_MSG(window, "Window is null");

	PASSERT_MSG(key >= 0 && key < primeKeyMax, "Invalid Key");
	PASSERT_MSG(action == primeActionRelease || action == primeActionPress, "Invalid action");

	b8 repeated = false;
	if (action == primeActionRelease && window->keys[key] == primeActionRelease) {
		return;
	}

	if (action == primeActionPress && window->keys[key] == primeActionPress) {
		repeated = true;
	}

	if (action == primeActionPress && window->keys[key] == primeActionRelease) {
		window->keys[key] = primeActionPress;
	}
	else {
		window->keys[key] = action;
	}

	if (repeated) {
		action = primeActionRepeat;
	}

	if (s_Callbacks.key) {
		s_Callbacks.key(window, key, scancode, action);
	}
}

static void
processButton(primeWindow* window, u16 button, u8 action)
{
	PASSERT_MSG(window, "Window is null");

	PASSERT_MSG(button >= 0 && button < primeButtonMax, "Invalid Key");
	PASSERT_MSG(action == primeActionRelease || action == primeActionPress, "Invalid action");

	if (action == primeActionPress && window->buttons[button] == primeActionRelease) {
		window->buttons[button] = primeActionPress;
	}
	else {
		window->buttons[button] = action;
	}

	if (s_Callbacks.button) {
		s_Callbacks.button(window, button, action);
	}
}

static void
processMouseMoved(primeWindow* window, i32 x, i32 y)
{
	PASSERT_MSG(window, "Window is null");

	window->mousePos[0] = x;
	window->mousePos[1] = y;

	if (s_Callbacks.mouseMoved) {
		s_Callbacks.mouseMoved(window, x, y);
	}
}

static void
processFocus(primeWindow* window, b8 focused)
{
	PASSERT_MSG(window, "Window is null");

	window->isFocused = focused;
	if (s_Callbacks.windowFocused) {
		s_Callbacks.windowFocused(window, focused);
	}

	if (focused == false) {
		u16 key, button;

		// process keys
		for (key = 0; key <= primeKeyMax; key++) {
			if (window->keys[key] == primeActionPress) {
				const i32 scancode = window->scancodes[key];
				processKey(window, key, scancode, primeActionRelease);
			}
		}

		// proces mouse buttons
		for (button = 0; button <= primeButtonMax; button++) {
			if (window->buttons[button] == primeActionPress) {
				processButton(window, button, primeActionRelease);
			}
		}
	}
}

static void
centerWindow(primeWindow* window, u32 width, u32 height)
{
	PASSERT_MSG(window, "Window is null");

	MONITORINFO monitor_info;
	monitor_info.cbSize = sizeof(MONITORINFO);
	GetMonitorInfo(MonitorFromWindow(window->handle, MONITOR_DEFAULTTONEAREST), &monitor_info);
	u32 max_hwidth = monitor_info.rcMonitor.right;
	u32 max_hheight = monitor_info.rcMonitor.bottom;

	i32 x = (max_hwidth - width) / 2;
	i32 y = (max_hheight - height) / 2;
	window->posX = x;
	window->posY = y;
	SetWindowPos(window->handle, 0, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_SHOWWINDOW);
}

primeWindow*
primeWindowCreate(const char* title, u32 width, u32 height)
{
	u32 style = WS_OVERLAPPEDWINDOW;
	u32 ex_style = WS_EX_APPWINDOW;

	RECT rect = { 0, 0, 0, 0 };
	rect.right = width;
	rect.bottom = height;
	AdjustWindowRectEx(&rect, style, 0, ex_style);

	primeWindow* win = nullptr;
	if (s_Allocator) {}
	else {
		win = (primeWindow*)primeMemoryAlloc(sizeof(primeWindow));
	}

	PASSERT_MSG(win, "window buffer allocation failed");
	win->title = primeStringDuplicate(title);

#ifdef UNICODE
	wchar_t* wstr = primeStringToWstring(title);

	win->handle = CreateWindowExW(ex_style,
		s_ClassName,
		wstr,
		style,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rect.right - rect.left,
		rect.bottom - rect.top,
		NULL,
		NULL,
		s_Instance,
		NULL);

		primeWstringFree(wstr);

#else
	win->handle = CreateWindowExA(ex_style,
			s_ClassName,
			title,
			style,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			rect.right - rect.left,
			rect.bottom - rect.top,
			NULL,
			NULL,
			s_Instance,
			NULL);
#endif // UNICODE
	
	PASSERT_MSG(win->handle, "Window Creation Failed");

	UpdateWindow(win->handle);
	ShowWindow(win->handle, SW_NORMAL);
	SetProp(win->handle, s_PropName, win);

	win->width = width;
	win->height = height;

	primeMemoryZero(win->keycodes, 512);
	primeMemoryZero(win->scancodes, primeKeyMax + 1);
	mapKeys(win);
	win->isFocused = true;

	return win;
}

void
primeWindowDestroy(primeWindow* window)
{
	PASSERT_MSG(window, "Window is null");
	DestroyWindow(window->handle);
	if (window->title) {
		primeStringFree(window->title);
		window->title = nullptr;
	}

	if (s_Allocator) {}
	else {
		primeMemoryFree(window, sizeof(primeWindow));
	}
}

b8
primeWindowShouldClose(primeWindow* window)
{
	PASSERT_MSG(window, "Window is null");
	return window->shouldClose;
}

void
primeWindowPollEvents()
{
	MSG msg;
	while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}

	// from GLFW
	HWND handle = GetActiveWindow();
	if (handle) {

		primeWindow* window = (primeWindow*)GetProp(handle, s_PropName);
		if (window) {
			int i;
			const int keys[4][2] = {
				{ VK_LSHIFT, primeKeyLeftShift },
				{ VK_RSHIFT, primeKeyRightShift },
				{ VK_LWIN, primeKeyLeftSuper },
				{ VK_RWIN, primeKeyRightSuper }
			};

			for (i = 0; i < 4; i++) {
				const int vk = keys[i][0];
				const int key = keys[i][1];
				const int scancode = window->scancodes[key];

				if ((GetKeyState(vk) & 0x8000)) { continue; }
				if (window->keycodes[key] != primeActionPress) { continue; }

				processKey(window, key, scancode, primeActionRelease);
			}
		}
	}
}

void
primeWindowHide(primeWindow* window)
{
	PASSERT_MSG(window, "Window is null");
	window->isHidden = true;
	ShowWindow(window->handle, SW_HIDE);
}

void
primeWindowShow(primeWindow* window)
{
	PASSERT_MSG(window, "Window is null");
	window->isHidden = false;
	ShowWindow(window->handle, SW_SHOW);
}

void
primeWindowSetSize(primeWindow* window, u32 width, u32 height)
{
	PASSERT_MSG(window, "Window is null");
	PASSERT_MSG(width > 0 && height > 0, "invalid Parameter");

	u32 w = 0, h = 0;
	if (width < window->minWidth) {
		w = window->minWidth;
	}

	if (width > window->maxWidth) {
		w = window->maxWidth;
	}
	if (height < window->minHeight) {
		w = window->minHeight;
	}

	if (height > window->maxHeight) {
		w = window->maxHeight;
	}

	RECT rect = { 0, 0, 0, 0 };
	rect.right = w;
	rect.bottom = h;
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, 0, WS_EX_OVERLAPPEDWINDOW);

	window->width = w;
	window->height = h;
	SetWindowPos(window->handle, HWND_TOP,
		0, 0, rect.right - rect.left, rect.bottom - rect.top,
		SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOMOVE | SWP_NOZORDER);
}

void
primeWindowSetPos(primeWindow* window, i32 x, i32 y)
{
	PASSERT_MSG(window, "Window is null");
	RECT rect = { 0, 0, 0, 0 };
	rect.left = x;
	rect.right = x;
	rect.top = y;
	rect.bottom = y;
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, 0, WS_EX_OVERLAPPEDWINDOW);

	window->posX = x;
	window->posY = y;
	SetWindowPos(window->handle, NULL, rect.left, rect.top, 0, 0,
		SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOSIZE);
}

void
primeWindowSetTitle(primeWindow* window, const char* title)
{
	PASSERT_MSG(window, "Window is null");
	window->title = primeStringDuplicate(title);
#ifdef UNICODE
	wchar_t* wstr = primeStringToWstring(title);
	SetWindowText(window->handle, wstr);
	primeWstringFree(wstr);
#else
	SetWindowTextA(window->handle, title);
#endif // UNCODE
}

void
primeWindowSetMinSize(primeWindow* window, u32 width, u32 height)
{
	PASSERT_MSG(window, "Window is null");
	window->minWidth = width;
	window->minHeight = height;
}

void
primeWindowSetMaxSize(primeWindow* window, u32 width, u32 height)
{
	PASSERT_MSG(window, "Window is null");
	window->maxWidth = width;
	window->maxHeight = height;
}

void
primeWindowSetUserData(primeWindow* window, void* data)
{
	PASSERT_MSG(window, "Window is null");
	window->userData = data;
}

void
primeWindowSetCloseCallback(primeWindowCloseFunc func)
{
	s_Callbacks.close = func;
}

void
primeWindowSetKeyCallback(primeWindowKeyFunc func)
{
	s_Callbacks.key = func;
}

void
primeWindowSetButtonCallback(primeWindowButtonFunc func)
{
	s_Callbacks.button = func;
}

void
primeWindowSetMouseMovedCallback(primeWindowMouseMovedFunc func)
{
	s_Callbacks.mouseMoved = func;
}

void
primeWindowSetMouseScrolledCallback(primeWindowMouseScrolledFunc func)
{
	s_Callbacks.mouseScrolled = func;
}

void
primeWindowSetMovedCallback(primeWindowMovedFunc func)
{
	s_Callbacks.windowMoved = func;
}

void
primeWindowSetResizeCallback(primeWindowResizeFunc func)
{
	s_Callbacks.windowResize = func;
}

void
primeWindowSetFocusedCallback(primeWindowFocusedFunc func)
{
	s_Callbacks.windowFocused = func;
}

void 
primeWindowResetCallbacks()
{
	s_Callbacks.button = nullptr;
	s_Callbacks.button = nullptr;
	s_Callbacks.key = nullptr;
	s_Callbacks.mouseMoved = nullptr;
	s_Callbacks.mouseScrolled = nullptr;
	s_Callbacks.windowFocused = nullptr;
	s_Callbacks.windowMoved = nullptr;
	s_Callbacks.windowResize = nullptr;
}

const u32
primeWindowGetWidth(primeWindow* window)
{
	PASSERT_MSG(window, "Window is null");
	return window->width;
}

const u32
primeWindowGetHeight(primeWindow* window)
{
	PASSERT_MSG(window, "Window is null");
	return window->height;
}

void
primeWindowGetMinSize(primeWindow* window, u32* width, u32* height)
{
	PASSERT_MSG(window, "Window is null");
	*width = window->minWidth;
	*height = window->minHeight;
}

void
primeWindowGetMaxSize(primeWindow* window, u32* width, u32* height)
{
	PASSERT_MSG(window, "Window is null");
	*width = window->maxWidth;
	*height = window->maxHeight;
}

const i32
primeWindowGetPosX(primeWindow* window)
{
	PASSERT_MSG(window, "Window is null");
	return window->posX;
}

const i32
primeWindowGetPosY(primeWindow* window)
{
	PASSERT_MSG(window, "Window is null");
	return window->posY;
}

const char*
primeWindowGetTitle(primeWindow* window)
{
	PASSERT_MSG(window, "Window is null");
	return window->title;
}

void*
primeWindowGetUserData(primeWindow* window)
{
	PASSERT_MSG(window, "Window is null");
	return window->userData;
}

b8
primeWindowGetKeyState(primeWindow* window, u16 key)
{
	PASSERT_MSG(window, "Window is null");
	PASSERT_MSG(key >= 0, "Invalid key");
	PASSERT_MSG(key < primeKeyMax, "Invalid key");
	return window->keys[key] == primeActionPress;
}

b8
primeWindowGetButtonState(primeWindow* window, u16 button)
{
	PASSERT_MSG(window, "Window is null");
	PASSERT_MSG(button >= 0, "Invalid button");
	PASSERT_MSG(button < primeButtonMax, "Invalid button");
	return window->buttons[button] == primeActionPress;
}

const b8
primeWindowIsHidden(primeWindow* window)
{
	PASSERT_MSG(window, "Window is null");
	return window->isHidden;
}

const b8
primeWindowIsMaximized(primeWindow* window)
{
	PASSERT_MSG(window, "Window is null");
	GetWindowPlacement(window->handle, &s_WndPlacement);
	if (s_WndPlacement.showCmd == SW_SHOWMAXIMIZED) {
		return true;
	}
	return false;
}

HWND
primeWindowGetWin32Handle(primeWindow* window)
{
	PASSERT_MSG(window, "window is null");
	return window->handle;
}

HINSTANCE
primeWindowGetWin32HInstance(primeWindow* window)
{
	PASSERT_MSG(window, "window is null");
	return s_Instance;
}

LRESULT CALLBACK
primeWin32Proc(HWND hwnd, u32 msg, WPARAM w_param, LPARAM l_param)
{
	primeWindow* window = (primeWindow*)GetProp(hwnd, s_PropName);

	if (!window) {
		// no window created
		return DefWindowProc(hwnd, msg, w_param, l_param);
	}

	switch (msg)
	{
	case WM_CLOSE: {
		window->shouldClose = true;
		if (s_Callbacks.close) {
			s_Callbacks.close(window);
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
		const u8 action = (HIWORD(l_param) & KF_UP) ? primeActionRelease : primeActionPress;
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

		key = window->keycodes[scancode];

		// The Ctrl keys require special handling
		if (w_param == VK_CONTROL)
		{
			if (HIWORD(l_param) & KF_EXTENDED)
			{
				// Right side keys have the extended key bit set
				key = primeKeyRightControl;
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
				key = primeKeyLeftControl;
			}
		}
		else if (w_param == VK_PROCESSKEY)
		{
			// IME notifies that keys have been filtered by setting the
			// virtual key-code to VK_PROCESSKEY
			break;
		}

		if (action == primeActionRelease && w_param == VK_SHIFT)
		{
			// HACK: Release both Shift keys on Shift up event, as when both
			//       are pressed the first release does not emit any event
			// NOTE: The other half of this is in _glfwPollEventsWin32
			processKey(window, primeKeyLeftShift, scancode, action);
			processKey(window, primeKeyRightShift, scancode, action);
		}
		else if (w_param == VK_SNAPSHOT)
		{
			// HACK: Key down is not reported for the Print Screen key
			processKey(window, key, scancode, primeActionPress);
			processKey(window, key, scancode, primeActionRelease);
		}
		else {
			processKey(window, key, scancode, action);
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

		if (msg == WM_LBUTTONDOWN || msg == WM_LBUTTONUP) {
			button = primeButtonLeft;
		}

		else if (msg == WM_RBUTTONDOWN || msg == WM_RBUTTONUP) {
			button = primeButtonRight;
		}

		else if (msg == WM_MBUTTONDOWN || msg == WM_MBUTTONUP) {
			button = primeButtonMiddle;
		}

		if (msg == WM_LBUTTONDOWN || msg == WM_RBUTTONDOWN ||
			msg == WM_MBUTTONDOWN || msg == WM_XBUTTONDOWN) {
			action = primeActionPress;
		}
		else {
			action = primeActionRelease;
		}

		if (msg == WM_LBUTTONDOWN) {
			SetCapture(hwnd);
		}
		else if (msg == WM_LBUTTONUP) {
			ReleaseCapture();
		}

		processButton(window, button, action);
		if (msg == WM_XBUTTONDOWN || msg == WM_XBUTTONUP) { return true; }

		return 0;
		break;
	}

	case WM_MOUSEMOVE: {
		const int x = GET_X_LPARAM(l_param);
		const int y = GET_Y_LPARAM(l_param);

		if (window->isFocused) { processMouseMoved(window, x, y); }

		return 0;
		break;
	}

	case WM_MOUSEWHEEL: {
		if (s_Callbacks.mouseScrolled) {
			s_Callbacks.mouseScrolled(window, 0.0, (f32)HIWORD(w_param) / (f32)WHEEL_DELTA);
		}

		return 0;
		break;
	}

	case WM_MOVE: {
		i32 x = GET_X_LPARAM(l_param);
		i32 y = GET_Y_LPARAM(l_param);
		window->posX = x;
		window->posY = y;

		if (s_Callbacks.windowMoved) {
			s_Callbacks.windowMoved(window, x, y);
		}

		return 0;
		break;
	}

	case WM_SIZE: {
		const u32 width = (u32)LOWORD(l_param);
		const u32 height = (u32)HIWORD(l_param);

		if (width != window->width || height != window->height) {
			window->width = width;
			window->height = height;

			if (s_Callbacks.windowResize) {
				s_Callbacks.windowResize(window, width, height);
			}
		}
		return 0;
		break;
	}

	case WM_SETFOCUS: {
		processFocus(window, true);

		return 0;
		break;
	}

	case WM_KILLFOCUS: {
		processFocus(window, false);

		return 0;
		break;
	}

	case WM_GETMINMAXINFO: {
		MINMAXINFO* mmi = (MINMAXINFO*)l_param;
		if (window->minWidth > 0) {
			mmi->ptMinTrackSize.x = window->minWidth;
		}
		if (window->maxWidth > 0) {
			mmi->ptMaxTrackSize.x = window->maxWidth;
		}

		if (window->minHeight > 0) {
			mmi->ptMinTrackSize.y = window->minHeight;
		}
		if (window->maxHeight > 0) {
			mmi->ptMaxTrackSize.y = window->maxHeight;
		}
		return 0;
		break;
	}

	case WM_PAINT:
    {
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		HBRUSH brush = CreateSolidBrush(0);
		FillRect(hdc, &ps.rcPaint, brush);
		EndPaint(hwnd, &ps);
		DeleteObject(brush);

		return 0;
        break;
    }

	}

	return DefWindowProc(hwnd, msg, w_param, l_param);
}