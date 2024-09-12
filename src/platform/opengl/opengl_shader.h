#pragma once

#include "prime/prime_shader.h"
#include <unordered_map>

namespace prime {

	class OpenGLShader : public Shader
	{
	private:
		ShaderHandle m_Handle;
		u32 m_ID = 0, m_VShader, m_PShader;
		Device* m_Device;
		std::unordered_map<str, i32> m_UniformLocations;

	public:
		OpenGLShader(Device* device, const str& vSource, const str& pSource, b8 load);
		virtual ~OpenGLShader() override;

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void setInt(const str& name, i32 data) override;
		virtual void setIntArray(const str& name, i32* data, u32 count) override;

		virtual void setFloat(const str& name, f32 data) override;
		virtual void setFloat2(const str& name, f32 data, f32 data2) override;
		virtual void setFloat3(const str& name, f32 data, f32 data2, f32 data3) override;
		virtual void setFloat4(const str& name, f32 data, f32 data2, f32 data3, f32 data4) override;

		virtual void setMat2(const str& name, f32* value) override;
		virtual void setMat3(const str& name, f32* value) override;
		virtual void setMat4(const str& name, f32* value) override;

	private:
		i32 GetUniformLocation(const str& name);
	};
}
