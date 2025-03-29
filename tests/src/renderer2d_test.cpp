
#include "prime/prime.h"

struct UserData
{
    primeContext* context = nullptr;
    primeRenderer2D* renderer = nullptr;
};

void onResize(primeWindow* window, u32 width, u32 height)
{
    UserData* data = (UserData*)primeGetUserData();
    primeView view;
    view.size.x = width;
    view.size.y = height;
    primeSetView(data->context, view);
    if (primeIsMaximized(window)) {
        primeRenderSetView(data->renderer, view, 1.3f);
    }
    else {
        primeRenderSetView(data->renderer, view, 1.0f);
    }
}

b8 renderer2dTest(void* data)
{
    primeWindowDesc desc;
    desc.size.x = 1000;
    desc.size.y = 600;
    desc.title = "window";
    desc.flag = primeWindowFlags_Center;
    primeWindow* window = primeCreateWindow(desc);

    primeContext* context = primeCreateContext(window);
    primeSetVsync(context, true);
    primeSetClearColor(context, { .2f, .2f, .2f, 1.0f });

    primeRenderer2D* renderer = primeCreateRenderer2D(context);
    primeSetDrawColor(renderer, { 1.0f, 0.0, 0.0, 1.0f });
    primeSetTextColor(renderer, { 0.0f, 1.0f, 0.0f, 1.0f });

    primeTexture* texture = primeLoadTexture("textures/texture2d.png");
    primeFont* font = primeLoadFont("fonts/font.ttf", 30);
    primeFont* font2 = primeLoadFont("fonts/font2.ttf", 30);

    primeTexture* sheet = primeLoadTexture("textures/sheet.png");
    primeSetFontScale(renderer, 1.0f);
    primeSetTextureScale(renderer, .5f);
    f32 rotation = 0.0f;

    UserData user_data;
    user_data.context = context;
    user_data.renderer = renderer;
    primeSetUserData(&user_data);
    primeSetResizedCallback(onResize);

    while (!primeWindowShouldClose(window)) {
        primePullEvents();

        rotation += 3.0f;
        primeClear(context);

        // rects
        primeDrawRect(renderer, { 100.0f, 50.0f, 50.0f, 50.0f });
        
        primeSetAnchor(renderer, primeAnchors_TopLeft);
        primeDrawRectEx(renderer, { 100.0f, 250.0f, 50.0f, 50.0f }, rotation);
        primeSetAnchor(renderer, primeAnchors_Center);
        primeDrawRectEx(renderer, { 100.0f, 450.0f, 50.0f, 50.0f }, rotation);

        // textures
        primeSetTexture(renderer, texture);
        primeDrawTexture(renderer, { 300.0f, 50.0f });
        primeSetAnchor(renderer, primeAnchors_TopLeft);
        primeDrawTextureEx(renderer, { 300.0f, 250.0f }, rotation, primeFlips_Y);
        primeSetAnchor(renderer, primeAnchors_Center);
        primeDrawTextureEx(renderer, { 300.0f, 450.0f }, rotation, primeFlips_None);

        // texts
        primeSetFont(renderer, font);
        primeDrawText(renderer, "Text Rendering", { 500.0f, 50.0f });
        primeSetAnchor(renderer, primeAnchors_TopLeft);
        primeDrawTextEx(renderer, "Hello", { 500.0f, 250.0f }, primeFlips_X);
        primeSetFont(renderer, font2);
        primeSetAnchor(renderer, primeAnchors_Center);
        primeDrawTextEx(renderer, "Text Rendering", { 500.0f, 450.0f }, primeFlips_Y);

        // sub textures
        primeSetTexture(renderer, sheet);
        primeDrawSubTexture(renderer, 211, 941, 99, 75, { 700.0f, 50.0f });
        primeSetAnchor(renderer, primeAnchors_TopLeft);
        primeDrawSubTextureEx(renderer, 237, 377, 99, 75, { 700.0f, 250.0f }, rotation, primeFlips_Y);
        primeSetAnchor(renderer, primeAnchors_Center);
        primeDrawSubTextureEx(renderer, 247, 84, 99, 75, { 700.0f, 450.0f }, rotation, primeFlips_None);

        primeFlush(renderer);
        primePresent(context);
    }

    primeResetCallbacks();
    primeDestroyRenderer2D(renderer);
    primeDestroyContext(context);
    primeDestroyWindow(window);
    return PRIME_PASSED;
}