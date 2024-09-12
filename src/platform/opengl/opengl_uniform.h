#pragma once

#include "prime/prime_uniformbuffer.h"

namespace prime {

	class OpenGLUniformbuffer : public Uniformbuffer
	{
	private:
		UniformbufferHandle m_Handle;
		u32 m_ID;
		Device* m_Device;

	public:
		OpenGLUniformbuffer(Device* device, u32 size, u32 binding);
		virtual ~OpenGLUniformbuffer() override;

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void SetData(u32 size, void* data) override;
	};
}
