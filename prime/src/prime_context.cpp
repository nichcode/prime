
#include "pch.h"
#include "prime/prime.h"

struct prime_context
{
    prime_window* window;
    void* handle = nullptr;
    prime_view view;
};

prime_context* prime_create_context(prime_window* window)
{
    PRIME_ASSERT_MSG(window, "window is nullptr");
    PRIME_ASSERT_MSG(!prime_HasContext(window), "window already has context");

    prime_context* context;
    context = new prime_context();
    PRIME_ASSERT_MSG(context, "failed to create context");

    context->handle = s_Data.api.createContext(prime_get_window_handle(window));
    prime_vec2u window_size = prime_get_window_size(window);

    context->view.x = 0.0f;
    context->view.y = 0.0f;
    context->view.width = (f32)window_size.x;
    context->view.height = (f32)window_size.y;
    prime_SetContext(window, context);

    s_Data.contexts.push_back(context);
    return context;
}

void prime_destroy_context(prime_context* context)
{
    PRIME_ASSERT_MSG(context, "context is null");
    auto it = std::find(s_Data.contexts.begin(), s_Data.contexts.end(), context);
    if (it != s_Data.contexts.end()) {
        s_Data.contexts.erase(it); 
    }
    prime_DestroyContext(context);
}

void prime_swap_buffers()
{
    PRIME_ASSERT_MSG(s_Data.activeContext, "no context bound");
    s_Data.api.swapBuffers(s_Data.activeContext->handle);
}

void prime_clear()
{
    PRIME_ASSERT_MSG(s_Data.activeContext, "no context bound");
    s_Data.api.clear(s_Data.activeContext->handle);
}

void prime_make_active(prime_context* context)
{
    PRIME_ASSERT_MSG(context, "context is null");
    s_Data.activeContext = context;
    s_Data.api.makeActive(context->handle);

    if (!s_Data.renderDataInit) {
        prime_InitSprites();
        s_Data.renderDataInit = true;
    }
}

void prime_set_vsync(b8 vsync)
{
    PRIME_ASSERT_MSG(s_Data.activeContext, "no context bound");
    s_Data.api.setVsync(s_Data.activeContext->handle, vsync);
}

void prime_set_clear_color(prime_vec4 color)
{
    PRIME_ASSERT_MSG(s_Data.activeContext, "no context bound");
    s_Data.api.setClearColor(s_Data.activeContext->handle, color);
}

void prime_set_clear_colori(prime_vec4i color)
{
    PRIME_ASSERT_MSG(s_Data.activeContext, "no context bound");
    f32 fr = (f32)color.x / 255.0f;
    f32 fg = (f32)color.y / 255.0f;
    f32 fb = (f32)color.z / 255.0f;
    f32 fa = (f32)color.w / 255.0f;
    prime_vec4 fcolor = { fr, fg, fb, fa };
    s_Data.api.setClearColor(s_Data.activeContext->handle, fcolor);
}

void prime_submit_arrays(u32 mode, u32 count)
{
    PRIME_ASSERT_MSG(s_Data.activeContext, "no context bound");
    s_Data.api.submitArrays(s_Data.activeContext->handle, mode, count);
}

void prime_submit_elements(u32 mode, u32 count)
{
    PRIME_ASSERT_MSG(s_Data.activeContext, "no context bound");
    s_Data.api.submitElements(s_Data.activeContext->handle, mode, count);
}

void prime_submit_layout(prime_layout* layout)
{
    PRIME_ASSERT_MSG(layout, "layout is null");
    PRIME_ASSERT_MSG(s_Data.activeContext, "no context bound");
    s_Data.api.submitLayout(s_Data.activeContext->handle, layout);
}

void prime_submit_arrays_instanced(u32 mode, u32 count, u32 instance_count)
{
    PRIME_ASSERT_MSG(s_Data.activeContext, "no context bound");
    s_Data.api.submitArraysInstanced(s_Data.activeContext->handle, mode, count, instance_count);
}

void prime_submit_elements_instanced(u32 mode, u32 count, u32 instance_count)
{
    PRIME_ASSERT_MSG(s_Data.activeContext, "no context bound");
    s_Data.api.submitElementsInstanced(s_Data.activeContext->handle, mode, count, instance_count);
}

void prime_set_view(prime_view view)
{
    PRIME_ASSERT_MSG(s_Data.activeContext, "no context bound");
    s_Data.api.setView(s_Data.activeContext->handle, view);
    s_Data.activeContext->view = view;
}

prime_view prime_get_view()
{
    PRIME_ASSERT_MSG(s_Data.activeContext, "no context bound");
    return s_Data.activeContext->view;
}

void prime_DestroyContext(prime_context* context)
{
    if (s_Data.activeContext == context) {
        s_Data.activeContext = nullptr;
    }
    s_Data.api.destroyContext(context->handle);
    delete context;
    context = nullptr;
}
