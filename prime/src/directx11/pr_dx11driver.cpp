
#include "pr_dx11driver.h"
#include "prime/pr_log.h"
#include "prime/pr_memory.h"
#include "pr_platform.h"

#ifdef PR_PLATFORM_WINDOWS

// TODO: check direct verion to see if we support 11
#include <d3d11.h>

struct PrDriverContext
{
	ID3D11Device* device = nullptr;
	ID3D11DeviceContext* context = nullptr;
	IDXGISwapChain* swapChain = nullptr;
	ID3D11RenderTargetView* view = nullptr;
	PrColor color;
	u32 vSync = 0;
};

PrDriverContext*
prDx11DriverContextCreate(PrWindow* window)
{
	PrDriverContext* context = nullptr;
	context = (PrDriverContext*)prMemAlloc(sizeof(PrDriverContext));

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
	desc.OutputWindow = prWin32GetWindowHandle(window);

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

	PR_ASSERT_MSG(back_buffer, "Swapchain Back buffer is null");
	context->device->CreateRenderTargetView(back_buffer, nullptr, &context->view);

	PR_ASSERT_MSG(context->view, "View creation failed");
	back_buffer->Release();

	PR_INFO("DirectX11 Driver Created!");
	return context;
}

void
prDx11DriverDestroy(PrDriverContext* driver_context)
{
	if (driver_context->context) {
		driver_context->context->Release();
	}

	if (driver_context->swapChain) {
		driver_context->swapChain->Release();
	}

	if (driver_context->device) {
		driver_context->device->Release();
	}

	if (driver_context->view) {
		driver_context->view->Release();
	}

	driver_context->context = nullptr;
	driver_context->swapChain = nullptr;
	driver_context->view = nullptr;
	driver_context->device = nullptr;

	prMemFree(driver_context, sizeof(PrDriverContext));
	driver_context = nullptr;
	PR_INFO("DirectX11 Driver Destroyed!");
}

void 
prDx11DriverSwapbuffers(PrWindow* window, PrDriverContext* driver_context)
{
	driver_context->swapChain->Present(driver_context->vSync, 0);
}

void 
prDx11DriverMakeActive(PrWindow* window, PrDriverContext* driver_context)
{
	// This does nothing in DirectX
}

void 
prDx11DriverSetVsync(PrDriverContext* driver_context, b8 vsync)
{
	if (vsync) {
		driver_context->vSync = 1;
	}
	else {
		driver_context->vSync = 0;
	}
}

void 
prDx11DriverSetClearColor(PrDriverContext* driver_context, const PrColor& color)
{
	driver_context->color = color;
}

void 
prDx11DriverClear(PrDriverContext* driver_context)
{
	const f32 color[] = {
		driver_context->color.r,
		driver_context->color.g,
		driver_context->color.b,
		driver_context->color.a,
	};

	driver_context->context->ClearRenderTargetView(
		driver_context->view,
		color
	);
}

#endif // PR_PLATFORM_WINDOWS