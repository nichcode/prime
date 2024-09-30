
#include "prime/prime.h"

class Rect2D
{
public:
	f32 X = 0.0f;
	f32 Y = 0.0f;
	u32 Width = 50;
	u32 Height = 50;
};

struct Color
{
	u8 R = 0;
	u8 G = 0;
	u8 B= 0;
	u8 A = 255;
};

class Renderer2D
{
	struct Data
	{
		
	};

	prime::Ref<prime::Context> m_Context;
	prime::Device* m_Device;
	Data m_Data;

public:
	Renderer2D() : m_Device(nullptr) {}

	void Init(prime::Device* device, prime::Window* window);
	void Shutdown();

	void SetClearColor(u8 r, u8 g, u8 b, u8 a);
	void Clear();

	void Draw(Rect2D& rect, Color& color);
	void Present();
};

void Renderer2D::Init(prime::Device* device, prime::Window* window)
{
	m_Device = device;
	m_Context = device->CreateContext(window);
	m_Context->SetVSync(true);
}

void Renderer2D::Shutdown()
{
	
}

void Renderer2D::SetClearColor(u8 r, u8 g, u8 b, u8 a)
{
	f32 ndcR = (f32)r / 255;
	f32 ndcG = (f32)g / 255;
	f32 ndcB = (f32)b / 255;
	f32 ndcA = (f32)a / 255;
	m_Context->SetClearColor(ndcR, ndcG, ndcB, ndcA);
}

void Renderer2D::Clear()
{
	m_Context->Clear();
}

void Renderer2D::Draw(Rect2D& rect, Color& color)
{

}

void Renderer2D::Present()
{
	m_Context->SwapBuffers();
}

b8 GameTest()
{
	prime::Device device;
	device.Init(prime::DriverTypesOpenGL);

	prime::Window window;
	prime::WindowProperties props;
	props.title = "GameTest Window";
	window.Init(props);

	Renderer2D renderer;
	renderer.Init(&device, &window);
	renderer.SetClearColor(40, 40, 40, 255);

	while (!window.ShouldClose())
	{
		prime::PollEvents();

		renderer.Clear();
		renderer.Present();
	}

	renderer.Shutdown();
	window.Destroy();
	return PPASSED;
}
