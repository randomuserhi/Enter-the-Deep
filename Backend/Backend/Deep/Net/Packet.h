#pragma once

#include <vector>
#include "Deep.h"
#include "Math/Core.h"

namespace Deep
{
    struct PacketReader
    {
        PacketReader(const char* const data) : data(data) {}

    private:
        const char* const data;
    };

    struct Packet
    {
        Packet() {}
        Packet(size_t size)
        {
            buffer.reserve(size);
        }
         
        // TODO(randomuserhi): https://stackoverflow.com/a/51615364/9642458
        Deep_Inline const byte* Data();
        Deep_Inline size_t Size();

        void Write(byte byte);
        void Write(const byte* bytes, size_t numBytes);
        void Write(int value);
        void Write(Vec3 value);
        void Write(Vec4 value);

    private:
        std::vector<byte> buffer;
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