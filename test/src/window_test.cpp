
#include "prime/prime.h"

static PrWindow* window = nullptr;

static void 
onWindowClose(PrWindow* window)
{
	PrString* msg = prStringFormat("%s is closed",
		prStringGetBuffer(prWindowGetTitle(window)));

	prStringLog(msg);
	prStringDestroy(msg);
}

static void
onWindowResize(PrWindow* window, u32 width, u32 height)
{
	PrString* msg = prStringFormat("%s - size(%i, %i)",
		prStringGetBuffer(prWindowGetTitle(window)), width, height);

	prStringLog(msg);
	prStringDestroy(msg);
}

static void 
onWindowKey(PrWindow* window, u16 key, i32 scancode, u8 action)
{
	PrString* msg = prStringFormat("%s - %s, %s)",
		prStringGetBuffer(prWindowGetTitle(window)),
		prStringGetBuffer(prWindowGetKeyName(window, key)),
		prStringGetBuffer(prWindowGetActionName(window, action)));

	prStringLog(msg);
	prStringDestroy(msg);
}

static void 
onWindowButton(PrWindow* window, u16 button, u8 action)
{
	PrString* msg = prStringFormat("%s - %s, %s)",
		prStringGetBuffer(prWindowGetTitle(window)),
		prStringGetBuffer(prWindowGetButtonName(window, button)),
		prStringGetBuffer(prWindowGetActionName(window, action)));

	prStringLog(msg);
	prStringDestroy(msg);
}

static void 
onWindowMouseMoved(PrWindow* window, i32 x, i32 y)
{
	PrString* msg = prStringFormat("%s - mousePos(%i, %i))",
		prStringGetBuffer(prWindowGetTitle(window)), x, y);

	prStringLog(msg);
	prStringDestroy(msg);
}

static void 
onWindowMouseScrolled(PrWindow* window, f32 x_offset, f32 y_offset)
{
	PrString* msg = prStringFormat("%s - mouseScroll(%i, %i))",
		prStringGetBuffer(prWindowGetTitle(window)), x_offset, y_offset);

	prStringLog(msg);
	prStringDestroy(msg);
}

static void
onWindowPos(PrWindow* window, i32 x, i32 y)
{
	PrString* msg = prStringFormat("%s - windowPos(%i, %i))",
		prStringGetBuffer(prWindowGetTitle(window)), x, y);

	prStringLog(msg);
	prStringDestroy(msg);
}

static void 
onWindowFocused(PrWindow* window, b8 focused)
{
	if (focused) {
		PrString* msg = prStringFormat("%s is focused)",
			prStringGetBuffer(prWindowGetTitle(window)));

		prStringLog(msg);
		prStringDestroy(msg);
	}
}

b8
windowTest()
{
	PR_INFO("");
	PR_INFO("Begin Window Test");

	window = prWindowCreate("Prime Window", 640, 480);

	// callbacks
	prWindowSetCloseCallback(onWindowClose);
	prWindowSetKeyCallback(onWindowKey);
	prWindowSetButtonCallback(onWindowButton);
	prWindowSetMouseMovedCallback(onWindowMouseMoved);
	prWindowSetMouseScrolledCallback(onWindowMouseScrolled);
	prWindowSetPosCallback(onWindowPos);
	prWindowSetSizeCallback(onWindowResize);
	prWindowSetFocusCallback(onWindowFocused);

	while (!prWindowShouldClose(window)) {
		prWindowPollEvents();
	}

	prWindowDestroy(window);

	PR_INFO("End PrWindow Test");
	PR_INFO("");

	return PR_PASSED;
}