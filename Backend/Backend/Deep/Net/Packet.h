#pragma once

#include <vector>
#include "Deep.h"

namespace Deep
{
    class Packet
    {
        std::vector<byte> buffer;

    public:
        Deep_Inline const byte* Data();
        Deep_Inline size_t Size();
        
        void Write(byte byte);
        void Write(const byte* bytes, size_t numBytes);
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