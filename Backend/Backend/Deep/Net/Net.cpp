#include "../Net.h"

namespace Deep
{
    bool IsBigEndian()
    {
        unsigned int x = 1;
        char* c = (char*)&x;
        return (int)*c == 0; // 0 if big endian, 1 if little endian
    }
}