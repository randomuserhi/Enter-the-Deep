#pragma once

#include "../Deep.h"

namespace Deep
{
    struct IPv4
    {
        IPv4() :
            a(0), b(0), c(0), d(0), port(0)
        {}

        IPv4(uint8_t a, uint8_t b, uint8_t c, uint8_t d, uint16_t port) :
            a(a), b(b), c(c), d(d), port(port)
        {}

        friend bool operator==(const IPv4& sockA, const IPv4& sockB);

    public:
        static const IPv4 any;

        uint8_t a;
        uint8_t b;
        uint8_t c;
        uint8_t d;
        uint16_t port;
    };
    Deep_Inline bool operator==(const IPv4& lhs, const IPv4& rhs)
    {
        return lhs.a == rhs.a &&
            lhs.b == rhs.b &&
            lhs.c == rhs.c &&
            lhs.d == rhs.d &&
            lhs.port == rhs.port;
    }
}