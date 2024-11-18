
#include "prime/forward_renderer2d.h"
#include "prime/vertex.h"
#include "shader_sources.h"

#include "platform/glm/glm.hpp"
#include "platform/glm/gtc/matrix_transform.hpp"

using namespace glm;

namespace prime {

	static vec4 s_vertices[4]{};
	static vec2 s_tex_coords[4]{};
	static mat4 s_identity;

	void ForwardRenderer2D::init(Ref<Device>& device, Ref<Context>& context)
	{
		PASSERT_MSG(device.get(), "Device is null");
		PASSERT_MSG(context.get(), "Context is null");
		m_device = device;
		m_context = context;

		s_identity = mat4(1.0f);

		// sprite
		m_sprite_data.layout.add_buffer_element({ DataTypeFloat2 });
		m_sprite_data.layout.add_buffer_element({ DataTypeFloat4 });
		m_sprite_data.layout.add_buffer_element({ DataTypeFloat2 });
		m_sprite_data.layout.process_elements();

		s_vertices[0] = { 0.0f, 0.0f, 0.0f, 1.0f };
		s_vertices[1] = { 1.0f, 0.0f, 0.0f, 1.0f };
		s_vertices[2] = { 1.0f, 1.0f, 0.0f, 1.0f };
		s_vertices[3] = { 0.0f, 1.0f, 0.0f, 1.0f };

		s_tex_coords[0] = { 0.0f, 1.0f };
		s_tex_coords[1] = { 1.0f, 1.0f };
		s_tex_coords[2] = { 1.0f, 0.0f };
		s_tex_coords[3] = { 0.0f, 0.0f };

		m_sprite_data.shader = m_device->create_shader(
			sprite_vertex_shader_source_f,
			sprite_pixel_shader_source_f,
			false);

		m_projetion_buffer = m_device->create_uniformbuffer(sizeof(mat4), 0);

		m_white_texture = device->create_texture2d(TextureProperties());

		u32 indices[6] = { 0, 1, 2, 2, 3, 0 };

		m_sprite_data.vertexbuffer = m_device->create_vertexbuffer(
			nullptr,
			4 * sizeof(SpriteVertexF),
			VertexbufferTypeDynamic);
		m_sprite_data.vertexbuffer->bind();
		m_sprite_data.vertexbuffer->set_layout(m_sprite_data.layout);
		m_sprite_data.vertexbuffer_base = new SpriteVertexF[4];

		m_sprite_data.indexbuffer = m_device->create_indexbuffer(indices, 6);
		m_sprite_data.indexbuffer->bind();

		m_sprite_data.vertexbuffer_ptr = m_sprite_data.vertexbuffer_base;
	}

	void ForwardRenderer2D::destroy()
	{
		delete[] m_sprite_data.vertexbuffer_base;
	}

	void ForwardRenderer2D::draw(const Rect2D& rect, const Color& color)
	{
		mat4 transform = translate(s_identity, glm::vec3(rect.x, rect.y, 0.0f))
			* glm::scale(s_identity, glm::vec3(rect.width, rect.height, 1.0f));

		for (size_t i = 0; i < 4; i++)
		{
			// pos
			vec2 position = transform * s_vertices[i];
			m_sprite_data.vertexbuffer_ptr->pos.x = position.x;
			m_sprite_data.vertexbuffer_ptr->pos.y = position.y;

			// color
			m_sprite_data.vertexbuffer_ptr->color.r = color.r;
			m_sprite_data.vertexbuffer_ptr->color.g = color.g;
			m_sprite_data.vertexbuffer_ptr->color.b = color.b;
			m_sprite_data.vertexbuffer_ptr->color.a = color.a;

			// texture_coords
			m_sprite_data.vertexbuffer_ptr->texture_coords.u = s_tex_coords[i].x;
			m_sprite_data.vertexbuffer_ptr->texture_coords.v = s_tex_coords[i].y;

			m_sprite_data.vertexbuffer_ptr++;
		}
		flush_sprites(m_white_texture);
	}

	void ForwardRenderer2D::draw(const Rect2D& rect, Ref<Texture2D>& texture)
	{
		mat4 transform = translate(s_identity, glm::vec3(rect.x, rect.y, 0.0f))
			* glm::scale(s_identity, glm::vec3(rect.width, rect.height, 1.0f));

		for (size_t i = 0; i < 4; i++)
		{
			// pos
			vec2 position = transform * s_vertices[i];
			m_sprite_data.vertexbuffer_ptr->pos.x = position.x;
			m_sprite_data.vertexbuffer_ptr->pos.y = position.y;

			// color
			m_sprite_data.vertexbuffer_ptr->color.r = 1.0f;
			m_sprite_data.vertexbuffer_ptr->color.g = 1.0f;
			m_sprite_data.vertexbuffer_ptr->color.b = 1.0f;
			m_sprite_data.vertexbuffer_ptr->color.a = 1.0f;

			// texture_coords
			m_sprite_data.vertexbuffer_ptr->texture_coords.u = s_tex_coords[i].x;
			m_sprite_data.vertexbuffer_ptr->texture_coords.v = s_tex_coords[i].y;

			m_sprite_data.vertexbuffer_ptr++;
		}

		if (texture.get()) { flush_sprites(texture); }
		else { flush_sprites(m_white_texture); }
	}

	void ForwardRenderer2D::draw(const Rect2D& rect, Ref<Texture2D>& texture, const Color& tint_color)
	{
		mat4 transform = translate(s_identity, glm::vec3(rect.x, rect.y, 0.0f))
			* glm::scale(s_identity, glm::vec3(rect.width, rect.height, 1.0f));

		for (size_t i = 0; i < 4; i++)
		{
			// pos
			vec2 position = transform * s_vertices[i];
			m_sprite_data.vertexbuffer_ptr->pos.x = position.x;
			m_sprite_data.vertexbuffer_ptr->pos.y = position.y;

			// color
			m_sprite_data.vertexbuffer_ptr->color.r = tint_color.r;
			m_sprite_data.vertexbuffer_ptr->color.g = tint_color.g;
			m_sprite_data.vertexbuffer_ptr->color.b = tint_color.b;
			m_sprite_data.vertexbuffer_ptr->color.a = tint_color.a;

			// texture_coords
			m_sprite_data.vertexbuffer_ptr->texture_coords.u = s_tex_coords[i].x;
			m_sprite_data.vertexbuffer_ptr->texture_coords.v = s_tex_coords[i].y;

			m_sprite_data.vertexbuffer_ptr++;
		}

		if (texture.get()) { flush_sprites(texture); }
		else { flush_sprites(m_white_texture); }
	}

	void ForwardRenderer2D::set_view(Viewport& viewport)
	{
		mat matrix = ortho(
			viewport.x,
			(f32)viewport.width,
			(f32)viewport.height,
			viewport.y,
			-1.0f,
			1.0f);

		m_projetion_buffer->bind();
		m_projetion_buffer->set_data(sizeof(mat4), &matrix);
	}
	
	void ForwardRenderer2D::flush_sprites(Ref<Texture2D>& texture)
	{
		u32 data_size = (u32)((u8*)m_sprite_data.vertexbuffer_ptr - (u8*)m_sprite_data.vertexbuffer_base);
		m_sprite_data.vertexbuffer->bind();
		m_sprite_data.vertexbuffer->set_data(m_sprite_data.vertexbuffer_base, data_size);

		texture->bind();
		m_sprite_data.shader->bind();
		m_context->draw_indexed(prime::PrimitiveTopologyTriangles, 6);

		m_sprite_data.vertexbuffer_ptr = m_sprite_data.vertexbuffer_base;
	}
}