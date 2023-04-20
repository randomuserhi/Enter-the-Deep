#pragma once

#include "Sock.h"

namespace Deep
{
    class Channel
    {
        size_t bufferSize;
        byte* const buffer;
        UDPSocket socket;

    public:
        Channel(size_t bufferSize) 
            : bufferSize(bufferSize), buffer(new byte[bufferSize])
        {

        }
    };
}