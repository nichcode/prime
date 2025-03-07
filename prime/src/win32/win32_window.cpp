
#include "win32_API.h"
#include "prime/core/window.h"
#include "prime/core/logger.h"
#include "prime/core/fmt.h"
#include "prime/internal.h"

namespace prime::core {

    struct WindowHandle
    {
        HWND hwnd = nullptr;
        u32 width = 0, height = 0;
        str title = "";
        b8 shouldClose = false, isFocused = false;
        b8 isHidden = false;

        u32 keycodes[512] = {};
        u32 scancodes[KeyMax + 1] = {};

        u16 keys[KeyMax + 1] = {};
        u16 buttons[ButtonMax + 1] = {};

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

    static void mapKeys(WindowHandle* win)
    {
        win->keycodes[0x01E] = KeyA;
        win->keycodes[0x030] = KeyB;
        win->keycodes[0x02E] = KeyC;
        win->keycodes[0x020] = KeyD;
        win->keycodes[0x012] = KeyE;
        win->keycodes[0x021] = KeyF;
        win->keycodes[0x022] = KeyG;
        win->keycodes[0x023] = KeyH;
        win->keycodes[0x017] = KeyI;
        win->keycodes[0x024] = KeyJ;
        win->keycodes[0x025] = KeyK;
        win->keycodes[0x026] = KeyL;
        win->keycodes[0x032] = KeyM;
        win->keycodes[0x031] = KeyN;
        win->keycodes[0x018] = KeyO;
        win->keycodes[0x019] = KeyP;
        win->keycodes[0x010] = KeyQ;
        win->keycodes[0x013] = KeyR;
        win->keycodes[0x01F] = KeyS;
        win->keycodes[0x014] = KeyT;
        win->keycodes[0x016] = KeyU;
        win->keycodes[0x02F] = KeyV;
        win->keycodes[0x011] = KeyW;
        win->keycodes[0x02D] = KeyX;
        win->keycodes[0x015] = KeyY;
        win->keycodes[0x02C] = KeyZ;

        win->keycodes[0x00B] = Key0;
        win->keycodes[0x002] = Key1;
        win->keycodes[0x003] = Key2;
        win->keycodes[0x004] = Key3;
        win->keycodes[0x005] = Key4;
        win->keycodes[0x006] = Key5;
        win->keycodes[0x007] = Key6;
        win->keycodes[0x008] = Key7;
        win->keycodes[0x009] = Key8;
        win->keycodes[0x00A] = Key9;

        win->keycodes[0x028] = KeyApostrophe;
        win->keycodes[0x02B] = KeyBackslash;
        win->keycodes[0x033] = KeyComma;
        win->keycodes[0x00D] = KeyEqual;
        win->keycodes[0x029] = KeyGraveAccent;
        win->keycodes[0x01A] = KeyLeftBracket;
        win->keycodes[0x00C] = KeyMinus;
        win->keycodes[0x034] = KeyPeriod;
        win->keycodes[0x01B] = KeyRightBracket;
        win->keycodes[0x027] = KeySemiColon;
        win->keycodes[0x035] = KeySlash;

        win->keycodes[0x00E] = KeyBackspace;
        win->keycodes[0x153] = KeyDelete;
        win->keycodes[0x14F] = KeyEnd;
        win->keycodes[0x01C] = KeyEnter;
        win->keycodes[0x001] = KeyEscape;
        win->keycodes[0x147] = KeyHome;
        win->keycodes[0x152] = KeyInsert;
        win->keycodes[0x15D] = KeyMenu;
        win->keycodes[0x151] = KeyPageDown;
        win->keycodes[0x149] = KeyPageUp;
        win->keycodes[0x045] = KeyPause;
        win->keycodes[0x039] = KeySpace;
        win->keycodes[0x00F] = KeyTab;
        win->keycodes[0x03A] = KeyCapsLock;
        win->keycodes[0x145] = KeyNumLock;
        win->keycodes[0x046] = KeyScrollLock;
        win->keycodes[0x03B] = KeyF1;
        win->keycodes[0x03C] = KeyF2;
        win->keycodes[0x03D] = KeyF3;
        win->keycodes[0x03E] = KeyF4;
        win->keycodes[0x03F] = KeyF5;
        win->keycodes[0x040] = KeyF6;
        win->keycodes[0x041] = KeyF7;
        win->keycodes[0x042] = KeyF8;
        win->keycodes[0x043] = KeyF9;
        win->keycodes[0x044] = KeyF10;
        win->keycodes[0x057] = KeyF11;
        win->keycodes[0x058] = KeyF12;

        win->keycodes[0x038] = KeyLeftAlt;
        win->keycodes[0x01D] = KeyLeftControl;
        win->keycodes[0x02A] = KeyLeftShift;
        win->keycodes[0x15B] = KeyLeftSuper;
        win->keycodes[0x137] = KeyPrintScreen;
        win->keycodes[0x138] = KeyRightAlt;
        win->keycodes[0x11D] = KeyRightControl;
        win->keycodes[0x036] = KeyRightShift;
        win->keycodes[0x15C] = KeyRightSuper;
        win->keycodes[0x150] = KeyDown;
        win->keycodes[0x14B] = KeyLeft;
        win->keycodes[0x14D] = KeyRight;
        win->keycodes[0x148] = KeyUp;

        win->keycodes[0x052] = KeyP0;
        win->keycodes[0x04F] = KeyP1;
        win->keycodes[0x050] = KeyP2;
        win->keycodes[0x051] = KeyP3;
        win->keycodes[0x04B] = KeyP4;
        win->keycodes[0x04C] = KeyP5;
        win->keycodes[0x04D] = KeyP6;
        win->keycodes[0x047] = KeyP7;
        win->keycodes[0x048] = KeyP8;
        win->keycodes[0x049] = KeyP9;
        win->keycodes[0x04E] = KeyPAdd;
        win->keycodes[0x053] = KeyPDecimal;
        win->keycodes[0x135] = KeyPDivide;
        win->keycodes[0x11C] = KeyPEnter;
        win->keycodes[0x059] = KeyPEqual;
        win->keycodes[0x037] = KeyPMultiply;
        win->keycodes[0x04A] = KeyPSubtract;
    }

