#pragma once

namespace Deep {
    struct Mat3 {
        /**
         * (00, 10, 20)
         * (01, 11, 21)
         * (02, 12, 22)
         */
        union {
            float values[9];
            // NOTE(randomuserhi): order of values matter for specific memory access patterns
            struct {
                float m00;
                float m01;
                float m02;
                float m10;
                float m11;
                float m12;
                float m20;
                float m21;
                float m22;
            };
        };
    };
}