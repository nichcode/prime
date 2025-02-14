
#pragma once

#include "prime_defines.h"

using primeWindowCloseFunc = void(*)(primeWindow* window);
using primeWindowKeyFunc = void(*)(primeWindow* window, u16 key, i32 scancode, u8 action);
using primeWindowButtonFunc = void(*)(primeWindow* window, u16 button, u8 action);
using primeWindowMouseMovedFunc = void(*)(primeWindow* window, i32 x, i32 y);
using primeWindowMouseScrolledFunc = void(*)(primeWindow* window, f32 x_offset, f32 y_offset);
using primeWindowMovedFunc = void(*)(primeWindow* window, i32 x, i32 y);
using primeWindowResizeFunc = void(*)(primeWindow* window, u32 width, u32 height);
using primeWindowFocusedFunc = void(*)(primeWindow* window, b8 focused);

PAPI primeWindow*
primeWindowCreate(const char* title, u32 width, u32 height);

PAPI void
primeWindowDestroy(primeWindow* window);

PAPI b8
primeWindowShouldClose(primeWindow* window);

PAPI void
primeWindowPollEvents();

PAPI void
primeWindowHide(primeWindow* window);

PAPI void
primeWindowShow(primeWindow* window);

PAPI void
primeWindowSetSize(primeWindow* window, u32 width, u32 height);

PAPI void
primeWindowSetPos(primeWindow* window, i32 x, i32 y);

PAPI void
primeWindowSetTitle(primeWindow* window, const char* title);

PAPI void
primeWindowSetMinSize(primeWindow* window, u32 width, u32 height);

PAPI void
primeWindowSetMaxSize(primeWindow* window, u32 width, u32 height);

PAPI void
primeWindowSetUserData(primeWindow* window, void* data);

PAPI void
primeWindowSetCloseCallback(primeWindowCloseFunc func);

PAPI void
primeWindowSetKeyCallback(primeWindowKeyFunc func);

PAPI void
primeWindowSetButtonCallback(primeWindowButtonFunc func);

PAPI void
primeWindowSetMouseMovedCallback(primeWindowMouseMovedFunc func);

PAPI void
primeWindowSetMouseScrolledCallback(primeWindowMouseScrolledFunc func);

PAPI void
primeWindowSetMovedCallback(primeWindowMovedFunc func);

PAPI void
primeWindowSetResizeCallback(primeWindowResizeFunc func);

PAPI void
primeWindowSetFocusedCallback(primeWindowFocusedFunc func);

PAPI void
primeWindowResetCallbacks();

PAPI const u32
primeWindowGetWidth(primeWindow* window);

PAPI const u32
primeWindowGetHeight(primeWindow* window);

PAPI void
primeWindowGetMinSize(primeWindow* window, u32* width, u32* height);

PAPI void
primeWindowGetMaxSize(primeWindow* window, u32* width, u32* height);

PAPI const i32
primeWindowGetPosX(primeWindow* window);

PAPI const i32
primeWindowGetPosY(primeWindow* window);

PAPI const char*
primeWindowGetTitle(primeWindow* window);

PAPI void*
primeWindowGetUserData(primeWindow* window);

PAPI b8
primeWindowGetKeyState(primeWindow* window, u16 key);

PAPI b8
primeWindowGetButtonState(primeWindow* window, u16 button);

PAPI const b8
primeWindowIsHidden(primeWindow* window);

PAPI const b8
primeWindowIsMaximized(primeWindow* window);

PAPI const b8
primeWindowHasContext(primeWindow* window);



















