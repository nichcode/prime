
#include "prime/prime.h"

void onWindowResize(prWindow* window, u32 width, u32 height)
{
    prContext* context = (prContext*)prGetUserData();
    prViewport view;
    view.width = width;
    view.height = height;
    prSetView(view);
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
    camera.aspect_ratio = 1.77f;
    camera.rotation = 0.0f;
    camera.zoom = 3.0f;

    prTexture* texture = prLoadTexture("textures/texture2d.png");
    prFont* font = prLoadFont("fonts/font.ttf", 30);

    prSetWindowResizedCallback(onWindowResize);
    prSetUserData(context);
   
    while (!prWindowShouldClose(window)) {
        prPullEvents();

        prClear({ .2f, .2f, .2f, 1.0f });
        prSetRendererCamera(renderer, camera);

        prRendererDrawText(renderer, 0.0f, 0.0f, 1.0f, "Text Rendering", font, { 1.0f, 1.0f, 0.0f, 1.0f });

        prRendererDrawRect(renderer, {-1.0f, 0.0f, 0.5f, 0.5f }, { 1.0f, 0.0f, 0.0f, 1.0f });
        prRendererDrawRect(renderer, { 0.0f, 0.0f, 0.5f, 0.5f }, { 0.0f, 1.0f, 0.0f, 1.0f });
        prRendererDrawRect(renderer, { 1.0f, 0.0f, 0.5f, 0.5f }, { 0.0f, 0.0f, 1.0f, 1.0f });

        prRendererDrawTexture(renderer, { 0.0f, 0.8f, 0.5f, 0.5f }, texture);

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