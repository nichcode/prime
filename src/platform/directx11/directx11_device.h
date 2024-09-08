#pragma once

#include "prime_idevice.h"
#include <d3d11.h>

namespace prime {

	class DirectX11Device : public IDevice
	{
	private:
		ID3D11Device* m_Device;
		IDXGISwapChain* m_SwapChain;
		ID3D11DeviceContext* m_Context;
		ID3D11RenderTargetView* m_RenderTargetView;

		f32 m_ClearColor[4];

	public:
		DirectX11Device() : m_Device(nullptr), m_SwapChain(nullptr),
			m_Context(nullptr), m_RenderTargetView(nullptr) 
		{
			memset(m_ClearColor, 0, sizeof(m_ClearColor));
			m_ClearColor[0] = 0.0f;
			m_ClearColor[1] = 0.0f;
			m_ClearColor[2] = 0.0f;
			m_ClearColor[3] = 1.0f;
	    }

		virtual void Init(const Window* window) override;
		virtual void Shutdown() override;

        PINLINE virtual void SetClearColor(f32 r, f32 g, f32 b, f32 a) override
		{
			m_ClearColor[0] = r;
			m_ClearColor[1] = g;
			m_ClearColor[2] = b;
			m_ClearColor[3] = a;
		}

		virtual void Clear() override;
		virtual void SwapBuffers() override;
	};
}
