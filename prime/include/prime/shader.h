
#pragma once

#include "defines.h"

/// @brief Shader
struct prShader;

struct prContext;

/// @brief Shader data types
enum prShaderDataTypes_
{
    prShaderDataTypes_Int,
    prShaderDataTypes_Int2,
    prShaderDataTypes_Int3,
    prShaderDataTypes_Int4,
    prShaderDataTypes_Float,
    prShaderDataTypes_Float2,
    prShaderDataTypes_Float3,
    prShaderDataTypes_Float4
};

/// @brief Shader source types
enum prShaderSourceTypes_
{
    prShaderSourceTypes_GLSL,
};

/// @brief Shader attribute
struct prShaderAttrib
{
    /// @brief The divisor of the attribute. 0 for default;
    u32 divisor = 0;

    /// @brief Normalize the attribue;
    b8 normalize = false;

    /// @brief The type of the attribute. Choose from prShaderDataTypes_
    u32 type = 0;
};

/// @brief Shader layout
struct prShaderLayout
{
    /// @brief attributes
    prShaderAttrib attribs[PR_MAX_ATTRIB]{};
    
    /// @brief attributes count
    u32 count = 0;
};

/// @brief Shader descriptor
struct prShaderDesc
{
    /// @brief Shader shource type. Choose from prShaderSourceTypes_
    u32 type = 0;

    /// @brief Shader vertex source
    const char* vertex_src = nullptr;
    /// @brief Shader vertex source

    const char* pixel_src = nullptr;

    /// @brief Load shader sources from disk
    b8 load = true;

    /// @brief Shader layout
    prShaderLayout layout;
};

/**
 * @brief Create a shader with a shader descriptor. 
 * A Context must be bound before creating the renderer.
 * @param desc The shader descriptor
 * @returns If successful, a pointer to the created shader otherwise nullptr.
 */
PR_API prShader* prCreateShader(prShaderDesc desc);

/**
 * @brief Destroy a shader. A Context must be bound before destroying the shader.
 * @param shader The shader
 */
PR_API void prDestroyShader(prShader* shader);

/**
 * @brief Bind a shader.
 * @param shader The shader
 */
PR_API void prBindShader(prShader* shader);

/**
 * @brief Set the currently bound shader uniform int.
 * @param name The uniform name
 * @param data The data
 */
PR_API void prSetInt(const char* name, i32 data);

/**
 * @brief Set the currently bound shader uniform int array.
 * @param name The uniform name
 * @param data The data array
 * @param count The count of elements in the array
 */
PR_API void prSetIntArray(const char* name, i32* data, u32 count);

/**
 * @brief Set the currently bound shader uniform float.
 * @param name The uniform name
 * @param data The data
 */
PR_API void prSetFloat(const char* name, f32 data);

/**
 * @brief Set the currently bound shader uniform float2.
 * @param name The uniform name
 * @param data The data
 * @param data2 The data2
 */
PR_API void prSetFloat2(const char* name, f32 data, f32 data2);

/**
 * @brief Set the currently bound shader uniform float3.
 * @param name The uniform name
 * @param data The data
 * @param data2 The data2
 * @param data3 The data3
 */
PR_API void prSetFloat3(const char* name, f32 data, f32 data2, f32 data3);

/**
 * @brief Set the currently bound shader uniform float4.
 * @param name The uniform name
 * @param data The data
 * @param data2 The data2
 * @param data3 The data3
 * @param data4 The data4
 */
PR_API void prSetFloat4(const char* name, f32 data, f32 data2, f32 data3, f32 data4);

/**
 * @brief Set the currently bound shader uniform mat4.
 * @param name The uniform name
 * @param data The data
 */
PR_API void prSetMat4(const char* name, f32* data);
