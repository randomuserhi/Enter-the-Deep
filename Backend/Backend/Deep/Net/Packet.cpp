#include <winsock2.h>

#include "Packet.h"

namespace Deep
{
    void Packet::Write(byte byte)
    {
        buffer.push_back(byte);
    }

    // NOTE(randomuserhi): This writes raw bytes to the buffer and does not account
    //                     for endianess. For ASCII strings or formats where data only
    //                     spans 1 byte, this works fine.
    void Packet::Write(const byte* bytes, size_t numBytes)
    {
        size_t old = buffer.size();
        buffer.resize(buffer.size() + numBytes);
        // Fairly sure this is UB to the abstract Cpp engine, since no char objects
        // are constructed and besides, we don't construct them as array elements
        // so adjacent access is still UB.
        // 
        // Reasonable compilers shouldn't care, but by the abstract cpp engine this is UB
        memcpy(buffer.data() + old, bytes, numBytes);
    }

    void Packet::Write(int value)
    {
        size_t old = buffer.size();
        buffer.resize(buffer.size() + sizeof(int));
        // Fairly sure this is UB to the abstract Cpp engine, since we are 
        // constructing an int object instead of an array of char objects, 
        // so access to the char objects via the vector is UB.
        // 
        // Reasonable compilers shouldn't care, but by the cpp standard this is UB
        *reinterpret_cast<int*>(buffer.data() + old) = htonl(value);
    }
}