    static void processKey(Window* window, u32 key, i32 scancode, u8 action)
    {
        PRIME_ASSERT_MSG(key >= 0 && key < KeyMax, "Invalid Key");
        PRIME_ASSERT_MSG(action == ActionRelease || action == ActionPress, "Invalid action");

        WindowHandle* win = window->getHandle();

        b8 repeated = false;
        if (action == ActionRelease && win->keys[key] == ActionRelease) {
            return;
        }

        if (action == ActionPress && win->keys[key] == ActionPress) {
            repeated = true;
        }

        if (action == ActionPress && win->keys[key] == ActionRelease) {
            win->keys[key] = ActionPress;
        }
        else {
            win->keys[key] = action;
        }

        if (repeated) {
            action = ActionRepeat;
        }

        if (s_Callbacks.key) {
            s_Callbacks.key(window, key, scancode, action);
        }
    }

    static void processButton(Window* window, u16 button, u8 action)
    {
        PRIME_ASSERT_MSG(button >= 0 && button < ButtonMax, "Invalid Key");
        PRIME_ASSERT_MSG(action == ActionRelease || action == ActionPress, "Invalid action");

        WindowHandle* win = window->getHandle();

        if (action == ActionPress && win->buttons[button] == ActionRelease) {
            win->buttons[button] = ActionPress;
        }
        else {
            win->buttons[button] = action;
        }

        if (s_Callbacks.button) {
            s_Callbacks.button(window, button, action);
        }
    }

    static void processMouseMoved(Window* window, i32 x, i32 y)
    {
        WindowHandle* win = window->getHandle();
        win->mousePos[0] = x;
        win->mousePos[1] = y;

        if (s_Callbacks.mouseMoved) {
            s_Callbacks.mouseMoved(window, x, y);
        }
    }

    static void processFocus(Window* window, b8 focused)
    {
        WindowHandle* win = window->getHandle();

        win->isFocused = focused;
        if (s_Callbacks.windowFocused) {
            s_Callbacks.windowFocused(window, focused);
        }

        if (focused == false) {
            // process keys
            for (u32 key = 0; key <= KeyMax; key++) {
                if (win->keys[key] == ActionPress) {
                    const i32 scancode = win->scancodes[key];
                    processKey(window, key, scancode, ActionRelease);
                }
            }

            // proces mouse buttons
            for (u32 button = 0; button <= ButtonMax; button++) {
                if (win->buttons[button] == ActionPress) {
                    processButton(window, button, ActionRelease);
                }
            }
        }
    }

