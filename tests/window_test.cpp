
#include "prime/prime.h"

void onWindowClose(prWindow* window)
{
	const char* title = prGetWindowTitle(window);
    prLogInfo("%s is closed", title);
}

void onWindowResize(prWindow* window, u32 width, u32 height)
{
    const char* title = prGetWindowTitle(window);
    prLogInfo("size(%i, %i)", width, height);
}

void onWindowKey(prWindow* window, u32 key, i32 scancode, u32 action)
{
    const char* title = prGetWindowTitle(window);
    prLogInfo(
        "%s - %s, %s", title, 
        prGetKeyName(key), 
        prGetActionName(action)
    );
}

void onWindowButton(prWindow* window, u32 button, u32 action)
{
    const char* title = prGetWindowTitle(window);
    prLogInfo(
        "%s - %s, %s", title, 
        prGetButtonName(button), 
        prGetActionName(action)
    );
}

void onWindowMouseMoved(prWindow* window, i32 x, i32 y)
{
    const char* title = prGetWindowTitle(window);
	prLogInfo("%s - mousePos(%i, %i))", title, x, y);
}

void onWindowMouseScrolled(prWindow* window, f32 x_offset, f32 y_offset)
{
    const char* title = prGetWindowTitle(window);
	prLogInfo("%s - mouseScroll(%i, %i))", title, x_offset, y_offset);
}

void onWindowMoved(prWindow* window, i32 x, i32 y)
{
    const char* title = prGetWindowTitle(window);
	prLogInfo("%s - windowPos(%i, %i))", title, x, y);
}

void onWindowFocused(prWindow* window, b8 focused)
{
    if (focused) {
        const char* title = prGetWindowTitle(window);
		prLogInfo("%s is focused", title);
	}
}

int main(int argc, char** argv)
{
    b8 succes = prInit();

    u32 flags = prWindowFlags_Center | prWindowFlags_Show;
    prWindow* window = prCreateWindow("window", 640, 480, flags);

    prSetWindowCloseCallback(onWindowClose);
	prSetWindowKeyCallback(onWindowKey);
	prSetWindowButtonCallback(onWindowButton);
	prSetWindowMouseMovedCallback(onWindowMouseMoved);
	prSetWindowMouseScrolledCallback(onWindowMouseScrolled);
	prSetWindowMovedCallback(onWindowMoved);
	prSetWindowResizedCallback(onWindowResize);
	prSetWindowFocusedCallback(onWindowFocused);

    while (!prWindowShouldClose(window)) {
        prPullEvents();
    }

    prWindowResetCallbacks();
    prDestroyWindow(window);
    prShutdown();
    return 0;
}