
#include "prime/prime.h"

PRIME_API void
prime_UnSetWindowCallbacks()
{
	prime_SetWindowCloseCallback(nullptr);
	prime_SetWindowKeyCallback(nullptr);
	prime_SetWindowButtonCallback(nullptr);
	prime_SetWindowMouseMovedCallback(nullptr);
	prime_SetWindowMouseScrolledCallback(nullptr);
	prime_SetWindowPosCallback(nullptr);
	prime_SetWindowSizeCallback(nullptr);
	prime_SetWindowFocusCallback(nullptr);
}