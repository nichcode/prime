
#pragma once

#include "prime/renderer/shader.h"

namespace prime::renderer {

    class GLShader : public Shader
    {
    private:
        u32 m_ID, m_Vertex, m_Frag;

    public:
        GLShader(const str& vertex, const str& pixel, b8 load, SourceType type);
        virtual ~GLShader() override;

        GLShader (GLShader& other) = delete;
        GLShader (const GLShader& other) = delete;
        GLShader& operator=(GLShader& other) = delete;
        GLShader& operator=(const GLShader& other) = delete;

        virtual void setInt(const char* name, i32 data) override;
        virtual void setIntArray(const char* name, i32* data, u32 count) override;
        virtual void setFloat(const char* name, f32 data) override;
        virtual void setFloat2(const char* name, maths::vec2 data) override;
        virtual void setFloat3(const char* name, maths::vec3 data) override;
        virtual void setFloat4(const char* name, maths::vec4 data) override;
        virtual void setMat4(const char* name, maths::mat4 data) override;

        virtual void bind() const override;
        virtual void unBind() const override;
    };
    
} // namespace prime::renderer
