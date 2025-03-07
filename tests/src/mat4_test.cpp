
#include "prime/prime.h"

b8 mat4Test()
{
    using namespace prime::maths;

    mat4 ortho = mat4::orthographic(0.0f, 640.0f, 480.0f, 0.0f, 1.0f, -1.0f);

	mat4 perps = mat4::perspective(45.0f, 640.0f / 480.0f, 30.0f, 1000.0f);
	mat4 translation = mat4::translate({2.0f, 11.0f, -2.0f});
	mat4 rotation = mat4::rotateZ(45.0f);
	mat4 scale = mat4::scale({ 2.0f, 2.0f, 2.0f });
	mat4 trs = translation * rotation * scale;
	mat4 inverse = mat4::inverse(trs);

	str string_ortho = mat4::toString(ortho);
	str string_perps = mat4::toString(perps);
	str string_translation = mat4::toString(translation);
	str string_rotation = mat4::toString(rotation);
	str string_scale = mat4::toString(scale);
	str string_trs = mat4::toString(trs);
	str string_inverse = mat4::toString(inverse);

	prime::core::Logger::info(string_ortho);
	prime::core::Logger::info(string_perps);
	prime::core::Logger::info(string_translation);
	prime::core::Logger::info(string_rotation);
	prime::core::Logger::info(string_scale);
	prime::core::Logger::info(string_trs);
	prime::core::Logger::info(string_inverse);

    return PRIME_TRUE;
}