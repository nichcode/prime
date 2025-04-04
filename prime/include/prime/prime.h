
#pragma once

#include <stdarg.h>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#define PRIME_PLATFORM_WINDOWS 1
#ifndef _WIN64
#error "64-bit is required on Windows!"
#endif
#elif defined(__linux__) || defined(__gnu_linux__)
// Linux OS
#define PRIME_PLATFORM_LINUX 1
#if defined(__ANDROID__)
#define PRIME_PLATFORM_ANDROID 1
#endif
#elif defined(__unix__)
// Catch anything not caught by the above.
#define PRIME_PLATFORM_UNIX 1
#elif defined(_POSIX_VERSION)
// Posix
#define PRIME_PLATFORM_POSIX 1
#elif __APPLE__
// Apple platforms
#define PRIME_PLATFORM_APPLE 1
#include <TargetConditionals.h>
#if TARGET_IPHONE_SIMULATOR
// iOS Simulator
#define PRIME_PLATFORM_IOS 1
#define PRIME_PLATFORM_IOS_SIMULATOR 1
#elif TARGET_OS_IPHONE
#define PRIME_PLATFORM_IOS 1
// iOS device
#elif TARGET_OS_MAC
// Other kinds of Mac OS
#else
#error "Unknown Apple platform"
#endif
#else
#error "Unknown platform!"
#endif

using u8 = unsigned char;
using u16 = unsigned short;
using u32 = unsigned int;
using u64 = unsigned long long;

using i8 = signed char;
using i16 = signed short;
using i32 = signed int;
using i64 = signed long long;

using f32 = float;
using f64 = double;

using b32 = int;
using b8 = bool;

#define PRIME_RELEASE 0
#define PRIME_PRESS 1
#define PRIME_REPEAT 2
#define PRIME_TRUE 1
#define PRIME_FALSE 0
#define PRIME_PASSED 1
#define PRIME_FAILED 0
#define PRIME_STR(x) #x
#define PRIME_LINE __LINE__
#define PRIME_FILE __FILE__
#define PRIME_INLINE inline
#define PRIME_MAX_TEXTURE_SLOTS 16
#define PRIME_PI 3.14159265358979323846f
#define PRIME_BIT(x) 1 << x
#define PRIME_MAX_ATTRIB 8

#ifdef PRIME_PLATFORM_WINDOWS
#define PRIME_EXT __declspec(dllexport)
#define PRIME_IMT __declspec(dllimport)
#define PRIME_BREAK __debugbreak();
#else
#define PRIME_EXPORT __attribute__((visibility("default")))
#define PRIME_IMPORT
#define PRIME_BREAK 
#endif // PRIME_PLATFORM_WINDOWS

#ifdef PRIME_EXPORT
#define PRIME_LIB PRIME_EXT
#else 
#define PRIME_LIB PRIME_IMT
#endif // PRIME_EXPORT

#ifdef __cplusplus
#define PRIME_API extern "C" PRIME_LIB
#else
#define PRIME_API PRIME_LIB
#endif // __cplusplus

// static assertions
#if defined(__clang__) || defined(__gcc__)
#define PRIME_STATIC_ASSERT _Static_assert
#else
#define PRIME_STATIC_ASSERT static_assert
#endif

PRIME_STATIC_ASSERT(sizeof(u8) == 1, "Expected u8 to be 1 byte.");
PRIME_STATIC_ASSERT(sizeof(u16) == 2, "Expected u16 to be 2 bytes.");
PRIME_STATIC_ASSERT(sizeof(u32) == 4, "Expected u32 to be 4 bytes.");
PRIME_STATIC_ASSERT(sizeof(u64) == 8, "Expected u64 to be 8 bytes.");
PRIME_STATIC_ASSERT(sizeof(i8) == 1, "Expected i8 to be 1 byte.");
PRIME_STATIC_ASSERT(sizeof(i16) == 2, "Expected i16 to be 2 bytes.");
PRIME_STATIC_ASSERT(sizeof(i32) == 4, "Expected i32 to be 4 bytes.");
PRIME_STATIC_ASSERT(sizeof(i64) == 8, "Expected i64 to be 8 bytes.");
PRIME_STATIC_ASSERT(sizeof(f32) == 4, "Expected f32 to be 4 bytes.");
PRIME_STATIC_ASSERT(sizeof(f64) == 8, "Expected f64 to be 8 bytes.");

