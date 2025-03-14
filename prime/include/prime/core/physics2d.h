
#pragma once

#include "prime/defines.h"
#include "prime/renderer/rect.h"
#include <vector>

namespace prime::core {

    struct Body2DDesc
    {
        BodyType2D type = BodyType2DStatic;
        ColliderType2D collider = ColliderType2DBox;
		f32 density = 1.0f;
		f32 friction = 0.5f;
		f32 restitution = 0.0f;
		f32 restitution_threshold = 0.5f;
		b8 fixed_rotation = false;
        f32 rotation = 0.0f;
		maths::vec2 position = { 0.0f, 0.0f };
		maths::vec2 size = { 50.0f, 50.0f };
    };

    class Body2D
    {
    private:
        void* m_Handle = nullptr;
        maths::vec2 m_Position;
        maths::vec2 m_Size;
        f32 m_Rotation = 0.0f;

        friend class Physics2D;

    public:
        void setVelocity(const maths::vec2& velocity);

        const maths::vec2& getPosition() const { return m_Position; }
        const maths::vec2& getSize() const { return m_Size; }
        f32 getRotation() const { return m_Rotation; }
    }; 

    class Physics2D
    {
    private:
        void* m_World;
        std::vector<Body2D*> m_Bodies;
        maths::vec2 m_Gravity;

    public:
        Physics2D() : m_World(nullptr) {}
        ~Physics2D() { destroy(); }

        void init(const maths::vec2& gravity = { 0.0f, 9.8f });
        void destroy();

        Body2D createBody(const Body2DDesc& desc);
        void addBody(Body2D* body);

        void step(f32 delta_time);

        const maths::vec2& getGravity() const { return m_Gravity; }
    };    
    
} // namespace prime::core
