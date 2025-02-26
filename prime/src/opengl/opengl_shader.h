
#pragma once

#include "prime/shader.h"

namespace prime {

    class GLShader : public Shader
    {
    private:
        u32 m_Vertex, m_Pixel;
        ShaderHandle* m_Handle;

    public:
        GLShader(const ShaderDesc& desc);
        virtual ~GLShader() override;

        virtual void
        setInt(const char* name, i32 data) override;

        virtual void
        setIntArray(const char* name, i32* data, u32 count) override;

        virtual void
        setFloat(const char* name, f32 data) override;

        virtual void
        setFloat2(const char* name, vec2 data) override;

        virtual void
        setFloat3(const char* name, vec3 data) override;

        virtual void
        setFloat4(const char* name, vec4 data) override;

        virtual void
        setMat4(const char* name, mat4 data) override;

        virtual ShaderHandle* 
        getHandle() const override { return m_Handle; }
    };
    
} // namespace prime
