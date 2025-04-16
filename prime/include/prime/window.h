
#pragma once

#include "defines.h"

/// @brief Window
struct prWindow;

/// @brief Window close callback
using prWindowCloseFunc = void(*)(prWindow* window);

/// @brief Window key callback
using prWindowKeyFunc = void(*)(prWindow* window, u32 key, i32 scancode, u32 action);

/// @brief Window button callback
using prWindowButtonFunc = void(*)(prWindow* window, u32 button, u32 action);

/// @brief Window mouse moved callback
using prWindowMouseMovedFunc = void(*)(prWindow* window, i32 x, i32 y);

/// @brief Window mouse scrolled callback
using prWindowMouseScrolledFunc = void(*)(prWindow* window, f32 offset_x, f32 offset_y);

/// @brief Window moved callback
using prWindowMovedFunc = void(*)(prWindow* window, i32 x, i32 y);

/// @brief Window resized callback
using prWindowResizeFunc = void(*)(prWindow* window, u32 width, u32 height);

/// @brief Window focused callback
using prWindowFocusedFunc = void(*)(prWindow* window, b8 focused);

/// @brief Window flags
enum prWindowFlags_
{
    prWindowFlags_Show = PR_BIT(0),
    prWindowFlags_Center = PR_BIT(1)
};

/**
 * @brief Create a window.
 * @param title The title of the window
 * @param width The width of the window
 * @param height The height of the window
 * @param flags The window flags
 * @returns If successful, a pointer to the created window otherwise nullptr.
 */
PR_API prWindow* prCreateWindow(const char* title, u32 width, u32 height, u32 flags);

/**
 * @brief Destroy a window.
 * @param window The window
 */
PR_API void prDestroyWindow(prWindow* window);

/**
 * @brief Pull window events for all created windows.
 */
PR_API void prPullEvents();

/**
 * @brief Hide window
 * @param window The window
 */
PR_API void prHideWindow(prWindow* window);

/**
 * @brief Show window
 * @param window The window
 */
PR_API void prShowWindow(prWindow* window);

/**
 * @brief Set the title of the window
 * @param window The window
 * @param title The title
 */
PR_API void prSetWindowTitle(prWindow* window, const char* title);

/**
 * @brief Set the size of the window
 * @param window The window
 * @param width The width of the window
 * @param height The height of the window
 */
PR_API void prSetWindowSize(prWindow* window, u32 width, u32 height);

/**
 * @brief Set the position of the window
 * @param window The window
 * @param x The x position of the window
 * @param y The y position of the window
 */
PR_API void prSetWindowPos(prWindow* window, i32 x, i32 y);

/**
 * @brief Set the window close callback
 * @param func The callback
 */
PR_API void prSetWindowCloseCallback(prWindowCloseFunc func);

/**
 * @brief Set the window key callback
 * @param func The callback
 */
PR_API void prSetWindowKeyCallback(prWindowKeyFunc func);

/**
 * @brief Set the window button callback
 * @param func The callback
 */
PR_API void prSetWindowButtonCallback(prWindowButtonFunc func);

/**
 * @brief Set the window mouse moved callback
 * @param func The callback
 */
PR_API void prSetWindowMouseMovedCallback(prWindowMouseMovedFunc func);

/**
 * @brief Set the window mouse scrolled callback
 * @param func The callback
 */
PR_API void prSetWindowMouseScrolledCallback(prWindowMouseScrolledFunc func);

/**
 * @brief Set the window moved callback
 * @param func The callback
 */
PR_API void prSetWindowMovedCallback(prWindowMovedFunc func);

/**
 * @brief Set the window resized callback
 * @param func The callback
 */
PR_API void prSetWindowResizedCallback(prWindowResizeFunc func);

/**
 * @brief Set the window focused callback
 * @param func The callback
 */
PR_API void prSetWindowFocusedCallback(prWindowFocusedFunc func);

/**
 * @brief Reset all window callbacks
 */
PR_API void prWindowResetCallbacks();

/**
 * @brief Check if window close button has been clicked.
 * @param window The window
 * @returns True if clicked otherwise false
 */
PR_API b8 prWindowShouldClose(prWindow* window);

/**
 * @brief Get the state of a key.
 * @param window The window
 * @param key The key
 * @returns True if pressed otherwise false
 */
PR_API b8 prGetKeyState(prWindow* window, u32 key);

/**
 * @brief Get the state of a button.
 * @param window The window
 * @param button The button
 * @returns True if pressed otherwise false
 */
PR_API b8 prGetButtonState(prWindow* window, u32 button);

/**
 * @brief Get the title of a window.
 * @param window The window
 * @returns the title of the window
 */
PR_API const char* prGetWindowTitle(prWindow* window);

/**
 * @brief Get the handle of a window.
 * @param window The window
 * @returns the handle of the window
 */
PR_API void* prGetWindowHandle(prWindow* window);

/**
 * @brief Get the width of a window.
 * @param window The window
 * @returns the width of the window
 */
PR_API u32 prGetWindowWidth(prWindow* window);

/**
 * @brief Get the height of a window.
 * @param window The window
 * @returns the height of the window
 */
PR_API u32 prGetWindowHeight(prWindow* window);

/**
 * @brief Get the x position of a window.
 * @param window The window
 * @returns the x position of the window
 */
PR_API i32 prGetWindowPosX(prWindow* window);

/**
 * @brief Get the y position of a window.
 * @param window The window
 * @returns the y position of the window
 */
PR_API i32 prGetWindowPosY(prWindow* window);