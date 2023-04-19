#pragma once

#include "Deep.h"

#define DEEP_NETWORK_DEFAULTPORT 57687

#define DEEP_SOCKET_NOERROR 0
#define DEEP_SOCKET_ERROR -1

namespace Deep
{
    bool IsBigEndian();

    struct IPv4
    {
        unsigned char a;
        unsigned char b;
        unsigned char c;
        unsigned char d;
        unsigned short port;

        friend bool operator==(const IPv4& sockA, const IPv4& sockB);
    };
    Deep_Inline bool operator==(const IPv4& lhs, const IPv4& rhs)
    {
        return lhs.a == rhs.a &&
               lhs.b == rhs.b &&
               lhs.c == rhs.c &&
               lhs.d == rhs.d &&
               lhs.port == rhs.port;
    }

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
        int GetSockName(IPv4& address);

        int Open();
        int Close();
        int Bind(unsigned short port);
        int Connect(const IPv4 address);
        int Send(const char* data, int dataSize);
        int SendTo(const char* data, int dataSize, const IPv4 address);
        int Receive(const char* buffer, const int maxBufferSize, int& bytesReceived, IPv4& fromAddress);
    };
}

#if defined(DEEP_PLATFORM_WINDOWS)

#include "Net/Net_Windows.h"

#endif