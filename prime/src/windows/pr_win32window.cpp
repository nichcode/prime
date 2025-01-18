
#include "pr_win32platform.h"
#include "pr_platform.h"

#ifdef PR_PLATFORM_WINDOWS

#include <string>

struct PrWindow
{
	HWND handle = nullptr;
	PrDriverContext* context = nullptr;
	u32 width = 0;
	u32 height = 0;
	PrString* title = nullptr;
	b8 shouldClose = false, isFocused = false;
	b8 isHidden = false;

	u16 keycodes[512] = {};
	u16 scancodes[PrKey_Max + 1] = {};

	u8 keys[PrKey_Max + 1] = {};
	u8 buttons[PrButton_Max + 1] = {};

	i32 mousePos[2] = {};
	u32 minWidth = 0, maxWidth = 0;
	u32 minHeight = 0, maxHeight = 0;

	void* userData = nullptr;
	i32 posX = 0;
	i32 posY = 0;
};

static std::string s_Keynames[PrKey_Max + 1] = {};
static std::string s_Buttonnames[PrButton_Max + 1] = {};
static b8 s_Init = false;

struct PrCallbacks
{
	PrWindowCloseFunc close = nullptr;
	PrWindowKeyFunc key = nullptr;
	PrWindowButtonFunc button = nullptr;
	PrWindowMouseMovedFunc mouseMoved = nullptr;
	PrWindowMouseScrolledFunc mouseScrolled = nullptr;
	PrWindowPosFunc windowPos = nullptr;
	PrWindowSizeFunc windowSize = nullptr;
	PrWindowFocusFunc windowFocus = nullptr;
};

static PrCallbacks s_Callbacks;

