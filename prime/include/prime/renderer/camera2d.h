
#pragma once

#include "prime/maths/mat4.h"

namespace prime::renderer {

    class Camera2D
    {
    private:
        maths::mat4 m_ViewMatrix;
        maths::mat4 m_ProjectionMatrix;
        maths::mat4 m_ViewProjectionMatrix;
        maths::vec2 m_Position;
        f32 m_Rotation;

    public:
        Camera2D();
        
        void setProjection(f32 x, f32 y, f32 width, f32 height);
        void setProjection(f32 width, f32 height);

        void setPosition(const maths::vec2& position);
        void setRotation(const f32 rotation);

        const maths::vec2& getPosition() { return m_Position; }
        const f32 getRotation() { return m_Rotation; }

        const maths::mat4 getViewMatrix() const { return m_ViewProjectionMatrix; }
        const maths::mat4 getViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
        const maths::mat4 getProjectionMatrix() const { return m_ViewProjectionMatrix; }

    private:
        void calculateMatrix();
    };
    
} // namespace prime::renderer
