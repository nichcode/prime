#pragma once

#include "defines.h"

namespace prime {

	enum TextureFormat
	{
		TextureFormatNone,
		TextureFormatR8,
		TextureFormatRGB8,
		TextureFormatRGBA8,
		TextureFormatRGBA32F
	};

	struct TextureProperties
	{
		/**
		 * @brief Width of the texture.
		 */
		uint32_t width = 1;

		/**
		 * @brief Width of the texture.
		 */
		uint32_t height = 1;

		/**
		 * @brief Format of the texture.
		 */
		TextureFormat format = TextureFormatRGBA8;
	};

	class Texture2D
	{
	public:
		virtual ~Texture2D() {}

		/**
		 * @brief  Bind the texture2d.
		 * @param slot The texture slot to bind the texture2d.
		 */
		virtual void bind(u32 slot = 0) = 0;

		/**
		 * @brief Unbind the texture2d.
		 */
		virtual void unbind() = 0;

        /**
		 * @brief Get the width of the texture2d.
		 * 
		 * @return The width of the texture2d.
		 */
		virtual u32 get_width() const = 0;

		/**
		 * @brief Get the height of the texture2d.
		 * 
		 * @return The height of the texture2d.
		 */
		virtual u32 get_height() const = 0;

		/**
		 * @brief Get the path of the texture2d.
		 * @return The path of the texture2d otherwise empty.
		 */
		virtual str get_path() const = 0;

		/**
		 * @brief Get the handle of the texture2d.
		 * @return The texture2d handle.
		 */
		virtual const void* get_handle() const = 0;
	};
}
