
#include "prime/pr_context.h"
#include "prime/pr_log.h"

#include "pr_types.h"
#include "windows/pr_wglcontext.h"
#include "glad/glad.h"

static u32 s_Major = 0, s_Minor = 0;

PrContext*
prContextCreate(PrDevice* device, PrWindow* window)
{
	PR_ASSERT_MSG(device, "Device is null");
	PR_ASSERT_MSG(window, "Window is null");

	PrContext* context = (PrContext*)prMemAlloc(sizeof(PrContext));
	context->device = device;
	context->window = window;
	s_Major = GLVersion.major;
	s_Minor = GLVersion.minor;

#ifdef PR_PLATFORM_WINDOWS
	context->handle = prWGLContextCreate(window->handle);
#endif // PR_PLATFORM_WINDOWS

	PR_ASSERT_MSG(context, "Context creation failed");

	device->contexts.emplace_back(context);
	if (device->contexts.size() == 1) {
		device->activeContext = context;
	}

	window->context = context->handle;
	return context;
}

void
prContextDestroy(PrContext* context)
{
	PR_ASSERT_MSG(context, "Context is null");
	prWGLContextDestroy(context->handle);

	if (context->device->activeContext) {
		if (context->device->activeContext == context) {
			context->device->activeContext = nullptr;
		}
	}
	prMemFree(context, sizeof(PrContext));
	context = nullptr;
}

void
prContextSwapbuffers(PrDevice* device)
{
	PR_ASSERT_MSG(device, "Device is null");
#ifdef PR_PLATFORM_WINDOWS
	SwapBuffers(GetDC(device->activeContext->window->handle));
#endif // PR_PLATFORM_WINDOWS
}

void
prContextSetClearColor(PrContext* context, const PrColor& color)
{
	PR_ASSERT_MSG(context, "Context is null");
	context->color = color;
}

void
prContextClear(PrDevice* device)
{
	PR_ASSERT_MSG(device, "Device is null");
	const PrColor& color = device->activeContext->color;
	glClearColor(color.r, color.g, color.b, color.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}