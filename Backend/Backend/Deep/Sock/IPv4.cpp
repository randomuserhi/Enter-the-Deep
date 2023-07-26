#include "IPv4.h"
#include <cassert>
#include <limits>

namespace Deep
{
    IPv4 const IPv4::any{};

    IPv4::IPv4(uint8 a, uint8 b, uint8 c, uint8 d, uint16 port) :
        a(a), b(b), c(c), d(d), port(port)
    {
        // NOTE(randomuserhi): handle uint16 not guaranteed to be a 16 bit integer -> refer to Deep_Types.h
        //                     could use uint16_t instead.
        assert(port < USHRT_MAX);
    }
}