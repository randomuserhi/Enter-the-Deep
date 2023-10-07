#pragma once

#include "../Deep.h"

namespace Deep {
    struct Vec3 {
        Vec3& operator+= (const Vec3& other);
        Vec3& operator-= (const Vec3& other);
        Vec3& operator*= (const float other);
        Vec3& operator/= (const float other);

        // NOTE(randomuserhi): Fairly sure this format of union inside struct is also UB by
        //                     Cpp abstract machine, but luckily compilers support it as an 
        //                     extension
        union {
            float values[3];
            struct {
                float x;
                float y;
                float z;
            };
        };
    };

    Vec3 operator+ (Vec3 a, const Vec3& b);
    Vec3 operator- (Vec3 a, const Vec3& b);
    Vec3 operator* (Vec3 v, const float a);
    Vec3 operator* (const float a, Vec3 v);
    float operator* (const Vec3& a, const Vec3& b);
}