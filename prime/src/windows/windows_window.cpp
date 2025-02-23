
#include "prime/window.h"
#include "prime/logger.h"
#include "prime/utils.h"
#include "prime/platform.h"

#ifdef PPLATFORM_WINDOWS

#include "windows_api.h"

namespace prime {

    struct WindowHandle
    {
        HWND hwnd = nullptr;
        u32 width = 0, height = 0;
        str title = "";
        b8 shouldClose = false, isFocused = false;
        b8 isHidden = false;

        u16 keycodes[512] = {};
        u16 scancodes[(u32)(u32)Key::Max + 1] = {};

        u8 keys[(u32)(u32)Key::Max + 1] = {};
        u8 buttons[(u32)Button::Max + 1] = {};

        i32 mousePos[2] = {};
        u32 minWidth = 0, maxWidth = 0;
        u32 minHeight = 0, maxHeight = 0;

        i32 posX = 0;
        i32 posY = 0;
    };

    struct Callbacks
    {
        WindowCloseFunc close = nullptr;
        WindowKeyFunc key = nullptr;
        WindowButtonFunc button = nullptr;
        WindowMouseMovedFunc mouseMoved = nullptr;
        WindowMouseScrolledFunc mouseScrolled = nullptr;
        WindowMovedFunc windowMoved = nullptr;
        WindowResizeFunc windowResize = nullptr;
        WindowFocusedFunc windowFocused = nullptr;
    };

    static Callbacks s_Callbacks;

