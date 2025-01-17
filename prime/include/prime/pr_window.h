#pragma once

#include "pr_defines.h"

struct PrWindow;
struct PrString;

using PrWindowCloseFunc = void(*)(PrWindow* window);
using PrWindowKeyFunc = void(*)(PrWindow* window, u16 key, i32 scancode, u8 action);
using PrWindowButtonFunc = void(*)(PrWindow* window, u16 button, u8 action);
using PrWindowMouseMovedFunc = void(*)(PrWindow* window, i32 x, i32 y);
using PrWindowMouseScrolledFunc = void(*)(PrWindow* window, f32 x_offset, f32 y_offset);
using PrWindowPosFunc = void(*)(PrWindow* window, i32 x, i32 y);
using PrWindowSizeFunc = void(*)(PrWindow* window, u32 width, u32 height);
using PrWindowFocusFunc = void(*)(PrWindow* window, b8 focused);

PR_API PrWindow*
prWindowCreate(const char* title, u32 width, u32 height);

PR_API void
prWindowDestroy(PrWindow* window);

PR_API b8
prWindowShouldClose(PrWindow* window);

PR_API void
prWindowPollEvents();

PR_API void 
prWindowSetCloseCallback(PrWindowCloseFunc func);

PR_API void
prWindowSetKeyCallback(PrWindowKeyFunc func);

PR_API void
prWindowSetButtonCallback(PrWindowButtonFunc func);

PR_API void
prWindowSetMouseMovedCallback(PrWindowMouseMovedFunc func);

PR_API void
prWindowSetMouseScrolledCallback(PrWindowMouseScrolledFunc func);

PR_API void
prWindowSetPosCallback(PrWindowPosFunc func);

PR_API void
prWindowSetSizeCallback(PrWindowSizeFunc func);

PR_API void
prWindowSetFocusCallback(PrWindowFocusFunc func);

PR_API void
prWindowHide(PrWindow* window);

PR_API void
prWindowShow(PrWindow* window);

PR_API void
prWindowSetSize(PrWindow* window, u32 width, u32 height);

PR_API void
prWindowSetPos(PrWindow* window, i32 x, i32 y);

PR_API void
prWindowSetTitle(PrWindow* window, const char* title);

PR_API void
prWindowSetMinSize(PrWindow* window, u32 width, u32 height);

PR_API void
prWindowSetMaxSize(PrWindow* window, u32 width, u32 height);

PR_API void
prWindowSetUserData(PrWindow* window, void* data);

PR_API const u32 
prWindowGetWidth(PrWindow* window);

PR_API const u32
prWindowGetHeight(PrWindow* window);

PR_API const u32
prWindowGetMinWidth(PrWindow* window);

PR_API const u32
prWindowGetMinHeight(PrWindow* window);

PR_API const u32
prWindowGetMaxWidth(PrWindow* window);

PR_API const u32
prWindowGetMaxHeight(PrWindow* window);

PR_API const i32
prWindowGetPosX(PrWindow* window);

PR_API const i32
prWindowGetPosY(PrWindow* window);

PR_API PrString*
prWindowGetTitle(PrWindow* window);

PR_API void*
prWindowGetUserData(PrWindow* window);

PR_API b8 
prWindowGetKeyState(PrWindow* window, u16 key);

PR_API b8
prWindowGetButtonState(PrWindow* window, u16 button);

PR_API PrString*
prWindowGetKeyName(PrWindow* window, u16 key);

PR_API PrString*
prWindowGetButtonName(PrWindow* window, u16 button);

PR_API PrString*
prWindowGetActionName(PrWindow* window, u8 action);

PR_API const b8
prWindowHidden(PrWindow* window);

PR_API const b8
prWindowMaximized(PrWindow* window);