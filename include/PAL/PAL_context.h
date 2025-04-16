
#pragma once

#include "PAL_viewport.h"
#include "PAL_color.h"

struct PAL_Window;

/// @brief Context
struct PAL_Context;

/// @brief Context types
enum PAL_ContextTypes_
{
    PAL_ContextTypes_OpenGL
};

/// @brief Draw mode
enum PAL_DrawModes_
{
    PAL_DrawModes_Triangles
};

/// @brief Blend modes
enum PAL_BlendModes_
{
    PAL_BlendModes_None,
    PAL_BlendModes_Alpha
};

/// @brief Context descriptor
struct PAL_ContextDesc
{
    /// @brief The type of the context.
    u32 type;

    /// @brief The major version of the context
    u32 major;

    /// @brief The minor version of the context
    u32 minor;
};

/**
 * @brief Create a context
 * @param window The window to create the context for
 * @param desc The context descriptor
 * @returns If successful, a pointer to the created context otherwise nullptr.
 */
PAL_API PAL_Context* PAL_CreateContext(PAL_Window* window, PAL_ContextDesc desc);

/**
 * @brief Destroy a context. The destroys all objects created by the context. 
 * @param context The context to destroy
 */
PAL_API void PAL_DestroyContext(PAL_Context* context);

/**
 * @brief Update the currently bound context. 
 */
PAL_API void PAL_SwapBuffers();

/**
 * @brief Clear the currently bound context with the specified color. 
 * @param color The clear color
 */
PAL_API void PAL_Clear(const PAL_Color color);

/**
 * @brief Make the context active. 
 * @param context The context to bind
 */
PAL_API void PAL_MakeActive(PAL_Context* context);

/**
 * @brief Set Vsync for the currently bound context.
 * @param vsync The vsync. true to turn on vsync, otherwise false to turn off vsync
 */
PAL_API void PAL_SetVsync(b8 vsync);

/**
 * @brief Set viewport for the currently bound context.
 * @param viewport The viewport.
 */
PAL_API void PAL_SetViewport(PAL_Viewport viewport);

/**
 * @brief Set blend mode for the currently bound context.
 * @param blend_mode The blend_mode.
 */
PAL_API void PAL_SetBlendMode(u32 blend_mode);

/**
 * @brief Draw arrays using the currently bound context.
 * @param mode The Rendering mode.
 * @param count The count.
 */
PAL_API void PAL_DrawArrays(u32 mode, u32 count);

/**
 * @brief Draw elements using the currently bound context.
 * @param mode The Rendering mode.
 * @param count The count.
 */
PAL_API void PAL_DrawElements(u32 mode, u32 count);

/**
 * @brief Draw elements instanced using the currently bound context.
 * @param mode The Rendering mode.
 * @param count The count.
 * @param instance_count The instanced count.
 */
PAL_API void PAL_DrawElementsInstanced(u32 mode, u32 count, u32 instance_count);

/**
 * @brief Draw arrays instanced using the currently bound context.
 * @param mode The Rendering mode.
 * @param count The count.
 * @param instance_count The instanced count.
 */
PAL_API void PAL_DrawArraysInstanced(u32 mode, u32 count, u32 instance_count);

/**
 * @brief Get the viewport of the currently bound context.
 * @returns the viewport.
 */
PAL_API PAL_Viewport PAL_GetViewport();
