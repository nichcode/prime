
#include "tests.h"

static void 
onWindowClose(prime_Window* window)
{
	prime_String* msg = prime_StringFormat("%s is closed",
		prime_StringGetCstr(prime_WindowGetTitle(window)));

	prime_LogString(msg);
	prime_StringDestroy(msg);
}

static void
onWindowResize(prime_Window* window, u32 width, u32 height)
{
	prime_String* msg = prime_StringFormat("%s - size(%i, %i)",
		prime_StringGetCstr(prime_WindowGetTitle(window)), width, height);

	prime_LogString(msg);
	prime_StringDestroy(msg);
}

static void 
onWindowKey(prime_Window* window, u16 key, i32 scancode, u8 action)
{
	prime_String* msg = prime_StringFormat("%s - %s, %s)",
		prime_StringGetCstr(prime_WindowGetTitle(window)),
		prime_StringGetCstr(prime_WindowGetKeyName(window, key)),
		prime_StringGetCstr(prime_WindowGetActionName(window, action)));

	prime_LogString(msg);
	prime_StringDestroy(msg);
}

static void 
onWindowButton(prime_Window* window, u16 button, u8 action)
{
	prime_String* msg = prime_StringFormat("%s - %s, %s)",
		prime_StringGetCstr(prime_WindowGetTitle(window)),
		prime_StringGetCstr(prime_WindowGetButtonName(window, button)),
		prime_StringGetCstr(prime_WindowGetActionName(window, action)));

	prime_LogString(msg);
	prime_StringDestroy(msg);
}

static void 
onWindowMouseMoved(prime_Window* window, i32 x, i32 y)
{
	prime_String* msg = prime_StringFormat("%s - mousePos(%i, %i))",
		prime_StringGetCstr(prime_WindowGetTitle(window)), x, y);

	prime_LogString(msg);
	prime_StringDestroy(msg);
}

static void 
onWindowMouseScrolled(prime_Window* window, f32 x_offset, f32 y_offset)
{
	prime_String* msg = prime_StringFormat("%s - mouseScroll(%i, %i))",
		prime_StringGetCstr(prime_WindowGetTitle(window)), x_offset, y_offset);

	prime_LogString(msg);
	prime_StringDestroy(msg);
}

static void
onWindowPos(prime_Window* window, i32 x, i32 y)
{
	prime_String* msg = prime_StringFormat("%s - windowPos(%i, %i))",
		prime_StringGetCstr(prime_WindowGetTitle(window)), x, y);

	prime_LogString(msg);
	prime_StringDestroy(msg);
}

static void 
onWindowFocused(prime_Window* window, b8 focused)
{
	if (focused) {
		prime_String* msg = prime_StringFormat("%s is focused)",
			prime_StringGetCstr(prime_WindowGetTitle(window)));

		prime_LogString(msg);
		prime_StringDestroy(msg);
	}
}

b8
windowTest()
{
	prime_LogInfo("");
	prime_LogInfo("Begin Window Test");

	prime_Window* window = prime_WindowCreate("Begin Window Test", 640, 480);

	// callbacks
	prime_WindowSetCloseCallback(onWindowClose);
	prime_WindowSetKeyCallback(onWindowKey);
	prime_WindowSetButtonCallback(onWindowButton);
	prime_WindowSetMouseMovedCallback(onWindowMouseMoved);
	prime_WindowSetMouseScrolledCallback(onWindowMouseScrolled);
	prime_WindowSetPosCallback(onWindowPos);
	prime_WindowSetSizeCallback(onWindowResize);
	prime_WindowSetFocusCallback(onWindowFocused);

	while (!prime_WindowShouldClose(window)) {
		prime_WindowPollEvents();
	}

	prime_WindowDestroy(window);

	prime_LogInfo("End Window Test");
	prime_LogInfo("");

	return PRIME_PASSED;
}

b8
multiWindowTest()
{
	prime_LogInfo("");
	prime_LogInfo("Begin Multi Window Test");

	prime_Window* window1 = prime_WindowCreate("Begin Multi Window Test Window 1", 640, 480);
	prime_Window* window2 = prime_WindowCreate("Begin Multi Window Test Window 2", 640, 480);

	// callbacks
	prime_WindowSetCloseCallback(onWindowClose);
	prime_WindowSetKeyCallback(onWindowKey);
	prime_WindowSetButtonCallback(onWindowButton);
	prime_WindowSetMouseMovedCallback(onWindowMouseMoved);
	prime_WindowSetMouseScrolledCallback(onWindowMouseScrolled);
	prime_WindowSetPosCallback(onWindowPos);
	prime_WindowSetSizeCallback(onWindowResize);
	prime_WindowSetFocusCallback(onWindowFocused);

	while (!prime_WindowShouldClose(window1)) {
		prime_WindowPollEvents();
	}

	prime_WindowDestroy(window1);
	prime_WindowDestroy(window2);

	prime_LogInfo("End Multi Window Test");
	prime_LogInfo("");

	prime_WindowCallbacksReset();

	return PRIME_PASSED;
}