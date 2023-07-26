#pragma once

#include "Sock.h"

namespace Deep
{
    class Channel
    {
    public:
        Channel(size_t bufferSize)
            : bufferSize(bufferSize), buffer(new uint8_t[bufferSize])
        {}

    private:
        size_t bufferSize;
        uint8_t* const buffer;
        UDPSocket socket;
    };
}