static void
prWindowMapKeys(PrWindow* window)
{
	PR_ASSERT_MSG(window, "Window is null");

	window->keycodes[0x01E] = PrKey_A;
	window->keycodes[0x030] = PrKey_B;
	window->keycodes[0x02E] = PrKey_C;
	window->keycodes[0x020] = PrKey_D;
	window->keycodes[0x012] = PrKey_E;
	window->keycodes[0x021] = PrKey_F;
	window->keycodes[0x022] = PrKey_G;
	window->keycodes[0x023] = PrKey_H;
	window->keycodes[0x017] = PrKey_I;
	window->keycodes[0x024] = PrKey_J;
	window->keycodes[0x025] = PrKey_K;
	window->keycodes[0x026] = PrKey_L;
	window->keycodes[0x032] = PrKey_M;
	window->keycodes[0x031] = PrKey_N;
	window->keycodes[0x018] = PrKey_O;
	window->keycodes[0x019] = PrKey_P;
	window->keycodes[0x010] = PrKey_Q;
	window->keycodes[0x013] = PrKey_R;
	window->keycodes[0x01F] = PrKey_S;
	window->keycodes[0x014] = PrKey_T;
	window->keycodes[0x016] = PrKey_U;
	window->keycodes[0x02F] = PrKey_V;
	window->keycodes[0x011] = PrKey_W;
	window->keycodes[0x02D] = PrKey_X;
	window->keycodes[0x015] = PrKey_Y;
	window->keycodes[0x02C] = PrKey_Z;

	window->keycodes[0x00B] = PrKey_0;
	window->keycodes[0x002] = PrKey_1;
	window->keycodes[0x003] = PrKey_2;
	window->keycodes[0x004] = PrKey_3;
	window->keycodes[0x005] = PrKey_4;
	window->keycodes[0x006] = PrKey_5;
	window->keycodes[0x007] = PrKey_6;
	window->keycodes[0x008] = PrKey_7;
	window->keycodes[0x009] = PrKey_8;
	window->keycodes[0x00A] = PrKey_9;

	window->keycodes[0x028] = PrKey_Apostrophe;
	window->keycodes[0x02B] = PrKey_Backslash;
	window->keycodes[0x033] = PrKey_Comma;
	window->keycodes[0x00D] = PrKey_Equal;
	window->keycodes[0x029] = PrKey_GraveAccent;
	window->keycodes[0x01A] = PrKey_LeftBracket;
	window->keycodes[0x00C] = PrKey_Minus;
	window->keycodes[0x034] = PrKey_Period;
	window->keycodes[0x01B] = PrKey_RightBracket;
	window->keycodes[0x027] = PrKey_SemiColon;
	window->keycodes[0x035] = PrKey_Slash;

	window->keycodes[0x00E] = PrKey_Backspace;
	window->keycodes[0x153] = PrKey_Delete;
	window->keycodes[0x14F] = PrKey_End;
	window->keycodes[0x01C] = PrKey_Enter;
	window->keycodes[0x001] = PrKey_Escape;
	window->keycodes[0x147] = PrKey_Home;
	window->keycodes[0x152] = PrKey_Insert;
	window->keycodes[0x15D] = PrKey_Menu;
	window->keycodes[0x151] = PrKey_PageDown;
	window->keycodes[0x149] = PrKey_PageUp;
	window->keycodes[0x045] = PrKey_Pause;
	window->keycodes[0x039] = PrKey_Space;
	window->keycodes[0x00F] = PrKey_Tab;
	window->keycodes[0x03A] = PrKey_CapsLock;
	window->keycodes[0x145] = PrKey_NumLock;
	window->keycodes[0x046] = PrKey_ScrollLock;
	window->keycodes[0x03B] = PrKey_F1;
	window->keycodes[0x03C] = PrKey_F2;
	window->keycodes[0x03D] = PrKey_F3;
	window->keycodes[0x03E] = PrKey_F4;
	window->keycodes[0x03F] = PrKey_F5;
	window->keycodes[0x040] = PrKey_F6;
	window->keycodes[0x041] = PrKey_F7;
	window->keycodes[0x042] = PrKey_F8;
	window->keycodes[0x043] = PrKey_F9;
	window->keycodes[0x044] = PrKey_F10;
	window->keycodes[0x057] = PrKey_F11;
	window->keycodes[0x058] = PrKey_F12;

	window->keycodes[0x038] = PrKey_LeftAlt;
	window->keycodes[0x01D] = PrKey_LeftControl;
	window->keycodes[0x02A] = PrKey_LeftShift;
	window->keycodes[0x15B] = PrKey_LeftSuper;
	window->keycodes[0x137] = PrKey_PrintScreen;
	window->keycodes[0x138] = PrKey_RightAlt;
	window->keycodes[0x11D] = PrKey_RightControl;
	window->keycodes[0x036] = PrKey_RightShift;
	window->keycodes[0x15C] = PrKey_RightSuper;
	window->keycodes[0x150] = PrKey_Down;
	window->keycodes[0x14B] = PrKey_Left;
	window->keycodes[0x14D] = PrKey_Right;
	window->keycodes[0x148] = PrKey_Up;

	window->keycodes[0x052] = PrKey_P0;
	window->keycodes[0x04F] = PrKey_P1;
	window->keycodes[0x050] = PrKey_P2;
	window->keycodes[0x051] = PrKey_P3;
	window->keycodes[0x04B] = PrKey_P4;
	window->keycodes[0x04C] = PrKey_P5;
	window->keycodes[0x04D] = PrKey_P6;
	window->keycodes[0x047] = PrKey_P7;
	window->keycodes[0x048] = PrKey_P8;
	window->keycodes[0x049] = PrKey_P9;
	window->keycodes[0x04E] = PrKey_PAdd;
	window->keycodes[0x053] = PrKey_PDecimal;
	window->keycodes[0x135] = PrKey_PDivide;
	window->keycodes[0x11C] = PrKey_PEnter;
	window->keycodes[0x059] = PrKey_PEqual;
	window->keycodes[0x037] = PrKey_PMultiply;
	window->keycodes[0x04A] = PrKey_PSubtract;
}

