
#pragma once

#include "prime/prime.h"

void onWindowClose(primeWindow* window)
{
	const char* title = primeGetWindowTitle(window);
    primeLogInfo("%s is closed", title);
}

void onWindowResize(primeWindow* window, u32 width, u32 height)
{
    const char* title = primeGetWindowTitle(window);
    primeLogInfo("size(%i, %i)", width, height);
}

void onWindowKey(primeWindow* window, u32 key, i32 scancode, u32 action)
{
    const char* title = primeGetWindowTitle(window);
    primeLogInfo(
        "%s - %s, %s", title, 
        primeGetKeyName(key), 
        primeGetActionName(action)
    );
}

void onWindowButton(primeWindow* window, u32 button, u32 action)
{
    const char* title = primeGetWindowTitle(window);
    primeLogInfo(
        "%s - %s, %s", title, 
        primeGetButtonName(button), 
        primeGetActionName(action)
    );
}

void onWindowMouseMoved(primeWindow* window, i32 x, i32 y)
{
    const char* title = primeGetWindowTitle(window);
	primeLogInfo("%s - mousePos(%i, %i))", title, x, y);
}

void onWindowMouseScrolled(primeWindow* window, f32 x_offset, f32 y_offset)
{
    const char* title = primeGetWindowTitle(window);
	primeLogInfo("%s - mouseScroll(%i, %i))", title, x_offset, y_offset);
}

void onWindowMoved(primeWindow* window, i32 x, i32 y)
{
    const char* title = primeGetWindowTitle(window);
	primeLogInfo("%s - windowPos(%i, %i))", title, x, y);
}

void onWindowFocused(primeWindow* window, b8 focused)
{
    if (focused) {
        const char* title = primeGetWindowTitle(window);
		primeLogInfo("%s is focused", title);
	}
}

b8 windowTest(void* data)
{
    primeWindowDesc desc;
    desc.size.x = 640;
    desc.size.y = 480;
    desc.title = "window";
    desc.flag = primeWindowFlags_Center;
    primeWindow* window = primeCreateWindow(desc);

    // callbacks
    primeSetCloseCallback(onWindowClose);
	primeSetKeyCallback(onWindowKey);
	primeSetButtonCallback(onWindowButton);
	primeSetMouseMovedCallback(onWindowMouseMoved);
	primeSetMouseScrolledCallback(onWindowMouseScrolled);
	primeSetMovedCallback(onWindowMoved);
	primeSetResizedCallback(onWindowResize);
	primeSetFocusedCallback(onWindowFocused);

    while (!primeWindowShouldClose(window)) {
        primePullEvents();

    }

    primeResetCallbacks();
    primeDestroyWindow(window);
    return PRIME_PASSED;
}
