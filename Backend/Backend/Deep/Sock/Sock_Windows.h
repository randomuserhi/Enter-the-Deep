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
        public:
            SOCKET socketFD = INVALID_SOCKET;
        };

        Deep_Inline int GetWSAError()
        {
            return WSAGetLastError();
        }
    }
}