static void 
prWindowMapKeyNames()
{
	s_Keynames[PrKey_A] = "Key A";
	s_Keynames[PrKey_B] = "Key B";
	s_Keynames[PrKey_C] = "Key C";
	s_Keynames[PrKey_D] = "Key D";
	s_Keynames[PrKey_E] = "Key E";
	s_Keynames[PrKey_F] = "Key F";
	s_Keynames[PrKey_G] = "Key G";
	s_Keynames[PrKey_H] = "Key H";
	s_Keynames[PrKey_I] = "Key I";
	s_Keynames[PrKey_J] = "Key J";
	s_Keynames[PrKey_K] = "Key K";
	s_Keynames[PrKey_L] = "Key L";
	s_Keynames[PrKey_M] = "Key M";
	s_Keynames[PrKey_N] = "Key N";
	s_Keynames[PrKey_O] = "Key O";
	s_Keynames[PrKey_P] = "Key P";
	s_Keynames[PrKey_Q] = "Key Q";
	s_Keynames[PrKey_R] = "Key R";
	s_Keynames[PrKey_S] = "Key S";
	s_Keynames[PrKey_T] = "Key T";
	s_Keynames[PrKey_U] = "Key U";
	s_Keynames[PrKey_V] = "Key V";
	s_Keynames[PrKey_W] = "Key W";
	s_Keynames[PrKey_X] = "Key X";
	s_Keynames[PrKey_Y] = "Key Y";
	s_Keynames[PrKey_Z] = "Key Z";

	s_Keynames[PrKey_Escape] = "Key Escape";
	s_Keynames[PrKey_Enter] = "Key Enter";
	s_Keynames[PrKey_Tab] = "Key Tab";
	s_Keynames[PrKey_Backspace] = "Key Backspace";
	s_Keynames[PrKey_Insert] = "Key Insert";
	s_Keynames[PrKey_Delete] = "Key Delete";
	s_Keynames[PrKey_Right] = "Key Right";
	s_Keynames[PrKey_Left] = "Key Left";
	s_Keynames[PrKey_Down] = "Key Down";
	s_Keynames[PrKey_Up] = "Key Up";
	s_Keynames[PrKey_PageUp] = "Key PageUp";
	s_Keynames[PrKey_PageDown] = "Key PageDown";
	s_Keynames[PrKey_Home] = "Key Home";
	s_Keynames[PrKey_End] = "Key End";
	s_Keynames[PrKey_CapsLock] = "Key CapsLock";
	s_Keynames[PrKey_ScrollLock] = "Key ScrollLock";
	s_Keynames[PrKey_NumLock] = "Key NumLock";
	s_Keynames[PrKey_PrintScreen] = "Key Pru16Screen";
	s_Keynames[PrKey_Pause] = "Key Pause";
	s_Keynames[PrKey_F1] = "Key F1";
	s_Keynames[PrKey_F2] = "Key F2";
	s_Keynames[PrKey_F3] = "Key F3";
	s_Keynames[PrKey_F4] = "Key F4";
	s_Keynames[PrKey_F5] = "Key F5";
	s_Keynames[PrKey_F6] = "Key F6";
	s_Keynames[PrKey_F7] = "Key F7";
	s_Keynames[PrKey_F8] = "Key F8";
	s_Keynames[PrKey_F9] = "Key F9";
	s_Keynames[PrKey_F10] = "Key F10";
	s_Keynames[PrKey_F11] = "Key F11";
	s_Keynames[PrKey_F12] = "Key F12";

	s_Keynames[PrKey_LeftShift] = "Key LeftShift";
	s_Keynames[PrKey_LeftControl] = "Key LeftControl";
	s_Keynames[PrKey_LeftAlt] = "Key LeftAlt";
	s_Keynames[PrKey_LeftSuper] = "Key LeftSuper";
	s_Keynames[PrKey_LeftBracket] = "Key LeftBracket";
	s_Keynames[PrKey_RightShift] = "Key RightShift";
	s_Keynames[PrKey_RightControl] = "Key RightControl";
	s_Keynames[PrKey_RightAlt] = "Key RightAlt";
	s_Keynames[PrKey_RightSuper] = "Key RightSuper";
	s_Keynames[PrKey_RightBracket] = "Key RightBracket";

	s_Keynames[PrKey_Menu] = "Key Menu";
	s_Keynames[PrKey_Backslash] = "Key Backslash";
	s_Keynames[PrKey_GraveAccent] = "Key GraveAccent";
	s_Keynames[PrKey_SemiColon] = "Key SemiColon";
	s_Keynames[PrKey_Equal] = "Key Equal";

	s_Keynames[PrKey_Space] = "Key Space";
	s_Keynames[PrKey_Apostrophe] = "Key Apostrophe";
	s_Keynames[PrKey_Comma] = "Key Comma";
	s_Keynames[PrKey_Minus] = "Key Minus";
	s_Keynames[PrKey_Period] = "Key Period";
	s_Keynames[PrKey_Slash] = "Key Slash";

	s_Keynames[PrKey_0] = "Key 0";
	s_Keynames[PrKey_1] = "Key 1";
	s_Keynames[PrKey_2] = "Key 2";
	s_Keynames[PrKey_3] = "Key 3";
	s_Keynames[PrKey_4] = "Key 4";
	s_Keynames[PrKey_5] = "Key 5";
	s_Keynames[PrKey_6] = "Key 6";
	s_Keynames[PrKey_7] = "Key 7";
	s_Keynames[PrKey_8] = "Key 8";
	s_Keynames[PrKey_9] = "Key 9";

	s_Keynames[PrKey_P0] = "Key P0";
	s_Keynames[PrKey_P1] = "Key P1";
	s_Keynames[PrKey_P2] = "Key P2";
	s_Keynames[PrKey_P3] = "Key P3";
	s_Keynames[PrKey_P4] = "Key P4";
	s_Keynames[PrKey_P5] = "Key P5";
	s_Keynames[PrKey_P6] = "Key P6";
	s_Keynames[PrKey_P7] = "Key P7";
	s_Keynames[PrKey_P8] = "Key P8";
	s_Keynames[PrKey_P9] = "Key P9";
	s_Keynames[PrKey_PDecimal] = "Key PDecimal";
	s_Keynames[PrKey_PDivide] = "Key PDivide";
	s_Keynames[PrKey_PMultiply] = "Key PMultiply";
	s_Keynames[PrKey_PSubtract] = "Key PSubtract";
	s_Keynames[PrKey_PAdd] = "Key PAdd";
	s_Keynames[PrKey_PEnter] = "Key PEnter";
	s_Keynames[PrKey_PEqual] = "Key PEqual";
}

