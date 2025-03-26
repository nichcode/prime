
#pragma once

#include "prime/maths.h"
#include "prime/input.h"

using primeWindowFlag = u32;
using primeCloseCallback = void(*)(primeWindow* window);
using primeKeyCallback = void(*)(primeWindow* window, u32 key, i32 scancode, u32 action);
using primeButtonCallback = void(*)(primeWindow* window, u32 button, u32 action);
using primeMouseMovedCallback = void(*)(primeWindow* window, i32 x, i32 y);
using primeMouseScrolledCallback = void(*)(primeWindow* window, f32 offsetX, f32 offsetY);
using primeMovedCallback = void(*)(primeWindow* window, i32 x, i32 y);
using primeResizedCallback = void(*)(primeWindow* window, u32 width, u32 height);
using primeFocusedCallback = void(*)(primeWindow* window, b8 focused);

enum primeWindowFlags_
{
    primeWindowFlags_None = 0,
    primeWindowFlags_Center = PRIME_BIT(0)
};

struct primeWindowDesc
{
    primeVec2u size = primeCreateVec2u(640, 480);
    primeVec2i pos;
    const char* title = "prime window";
    primeWindowFlag flag = primeWindowFlags_None;
};

PRIME_API primeWindow* primeCreateWindow(primeWindowDesc desc);
PRIME_API void primeDestroyWindow(primeWindow* window);

PRIME_API void primePullEvents();
PRIME_API void primeHideWindow(primeWindow* window);
PRIME_API void primeShowWindow(primeWindow* window);
PRIME_API void primeResetCallbacks();

PRIME_API void primeSetWindowPos(primeWindow* window, primeVec2i pos);
PRIME_API void primeSetWindowSize(primeWindow* window, primeVec2u size);
PRIME_API void primeSetWindowTitle(primeWindow* window, const char* title);

PRIME_API void primeSetCloseCallback(primeCloseCallback callback);
PRIME_API void primeSetKeyCallback(primeKeyCallback callback);
PRIME_API void primeSetButtonCallback(primeButtonCallback callback);
PRIME_API void primeSetMouseMovedCallback(primeMouseMovedCallback callback);
PRIME_API void primeSetMouseScrolledCallback(primeMouseScrolledCallback callback);
PRIME_API void primeSetMovedCallback(primeMovedCallback callback);
PRIME_API void primeSetResizedCallback(primeResizedCallback callback);
PRIME_API void primeSetFocusedCallback(primeFocusedCallback callback);

PRIME_API b8 primeWindowShouldClose(primeWindow* window);
PRIME_API const void* primeGetWindowHandle(primeWindow* window);
PRIME_API const primeVec2i* primeGetWindowPos(primeWindow* window);
PRIME_API const primeVec2u* primeGetWindowSize(primeWindow* window);
PRIME_API const char* primeGetWindowTitle(primeWindow* window);

PRIME_API b8 primeGetKeyState(primeWindow* window, u32 key);
PRIME_API b8 primeGetbuttonState(primeWindow* window, u32 button);
