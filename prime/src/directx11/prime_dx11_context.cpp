
#include "prime_dx11_context.h"
#include "prime/prime_log.h"
#include "prime/prime_memory.h"
#include "prime/prime_native.h"
#include "prime_utils.h"

#ifdef PRIME_PLATFORM_WINDOWS

// TODO: check direct verion to see if we support 11
#include <d3d11.h>

struct prime_ContextHandle
{
	ID3D11Device* device = nullptr;
	ID3D11DeviceContext* context_handle = nullptr;
	IDXGISwapChain* swapChain = nullptr;
	ID3D11RenderTargetView* view = nullptr;
	prime_Color color;
	u32 vSync = 0;
};

prime_ContextHandle*
prime_Dx11CreateContext(prime_Window* window)
{
	prime_ContextHandle* context_handle = nullptr;
	context_handle = (prime_ContextHandle*)prime_MemAlloc(sizeof(prime_ContextHandle));

	DXGI_SWAP_CHAIN_DESC desc;
	desc.BufferDesc.Width = 0;
	desc.BufferDesc.Height = 0;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.RefreshRate.Denominator = 0;
	desc.BufferDesc.RefreshRate.Numerator = 0;
	desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.BufferCount = 1;
	desc.Windowed = true;
	desc.Flags = 0;
	desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	desc.OutputWindow = prime_GetWin32WindowHandle(window);

	D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&desc,
		&context_handle->swapChain,
		&context_handle->device,
		nullptr,
		&context_handle->context_handle
	);

	ID3D11Resource* back_buffer = nullptr;
	context_handle->swapChain->GetBuffer(0, 
		__uuidof(ID3D11Resource),
		reinterpret_cast<void**>(&back_buffer));

	PRIME_ASSERT_MSG(back_buffer, "Swapchain Back buffer is null");
	context_handle->device->CreateRenderTargetView(back_buffer, nullptr, &context_handle->view);

	PRIME_ASSERT_MSG(context_handle->view, "View creation failed");
	back_buffer->Release();

	if (context_handle->context_handle) {
		prime_SetWindowContextHandle(window, context_handle);
	}
	return context_handle;
}

void
prime_Dx11GDestroy(prime_ContextHandle* context_handle)
{
	if (context_handle->context_handle) {
		context_handle->context_handle->Release();
	}

	if (context_handle->swapChain) {
		context_handle->swapChain->Release();
	}

	if (context_handle->device) {
		context_handle->device->Release();
	}

	if (context_handle->view) {
		context_handle->view->Release();
	}

	context_handle->context_handle = nullptr;
	context_handle->swapChain = nullptr;
	context_handle->view = nullptr;
	context_handle->device = nullptr;

	prime_MemFree(context_handle, sizeof(prime_ContextHandle));
}

void 
prime_Dx11Swapbuffer(prime_Window* window, prime_ContextHandle* context_handle)
{
	context_handle->swapChain->Present(context_handle->vSync, 0);
}

void 
prime_Dx11MakeActive(prime_Window* window, prime_ContextHandle* context_handle)
{
	// TODO:
}

void 
prime_Dx11SetVsync(prime_ContextHandle* context_handle, b8 vsync)
{
	if (vsync) {
		context_handle->vSync = 1;
	}
	else {
		context_handle->vSync = 0;
	}
}

void 
prime_Dx11SetClearColor(prime_ContextHandle* context_handle, const prime_Color& color)
{
	context_handle->color = color;
}

void 
prime_Dx11Clear(prime_ContextHandle* context_handle)
{
	const f32 color[] = {
		context_handle->color.r,
		context_handle->color.g,
		context_handle->color.b,
		context_handle->color.a,
	};

	context_handle->context_handle->ClearRenderTargetView(
		context_handle->view,
		color
	);
}

#endif // PRIME_PLATFORM_WINDOWS