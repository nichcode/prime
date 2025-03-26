
#include "prime/layout.h"
#include "pch.h"

#include "opengl/opengl_layout.h"

struct primeLayout
{
    void* handle = nullptr;

    void(*destroy)(void* handle) = nullptr;
    void(*add)(void* handle, primeDataType type, u32 divisor, b8 normalize) = nullptr;
    void(*bind)(void* handle) = nullptr;
    void(*unbind)(void* handle) = nullptr;
};

primeLayout* primeCreateLayout()
{
    primeLayout* layout = new primeLayout();
    switch (s_InitData.type) {
        case primeDeviceTypes_OpenGL: {
            layout->handle = _glCreateLayout();
            layout->destroy = _glDestroyLayout;
            layout->add = _glAddAttrib;
            layout->bind = _glBindLayout;
            layout->unbind = _glUnbindLayout;
            break;
        } 
    }
    s_InitData.layouts.push_back(layout);
    return layout;
}

void primeDestroyLayout(primeLayout* layout)
{
    PRIME_ASSERT_MSG(layout, "layout is null");
    auto it = std::find(s_InitData.layouts.begin(), s_InitData.layouts.end(), layout);
    if (it != s_InitData.layouts.end()) {
        s_InitData.layouts.erase(it); 
    }
    _primeDeleteLayout(layout);
}

void _primeDeleteLayout(primeLayout* layout)
{
    if (s_InitData.activeLayout == layout) {
        layout->unbind(layout->handle);
        s_InitData.activeLayout = nullptr;
    }
    layout->destroy(layout->handle);
    delete layout;
    layout = nullptr;
}

void primeBindLayout(primeLayout* layout)
{
    PRIME_ASSERT_MSG(layout, "layout is null");
    if (s_InitData.activeLayout == nullptr || s_InitData.activeLayout != layout) {
        layout->bind(layout->handle);
        s_InitData.activeLayout = layout;
    }
}

void primeUnbindLayout(primeLayout* layout)
{
    PRIME_ASSERT_MSG(layout, "layout is null");
    if (s_InitData.activeLayout == layout) {
        layout->unbind(layout->handle);
        s_InitData.activeLayout = nullptr;
    }
}

void primeAddAttrib(primeLayout* layout, primeDataType type, u32 divisor, b8 normalize)
{
    PRIME_ASSERT_MSG(layout, "layout is null");
    layout->add(layout->handle, type, divisor, normalize);
}
