#pragma once

#include "defines.h"
#include "keycodes.h"
#include "mousecodes.h"

namespace prime {

	class Window;

	struct WindowProperties
	{
		/**
		 * @brief The width of the window.
		 */
		u32 width = 640;

		/**
		 * @brief The height of the window.
		 */
		u32 height = 480;

		/**
		 * @brief The title of the window.
		 */
		str title = "PrimeWindow";

		/**
		 * @brief Center the window on creation.
		 */
		b8 center = false;

		/**
		 * @brief Maximize the window on creation.
		 */
		b8 maximize = false;

		/**
		 * @brief Hide the window on creation.
		 */
		b8 hidden = false;

		/**
		 * @brief The left position of the window.
		 * if window is centered on creation this does nothing.
		 */
		i32 x_pos = 100;

		/**
		 * @brief The bottom position of the window.
		 * if window is centered on creation this does nothing.
		 */
		i32 y_pos = 100;
	};
 
	/**
    * @brief Window close callback.
    */
	using CloseFunc = void(*)(const Window* window);

	/**
	* @brief Window key callback.
	*/
	using KeyFunc = void(*)(const Window* window, u16 key, i32 scancode, u8 action);

	/**
	* @brief Window mouse button callback.
	*/
	using MouseButtonFunc = void(*)(const Window* window, u16 button, u8 action);

	/**
	* @brief Window mouse moved callback.
	*/
	using MouseMovedFunc = void(*)(const Window* window, i32 x, i32 y);

	/**
	* @brief Window scrolled callback.
	*/
	using MouseScrolledFunc = void(*)(const Window* window, f32 x_offset, f32 y_offset);

	/**
	* @brief Window position callback.
	*/
	using WindowPosFunc = void(*)(const Window* window, i32 x, i32 y);

	/**
	* @brief Window resize callback.
	*/
	using WindowResizeFunc = void(*)(const Window* window, u32 width, u32 height);

	/**
	* @brief Window focus callback.
	*/
	using WindowFocusFunc = void(*)(const Window* window, b8 focused);

	
	struct WindowData 
	{
		WindowProperties props;
		b8 should_close = false, is_focused = false;

		u16 keycodes[512] = {};
		u16 scancodes[Key_Max + 1] = {};
		str keynames[Key_Max + 1] = {};

		u8 keys[Key_Max + 1] = {};
		u8 mouse[Mouse_Max + 1] = {};

		i32 mouse_pos[2] = {};

		WindowData()
		{
			memset(keycodes, 0, sizeof(keycodes));
			memset(scancodes, 0, sizeof(scancodes));
		}
	};

	class Window
	{
	private:
		void* m_handle;
		WindowData m_data;
		void* m_user_data;

	public:
		Window() :m_user_data(nullptr), m_handle(nullptr) {}

        /**
         * @brief Initialize the window.
         * 
         * @param props The window properities.
         */
		void init(const WindowProperties& props);

		/**
	    * @brief Destroy the window.
	    */
		void destroy();

		/**
		 * @brief Get the window handle.
		 * 
		 * @return The window handle.
		 */
		PINLINE void* get_handle() const { return m_handle; }

		/**
		 * @brief Get the width of the window.
		 * 
		 * @return The width of the window.
		 */
		PINLINE u32 get_width() const { return m_data.props.width; }

		/**
		 * @brief Get the height of the window.
		 * 
		 * @return The height of the window.
		 */
		PINLINE u32 get_height() const { return m_data.props.height; }
        
		/**
		 * @brief Get the x position of the window.
		 * 
		 * @return The x position of the window.
		 */
		PINLINE i32 get_xpos() const { return m_data.props.x_pos; }

		/**
		 * @brief Get the y position of the window.
		 * 
		 * @return The y position of the window.
		 */
		PINLINE i32 get_ypos() const { return m_data.props.y_pos; }

		/**
		 * @brief Get the title of the window.
		 * 
		 * @return The title of the window.
		 */
		PINLINE str get_title() const { return m_data.props.title; }

        /**
		 * @brief Check to see if the window is hidden.
		 * 
		 * @return True if window is hidden otherwise false.
		 */
		PINLINE b8 is_hidden() const { return m_data.props.hidden; }

		/**
		 * @brief Check to see if the window's close button has been clicked.
		 * 
		 * @return PINLINE True if the window's close button has been clicked else false.
		 */
		PINLINE b8 should_close() const { return m_data.should_close; }

