
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
}
