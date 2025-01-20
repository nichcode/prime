
#include "prime_dx11_context.h"
#include "prime/prime_log.h"
#include "prime/prime_memory.h"
#include "prime/prime_native.h"

#ifdef PRIME_PLATFORM_WINDOWS

// TODO: check direct verion to see if we support 11
#include <d3d11.h>

struct dx11_Context
{
	ID3D11Device* device = nullptr;
	ID3D11DeviceContext* handle = nullptr;
	IDXGISwapChain* swapChain = nullptr;
	ID3D11RenderTargetView* view = nullptr;
	prime_Color color;
	u32 vSync = 0;
};

void*
dx11_ContextCreate(prime_Window* window)
{
	dx11_Context* context = nullptr;
	context = (dx11_Context*)prime_MemAlloc(sizeof(dx11_Context));

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
	desc.OutputWindow = prime_WindowGetWin32Handle(window);

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
		&context->handle
	);

	ID3D11Resource* back_buffer = nullptr;
	context->swapChain->GetBuffer(0, 
		__uuidof(ID3D11Resource),
		reinterpret_cast<void**>(&back_buffer));

	PRIME_ASSERT_MSG(back_buffer, "Swapchain Back buffer is null");
	context->device->CreateRenderTargetView(back_buffer, nullptr, &context->view);

	PRIME_ASSERT_MSG(context->view, "View creation failed");
	back_buffer->Release();

	return context;
}

void
dx11_ContextDestroy(void* handle)
{
	dx11_Context* dx11_context = (dx11_Context*)handle;

	if (dx11_context->handle) {
		dx11_context->handle->Release();
	}

	if (dx11_context->swapChain) {
		dx11_context->swapChain->Release();
	}

	if (dx11_context->device) {
		dx11_context->device->Release();
	}

	if (dx11_context->view) {
		dx11_context->view->Release();
	}

	dx11_context->handle = nullptr;
	dx11_context->swapChain = nullptr;
	dx11_context->view = nullptr;
	dx11_context->device = nullptr;

	prime_MemFree(handle, sizeof(dx11_Context));
}

void 
dx11_ContextSwapbuffer(prime_Window* window, void* handle)
{
	dx11_Context* dx11_context = (dx11_Context*)handle;
	dx11_context->swapChain->Present(dx11_context->vSync, 0);
}

void 
dx11_ContextMakeActive(prime_Window* window, void* handle)
{
	// TODO:
}

void 
dx11_ContextSetVsync(void* handle, b8 vsync)
{
	dx11_Context* dx11_context = (dx11_Context*)handle;
	if (vsync) {
		dx11_context->vSync = 1;
	}
	else {
		dx11_context->vSync = 0;
	}
}

void 
dx11_ContextSetClearColor(void* handle, const prime_Color& color)
{
	dx11_Context* dx11_context = (dx11_Context*)handle;
	dx11_context->color = color;
}

void 
dx11_ContextClear(void* handle)
{
	dx11_Context* dx11_context = (dx11_Context*)handle;
	const f32 color[] = {
		dx11_context->color.r,
		dx11_context->color.g,
		dx11_context->color.b,
		dx11_context->color.a,
	};

	dx11_context->handle->ClearRenderTargetView(
		dx11_context->view,
		color
	);
}

#endif // PRIME_PLATFORM_WINDOWS