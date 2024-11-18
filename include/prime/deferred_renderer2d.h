#pragma once

#include "viewport.h"
#include "vertex.h"
#include "device.h"
#include "rect2d.h"
#include "color.h"

#include <array>

namespace prime {

	class DeferredRenderer2D
	{
	private:
		struct SpriteData
		{
			Ref<Vertexbuffer> vertexbuffer;
			Ref<Indexbuffer> indexbuffer;
			Ref<Shader> shader;

			VertexbufferLayout layout;
			SpriteVertex* vertexbuffer_base = nullptr;
			SpriteVertex* vertexbuffer_ptr = nullptr;

			std::array<Ref<Texture2D>, MAX_TEXTURE_SLOTS> tex_slots{};
			u32 tex_index = 1, index_count = 0;
		};

	private:
		Ref<Device> m_device;
		u32* m_indices;
		Ref<Uniformbuffer> m_projetion_buffer;
		SpriteData m_sprite_data;

	public:
		DeferredRenderer2D();

		void init(Ref<Device>& device);
		void destroy();

		void draw(const Rect2D& rect, const Color& color);
		void draw(const Rect2D& rect, Ref<Texture2D>& texture);
		void draw(const Rect2D& rect, Ref<Texture2D>& texture, const Color& tint_color);

		void set_view(Viewport& viewport);

		void flush_sprites(Ref<Context>& context);
		void flush(Ref<Context>& context);

	private:
		void LoadData(u32 sprite_max, b8 reset);
		f32 get_texture_index(Ref<Texture2D>& texture);

		void reset_sprite_batch();
	};
}