
#pragma once

#include "viewport.h"
#include "color.h"

struct prWindow;

/// @brief Context
struct prContext;

/// @brief Context types
enum prContextTypes_
{
    prContextTypes_OpenGL
};

/// @brief Draw mode
enum prDrawModes_
{
    prDrawModes_Triangles
};

/// @brief Blend modes
enum prBlendModes_
{
    prBlendModes_None,
    prBlendModes_Alpha
};

/// @brief Context descriptor
struct prContextDesc
{
    /// @brief The type of the context. Choose from prContextTypes_
    u32 type;

    /// @brief The major version of the context
    u32 major;

    /// @brief The minor version of the context
    u32 minor;
};

/**
 * @brief Create a context with a context descriptor struct
 * @param window The window to create the context for
 * @param desc The context descriptor
 * @returns If successful, a pointer to the created context otherwise nullptr.
 */
PR_API prContext* prCreateContext(prWindow* window, prContextDesc desc);

/**
 * @brief Destroy a context. The destroys all objects created by the context. 
 * @param context The context to destroy
 */
PR_API void prDestroyContext(prContext* context);

/**
 * @brief Update the currently bound context. 
 */
PR_API void prSwapBuffers();

/**
 * @brief Clear the currently bound context with the specified color. 
 * @param color The clear color
 */
PR_API void prClear(const prColor color);

/**
 * @brief Make the context active. 
 * @param context The context to bind
 */
PR_API void prMakeActive(prContext* context);

/**
 * @brief Set Vsync for the currently bound context.
 * @param vsync The vsync. true to turn on vsync, otherwise false to turn off vsync
 */
PR_API void prSetVsync(b8 vsync);

/**
 * @brief Set viewport for the currently bound context.
 * @param viewport The viewport.
 */
PR_API void prSetView(prViewport viewport);

/**
 * @brief Set blend mode for the currently bound context.
 * @param blend_mode The blend_mode. Choose from prBlendModes_
 */
PR_API void prSetBlendMode(u32 blend_mode);

/**
 * @brief Draw arrays using the currently bound context.
 * @param mode The Rendering mode. Choose from prDrawModes_
 * @param count The count.
 */
PR_API void prDrawArrays(u32 mode, u32 count);

/**
 * @brief Draw elements using the currently bound context.
 * @param mode The Rendering mode. Choose from prDrawModes_
 * @param count The count.
 */
PR_API void prDrawElements(u32 mode, u32 count);

/**
 * @brief Draw elements instanced using the currently bound context.
 * @param mode The Rendering mode. Choose from prDrawModes_
 * @param count The count.
 * @param instance_count The instanced count.
 */
PR_API void prDrawElementsInstanced(u32 mode, u32 count, u32 instance_count);

/**
 * @brief Draw arrays instanced using the currently bound context.
 * @param mode The Rendering mode. Choose from prDrawModes_
 * @param count The count.
 * @param instance_count The instanced count.
 */
PR_API void prDrawArraysInstanced(u32 mode, u32 count, u32 instance_count);

/**
 * @brief Get the viewport of the currently bound context.
 * @returns the viewport.
 */
PR_API prViewport prGetView();
