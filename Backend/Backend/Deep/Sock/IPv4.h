#pragma once

#include "../Deep.h"

namespace Deep
{
    struct IPv4
    {
        IPv4() :
            a(0), b(0), c(0), d(0), port(0)
        {}

        IPv4(u_char a, u_char b, u_char c, u_char d, u_short port) :
            a(a), b(b), c(c), d(d), port(port)
        {}

        friend bool operator==(const IPv4& sockA, const IPv4& sockB);

    public:
        static const IPv4 any;

        u_char a;
        u_char b;
        u_char c;
        u_char d;
        u_short port;
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