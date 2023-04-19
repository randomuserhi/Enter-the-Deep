#include "../Sock.h"

#if defined(DEEP_PLATFORM_WINDOWS)

#include "Sock_Windows.h"

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

    typedef int socklen_t;

    Deep_Inline SocketAddr ToSocketAddr(const IPv4 ip)
    {
        const unsigned int bitAddress = (ip.a << 24) | (ip.b << 16) | (ip.c << 8) | ip.d;

        SocketAddr address;
        address.sa_in.sin_family = AF_INET;
        address.sa_in.sin_addr.s_addr = htonl(bitAddress);
        address.sa_in.sin_port = htons(ip.port);

        return address;
    }
    int FromSocketAddr(const SocketAddr sockAddr, IPv4& format)
    {
        if (sockAddr.sa.sa_family == AF_INET)
        {
            const unsigned int bitAddress = ntohl(sockAddr.sa_in.sin_addr.s_addr);
            format.a = (bitAddress & 0xFF000000) >> 24;
            format.b = (bitAddress & 0x00FF0000) >> 16;
            format.c = (bitAddress & 0x0000FF00) >> 8;
            format.d = (bitAddress & 0x000000FF);
            format.port = ntohs(sockAddr.sa_in.sin_port);
            
            return DEEP_SOCKET_NOERROR;
        }

        return DEEP_SOCKET_INCOMPATIBLE_ADDRESS_FAMILY;
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
        socklen_t assignedAddressLen = sizeof sockAddr;
        if (getsockname(__impl__.socketFD, &sockAddr.sa, &assignedAddressLen) != NO_ERROR)
            return DEEP_SOCKET_ERROR;
        return FromSocketAddr(sockAddr, address);
    }

    int Socket::GetPeerName(IPv4& address)
    {
        SocketAddr sockAddr;
        socklen_t assignedAddressLen = sizeof sockAddr;
        if (getpeername(__impl__.socketFD, &sockAddr.sa, &assignedAddressLen) != NO_ERROR)
            return DEEP_SOCKET_ERROR;
        return FromSocketAddr(sockAddr, address);
    }

    int Socket::Open()
    {
        SOCKET& socketFD = __impl__.socketFD;
        socketFD = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

        if (socketFD == INVALID_SOCKET)
        {
            return DEEP_SOCKET_ERROR;
        }

        //Need to be aware of https://stackoverflow.com/questions/34242622/windows-udp-sockets-recvfrom-fails-with-error-10054
        #define SIO_UDP_CONNRESET _WSAIOW(IOC_VENDOR, 12)
        bool bNewBehavior = false;
        DWORD dwBytesReturned = 0;
        WSAIoctl(socketFD, SIO_UDP_CONNRESET, &bNewBehavior, sizeof bNewBehavior, NULL, 0, &dwBytesReturned, NULL, NULL);

        return DEEP_SOCKET_NOERROR;
    }

    int Socket::Close()
    {
        SOCKET& socketFD = __impl__.socketFD;
        if (socketFD == INVALID_SOCKET)
        {
            // Socket already closed / SocketFD is invalid
            return DEEP_SOCKET_NOERROR;
        }

        const int result = closesocket(socketFD);
        if (result == SOCKET_ERROR)
        {
            return DEEP_SOCKET_ERROR;
        }
        socketFD = INVALID_SOCKET;
        return DEEP_SOCKET_NOERROR;
    }

    int Socket::Bind(unsigned short port)
    {
        const SOCKET& socketFD = __impl__.socketFD;

        struct sockaddr_in address;
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(port);

        if (bind(socketFD, (struct sockaddr*)&address, sizeof address) == SOCKET_ERROR)
        {
            return DEEP_SOCKET_ERROR;
        }
        
        //Set socket to be non-blocking
        DWORD nonBlocking = 1;
        if (ioctlsocket(socketFD, FIONBIO, &nonBlocking) != 0)
        {
            // Failed to set socket to non-blocking
            return DEEP_SOCKET_ERROR;
        }

        return DEEP_SOCKET_NOERROR;
    }

    int Socket::Connect(const IPv4 address)
    {
        const SOCKET& socketFD = __impl__.socketFD;

        const SocketAddr sockAddr = ToSocketAddr(address);
        if (connect(socketFD, &sockAddr.sa, sizeof sockAddr) != NO_ERROR)
        {
            // Failed to connect socket with error
            return DEEP_SOCKET_ERROR;
        }
        return DEEP_SOCKET_NOERROR;
    }

    int Socket::Send(const char* data, int dataSize)
    {
        const SOCKET& socketFD = __impl__.socketFD;
        const int sentBytes = send(socketFD, data, dataSize, 0);
        if (sentBytes == SOCKET_ERROR)
        {
            return DEEP_SOCKET_ERROR;
        }
        return DEEP_SOCKET_NOERROR;
    }

    int Socket::SendTo(const char* data, int dataSize, const IPv4 address)
    {
        const SOCKET& socketFD = __impl__.socketFD;
        
        const SocketAddr sockAddr = ToSocketAddr(address);
        const int sentBytes = sendto(socketFD, data, dataSize, 0, &sockAddr.sa, sizeof sockAddr);
        if (sentBytes == SOCKET_ERROR)
        {
            return DEEP_SOCKET_ERROR;
        }
        return DEEP_SOCKET_NOERROR;
    }

    int Socket::Receive(char* buffer, const int maxBufferSize, int& bytesReceived, IPv4& fromAddress)
    {
        const SOCKET& socketFD = __impl__.socketFD;

        SocketAddr fromSockAddr = ToSocketAddr(fromAddress);
        socklen_t fromLength = sizeof fromSockAddr;

        bytesReceived = recvfrom(socketFD, buffer, maxBufferSize, 0, &fromSockAddr.sa, &fromLength);

        if (bytesReceived < 0)
        {
            return DEEP_SOCKET_ERROR;
        }

        return DEEP_SOCKET_NOERROR;
    }
}

#endif