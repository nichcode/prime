
#pragma once

#include "prime/utils.h"

namespace prime {

    struct math
    {
        static f32
        sqrt(f32 num);

        static f32
        tan(f32 num);

        static f32
        cos(f32 num);

        static f32
        sin(f32 num);

        PINLINE static f32 
        toRadians(f32 radians)
        {
            return radians * 180.0f / PPI;
        }

        PINLINE static f32 
        toDegress(f32 degrees)
        {
            return degrees * PPI / 180.0f;
        }
    };

    struct vec2
    {
        f32 x;
        f32 y;

        vec2()
        {
            this->x = 0.0f;
            this->y = 0.0f;
        }

        vec2(f32 x, f32 y)
        {
            this->x = x;
            this->y = y;
        }

        PINLINE void 
        add(const vec2& v)
        {
            this->x += v.x;
            this->y += v.y;
        }

        PINLINE void 
        sub(const vec2& v) 
        {
            this->x -= v.x;
            this->y -= v.y;
        }

        PINLINE void 
        div(const vec2& v)
        {
            this->x /= v.x;
            this->y /= v.y;
        }

        PINLINE void 
        mul(const vec2& v)
        {
            this->x *= v.x;
            this->y *= v.y;
        }

        PINLINE void 
        mulScaler(const f32 scaler)
        {
            this->x *= scaler;
            this->y *= scaler;
        }

        PINLINE void 
        divScaler(const f32 scaler)
        {
            this->x /= scaler;
            this->y /= scaler;
        }

        PINLINE void
        normalize()
        {
            const f32 length = math::sqrt(x * x + y * y);
            x /= length;
            y /= length;
        }

        PINLINE static vec2
        add(const vec2& lhs, const vec2& rhs)
        {
            return vec2(lhs.x + rhs.x, lhs.y + rhs.y);
        }

        PINLINE static vec2
        sub(const vec2& lhs, const vec2& rhs)
        {
            return vec2(lhs.x - rhs.x, lhs.y - rhs.y);
        }

        PINLINE static vec2
        div(const vec2& lhs, const vec2& rhs)
        {
            return vec2(lhs.x / rhs.x, lhs.y / rhs.y);
        }

        PINLINE static vec2
        mul(const vec2& lhs, const vec2& rhs)
        {
            return vec2(lhs.x * rhs.x, lhs.y * rhs.y);
        }

        PINLINE static vec2
        mulScaler(const vec2& vec, f32 scaler)
        {
            return vec2(vec.x * scaler, vec.y * scaler);
        }

        PINLINE static vec2
        divScaler(const vec2& vec, f32 scaler)
        {
            return vec2(vec.x / scaler, vec.y / scaler);
        }

        PINLINE static f32
        lengthSquared(const vec2& vec)
        {
            return vec.x * vec.x + vec.y * vec.y;
        }

        PINLINE static f32
        length(const vec2& vec)
        {
            return math::sqrt(vec.x * vec.x + vec.y * vec.y);
        }

        PINLINE static vec2
        normalized(const vec2& vec)
        {
            vec2 v = vec;
            const f32 length = vec2::length(vec);
            v.x /= length;
            v.y /= length;
            return v;
        }

        PINLINE static f32
        distanceSquared(const vec2& lhs, const vec2& rhs)
        {
            vec2 vec(lhs.x - rhs.x, lhs.y - rhs.y);
            return lengthSquared(vec);
        }

        PINLINE static f32
        distance(const vec2& lhs, const vec2& rhs)
        {
            vec2 vec(lhs.x - rhs.x, lhs.y - rhs.y);
            return length(vec);
        }

        PINLINE static b8
        equal(const vec2& lhs, const vec2& rhs)
        {
            return lhs.x == rhs.x && lhs.y == rhs.y;
        }

        PINLINE static b8
        notEqual(const vec2& lhs, const vec2& rhs)
        {
            return lhs.x != rhs.x && lhs.y != rhs.y;
        }

        PINLINE static str
        toString(const vec2& vec)
        {
            return Utils::format("vec2(%.2f, %.2f)", vec.x, vec.y);
        }
    };

    struct vec3
    {
        f32 x;
        f32 y;
        f32 z;

        vec3(f32 x, f32 y, f32 z)
        {
            this->x = x;
            this->y = y;
            this->z = z;
        }
    };

    struct vec4
    {
        f32 x;
        f32 y;
        f32 z;
        f32 w;

        vec4(f32 x, f32 y, f32 z, f32 w)
        {
            this->x = x;
            this->y = y;
            this->z = z;
            this->w = w;
        }
    };

    struct mat4
    {
        f32 data[16];

        mat4()
        {
            for (u32 x = 0; x < 16; x++) {
                data[x] = 0.0f;
            }   
        }
    };
    
} // namespace prime

#ifdef __cplusplus

// vec2

PINLINE prime::vec2 operator + (const prime::vec2& lhs, const prime::vec2& rhs)
{
    return prime::vec2::add(lhs, rhs);
}

PINLINE prime::vec2 operator - (const prime::vec2& lhs, const prime::vec2& rhs)
{
    return prime::vec2::sub(lhs, rhs);
}

PINLINE prime::vec2 operator / (const prime::vec2& lhs, const prime::vec2& rhs)
{
    return prime::vec2::div(lhs, rhs);
}

PINLINE prime::vec2 operator / (const prime::vec2& lhs, const f32 scaler)
{
    return prime::vec2::divScaler(lhs, scaler);
}

PINLINE prime::vec2 operator * (const prime::vec2& lhs, const prime::vec2& rhs)
{
    return prime::vec2::mul(lhs, rhs);
}

PINLINE prime::vec2 operator * (const prime::vec2& lhs, const f32 scaler)
{
    return prime::vec2::mulScaler(lhs, scaler);
}

PINLINE prime::vec2& operator += (prime::vec2& lhs, const prime::vec2& rhs)
{
    lhs.add(rhs);
    return lhs;
}

PINLINE prime::vec2& operator -= (prime::vec2& lhs, const prime::vec2& rhs)
{
    lhs.sub(rhs);
    return lhs;
}

PINLINE prime::vec2& operator /= (prime::vec2& lhs, const prime::vec2& rhs)
{
    lhs.div(rhs);
    return lhs;
}

PINLINE prime::vec2& operator /= (prime::vec2& lhs, f32 scaler)
{
    lhs.divScaler(scaler);
    return lhs;
}

PINLINE prime::vec2& operator *= (prime::vec2& lhs, const prime::vec2& rhs)
{
    lhs.mul(rhs);
    return lhs;
}

PINLINE prime::vec2& operator *= (prime::vec2& lhs, f32 scaler)
{
    lhs.mulScaler(scaler);
    return lhs;
}

PINLINE b8 operator == (const prime::vec2& lhs, const prime::vec2& rhs)
{
    return prime::vec2::equal(lhs, rhs);
}

PINLINE b8 operator != (const prime::vec2& lhs, const prime::vec2& rhs)
{
    return prime::vec2::notEqual(lhs, rhs);
}

#endif // __cplusplus
