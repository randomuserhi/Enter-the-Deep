#include "DeepNetwork.h"
#include <iostream>

namespace DeepNetwork
{
	bool IsBigEndian() //https://stackoverflow.com/questions/1001307/detecting-endianness-programmatically-in-a-c-program
	{
		union {
			uint32_t i;
			char c[4];
		} bint = { 0x01020304 };

		return bint.c[0] == 1;
	}

	Server::Server(void (*OnReceiveHandle)(unsigned char*, int, unsigned int, unsigned int))
	{
		this->OnReceiveHandle = OnReceiveHandle;
		
		Buffer = new unsigned char[MaxBufferSize];
	}

	Server::~Server()
	{
		delete[] Buffer;
	}

	void Server::Start(unsigned short Port)
	{
		Socket.Bind(Port);
	}

	void Server::Tick()
	{
		int BytesReceived = Socket.Receive(Buffer, MaxBufferSize, &From);
		if (BytesReceived > 0)
		{
			unsigned int FromAddress = ntohl(From.sin_addr.s_addr);
			unsigned int FromPort = ntohs(From.sin_port);

			if (OnReceiveHandle != nullptr) OnReceiveHandle(Buffer, BytesReceived, FromAddress, FromPort);
		}
	}

	unsigned short Server::GetPort()
	{
		return Socket.GetPort();
	}
}