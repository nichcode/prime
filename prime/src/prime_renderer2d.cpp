
#include "prime/prime_renderer2d.h"
#include "prime/prime_window.h"
#include "prime/prime_log.h"
#include "prime/prime_buffers.h"
#include "prime/prime_shader.h"
#include "prime/prime_context.h"
#include "prime_shader_sources.h"

struct SpriteData
{
	prime_Vertexbuffer* vertexbuffer = nullptr;
	prime_Indexbuffer* indexbuffer = nullptr;
	prime_Shader* shader = nullptr;
	u32 indexCount = 0;
};

struct prime_Renderer2D
{
	prime_Device* device = nullptr;
	prime_Context* context = nullptr;
	prime_Uniformbuffer* uniformbuffer = nullptr;
	prime_Viewport viewport;
	SpriteData spriteData;
};

static void 
setProjectionMatrix(prime_Renderer2D* ren)
{
	const prime_Viewport& viewport = prime_Renderer2DGetViewport(ren);
	prime_Mat4 matrix = prime_Mat4Orthographic(
		viewport.x,
		(f32)viewport.width,
		(f32)viewport.height,
		viewport.y,
		-1.0f,
		1.0f);

	prime_UniformbufferBind(ren->uniformbuffer);
	prime_UniformbufferSetData(ren->uniformbuffer, &matrix, sizeof(prime_Mat4));
}

static void
initSprites(prime_Renderer2D* ren)
{
	prime_BufferLayout* layout = nullptr;
	layout = prime_BufferLayoutCreate();
	prime_BufferElementAdd(layout, prime_BufferElementCreate(prime_DataTypeFloat2));

	f32 vertices[] = {
		 0.0f,   0.0f,
		 50.0f,  0.0f,
		 50.0f,  50.0f,
		 0.0f,   50.0f
	};

	u32 indices[] = { 0, 1, 2, 2, 3, 0 };

	ren->spriteData.vertexbuffer = prime_VertexbufferCreate(
		ren->device,
		nullptr,
		sizeof(vertices),
		prime_VertexbufferTypeDynamic
	);

	prime_BufferLayoutSet(ren->spriteData.vertexbuffer, layout);

	ren->spriteData.indexbuffer = prime_IndexbufferCreate(
		ren->device, indices, 6);

	prime_VertexbufferSetData(ren->spriteData.vertexbuffer, vertices, sizeof(vertices));

	ren->spriteData.shader = prime_ShaderCreate(ren->device,
		s_SpriteVertexSource, s_SpritePixelSource, false);

	prime_ShaderBind(ren->spriteData.shader);
	prime_BufferLayoutDestroy(layout);
}

prime_Renderer2D*
prime_Renderer2DCreate(prime_Device* device, prime_Window* window)
{
	prime_Renderer2D* ren = (prime_Renderer2D*)prime_MemAlloc(sizeof(prime_Renderer2D));
	ren->context = prime_ContextCreate(device, window);
	ren->viewport.width = prime_WindowGetWidth(window);
	ren->viewport.height = prime_WindowGetHeight(window);
	ren->device = device;
	initSprites(ren);
	prime_ContextMakeActive(ren->context);

	ren->uniformbuffer = prime_UniformbufferCreate(device, sizeof(prime_Mat4), 0);
	setProjectionMatrix(ren);

	return ren;
}

void
prime_Renderer2DDestroy(prime_Renderer2D* renderer2d)
{
	PRIME_ASSERT_MSG(renderer2d, "Renderer2D is null");

	prime_ContextDestroy(renderer2d->context);
	prime_VertexbufferDestroy(renderer2d->spriteData.vertexbuffer);
	prime_IndexbufferDestroy(renderer2d->spriteData.indexbuffer);
	prime_ShaderDestroy(renderer2d->spriteData.shader);
	prime_UniformbufferDestroy(renderer2d->uniformbuffer);
	renderer2d->device = nullptr;
	renderer2d->context = nullptr;
	renderer2d->uniformbuffer = nullptr;
	renderer2d->spriteData.indexbuffer = nullptr;
	renderer2d->spriteData.vertexbuffer = nullptr;
	renderer2d->spriteData.shader = nullptr;
	prime_MemFree(renderer2d, sizeof(prime_Renderer2D));
}

void
prime_Renderer2DSetClearColor(prime_Renderer2D* renderer2d, const prime_Color& color)
{
	PRIME_ASSERT_MSG(renderer2d, "Renderer2D is null");
	prime_ContextSetClearColor(renderer2d->context, color);
}

void
prime_Renderer2DSetVsync(prime_Renderer2D* renderer2d, b8 vsync)
{
	PRIME_ASSERT_MSG(renderer2d, "Renderer2D is null");
	prime_ContextSetVsync(renderer2d->context, vsync);
}

void
prime_Renderer2DSetViewport(prime_Renderer2D* renderer2d, const prime_Viewport& viewport)
{
	PRIME_ASSERT_MSG(renderer2d, "Renderer2D is null");
	renderer2d->viewport = viewport;
	prime_ContextSetViewport(renderer2d->context, &viewport);
}

void
prime_Renderer2DClear(prime_Renderer2D* renderer2d)
{
	PRIME_ASSERT_MSG(renderer2d, "Renderer2D is null");
	prime_ContextClear(renderer2d->context);
}

void
prime_Renderer2DBegin(prime_Renderer2D* renderer2d)
{

}

void
prime_Renderer2DEnd(prime_Renderer2D* renderer2d)
{
	PRIME_ASSERT_MSG(renderer2d, "Renderer2D is null");
	prime_ContextDrawIndexed(renderer2d->context, prime_DrawModeTriangles, 6);
}

void
prime_Renderer2DPresent(prime_Renderer2D* renderer2d)
{
	PRIME_ASSERT_MSG(renderer2d, "Renderer2D is null");
	prime_ContextSwapbuffers(renderer2d->context);
}

const prime_Viewport&
prime_Renderer2DGetViewport(prime_Renderer2D* renderer2d)
{
	PRIME_ASSERT_MSG(renderer2d, "Renderer2D is null");
	return renderer2d->viewport;
}