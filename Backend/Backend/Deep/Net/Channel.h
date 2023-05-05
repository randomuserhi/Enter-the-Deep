#pragma once

#include "Sock.h"

namespace Deep
{
    class Channel
    {
    public:
        Channel(size_t bufferSize)
            : bufferSize(bufferSize), buffer(new byte[bufferSize])
        {}

    private:
        size_t bufferSize;
        byte* const buffer;
        UDPSocket socket;
    };
}