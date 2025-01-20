#pragma once

#include "prime_defines.h"

using prime_WindowCloseFunc = void(*)(prime_Window* window);
using prime_WindowKeyFunc = void(*)(prime_Window* window, u16 key, i32 scancode, u8 action);
using prime_WindowButtonFunc = void(*)(prime_Window* window, u16 button, u8 action);
using prime_WindowMouseMovedFunc = void(*)(prime_Window* window, i32 x, i32 y);
using prime_WindowMouseScrolledFunc = void(*)(prime_Window* window, f32 x_offset, f32 y_offset);
using prime_WindowPosFunc = void(*)(prime_Window* window, i32 x, i32 y);
using prime_WindowSizeFunc = void(*)(prime_Window* window, u32 width, u32 height);
using prime_WindowFocusFunc = void(*)(prime_Window* window, b8 focused);

PRIME_API prime_Window*
prime_WindowCreate(const char* title, u32 width, u32 height);

PRIME_API void
prime_WindowDestroy(prime_Window* window);

PRIME_API b8
prime_WindowShouldClose(prime_Window* window);

PRIME_API void
prime_WindowPollEvents();

PRIME_API void 
prime_WindowSetCloseCallback(prime_WindowCloseFunc func);

PRIME_API void
prime_WindowSetKeyCallback(prime_WindowKeyFunc func);

PRIME_API void
prime_WindowSetButtonCallback(prime_WindowButtonFunc func);

PRIME_API void
prime_WindowSetMouseMovedCallback(prime_WindowMouseMovedFunc func);

PRIME_API void
prime_WindowSetMouseScrolledCallback(prime_WindowMouseScrolledFunc func);

PRIME_API void
prime_WindowSetPosCallback(prime_WindowPosFunc func);

PRIME_API void
prime_WindowSetSizeCallback(prime_WindowSizeFunc func);

PRIME_API void
prime_WindowSetFocusCallback(prime_WindowFocusFunc func);

PRIME_API void
prime_WindowHide(prime_Window* window);

PRIME_API void
prime_WindowShow(prime_Window* window);

PRIME_API void
prime_WindowSetSize(prime_Window* window, u32 width, u32 height);

PRIME_API void
prime_WindowSetPos(prime_Window* window, i32 x, i32 y);

PRIME_API void
prime_WindowSetTitle(prime_Window* window, const char* title);

PRIME_API void
prime_WindowSetMinSize(prime_Window* window, u32 width, u32 height);

PRIME_API void
prime_WindowSetMaxSize(prime_Window* window, u32 width, u32 height);

PRIME_API void
prime_WindowSetUserData(prime_Window* window, void* data);

PRIME_API const u32 
prime_WindowGetWidth(prime_Window* window);

PRIME_API const u32
prime_WindowGetHeight(prime_Window* window);

PRIME_API const u32
prime_WindowGetMinWidth(prime_Window* window);

PRIME_API const u32
prime_WindowGetMinHeight(prime_Window* window);

PRIME_API const u32
prime_WindowGetMaxWidth(prime_Window* window);

PRIME_API const u32
prime_WindowGetMaxHeight(prime_Window* window);

PRIME_API const i32
prime_WindowGetPosX(prime_Window* window);

PRIME_API const i32
prime_WindowGetPosY(prime_Window* window);

PRIME_API prime_String*
prime_WindowGetTitle(prime_Window* window);

PRIME_API void*
prime_WindowGetUserData(prime_Window* window);

PRIME_API b8 
prime_WindowGetKeyState(prime_Window* window, u16 key);

PRIME_API b8
prime_WindowGetButtonState(prime_Window* window, u16 button);

PRIME_API prime_String*
prime_WindowGetKeyName(prime_Window* window, u16 key);

PRIME_API prime_String*
prime_WindowGetButtonName(prime_Window* window, u16 button);

PRIME_API prime_String*
prime_WindowGetActionName(prime_Window* window, u8 action);

PRIME_API const b8
prime_WindowHidden(prime_Window* window);

PRIME_API const b8
prime_WindowMaximized(prime_Window* window);