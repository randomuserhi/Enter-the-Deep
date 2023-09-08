#include "Vec3.h"

namespace Deep
{
    Vec3& Vec3::operator+= (const Vec3& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    Vec3 operator+ (Vec3 a, const Vec3& b)
    {
        return a += b;
    }

    Vec3& Vec3::operator-= (const Vec3& other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    Vec3 operator- (Vec3 a, const Vec3& b)
    {
        return a -= b;
    }

    float operator* (const Vec3& a, const Vec3& b)
    {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }
}