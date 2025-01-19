
#include "prime/prime.h"

static void 
onWindowClose(prime_Window* window)
{
	prime_String* msg = prime_FormatString("%s is closed",
		prime_GetCstr(prime_GetWindowTitle(window)));

	prime_LogString(msg);
	prime_DestroyString(msg);
}

static void
onWindowResize(prime_Window* window, u32 width, u32 height)
{
	prime_String* msg = prime_FormatString("%s - size(%i, %i)",
		prime_GetCstr(prime_GetWindowTitle(window)), width, height);

	prime_LogString(msg);
	prime_DestroyString(msg);
}

static void 
onWindowKey(prime_Window* window, u16 key, i32 scancode, u8 action)
{
	prime_String* msg = prime_FormatString("%s - %s, %s)",
		prime_GetCstr(prime_GetWindowTitle(window)),
		prime_GetCstr(prime_GetWindowKeyName(window, key)),
		prime_GetCstr(prime_GetWindowActionName(window, action)));

	prime_LogString(msg);
	prime_DestroyString(msg);
}

static void 
onWindowButton(prime_Window* window, u16 button, u8 action)
{
	prime_String* msg = prime_FormatString("%s - %s, %s)",
		prime_GetCstr(prime_GetWindowTitle(window)),
		prime_GetCstr(prime_GetWindowButtonName(window, button)),
		prime_GetCstr(prime_GetWindowActionName(window, action)));

	prime_LogString(msg);
	prime_DestroyString(msg);
}

static void 
onWindowMouseMoved(prime_Window* window, i32 x, i32 y)
{
	prime_String* msg = prime_FormatString("%s - mousePos(%i, %i))",
		prime_GetCstr(prime_GetWindowTitle(window)), x, y);

	prime_LogString(msg);
	prime_DestroyString(msg);
}

static void 
onWindowMouseScrolled(prime_Window* window, f32 x_offset, f32 y_offset)
{
	prime_String* msg = prime_FormatString("%s - mouseScroll(%i, %i))",
		prime_GetCstr(prime_GetWindowTitle(window)), x_offset, y_offset);

	prime_LogString(msg);
	prime_DestroyString(msg);
}

static void
onWindowPos(prime_Window* window, i32 x, i32 y)
{
	prime_String* msg = prime_FormatString("%s - windowPos(%i, %i))",
		prime_GetCstr(prime_GetWindowTitle(window)), x, y);

	prime_LogString(msg);
	prime_DestroyString(msg);
}

static void 
onWindowFocused(prime_Window* window, b8 focused)
{
	if (focused) {
		prime_String* msg = prime_FormatString("%s is focused)",
			prime_GetCstr(prime_GetWindowTitle(window)));

		prime_LogString(msg);
		prime_DestroyString(msg);
	}
}

b8
windowTest()
{
	prime_LogInfo("");
	prime_LogInfo("Begin Window Test");

	prime_Window* window = prime_CreateWindow("Prime Window", 640, 480);

	// callbacks
	prime_SetWindowCloseCallback(onWindowClose);
	prime_SetWindowKeyCallback(onWindowKey);
	prime_SetWindowButtonCallback(onWindowButton);
	prime_SetWindowMouseMovedCallback(onWindowMouseMoved);
	prime_SetWindowMouseScrolledCallback(onWindowMouseScrolled);
	prime_SetWindowPosCallback(onWindowPos);
	prime_SetWindowSizeCallback(onWindowResize);
	prime_SetWindowFocusCallback(onWindowFocused);

	while (!prime_WindowShouldClose(window)) {
		prime_PollEvents();
	}

	prime_DestroyWindow(window);

	prime_LogInfo("End Window Test");
	prime_LogInfo("");

	return PRIME_PASSED;
}

b8
multiWindowTest()
{
	prime_LogInfo("");
	prime_LogInfo("Begin Multi Window Test");

	prime_Window* window1 = prime_CreateWindow("Prime Window 1", 640, 480);
	prime_Window* window2 = prime_CreateWindow("Prime Window 2", 640, 480);

	// callbacks
	prime_SetWindowCloseCallback(onWindowClose);
	prime_SetWindowKeyCallback(onWindowKey);
	prime_SetWindowButtonCallback(onWindowButton);
	prime_SetWindowMouseMovedCallback(onWindowMouseMoved);
	prime_SetWindowMouseScrolledCallback(onWindowMouseScrolled);
	prime_SetWindowPosCallback(onWindowPos);
	prime_SetWindowSizeCallback(onWindowResize);
	prime_SetWindowFocusCallback(onWindowFocused);

	while (!prime_WindowShouldClose(window1)) {
		prime_PollEvents();
	}

	prime_DestroyWindow(window1);
	prime_DestroyWindow(window2);

	prime_LogInfo("End Multi Window Test");
	prime_LogInfo("");

	return PRIME_PASSED;
}