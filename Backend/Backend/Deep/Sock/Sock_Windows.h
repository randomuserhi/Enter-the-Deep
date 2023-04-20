#pragma once

#include <WinSock2.h>

namespace Deep
{
    int InitializeSockets();
    int ShutdownSockets();

    namespace __impl__
    {
        struct UDPSocket
        {
            SOCKET socketFD;
        };

        Deep_Inline int GetWSAError()
        {
            return WSAGetLastError();
        }
    }
}