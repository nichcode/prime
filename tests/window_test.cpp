
#include "PAL/PAL.h"

void onWindowClose(PAL_Window* window)
{
	const char* title = PAL_GetWindowTitle(window);
    PAL_LogInfo("%s is closed", title);
}

void onWindowResize(PAL_Window* window, u32 width, u32 height)
{
    const char* title = PAL_GetWindowTitle(window);
    PAL_LogInfo("size(%i, %i)", width, height);
}

void onWindowKey(PAL_Window* window, u32 key, i32 scancode, u32 action)
{
    const char* title = PAL_GetWindowTitle(window);
    PAL_LogInfo(
        "%s - %s, %s", title, 
        PAL_GetKeyName(key), 
        PAL_GetActionName(action)
    );
}

void onWindowButton(PAL_Window* window, u32 button, u32 action)
{
    const char* title = PAL_GetWindowTitle(window);
    PAL_LogInfo(
        "%s - %s, %s", title, 
        PAL_GetButtonName(button), 
        PAL_GetActionName(action)
    );
}

void onWindowMouseMoved(PAL_Window* window, i32 x, i32 y)
{
    const char* title = PAL_GetWindowTitle(window);
	PAL_LogInfo("%s - mousePos(%i, %i))", title, x, y);
}

void onWindowMouseScrolled(PAL_Window* window, f32 x_offset, f32 y_offset)
{
    const char* title = PAL_GetWindowTitle(window);
	PAL_LogInfo("%s - mouseScroll(%i, %i))", title, x_offset, y_offset);
}

void onWindowMoved(PAL_Window* window, i32 x, i32 y)
{
    const char* title = PAL_GetWindowTitle(window);
	PAL_LogInfo("%s - windowPos(%i, %i))", title, x, y);
}

void onWindowFocused(PAL_Window* window, b8 focused)
{
    if (focused) {
        const char* title = PAL_GetWindowTitle(window);
		PAL_LogInfo("%s is focused", title);
	}
}

int main(int argc, char** argv)
{
    b8 succes = PAL_Init();

    u32 flags = PAL_WindowFlags_Center | PAL_WindowFlags_Show;
    PAL_Window* window = PAL_CreateWindow("window", 640, 480, flags);

    PAL_SetWindowCloseCallback(onWindowClose);
	PAL_SetWindowKeyCallback(onWindowKey);
	PAL_SetWindowButtonCallback(onWindowButton);
	PAL_SetWindowMouseMovedCallback(onWindowMouseMoved);
	PAL_SetWindowMouseScrolledCallback(onWindowMouseScrolled);
	PAL_SetWindowMovedCallback(onWindowMoved);
	PAL_SetWindowResizedCallback(onWindowResize);
	PAL_SetWindowFocusedCallback(onWindowFocused);

    while (!PAL_WindowShouldClose(window)) {
        PAL_PullEvents();
    }

    PAL_WindowResetCallbacks();
    PAL_DestroyWindow(window);
    PAL_Shutdown();
    return 0;
}