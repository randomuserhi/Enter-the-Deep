#include "./Quaternion.h"

namespace Deep {
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
        Mat3 mat;

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

        mat.values[0] = x2 - y2 - z2 + w2;
        mat.values[1] = 2.0f * (xy - zw);
        mat.values[2] = 2.0f * (xz + yw);

        mat.values[3] = 2.0f * (xy + zw);
        mat.values[4] = (-x2 + y2 - z2 + w2);
        mat.values[5] = 2.0f * (yz - xw);

        mat.values[6] = 2.0f * (xz - yw);
        mat.values[7] = 2.0f * (yz + xw);
        mat.values[8] = -x2 - y2 + z2 + w2;

        return mat;
    }
}