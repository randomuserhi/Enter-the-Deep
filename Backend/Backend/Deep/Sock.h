#pragma once

#include "Deep.h"

#define DEEP_NETWORK_DEFAULTPORT (57687)

#define DEEP_SOCKET_NOERROR (0)
#define DEEP_SOCKET_ERROR (-1)
#define DEEP_SOCKET_UNKNOWN_ADDRESS_FAMILY (-2)
#define DEEP_SOCKET_INCOMPATIBLE_ADDRESS_FAMILY (-3)

#include "Sock/AF_INET.h"

#if defined(DEEP_PLATFORM_WINDOWS)

#include "Sock/Sock_Windows.h"

#endif

namespace Deep
{
    bool IsBigEndian();

    // This namespace is used for storing OS implementation specifics
    // NOTE(randomuserhi): They can still be accessed by the user via __impl__ to allow them to write 
    //                     OS specific code.
    //                     It is ill-advised to rely on this in normal use-cases as it may change 
    //                     between compilation on different OS.
    //                     Only specific definitions that MUST be visible or that are useful to be exposed
    //                     for OS specific reasons will be found under __impl__ in this header
    namespace __impl__
    {
        struct Socket; // Stores implementation specific socket information such as Handles etc...
    }

    class Socket
    {
        __impl__::Socket __impl__;

    public:
        Socket() : __impl__() {}

        int GetSockName(IPv4& address);
        
        int GetPeerName(IPv4& address);

        int Open();
        int Close();
        int Bind(u_short port = 0);
        int Connect(const IPv4 address);
        //int Send(const char* data, int dataSize);
        //int SendTo(const char* data, int dataSize, const IPv4 address);
        //int Receive(const char* buffer, const int maxBufferSize, int& bytesReceived, IPv4& fromAddress);
    };
}