    static void centerWindow(WindowHandle* win, u32 width, u32 height)
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

    b8 Window::init(const str& title, u32 width, u32 height)
    {
        u32 style = WS_OVERLAPPEDWINDOW;
        u32 ex_style = WS_EX_APPWINDOW;

        RECT rect = { 0, 0, 0, 0 };
        rect.right = width;
        rect.bottom = height;
        AdjustWindowRectEx(&rect, style, 0, ex_style);

        wstr wstr = toWideString(title);
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
        
        PRIME_ASSERT_MSG(m_Handle->hwnd, "Window Creation Failed");
        centerWindow(m_Handle, width, height);
        UpdateWindow(m_Handle->hwnd);
        ShowWindow(m_Handle->hwnd, SW_NORMAL);
        SetPropW(m_Handle->hwnd, s_PropName, this);

        memset(m_Handle->keycodes, 0, sizeof(u32) * 512);
	    memset(m_Handle->scancodes, 0, sizeof(u32) * KeyMax + 1);
	    mapKeys(m_Handle);

        m_Handle->title = title;
        m_Handle->width = width;
        m_Handle->height = height;
        m_Handle->isFocused = true;
        return true;
    }

    void Window::destroy()
    {
        if (m_Handle->hwnd) {
            DestroyWindow(m_Handle->hwnd);
            delete m_Handle;
        }
    }

    b8 Window::shouldClose()
    {
        return m_Handle->shouldClose;
    }

    void Window::pollEvents()
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
                    { VK_LSHIFT, KeyLeftShift },
                    { VK_RSHIFT, KeyRightShift },
                    { VK_LWIN, KeyLeftSuper },
                    { VK_RWIN, KeyRightSuper }
                };

                for (i = 0; i < 4; i++) {
                    const int vk = keys[i][0];
                    const int key = keys[i][1];
                    const int scancode = window->m_Handle->scancodes[key];

                    if ((GetKeyState(vk) & 0x8000)) { continue; }
                    if (window->m_Handle->keycodes[key] != ActionPress) { continue; }

                    processKey(window, key, scancode, ActionRelease);
                }
            }
        }
    }

    void Window::hide()
    {
        m_Handle->isHidden = true;
        ShowWindow(m_Handle->hwnd, SW_HIDE);
    }

    void Window::show()
    {
        m_Handle->isHidden = false;
        ShowWindow(m_Handle->hwnd, SW_SHOW);
    }

    void Window::setSize(u32 width, u32 height)
    {
        PRIME_ASSERT_MSG(width > 0 && height > 0, "invalid Parameter");

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

    void Window::setPos(i32 x, i32 y)
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

    void Window::setTitle(const str& title)
    {
        m_Handle->title = title;
        wstr wstr = toWideString(title);
        SetWindowText(m_Handle->hwnd, wstr.c_str());
    }

    void Window::setMinSize(u32 width, u32 height)
    {
        m_Handle->minWidth = width;
        m_Handle->minHeight = height;
    }

    void Window::setMaxSize(u32 width, u32 height)
    {
        m_Handle->maxWidth = width;
        m_Handle->maxHeight = height;
    }

    u32 Window::getWidth() const
    {
        return m_Handle->width;
    }

    u32 Window::getHeight() const
    {
        return m_Handle->height;
    }

    void Window::getMinSize(u32* width, u32* height)
    {
        *width = m_Handle->minWidth;
        *height = m_Handle->minHeight;
    }

    void Window::getMaxSize(u32* width, u32* height)
    {
        *width = m_Handle->maxWidth;
        *height = m_Handle->maxHeight;
    }

    i32 Window::getPosX() const
    {
        return m_Handle->posX;
    }

    i32 Window::getPosY() const
    {
        return m_Handle->posY;
    }

    const str& Window::getTitle() const
    {
        return m_Handle->title;
    }

    b8 Window::getKeyState(Key key) const
    {
        PRIME_ASSERT_MSG(key >= 0, "Invalid key");
        PRIME_ASSERT_MSG(key < KeyMax, "Invalid key");
        return m_Handle->keys[key] == ActionPress;
    }

    b8 Window::getButtonState(Button button) const
    {
        PRIME_ASSERT_MSG(button >= 0, "Invalid button");
        PRIME_ASSERT_MSG(button < ButtonMax, "Invalid button");
        return m_Handle->buttons[button] == ActionPress;
    }

    b8 Window::isHidden() const
    {
        return m_Handle->isHidden;
    }

    b8 Window::isMaximized() const
    {
        GetWindowPlacement(m_Handle->hwnd, &s_WndPlacement);
        if (s_WndPlacement.showCmd == SW_SHOWMAXIMIZED) {
            return true;
        }
        return false;
    }

    WindowHandle* Window::getHandle()
    {
        return m_Handle;
    }

    WindowHandle* Window::getHandle() const
    {
        return m_Handle;
    }

    void Window::setCloseCallback(WindowCloseFunc func)
    {
        s_Callbacks.close = func;
    }

    void Window::setKeyCallback(WindowKeyFunc func)
    {
        s_Callbacks.key = func;
    }

    void Window::setButtonCallback(WindowButtonFunc func)
    {
        s_Callbacks.button = func;
    }

    void Window::setMouseMovedCallback(WindowMouseMovedFunc func)
    {
        s_Callbacks.mouseMoved = func;
    }

    void Window::setMouseScrolledCallback(WindowMouseScrolledFunc func)
    {
        s_Callbacks.mouseScrolled = func;
    }

    void Window::setMovedCallback(WindowMovedFunc func)
    {
        s_Callbacks.windowMoved = func;
    }

    void Window::setResizeCallback(WindowResizeFunc func)
    {
        s_Callbacks.windowResize = func;
    }

    void Window::setFocusedCallback(WindowFocusedFunc func)
    {
        s_Callbacks.windowFocused = func;
    }

    void Window::resetCallbacks()
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

} // namespace prime::core

