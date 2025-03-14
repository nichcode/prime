
#include "prime/prime.h"

using namespace prime;
using namespace prime::core;
using namespace prime::renderer;
using namespace prime::maths;

b8 physics2dTest()
{
    Scope<Window> window = Platform::createWindow("Physics2DTest", 640, 480);
    Scope<RendererAPI> rendererAPI = Platform::createAPI(GraphicsAPIGL, window);
    rendererAPI->setClearColor({ .2f, .2f, .2f, 1.0f });
    rendererAPI->setVsync(true);

    Renderer2D renderer;
    renderer.init(rendererAPI);
    renderer.setDrawColor(PRIME_COLOR_GREEN);

    Camera2D camera;
    camera.setProjection(640, 480);

    Physics2D physics_world;
    physics_world.init();

    Body2DDesc player_desc;
    player_desc.type = BodyType2DDynamic;
    player_desc.position.x = 295.0f;
    player_desc.position.y = 215.0f;
    Body2D player = physics_world.createBody(player_desc);

    Body2DDesc left_wall_desc;
    left_wall_desc.position.x = 0.0f;
    left_wall_desc.position.y = 0.0f;
    left_wall_desc.size.x = 30.0f;
    left_wall_desc.size.y = 480.0f;
    Body2D left_wall = physics_world.createBody(left_wall_desc);

    Body2DDesc right_wall_desc;
    right_wall_desc.position.x = 610.0f;
    right_wall_desc.position.y = 0.0f;
    right_wall_desc.size.x = 30.0f;
    right_wall_desc.size.y = 480.0f;
    Body2D right_wall = physics_world.createBody(right_wall_desc);

    Body2DDesc bottom_wall_desc;
    bottom_wall_desc.position.x = 0.0f;
    bottom_wall_desc.position.y = 450.0f;
    bottom_wall_desc.size.x = 640.0f;
    bottom_wall_desc.size.y = 30.0f;
    Body2D bottom_wall = physics_world.createBody(bottom_wall_desc);

    physics_world.addBody(&player);
    physics_world.addBody(&left_wall);
    physics_world.addBody(&bottom_wall);

    maths::vec2 velocity;
    velocity.y = physics_world.getGravity().y;

    while (!window->shouldClose()) {
        Window::pollEvents();

        // move
        velocity.x = 0.0f;
        if (window->getKeyState(KeyRight)) {
            velocity.x = 15.0f;
        }
        else if (window->getKeyState(KeyLeft)) {
            velocity.x = -15.0f;
        }
        player.setVelocity(velocity);

        rendererAPI->clear();

        physics_world.step(1.0f / 60.0f);

        renderer.setCamera(camera);
        renderer.setDrawColor(PRIME_COLOR_RED);
        renderer.draw(player.getPosition(), player.getSize());

        renderer.setDrawColor(PRIME_COLOR_GREEN);
        renderer.draw(left_wall.getPosition(), left_wall.getSize());
        renderer.draw(right_wall.getPosition(), right_wall.getSize());
        renderer.draw(bottom_wall.getPosition(), bottom_wall.getSize());
        renderer.flush();

        rendererAPI->present();
    }

    return PRIME_TRUE;
}

b8 physics2dSceneTest()
{
    using namespace prime::scene;

    Scope<Window> window = Platform::createWindow("Physics2DSceneTest", 640, 480);
    Scope<RendererAPI> rendererAPI = Platform::createAPI(GraphicsAPIGL, window);
    rendererAPI->setClearColor({ .2f, .2f, .2f, 1.0f });
    rendererAPI->setVsync(true);

    Renderer2D renderer;
    renderer.init(rendererAPI);
    renderer.setDrawColor(PRIME_COLOR_GREEN);

    Ref<Scene2D> scene = SceneManager::createScene2D();
    Entity player = scene->createEntity();
    player.addComponent<SpriteRenderer>().color = PRIME_COLOR_BLUE;
    player.addComponent<RigidBody2D>().type = BodyType2DDynamic;
    player.addComponent<BoxCollider2D>();

    Transform& player_tc = player.getComponent<Transform>();
    player_tc.position.x = 400.0f;
    player_tc.position.y = 300.0f;
    player_tc.scale.x = 1.0f;
    player_tc.scale.y = 1.0f;

    // left wall
    Entity left_wall = scene->createEntity();
    left_wall.addComponent<SpriteRenderer>().color = PRIME_COLOR_GREEN;
    left_wall.addComponent<RigidBody2D>();
    left_wall.addComponent<BoxCollider2D>();

    Transform& left_wall_tc = left_wall.getComponent<Transform>();
    left_wall_tc.position.x = 0.0f;
    left_wall_tc.position.y = 0.0f;
    left_wall_tc.scale.x = 0.6f;
    left_wall_tc.scale.y = 9.6f;

    // right wall
    Entity right_wall = scene->createEntity();
    right_wall.addComponent<SpriteRenderer>().color = PRIME_COLOR_GREEN;
    right_wall.addComponent<RigidBody2D>();
    right_wall.addComponent<BoxCollider2D>();

    Transform& right_wall_tc = right_wall.getComponent<Transform>();
    right_wall_tc.position.x = 610.0f;
    right_wall_tc.position.y = 0.0f;
    right_wall_tc.scale.x = 0.6f;
    right_wall_tc.scale.y = 9.6f;

    // bottom wall
    Entity bottom_wall = scene->createEntity();
    bottom_wall.addComponent<SpriteRenderer>().color = PRIME_COLOR_GREEN;
    bottom_wall.addComponent<RigidBody2D>();
    bottom_wall.addComponent<BoxCollider2D>();

    Transform& bottom_wall_tc = bottom_wall.getComponent<Transform>();
    bottom_wall_tc.position.x = 0.0f;
    bottom_wall_tc.position.y = 450.0f;
    bottom_wall_tc.scale.x = 12.8f;
    bottom_wall_tc.scale.y = 0.6f;

    maths::vec2 velocity;
    velocity.y = 9.8f;
    scene->initPhysics();

    RigidBody2D& player_rb = player.getComponent<RigidBody2D>();

    while (!window->shouldClose()) {
        Window::pollEvents();

        // move
        velocity.x = 0.0f;
        if (window->getKeyState(KeyRight)) {
            velocity.x = 15.0f;
        }
        else if (window->getKeyState(KeyLeft)) {
            velocity.x = -15.0f;
        }

        player_rb.setVelocity(velocity);
        rendererAPI->clear();

        scene->stepPhysics();
        scene->render(renderer);
        renderer.flush();

        rendererAPI->present();
    }

    return PRIME_TRUE;
}