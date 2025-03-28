
#include "prime/context.h"
#include "pch.h"
#include "prime/window.h"

#include "opengl/opengl_context.h"

struct primeContext
{
    void* handle = nullptr;
    primeView view;

    void(*destroy)(void* handle) = nullptr;
    void(*present)(void* handle) = nullptr;
    void(*bind)(void* handle) = nullptr;
    void(*unbind)(void* handle) = nullptr;
    void(*clear)(void* handle) = nullptr;
    void(*setblend)(void* handle, primeBlendMode blend) = nullptr;
    void(*setVsync)(void* handle, b8 vsync) = nullptr;
    void(*color)(void* handle, f32 r, f32 g, f32 b, f32 a) = nullptr;
    void(*setView)(void* handle, const primeView* view) = nullptr;
    void(*submit)(void* handle, primeDrawType type, primeDrawMode mode, u32 count) = nullptr;
    void(*submitInsd)(void* handle, primeDrawType type, primeDrawMode mode,
                        u32 count, u32 ins_count) = nullptr;

};

primeContext* primeCreateContext(primeWindow* window)
{
    primeContext* context = new primeContext();
    context->view.size = primeGetWindowSize(window);

    switch (s_InitData.type) {
        case primeDeviceTypes_OpenGL: {
            context->handle = _glCreateContext(window);
            context->clear = _glClear;
            context->destroy = _glDestroyContext;
            context->bind = _glBindContext;
            context->unbind = _glUnbindContext;
            context->present = _glPresent;
            context->setVsync = _glSetVsync;
            context->setblend = _glSetBlendMode;
            context->color = _glSetClearColor;
            context->setView = _glSetView;
            context->submit = _glSubmit;
            context->submitInsd = _glSubmitInstanced;

            return context;
            break;
        }
    } // switch

    s_InitData.contexts.push_back(context);
    return context;
}

void primeDestroyContext(primeContext* context)
{
    PRIME_ASSERT_MSG(context, "context is null");
    auto it = std::find(s_InitData.contexts.begin(), s_InitData.contexts.end(), context);
    if (it != s_InitData.contexts.end()) {
        s_InitData.contexts.erase(it); 
    }
    _primeDeleteContext(context);
}

void _primeDeleteContext(primeContext* context)
{
    PRIME_ASSERT_MSG(context, "context is null");
    if (s_InitData.activeContext == context) {
        context->unbind(context->handle);
        s_InitData.activeContext = nullptr;
    }
    context->destroy(context->handle);
    delete context;
    context = nullptr;
}

void primeClear(primeContext* context)
{
    PRIME_ASSERT_MSG(context, "context is null");
    context->clear(context->handle);
}

void primePresent(primeContext* context)
{
    PRIME_ASSERT_MSG(context, "context is null");
    context->present(context->handle);
}

void primeBindContext(primeContext* context)
{
    PRIME_ASSERT_MSG(context, "context is null");
    if (s_InitData.activeContext == nullptr || s_InitData.activeContext != context) {
        context->bind(context->handle);
        s_InitData.activeContext = context;
    }
}

void primeUnbindContext(primeContext* context)
{
    PRIME_ASSERT_MSG(context, "context is null");
    if (s_InitData.activeContext == context) {
        context->unbind(context->handle);
        s_InitData.activeContext = nullptr;
    }
}

void primeSubmit(primeContext* context, primeDrawType type, primeDrawMode mode, u32 count)
{
    PRIME_ASSERT_MSG(context, "context is null");
    context->submit(context->handle, type, mode, count);
}

void primeSubmitInstanced(primeContext* context, primeDrawType type, primeDrawMode mode, u32 count, u32 instance_count)
{
    PRIME_ASSERT_MSG(context, "context is null");
    context->submitInsd(context->handle, type, mode, count, instance_count);
}

void primeSetVsync(primeContext* context, b8 vsync)
{
    PRIME_ASSERT_MSG(context, "context is null");
    context->setVsync(context->handle, vsync);
}

void primeSetBlendMode(primeContext* context, primeBlendMode blend)
{
    PRIME_ASSERT_MSG(context, "context is null");
    context->setblend(context->handle, blend);
}

void primeSetClearColor(primeContext* context, const primeVec4 color)
{
    PRIME_ASSERT_MSG(context, "context is null");
    context->color(context->handle, color.x, color.y, color.z, color.w);
}

void primeSetClearColori(primeContext* context, const primeVec4i color)
{
    PRIME_ASSERT_MSG(context, "context is null");
    f32 fr = (f32)color.x / 255.0f;
    f32 fg = (f32)color.y / 255.0f;
    f32 fb = (f32)color.z / 255.0f;
    f32 fa = (f32)color.w / 255.0f;
    context->color(context->handle, fr, fg, fb, fa);
}

void primeSetView(primeContext* context, const primeView view)
{
    PRIME_ASSERT_MSG(context, "context is null");
    context->view =  view;
    context->setView(context->handle, &context->view);
}

primeView primeGetView(primeContext* context)
{
    PRIME_ASSERT_MSG(context, "context is null");
    return context->view;
}