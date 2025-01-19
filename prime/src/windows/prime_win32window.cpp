
#include "prime_win32platform.h"
#include "prime_utils.h"

#ifdef PRIME_PLATFORM_WINDOWS

#include <string>

struct prime_Window
{
	HWND handle = nullptr;
	prime_Context* context = nullptr;
	u32 width = 0;
	u32 height = 0;
	prime_String* title = nullptr;
	b8 shouldClose = false, isFocused = false;
	b8 isHidden = false;

	u16 keycodes[512] = {};
	u16 scancodes[prime_KeyMax + 1] = {};

	u8 keys[prime_KeyMax + 1] = {};
	u8 buttons[prime_ButtonMax + 1] = {};

	i32 mousePos[2] = {};
	u32 minWidth = 0, maxWidth = 0;
	u32 minHeight = 0, maxHeight = 0;

	void* userData = nullptr;
	i32 posX = 0;
	i32 posY = 0;
};

static std::string s_Keynames[prime_KeyMax + 1] = {};
static std::string s_Buttonnames[prime_ButtonMax + 1] = {};
static b8 s_Init = false;

struct Callbacks
{
	prime_WindowCloseFunc close = nullptr;
	prime_WindowKeyFunc key = nullptr;
	prime_WindowButtonFunc button = nullptr;
	prime_WindowMouseMovedFunc mouseMoved = nullptr;
	prime_WindowMouseScrolledFunc mouseScrolled = nullptr;
	prime_WindowPosFunc windowPos = nullptr;
	prime_WindowSizeFunc windowSize = nullptr;
	prime_WindowFocusFunc windowFocus = nullptr;
};

static Callbacks s_Callbacks;

