
#include "prime/scene/scene2d.h"
#include "prime_utils.h"
#include "prime/scene/components.h"
#include "prime_utils.h"
#include "prime/maths/maths.h"

#define SIZE 50

namespace prime::scene {

    void RigidBody2D::setVelocity(const maths::vec2& velocity)
    {
        if (m_Body) {
            b2Body* body = (b2Body*)m_Body;
            body->SetLinearVelocity({ velocity.x, velocity.y });
        }
    }

    Scene2D::Scene2D()
    {
        m_Handle = new SceneHandle();
        u32 id = (u32)m_Handle->registry.create();
        Entity camera_entity = { id, m_Handle };
		camera_entity.addComponent<Transform>();
		camera_entity.addComponent<Camera2DComponent>().camera.setProjection(0.0f, 0.0f, 640.0f, 480.0f);
		m_MainCamera2D = id;
    }
    
    Scene2D::~Scene2D()
    {
        auto entities = m_Handle->registry.view<Transform>();
		for (entt::entity entity : entities)
		{
			m_Handle->registry.destroy(entity);
		}

        if (m_World) {
            delete (b2World*)m_World;
            m_World = nullptr;
        }
        delete m_Handle;
    }
    
    Entity Scene2D::createEntity()
    {
        u32 id = (u32)m_Handle->registry.create();
        Entity entity(id, m_Handle);
		entity.addComponent<Transform>();
		return entity;
    }
    
    void Scene2D::deleteEntity(Entity entity)
    {
        entt::entity id = (entt::entity)entity.getHandle();
        m_Handle->registry.destroy(id);
    }

    void Scene2D::initPhysics()
    {
        b2World* world = new b2World({ 0.0f, 9.8f });
        m_World = world;

        auto physics_entities = m_Handle->registry.view<RigidBody2D>();
		for (entt::entity entityID : physics_entities) {
            u32 id = (u32)entityID;
			Entity entity = { id, m_Handle };
			auto& transform = entity.getComponent<Transform>();
			auto& rb = entity.getComponent<RigidBody2D>();

            b2BodyDef body_def;
            body_def.type = core::getBodyType(rb.type);
            maths::vec2 middle;
            middle.x = transform.position.x + (transform.scale.x * SIZE) / 2.0f;
            middle.y = transform.position.y + (transform.scale.y * SIZE) / 2.0f;
            body_def.position.x = middle.x * (1.0f / PRIME_P2M);
            body_def.position.y = middle.y * (1.0f / PRIME_P2M);
            body_def.angle = maths::toRadians(transform.rotation.z);

            b2Body* body = world->CreateBody(&body_def);
            body->SetFixedRotation(rb.fixed_rotation);
            rb.m_Body = body;

			// box collider
			if (entity.hasComponent<BoxCollider2D>()) {
				auto& bc = entity.getComponent<BoxCollider2D>();
                b2PolygonShape box_shape;
                f32 width = (bc.size.x * transform.scale.x) * (1.0f / PRIME_P2M);
                f32 height = (bc.size.y * transform.scale.y) * (1.0f / PRIME_P2M);
                maths::vec2 offset;
                offset.x = bc.offset.x * (1.0f / PRIME_P2M);
                offset.y = bc.offset.y * (1.0f / PRIME_P2M);

                box_shape.SetAsBox(width / 2.0f, height / 2.0f, { offset.x, offset.y }, 0.0f);
                b2FixtureDef fixture_def;
                fixture_def.shape = &box_shape;
                fixture_def.density = rb.density;
                fixture_def.friction = rb.friction;
                fixture_def.restitution = rb.restitution;
                fixture_def.restitutionThreshold = rb.restitution_threshold;
                body->CreateFixture(&fixture_def);
			}
        }
    }

    void Scene2D::stepPhysics(f32 delta_time)
    {
        const i32 velocity_iter = 6;
		const i32 position_iter = 2;

		b2World* world = (b2World*)m_World;
		world->Step(delta_time, velocity_iter, position_iter);

		auto physics_entities = m_Handle->registry.view<RigidBody2D>();
		for (entt::entity entityID : physics_entities)
		{
            u32 id = (u32)entityID;
			Entity entity = { id, m_Handle };
			auto& transform = entity.getComponent<Transform>();
            auto& rb = entity.getComponent<RigidBody2D>();
			b2Body* body = (b2Body*)rb.m_Body;

            const auto& position = body->GetPosition();
			transform.position.x = position.x * PRIME_P2M;
			transform.position.y = position.y * PRIME_P2M;

            transform.position.x -= (transform.scale.x * SIZE) / 2.0f;
            transform.position.y -= (transform.scale.y * SIZE) / 2.0f;
			transform.rotation.z = body->GetAngle();
		}

    }
    
    void Scene2D::render(renderer::Renderer2D& renderer)
    {
        Entity camera_entity;
        if (m_Handle->registry.size() > 0) {

            camera_entity = Entity(m_MainCamera2D, m_Handle);
            renderer::Camera2D& camera = camera_entity.getComponent<Camera2DComponent>().camera;
            renderer.setCamera(camera);

            // renderer
            auto sprites = m_Handle->registry.view<Transform, SpriteRenderer>();
            for (entt::entity sprite : sprites) {
                auto [tc, sr] = sprites.get<Transform, SpriteRenderer>(sprite);
                renderer.setDrawColor(sr.color);
                if (sr.texture.get()) {
                    renderer.draw({ tc.position.x, tc.position.y }, { tc.scale.x * 50.0f, tc.scale.y * 50.0f }, sr.texture);
                }
                else {
                    renderer.draw({ tc.position.x, tc.position.y }, { tc.scale.x * 50.0f, tc.scale.y * 50.0f });
                }
            }
        }
    }

} // namespace prime::scene
