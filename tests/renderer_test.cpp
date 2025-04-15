
#include "prime/prime.h"

struct Data
{
    prRenderer* renderer;
    prCamera* camera;
};

void onWindowResize(prWindow* window, u32 width, u32 height)
{
    Data* data = (Data*)prGetUserData();
    prViewport view;
    view.width = width;
    view.height = height;
    prSetView(view);

    data->camera->view = view;
}

int main(int argc, char** argv)
{
    prInit();

    u32 flags = prWindowFlags_Center | prWindowFlags_Show;
    prWindow* window = prCreateWindow("window", 640, 480, flags);

    prContextDesc desc;
    desc.type = prContextTypes_OpenGL;
    desc.major = 3;
    desc.minor = 3;
    prContext* context = prCreateContext(window, desc);
    prMakeActive(context);
    prSetVsync(true);

    prRenderer* renderer = prCreateRenderer();

    prCamera camera;
    camera.view = { 0.0f, 0.0f, 640.0f, 480.0f };
    camera.rotation = 0.0f;

    prTexture* texture = prLoadTexture("textures/texture2d.png");
    prFont* font = prLoadFont("fonts/font.ttf", 30);

    Data data;
    data.camera = &camera;
    data.renderer = renderer;
    prSetUserData(&data);
    prSetWindowResizedCallback(onWindowResize);

    f32 rotation = 0.0f;
   
    while (!prWindowShouldClose(window)) {
        prPullEvents();

        prClear({ .2f, .2f, .2f, 1.0f });
        prSetRendererCamera(renderer, camera); 
        rotation += 4.0f;

        prRendererDrawText(renderer, 0.0f, 0.0f, 1.0f, "Text Rendering", font, { 1.0f, 1.0f, 0.0f, 1.0f });
        prRendererDrawText(renderer, 200.0f, 0.0f, 1.0f, "Prime", font, { 1.0f, 1.0f, 0.0f, 1.0f });

        prRect red;
        red.x = 100.0f;
        red.y = camera.view.height / 3.0f;
        red.w = 70.0f;
        red.h = 70.0f;
        prRendererDrawRectEx(renderer, red, rotation, prAnchors_Center, PR_RED);

        prRect green;
        green.x = 300.0f;
        green.y = camera.view.height / 2.0f;
        green.w = 70.0f;
        green.h = 70.0f;
        prRendererDrawRect(renderer, green, PR_GREEN);

        prRect non_scalable;
        non_scalable.x = camera.view.width - 70.0f;
        non_scalable.y = 30.0f;
        non_scalable.w = 70.0f;
        non_scalable.h = 70.0f;
        prRendererDrawRect(renderer, non_scalable, PR_GREEN);

        prRect blue;
        blue.x = 500.0f;
        blue.y = camera.view.height / 3.0f;
        blue.w = 70.0f;
        blue.h = 70.0f;
        prRendererDrawRectEx(renderer, blue, rotation, prAnchors_Center, PR_BLUE);

        prRect tex_x;
        tex_x.x = 100.0f;
        tex_x.y = camera.view.height - camera.view.height / 3.0f;
        tex_x.w = 70.0f;
        tex_x.h = 70.0f;
        prRendererDrawTextureEx(renderer, tex_x, 0.0f, prAnchors_Center, texture, PR_WHITE, prFlips_Horizontal);

        prRect tex;
        tex.x = 300.0f;
        tex.y = camera.view.height - camera.view.height / 3.0f;
        tex.w = 70.0f;
        tex.h = 70.0f;
        prRendererDrawTexture(renderer, tex, texture);

        prRect tex_xy;
        tex_xy.x = 500.0f;
        tex_xy.y = camera.view.height - camera.view.height / 3.0f;
        tex_xy.w = 70.0f;
        tex_xy.h = 70.0f;
        prRendererDrawTextureEx(renderer, tex_xy, 0.0f, prAnchors_Center, texture, PR_WHITE, prFlips_Horizontal | prFlips_Vertical);

        prRendererFlush(renderer);
        prSwapBuffers(); 
    }

    prSetWindowResizedCallback(nullptr);
    prDestroyRenderer(renderer);
    prDestroyContext(context);
    prDestroyWindow(window);
    prShutdown();
    return 0;
}