static void
mapKeys(prime_Window* window)
{
	PRIME_ASSERT_MSG(window, "Window is null");

	window->keycodes[0x01E] = prime_KeyA;
	window->keycodes[0x030] = prime_KeyB;
	window->keycodes[0x02E] = prime_KeyC;
	window->keycodes[0x020] = prime_KeyD;
	window->keycodes[0x012] = prime_KeyE;
	window->keycodes[0x021] = prime_KeyF;
	window->keycodes[0x022] = prime_KeyG;
	window->keycodes[0x023] = prime_KeyH;
	window->keycodes[0x017] = prime_KeyI;
	window->keycodes[0x024] = prime_KeyJ;
	window->keycodes[0x025] = prime_KeyK;
	window->keycodes[0x026] = prime_KeyL;
	window->keycodes[0x032] = prime_KeyM;
	window->keycodes[0x031] = prime_KeyN;
	window->keycodes[0x018] = prime_KeyO;
	window->keycodes[0x019] = prime_KeyP;
	window->keycodes[0x010] = prime_KeyQ;
	window->keycodes[0x013] = prime_KeyR;
	window->keycodes[0x01F] = prime_KeyS;
	window->keycodes[0x014] = prime_KeyT;
	window->keycodes[0x016] = prime_KeyU;
	window->keycodes[0x02F] = prime_KeyV;
	window->keycodes[0x011] = prime_KeyW;
	window->keycodes[0x02D] = prime_KeyX;
	window->keycodes[0x015] = prime_KeyY;
	window->keycodes[0x02C] = prime_KeyZ;

	window->keycodes[0x00B] = prime_Key0;
	window->keycodes[0x002] = prime_Key1;
	window->keycodes[0x003] = prime_Key2;
	window->keycodes[0x004] = prime_Key3;
	window->keycodes[0x005] = prime_Key4;
	window->keycodes[0x006] = prime_Key5;
	window->keycodes[0x007] = prime_Key6;
	window->keycodes[0x008] = prime_Key7;
	window->keycodes[0x009] = prime_Key8;
	window->keycodes[0x00A] = prime_Key9;

	window->keycodes[0x028] = prime_KeyApostrophe;
	window->keycodes[0x02B] = prime_KeyBackslash;
	window->keycodes[0x033] = prime_KeyComma;
	window->keycodes[0x00D] = prime_KeyEqual;
	window->keycodes[0x029] = prime_KeyGraveAccent;
	window->keycodes[0x01A] = prime_KeyLeftBracket;
	window->keycodes[0x00C] = prime_KeyMinus;
	window->keycodes[0x034] = prime_KeyPeriod;
	window->keycodes[0x01B] = prime_KeyRightBracket;
	window->keycodes[0x027] = prime_KeySemiColon;
	window->keycodes[0x035] = prime_KeySlash;

	window->keycodes[0x00E] = prime_KeyBackspace;
	window->keycodes[0x153] = prime_KeyDelete;
	window->keycodes[0x14F] = prime_KeyEnd;
	window->keycodes[0x01C] = prime_KeyEnter;
	window->keycodes[0x001] = prime_KeyEscape;
	window->keycodes[0x147] = prime_KeyHome;
	window->keycodes[0x152] = prime_KeyInsert;
	window->keycodes[0x15D] = prime_KeyMenu;
	window->keycodes[0x151] = prime_KeyPageDown;
	window->keycodes[0x149] = prime_KeyPageUp;
	window->keycodes[0x045] = prime_KeyPause;
	window->keycodes[0x039] = prime_KeySpace;
	window->keycodes[0x00F] = prime_KeyTab;
	window->keycodes[0x03A] = prime_KeyCapsLock;
	window->keycodes[0x145] = prime_KeyNumLock;
	window->keycodes[0x046] = prime_KeyScrollLock;
	window->keycodes[0x03B] = prime_KeyF1;
	window->keycodes[0x03C] = prime_KeyF2;
	window->keycodes[0x03D] = prime_KeyF3;
	window->keycodes[0x03E] = prime_KeyF4;
	window->keycodes[0x03F] = prime_KeyF5;
	window->keycodes[0x040] = prime_KeyF6;
	window->keycodes[0x041] = prime_KeyF7;
	window->keycodes[0x042] = prime_KeyF8;
	window->keycodes[0x043] = prime_KeyF9;
	window->keycodes[0x044] = prime_KeyF10;
	window->keycodes[0x057] = prime_KeyF11;
	window->keycodes[0x058] = prime_KeyF12;

	window->keycodes[0x038] = prime_KeyLeftAlt;
	window->keycodes[0x01D] = prime_KeyLeftControl;
	window->keycodes[0x02A] = prime_KeyLeftShift;
	window->keycodes[0x15B] = prime_KeyLeftSuper;
	window->keycodes[0x137] = prime_KeyPrintScreen;
	window->keycodes[0x138] = prime_KeyRightAlt;
	window->keycodes[0x11D] = prime_KeyRightControl;
	window->keycodes[0x036] = prime_KeyRightShift;
	window->keycodes[0x15C] = prime_KeyRightSuper;
	window->keycodes[0x150] = prime_KeyDown;
	window->keycodes[0x14B] = prime_KeyLeft;
	window->keycodes[0x14D] = prime_KeyRight;
	window->keycodes[0x148] = prime_KeyUp;

	window->keycodes[0x052] = prime_KeyP0;
	window->keycodes[0x04F] = prime_KeyP1;
	window->keycodes[0x050] = prime_KeyP2;
	window->keycodes[0x051] = prime_KeyP3;
	window->keycodes[0x04B] = prime_KeyP4;
	window->keycodes[0x04C] = prime_KeyP5;
	window->keycodes[0x04D] = prime_KeyP6;
	window->keycodes[0x047] = prime_KeyP7;
	window->keycodes[0x048] = prime_KeyP8;
	window->keycodes[0x049] = prime_KeyP9;
	window->keycodes[0x04E] = prime_KeyPAdd;
	window->keycodes[0x053] = prime_KeyPDecimal;
	window->keycodes[0x135] = prime_KeyPDivide;
	window->keycodes[0x11C] = prime_KeyPEnter;
	window->keycodes[0x059] = prime_KeyPEqual;
	window->keycodes[0x037] = prime_KeyPMultiply;
	window->keycodes[0x04A] = prime_KeyPSubtract;
}