namespace prime::internal {

    HWND getWin32WindowHandle(const core::Window& window)
    {
        return window.getHandle()->hwnd;
    }
    
} // namespace prime::internal

LRESULT CALLBACK
win32Proc(HWND hwnd, u32 msg, WPARAM w_param, LPARAM l_param)
{
    using namespace prime::core;

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
            u8 action;
            i32 scancode;

            // from GLFW
            action = (HIWORD(l_param) & KF_UP) ? prime::ActionRelease : prime::ActionPress;
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
                    key = prime::KeyRightControl;
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
                    key = prime::KeyLeftControl;
                }
            }
            else if (w_param == VK_PROCESSKEY)
            {
                // IME notifies that keys have been filtered by setting the
                // virtual key-code to VK_PROCESSKEY
                break;
            }

            if (action == prime::ActionRelease && w_param == VK_SHIFT)
            {
                // HACK: Release both Shift keys on Shift up event, as when both
                //       are pressed the first release does not emit any event
                // NOTE: The other half of this is in _glfwPollEventsWin32
                processKey(window, prime::KeyLeftShift, scancode, action);
                processKey(window, prime::KeyRightShift, scancode, action);
            }
            else if (w_param == VK_SNAPSHOT)
            {
                // HACK: Key down is not reported for the Print Screen key
                processKey(window, key, scancode, prime::ActionPress);
                processKey(window, key, scancode, prime::ActionRelease);
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

            u8 action;
            u16 button;

            if (msg == WM_LBUTTONDOWN || msg == WM_LBUTTONUP) {
                button = prime::ButtonLeft;
            }

            else if (msg == WM_RBUTTONDOWN || msg == WM_RBUTTONUP) {
                button = prime::ButtonRight;
            }

            else if (msg == WM_MBUTTONDOWN || msg == WM_MBUTTONUP) {
                button = prime::ButtonMiddle;
            }

            if (msg == WM_LBUTTONDOWN || msg == WM_RBUTTONDOWN ||
                msg == WM_MBUTTONDOWN || msg == WM_XBUTTONDOWN) {
                action = prime::ActionPress;
            }
            else {
                action = prime::ActionRelease;
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

