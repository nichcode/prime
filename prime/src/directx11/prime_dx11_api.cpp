
#include "prime_dx11_api.h"
#include "prime/prime_log.h"
#include "prime/prime_memory.h"
#include "prime/prime_native.h"
#include "prime_utils.h"

#ifdef PRIME_PLATFORM_WINDOWS

// TODO: check direct verion to see if we support 11
#include <d3d11.h>

struct prime_Context
{
	ID3D11Device* device = nullptr;
	ID3D11DeviceContext* context = nullptr;
	IDXGISwapChain* swapChain = nullptr;
	ID3D11RenderTargetView* view = nullptr;
	prime_Color color;
	u32 vSync = 0;
};

prime_Context*
prime_Dx11CreateContext(prime_Window* window)
{
	prime_Context* context = nullptr;
	context = (prime_Context*)prime_MemAlloc(sizeof(prime_Context));

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
		&context->swapChain,
		&context->device,
		nullptr,
		&context->context
	);

	ID3D11Resource* back_buffer = nullptr;
	context->swapChain->GetBuffer(0, 
		__uuidof(ID3D11Resource),
		reinterpret_cast<void**>(&back_buffer));

	PRIME_ASSERT_MSG(back_buffer, "Swapchain Back buffer is null");
	context->device->CreateRenderTargetView(back_buffer, nullptr, &context->view);

	PRIME_ASSERT_MSG(context->view, "View creation failed");
	back_buffer->Release();

	if (context->context) {
		prime_SetWindowContext(window, context);
	}

	PRIME_INFO("DirectX11 Driver Created!");
	return context;
}

void
prime_Dx11GDestroy(prime_Context* context)
{
	if (context->context) {
		context->context->Release();
	}

	if (context->swapChain) {
		context->swapChain->Release();
	}

	if (context->device) {
		context->device->Release();
	}

	if (context->view) {
		context->view->Release();
	}

	context->context = nullptr;
	context->swapChain = nullptr;
	context->view = nullptr;
	context->device = nullptr;

	prime_MemFree(context, sizeof(prime_Context));
	context = nullptr;
	PRIME_INFO("DirectX11 Driver Destroyed!");
}

void 
prime_Dx11Swapbuffer(prime_Window* window, prime_Context* context)
{
	context->swapChain->Present(context->vSync, 0);
}

void 
prime_Dx11MakeActive(prime_Window* window, prime_Context* context)
{
	// TODO:
}

void 
prime_Dx11SetVsync(prime_Context* context, b8 vsync)
{
	if (vsync) {
		context->vSync = 1;
	}
	else {
		context->vSync = 0;
	}
}

void 
prime_Dx11SetClearColor(prime_Context* context, const prime_Color& color)
{
	context->color = color;
}

void 
prime_Dx11Clear(prime_Context* context)
{
	const f32 color[] = {
		context->color.r,
		context->color.g,
		context->color.b,
		context->color.a,
	};

	context->context->ClearRenderTargetView(
		context->view,
		color
	);
}

#endif // PRIME_PLATFORM_WINDOWS