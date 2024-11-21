
#include "prime/deferred_renderer2d.h"
#include "prime/vertex.h"
#include "shader_sources.h"

#include "platform/glm/glm.hpp"
#include "platform/glm/gtc/matrix_transform.hpp"

using namespace glm;

namespace prime {

	static vec4 s_vertices[4]{};
	static vec2 s_tex_coords[4]{};
	static mat4 s_identity;

	DeferredRenderer2D::DeferredRenderer2D()
	{
		m_indices = nullptr;
	}

	void DeferredRenderer2D::init(Ref<Device>& device, Ref<Context>& context)
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
		m_sprite_data.layout.add_buffer_element({ DataTypeFloat });
		m_sprite_data.layout.process_elements();

		s_vertices[0] = { 0.0f, 0.0f, 0.0f, 1.0f };
		s_vertices[1] = { 1.0f, 0.0f, 0.0f, 1.0f };
		s_vertices[2] = { 1.0f, 1.0f, 0.0f, 1.0f };
		s_vertices[3] = { 0.0f, 1.0f, 0.0f, 1.0f };

		s_tex_coords[0] = { 0.0f, 1.0f};
		s_tex_coords[1] = { 1.0f, 1.0f};
		s_tex_coords[2] = { 1.0f, 0.0f};
		s_tex_coords[3] = { 0.0f, 0.0f};

		m_sprite_data.shader = m_device->create_shader(
			sprite_vertex_shader_source,
			sprite_pixel_shader_source,
			false);

		m_projetion_buffer = m_device->create_uniformbuffer(sizeof(mat4), 0);

		i32 samplers[MAX_TEXTURE_SLOTS]{};
		for (u32 i = 0; i < MAX_TEXTURE_SLOTS; i++) { samplers[i] = i; }

		m_sprite_data.shader->bind();
		m_sprite_data.shader->set_int_array("u_textures", samplers, MAX_TEXTURE_SLOTS);

		Ref<Texture2D> texture = device->create_texture2d(TextureProperties());
		m_sprite_data.tex_slots[0] = texture;

