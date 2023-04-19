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

        //https://stackoverflow.com/a/17925300/9642458 => Although not allowed by the standard, target compilers
        // support accessing inactive member of union.
        // Additionally, the use of a union also ensures alignment.
        union SocketAddr
        {
            sockaddr sa;
            sockaddr_in sa_in;
        };
    }

    Deep_Inline int Socket::GetSockName(IPv4& address)
    {
        __impl__::SocketAddr sockAddr;
        int assignedAddressLen = sizeof sockAddr;
        if (getsockname(__impl__.socketFD, &sockAddr.sa, &assignedAddressLen) != NO_ERROR)
            return DEEP_SOCKET_ERROR;
        return DEEP_SOCKET_NOERROR;
    }
}