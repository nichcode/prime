#pragma once

#include "prime/prime_shader.h"
#include <unordered_map>

namespace prime {

	class OpenGLShader : public Shader
	{
		u32 m_ID = 0, m_VShader, m_PShader;
		std::unordered_map<str, i32> m_UniformLocations;

	public:
		OpenGLShader(const str& vSource, const str& pSource, b8 load);
		virtual ~OpenGLShader() override;

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void SetInt(const str& name, i32 data) override;
		virtual void SetIntArray(const str& name, i32* data, u32 count) override;

		virtual void SetFloat(const str& name, f32 data) override;
		virtual void SetFloat2(const str& name, f32 data, f32 data2) override;
		virtual void SetFloat3(const str& name, f32 data, f32 data2, f32 data3) override;
		virtual void SetFloat4(const str& name, f32 data, f32 data2, f32 data3, f32 data4) override;

		virtual void SetMat2(const str& name, f32* data) override;
		virtual void SetMat3(const str& name, f32* data) override;
		virtual void SetMat4(const str& name, f32* data) override;

	private:
		i32 GetUniformLocation(const str& name);
	};
}