    static void
    mapKeys(WindowHandle* win)
    {
        win->keycodes[0x01E] = (u32)Key::A;
        win->keycodes[0x030] = (u32)Key::B;
        win->keycodes[0x02E] = (u32)Key::C;
        win->keycodes[0x020] = (u32)Key::D;
        win->keycodes[0x012] = (u32)Key::E;
        win->keycodes[0x021] = (u32)Key::F;
        win->keycodes[0x022] = (u32)Key::G;
        win->keycodes[0x023] = (u32)Key::H;
        win->keycodes[0x017] = (u32)Key::I;
        win->keycodes[0x024] = (u32)Key::J;
        win->keycodes[0x025] = (u32)Key::K;
        win->keycodes[0x026] = (u32)Key::L;
        win->keycodes[0x032] = (u32)Key::M;
        win->keycodes[0x031] = (u32)Key::N;
        win->keycodes[0x018] = (u32)Key::O;
        win->keycodes[0x019] = (u32)Key::P;
        win->keycodes[0x010] = (u32)Key::Q;
        win->keycodes[0x013] = (u32)Key::R;
        win->keycodes[0x01F] = (u32)Key::S;
        win->keycodes[0x014] = (u32)Key::T;
        win->keycodes[0x016] = (u32)Key::U;
        win->keycodes[0x02F] = (u32)Key::V;
        win->keycodes[0x011] = (u32)Key::W;
        win->keycodes[0x02D] = (u32)Key::X;
        win->keycodes[0x015] = (u32)Key::Y;
        win->keycodes[0x02C] = (u32)Key::Z;

        win->keycodes[0x00B] = (u32)Key::Num0;
        win->keycodes[0x002] = (u32)Key::Num1;
        win->keycodes[0x003] = (u32)Key::Num2;
        win->keycodes[0x004] = (u32)Key::Num3;
        win->keycodes[0x005] = (u32)Key::Num4;
        win->keycodes[0x006] = (u32)Key::Num5;
        win->keycodes[0x007] = (u32)Key::Num6;
        win->keycodes[0x008] = (u32)Key::Num7;
        win->keycodes[0x009] = (u32)Key::Num8;
        win->keycodes[0x00A] = (u32)Key::Num9;

        win->keycodes[0x028] = (u32)Key::Apostrophe;
        win->keycodes[0x02B] = (u32)Key::Backslash;
        win->keycodes[0x033] = (u32)Key::Comma;
        win->keycodes[0x00D] = (u32)Key::Equal;
        win->keycodes[0x029] = (u32)Key::GraveAccent;
        win->keycodes[0x01A] = (u32)Key::LeftBracket;
        win->keycodes[0x00C] = (u32)Key::Minus;
        win->keycodes[0x034] = (u32)Key::Period;
        win->keycodes[0x01B] = (u32)Key::RightBracket;
        win->keycodes[0x027] = (u32)Key::SemiColon;
        win->keycodes[0x035] = (u32)Key::Slash;

        win->keycodes[0x00E] = (u32)Key::Backspace;
        win->keycodes[0x153] = (u32)Key::Delete;
        win->keycodes[0x14F] = (u32)Key::End;
        win->keycodes[0x01C] = (u32)Key::Enter;
        win->keycodes[0x001] = (u32)Key::Escape;
        win->keycodes[0x147] = (u32)Key::Home;
        win->keycodes[0x152] = (u32)Key::Insert;
        win->keycodes[0x15D] = (u32)Key::Menu;
        win->keycodes[0x151] = (u32)Key::PageDown;
        win->keycodes[0x149] = (u32)Key::PageUp;
        win->keycodes[0x045] = (u32)Key::Pause;
        win->keycodes[0x039] = (u32)Key::Space;
        win->keycodes[0x00F] = (u32)Key::Tab;
        win->keycodes[0x03A] = (u32)Key::CapsLock;
        win->keycodes[0x145] = (u32)Key::NumLock;
        win->keycodes[0x046] = (u32)Key::ScrollLock;
        win->keycodes[0x03B] = (u32)Key::F1;
        win->keycodes[0x03C] = (u32)Key::F2;
        win->keycodes[0x03D] = (u32)Key::F3;
        win->keycodes[0x03E] = (u32)Key::F4;
        win->keycodes[0x03F] = (u32)Key::F5;
        win->keycodes[0x040] = (u32)Key::F6;
        win->keycodes[0x041] = (u32)Key::F7;
        win->keycodes[0x042] = (u32)Key::F8;
        win->keycodes[0x043] = (u32)Key::F9;
        win->keycodes[0x044] = (u32)Key::F10;
        win->keycodes[0x057] = (u32)Key::F11;
        win->keycodes[0x058] = (u32)Key::F12;

        win->keycodes[0x038] = (u32)Key::LeftAlt;
        win->keycodes[0x01D] = (u32)Key::LeftControl;
        win->keycodes[0x02A] = (u32)Key::LeftShift;
        win->keycodes[0x15B] = (u32)Key::LeftSuper;
        win->keycodes[0x137] = (u32)Key::PrintScreen;
        win->keycodes[0x138] = (u32)Key::RightAlt;
        win->keycodes[0x11D] = (u32)Key::RightControl;
        win->keycodes[0x036] = (u32)Key::RightShift;
        win->keycodes[0x15C] = (u32)Key::RightSuper;
        win->keycodes[0x150] = (u32)Key::Down;
        win->keycodes[0x14B] = (u32)Key::Left;
        win->keycodes[0x14D] = (u32)Key::Right;
        win->keycodes[0x148] = (u32)Key::Up;

        win->keycodes[0x052] = (u32)Key::P0;
        win->keycodes[0x04F] = (u32)Key::P1;
        win->keycodes[0x050] = (u32)Key::P2;
        win->keycodes[0x051] = (u32)Key::P3;
        win->keycodes[0x04B] = (u32)Key::P4;
        win->keycodes[0x04C] = (u32)Key::P5;
        win->keycodes[0x04D] = (u32)Key::P6;
        win->keycodes[0x047] = (u32)Key::P7;
        win->keycodes[0x048] = (u32)Key::P8;
        win->keycodes[0x049] = (u32)Key::P9;
        win->keycodes[0x04E] = (u32)Key::PAdd;
        win->keycodes[0x053] = (u32)Key::PDecimal;
        win->keycodes[0x135] = (u32)Key::PDivide;
        win->keycodes[0x11C] = (u32)Key::PEnter;
        win->keycodes[0x059] = (u32)Key::PEqual;
        win->keycodes[0x037] = (u32)Key::PMultiply;
        win->keycodes[0x04A] = (u32)Key::PSubtract;
    }