static void
prWindowMapButtonNames()
{
	s_Buttonnames[PrButton_Left] = "Button Left";
	s_Buttonnames[PrButton_Right] = "Button Right";
	s_Buttonnames[PrButton_Middle] = "Button Middle";
}

static void
prWindowProcessKey(PrWindow* window, u16 key, i32 scancode, u8 action)
{
	PR_ASSERT_MSG(window, "Window is null");

	PR_ASSERT_MSG(key >= 0 && key < PrKey_Max, "Invalid Key");
	PR_ASSERT_MSG(action == PR_RELEASE || action == PR_PRESS, "Invalid action");

	b8 repeated = false;
	if (action == PR_RELEASE && window->keys[key] == PR_RELEASE) {
		return;
	}

	if (action == PR_PRESS && window->keys[key] == PR_PRESS) {
		repeated = true;
	}

	if (action == PR_PRESS && window->keys[key] == PR_RELEASE) {
		window->keys[key] = PR_PRESS;
	}
	else {
		window->keys[key] = action;
	}

	if (repeated) {
		action = PR_REPEAT;
	}

	if (s_Callbacks.key) {
		s_Callbacks.key(window, key, scancode, action);
	}
}

static void
prWindowProcessButton(PrWindow* window, u16 button, u8 action)
{
	PR_ASSERT_MSG(window, "Window is null");

	PR_ASSERT_MSG(button >= 0 && button < PrButton_Max, "Invalid Key");
	PR_ASSERT_MSG(action == PR_RELEASE || action == PR_PRESS, "Invalid action");

	if (action == PR_PRESS && window->buttons[button] == PR_RELEASE) {
		window->buttons[button] = PR_PRESS;
	}
	else {
		window->buttons[button] = action;
	}

	if (s_Callbacks.button) {
		s_Callbacks.button(window, button, action);
	}
}

static void
prWindowProcessMouseMoved(PrWindow* window, i32 x, i32 y)
{
	PR_ASSERT_MSG(window, "Window is null");

	window->mousePos[0] = x;
	window->mousePos[1] = y;

	if (s_Callbacks.mouseMoved) {
		s_Callbacks.mouseMoved(window, x, y);
	}
}

static void
prWindowProcessFocus(PrWindow* window, b8 focused)
{
	PR_ASSERT_MSG(window, "Window is null");

	window->isFocused = focused;
	if (s_Callbacks.windowFocus) {
		s_Callbacks.windowFocus(window, focused);
	}

	if (focused == false) {
		u16 key, button;

		// process keys
		for (key = 0; key <= PrKey_Max; key++) {
			if (window->keys[key] == PR_PRESS) {
				const i32 scancode = window->scancodes[key];
				prWindowProcessKey(window, key, scancode, PR_RELEASE);
			}
		}

		// proces mouse buttons
		for (button = 0; button <= PrButton_Max; button++) {
			if (window->buttons[button] == PR_PRESS) {
				prWindowProcessButton(window, button, PR_RELEASE);
			}
		}
	}
}