static void 
mapKeyNames()
{
	s_Keynames[prime_KeyA] = "Key A";
	s_Keynames[prime_KeyB] = "Key B";
	s_Keynames[prime_KeyC] = "Key C";
	s_Keynames[prime_KeyD] = "Key D";
	s_Keynames[prime_KeyE] = "Key E";
	s_Keynames[prime_KeyF] = "Key F";
	s_Keynames[prime_KeyG] = "Key G";
	s_Keynames[prime_KeyH] = "Key H";
	s_Keynames[prime_KeyI] = "Key I";
	s_Keynames[prime_KeyJ] = "Key J";
	s_Keynames[prime_KeyK] = "Key K";
	s_Keynames[prime_KeyL] = "Key L";
	s_Keynames[prime_KeyM] = "Key M";
	s_Keynames[prime_KeyN] = "Key N";
	s_Keynames[prime_KeyO] = "Key O";
	s_Keynames[prime_KeyP] = "Key P";
	s_Keynames[prime_KeyQ] = "Key Q";
	s_Keynames[prime_KeyR] = "Key R";
	s_Keynames[prime_KeyS] = "Key S";
	s_Keynames[prime_KeyT] = "Key T";
	s_Keynames[prime_KeyU] = "Key U";
	s_Keynames[prime_KeyV] = "Key V";
	s_Keynames[prime_KeyW] = "Key W";
	s_Keynames[prime_KeyX] = "Key X";
	s_Keynames[prime_KeyY] = "Key Y";
	s_Keynames[prime_KeyZ] = "Key Z";

	s_Keynames[prime_KeyEscape] = "Key Escape";
	s_Keynames[prime_KeyEnter] = "Key Enter";
	s_Keynames[prime_KeyTab] = "Key Tab";
	s_Keynames[prime_KeyBackspace] = "Key Backspace";
	s_Keynames[prime_KeyInsert] = "Key Insert";
	s_Keynames[prime_KeyDelete] = "Key Delete";
	s_Keynames[prime_KeyRight] = "Key Right";
	s_Keynames[prime_KeyLeft] = "Key Left";
	s_Keynames[prime_KeyDown] = "Key Down";
	s_Keynames[prime_KeyUp] = "Key Up";
	s_Keynames[prime_KeyPageUp] = "Key PageUp";
	s_Keynames[prime_KeyPageDown] = "Key PageDown";
	s_Keynames[prime_KeyHome] = "Key Home";
	s_Keynames[prime_KeyEnd] = "Key End";
	s_Keynames[prime_KeyCapsLock] = "Key CapsLock";
	s_Keynames[prime_KeyScrollLock] = "Key ScrollLock";
	s_Keynames[prime_KeyNumLock] = "Key NumLock";
	s_Keynames[prime_KeyPrintScreen] = "Key Pru16Screen";
	s_Keynames[prime_KeyPause] = "Key Pause";
	s_Keynames[prime_KeyF1] = "Key F1";
	s_Keynames[prime_KeyF2] = "Key F2";
	s_Keynames[prime_KeyF3] = "Key F3";
	s_Keynames[prime_KeyF4] = "Key F4";
	s_Keynames[prime_KeyF5] = "Key F5";
	s_Keynames[prime_KeyF6] = "Key F6";
	s_Keynames[prime_KeyF7] = "Key F7";
	s_Keynames[prime_KeyF8] = "Key F8";
	s_Keynames[prime_KeyF9] = "Key F9";
	s_Keynames[prime_KeyF10] = "Key F10";
	s_Keynames[prime_KeyF11] = "Key F11";
	s_Keynames[prime_KeyF12] = "Key F12";

	s_Keynames[prime_KeyLeftShift] = "Key LeftShift";
	s_Keynames[prime_KeyLeftControl] = "Key LeftControl";
	s_Keynames[prime_KeyLeftAlt] = "Key LeftAlt";
	s_Keynames[prime_KeyLeftSuper] = "Key LeftSuper";
	s_Keynames[prime_KeyLeftBracket] = "Key LeftBracket";
	s_Keynames[prime_KeyRightShift] = "Key RightShift";
	s_Keynames[prime_KeyRightControl] = "Key RightControl";
	s_Keynames[prime_KeyRightAlt] = "Key RightAlt";
	s_Keynames[prime_KeyRightSuper] = "Key RightSuper";
	s_Keynames[prime_KeyRightBracket] = "Key RightBracket";

	s_Keynames[prime_KeyMenu] = "Key Menu";
	s_Keynames[prime_KeyBackslash] = "Key Backslash";
	s_Keynames[prime_KeyGraveAccent] = "Key GraveAccent";
	s_Keynames[prime_KeySemiColon] = "Key SemiColon";
	s_Keynames[prime_KeyEqual] = "Key Equal";

	s_Keynames[prime_KeySpace] = "Key Space";
	s_Keynames[prime_KeyApostrophe] = "Key Apostrophe";
	s_Keynames[prime_KeyComma] = "Key Comma";
	s_Keynames[prime_KeyMinus] = "Key Minus";
	s_Keynames[prime_KeyPeriod] = "Key Period";
	s_Keynames[prime_KeySlash] = "Key Slash";

	s_Keynames[prime_Key0] = "Key 0";
	s_Keynames[prime_Key1] = "Key 1";
	s_Keynames[prime_Key2] = "Key 2";
	s_Keynames[prime_Key3] = "Key 3";
	s_Keynames[prime_Key4] = "Key 4";
	s_Keynames[prime_Key5] = "Key 5";
	s_Keynames[prime_Key6] = "Key 6";
	s_Keynames[prime_Key7] = "Key 7";
	s_Keynames[prime_Key8] = "Key 8";
	s_Keynames[prime_Key9] = "Key 9";

	s_Keynames[prime_KeyP0] = "Key P0";
	s_Keynames[prime_KeyP1] = "Key P1";
	s_Keynames[prime_KeyP2] = "Key P2";
	s_Keynames[prime_KeyP3] = "Key P3";
	s_Keynames[prime_KeyP4] = "Key P4";
	s_Keynames[prime_KeyP5] = "Key P5";
	s_Keynames[prime_KeyP6] = "Key P6";
	s_Keynames[prime_KeyP7] = "Key P7";
	s_Keynames[prime_KeyP8] = "Key P8";
	s_Keynames[prime_KeyP9] = "Key P9";
	s_Keynames[prime_KeyPDecimal] = "Key PDecimal";
	s_Keynames[prime_KeyPDivide] = "Key PDivide";
	s_Keynames[prime_KeyPMultiply] = "Key PMultiply";
	s_Keynames[prime_KeyPSubtract] = "Key PSubtract";
	s_Keynames[prime_KeyPAdd] = "Key PAdd";
	s_Keynames[prime_KeyPEnter] = "Key PEnter";
	s_Keynames[prime_KeyPEqual] = "Key PEqual";
}

