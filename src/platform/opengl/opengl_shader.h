#pragma once

#include "prime/shader.h"
#include <unordered_map>

namespace prime {

	class OpenGLShader : public Shader
	{
	private:
		u32 m_id = 0, m_v_shader, m_p_shader;
		std::unordered_map<str, i32> m_uniform_locations;

	public:
		OpenGLShader(const str& v_source, const str& p_source, b8 load);
		virtual ~OpenGLShader() override;

		virtual void bind() override;
		virtual void unbind() override;

		virtual void set_int(const str& name, i32 data) override;
		virtual void set_int_array(const str& name, i32* data, u32 count) override;

		virtual void set_float(const str& name, f32 data) override;
		virtual void set_float2(const str& name, f32 data, f32 data2) override;
		virtual void set_float3(const str& name, f32 data, f32 data2, f32 data3) override;
		virtual void set_float4(const str& name, f32 data, f32 data2, f32 data3, f32 data4) override;

		virtual void set_mat2(const str& name, f32* data) override;
		virtual void set_mat3(const str& name, f32* data) override;
		virtual void set_mat4(const str& name, f32* data) override;

	private:
		i32 get_uniform_location(const str& name);
	};
}
