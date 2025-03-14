
#pragma once

#include "prime/renderer/color.h"
#include "prime/renderer/camera2d.h"
#include "prime/maths/vec3.h"
#include "prime/core/ref.h"
#include "prime/renderer/texture.h"
#include "prime/renderer/camera2d.h"

namespace prime::scene {

	struct Transform
	{
		maths::vec3 position = maths::vec3(0.0f, 0.0f, 0.0f);
		maths::vec3 scale = maths::vec3(1.0f, 1.0f, 1.0f);
		maths::vec3 rotation = maths::vec3(0.0f);
	};

    struct SpriteRenderer
	{
		renderer::Color color = renderer::Color(1.0f, 1.0f, 1.0f, 1.0f);
		core::Ref<renderer::Texture> texture;
	};

	struct Camera2DComponent
	{
		renderer::Camera2D camera;
	};

	struct RigidBody2D
	{
	private:
		void* m_Body = nullptr;
		friend class Scene2D;

	public:
		BodyType2D type = BodyType2DStatic;
		f32 density = 1.0f;
		f32 friction = 0.5f;
		f32 restitution = 0.0f;
		f32 restitution_threshold = 0.5f;
		b8 fixed_rotation = false;
        f32 rotation = 0.0f;

		void setVelocity(const maths::vec2& velocity);
	};

	struct BoxCollider2D
	{
		maths::vec2 offset = { 0.0f, 0.0f };
		maths::vec2 size = { 50.0f, 50.0f };
	};
}
