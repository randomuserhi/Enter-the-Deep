#include "../Sock.h"

namespace Deep
{
    bool IsBigEndian()
    {
        u_int x = 1;
        char* c = (char*)&x;
        return (int)*c == 0; // 0 if big endian, 1 if little endian
    }
}