    static void
    processKey(Window* window, Key key, i32 scancode, Action action)
    {
        u32 k = (u32)key;
        PASSERT_MSG(k >= 0 && key < Key::Max, "Invalid Key");
        PASSERT_MSG(action == Action::Release || action == Action::Press, "Invalid action");

        WindowHandle* win = window->getHandle();

        b8 repeated = false;
        if (action == Action::Release && win->keys[k] == (u32)Action::Release) {
            return;
        }

        if (action == Action::Press && win->keys[k] == (u32)Action::Press) {
            repeated = true;
        }

        if (action == Action::Press && win->keys[k] == (u32)Action::Release) {
            win->keys[k] = (u32)Action::Press;
        }
        else {
            win->keys[k] = (u32)action;
        }

        if (repeated) {
            action = Action::Repeat;
        }

        if (s_Callbacks.key) {
            s_Callbacks.key(window, key, scancode, action);
        }
    }

    static void
    processButton(Window* window, Button button, Action action)
    {
        u32 b = (u32)button;
        PASSERT_MSG(b >= 0 && button < Button::Max, "Invalid Key");
        PASSERT_MSG(action == Action::Release || action == Action::Press, "Invalid action");

        WindowHandle* win = window->getHandle();

        if (action == Action::Press && win->buttons[b] == (u32)Action::Release) {
            win->buttons[b] = (u32)Action::Press;
        }
        else {
            win->buttons[b] = (u32)action;
        }

        if (s_Callbacks.button) {
            s_Callbacks.button(window, button, action);
        }
    }

    static void
    processMouseMoved(Window* window, i32 x, i32 y)
    {
        WindowHandle* win = window->getHandle();
        win->mousePos[0] = x;
        win->mousePos[1] = y;

        if (s_Callbacks.mouseMoved) {
            s_Callbacks.mouseMoved(window, x, y);
        }
    }

    static void
    processFocus(Window* window, b8 focused)
    {
        WindowHandle* win = window->getHandle();

        win->isFocused = focused;
        if (s_Callbacks.windowFocused) {
            s_Callbacks.windowFocused(window, focused);
        }

        if (focused == false) {
            // process keys
            for (u32 key = 0; key <= (u32)Key::Max; key++) {
                if (win->keys[key] == (u32)Action::Press) {
                    const i32 scancode = win->scancodes[key];
                    processKey(window, (Key)key, scancode, Action::Release);
                }
            }

            // proces mouse buttons
            for (u32 button = 0; button <= (u32)Button::Max; button++) {
                if (win->buttons[button] == (u32)Action::Press) {
                    processButton(window, (Button)button, Action::Release);
                }
            }
        }
    }

    static void
    centerWindow(WindowHandle* win, u32 width, u32 height)
    {
        MONITORINFO monitor_info;
        monitor_info.cbSize = sizeof(MONITORINFO);
        GetMonitorInfo(MonitorFromWindow(win->hwnd, MONITOR_DEFAULTTONEAREST), &monitor_info);
        u32 max_hwidth = monitor_info.rcMonitor.right;
        u32 max_hheight = monitor_info.rcMonitor.bottom;

        i32 x = (max_hwidth - width) / 2;
        i32 y = (max_hheight - height) / 2;
        win->posX = x;
        win->posY = y;
        SetWindowPos(win->hwnd, 0, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_SHOWWINDOW);
    }

