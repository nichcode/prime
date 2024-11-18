#pragma once

#include "defines.h"
#include "assert.h"

namespace prime {

	struct Position2DVertex
	{
		f32 x = 0.0f;
		f32 y = 0.0f;
	};

	struct ColorVertex
	{
		f32 r = 0.0f;
		f32 g = 0.0f;
		f32 b = 0.0f;
		f32 a = 0.0f;
	};

	struct TextureVertex
	{
		f32 u = 0.0f;
		f32 v = 0.0f;
	};

	struct TextureIDVertex
	{
		f32 index = 0.0f;
	};

	struct SpriteVertex
	{
		Position2DVertex pos;
		ColorVertex color;
		TextureVertex texture_coords;
		TextureIDVertex texture_index;
	};

	enum DataType : u8
	{
		DataTypeNone,
		DataTypeInt,
		DataTypeInt2,
		DataTypeInt3,
		DataTypeInt4,
		DataTypeFloat,
		DataTypeFloat2,
		DataTypeFloat3,
		DataTypeFloat4,
		DataTypeMat3,
		DataTypeMat4,
		DataTypeBool,

		DataTypeMax
	};

	/**
	 * @brief Get the data type size.
	 *
	 * @param type The vertexbuffer element data type.
	 * @return The size of the data type.
	 */
	PINLINE u8 get_data_type_size(DataType type)
	{
		switch (type)
		{
		case DataTypeInt:
		case DataTypeFloat: {
			return 4;
		}

		case DataTypeInt2:
		case DataTypeFloat2: {
			return 8;
		}

		case DataTypeInt3:
		case DataTypeFloat3: {
			return 12;
		}

		case DataTypeInt4:
		case DataTypeFloat4: {
			return 16;
		}

		case DataTypeMat3:     return 4 * 3 * 3;
		case DataTypeMat4:     return 4 * 4 * 4;
		case DataTypeBool:     return 1;
		}

		PASSERT_MSG(false, "Invalid DataType");
		return 0;
	}

	/**
	 * @brief Get the data type count.
	 *
	 * @param type The vertexbuffer element data type.
	 * @return The count of the data type.
	 */
	PINLINE u8 get_data_type_count(DataType type)
	{
		switch (type)
		{
		case DataTypeFloat:
		case DataTypeInt:
		case DataTypeBool: {
			return 1;
		}

		case DataTypeFloat2:
		case DataTypeInt2: {
			return 2;
		}

		case DataTypeFloat3:
		case DataTypeInt3: {
			return 3;
		}

		case DataTypeFloat4:
		case DataTypeInt4: {
			return 4;
		}


		case DataTypeMat3:     return 9;
		case DataTypeMat4:     return 16;
		}

		PASSERT_MSG(false, "Invalid DataType");
		return 0;
	}
}