struct prime_window;
struct prime_context;
struct prime_buffer;

using prime_close_func = void(*)(prime_window* window);
using prime_key_func = void(*)(prime_window* window, u32 key, i32 scancode, u32 action);
using prime_button_func = void(*)(prime_window* window, u32 button, u32 action);
using prime_mouse_moved_func = void(*)(prime_window* window, i32 x, i32 y);
using prime_mouse_scrolled_func = void(*)(prime_window* window, f32 offset_x, f32 offset_y);
using prime_window_moved_func = void(*)(prime_window* window, i32 x, i32 y);
using prime_window_resized_func = void(*)(prime_window* window, u32 width, u32 height);
using prime_window_focused_func = void(*)(prime_window* window, b8 focused);

enum prime_device_types
{
    PRIME_DEVICE_OPENGL
};

enum prime_log_levels
{
    PRIME_LEVEL_TRACE,
    PRIME_LEVEL_INFO,
    PRIME_LEVEL_WARN,
    PRIME_LEVEL_ERROR
};

enum prime_keys
{
    PRIME_KEY_A,
    PRIME_KEY_B,
    PRIME_KEY_C,
    PRIME_KEY_D,
    PRIME_KEY_E,
    PRIME_KEY_F,
    PRIME_KEY_G,
    PRIME_KEY_H,
    PRIME_KEY_I,
    PRIME_KEY_J,
    PRIME_KEY_K,
    PRIME_KEY_L,
    PRIME_KEY_M,
    PRIME_KEY_N,
    PRIME_KEY_O,
    PRIME_KEY_P,
    PRIME_KEY_Q,
    PRIME_KEY_R,
    PRIME_KEY_S,
    PRIME_KEY_T,
    PRIME_KEY_U,
    PRIME_KEY_V,
    PRIME_KEY_W,
    PRIME_KEY_X,
    PRIME_KEY_Y,
    PRIME_KEY_Z,

    PRIME_KEY_ESCAPE,
    PRIME_KEY_ENTER,
    PRIME_KEY_TAB,
    PRIME_KEY_BACK_SPACE,
    PRIME_KEY_INSERT,
    PRIME_KEY_DELETE,
    PRIME_KEY_RIGHT,
    PRIME_KEY_LEFT,
    PRIME_KEY_DOWN,
    PRIME_KEY_UP,
    PRIME_KEY_PAGE_UP,
    PRIME_KEY_PAGE_DOWN,
    PRIME_KEY_HOME,
    PRIME_KEY_END,
    PRIME_KEY_CAPS_LOCK,
    PRIME_KEY_SCROLL_LOCK,
    PRIME_KEY_NUM_LOCK,
    PRIME_KEY_PAUSE,

    PRIME_KEY_F1,
    PRIME_KEY_F2,
    PRIME_KEY_F3,
    PRIME_KEY_F4,
    PRIME_KEY_F5,
    PRIME_KEY_F6,
    PRIME_KEY_F7,
    PRIME_KEY_F8,
    PRIME_KEY_F9,
    PRIME_KEY_F10,
    PRIME_KEY_F11,
    PRIME_KEY_F12,

    PRIME_KEY_LEFT_SHIFT,
    PRIME_KEY_LEFT_CONTROL,
    PRIME_KEY_LEFT_ALT,
    PRIME_KEY_LEFT_SUPER,
    PRIME_KEY_RIGHT_SHIFT,
    PRIME_KEY_RIGHT_CONTROL,
    PRIME_KEY_RIGHT_ALT,
    PRIME_KEY_RIGHT_SUPER,
    PRIME_KEY_MENU,

