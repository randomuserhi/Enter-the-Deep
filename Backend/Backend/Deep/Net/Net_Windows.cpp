#include "../Net.h"

#if defined(DEEP_PLATFORM_WINDOWS)

#include "Net_Windows.h"

namespace Deep
{
    Deep_Inline __impl__::SocketAddr ToSocketAddr(const IPv4 ip)
    {
        const unsigned int bitAddress = (ip.a << 24) | (ip.b << 16) | (ip.c << 8) | ip.d;

        __impl__::SocketAddr address;
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
}

#endif