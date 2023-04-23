#include <iostream>

#include "Deep.h"
#include "Net.h"

// https://stackoverflow.com/a/62047818/9642458
#include <chrono>
#include <thread>

// NOTE(randomuserhi): Needs to be included after all standard library includes to 
//                     prevent overwritting malloc and new in their code.
#define DEEP_DEBUG_MEMORY
#include "DebugUtil/Memory.h"

// TODO(randomuserhi): Documentation, I need to stay on top of documentation
//                     in code docs along side doc website

int main()
{
    Deep::StartMemoryDebug();

    std::cout << "Hello World!" << std::endl;
    Deep::InitializeSockets();
    Deep::UDPSocket socket;
    socket.Open();
    socket.Connect(Deep::IPv4(127, 0, 0, 1, 1000));
    Deep::IPv4 address;
    socket.GetPeerName(address);
    std::cout << static_cast<u_int>(address.a)
       << ":" << static_cast<u_int>(address.b)
       << ":" << static_cast<u_int>(address.c)
       << ":" << static_cast<u_int>(address.d)
       << ":" << address.port << std::endl;

    const byte data[] = "That's crazy";

    std::cout << sizeof data << std::endl;

    while (true)
    {
        Deep::Packet packet;
        packet.Write(10);
        packet.Write(data, sizeof data);

        socket.Send(packet.Data(), packet.Size());

        using namespace std::chrono_literals;
        std::this_thread::sleep_for(100ms);
    };

    socket.Close();
    Deep::ShutdownSockets();

    Deep::PrintAllocationMap();
    Deep::EndMemoryDebug();
}