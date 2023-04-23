#pragma once

#include "../Deep.h"

namespace Deep
{
    // NOTE(randomuserhi): Fairly sure this format of union inside struct is also UB by
    //                     Cpp abstract machine, but luckily compilers support it as an 
    //                     extension

    struct Vec3
    {
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
    typedef Vec3 Vec2;

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