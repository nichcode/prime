
#pragma once

#include "defines.h"

/// @brief Buffer
struct prBuffer;

/// @brief Buffer types
enum prBufferTypes_
{
    prBufferTypes_Vertex,
    prBufferTypes_Index,
    prBufferTypes_Storage,
    prBufferTypes_Uniform
};

/// @brief Buffer usages
enum prBufferUsages_
{
    prBufferUsages_Static,
    prBufferUsages_Dynamic
};

/// @brief Buffer descriptor
struct prBufferDesc
{
    /// @brief The type of the buffer. Choose from prBufferTypes_
    u32 type = 0;

    /// @brief The usage of the buffer. Choose from prBufferUsages_
    u32 usage = 0;

    /// @brief The size in bytes of the buffer.
    u32 size = 0;

    /// @brief The binding base of the buffer. This only applys for Uniform and storage buffers
    u32 binding = 0;

    /// @brief The actual data of the buffer..
    void* data = nullptr;
};

/**
 * @brief Create a buffer with a buffer descriptor struct. A Context must be bound before creating the buffer.
 * @param desc The buffer descriptor
 * @returns If successful, a pointer to the created buffer otherwise nullptr.
 */
PR_API prBuffer* prCreateBuffer(prBufferDesc desc);

/**
 * @brief Destroy a buffer. A Context must be bound before destroying the buffer.
 * @param buffer The buffer
 */
PR_API void prDestroyBuffer(prBuffer* buffer);

/**
 * @brief Bind a buffer to the pipeline
 * @param buffer The buffer
 */
PR_API void prBindBuffer(prBuffer* buffer);

/**
 * @brief Set data to a binded buffer in the pipeline
 * @param type The buffer type to set the data to. the buffer should be bound to the pipeline
 * @param data The data
 * @param size The size of the data
 */
PR_API void prSetBufferData(u32 type, void* data, u32 size);
