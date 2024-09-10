#pragma once

#include "prime/prime_indexbuffer.h"

namespace prime {

	class DirectX11Indexbuffer : public Indexbuffer
	{
	private:
		Device* m_Device;
		IndexbufferHandle m_Handle;
		u32 m_Count;

	public:
		DirectX11Indexbuffer(Device* device, u32* indices, u32 count);
		virtual ~DirectX11Indexbuffer() override;

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual u32 GetCount() const override { return m_Count; }
	};
}
