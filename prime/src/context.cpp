
#include "prime/context.h"
#include "pch.h"

#include "opengl/opengl_context.h"

struct primeBuffer
{
    primeContext* context = nullptr;
    void* handle = nullptr;
    primeBufferType type;
    primeBufferUsage usage;
};

struct primeShader
{
    primeContext* context = nullptr;
    void* handle = nullptr;
    primeShaderSourceType source_type = PRIME_SHADER_SOURCE_TYPE_GLSL;
};

struct primeLayout
{
    primeContext* context = nullptr;
    void* handle = nullptr;
};

struct primeContext
{
    void* handle = nullptr;
    primeView view;

    std::vector<primeBuffer*> buffers;
    std::vector<primeShader*> shaders;
    std::vector<primeLayout*> layouts;

    void(*destroy)(void* handle) = nullptr;
    void(*present)(void* handle) = nullptr;
    void(*make)(void* handle) = nullptr;
    void(*clear)(void* handle) = nullptr;
    void(*setVsync)(void* handle, b8 vsync) = nullptr;
    void(*color)(void* handle, f32 r, f32 g, f32 b, f32 a) = nullptr;
    void(*setView)(void* handle, primeView* view) = nullptr;
    void(*submit)(void* handle, primeDrawType type, primeDrawMode mode, u32 count) = nullptr;
    void(*submitInsd)(void* handle, primeDrawType type, primeDrawMode mode, u32 count, u32 ins_count) = nullptr;

    // buffer
    void*(*createBuffer)(primeBufferDesc desc) = nullptr;
    void(*destroyBuffer)(void* handle) = nullptr;
    void(*setBuffer)(void* handle) = nullptr;
    void(*setData)(void* handle, const void* data, u32 size) = nullptr;

    // shader
    void*(*createShader)(primeShaderDesc desc) = nullptr;
    void(*destroyShader)(void* handle) = nullptr;
    void(*setShader)(void* handle) = nullptr;
    void(*setInt)(void* handle, const char* name, i32 data) = nullptr;
    void(*setIntArray)(void* handle, const char* name, i32* data, u32 count) = nullptr;
    void(*setFloat)(void* handle, const char* name, f32 data) = nullptr;
    void(*setFloat2)(void* handle, const char* name, primeVec2 data) = nullptr;
    void(*setFloat3)(void* handle, const char* name, primeVec3 data) = nullptr;
    void(*setFloat4)(void* handle, const char* name, primeVec4 data) = nullptr;
    void(*setMat2)(void* handle, const char* name, primeMat2 data) = nullptr;
    void(*setMat3)(void* handle, const char* name, primeMat3 data) = nullptr;
    void(*setMat4)(void* handle, const char* name, primeMat4 data) = nullptr;

    // layouts
    void*(*createLayout)() = nullptr;
    void(*destroyLayout)(void* handle) = nullptr;
    void(*addAttrib)(void* handle, primeDataType type, u32 divisor, b8 normalize) = nullptr;
    void(*setLayout)(void* handle) = nullptr;
};

primeContext* primeCreateContext(primeWindow* window)
{
    primeContext* context = new primeContext();
    context->view.size = *primeGetWindowSize(window);

    switch (s_InitData.type) {
        case PRIME_DEVICE_TYPE_OPENGL: {
            context->handle = glCreateContext(window);
            context->clear = _glClear;
            context->destroy = glDestroyContext;
            context->make = glMakeActive;
            context->present = glPresent;
            context->setVsync = glSetVsync;
            context->color = glSetClearColor;

            // buffer
            context->createBuffer = glCreateBuffer;
            context->destroyBuffer = glDestroyBuffer;
            context->setBuffer = glSetBuffer;
            context->setData = glSetData;
            context->submit = glSubmit;
            context->submitInsd = glSubmitInstanced;

            // shader
            context->createShader = _glCreateShader;
            context->destroyShader = glDestroyShader;
            context->setShader = glSetShader;
            context->setInt = glSetInt;
            context->setIntArray = glSetIntArray;
            context->setFloat = glSetFloat;
            context->setFloat2 = glSetFloat2;
            context->setFloat3 = glSetFloat3;
            context->setFloat4 = glSetFloat4;
            context->setMat2 = glSetMat2;
            context->setMat3 = glSetMat3;
            context->setMat4 = glSetMat4;

            // layout
            context->createLayout = glCreateLayout;
            context->destroyLayout = glDestroyLayout;
            context->addAttrib = glAddAttrib;
            context->setLayout = glSetLayout;

            return context;
            break;
        }
    } // switch

    return context;
}

