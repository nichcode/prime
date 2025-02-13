
#include "prime/prime.h"

static void
onWindowClose(primeWindow* window)
{
	char* msg = primeStringFormat("%s is closed", primeWindowGetTitle(window));
	primeLogInfo(msg);
	primeStringFree(msg);
}

static void
onWindowResize(primeWindow* window, u32 width, u32 height)
{
	char* msg = primeStringFormat("%s - size(%i, %i)", primeWindowGetTitle(window), width, height);
	primeLogInfo(msg);
	primeStringFree(msg);
}

static void
onWindowKey(primeWindow* window, u16 key, i32 scancode, u8 action)
{
	char* msg = primeStringFormat("%s - %s, %s)",
		primeWindowGetTitle(window),
		primeKeyGetName(key),
		primeActionGetName(action));

	primeLogInfo(msg);
	primeStringFree(msg);
}

static void
onWindowButton(primeWindow* window, u16 button, u8 action)
{
	char* msg = primeStringFormat("%s - %s, %s)",
		primeWindowGetTitle(window),
		primeButtonGetName(button),
		primeActionGetName(action));

	primeLogInfo(msg);
	primeStringFree(msg);
}

static void
onWindowMouseMoved(primeWindow* window, i32 x, i32 y)
{
	char* msg = primeStringFormat("%s - mousePos(%i, %i))", primeWindowGetTitle(window), x, y);
	primeLogInfo(msg);
	primeStringFree(msg);
}

static void
onWindowMouseScrolled(primeWindow* window, f32 x_offset, f32 y_offset)
{
	char* msg = primeStringFormat("%s - mouseScroll(%i, %i))", primeWindowGetTitle(window), x_offset, y_offset);
	primeLogInfo(msg);
	primeStringFree(msg);
}

static void
onWindowMoved(primeWindow* window, i32 x, i32 y)
{
	char* msg = primeStringFormat("%s - windowPos(%i, %i))", primeWindowGetTitle(window), x, y);
	primeLogInfo(msg);
	primeStringFree(msg);
}

static void
onWindowFocused(primeWindow* window, b8 focused)
{
	if (focused) {
		char* msg = primeStringFormat("%s is focused)", primeWindowGetTitle(window));
		primeLogInfo(msg);
		primeStringFree(msg);
	}
}

b8
windowTest()
{
	primeWindow* window = primeWindowCreate("Window Test", 640, 480);

	// callbacks
	primeWindowSetCloseCallback(onWindowClose);
	primeWindowSetKeyCallback(onWindowKey);
	primeWindowSetButtonCallback(onWindowButton);
	primeWindowSetMouseMovedCallback(onWindowMouseMoved);
	primeWindowSetMouseScrolledCallback(onWindowMouseScrolled);
	primeWindowSetMovedCallback(onWindowMoved);
	primeWindowSetResizeCallback(onWindowResize);
	primeWindowSetFocusedCallback(onWindowFocused);

	while (!primeWindowShouldClose(window)) {
		primeWindowPollEvents();
	}

	primeWindowResetCallbacks();
	primeWindowDestroy(window);

	return true;
}

b8
multiWindowTest()
{
	primeWindow* window = primeWindowCreate("Window Test", 640, 480);
	primeWindow* window2 = primeWindowCreate("Window Test2", 640, 480);

	// callbacks
	primeWindowSetCloseCallback(onWindowClose);
	primeWindowSetKeyCallback(onWindowKey);
	primeWindowSetButtonCallback(onWindowButton);
	primeWindowSetMouseMovedCallback(onWindowMouseMoved);
	primeWindowSetMouseScrolledCallback(onWindowMouseScrolled);
	primeWindowSetMovedCallback(onWindowMoved);
	primeWindowSetResizeCallback(onWindowResize);
	primeWindowSetFocusedCallback(onWindowFocused);

	while (!primeWindowShouldClose(window)) {
		primeWindowPollEvents();
	}

	primeWindowResetCallbacks();
	primeWindowDestroy(window);
	primeWindowDestroy(window2);

	return true;
}