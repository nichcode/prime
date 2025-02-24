
#pragma once

#include "math.h"

namespace prime {

    enum class ShaderSourceType
    {
        GLSL
    };

    struct ShaderDesc
    {
        str vertex = "";
        str pixel = "";
        b8 load = true;
        ShaderSourceType type = ShaderSourceType::GLSL;
    };

    class Shader
    {
    public:
        virtual ~Shader() {}

        virtual void
        setInt(const char* name, i32 data) = 0;

        virtual void
        setIntArray(const char* name, i32* data, u32 count) = 0;

        virtual void
        setFloat(const char* name, f32 data) = 0;

        virtual void
        setFloat2(const char* name, vec2 data) = 0;

        virtual void
        setFloat3(const char* name, vec3 data) = 0;

        virtual void
        setFloat4(const char* name, vec4 data) = 0;

        virtual void
        setMat4(const char* name, mat4 data) = 0;

        virtual u32 getID() const = 0;
        virtual void* getHandle() const = 0;
    };
    
} // namespace prime
