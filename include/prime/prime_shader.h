#pragma once

#include "prime_defines.h"
#include "prime_ref.h"

namespace prime {

	class Device;

	struct ShaderHandle
	{
		void* Ptr = nullptr;
	};

	class Shader
	{
	private:
		friend class Device;

	public:
		virtual ~Shader() {}

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void setInt(const str& name, i32 data) = 0;
		virtual void setIntArray(const str& name, i32* data, u32 count) = 0;

		virtual void setFloat(const str& name, f32 data) = 0;
		virtual void setFloat2(const str& name, f32 data, f32 data2) = 0;
		virtual void setFloat3(const str& name, f32 data, f32 data2, f32 data3) = 0;
		virtual void setFloat4(const str& name, f32 data, f32 data2, f32 data3, f32 data4) = 0;

		virtual void setMat2(const str& name, f32* value) = 0;
		virtual void setMat3(const str& name, f32* value) = 0;
		virtual void setMat4(const str& name, f32* value) = 0;

	private:
		static Ref<Shader> Create(Device* devide, const str& vSource, const str& pSource, b8 load);
	};
}