static void
mapButtonNames()
{
	s_Buttonnames[prime_ButtonLeft] = "Button Left";
	s_Buttonnames[prime_ButtonRight] = "Button Right";
	s_Buttonnames[prime_ButtonMiddle] = "Button Middle";
}

static void
processKey(prime_Window* window, u16 key, i32 scancode, u8 action)
{
	PRIME_ASSERT_MSG(window, "Window is null");

	PRIME_ASSERT_MSG(key >= 0 && key < prime_KeyMax, "Invalid Key");
	PRIME_ASSERT_MSG(action == PRIME_RELEASE || action == PRIME_PRESS, "Invalid action");

	b8 repeated = false;
	if (action == PRIME_RELEASE && window->keys[key] == PRIME_RELEASE) {
		return;
	}

	if (action == PRIME_PRESS && window->keys[key] == PRIME_PRESS) {
		repeated = true;
	}

	if (action == PRIME_PRESS && window->keys[key] == PRIME_RELEASE) {
		window->keys[key] = PRIME_PRESS;
	}
	else {
		window->keys[key] = action;
	}

	if (repeated) {
		action = PRIME_REPEAT;
	}

	if (s_Callbacks.key) {
		s_Callbacks.key(window, key, scancode, action);
	}
}

static void
processButton(prime_Window* window, u16 button, u8 action)
{
	PRIME_ASSERT_MSG(window, "Window is null");

	PRIME_ASSERT_MSG(button >= 0 && button < prime_ButtonMax, "Invalid Key");
	PRIME_ASSERT_MSG(action == PRIME_RELEASE || action == PRIME_PRESS, "Invalid action");

	if (action == PRIME_PRESS && window->buttons[button] == PRIME_RELEASE) {
		window->buttons[button] = PRIME_PRESS;
	}
	else {
		window->buttons[button] = action;
	}

	if (s_Callbacks.button) {
		s_Callbacks.button(window, button, action);
	}
}

