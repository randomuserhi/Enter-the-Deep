#include <iostream>

#include "Deep.h"
#include "Sock.h"

#define DEEP_DEBUG_MEMORY
#include "Debug/Memory.h"

// TODO(randomuserhi): Documentation, I need to stay on top of documentation
//                     in code docs along side doc website

int main()
{
    Deep::StartMemoryDebug();

    std::cout << "Hello World!" << std::endl;
    Deep::InitializeSockets();
    Deep::Socket socket;
    socket.Open();
    socket.Bind();
    Deep::IPv4 address;
    socket.GetSockName(address);
    std::cout << static_cast<u_int>(address.a)
        << ":" << static_cast<u_int>(address.b)
        << ":" << static_cast<u_int>(address.c)
        << ":" << static_cast<u_int>(address.d)
        << ":" << address.port << std::endl;
    socket.Close();
    Deep::ShutdownSockets();

    Deep::PrintAllocationMap();
    Deep::EndMemoryDebug();
}