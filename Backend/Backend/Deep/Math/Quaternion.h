#pragma once

namespace Deep {
    struct Quaternion {
        
    };

    Vec3 operator* (const Quaternion& rot, Vec3 v);
}