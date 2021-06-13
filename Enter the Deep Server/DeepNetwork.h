#pragma once

// https://gafferongames.com/post/sending_and_receiving_packets/

#define PLATFORM_WINDOWS  1
#define PLATFORM_MAC      2
#define PLATFORM_UNIX     3

#if defined(_WIN32)
	#define PLATFORM PLATFORM_WINDOWS
#elif defined(__APPLE__)
	#define PLATFORM PLATFORM_MAC
#else
	#define PLATFORM PLATFORM_UNIX
#endif

#if PLATFORM == PLATFORM_WINDOWS
	#include <winsock2.h>
#elif PLATFORM == PLATFORM_MAC || 
	PLATFORM == PLATFORM_UNIX

	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <fcntl.h>
#endif

#if PLATFORM == PLATFORM_WINDOWS
	typedef int socklen_t;
#endif

namespace DeepNetwork
{
	bool InitializeSockets();

	void ShutdownSockets();

	bool IsBigEndian(void);

	class Address
	{
	private:
		unsigned char A;
		unsigned char B;
		unsigned char C;
		unsigned char D;
		unsigned short Port;

		void GetAddress();

	public:
		Address(unsigned char A = 127, unsigned char B = 0, unsigned char C = 0, unsigned char D = 1, unsigned short Port = 0);

		sockaddr_in Formatted;

		friend inline bool operator ==(const Address& LHS, const Address& RHS);
		friend inline bool operator !=(const Address& LHS, const Address& RHS) { return !(LHS == RHS); }
	};

	class Socket
	{
	private:
		SOCKET SocketFD = INVALID_SOCKET; //Socket File Descriptor (as returned from socket function)
		unsigned short Port;

		bool CreateSocket();
		bool CloseSocket();

	public:
		Socket();
		~Socket();

		unsigned short GetPort();
		bool Bind(unsigned short Port);

		bool Send(const char* const Data, int DataSize, sockaddr* Address);
		inline bool Send(const char* const Data, int DataSize, sockaddr_in* Address)
		{
			return DeepNetwork::Socket::Send(Data, DataSize, (sockaddr*)Address);
		}
		inline bool Send(const char* const Data, int DataSize, Address* Address)
		{
			return DeepNetwork::Socket::Send(Data, DataSize, (sockaddr*) & (Address->Formatted));
		}

		int Receive(unsigned char* const Buffer, unsigned int MaxBufferSize, sockaddr* From);
		inline int Receive(unsigned char* const Buffer, unsigned int MaxBufferSize, sockaddr_in* From)
		{
			return Receive(Buffer, MaxBufferSize, (sockaddr*)From);
		}
	};

	class Server
	{
	private:
		Socket Socket;
		sockaddr_in From;

	public:
		void (*OnReceiveHandle)(unsigned char*, int, unsigned int, unsigned int) = nullptr;

		Server(void (*OnReceiveHandle)(unsigned char*, int, unsigned int, unsigned int));
		~Server();

		unsigned char* Buffer;
		unsigned int MaxBufferSize = 256; //Size in bytes

		void Start(unsigned short Port);
		void Tick();

		unsigned short GetPort();

		inline bool Send(const char* const Data, int DataSize, sockaddr* Address)
		{
			return Socket.Send(Data, DataSize, Address);
		}
		inline bool Send(const char* const Data, int DataSize, sockaddr_in* Address)
		{
			return Socket.Send(Data, DataSize, Address);
		}
		inline bool Send(const char* const Data, int DataSize, Address* Address)
		{
			return Socket.Send(Data, DataSize, Address);
		}
	};
}
