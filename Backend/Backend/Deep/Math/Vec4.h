#pragma once

namespace Deep
{
    // TODO(randomuserhi): Consider making Vec4 and Quaternion different types since their operations are seperate anyway
    //                     so I shouldn't mix them up
    struct Vec4
    {
        Vec4& operator+= (const Vec4& other);
        Vec4& operator-= (const Vec4& other);
        Vec4& operator*= (const float other);
        Vec4& operator/= (const float other);

        union
        {
            float values[4];
            struct
            {
                float x;
                float y;
                float z;
                float w;
            };
        };
    };
    typedef Vec4 Quaternion;

    Vec4 operator+ (Vec4 a, const Vec4& b);
    Vec4 operator- (Vec4 a, const Vec4& b);
    Vec4 operator* (Vec4 v, const float a);
    Vec4 operator* (const float a, Vec4 v);
    float operator* (const Vec4& a, const Vec4& b);
}