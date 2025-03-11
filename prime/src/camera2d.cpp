
#include "prime/renderer/camera2d.h"
#include "prime/maths/maths.h"

namespace prime::renderer {

    Camera2D::Camera2D()
    {
        m_ViewMatrix = maths::mat4::identity();
        m_ProjectionMatrix = maths::mat4::identity();
        m_ViewProjectionMatrix = maths::mat4::identity();
        m_Position = maths::vec2(0.0f);
        m_Rotation = 0.0f;
    }

    void Camera2D::setProjection(f32 x, f32 y, f32 width, f32 height)
    {
        m_ProjectionMatrix = maths::mat4::orthographic(x, width, height, y, -1.0f, 1.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void Camera2D::setProjection(f32 width, f32 height)
    {
        m_ProjectionMatrix = maths::mat4::orthographic(0.0f, width, height, 0.0f, -1.0f, 1.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void Camera2D::setPosition(const maths::vec2& position)
    {
        m_Position = position;
        calculateMatrix();
    }
    
    void Camera2D::setRotation(const f32 rotation)
    {
        m_Rotation = rotation;
        calculateMatrix();
    }

    void Camera2D::calculateMatrix()
    {
        maths::mat4 transform = maths::mat4::translate({ m_Position.x, m_Position.y }) *
            maths::mat4::rotateZ(maths::toRadians(m_Rotation));

		m_ViewMatrix = maths::mat4::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }
    
} // namespace prime::renderer
