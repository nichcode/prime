
#pragma once

#include "API.h"

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
