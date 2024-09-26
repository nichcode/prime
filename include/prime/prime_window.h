#pragma once

#include "prime_defines.h"
#include "prime_keycodes.h"
#include "prime_mousecodes.h"

namespace prime {

	class Window;

	struct WindowProperties
	{
		/**
		 * @brief The width of the window.
		 */
		u32 Width = 640;

		/**
		 * @brief The height of the window.
		 */
		u32 Height = 480;

		/**
		 * @brief The title of the window.
		 */
		str Title = "PrimeWindow";

		/**
		 * @brief Center the window on creation.
		 */
		b8 Center = false;

		/**
		 * @brief Maximize the window on creation.
		 */
		b8 Maximize = false;

		/**
		 * @brief Hide the window on creation.
		 */
		b8 Hidden = false;

		/**
		 * @brief The left position of the window.
		 */
		i32 XPos = 100;

		/**
		 * @brief The bottom position of the window.
		 */
		i32 YPos = 100;
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
	using MouseButtonFunc = void(*)(const Window* window, u16 mouse, u8 action);

	/**
	* @brief Window mouse moved callback.
	*/
	using MouseMovedFunc = void(*)(const Window* window, i32 x, i32 y);

	/**
	* @brief Window scrolled callback.
	*/
	using MouseScrolledFunc = void(*)(const Window* window, f32 xOffset, f32 yOffset);

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
		WindowProperties Props;
		b8 ShouldClose = false, IsFocused = false;

		u16 Keycodes[512] = {};
		u16 Scancodes[Key_Max + 1] = {};
		str Keynames[Key_Max + 1] = {};

		u8 keys[Key_Max + 1] = {};
		u8 Mouse[Mouse_Max + 1] = {};

		i32 MousePos[2] = {};

		WindowData()
		{
			memset(Keycodes, 0, sizeof(Keycodes));
			memset(Scancodes, 0, sizeof(Scancodes));
		}
	};

	class Window
	{
	private:
		void* m_Handle;
		WindowData m_Data;
		void* m_UserData;

	public:
		Window() :m_UserData(nullptr), m_Handle(nullptr) {}

        /**
         * @brief Initialize the window.
         * 
         * @param props The window properities to create the window with.
         */
		void Init(const WindowProperties& props);

		/**
	    * @brief Destroy the window.
	    */
		void Destroy();

		/**
		 * @brief Get the window handle.
		 * 
		 * @return PINLINE void* The window handle.
		 */
		PINLINE void* GetHandle() const { return m_Handle; }

		/**
		 * @brief Get the width of the window.
		 * 
		 * @return u32 The width of the window.
		 */
		PINLINE u32 GetWidth() const { return m_Data.Props.Width; }

		/**
		 * @brief Get the height of the window.
		 * 
		 * @return u32 The height of the window.
		 */
		PINLINE u32 GetHeight() const { return m_Data.Props.Height; }
        
		/**
		 * @brief Get the x position of the window.
		 * 
		 * @return i32 The x position of the window.
		 */
		PINLINE i32 GetXPos() const { return m_Data.Props.XPos; }

		/**
		 * @brief Get the y position of the window.
		 * 
		 * @return i32 The y position of the window.
		 */
		PINLINE i32 GetYPos() const { return m_Data.Props.YPos; }

		/**
		 * @brief Get the title of the window.
		 * 
		 * @return str The title of the window.
		 */
		PINLINE str GetTitle() const { return m_Data.Props.Title; }

        /**
		 * @brief Check to see if the window is hidden.
		 * 
		 * @return True if window is hidden else false.
		 */
		PINLINE b8 IsHidden() const { return m_Data.Props.Hidden; }

		/**
		 * @brief Check to see if the window's close button has been clicked.
		 * 
		 * @return PINLINE True if the window's close button has been clicked else false.
		 */
		PINLINE b8 ShouldClose() const { return m_Data.ShouldClose; }

		/**
		 * @brief Hide the window. If the window is already hidden, this does nothing.
		 */
		void Hide();

		/**
		 * @brief Show the window. If the window is already shown, this does nothing.
		 */
		void Show();