    PRIME_KEY_LEFT_BRACKET, /* [ */
    PRIME_KEY_BACK_SLASH, /* \ */
    PRIME_KEY_RIGHT_BRACKET,  /* ] */
    PRIME_KEY_GRAVE_ACCENT,  /* ` */
    PRIME_KEY_SEMi_COLON, /* ; */
    PRIME_KEY_EQUAL, /* = */

    PRIME_KEY_SPACE,
    PRIME_KEY_APOSTROPHE, /* ' */
    PRIME_KEY_COMMA, /* , */
    PRIME_KEY_MINUS, /* - */
    PRIME_KEY_PERIOD, /* . */
    PRIME_KEY_SLASH, /* / */

    PRIME_KEY_0, /* 0 */
    PRIME_KEY_1, /* 1 */
    PRIME_KEY_2, /* 2 */
    PRIME_KEY_3, /* 3 */
    PRIME_KEY_4, /* 4 */
    PRIME_KEY_5, /* 5 */
    PRIME_KEY_6, /* 6 */
    PRIME_KEY_7, /* 7 */
    PRIME_KEY_8, /* 8 */
    PRIME_KEY_9, /* 9 */

    PRIME_KEY_MAX
};

enum prime_buttons
{
    PRIME_BUTTON_LEFT,
    PRIME_BUTTON_RIGHT,
    PRIME_BUTTON_MIDDLE,

    PRIME_BUTTON_MAX
};

enum prime_actions
{
    PRIME_ACTION_RELEASE,
    PRIME_ACTION_PRESS,
    PRIME_ACTION_REPEAT,

    PRIME_ACTION_MAX
};

enum prime_window_flags
{
    PRIME_WINDOW_SHOW = PRIME_BIT(0),
    PRIME_WINDOW_CENTER = PRIME_BIT(1)
};

enum prime_buffer_types
{
    PRIME_BUFFER_VERTEX,
    PRIME_BUFFER_INDEX,
    PRIME_BUFFER_UNIFORM,
    PRIME_BUFFER_STORAGE
};

enum prime_buffer_usages
{
    PRIME_BUFFER_USAGE_STATIC,
    PRIME_BUFFER_USAGE_DYNAMIC
};

enum prime_mode
{
    PRIME_TRIANGLES,
};

enum prime_types
{
    PRIME_INT,
    PRIME_INT2,
    PRIME_INT3,
    PRIME_INT4,
    PRIME_FLOAT,
    PRIME_FLOAT2,
    PRIME_FLOAT3,
    PRIME_FLOAT4,
    PRIME_BOOL
};

struct prime_vec2
{
    f32 x = 0.0f;
    f32 y = 0.0f;
};

struct prime_vec2i
{
    i32 x = 0;
    i32 y = 0;
};

struct prime_vec2u
{
    u32 x = 0;
    u32 y = 0;
};

struct prime_vec3
{
    f32 x = 0.0f;
    f32 y = 0.0f;
    f32 z = 0.0f;
};

struct prime_vec3i
{
    i32 x = 0;
    i32 y = 0;
    i32 z = 0;
};

struct prime_vec3u
{
    u32 x = 0;
    u32 y = 0;
    u32 z = 0;
};

struct prime_vec4
{
    f32 x = 0.0f;
    f32 y = 0.0f;
    f32 z = 0.0f;
    f32 w = 0.0f;
};

struct prime_vec4i
{
    i32 x = 0;
    i32 y = 0;
    i32 z = 0;
    i32 w = 0;
};

struct prime_vec4u
{
    u32 x = 0;
    u32 y = 0;
    u32 z = 0;
    u32 w = 0;
};

struct prime_mat4
{
    f32 data[16]{};
};

struct prime_window_desc
{
    prime_vec2u size;
    prime_vec2i pos;
    const char* title = "prime window";
    u32 flag;
};

struct prime_buffer_desc
{
    u32 type;
    u32 usage;
    u32 size;
    u32 binding;
    void* data;
};

