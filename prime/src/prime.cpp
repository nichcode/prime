
#include "prime/prime.h"

PRIME_API void
prime_WindowCallbacksReset()
{
	prime_WindowSetCloseCallback(nullptr);
	prime_WindowSetKeyCallback(nullptr);
	prime_WindowSetButtonCallback(nullptr);
	prime_WindowSetMouseMovedCallback(nullptr);
	prime_WindowSetMouseScrolledCallback(nullptr);
	prime_WindowSetPosCallback(nullptr);
	prime_WindowSetSizeCallback(nullptr);
	prime_WindowSetFocusCallback(nullptr);
}