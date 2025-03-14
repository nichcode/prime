
#include "prime/core/physics2d.h"
#include "prime/maths/maths.h"
#include "box2d/box2d.h"

#define P2M 30.0f

namespace prime::core {

    PRIME_INLINE b2BodyType getBodyType(BodyType2D type)
	{
		switch (type) {
            case BodyType2DStatic:    return b2_staticBody; break;
            case BodyType2DDynamic:   return b2_dynamicBody; break;
            case BodyType2DKinematic: return b2_kinematicBody; break;
		}
		return b2_staticBody;
	}

    // body
    void Body2D::setVelocity(const maths::vec2& velocity)
    {
        b2Body* body = (b2Body*)m_Handle;
        body->SetLinearVelocity({ velocity.x, velocity.y });
    }

    void Physics2D::init(const maths::vec2& gravity)
    {
        b2World* world = new b2World({ gravity.x, gravity.y });
        m_Gravity = gravity;
        m_World = world;
    }

    void Physics2D::destroy()
    {
        if (m_World) {
            m_Bodies.clear();
            delete (b2World*)m_World;
            m_World = nullptr;
        }
    }

    Body2D Physics2D::createBody(const Body2DDesc& desc)
    {
        b2World* world = (b2World*)m_World;

        b2BodyDef body_def;
        body_def.type = getBodyType(desc.type);
        maths::vec2 middle;
        middle.x = desc.position.x + desc.size.x / 2.0f;
        middle.y = desc.position.y + desc.size.y / 2.0f;
        body_def.position.x = middle.x * (1.0f / P2M);
        body_def.position.y = middle.y * (1.0f / P2M);
        body_def.angle = maths::toRadians(desc.rotation);

        b2Body* body = world->CreateBody(&body_def);
        body->SetFixedRotation(desc.fixed_rotation);
        if (desc.collider == ColliderType2DBox) {
            b2PolygonShape box_shape;
            f32 width = desc.size.x * (1.0f / P2M);
            f32 height = desc.size.y * (1.0f / P2M);
            box_shape.SetAsBox(width / 2.0f, height / 2.0f);
            b2FixtureDef fixture_def;
            fixture_def.shape = &box_shape;
            fixture_def.density = desc.density;
            fixture_def.friction = desc.friction;
            fixture_def.restitution = desc.restitution;
            fixture_def.restitutionThreshold = desc.restitution_threshold;
            body->CreateFixture(&fixture_def);
        }
        Body2D physics_body;
        physics_body.m_Handle = body;
        physics_body.m_Position = desc.position;
        physics_body.m_Size = desc.size;
        physics_body.m_Rotation = body_def.angle;
        return physics_body;
    }

    void Physics2D::addBody(Body2D* body)
    {
        m_Bodies.push_back(body);
    }

    void Physics2D::step(f32 delta_time)
    {
        const i32 velocity_iter = 6;
		const i32 position_iter = 2;

		b2World* world = (b2World*)m_World;
		world->Step(delta_time, velocity_iter, position_iter);

        for (Body2D* body2d : m_Bodies) {
            b2Body* body = (b2Body*)body2d->m_Handle;

			const auto& position = body->GetPosition();
			body2d->m_Position.x = position.x  * P2M;
			body2d->m_Position.y = position.y * P2M;

            body2d->m_Position.x -= body2d->m_Size.x / 2.0f;
            body2d->m_Position.y -= body2d->m_Size.y / 2.0f;
			body2d->m_Rotation = body->GetAngle();
        }
    }
    
} // namespace prime::core