    b8
    Window::init(const str& title, u32 width, u32 height)
    {
        u32 style = WS_OVERLAPPEDWINDOW;
        u32 ex_style = WS_EX_APPWINDOW;

        RECT rect = { 0, 0, 0, 0 };
        rect.right = width;
        rect.bottom = height;
        AdjustWindowRectEx(&rect, style, 0, ex_style);

        wstr wstr = Utils::toWstring(title);
        m_Handle = new WindowHandle;

        m_Handle->hwnd = CreateWindowExW(
            ex_style,
            s_ClassName,
            wstr.c_str(),
            style,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            rect.right - rect.left,
            rect.bottom - rect.top,
            NULL,
            NULL,
            s_Instance,
            NULL
        );
        
        PASSERT_MSG(m_Handle->hwnd, "Window Creation Failed");
        centerWindow(m_Handle, width, height);
        UpdateWindow(m_Handle->hwnd);
        ShowWindow(m_Handle->hwnd, SW_NORMAL);
        SetPropW(m_Handle->hwnd, s_PropName, this);

        memset(m_Handle->keycodes, 0, sizeof(u16) * 512);
	    memset(m_Handle->scancodes, 0, sizeof(u16) * (u32)Key::Max + 1);
	    mapKeys(m_Handle);

        m_Handle->title = title;
        m_Handle->width = width;
        m_Handle->height = height;
        m_Handle->isFocused = true;
        return true;
    }

    void
    Window::destroy()
    {
        if (m_Handle->hwnd) {
            DestroyWindow(m_Handle->hwnd);
            delete m_Handle;
        }
    }

    b8
    Window::shouldClose()
    {
        return m_Handle->shouldClose;
    }

    void
    Window::pollEvents()
    {
        MSG msg;
        while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessageA(&msg);
        }

