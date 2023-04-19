#pragma once

#include <WinSock2.h>
#include "../Net.h"

namespace Deep
{
    int InitializeSockets();
    int ShutdownSockets();
    Deep_Inline int GetWSAError()
    {
        return WSAGetLastError();
    }

    namespace __impl__
    {
        struct Socket
        {
            SOCKET socketFD;
        };
    }
}