		/**
		 * @brief Hide the window. If the window is already hidden, this does nothing.
		 */
		void hide();

		/**
		 * @brief Show the window. If the window is already shown, this does nothing.
		 */
		void show();

        /**
         * @brief Set the title of the window.
         * 
         * @param title the title to set.
         */
		void set_title(const str& title);

		/**
		 * @brief Set the position of the window.
		 * 
		 * @param x_pos The x position of the window to set.
		 * @param y_pos The y position of the window to set.
		 */
		void set_pos(i32 x_pos, i32 y_pos);

		/**
		 * @brief Set The size of the window.
		 * 
		 * @param width The width of the window to set.
		 * @param height The height of the window to set.
		 */
		void set_size(u32 width, u32 height);
		
		/**
		 * @brief Set user data which can be retrieved in window callback functions.
		 * This function returns a void* so user have to cast the this into the desired pointer.
		 * ie. prime::WindowProperties* props = (prime::WindowProperties*)window.GetUserData().
		 * 
		 * @param user_data_ptr the user pointer to set. This should be a pointer.
		 */
		void Set_user_data(void* user_data_ptr) { m_user_data = user_data_ptr; }

		/**
		 * @brief Set the user data pointer of the window.
		 * 
		 * @return The user data of the window.
		 */
		PINLINE void* get_user_data() const { return m_user_data; }

		/**
		 * @brief Get the state of a key on the keyboard.
		 * 
		 * @param key The key to check the state.
		 * @return True if the key is pressed otherwise false.
		 */
		PINLINE b8 get_key_state(u16 key) const 
		{
			return m_data.keys[key] == PPRESS;
		}

        /**
         * @brief Get the key name of a key on the keyboard.
         * 
         * @param key The key to check the name.
         * @return The name of the key.
         */
		PINLINE str get_key_name(u16 key) const
		{ 
			if (key >= 0 && key < (u16)Keys::Key_Max) { 
				return m_data.keynames[key];
			}
			return "";
		}

        /**
         * @brief Get the mouse button name of a mouse button on the mouse.
         * 
         * @param mouse The mouse button to check the name.
         * @return The name of the mouse button.
         */
		PINLINE str get_mouse_button_name(u16 mouse_button) const
		{
			switch (mouse_button)
			{
			case 0:
				return "mouse_ButtonLeft";
				break;
			case 1:
				return "mouse_ButtonRight";
				break;
			case 2:
				return "mouse_ButtonMiddle";
				break;
			}
			return "";
		}

        /**
         * @brief Get the name of the action of a key or mouse button.
         * 
         * @param action The action to check.
         * @return The name of the action.
         */
		PINLINE str get_action_name(u8 action) const
		{
			if (action == PRELEASE) {
				return "Release";
			}
			else if (action == PPRESS) {
				return "Press";
			}
			else if (action == PREPEAT) {
				return "Repeat";
			}
			return "";
		}
	};
    
	/**
	 * @brief Poll events from all created windows.
	 */
	void poll_events();

    /**
     * @brief Set the window close callback for all created windows.
     * 
     * @param func The window close callback function.
     */
	void set_window_close_callback(CloseFunc func);

	/**
	 * @brief Set the window key callback for all created windows.
	 * 
	 * @param func The window key callback function.
	 */
	void set_window_key_callback(KeyFunc func);

	/**
	 * @brief Set the window mouse button callback for all created windows.
	 * 
	 * @param func The window mouse button callback function.
	 */
	void set_window_mouse_button_callback(MouseButtonFunc func);

	/**
	 * @brief Set the window mouse moved callback for all created windows.
	 * 
	 * @param func The window mouse moved callback function.
	 */
	void set_window_mouse_moved_callback(MouseMovedFunc func);

	/**
	 * @brief Set the window mouse scrolled callback for all created windows.
	 * 
	 * @param func The window mouse scrolled callback function.
	 */
	void set_window_mouse_scrolled_callback(MouseScrolledFunc func);

	/**
	 * @brief Set the window position callback for all created windows.
	 * 
	 * @param func The window position callback.
	 */
	void set_window_pos_callback(WindowPosFunc func);

	/**
	 * @brief Set the window reisze callback for all created windows.
	 * 
	 * @param func The window resize callback.
	 */
	void set_window_resize_callback(WindowResizeFunc func);

	/**
	 * @brief Set the window focus callback for all created windows.
	 * 
	 * @param func The window focus callback.
	 */
	void set_window_focus_callback(WindowFocusFunc func);
}