struct prime_attrib
{
    u32 divisor;
    b8 normalize;
    u32 type;
};

struct prime_layout
{
    prime_attrib attribs[PRIME_MAX_ATTRIB]{};
    u32 count = 0;
};

PRIME_API b8 prime_init(u32 type);
PRIME_API void prime_shutdown();

PRIME_API char* prime_format(const char* fmt, ...);
PRIME_API char* prime_format_args(const char* fmt, va_list args_list);

PRIME_API char* prime_to_string(const wchar_t* wstring);
PRIME_API wchar_t* prime_to_wstring(const char* string);

PRIME_API void prime_free_string(char* string);
PRIME_API void prime_free_wstring(wchar_t* wstring);

PRIME_API void* prime_load_library(const char* dll);
PRIME_API void* prime_load_proc(void* dll, const char* func_name);
PRIME_API void prime_free_library(void* dll);

PRIME_API void prime_log(u32 level, const char* msg, ...);
PRIME_API void prime_log_trace(const char* msg, ...);
PRIME_API void prime_log_info(const char* msg, ...);
PRIME_API void prime_log_warn(const char* msg, ...);
PRIME_API void prime_log_error(const char* msg, ...);

PRIME_API void prime_assert(b8 expr, const char* file, u32 line);
PRIME_API void prime_assert_msg(b8 expr, const char* file, u32 line, const char* msg, ...);

PRIME_API prime_window* prime_create_window(prime_window_desc desc);
PRIME_API void prime_destroy_window(prime_window* window);

PRIME_API void prime_pull_events();
PRIME_API void prime_hide_Window(prime_window* window);
PRIME_API void prime_show_window(prime_window* window);
PRIME_API void prime_reset_callbacks();

PRIME_API void prime_set_window_pos(prime_window* window, prime_vec2i pos);
PRIME_API void prime_set_window_size(prime_window* window, prime_vec2u size);
PRIME_API void prime_set_window_title(prime_window* window, const char* title);

PRIME_API void prime_set_close_callback(prime_close_func callback);
PRIME_API void prime_set_key_callback(prime_key_func callback);
PRIME_API void prime_set_button_callback(prime_button_func callback);
PRIME_API void prime_set_mouse_moved_callback(prime_mouse_moved_func callback);
PRIME_API void prime_set_mouse_scrolled_callback(prime_mouse_scrolled_func callback);
PRIME_API void prime_set_window_moved_callback(prime_window_moved_func callback);
PRIME_API void prime_set_window_resized_callback(prime_window_resized_func callback);
PRIME_API void prime_set_window_focused_callback(prime_window_focused_func callback);

PRIME_API b8 prime_window_should_close(prime_window* window);
PRIME_API b8 prime_is_maximized(prime_window* window);

PRIME_API void* prime_get_window_handle(prime_window* window);
PRIME_API prime_vec2i prime_get_window_pos(prime_window* window);
PRIME_API prime_vec2u prime_get_window_size(prime_window* window);
PRIME_API const char* prime_get_window_title(prime_window* window);

PRIME_API void prime_input_set_window(prime_window* window);
PRIME_API b8 prime_get_key_state(u32 key);
PRIME_API b8 prime_get_button_state(u32 button);
PRIME_API b8 prime_get_action_state(u32 action);

PRIME_API const char* prime_get_key_name(u32 key);
PRIME_API const char* prime_get_button_name(u32 button);
PRIME_API const char* prime_get_action_name(u32 action);

PRIME_API f32 prime_sqrt(f32 number);
PRIME_API f32 prime_tan(f32 number);

PRIME_API f32 prime_cos(f32 number);
PRIME_API f32 prime_sin(f32 number);

PRIME_API prime_context* prime_create_context(prime_window* window);
PRIME_API void prime_destroy_context(prime_context* context);

PRIME_API void prime_swap_buffers();
PRIME_API void prime_clear();
PRIME_API void prime_make_active(prime_context* context);

