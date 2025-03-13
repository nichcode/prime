
#include "prime/prime.h"

using namespace prime;
using namespace prime::core;
using namespace prime::renderer;
using namespace prime::maths;

b8 renderer2dTest()
{
    Scope<Window> window = Platform::createWindow("Renderer2DTest", 640, 480);
    Scope<RendererAPI> rendererAPI = Platform::createAPI(GraphicsAPIGL, window);
    rendererAPI->setClearColor({ .2f, .2f, .2f, 1.0f });
    rendererAPI->setVsync(true);

    Renderer2D renderer;
    renderer.init(rendererAPI);
    renderer.setDrawColor(PRIME_COLOR_GREEN);

    Camera2D camera;
    camera.setProjection(640, 480);

    Ref<Texture> texture = rendererAPI->loadTexture("textures/texture2d.png");
    f32 rotation = 0.0f;

    Rect rect;
    rect = Rect(100.0f, 0.0f, 50.0f, 50.0f);
    Sprite sprite;
    sprite = Sprite(200.0f, 0.0f, 50.0f, 50.0f, texture);

    while (!window->shouldClose()) {
        Window::pollEvents();

        rendererAPI->clear();
        rotation += 2.0f;

        renderer.setCamera(camera);

        renderer.draw({ 0.0f, 0.0f });
        renderer.draw({ 200.0f, 200.0f }, { 100.0f, 100.0f }, texture, false, true);

        renderer.draw({ 100.0f, 200.0f }, { 50.0f, 50.0f }, rotation);
        renderer.draw({ 300.0f, 300.0f }, { 100.0f, 100.0f }, texture, 45.0f);

        rect.render(renderer);
        sprite.render(renderer);

        renderer.flush();

        rendererAPI->present();
    }

    return PRIME_TRUE;
}

std::vector<Rect> getHits(Rect& rect, std::vector<Rect>& walls)
{
    std::vector<Rect> collisions;
    for (auto wall : walls) {
        if (rect.collide(wall)) {
            collisions.push_back(wall);
        }
    }
    return collisions;
}

void checkCollisionsX(Rect& rect, vec2 vel, std::vector<Rect>& walls)
{
    std::vector<Rect> collisions = getHits(rect, walls);
    for (Rect& wall : collisions) {
        if (vel.x > 0.0f) {
            // moving right
            rect.position.x = wall.position.x - rect.size.x;
        }
        else if (vel.x < 0.0f) {
            // moving right
            rect.position.x = wall.position.x + wall.size.x;
        }
    }
}

void checkCollisionsY(Rect& rect, vec2 vel, std::vector<Rect>& walls)
{
    std::vector<Rect> collisions = getHits(rect, walls);
    for (Rect& wall : collisions) {
        if (vel.y > 0.0f) {
            // moving down
            rect.position.y = wall.position.y - rect.size.y;
        }
        else if (vel.y < 0.0f) {
            // moving up
            rect.position.y = wall.position.y + wall.size.y;
        }
    }
}

b8 collisionTest()
{
    Scope<Window> window = Platform::createWindow("CollisionTest", 640, 480);
    Scope<RendererAPI> rendererAPI = Platform::createAPI(GraphicsAPIGL, window);
    rendererAPI->setClearColor({ .2f, .2f, .2f, 1.0f });
    rendererAPI->setVsync(true);

    Renderer2D renderer;
    renderer.init(rendererAPI);

    Camera2D camera;
    camera.setProjection(640, 480);

    Ref<Texture> texture = rendererAPI->loadTexture("textures/texture2d.png");
    Sprite player(295.0f, 215.0f, 50.0f, 50.0f, texture);
    Rect& rect = player.getRect();

    std::vector<Rect> walls;
    Rect left_wall(0.0f, 0.0f, 30.0f, 480.0f);
    Rect right_wall(610.0f, 0.0f, 30.0f, 480.0f);
    Rect top_wall(0.0f, 0.0f, 640.0f, 30.0f);
    Rect botton_wall(0.0f, 450.0f, 640.0f, 30.0f);

    walls.push_back(left_wall);
    walls.push_back(right_wall);
    walls.push_back(top_wall);
    walls.push_back(botton_wall);

    f32 speed = 4.0f;
    vec2 velocity;

    while (!window->shouldClose()) {
        Window::pollEvents();

        velocity.x = 0.0f;
        velocity.y = 0.0f;
        renderer.setDrawColor(PRIME_COLOR_BLUE);

        if (window->getKeyState(KeyRight)) {
            velocity.x += speed;
        }
        else if (window->getKeyState(KeyLeft)) {
            velocity.x -= speed;
        }

        else if (window->getKeyState(KeyUp)) {
            velocity.y -= speed;
        }

        else if (window->getKeyState(KeyDown)) {
            velocity.y += speed;
        }

        rect.position.x += velocity.x;
        checkCollisionsX(rect, velocity, walls);
        rect.position.y += velocity.y;
        checkCollisionsY(rect, velocity, walls);

        rendererAPI->clear();
        renderer.setCamera(camera);

        player.render(renderer);

        renderer.setDrawColor(PRIME_COLOR_GREEN);
        for (Rect& wall : walls) {
            wall.render(renderer);
        }

        renderer.flush();
        rendererAPI->present();
    }

    return PRIME_TRUE;
}