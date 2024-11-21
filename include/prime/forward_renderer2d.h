#pragma once

#include "viewport.h"
#include "device.h"
#include "rect2d.h"

namespace prime {

	class ForwardRenderer2D
	{
	private:
		struct SpriteData
		{
			Ref<Vertexbuffer> vertexbuffer;
			Ref<Indexbuffer> indexbuffer;
			Ref<Shader> shader;

			VertexbufferLayout layout;
			SpriteVertexF* vertexbuffer_base = nullptr;
			SpriteVertexF* vertexbuffer_ptr = nullptr;
		};

	private:
		Ref<Device> m_device;
		Ref<Context> m_context;
		Ref<Uniformbuffer> m_projetion_buffer;
		Ref<Texture2D> m_white_texture;
		SpriteData m_sprite_data;
		Viewport m_view;

	public:
		void init(Ref<Device>& device, Ref<Context>& context);
		void destroy();

		void draw(const Rect2D& rect, const Color& color);
		void draw(const Rect2D& rect, Ref<Texture2D>& texture);
		void draw(const Rect2D& rect, Ref<Texture2D>& texture, const Color& tint_color);

		void set_view(Viewport& viewport);
		void set_scale(f32 scale_x, f32 scale_y);

	private:
		void flush_sprites(Ref<Texture2D>& texture);
	};
}