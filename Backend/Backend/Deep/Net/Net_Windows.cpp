#include "../Net.h"

#if defined(DEEP_PLATFORM_WINDOWS)

#include "Net_Windows.h"

namespace Deep
{
    //https://stackoverflow.com/a/17925300/9642458 => Although not allowed by the standard, target compilers
    // support accessing inactive member of union.
    // Additionally, the use of a union also ensures alignment.
    union SocketAddr
    {
        sockaddr sa;
        sockaddr_in sa_in;
    };

    Deep_Inline SocketAddr ToSocketAddr(const IPv4 ip)
    {
        const unsigned int bitAddress = (ip.a << 24) | (ip.b << 16) | (ip.c << 8) | ip.d;

        SocketAddr address;
        address.sa_in.sin_family = AF_INET;
        address.sa_in.sin_addr.s_addr = htonl(bitAddress);
        address.sa_in.sin_port = htons(ip.port);

        return address;
    }

    int InitializeSockets()
    {
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) == NO_ERROR)
        {
            return DEEP_SOCKET_NOERROR;
        }
        return DEEP_SOCKET_ERROR;
    }

    int ShutdownSockets()
    {
        const int result = WSACleanup();
        return result == SOCKET_ERROR ? DEEP_SOCKET_ERROR 
                                      : DEEP_SOCKET_NOERROR;
    }

    int Socket::GetSockName(IPv4& address)
    {
        SocketAddr sockAddr;
        int assignedAddressLen = sizeof sockAddr;
        if (getsockname(__impl__.socketFD, &sockAddr.sa, &assignedAddressLen) != NO_ERROR)
            return DEEP_SOCKET_ERROR;
        // TODO(randomuserhi): convert to IPv4 address
        return DEEP_SOCKET_NOERROR;
    }
}

#endif