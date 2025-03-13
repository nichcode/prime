
#pragma once

#include "prime/defines.h"
#include "prime/maths/mat4.h"

namespace prime::renderer {

    class Shader
    {
    public:
        virtual ~Shader() {}

        virtual void setInt(const char* name, i32 data) = 0;
        virtual void setIntArray(const char* name, i32* data, u32 count) = 0;
        virtual void setFloat(const char* name, f32 data) = 0;
        virtual void setFloat2(const char* name, maths::vec2 data) = 0;
        virtual void setFloat3(const char* name, maths::vec3 data) = 0;
        virtual void setFloat4(const char* name, maths::vec4 data) = 0;
        virtual void setMat4(const char* name, maths::mat4 data) = 0;

        virtual void bind() const = 0;
        virtual void unBind() const = 0;
    };
    
} // namespace prime::renderer
