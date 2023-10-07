#include "./Vec3.h"

namespace Deep {
    Vec3& Vec3::operator+= (const Vec3& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    Vec3 operator+ (Vec3 a, const Vec3& b) {
        return a += b;
    }

    Vec3& Vec3::operator-= (const Vec3& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    Vec3 operator- (Vec3 a, const Vec3& b) {
        return a -= b;
    }

    Vec3& Vec3::operator*= (const float other) {
        x *= other;
        y *= other;
        z *= other;
        return *this;
    }

    Vec3& Vec3::operator/= (const float other) {
        x /= other;
        y /= other;
        z /= other;
        return *this;
    }

    Vec3 operator* (Vec3 a, const float other) {
        return a *= other;
    }

    Vec3 operator* (const float other, Vec3 a) {
        return a *= other;
    }

    Vec3 operator/ (Vec3 a, const float other) {
        return a /= other;
    }

    float operator* (const Vec3& a, const Vec3& b) {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    Vec3& Vec3::operator*= (const Mat3& m) {
        x = m.m00 * x + m.m01 * y + m.m02 * z;
        y = m.m10 * x + m.m11 * y + m.m12 * z;
        z = m.m20 * x + m.m21 * y + m.m22 * z;
        return *this;
    }

    Vec3 operator* (Vec3 v, const Mat3& m) {
        v.x = m.m00 * v.x + m.m01 * v.y + m.m02 * v.z;
        v.y = m.m10 * v.x + m.m11 * v.y + m.m12 * v.z;
        v.z = m.m20 * v.x + m.m21 * v.y + m.m22 * v.z;
        return v;
    }
}