static void 
prWindowCenter(PrWindow* window, u32 width, u32 height)
{
	PR_ASSERT_MSG(window, "Window is null");

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

PrWindow*
prWindowCreate(const char* title, u32 width, u32 height)
{
	u32 style = WS_OVERLAPPEDWINDOW;
	u32 ex_style = WS_EX_APPWINDOW;

	RECT rect = { 0, 0, 0, 0 };
	rect.right = width;
	rect.bottom = height;
	AdjustWindowRectEx(&rect, style, 0, ex_style);

	PrWindow* window = (PrWindow*)prMemAlloc(sizeof(PrWindow));
	window->title = prStringCreate(title);

	PrWideString* wide_Str = prWideStringCreateFromPrString(window->title);

	HWND hwnd = CreateWindowExW(ex_style,
		s_ClassName,
		prWideStringGetBuffer(wide_Str),
		style,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rect.right - rect.left,
		rect.bottom - rect.top,
		NULL,
		NULL,
		s_Instance,
		NULL);

	PR_ASSERT_MSG(hwnd, "Window Creation Failed");

	
	window->handle = hwnd;
	UpdateWindow(window->handle);
	prWindowCenter(window, width, height);
	ShowWindow(window->handle, SW_NORMAL);
	SetPropW(window->handle, s_PropName, window);

	window->width = width;
	window->height = height;
	prMemZero(window->keycodes, 512);
	prMemZero(window->scancodes, PrKey_Max + 1);
	prWindowMapKeys(window);

	if (s_Init == false) {
		prWindowMapKeyNames();
		prWindowMapButtonNames();
		s_Init = true;
	}
	window->isFocused = true;

	return window;
}

void
prWindowDestroy(PrWindow* window)
{
	PR_ASSERT_MSG(window, "Window is null");
	DestroyWindow(window->handle);
	window->isFocused = false;
	window->userData = nullptr;
	prMemFree(window, sizeof(PrWindow));
	window = nullptr;
}

b8
prWindowShouldClose(PrWindow* window)
{
	PR_ASSERT_MSG(window, "Window is null");
	return window->shouldClose;
}

void
prWindowPollEvents()
{
	MSG msg;
	while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}

	// from GLFW
	HWND handle = GetActiveWindow();
	if (handle) {

		PrWindow* window = (PrWindow*)GetPropW(handle, s_PropName);
		if (window) {
			int i;
			const int keys[4][2] = {
				{ VK_LSHIFT, PrKey_LeftShift },
				{ VK_RSHIFT, PrKey_RightShift },
				{ VK_LWIN, PrKey_LeftSuper },
				{ VK_RWIN, PrKey_RightSuper }
			};

			for (i = 0; i < 4; i++) {
				const int vk = keys[i][0];
				const int key = keys[i][1];
				const int scancode = window->scancodes[key];

				if ((GetKeyState(vk) & 0x8000)) { continue; }
				if (window->keycodes[key] != PR_PRESS) { continue; }

				prWindowProcessKey(window, key, scancode, PR_RELEASE);
			}
		}
	}
}

void
prWindowSetCloseCallback(PrWindowCloseFunc func)
{
	if (func) {
		s_Callbacks.close = func;
	}
}

void
prWindowSetKeyCallback(PrWindowKeyFunc func)
{
	if (func) {
		s_Callbacks.key = func;
	}
}

void
prWindowSetButtonCallback(PrWindowButtonFunc func)
{
	if (func) {
		s_Callbacks.button = func;
	}
}

void
prWindowSetMouseMovedCallback(PrWindowMouseMovedFunc func)
{
	if (func) {
		s_Callbacks.mouseMoved = func;
	}
}

void
prWindowSetMouseScrolledCallback(PrWindowMouseScrolledFunc func)
{
	if (func) {
		s_Callbacks.mouseScrolled = func;
	}
}

void
prWindowSetPosCallback(PrWindowPosFunc func)
{
	if (func) {
		s_Callbacks.windowPos = func;
	}
}

void
prWindowSetSizeCallback(PrWindowSizeFunc func)
{
	if (func) {
		s_Callbacks.windowSize = func;
	}
}

void
prWindowSetFocusCallback(PrWindowFocusFunc func)
{
	if (func) {
		s_Callbacks.windowFocus = func;
	}
}