PRIME_API void prime_set_vsync(b8 vsync);
PRIME_API void prime_set_clear_color(prime_vec4 color);
PRIME_API void prime_set_clear_colori(prime_vec4i color);

PRIME_API void prime_submit_arrays(u32 mode, u32 count);
PRIME_API void prime_submit_elements(u32 mode, u32 count);
PRIME_API void prime_submit_layout(prime_layout* layout);

PRIME_API prime_buffer* prime_create_buffer(prime_buffer_desc desc);
PRIME_API void prime_destroy_buffer(prime_buffer* buffer);

PRIME_API void prime_bind_buffer(prime_buffer* buffer);
PRIME_API void prime_set_buffer_data(void* data, u32 size);

#ifdef PRIME_CONFIG_DEBUG
#define PRIME_TRACE(...)                    prime_log_trace(__VA_ARGS__)
#define PRIME_INFO(...)                     prime_log_info(__VA_ARGS__)
#define PRIME_WARN(...)                     prime_log_warn(__VA_ARGS__)
#define PRIME_ERROR(...)                    prime_log_error(__VA_ARGS__)
#define PRIME_ASSERT(expr)                  prime_assert(expr, PRIME_FILE, PRIME_LINE)
#define PRIME_ASSERT_MSG(expr, ...)         prime_assert_msg(expr, PRIME_FILE, PRIME_LINE, __VA_ARGS__)
#else
#define PRIME_TRACE(...)         
#define PRIME_DEBUG(...)         
#define PRIME_INFO(...)         
#define PRIME_WARN(...)          
#define PRIME_ERROR(...)               
#define PRIME_ASSERT(expr)
#define PRIME_ASSERT_MSG(expr, message)
#endif // PRIME_CONFIG_DEBUG

PRIME_API i32 prime_maxi(i32 a, i32 b);
PRIME_API i32 prime_mini(i32 a, i32 b);

PRIME_API f32 prime_to_radians(f32 degrees);
PRIME_API f32 prime_to_degrees(f32 radians);

PRIME_API prime_vec2 prime_create_vec2(f32 x, f32 y);
PRIME_API prime_vec2 prime_add_vec2(const prime_vec2 a, const prime_vec2 b);
PRIME_API prime_vec2 prime_sub_vec2(const prime_vec2 a, const prime_vec2 b);
PRIME_API prime_vec2 prime_div_vec2(const prime_vec2 a, const prime_vec2 b);

PRIME_API prime_vec2 prime_div_vec2_s(const prime_vec2 a, f32 scaler);
PRIME_API prime_vec2 prime_mul_vec2(const prime_vec2 a, const prime_vec2 b);
PRIME_API prime_vec2 prime_mul_vec2_s(const prime_vec2 a, f32 scaler);
PRIME_API f32 prime_vec2_length(const prime_vec2 vec);

PRIME_API f32 prime_vec2_length_s(const prime_vec2 vec);
PRIME_API f32 prime_vec2_distance(const prime_vec2 a, const prime_vec2 b);
PRIME_API f32 prime_vec2_distance_s(const prime_vec2 a, const prime_vec2 b);
PRIME_API prime_vec2 prime_vec2_normalized(const prime_vec2 vec);

PRIME_API b8 prime_vec2_equal(const prime_vec2 a, const prime_vec2 b);
PRIME_API char* prime_vec2_to_string(prime_vec2 vec);

PRIME_API prime_vec3 prime_create_vec3(f32 x, f32 y, f32 z);
PRIME_API prime_vec3 prime_add_vec3(const prime_vec3 a, const prime_vec3 b);
PRIME_API prime_vec3 prime_sub_vec3(const prime_vec3 a, const prime_vec3 b);
PRIME_API prime_vec3 prime_div_vec3(const prime_vec3 a, const prime_vec3 b);

