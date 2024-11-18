#pragma once

#include "defines.h"

namespace prime {

	class Shader
	{
	public:
		virtual ~Shader() {}

		/**
		 * @brief Bind the shader.
		 */
		virtual void bind() = 0;

		/**
		 * @brief Unbind the shader.
		 */
		virtual void unbind() = 0;
        
		/**
		 * @brief Set an interger.
		 * 
		 * @param name The name of the layout location to set the data.
		 * @param data The integer to set.
		 */
		virtual void set_int(const str& name, i32 data) = 0;

		/**
		 * @brief Set an interger array.
		 * 
		 * @param name The name of the layout location to set the data.
		 * @param data The interger array to set.
		 * @param count The number of the intergers in interget array.
		 */
		virtual void set_int_array(const str& name, i32* data, u32 count) = 0;

        /**
         * @brief Set a float.
         * 
         * @param name The name of the layout location to set the data.
         * @param data The float to set.
         */
		virtual void set_float(const str& name, f32 data) = 0;

        /**
         * @brief Set two floats.
         * 
         * @param name The name of the layout location to set the data.
         * @param data The first float to set.
         * @param data2 The second float to set.
         */
		virtual void set_float2(const str& name, f32 data, f32 data2) = 0;

		/**
		 * @brief Set three floats.
		 * 
		 * @param name The name of the layout location to set the data.
		 * @param data The first float to set.
		 * @param data2 The second float to set.
		 * @param data3 The third float to set.
		 */
		virtual void set_float3(const str& name, f32 data, f32 data2, f32 data3) = 0;

		/**
		 * @brief Set four floats.
		 * 
		 * @param name The name of the layout location to set the data.
		 * @param data The first float to set.
		 * @param data2 The second float to set.
		 * @param data3 The third float to set.
		 * @param data4 The fourth float to set.
		 */
		virtual void set_float4(const str& name, f32 data, f32 data2, f32 data3, f32 data4) = 0;

        /**
         * @brief Set a 2x2 matrix.
         * 
         * @param name The name of the layout location to set the data.
         * @param data A pointer to an array of floats ie. data[2][2].
         */
		virtual void set_mat2(const str& name, f32* data) = 0;

		/**
		 * @brief Set a 3x3 matrix.
		 * 
		 * @param name The name of the layout location to set the data.
		 * @param data A pointer to an array of floats ie. data[3][3].
		 */
		virtual void set_mat3(const str& name, f32* data) = 0;

		/**
		 * @brief Set a 4x4 matrix.
		 * 
		 * @param name The name of the layout location to set the data.
		 * @param data A pointer to an array of floats ie. data[4][4].
		 */
		virtual void set_mat4(const str& name, f32* value) = 0;
	};
}
