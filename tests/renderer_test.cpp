
#include "PAL/PAL.h"

struct Data
{
    PAL_Renderer* renderer;
    PAL_Camera* camera;
};

void onWindowResize(PAL_Window* window, u32 width, u32 height)
{
    Data* data = (Data*)PAL_GetUserData();
    PAL_Viewport view;
    view.width = width;
    view.height = height;
    PAL_SetViewport(view);

    data->camera->view = view;
}

int main(int argc, char** argv)
{
    PAL_Init();

    u32 flags = PAL_WindowFlags_Center | PAL_WindowFlags_Show;
    PAL_Window* window = PAL_CreateWindow("window", 640, 480, flags);

    PAL_ContextDesc desc;
    desc.type = PAL_ContextTypes_OpenGL;
    desc.major = 3;
    desc.minor = 3;
    PAL_Context* context = PAL_CreateContext(window, desc);
    PAL_MakeActive(context);
    PAL_SetVsync(true);

    PAL_Renderer* renderer = PAL_CreateRenderer();

    PAL_Camera camera;
    camera.view = { 0.0f, 0.0f, 640.0f, 480.0f };
    camera.rotation = 0.0f;

    PAL_Texture* texture = PAL_LoadTexture("textures/texture2d.png");
    PAL_Font* font = PAL_LoadFont("fonts/font.ttf", 30);

    Data data;
    data.camera = &camera;
    data.renderer = renderer;
    PAL_SetUserData(&data);
    PAL_SetWindowResizedCallback(onWindowResize);

    f32 rotation = 0.0f;
   
    while (!PAL_WindowShouldClose(window)) {
        PAL_PullEvents();

        PAL_Clear({ .2f, .2f, .2f, 1.0f });
        PAL_SetRendererCamera(renderer, camera); 
        rotation += 4.0f;

        PAL_RendererDrawText(renderer, 0.0f, 0.0f, 1.0f, "Text Rendering", font, { 1.0f, 1.0f, 0.0f, 1.0f });
        PAL_RendererDrawText(renderer, 200.0f, 0.0f, 1.0f, "PAL", font, { 1.0f, 1.0f, 0.0f, 1.0f });

        PAL_Rect red;
        red.x = 100.0f;
        red.y = camera.view.height / 3.0f;
        red.w = 70.0f;
        red.h = 70.0f;
        PAL_RendererDrawRectEx(renderer, red, rotation, PAL_Anchors_Center, PAL_RED);

        PAL_Rect green;
        green.x = 300.0f;
        green.y = camera.view.height / 2.0f;
        green.w = 70.0f;
        green.h = 70.0f;
        PAL_RendererDrawRect(renderer, green, PAL_GREEN);

        PAL_Rect non_scalable;
        non_scalable.x = camera.view.width - 70.0f;
        non_scalable.y = 30.0f;
        non_scalable.w = 70.0f;
        non_scalable.h = 70.0f;
        PAL_RendererDrawRect(renderer, non_scalable, PAL_GREEN);

        PAL_Rect blue;
        blue.x = 500.0f;
        blue.y = camera.view.height / 3.0f;
        blue.w = 70.0f;
        blue.h = 70.0f;
        PAL_RendererDrawRectEx(renderer, blue, rotation, PAL_Anchors_Center, PAL_BLUE);

        PAL_Rect tex_x;
        tex_x.x = 100.0f;
        tex_x.y = camera.view.height - camera.view.height / 3.0f;
        tex_x.w = 70.0f;
        tex_x.h = 70.0f;
        PAL_RendererDrawTextureEx(renderer, tex_x, 0.0f, PAL_Anchors_Center, texture, PAL_WHITE, PAL_Flips_Horizontal);

        PAL_Rect tex;
        tex.x = 300.0f;
        tex.y = camera.view.height - camera.view.height / 3.0f;
        tex.w = 70.0f;
        tex.h = 70.0f;
        PAL_RendererDrawTexture(renderer, tex, texture);

        PAL_Rect tex_xy;
        tex_xy.x = 500.0f;
        tex_xy.y = camera.view.height - camera.view.height / 3.0f;
        tex_xy.w = 70.0f;
        tex_xy.h = 70.0f;
        PAL_RendererDrawTextureEx(renderer, tex_xy, 0.0f, PAL_Anchors_Center, texture, PAL_WHITE, PAL_Flips_Horizontal | PAL_Flips_Vertical);

        PAL_RendererFlush(renderer);
        PAL_SwapBuffers(); 
    }

    PAL_SetWindowResizedCallback(nullptr);
    PAL_DestroyRenderer(renderer);
    PAL_DestroyContext(context);
    PAL_DestroyWindow(window);
    PAL_Shutdown();
    return 0;
}