static void
processMouseMoved(prime_Window* window, i32 x, i32 y)
{
	PRIME_ASSERT_MSG(window, "Window is null");

	window->mousePos[0] = x;
	window->mousePos[1] = y;

	if (s_Callbacks.mouseMoved) {
		s_Callbacks.mouseMoved(window, x, y);
	}
}

static void
processFocus(prime_Window* window, b8 focused)
{
	PRIME_ASSERT_MSG(window, "Window is null");

	window->isFocused = focused;
	if (s_Callbacks.windowFocus) {
		s_Callbacks.windowFocus(window, focused);
	}

	if (focused == false) {
		u16 key, button;

		// process keys
		for (key = 0; key <= prime_KeyMax; key++) {
			if (window->keys[key] == PRIME_PRESS) {
				const i32 scancode = window->scancodes[key];
				processKey(window, key, scancode, PRIME_RELEASE);
			}
		}

		// proces mouse buttons
		for (button = 0; button <= prime_ButtonMax; button++) {
			if (window->buttons[button] == PRIME_PRESS) {
				processButton(window, button, PRIME_RELEASE);
			}
		}
	}
}

static void 
centerWindow(prime_Window* window, u32 width, u32 height)
{
	PRIME_ASSERT_MSG(window, "Window is null");

	MONITORINFO monitor_info;
	monitor_info.cbSize = sizeof(MONITORINFO);
	GetMonitorInfo(MonitorFromWindow(window->handle, MONITOR_DEFAULTTONEAREST), &monitor_info);
	u32 max_width = monitor_info.rcMonitor.right;
	u32 max_height = monitor_info.rcMonitor.bottom;

	i32 x = (max_width - width) / 2;
	i32 y = (max_height - height) / 2;
	window->posX = x;
	window->posY = y;
	SetWindowPos(window->handle, 0, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_SHOWWINDOW);
}

prime_Window*
prime_CreateWindow(const char* title, u32 width, u32 height)
{
	u32 style = WS_OVERLAPPEDWINDOW;
	u32 ex_style = WS_EX_APPWINDOW;

	RECT rect = { 0, 0, 0, 0 };
	rect.right = width;
	rect.bottom = height;
	AdjustWindowRectEx(&rect, style, 0, ex_style);

	prime_Window* window = (prime_Window*)prime_MemAlloc(sizeof(prime_Window));
	window->title = prime_CstrToString(title);

	prime_WString* wide_str = prime_StringToWString(window->title);

	HWND hwnd = CreateWindowExW(ex_style,
		s_ClassName,
		prime_GetWstr(wide_str),
		style,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rect.right - rect.left,
		rect.bottom - rect.top,
		NULL,
		NULL,
		s_Instance,
		NULL);

	PRIME_ASSERT_MSG(hwnd, "Window Creation Failed");

	
	window->handle = hwnd;
	UpdateWindow(window->handle);
	centerWindow(window, width, height);
	ShowWindow(window->handle, SW_NORMAL);
	SetPropW(window->handle, s_PropName, window);

	window->width = width;
	window->height = height;
	prime_MemZero(window->keycodes, 512);
	prime_MemZero(window->scancodes, prime_KeyMax + 1);
	mapKeys(window);

	if (s_Init == false) {
		mapKeyNames();
		mapButtonNames();
		s_Init = true;
	}
	window->isFocused = true;

	return window;
}

