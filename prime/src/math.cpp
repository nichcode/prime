
#include "prime/math.h"

#include <cmath>

namespace prime {

    f32 
    math::sqrt(f32 num)
    {
        return sqrtf(num);
    }

    f32 
    math::tan(f32 num)
    {
        return tanf(num);
    }

    f32 
    math::cos(f32 num)
    {
        return cosf(num);
    }

    f32 
    math::sin(f32 num)
    {
        return sinf(num);
    }

    str
    mat4::toString(const mat4& matrix)
    {
        const f32* d = matrix.data;
        str row1 = Utils::format("[%f %f %f %f]", d[0], d[1], d[2], d[3]);
        str row2 = Utils::format("[%f %f %f %f]", d[4], d[5], d[6], d[7]);
        str row3 = Utils::format("[%f %f %f %f]", d[8], d[9], d[10], d[11]);
        str row4 = Utils::format("[%f %f %f %f]", d[12], d[13], d[14], d[15]);

        str str = Utils::format("mat4(%s \n\t     %s \n\t     %s \n\t     %s)",
            row1.c_str(),
            row2.c_str(),
            row3.c_str(),
            row4.c_str());

        return str;
    }

} // namespace prime