		LoadData(20, false);
	}

	void DeferredRenderer2D::destroy()
	{
		delete[] m_indices;

		// sprite
		delete[] m_sprite_data.vertexbuffer_base;
	}

	void DeferredRenderer2D::draw(const Rect2D& rect, const Color& color)
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

			// texture_index
			m_sprite_data.vertexbuffer_ptr->texture_index.index = 0.0f;

			m_sprite_data.vertexbuffer_ptr++;
		}
		m_sprite_data.index_count += 6;
	}

	void DeferredRenderer2D::draw(const Rect2D& rect, Ref<Texture2D>& texture)
	{
		mat4 transform = translate(s_identity, glm::vec3(rect.x, rect.y, 0.0f))
			* glm::scale(s_identity, glm::vec3(rect.width, rect.height, 1.0f));

		f32 texture_index = 0.0f;
		if (texture.get()) { texture_index = get_texture_index(texture); }

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

			// texture_index
			m_sprite_data.vertexbuffer_ptr->texture_index.index = texture_index;

			m_sprite_data.vertexbuffer_ptr++;
		}
		m_sprite_data.index_count += 6;
	}

	void DeferredRenderer2D::draw(const Rect2D& rect, Ref<Texture2D>& texture, const Color& tint_color)
	{
		mat4 transform = translate(s_identity, glm::vec3(rect.x, rect.y, 0.0f))
			* glm::scale(s_identity, glm::vec3(rect.width, rect.height, 1.0f));

		f32 texture_index = 0.0f;
		if (texture.get()) { texture_index = get_texture_index(texture); }

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

			// texture_index
			m_sprite_data.vertexbuffer_ptr->texture_index.index = texture_index;

			m_sprite_data.vertexbuffer_ptr++;
		}
		m_sprite_data.index_count += 6;
	}

	void DeferredRenderer2D::set_view(Viewport& viewport)
	{
		mat matrix = ortho(
			viewport.x,
			(f32)viewport.width,
			(f32)viewport.height,
			viewport.y,
			-1.0f,
			1.0f);

		m_view = viewport;
		m_projetion_buffer->bind();
		m_projetion_buffer->set_data(sizeof(mat4), &matrix);
	}

	void DeferredRenderer2D::set_scale(f32 scale_x, f32 scale_y)
	{
		PASSERT_MSG(scale_x, "Scale x invalid");
		PASSERT_MSG(scale_y, "Scale y invalid");
		f32 width = (f32)m_view.width / scale_x;
		f32 height = (f32)m_view.height / scale_y;

		mat matrix = ortho(
			m_view.x,
			width,
			height,
			m_view.y,
			-1.0f,
			1.0f);

		m_projetion_buffer->bind();
		m_projetion_buffer->set_data(sizeof(mat4), &matrix);
	}

	void DeferredRenderer2D::flush_sprites()
	{
		if (m_sprite_data.index_count)
		{
			u32 data_size = (u32)((u8*)m_sprite_data.vertexbuffer_ptr - (u8*)m_sprite_data.vertexbuffer_base);
			m_sprite_data.vertexbuffer->bind();
			m_sprite_data.vertexbuffer->set_data(m_sprite_data.vertexbuffer_base, data_size);

			for (u32 i = 0; i < m_sprite_data.tex_index; i++) {
				m_sprite_data.tex_slots[i]->bind(i);
			}

			m_context->draw_indexed(prime::PrimitiveTopologyTriangles, m_sprite_data.index_count);
		}

		reset_sprite_batch();
	}

	void DeferredRenderer2D::flush()
	{
		flush_sprites();
	}

	void DeferredRenderer2D::LoadData(u32 sprite_max, b8 reset)
	{
		if (reset) {
			// sprite
			delete[] m_indices;
			m_sprite_data.vertexbuffer.reset();
			m_sprite_data.indexbuffer.reset();
			m_sprite_data.shader.reset();
			delete[] m_sprite_data.vertexbuffer_base;
			m_sprite_data.vertexbuffer_ptr = nullptr;
		}

		u32 max_indices = sprite_max * 6;
		u32 max_vertices = sprite_max * 4;

		m_indices = new u32[max_indices];
		u32 offset = 0;
		for (u32 i = 0; i < max_indices; i += 6)
		{
			m_indices[i + 0] = offset + 0;
			m_indices[i + 1] = offset + 1;
			m_indices[i + 2] = offset + 2;

			m_indices[i + 3] = offset + 2;
			m_indices[i + 4] = offset + 3;
			m_indices[i + 5] = offset + 0;

			offset += 4;
		}

		m_sprite_data.vertexbuffer = m_device->create_vertexbuffer(
			nullptr,
			max_vertices * sizeof(SpriteVertex),
			VertexbufferTypeDynamic);
		m_sprite_data.vertexbuffer->bind();
		m_sprite_data.vertexbuffer->set_layout(m_sprite_data.layout);
		m_sprite_data.vertexbuffer_base = new SpriteVertex[max_vertices];

		m_sprite_data.indexbuffer = m_device->create_indexbuffer(m_indices, max_indices);
		m_sprite_data.indexbuffer->bind();

		reset_sprite_batch();
	}
	
	f32 DeferredRenderer2D::get_texture_index(Ref<Texture2D>& texture)
	{
		f32 tex_index = 0.0f;
		for (u32 i = 1; i < m_sprite_data.tex_index; i++) {
			if (m_sprite_data.tex_slots[i]->get_handle() == texture->get_handle()) {
				tex_index = (f32)i;
				break;
			}
		}

		if (tex_index == 0.0f) {
			tex_index = (f32)m_sprite_data.tex_index;
			m_sprite_data.tex_slots[m_sprite_data.tex_index] = texture;
			m_sprite_data.tex_index++;
		}
		return tex_index;
	}
	
	void DeferredRenderer2D::reset_sprite_batch()
	{
		m_sprite_data.index_count = 0;
		m_sprite_data.tex_index = 1;
		m_sprite_data.vertexbuffer_ptr = m_sprite_data.vertexbuffer_base;
	}
}