        // from GLFW
        HWND handle = GetActiveWindow();
        if (handle) {

            Window* window = (Window*)GetProp(handle, s_PropName);
            if (window) {
                int i;
                const int keys[4][2] = {
                    { VK_LSHIFT, (u32)Key::LeftShift },
                    { VK_RSHIFT, (u32)Key::RightShift },
                    { VK_LWIN, (u32)Key::LeftSuper },
                    { VK_RWIN, (u32)Key::RightSuper }
                };

                for (i = 0; i < 4; i++) {
                    const int vk = keys[i][0];
                    const int key = keys[i][1];
                    const int scancode = window->m_Handle->scancodes[key];

                    if ((GetKeyState(vk) & 0x8000)) { continue; }
                    if (window->m_Handle->keycodes[key] != (u32)Action::Press) { continue; }

                    processKey(window, (Key)key, scancode, Action::Release);
                }
            }
        }
    }

    void
    Window::hide()
    {
        m_Handle->isHidden = true;
        ShowWindow(m_Handle->hwnd, SW_HIDE);
    }

    void
    Window::show()
    {
        m_Handle->isHidden = false;
        ShowWindow(m_Handle->hwnd, SW_SHOW);
    }

    void
    Window::setSize(u32 width, u32 height)
    {
        PASSERT_MSG(width > 0 && height > 0, "invalid Parameter");

        u32 w = 0, h = 0;
        if (width < m_Handle->minWidth) {
            w = m_Handle->minWidth;
        }

        if (width > m_Handle->maxWidth) {
            w = m_Handle->maxWidth;
        }
        if (height < m_Handle->minHeight) {
            w = m_Handle->minHeight;
        }

        if (height > m_Handle->maxHeight) {
            w = m_Handle->maxHeight;
        }

        RECT rect = { 0, 0, 0, 0 };
        rect.right = w;
        rect.bottom = h;
        AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, 0, WS_EX_OVERLAPPEDWINDOW);

        m_Handle->width = w;
        m_Handle->height = h;
        SetWindowPos(m_Handle->hwnd, HWND_TOP,
            0, 0, rect.right - rect.left, rect.bottom - rect.top,
            SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOMOVE | SWP_NOZORDER);
    }

    void
    Window::setPos(i32 x, i32 y)
    {
        RECT rect = { 0, 0, 0, 0 };
        rect.left = x;
        rect.right = x;
        rect.top = y;
        rect.bottom = y;
        AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, 0, WS_EX_OVERLAPPEDWINDOW);

        m_Handle->posX = x;
        m_Handle->posY = y;
        SetWindowPos(m_Handle->hwnd, NULL, rect.left, rect.top, 0, 0,
            SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOSIZE);
    }

    void
    Window::setTitle(const str& title)
    {
        m_Handle->title = title;
        wstr wstr = Utils::toWstring(title);
        SetWindowText(m_Handle->hwnd, wstr.c_str());
    }

    void
    Window::setMinSize(u32 width, u32 height)
    {
        m_Handle->minWidth = width;
        m_Handle->minHeight = height;
    }

    void
    Window::setMaxSize(u32 width, u32 height)
    {
        m_Handle->maxWidth = width;
        m_Handle->maxHeight = height;
    }

    u32
    Window::getWidth() const
    {
        return m_Handle->width;
    }

    u32
    Window::getHeight() const
    {
        return m_Handle->height;
    }

    void
    Window::getMinSize(u32* width, u32* height)
    {
        *width = m_Handle->minWidth;
        *height = m_Handle->minHeight;
    }

    void
    Window::getMaxSize(u32* width, u32* height)
    {
        *width = m_Handle->maxWidth;
        *height = m_Handle->maxHeight;
    }

    i32
    Window::getPosX() const
    {
        return m_Handle->posX;
    }

    i32
    Window::getPosY() const
    {
        return m_Handle->posY;
    }

    const str&
    Window::getTitle() const
    {
        return m_Handle->title;
    }

    b8
    Window::getKeyState(Key key) const
    {
        u32 k = (u32)key;
        PASSERT_MSG(k >= 0, "Invalid key");
        PASSERT_MSG(key < Key::Max, "Invalid key");
        return m_Handle->keys[k] == (u32)Action::Press;
    }

    b8
    Window::getButtonState(Button button) const
    {
        u32 b = (u32)button;
        PASSERT_MSG(b >= 0, "Invalid button");
        PASSERT_MSG(button < Button::Max, "Invalid button");
        return m_Handle->buttons[b] == (u32)Action::Press;
    }

    b8
    Window::isHidden() const
    {
        return m_Handle->isHidden;
    }

    b8
    Window::isMaximized() const
    {
        GetWindowPlacement(m_Handle->hwnd, &s_WndPlacement);
        if (s_WndPlacement.showCmd == SW_SHOWMAXIMIZED) {
            return true;
        }
        return false;
    }

    WindowHandle*
    Window::getHandle()
    {
        return m_Handle;
    }

    void
    Window::setCloseCallback(WindowCloseFunc func)
    {
        s_Callbacks.close = func;
    }

    void
    Window::setKeyCallback(WindowKeyFunc func)
    {
        s_Callbacks.key = func;
    }

    void
    Window::setButtonCallback(WindowButtonFunc func)
    {
        s_Callbacks.button = func;
    }

    void
    Window::setMouseMovedCallback(WindowMouseMovedFunc func)
    {
        s_Callbacks.mouseMoved = func;
    }

    void
    Window::setMouseScrolledCallback(WindowMouseScrolledFunc func)
    {
        s_Callbacks.mouseScrolled = func;
    }

    void
    Window::setMovedCallback(WindowMovedFunc func)
    {
        s_Callbacks.windowMoved = func;
    }

    void
    Window::setResizeCallback(WindowResizeFunc func)
    {
        s_Callbacks.windowResize = func;
    }

    void
    Window::setFocusedCallback(WindowFocusedFunc func)
    {
        s_Callbacks.windowFocused = func;
    }

    void 
    Window::resetCallbacks()
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
    
} // namespace prime