        /**
         * @brief Set the title of the window.
         * 
         * @param title the title to set.
         */
		void SetTitle(const str& title);

		/**
		 * @brief Set the position of the window.
		 * 
		 * @param xPos The x position of the window to set.
		 * @param yPos The y position of the window to set.
		 */
		void SetPos(i32 xPos, i32 yPos);

		/**
		 * @brief Set The size of the window.
		 * 
		 * @param width The width of the window to set.
		 * @param height The height of the window to set.
		 */
		void SetSize(u32 width, u32 height);
		
		/**
		 * @brief Set user data which can be retrieved in window callback functions.
		 * This function returns a void* so user have to cast the this into the desired pointer.
		 * ie. prime::WindowProperties* props = (prime::WindowProperties*)window.GetUserData().
		 * 
		 * @param userDataPtr the user pointer to set. This should be a pointer.
		 */
		void SetUserData(void* userDataPtr) { m_UserData = userDataPtr; }

		/**
		 * @brief Set the user data pointer of the window.
		 * 
		 * @return PINLINE void* The user data of the window.
		 */
		PINLINE void* GetUserData() const { return m_UserData; }

		/**
		 * @brief Get the state of a key on the keyboard.
		 * 
		 * @param key The key to check the state.
		 * @return PINLINE True if the key is pressed else false.
		 */
		PINLINE b8 GetKeyState(u16 key) const {
			return m_Data.keys[key] == PPRESS;
		}

        /**
         * @brief Get the key name of a key on the keyboard.
         * 
         * @param key The key to check the name.
         * @return PINLINE str The name of the key.
         */
		PINLINE str GetKeyName(u16 key) const
		{ 
			if (key >= 0 && key < (u16)Keys::Key_Max) { 
				return m_Data.Keynames[key];
			}
			return "";
		}

        /**
         * @brief Get the mouse button name of a mouse button on the mouse.
         * 
         * @param mouse The mouse button to check the name.
         * @return PINLINE str The name of the mouse button.
         */
		PINLINE str GetMouseName(u16 mouse) const
		{
			switch (mouse)
			{
			case 0:
				return "Mouse_Left";
				break;
			case 1:
				return "Mouse_Right";
				break;
			case 2:
				return "Mouse_Middle";
				break;
			}
			return "";
		}

        /**
         * @brief Get the name of the action of a key or mouse button.
         * 
         * @param action The action to check.
         * @return PINLINE The name of the action.
         */
		PINLINE str GetActionName(u8 action) const
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
	void PollEvents();

    /**
     * @brief Set the window close callback for all created windows.
     * 
     * @param func The window close callback function.
     */
	void SetWindowCloseCallback(CloseFunc func);

	/**
	 * @brief Set the window key callback for all created windows.
	 * 
	 * @param func The window key callback function.
	 */
	void SetWindowKeyCallback(KeyFunc func);

	/**
	 * @brief Set the window mouse button callback for all created windows.
	 * 
	 * @param func The window mouse button callback function.
	 */
	void SetWindowMouseButtonCallback(MouseButtonFunc func);

	/**
	 * @brief Set the window mouse moved callback for all created windows.
	 * 
	 * @param func The window mouse moved callback function.
	 */
	void SetWindowMouseMovedCallback(MouseMovedFunc func);

	/**
	 * @brief Set the window mouse scrolled callback for all created windows.
	 * 
	 * @param func The window mouse scrolled callback function.
	 */
	void SetWindowMouseScrolledCallback(MouseScrolledFunc func);

	/**
	 * @brief Set the window position callback for all created windows.
	 * 
	 * @param func The window position callback.
	 */
	void SetWindowPosCallback(WindowPosFunc func);

	/**
	 * @brief Set the window reisze callback for all created windows.
	 * 
	 * @param func The window resize callback.
	 */
	void SetWindowResizeCallback(WindowResizeFunc func);

	/**
	 * @brief Set the window focus callback for all created windows.
	 * 
	 * @param func The window focus callback.
	 */
	void SetWindowFocusCallback(WindowFocusFunc func);
}
