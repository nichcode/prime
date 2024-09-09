
#include "directx11_device.h"
#include "prime/prime_assert.h"
#include "prime/prime_window.h"

#include <d3d11.h>

namespace prime {

	void DirectX11Device::Init(const Window* window)
	{
		D3D_FEATURE_LEVEL featureLevels[] = {
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0
		};

		ID3D11DeviceContext* context = nullptr;
		D3D_FEATURE_LEVEL supportedFeatureLevel;

		DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
		swapChainDesc.BufferDesc.Width = 0;
		swapChainDesc.BufferDesc.Height = 0;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 0;
		swapChainDesc.BufferCount = 1;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.Windowed = TRUE;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swapChainDesc.Flags = 0;
		swapChainDesc.OutputWindow = (HWND)window->GetHandle().Ptr;

		D3D11CreateDeviceAndSwapChain(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
#ifdef PCONFIG_DEBUG
			D3D11_CREATE_DEVICE_DEBUG,
#else
			0,
#endif // PCONFIG_DEBUG
			featureLevels,
			ARRAYSIZE(featureLevels),
			D3D11_SDK_VERSION,
			&swapChainDesc,
			&m_SwapChain,
			&m_Device,
			&supportedFeatureLevel,
			&m_Context
		);

		ID3D11Resource* backBuffer = nullptr;
		// use IID_PPV_ARGS
		m_SwapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
		if (backBuffer) {
			m_Device->CreateRenderTargetView(
				backBuffer,
				nullptr, // TODO: add a rendertarget view desc
				&m_RenderTargetView
			);
			backBuffer->Release();
		}
		
		PASSERT_MSG(m_Device, "DirectX11 device creation failed");
	}

	void DirectX11Device::Shutdown()
	{
		if (m_Device) {
			m_RenderTargetView->Release();
			m_Context->Release();
			m_SwapChain->Release();
			m_Device->Release();
		}
	}

	void DirectX11Device::SetClearColor(f32 r, f32 g, f32 b, f32 a)
	{
		m_ClearColor[0] = r;
		m_ClearColor[1] = g;
		m_ClearColor[2] = b;
		m_ClearColor[3] = a;
	}

	void DirectX11Device::Clear()
	{
		m_Context->ClearRenderTargetView(m_RenderTargetView, m_ClearColor);
	}

	void DirectX11Device::SwapBuffers()
	{
		m_SwapChain->Present(1, 0);
	}
}