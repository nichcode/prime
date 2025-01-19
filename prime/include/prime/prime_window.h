#pragma once

#include "prime_defines.h"

struct prime_Window;
struct prime_String;

using prime_WindowCloseFunc = void(*)(prime_Window* window);
using prime_WindowKeyFunc = void(*)(prime_Window* window, u16 key, i32 scancode, u8 action);
using prime_WindowButtonFunc = void(*)(prime_Window* window, u16 button, u8 action);
using prime_WindowMouseMovedFunc = void(*)(prime_Window* window, i32 x, i32 y);
using prime_WindowMouseScrolledFunc = void(*)(prime_Window* window, f32 x_offset, f32 y_offset);
using prime_WindowPosFunc = void(*)(prime_Window* window, i32 x, i32 y);
using prime_WindowSizeFunc = void(*)(prime_Window* window, u32 width, u32 height);
using prime_WindowFocusFunc = void(*)(prime_Window* window, b8 focused);

PRIME_API prime_Window*
prime_CreateWindow(const char* title, u32 width, u32 height);

PRIME_API void
prime_DestroyWindow(prime_Window* window);

PRIME_API b8
prime_WindowShouldClose(prime_Window* window);

PRIME_API void
prime_PollEvents();

PRIME_API void 
prime_SetWindowCloseCallback(prime_WindowCloseFunc func);

PRIME_API void
prime_SetWindowKeyCallback(prime_WindowKeyFunc func);

PRIME_API void
prime_SetWindowButtonCallback(prime_WindowButtonFunc func);

PRIME_API void
prime_SetWindowMouseMovedCallback(prime_WindowMouseMovedFunc func);

PRIME_API void
prime_SetWindowMouseScrolledCallback(prime_WindowMouseScrolledFunc func);

PRIME_API void
prime_SetWindowPosCallback(prime_WindowPosFunc func);

PRIME_API void
prime_SetWindowSizeCallback(prime_WindowSizeFunc func);

PRIME_API void
prime_SetWindowFocusCallback(prime_WindowFocusFunc func);

PRIME_API void
prime_HideWindow(prime_Window* window);

PRIME_API void
prime_ShowWindow(prime_Window* window);

PRIME_API void
prime_SetWindowSize(prime_Window* window, u32 width, u32 height);

PRIME_API void
prime_SetWindowPos(prime_Window* window, i32 x, i32 y);

PRIME_API void
prime_SetWindowTitle(prime_Window* window, const char* title);

PRIME_API void
prime_SetWindowMinSize(prime_Window* window, u32 width, u32 height);

PRIME_API void
prime_SetWindowMaxSize(prime_Window* window, u32 width, u32 height);

PRIME_API void
prime_SetWindowUserData(prime_Window* window, void* data);

PRIME_API const u32 
prime_GetWindowWidth(prime_Window* window);

PRIME_API const u32
prime_GetWindowHeight(prime_Window* window);

PRIME_API const u32
prime_GetWindowMinWidth(prime_Window* window);

PRIME_API const u32
prime_GetWindowMinHeight(prime_Window* window);

PRIME_API const u32
prime_GetWindowMaxWidth(prime_Window* window);

PRIME_API const u32
prime_GetWindowMaxHeight(prime_Window* window);

PRIME_API const i32
prime_GetWindowPosX(prime_Window* window);

PRIME_API const i32
prime_GetWindowPosY(prime_Window* window);

PRIME_API prime_String*
prime_GetWindowTitle(prime_Window* window);

PRIME_API void*
prime_GetWindowUserData(prime_Window* window);

PRIME_API b8 
prime_GetWindowKeyState(prime_Window* window, u16 key);

PRIME_API b8
prime_GetWindowButtonState(prime_Window* window, u16 button);

PRIME_API prime_String*
prime_GetWindowKeyName(prime_Window* window, u16 key);

PRIME_API prime_String*
prime_GetWindowButtonName(prime_Window* window, u16 button);

PRIME_API prime_String*
prime_GetWindowActionName(prime_Window* window, u8 action);

PRIME_API const b8
prime_IsWindowHidden(prime_Window* window);

PRIME_API const b8
prime_IsWindowMaximized(prime_Window* window);