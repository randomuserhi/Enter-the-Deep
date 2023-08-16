#pragma once

#include "../Deep.h"

namespace Deep
{
    Vec3 operator+ (Vec3 a, const Vec3& b);
    Vec3 operator- (Vec3 a, const Vec3& b);
    float operator* (const Vec3& a, const Vec3& b);

    struct Vec3
    {
        Vec3& operator+= (const Vec3& other);
        Vec3& operator-= (const Vec3& other);

        // NOTE(randomuserhi): Fairly sure this format of union inside struct is also UB by
        //                     Cpp abstract machine, but luckily compilers support it as an 
        //                     extension
        union
        {
            float values[3];
            struct
            {
                float x;
                float y;
                float z;
            };
        };
    };


    // TODO(randomuserhi): Consider making Vec4 and Quaternion different types since their operations are seperate anyway
    //                     so I shouldn't mix them up
    struct Vec4
    {
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
}