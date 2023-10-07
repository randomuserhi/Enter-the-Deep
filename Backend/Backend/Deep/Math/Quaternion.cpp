#include <cmath>

#include "./Quaternion.h"

namespace Deep {
    Quaternion& Quaternion::Normalize() {
        float length = std::sqrt(x * x + y * y + z * z + w * w);
        x /= length;
        y /= length;
        z /= length;
        w /= length;
        return *this;
    }

    Quaternion& Quaternion::Inverse() {
        x *= -1;
        y *= -1;
        z *= -1;
        return *this;
    }

    Quaternion::Quaternion(Vec3 axis, float angle) {
        axis.Normalize(); // Must be normalized for the below equation

        /**
         * cos(a) + sin(a)(xi, yj, zk)
         * cos(a) + sin(a)xi + sin(a)yj + sin(a)zk
         */
        angle /= 2.0f;
        float sin = std::sin(angle);
        x = axis.x * sin;
        y = axis.y * sin;
        z = axis.z * sin;
        w = std::cos(angle);

        Normalize();
    }

    Quaternion& Quaternion::operator+= (const Quaternion& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        w += other.w;
        return *this;
    }

    Quaternion operator+ (Quaternion a, const Quaternion& b) {
        return a += b;
    }

    Quaternion& Quaternion::operator-= (const Quaternion& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        w -= other.w;
        return *this;
    }

    Quaternion operator- (Quaternion a, const Quaternion& b) {
        return a -= b;
    }

    Quaternion& Quaternion::operator*= (const float other) {
        x *= other;
        y *= other;
        z *= other;
        w *= other;
        return *this;
    }

    Quaternion& Quaternion::operator/= (const float other) {
        x /= other;
        y /= other;
        z /= other;
        w /= other;
        return *this;
    }

    Quaternion operator* (Quaternion a, const float other) {
        return a *= other;
    }

    Quaternion operator* (const float other, Quaternion a) {
        return a *= other;
    }

    Quaternion operator/ (Quaternion a, const float other) {
        return a /= other;
    }

    float operator* (const Quaternion& a, const Quaternion& b) {
        return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
    }

    Vec3 operator* (const Quaternion& rot, Vec3 v) {
        Mat3 m = rot.toMat3();
        return v *= m;
    }

    Mat3 Quaternion::toMat3() const {
        float w2 = w * w;
        float x2 = x * x;
        float y2 = y * y;
        float z2 = z * z;

        float inverse = 1.0f / (w2 + x2 + y2 + z2);

        x2 *= inverse;
        y2 *= inverse;
        z2 *= inverse;
        w2 *= inverse;

        float xy = x * y * inverse;
        float zw = w * z * inverse;

        float xz = x * z * inverse;
        float yw = w * y * inverse;

        float yz = y * z * inverse;
        float xw = w * x * inverse;

        return {
            x2 - y2 - z2 + w2, 2.0f * (xy - zw)    , 2.0f * (xz + yw)  ,
            2.0f * (xy + zw) , (-x2 + y2 - z2 + w2), 2.0f * (yz - xw)  ,
            2.0f * (xz - yw) , 2.0f * (yz + xw)    , -x2 - y2 + z2 + w2
        };
    }
}