#pragma once

#include <vector>
#include "Deep.h"

namespace Deep
{
    class Packet
    {
        std::vector<byte> buffer;

    public:
        const byte* Data();

        Deep_Inline size_t Size();
        void Write(int value);
    };
    Deep_Inline const byte* Packet::Data()
    {
        return buffer.data();
    }
    Deep_Inline size_t Packet::Size()
    {
        return buffer.size();
    }
}