void
prWindowHide(PrWindow* window)
{
	PR_ASSERT_MSG(window, "Window is null");
	window->isHidden = true;
	ShowWindow(window->handle, SW_HIDE);
}

void
prWindowShow(PrWindow* window)
{
	PR_ASSERT_MSG(window, "Window is null");
	window->isHidden = false;
	ShowWindow(window->handle, SW_SHOW);
}

void
prWindowSetSize(PrWindow* window, u32 width, u32 height)
{
	PR_ASSERT_MSG(window, "Window is null");
	PR_ASSERT_MSG(width > 0 && height > 0, "invalid Parameter");

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
prWindowSetPos(PrWindow* window, i32 x, i32 y)
{
	PR_ASSERT_MSG(window, "Window is null");
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
prWindowSetTitle(PrWindow* window, const char* title)
{
	PR_ASSERT_MSG(window, "Window is null");
	window->title = prStringCreate(title);
	PrWideString* wide_str = prWideStringCreateFromPrString(window->title);
	SetWindowTextW(window->handle, prWideStringGetBuffer(wide_str));
}

void
prWindowSetMinSize(PrWindow* window, u32 width, u32 height)
{
	PR_ASSERT_MSG(window, "Window is null");
	window->minWidth = width;
	window->minHeight = width;
}

void
prWindowSetMaxSize(PrWindow* window, u32 width, u32 height)
{
	PR_ASSERT_MSG(window, "Window is null");
	window->maxWidth = width;
	window->maxHeight = width;
}

void
prWindowSetUserData(PrWindow* window, void* data)
{
	PR_ASSERT_MSG(window, "Window is null");
	if (data) {
		window->userData = data;
	}

}

const u32
prWindowGetWidth(PrWindow* window)
{
	PR_ASSERT_MSG(window, "Window is null");
	return window->width;
}

const u32
prWindowGetHeight(PrWindow* window)
{
	PR_ASSERT_MSG(window, "Window is null");
	return window->height;
}

const u32
prWindowGetMinWidth(PrWindow* window)
{
	PR_ASSERT_MSG(window, "Window is null");
	return window->minWidth;
}

const u32
prWindowGetMinHeight(PrWindow* window)
{
	PR_ASSERT_MSG(window, "Window is null");
	return window->minHeight;
}

const u32
prWindowGetMaxWidth(PrWindow* window)
{
	PR_ASSERT_MSG(window, "Window is null");
	return window->maxWidth;
}

const u32
prWindowGetMaxHeight(PrWindow* window)
{
	PR_ASSERT_MSG(window, "Window is null");
	return window->maxHeight;
}

const i32
prWindowGetPosX(PrWindow* window)
{
	PR_ASSERT_MSG(window, "Window is null");
	return window->posX;
}

const i32
prWindowGetPosY(PrWindow* window)
{
	PR_ASSERT_MSG(window, "Window is null");
	return window->posY;
}

PrString*
prWindowGetTitle(PrWindow* window)
{
	PR_ASSERT_MSG(window, "Window is null");
	return window->title;
}

void*
prWindowGetUserData(PrWindow* window)
{
	PR_ASSERT_MSG(window, "Window is null");
	return window->userData;
}

b8
prWindowGetKeyState(PrWindow* window, u16 key)
{
	PR_ASSERT_MSG(window, "Window is null");
	PR_ASSERT_MSG(key >= 0, "Invalid key");
	PR_ASSERT_MSG(key < PrKey_Max, "Invalid key");
	return window->keys[key] == PR_PRESS;
}

b8
prWindowGetButtonState(PrWindow* window, u16 button)
{
	PR_ASSERT_MSG(window, "Window is null");
	PR_ASSERT_MSG(button >= 0, "Invalid button");
	PR_ASSERT_MSG(button < PrButton_Max, "Invalid button");
	return window->buttons[button] == PR_PRESS;
}

PrString* 
prWindowGetKeyName(PrWindow* window, u16 key)
{
	PR_ASSERT_MSG(window, "Window is null");
	PR_ASSERT_MSG(key >= 0, "Invalid key");
	PR_ASSERT_MSG(key < PrKey_Max, "Invalid key");
	return prStringCreate(s_Keynames[key].c_str());
}

PrString*
prWindowGetButtonName(PrWindow* window, u16 button)
{
	PR_ASSERT_MSG(window, "Window is null");
	PR_ASSERT_MSG(button >= 0, "Invalid button");
	PR_ASSERT_MSG(button < PrButton_Max, "Invalid button");
	return prStringCreate(s_Buttonnames[button].c_str());
}

PrString*
prWindowGetActionName(PrWindow* window, u8 action)
{
	PR_ASSERT_MSG(window, "Window is null");
	PrString* str = nullptr;

	if (action == PR_RELEASE) {
		return prStringCreate("RELEASE");
	}
	else if (action == PR_PRESS) {
		return prStringCreate("PRESS");
	}
	else if (action == PR_REPEAT) {
		return prStringCreate("REPEAT");
	}
	PR_ASSERT_MSG(false, "Invalid action");
	return nullptr;
}

const b8
prWindowHidden(PrWindow* window)
{
	PR_ASSERT_MSG(window, "Window is null");
	return window->isHidden;
}

const b8
prWindowMaximized(PrWindow* window)
{
	PR_ASSERT_MSG(window, "Window is null");
	GetWindowPlacement(window->handle, &s_WndPlacement);
	if (s_WndPlacement.showCmd == SW_SHOWMAXIMIZED) {
		return true;
	}
	return false;
}

HWND 
prWin32GetWindowHandle(PrWindow* window)
{
	PR_ASSERT_MSG(window, "Window is null");
	return window->handle;
}

HINSTANCE 
prWin32GetHInstance(PrWindow* window)
{
	PR_ASSERT_MSG(window, "Window is null");
	return s_Instance;
}

void
prPlatformWin32WindowSetContext(PrWindow* window, PrDriverContext* context)
{
	window->context = context;
}

b8
prPlatformWin32HasContext(PrWindow* window)
{
	return window->context;
}

LRESULT CALLBACK
prWinProc(HWND hwnd, u32 msg, WPARAM w_param, LPARAM l_param)
{
	PrWindow* window = (PrWindow*)GetProp(hwnd, s_PropName);

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
		const u8 action = (HIWORD(l_param) & KF_UP) ? PR_RELEASE : PR_PRESS;
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
				key = PrKey_RightControl;
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
				key = PrKey_LeftControl;
			}
		}
		else if (w_param == VK_PROCESSKEY)
		{
			// IME notifies that keys have been filtered by setting the
			// virtual key-code to VK_PROCESSKEY
			break;
		}

		if (action == PR_RELEASE && w_param == VK_SHIFT)
		{
			// HACK: Release both Shift keys on Shift up event, as when both
			//       are pressed the first release does not emit any event
			// NOTE: The other half of this is in _glfwPollEventsWin32
			prWindowProcessKey(window, PrKey_LeftShift, scancode, action);
			prWindowProcessKey(window, PrKey_RightShift, scancode, action);
		}
		else if (w_param == VK_SNAPSHOT)
		{
			// HACK: Key down is not reported for the Print Screen key
			prWindowProcessKey(window, key, scancode, PR_PRESS);
			prWindowProcessKey(window, key, scancode, PR_RELEASE);
		}
		else {
			prWindowProcessKey(window, key, scancode, action);
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
			button = PrButton_Left;
		}

		else if (msg == WM_RBUTTONDOWN || msg == WM_RBUTTONUP) {
			button = PrButton_Right;
		}

		else if (msg == WM_MBUTTONDOWN || msg == WM_MBUTTONUP) {
			button = PrButton_Middle;
		}

		if (msg == WM_LBUTTONDOWN || msg == WM_RBUTTONDOWN ||
			msg == WM_MBUTTONDOWN || msg == WM_XBUTTONDOWN) {
			action = PR_PRESS;
		}
		else {
			action = PR_RELEASE;
		}

		if (msg == WM_LBUTTONDOWN) {
			SetCapture(hwnd);
		}
		else if (msg == WM_LBUTTONUP) {
			ReleaseCapture();
		}

		prWindowProcessButton(window, button, action);
		if (msg == WM_XBUTTONDOWN || msg == WM_XBUTTONUP) { return true; }

		return 0;
		break;
	}

	case WM_MOUSEMOVE: {
		const int x = GET_X_LPARAM(l_param);
		const int y = GET_Y_LPARAM(l_param);

		if (window->isFocused) { prWindowProcessMouseMoved(window, x, y); }

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
		prWindowProcessFocus(window, true);

		return 0;
		break;
	}

	case WM_KILLFOCUS: {
		prWindowProcessFocus(window, false);

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

#endif // PR_PLATFORM_WINDOWS