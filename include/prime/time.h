#pragma once

#include "defines.h"

namespace prime {

	class Device;

	class Time
	{
	public:
		/**
		 * @brief Initialize the time subsystem. This is called by the device.
		 */
		static void init();

        /**
         * @brief Get the current time.
         * 
         * @return f64 the current time.
         */
		static f64 get();

        /**
         * @brief sleep for a number of milliseconds.
         * 
         * @param milli_seconds the amount of milliseconds to sleep .
         */
		static void sleep(f64 milli_seconds);
	};

	class Timestep
	{
	private:
		f32 m_frame_time = 0.0f;
		f32 m_delta_time = 0.0f;

	public:
	    /**
	     * @brief get the delta time.
	     * 
	     * @return PINLINE the delta time.
	     */
		PINLINE f32 get_dt() const { return m_delta_time; }

		/**
		 * @brief Update the step on the current frame.
		 */
		void tick()
		{
			f32 time = (f32)Time::get();
			m_delta_time = time - m_frame_time;
			m_frame_time = time;
		}
	};
}