PRIME_API prime_vec3 prime_div_vec3_s(const prime_vec3 a, f32 scaler);
PRIME_API prime_vec3 prime_mul_vec3(const prime_vec3 a, const prime_vec3 b);
PRIME_API prime_vec3 prime_mul_vec3_s(const prime_vec3 a, f32 scaler);
PRIME_API f32 prime_vec3_length(const prime_vec3 vec);

PRIME_API f32 prime_vec3_length_s(const prime_vec3 vec);
PRIME_API f32 prime_vec3_distance(const prime_vec3 a, const prime_vec3 b);
PRIME_API f32 prime_vec3_distance_s(const prime_vec3 a, const prime_vec3 b);
PRIME_API prime_vec3 prime_vec3_normalized(const prime_vec3 vec);

PRIME_API f32 prime_vec3_dot(const prime_vec3 a, const prime_vec3 b);
PRIME_API prime_vec3 prime_vec3_cross(const prime_vec3 a, const prime_vec3 b);
PRIME_API b8 prime_vec3_equal(const prime_vec3 a, const prime_vec3 b);
PRIME_API char* prime_vec3_to_string(prime_vec3 vec);

PRIME_API prime_vec4 prime_create_vec4(f32 x, f32 y, f32 z, f32 w);
PRIME_API prime_vec4 prime_add_vec4(const prime_vec4 a, const prime_vec4 b);
PRIME_API prime_vec4 prime_sub_vec4(const prime_vec4 a, const prime_vec4 b);
PRIME_API prime_vec4 prime_div_vec4(const prime_vec4 a, const prime_vec4 b);

PRIME_API prime_vec4 prime_div_vec4_s(const prime_vec4 a, f32 scaler);
PRIME_API prime_vec4 prime_mul_vec4(const prime_vec4 a, const prime_vec4 b);
PRIME_API prime_vec4 prime_mul_vec4_s(const prime_vec4 a, f32 scaler);
PRIME_API f32 prime_vec4_length(const prime_vec4 vec);

PRIME_API f32 prime_vec4_length_s(const prime_vec4 vec);
PRIME_API f32 prime_vec4_distance(const prime_vec4 a, const prime_vec4 b);
PRIME_API f32 prime_vec4_distance_s(const prime_vec4 a, const prime_vec4 b);
PRIME_API prime_vec4 prime_vec4_normalized(const prime_vec4 vec);

PRIME_API b8 prime_vec4_equal(const prime_vec4 a, const prime_vec4 b);
PRIME_API char* prime_vec4_to_string(prime_vec4 vec);

PRIME_API prime_mat4 prime_identity();
PRIME_API prime_mat4 prime_mat4_mul(const prime_mat4 a, const prime_mat4 b);
PRIME_API prime_mat4 prime_ortho(f32 left, f32 right, f32 bottom, f32 top, f32 near_clip, f32 far_clip);
PRIME_API prime_mat4 prime_perspective(f32 fov_radians, f32 aspect_ratio, f32 near_clip, f32 far_clip);

PRIME_API prime_mat4 prime_look_at(const prime_vec3 position, const prime_vec3 target, const prime_vec3 up);
PRIME_API prime_mat4 prime_transposed(const prime_mat4& matrix);
PRIME_API prime_mat4 prime_inverse(const prime_mat4& matrix);
PRIME_API prime_mat4 prime_translate(const prime_vec3 translation);

PRIME_API prime_mat4 prime_scale(const prime_vec3 scale);
PRIME_API prime_mat4 prime_rotate_x(f32 angle_degrees);
PRIME_API prime_mat4 prime_rotate_y(f32 angle_degrees);
PRIME_API prime_mat4 prime_rotate_z(f32 angle_degrees);

PRIME_API prime_mat4 prime_rotate(f32 x_degrees, f32 y_degrees, f32 z_degrees);
PRIME_API prime_vec4 prime_vec4_mul_mat4(const prime_vec4 vec, const prime_mat4 mat);
PRIME_API prime_vec4 prime_mat4_mul_vec4(const prime_mat4 matrix, const prime_vec4 vec);
PRIME_API char* prime_mat4_to_string(prime_mat4 matrix);