void
prime_DestroyWindow(prime_Window* window)
{
	PRIME_ASSERT_MSG(window, "Window is null");
	DestroyWindow(window->handle);
	window->isFocused = false;
	window->userData = nullptr;
	prime_MemFree(window, sizeof(prime_Window));
	window = nullptr;
}

b8
prime_WindowShouldClose(prime_Window* window)
{
	PRIME_ASSERT_MSG(window, "Window is null");
	return window->shouldClose;
}

void
prime_PollEvents()
{
	MSG msg;
	while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}

	// from GLFW
	HWND handle = GetActiveWindow();
	if (handle) {

		prime_Window* window = (prime_Window*)GetPropW(handle, s_PropName);
		if (window) {
			int i;
			const int keys[4][2] = {
				{ VK_LSHIFT, prime_KeyLeftShift },
				{ VK_RSHIFT, prime_KeyRightShift },
				{ VK_LWIN, prime_KeyLeftSuper },
				{ VK_RWIN, prime_KeyRightSuper }
			};

			for (i = 0; i < 4; i++) {
				const int vk = keys[i][0];
				const int key = keys[i][1];
				const int scancode = window->scancodes[key];

				if ((GetKeyState(vk) & 0x8000)) { continue; }
				if (window->keycodes[key] != PRIME_PRESS) { continue; }

				processKey(window, key, scancode, PRIME_RELEASE);
			}
		}
	}
}

void
prime_SetWindowCloseCallback(prime_WindowCloseFunc func)
{
	if (func) {
		s_Callbacks.close = func;
	}
}

void
prime_SetWindowKeyCallback(prime_WindowKeyFunc func)
{
	if (func) {
		s_Callbacks.key = func;
	}
}

void
prime_SetWindowButtonCallback(prime_WindowButtonFunc func)
{
	if (func) {
		s_Callbacks.button = func;
	}
}

void
prime_SetWindowMouseMovedCallback(prime_WindowMouseMovedFunc func)
{
	if (func) {
		s_Callbacks.mouseMoved = func;
	}
}

void
prime_SetWindowMouseScrolledCallback(prime_WindowMouseScrolledFunc func)
{
	if (func) {
		s_Callbacks.mouseScrolled = func;
	}
}

void
prime_SetWindowPosCallback(prime_WindowPosFunc func)
{
	if (func) {
		s_Callbacks.windowPos = func;
	}
}

void
prime_SetWindowSizeCallback(prime_WindowSizeFunc func)
{
	if (func) {
		s_Callbacks.windowSize = func;
	}
}

void
prime_SetWindowFocusCallback(prime_WindowFocusFunc func)
{
	if (func) {
		s_Callbacks.windowFocus = func;
	}
}

void
prime_HideWindow(prime_Window* window)
{
	PRIME_ASSERT_MSG(window, "Window is null");
	window->isHidden = true;
	ShowWindow(window->handle, SW_HIDE);
}

void
prime_ShowWindow(prime_Window* window)
{
	PRIME_ASSERT_MSG(window, "Window is null");
	window->isHidden = false;
	ShowWindow(window->handle, SW_SHOW);
}