LRESULT CALLBACK
primeWin32Proc(HWND hwnd, u32 msg, WPARAM w_param, LPARAM l_param)
{
    using namespace prime;

    Window* window = (Window*)GetPropW(hwnd, s_PropName);

	if (!window) {
		// no window created
		return DefWindowProcW(hwnd, msg, w_param, l_param);
	}

	switch (msg) {

        case WM_CLOSE: {
            WindowHandle* handle = window->getHandle();
            handle->shouldClose = true;
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
            WindowHandle* handle = window->getHandle();
            u32 key;
            Action action;
            i32 scancode;

            // from GLFW
            action = (HIWORD(l_param) & KF_UP) ? Action::Release : Action::Press;
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

            key = handle->keycodes[scancode];

            // The Ctrl keys require special handling
            if (w_param == VK_CONTROL)
            {
                if (HIWORD(l_param) & KF_EXTENDED)
                {
                    // Right side keys have the extended key bit set
                    key = (u32)Key::RightControl;
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
                    key = (u32)Key::LeftControl;
                }
            }
            else if (w_param == VK_PROCESSKEY)
            {
                // IME notifies that keys have been filtered by setting the
                // virtual key-code to VK_PROCESSKEY
                break;
            }

            if (action == Action::Release && w_param == VK_SHIFT)
            {
                // HACK: Release both Shift keys on Shift up event, as when both
                //       are pressed the first release does not emit any event
                // NOTE: The other half of this is in _glfwPollEventsWin32
                processKey(window, Key::LeftShift, scancode, action);
                processKey(window, Key::RightShift, scancode, action);
            }
            else if (w_param == VK_SNAPSHOT)
            {
                // HACK: Key down is not reported for the Print Screen key
                processKey(window, (Key)key, scancode, Action::Press);
                processKey(window, (Key)key, scancode, Action::Release);
            }
            else {
                processKey(window, (Key)key, scancode, action);
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

            Action action;
            Button button;

            if (msg == WM_LBUTTONDOWN || msg == WM_LBUTTONUP) {
                button = Button::Left;
            }

            else if (msg == WM_RBUTTONDOWN || msg == WM_RBUTTONUP) {
                button = Button::Right;
            }

            else if (msg == WM_MBUTTONDOWN || msg == WM_MBUTTONUP) {
                button = Button::Middle;
            }

            if (msg == WM_LBUTTONDOWN || msg == WM_RBUTTONDOWN ||
                msg == WM_MBUTTONDOWN || msg == WM_XBUTTONDOWN) {
                action = Action::Press;
            }
            else {
                action = Action::Release;
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
            WindowHandle* handle = window->getHandle();
            const int x = GET_X_LPARAM(l_param);
            const int y = GET_Y_LPARAM(l_param);

            if (handle->isFocused) { processMouseMoved(window, x, y); }

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
            WindowHandle* handle = window->getHandle();
            i32 x = GET_X_LPARAM(l_param);
            i32 y = GET_Y_LPARAM(l_param);
            handle->posX = x;
            handle->posY = y;

            if (s_Callbacks.windowMoved) {
                s_Callbacks.windowMoved(window, x, y);
            }

            return 0;
            break;
        }

        case WM_SIZE: {
            WindowHandle* handle = window->getHandle();
            const u32 width = (u32)LOWORD(l_param);
            const u32 height = (u32)HIWORD(l_param);

            if (width != handle->width || height != handle->height) {
                handle->width = width;
                handle->height = height;

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
            WindowHandle* handle = window->getHandle();
            MINMAXINFO* mmi = (MINMAXINFO*)l_param;
            if (handle->minWidth > 0) {
                mmi->ptMinTrackSize.x = handle->minWidth;
            }
            if (handle->maxWidth > 0) {
                mmi->ptMaxTrackSize.x = handle->maxWidth;
            }

            if (handle->minHeight > 0) {
                mmi->ptMinTrackSize.y = handle->minHeight;
            }
            if (handle->maxHeight > 0) {
                mmi->ptMaxTrackSize.y = handle->maxHeight;
            }
            return 0;
            break;
        }

    }

    return DefWindowProcW(hwnd, msg, w_param, l_param);
}

#endif // PPLATFORM_WINDOWS
