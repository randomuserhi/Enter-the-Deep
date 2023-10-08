#pragma once

#include <vector>
#include "Deep.h"

namespace Deep {
    struct PacketReader {
        PacketReader(const uint8* const data) : data(data) {}

    private:
        const uint8* const data;
    };

    struct Packet {
        Packet() {}
        Packet(size_t size) {
            buffer.reserve(size);
        }
         
        // TODO(randomuserhi): https://stackoverflow.com/a/51615364/9642458
        Deep_Inline const uint8* Data();
        Deep_Inline size_t Size();

        void Write(uint8 byte);
        void Write(const uint8* bytes, size_t numBytes);
        void Write(int32 value);
        //void Write(float value);
        //void Write(Vec3 value);
        //void Write(Quaternion value);

        //void WriteHalf(float value);
        //void WriteHalf(Vec3 value);
        //void WriteHalf(Quaternion value);

    private:
        std::vector<uint8> buffer;
    };
    Deep_Inline const uint8* Packet::Data() {
        return buffer.data();
    }
    Deep_Inline size_t Packet::Size() {
        return buffer.size();
    }
}