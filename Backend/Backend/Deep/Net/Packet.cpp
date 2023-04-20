#include "Packet.h"

namespace Deep
{
    void Packet::Write(int value)
    {
        size_t old = buffer.size();
        buffer.resize(buffer.size() + sizeof(int));
        // Fairly sure this is UB, since we are constructing an int object 
        // instead of an array of char objects, so access to the char objects 
        // via the vector is UB.
        // 
        // Reasonable compilers shouldn't care, but by the cpp standard this is UB
        *reinterpret_cast<int*>(buffer.data() + old) = value;
    }
}