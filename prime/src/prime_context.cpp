
#include "pch.h"
#include "prime/prime.h"

struct prime_context
{
    prime_window* window;
    void* handle = nullptr;
};

prime_context* prime_create_context(prime_window* window)
{
    PRIME_ASSERT_MSG(window, "window is nullptr");
    PRIME_ASSERT_MSG(!prime_HasContext(window), "window already has context");

    prime_context* context;
    context = new prime_context();
    PRIME_ASSERT_MSG(context, "failed to create context");

    context->handle = s_Data.api.createContext(prime_get_window_handle(window));
    prime_SetContext(window, context);
    return context;
}

void prime_destroy_context(prime_context* context)
{
    PRIME_ASSERT_MSG(context, "context is null");
    if (s_Data.activeContext == context) {
        s_Data.activeContext = nullptr;
    }
    s_Data.api.destroyContext(context->handle);
    delete context;
    context = nullptr;
}

void prime_swap_buffers()
{
    PRIME_ASSERT_MSG(s_Data.activeContext, "active context not set");
    s_Data.api.swapBuffers(s_Data.activeContext->handle);
}

void prime_clear()
{
    PRIME_ASSERT_MSG(s_Data.activeContext, "active context not set");
    s_Data.api.clear(s_Data.activeContext->handle);
}

void prime_make_active(prime_context* context)
{
    PRIME_ASSERT_MSG(context, "context is null");
    s_Data.activeContext = context;
    s_Data.api.makeActive(context->handle);
}

void prime_set_vsync(b8 vsync)
{
    PRIME_ASSERT_MSG(s_Data.activeContext, "active context not set");
    s_Data.api.setVsync(s_Data.activeContext->handle, vsync);
}

void prime_set_clear_color(prime_vec4 color)
{
    PRIME_ASSERT_MSG(s_Data.activeContext, "active context not set");
    s_Data.api.setClearColor(s_Data.activeContext->handle, color);
}

void prime_set_clear_colori(prime_vec4i color)
{
    PRIME_ASSERT_MSG(s_Data.activeContext, "active context not set");
    f32 fr = (f32)color.x / 255.0f;
    f32 fg = (f32)color.y / 255.0f;
    f32 fb = (f32)color.z / 255.0f;
    f32 fa = (f32)color.w / 255.0f;
    prime_vec4 fcolor = { fr, fg, fb, fa };
    s_Data.api.setClearColor(s_Data.activeContext->handle, fcolor);
}

void prime_submit_arrays(u32 mode, u32 count)
{
    PRIME_ASSERT_MSG(s_Data.activeContext, "active context not set");
    s_Data.api.submitArrays(s_Data.activeContext->handle, mode, count);
}

void prime_submit_elements(u32 mode, u32 count)
{
    PRIME_ASSERT_MSG(s_Data.activeContext, "active context not set");
    s_Data.api.submitElements(s_Data.activeContext->handle, mode, count);
}

void prime_submit_layout(prime_layout* layout)
{
    PRIME_ASSERT_MSG(layout, "layout is null");
    PRIME_ASSERT_MSG(s_Data.activeContext, "active context not set");
    s_Data.api.submitLayout(s_Data.activeContext->handle, layout);
}