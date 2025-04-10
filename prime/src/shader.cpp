
#include "pch.h"
#include "prime/shader.h"

prShader* prCreateShader(prContext* context, prShaderDesc desc)
{
    prShader* shader = new prShader();
    PR_ASSERT(shader, "failed to create shader");
    shader->context = context;
    shader->handle = context->api.createShader(desc);
    shader->layout = desc.layout;
    shader->layoutSent = false;

    context->data.shaders.push_back(shader);
    return shader;
}

void prDestroyShader(prShader* shader)
{
    PR_ASSERT(shader, "shader is null");
    prContext* context = shader->context;

    auto it = std::find(context->data.shaders.begin(), context->data.shaders.end(), shader);
    if (it != context->data.shaders.end()) {
        context->data.shaders.erase(it); 
    }

    if (context->state.activeShader == shader) {
        context->state.activeShader = nullptr;
    }
    context->api.destroyShader(shader->handle);
    delete shader;
    shader = nullptr;
}

void prBindShader(prShader* shader)
{
    PR_ASSERT(shader, "shader is null");
    prContext* context = shader->context;

    if (context->state.activeShader != shader) {
        context->state.activeShader = shader;
        context->api.bindShader(shader->handle);
        if (!shader->layoutSent) {
            context->api.setLayout(shader->handle, &shader->layout);
            shader->layoutSent = true;
        }
    }
}

void prSetInt(const char* name, i32 data)
{
    PR_ASSERT(s_ActiveContext, "no context bound");
    PR_ASSERT(s_ActiveContext->state.activeShader, "no shader bound");
    s_ActiveContext->api.setInt(s_ActiveContext->state.activeShader->handle, name, data);
}

void prSetIntArray(const char* name, i32* data, u32 count) 
{
    PR_ASSERT(s_ActiveContext, "no context bound");
    PR_ASSERT(s_ActiveContext->state.activeShader, "no shader bound");
    s_ActiveContext->api.setIntArray(s_ActiveContext->state.activeShader->handle, name, data, count);
}

void prSetFloat(const char* name, f32 data)
{
    PR_ASSERT(s_ActiveContext, "no context bound");
    PR_ASSERT(s_ActiveContext->state.activeShader, "no shader bound");
    s_ActiveContext->api.setFloat(s_ActiveContext->state.activeShader->handle, name, data);
}

void prSetFloat2(const char* name, f32 data, f32 data2)
{
    PR_ASSERT(s_ActiveContext, "no context bound");
    PR_ASSERT(s_ActiveContext->state.activeShader, "no shader bound");
    s_ActiveContext->api.setFloat2(s_ActiveContext->state.activeShader->handle, name, data, data2);
}

void prSetFloat3(const char* name, f32 data, f32 data2, f32 data3)
{
    PR_ASSERT(s_ActiveContext, "no context bound");
    PR_ASSERT(s_ActiveContext->state.activeShader, "no shader bound");
    s_ActiveContext->api.setFloat3(s_ActiveContext->state.activeShader->handle, name, data, data2, data3);
}

void prSetFloat4(const char* name, f32 data, f32 data2, f32 data3, f32 data4)
{
    PR_ASSERT(s_ActiveContext, "no context bound");
    PR_ASSERT(s_ActiveContext->state.activeShader, "no shader bound");
    s_ActiveContext->api.setFloat4(s_ActiveContext->state.activeShader->handle, name, data, data2, data3, data4);
}

void prSetMat4(const char* name, f32* data)
{
    PR_ASSERT(s_ActiveContext, "no context bound");
    PR_ASSERT(s_ActiveContext->state.activeShader, "no shader bound");
    s_ActiveContext->api.setMat4(s_ActiveContext->state.activeShader->handle, name, data);
}