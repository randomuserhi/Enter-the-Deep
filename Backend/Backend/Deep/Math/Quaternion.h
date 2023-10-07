#pragma once

#include "./Vec3.h";
#include "./Vec4.h";
#include "./Mat3.h";

namespace Deep {
    struct Quaternion {
        Quaternion& operator+= (const Quaternion& other);
        Quaternion& operator-= (const Quaternion& other);
        Quaternion& operator*= (const float other);
        Quaternion& operator/= (const float other);

        Mat3 toMat3() const;

        union {
            float values[4];
            struct {
                float x;
                float y;
                float z;
                float w;
            };
            Vec4 vector;
        };
    };

    Quaternion operator+ (Quaternion a, const Quaternion& b);
    Quaternion operator- (Quaternion a, const Quaternion& b);
    Quaternion operator* (Quaternion v, const float a);
    Quaternion operator* (const float a, Quaternion v);
    float operator* (const Quaternion& a, const Quaternion& b);

    Vec3 operator* (const Quaternion& rot, Vec3 v);
}