void primeDestroyContext(primeContext* context)
{
    PRIME_ASSERT_MSG(context, "context is null");
    context->destroy(context->handle);

    // buffers
    for (primeBuffer* buffer : context->buffers) {
        context->destroyBuffer(buffer->handle);
        delete buffer;
        buffer = nullptr;
    }

    // shaders
    for (primeShader* shader : context->shaders) {
        context->destroyShader(shader->handle);
        delete shader;
        shader = nullptr;
    }

    // layouts
    for (primeLayout* layout : context->layouts) {
        context->destroyLayout(layout->handle);
        delete layout;
        layout = nullptr;
    }

    context->buffers.clear();
    context->shaders.clear();
    context->layouts.clear();
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

void primeSubmit(primeContext* context, primeDrawType type,
                          primeDrawMode mode, u32 count)
{
    PRIME_ASSERT_MSG(context, "context is null");
    context->submit(context->handle, type, mode, count);
}

void primeSubmitInstanced(primeContext* context, primeDrawType type,
                            primeDrawMode mode, u32 count, u32 instance_count)
{
    PRIME_ASSERT_MSG(context, "context is null");
    context->submitInsd(context->handle, type, mode, count, instance_count);
}

void primeSetVsync(primeContext* context, b8 vsync)
{
    PRIME_ASSERT_MSG(context, "context is null");
    context->setVsync(context->handle, vsync);
}

void primeSetClearColor(primeContext* context, const primeVec4 color)
{
    PRIME_ASSERT_MSG(context, "context is null");
    context->color(context->handle, color.x, color.y, color.z, color.w);
}

void primeSetClearColori(primeContext* context, const primeVec4u color)
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

const primeView* primeGetView(primeContext* context)
{
    PRIME_ASSERT_MSG(context, "context is null");
    return &context->view;
}

primeBuffer* primeCreateBuffer(primeContext* context, primeBufferDesc desc)
{
    PRIME_ASSERT_MSG(context, "context is null");
    primeBuffer* buffer = new primeBuffer();
    buffer->type = desc.type;
    buffer->usage = desc.usage;
    buffer->context = context;
    buffer->handle = context->createBuffer(desc);
    context->buffers.push_back(buffer);
    return buffer;
}

void primeDestroyBuffer(primeBuffer* buffer)
{
    PRIME_ASSERT_MSG(buffer, "buffer is null");

    auto it = std::find(buffer->context->buffers.begin(), buffer->context->buffers.end(), buffer);
    if (it != buffer->context->buffers.end()) {
        buffer->context->buffers.erase(it); 
    }

    buffer->context->destroyBuffer(buffer->handle);
    delete buffer;
    buffer = nullptr;
}

primeShader* primeCreateShader(primeContext* context, primeShaderDesc desc)
{
    PRIME_ASSERT_MSG(context, "context is null");
    primeShader* shader = new primeShader();
    shader->source_type = desc.source_type;
    shader->context = context;
    shader->handle = context->createShader(desc);
    context->shaders.push_back(shader);
    return shader;
}

void primeDestroyShader(primeShader* shader)
{
    PRIME_ASSERT_MSG(shader, "shader is null");

    auto it = std::find(shader->context->shaders.begin(), shader->context->shaders.end(), shader);
    if (it != shader->context->shaders.end()) {
        shader->context->shaders.erase(it); 
    }

    shader->context->destroyShader(shader->handle);
    delete shader;
    shader = nullptr;
}

primeLayout* primeCreateLayout(primeContext* context)
{
    primeLayout* layout = new primeLayout();
    layout->context = context;
    layout->handle = context->createLayout();
    context->layouts.push_back(layout);
    return layout;
}

void primeDestroyLayout(primeLayout* layout)
{
    PRIME_ASSERT_MSG(layout, "layout is null");

    auto it = std::find(layout->context->layouts.begin(), layout->context->layouts.end(), layout);
    if (it != layout->context->layouts.end()) {
        layout->context->layouts.erase(it); 
    }

    layout->context->destroyLayout(layout->handle);
    delete layout;
    layout = nullptr;
}

void primeSetData(primeBuffer* buffer, const void* data, u32 size)
{
    PRIME_ASSERT_MSG(buffer, "buffer is null");
    if (buffer->usage == PRIME_BUFFER_USAGE_DYNAMIC) {
        buffer->context->setData(buffer->handle, data, size);
    }
}

void primeAddAttrib(primeLayout* layout, primeDataType type, u32 divisor, b8 normalize)
{
    PRIME_ASSERT_MSG(layout, "layout is null");
    layout->context->addAttrib(layout->handle, type, divisor, normalize);
}

void primeSetInt(primeShader* shader, const char* name, i32 data)
{
    PRIME_ASSERT_MSG(shader, "shader is null");
    shader->context->setInt(shader->handle, name, data);
}

void primeSetIntArray(primeShader* shader, const char* name, i32* data, u32 count)
{
    PRIME_ASSERT_MSG(shader, "shader is null");
    shader->context->setIntArray(shader->handle, name, data, count);
}

void primeSetFloat(primeShader* shader, const char* name, f32 data)
{
    PRIME_ASSERT_MSG(shader, "shader is null");
    shader->context->setFloat(shader->handle, name, data);
}

void primeSetFloat2(primeShader* shader, const char* name, primeVec2 data)
{
    PRIME_ASSERT_MSG(shader, "shader is null");
    shader->context->setFloat2(shader->handle, name, data);
}

void primeSetFloat3(primeShader* shader, const char* name, primeVec3 data)
{
    PRIME_ASSERT_MSG(shader, "shader is null");
    shader->context->setFloat3(shader->handle, name, data);
}

void primeSetFloat4(primeShader* shader, const char* name, primeVec4 data)
{
    PRIME_ASSERT_MSG(shader, "shader is null");
    shader->context->setFloat4(shader->handle, name, data);
}

void primeSetMat2(primeShader* shader, const char* name, primeMat2 data)
{
    PRIME_ASSERT_MSG(shader, "shader is null");
    shader->context->setMat2(shader->handle, name, data);
}

void primeSetMat3(primeShader* shader, const char* name, primeMat3 data)
{
    PRIME_ASSERT_MSG(shader, "shader is null");
    shader->context->setMat3(shader->handle, name, data);
}

void primeSetMat4(primeShader* shader, const char* name, primeMat4 data)
{
    PRIME_ASSERT_MSG(shader, "shader is null");
    shader->context->setMat4(shader->handle, name, data);
}

void primeSetBuffer(primeBuffer* buffer)
{
    PRIME_ASSERT_MSG(buffer, "buffer is null");
    buffer->context->setBuffer(buffer->handle);
}

void primeSetShader(primeShader* shader)
{
    PRIME_ASSERT_MSG(shader, "shader is null");
    shader->context->setShader(shader->handle);
}

void primeSetLayout(primeLayout* layout)
{
    PRIME_ASSERT_MSG(layout, "layout is null");
    layout->context->setLayout(layout->handle);
}