void
prime_SetWindowSize(prime_Window* window, u32 width, u32 height)
{
	PRIME_ASSERT_MSG(window, "Window is null");
	PRIME_ASSERT_MSG(width > 0 && height > 0, "invalid Parameter");

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
prime_SetWindowPos(prime_Window* window, i32 x, i32 y)
{
	PRIME_ASSERT_MSG(window, "Window is null");
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
prime_SetWindowTitle(prime_Window* window, const char* title)
{
	PRIME_ASSERT_MSG(window, "Window is null");
	window->title = prime_CstrToString(title);
	prime_WString* wide_str = prime_StringToWString(window->title);
	SetWindowTextW(window->handle, prime_GetWstr(wide_str));
}

void
prime_SetWindowMinSize(prime_Window* window, u32 width, u32 height)
{
	PRIME_ASSERT_MSG(window, "Window is null");
	window->minWidth = width;
	window->minHeight = width;
}

void
prime_SetWindowMaxSize(prime_Window* window, u32 width, u32 height)
{
	PRIME_ASSERT_MSG(window, "Window is null");
	window->maxWidth = width;
	window->maxHeight = width;
}

void
prime_SetWindowUserData(prime_Window* window, void* data)
{
	PRIME_ASSERT_MSG(window, "Window is null");
	if (data) {
		window->userData = data;
	}

}

const u32
prime_GetWindowWidth(prime_Window* window)
{
	PRIME_ASSERT_MSG(window, "Window is null");
	return window->width;
}

const u32
prime_GetWindowHeight(prime_Window* window)
{
	PRIME_ASSERT_MSG(window, "Window is null");
	return window->height;
}

const u32
prime_GetWindowMinWidth(prime_Window* window)
{
	PRIME_ASSERT_MSG(window, "Window is null");
	return window->minWidth;
}

const u32
prime_GetWindowMinHeight(prime_Window* window)
{
	PRIME_ASSERT_MSG(window, "Window is null");
	return window->minHeight;
}

const u32
prime_GetWindowMaxWidth(prime_Window* window)
{
	PRIME_ASSERT_MSG(window, "Window is null");
	return window->maxWidth;
}

const u32
prime_GetWindowMaxHeight(prime_Window* window)
{
	PRIME_ASSERT_MSG(window, "Window is null");
	return window->maxHeight;
}

const i32
prime_GetWindowPosX(prime_Window* window)
{
	PRIME_ASSERT_MSG(window, "Window is null");
	return window->posX;
}

const i32
prime_GetWindowPosY(prime_Window* window)
{
	PRIME_ASSERT_MSG(window, "Window is null");
	return window->posY;
}

prime_String*
prime_GetWindowTitle(prime_Window* window)
{
	PRIME_ASSERT_MSG(window, "Window is null");
	return window->title;
}

void*
prime_GetWindowUserData(prime_Window* window)
{
	PRIME_ASSERT_MSG(window, "Window is null");
	return window->userData;
}

b8
prime_GetWindowKeyState(prime_Window* window, u16 key)
{
	PRIME_ASSERT_MSG(window, "Window is null");
	PRIME_ASSERT_MSG(key >= 0, "Invalid key");
	PRIME_ASSERT_MSG(key < prime_KeyMax, "Invalid key");
	return window->keys[key] == PRIME_PRESS;
}

b8
prime_GetWindowButtonState(prime_Window* window, u16 button)
{
	PRIME_ASSERT_MSG(window, "Window is null");
	PRIME_ASSERT_MSG(button >= 0, "Invalid button");
	PRIME_ASSERT_MSG(button < prime_ButtonMax, "Invalid button");
	return window->buttons[button] == PRIME_PRESS;
}

prime_String* 
prime_GetWindowKeyName(prime_Window* window, u16 key)
{
	PRIME_ASSERT_MSG(window, "Window is null");
	PRIME_ASSERT_MSG(key >= 0, "Invalid key");
	PRIME_ASSERT_MSG(key < prime_KeyMax, "Invalid key");
	return prime_CstrToString(s_Keynames[key].c_str());
}

prime_String*
prime_GetWindowButtonName(prime_Window* window, u16 button)
{
	PRIME_ASSERT_MSG(window, "Window is null");
	PRIME_ASSERT_MSG(button >= 0, "Invalid button");
	PRIME_ASSERT_MSG(button < prime_ButtonMax, "Invalid button");
	return prime_CstrToString(s_Buttonnames[button].c_str());
}

prime_String*
prime_GetWindowActionName(prime_Window* window, u8 action)
{
	PRIME_ASSERT_MSG(window, "Window is null");
	prime_String* str = nullptr;

	if (action == PRIME_RELEASE) {
		return prime_CstrToString("RELEASE");
	}
	else if (action == PRIME_PRESS) {
		return prime_CstrToString("PRESS");
	}
	else if (action == PRIME_REPEAT) {
		return prime_CstrToString("REPEAT");
	}
	PRIME_ASSERT_MSG(false, "Invalid action");
	return nullptr;
}

const b8
prime_IsWindowHidden(prime_Window* window)
{
	PRIME_ASSERT_MSG(window, "Window is null");
	return window->isHidden;
}

const b8
prime_IsWindowMaximized(prime_Window* window)
{
	PRIME_ASSERT_MSG(window, "Window is null");
	GetWindowPlacement(window->handle, &s_WndPlacement);
	if (s_WndPlacement.showCmd == SW_SHOWMAXIMIZED) {
		return true;
	}
	return false;
}

HWND 
prime_GetWin32WindowHandle(prime_Window* window)
{
	PRIME_ASSERT_MSG(window, "Window is null");
	return window->handle;
}

HINSTANCE 
prime_GetWin32HInstance(prime_Window* window)
{
	PRIME_ASSERT_MSG(window, "Window is null");
	return s_Instance;
}

void
prime_SetWindowContext(prime_Window* window, prime_Context* context)
{
	window->context = context;
}

b8
prime_WindowHasContext(prime_Window* window)
{
	return window->context;
}

LRESULT CALLBACK
prime_WinProc(HWND hwnd, u32 msg, WPARAM w_param, LPARAM l_param)
{
	prime_Window* window = (prime_Window*)GetProp(hwnd, s_PropName);

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
		const u8 action = (HIWORD(l_param) & KF_UP) ? PRIME_RELEASE : PRIME_PRESS;
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
				key = prime_KeyRightControl;
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
				key = prime_KeyLeftControl;
			}
		}
		else if (w_param == VK_PROCESSKEY)
		{
			// IME notifies that keys have been filtered by setting the
			// virtual key-code to VK_PROCESSKEY
			break;
		}

		if (action == PRIME_RELEASE && w_param == VK_SHIFT)
		{
			// HACK: Release both Shift keys on Shift up event, as when both
			//       are pressed the first release does not emit any event
			// NOTE: The other half of this is in _glfwPollEventsWin32
			processKey(window, prime_KeyLeftShift, scancode, action);
			processKey(window, prime_KeyRightShift, scancode, action);
		}
		else if (w_param == VK_SNAPSHOT)
		{
			// HACK: Key down is not reported for the Print Screen key
			processKey(window, key, scancode, PRIME_PRESS);
			processKey(window, key, scancode, PRIME_RELEASE);
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
			button = prime_ButtonLeft;
		}

		else if (msg == WM_RBUTTONDOWN || msg == WM_RBUTTONUP) {
			button = prime_ButtonRight;
		}

		else if (msg == WM_MBUTTONDOWN || msg == WM_MBUTTONUP) {
			button = prime_ButtonMiddle;
		}

		if (msg == WM_LBUTTONDOWN || msg == WM_RBUTTONDOWN ||
			msg == WM_MBUTTONDOWN || msg == WM_XBUTTONDOWN) {
			action = PRIME_PRESS;
		}
		else {
			action = PRIME_RELEASE;
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

		if (s_Callbacks.windowPos) {
			s_Callbacks.windowPos(window, x, y);
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

			if (s_Callbacks.windowSize) {
				s_Callbacks.windowSize(window, width, height);
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

	case WM_PAINT: {
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		HBRUSH brush = CreateSolidBrush(0);
		FillRect(hdc, &ps.rcPaint, brush);
		EndPaint(hwnd, &ps);
		DeleteObject(brush);

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

	}
	return DefWindowProc(hwnd, msg, w_param, l_param);
}

#endif // PRIME_PLATFORM_WINDOWS