
#pragma once

#include "defines.h"

struct prWindow;

using prWindowCloseFunc = void(*)(prWindow* window);
using prWindowKeyFunc = void(*)(prWindow* window, u32 key, i32 scancode, u32 action);
using prWindowButtonFunc = void(*)(prWindow* window, u32 button, u32 action);
using prWindowMouseMovedFunc = void(*)(prWindow* window, i32 x, i32 y);
using prWindowMouseScrolledFunc = void(*)(prWindow* window, f32 offset_x, f32 offset_y);
using prWindowMovedFunc = void(*)(prWindow* window, i32 x, i32 y);
using prWindowResizeFunc = void(*)(prWindow* window, u32 width, u32 height);
using prWindowFocusedFunc = void(*)(prWindow* window, b8 focused);

enum prWindowFlags_
{
    prWindowFlags_Show = PR_BIT(0),
    prWindowFlags_Center = PR_BIT(1)
};

PR_API prWindow* prCreateWindow(const char* title, u32 width, u32 height, u32 flags);
PR_API void prDestroyWindow(prWindow* window);
PR_API void prPullEvents();
PR_API void prHideWindow(prWindow* window);
PR_API void prShowWindow(prWindow* window);

PR_API void prSetWindowTitle(prWindow* window, const char* title);
PR_API void prSetWindowSize(prWindow* window, u32 width, u32 height);
PR_API void prSetWindowPos(prWindow* window, i32 x, i32 y);

PR_API void prSetWindowCloseCallback(prWindowCloseFunc func);
PR_API void prSetWindowKeyCallback(prWindowKeyFunc func);
PR_API void prSetWindowButtonCallback(prWindowButtonFunc func);
PR_API void prSetWindowMouseMovedCallback(prWindowMouseMovedFunc func);

PR_API void prSetWindowMouseScrolledCallback(prWindowMouseScrolledFunc func);
PR_API void prSetWindowMovedCallback(prWindowMovedFunc func);
PR_API void prSetWindowResizedCallback(prWindowResizeFunc func);
PR_API void prSetWindowFocusedCallback(prWindowFocusedFunc func);
PR_API void prWindowResetCallbacks();

PR_API b8 prWindowShouldClose(prWindow* window);
PR_API b8 prGetKeyState(prWindow* window, u32 key);
PR_API b8 prGetButtonState(prWindow* window, u32 button);

PR_API const char* prGetWindowTitle(prWindow* window);
PR_API void* prGetWindowHandle(prWindow* window);
PR_API u32 prGetWindowWidth(prWindow* window);
PR_API u32 prGetWindowHeight(prWindow* window);
PR_API i32 prGetWindowPosX(prWindow* window);
PR_API i32 prGetWindowPosY(prWindow* window);