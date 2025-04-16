
#pragma once

#include "PAL_defines.h"

/// @brief Buffer
struct PAL_Buffer;

/// @brief Buffer types
enum PAL_BufferTypes_
{
    PAL_BufferTypes_Vertex,
    PAL_BufferTypes_Index,
    PAL_BufferTypes_Storage,
    PAL_BufferTypes_Uniform
};

/// @brief Buffer usages
enum PAL_BufferUsages_
{
    PAL_BufferUsages_Static,
    PAL_BufferUsages_Dynamic
};

/// @brief Buffer descriptor
struct PAL_BufferDesc
{
    /// @brief The type of the buffer.
    u32 type = 0;

    /// @brief The usage of the buffer.
    u32 usage = 0;

    /// @brief The size in bytes of the buffer.
    u32 size = 0;

    /// @brief The binding base of the buffer. This only applys for Uniform and storage buffers
    u32 binding = 0;

    /// @brief The actual data of the buffer..
    void* data = nullptr;
};

/**
 * @brief Create a buffer. 
 * A Context must be bound before creating the buffer.
 * @param desc The buffer descriptor
 * @returns If successful, a pointer to the created buffer otherwise nullptr.
 */
PAL_API PAL_Buffer* PAL_CreateBuffer(PAL_BufferDesc desc);

/**
 * @brief Destroy a buffer. A Context must be bound before destroying the buffer.
 * @param buffer The buffer
 */
PAL_API void PAL_DestroyBuffer(PAL_Buffer* buffer);

/**
 * @brief Bind a buffer to the pipeline
 * @param buffer The buffer
 */
PAL_API void PAL_BindBuffer(PAL_Buffer* buffer);

/**
 * @brief Set data to a binded buffer in the pipeline
 * @param type The buffer type to set the data to. the buffer should be bound to the pipeline
 * @param data The data
 * @param size The size of the data
 */
PAL_API void PAL_SetBufferData(u32 type, void* data, u32 size);
