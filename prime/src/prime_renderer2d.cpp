
#include "prime/prime_renderer2d.h"
#include "prime/prime_window.h"
#include "prime/prime_log.h"
#include "prime/prime_buffers.h"
#include "prime/prime_shader.h"
#include "prime/prime_context.h"
#include "prime_shader_sources.h"

struct SpriteVertex
{
	prime_Vec2 position;
};

struct SpriteData
{
	prime_Vertexbuffer* vertexbuffer = nullptr;
	prime_Indexbuffer* indexbuffer = nullptr;
	prime_Shader* shader = nullptr;
	u32 indexCount = 0;
	prime_Vec4 vertices[4];

	SpriteVertex* vertexbufferBase = nullptr;
	SpriteVertex* vertexbufferPtr = nullptr;
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

	u32 max_indices = PRIME_MAX_RENDERER2D_SPRITES * 6;
	u32 max_vertices = PRIME_MAX_RENDERER2D_SPRITES * 4;

	u32* indices = (u32*)prime_MemAlloc(sizeof(u32) * max_indices);
	u32 offset = 0;
	for (u32 i = 0; i < max_indices; i += 6)
	{
		indices[i + 0] = offset + 0;
		indices[i + 1] = offset + 1;
		indices[i + 2] = offset + 2;

		indices[i + 3] = offset + 2;
		indices[i + 4] = offset + 3;
		indices[i + 5] = offset + 0;

		offset += 4;
	}

	ren->spriteData.vertexbuffer = prime_VertexbufferCreate(
		ren->device,
		nullptr,
		max_vertices * sizeof(SpriteVertex),
		prime_VertexbufferTypeDynamic
	);

	prime_BufferLayoutSet(ren->spriteData.vertexbuffer, layout);
	ren->spriteData.vertexbufferBase = (SpriteVertex*)prime_MemAlloc(sizeof(SpriteVertex) * max_vertices);

	ren->spriteData.indexbuffer = prime_IndexbufferCreate(
		ren->device, indices, max_indices);

	ren->spriteData.shader = prime_ShaderCreate(ren->device,
		s_SpriteVertexSource, s_SpritePixelSource, false);

	ren->spriteData.vertices[0] = prime_Vec4Create(0.0f, 0.0f, 0.0f, 1.0f);
	ren->spriteData.vertices[1] = prime_Vec4Create(1.0f, 0.0f, 0.0f, 1.0f);
	ren->spriteData.vertices[2] = prime_Vec4Create(1.0f, 1.0f, 0.0f, 1.0f);
	ren->spriteData.vertices[3] = prime_Vec4Create(0.0f, 1.0f, 0.0f, 1.0f);

	prime_ShaderBind(ren->spriteData.shader);
	prime_BufferLayoutDestroy(layout);

	prime_MemFree(indices, sizeof(u32) * max_indices);
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
	prime_MemFree(renderer2d->spriteData.vertexbufferBase,
		sizeof(SpriteVertex) * PRIME_MAX_RENDERER2D_SPRITES * 4);

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
	renderer2d->spriteData.indexCount = 0;
	renderer2d->spriteData.vertexbufferPtr = renderer2d->spriteData.vertexbufferBase;
}

void
prime_Renderer2DEnd(prime_Renderer2D* renderer2d)
{
	PRIME_ASSERT_MSG(renderer2d, "Renderer2D is null");
	if (renderer2d->spriteData.indexCount)
	{
		u32 data_size = (u32)((u8*)renderer2d->spriteData.vertexbufferPtr - (u8*)renderer2d->spriteData.vertexbufferBase);
		prime_VertexbufferSetData(
			renderer2d->spriteData.vertexbuffer,
			renderer2d->spriteData.vertexbufferBase,
			data_size);

		prime_ContextDrawIndexed(
			renderer2d->context, prime_DrawModeTriangles, 
			renderer2d->spriteData.indexCount);
	}
}

void
prime_Renderer2DDrawRect(prime_Renderer2D* renderer2d, prime_Rect2D rect)
{
	prime_Mat4 translation = prime_Mat4Translation({ rect.x, rect.y, 0.0f });
	prime_Mat4 scale = prime_Mat4Scale({ rect.width, rect.height, 1.0f });
	prime_Mat4 transform = translation * scale;

	for (size_t i = 0; i < 4; i++)
	{
		prime_Vec4 position = transform * renderer2d->spriteData.vertices[i];
		renderer2d->spriteData.vertexbufferPtr->position.x = position.x;
		renderer2d->spriteData.vertexbufferPtr->position.y = position.y;

		renderer2d->spriteData.vertexbufferPtr++;
	}
	renderer2d->spriteData.indexCount += 6;
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