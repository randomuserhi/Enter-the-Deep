#include "DeepNetwork.h"
#include <iostream>

//NOTE :: A lot of this code is not compatible with other platforms, WSAGetLastError (windows only), icotlsocket (icotl for linux) etc
//		  For future reference its probably better to seperate entire code from windows platform and linux etc... rather than only splitting parts of code as shown here

namespace DeepNetwork
{
	bool DEEP_RUNTIME_NETWORK_DEBUG = true; // Enable debugging of connection (during use, doesn't include startup etc...)

	bool InitializeSockets()
	{
		DEEP_RUNTIME_NETWORK_DEBUG = true;

#if PLATFORM == PLATFORM_WINDOWS
		WSADATA WsaData;
		if (WSAStartup(MAKEWORD(2, 2), &WsaData) == NO_ERROR)
		{
			std::cout << "WSA Initialized.\n";
			return true;
		}
		std::cout << "WSA failed to initialize with error = " << WSAGetLastError() << '\n';
		return false;
#else
		std::cout << "WSA not required, platform is not Windows.\n";
		return true;
#endif
	}

	void ShutdownSockets()
	{
		DEEP_RUNTIME_NETWORK_DEBUG = false;

#if PLATFORM == PLATFORM_WINDOWS
		int Result = WSACleanup();
		if (Result == NOERROR)
			std::cout << "WSA successfully cleaned up.\n";
		else
			std::cout << "WSA failed to cleaup with error = " << WSAGetLastError() << ".\n";
#else
		std::cout << "WSA cleaup not required, platform is not Windows.\n";
#endif
	}

	Address::Address(unsigned char A, unsigned char B, unsigned char C, unsigned char D, unsigned short Port)
	{
		this->A = A;
		this->B = B;
		this->C = C;
		this->D = D;
		this->Port = Port;
		GetAddress();
	}

	void Address::GetAddress()
	{
		unsigned int Address = (A << 24) | (B << 16) | (C << 8) | D;

		Formatted.sin_family = AF_INET;
		Formatted.sin_addr.s_addr = htonl(Address);
		Formatted.sin_port = htons(Port);
	}

	inline bool operator==(const Address& LHS, const Address& RHS)
	{
		return (LHS.Formatted.sin_addr.s_addr == RHS.Formatted.sin_addr.s_addr) && (LHS.Formatted.sin_port == RHS.Formatted.sin_port);
	}

	bool Socket::CreateSocket()
	{
		SocketFD = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

		if (SocketFD == INVALID_SOCKET)
		{
			std::cout << "Socket function failed with error = " << WSAGetLastError() << ".\n";
			return false;
		}
		std::cout << "Socket function succeeded.\n";

		//Need to be aware of https://stackoverflow.com/questions/34242622/windows-udp-sockets-recvfrom-fails-with-error-10054
#if PLATFORM == PLATFORM_WINDOWS
#define SIO_UDP_CONNRESET _WSAIOW(IOC_VENDOR, 12)
		BOOL bNewBehavior = FALSE;
		DWORD dwBytesReturned = 0;
		WSAIoctl(SocketFD, SIO_UDP_CONNRESET, &bNewBehavior, sizeof bNewBehavior, NULL, 0, &dwBytesReturned, NULL, NULL);
#endif

		return true;
	}

	bool Socket::CloseSocket() //https://stackoverflow.com/questions/4160347/close-vs-shutdown-socket
	{
		if (SocketFD == INVALID_SOCKET)
		{
			std::cout << "Socket already closed / SocketFD is invalid.\n";
			return true;
		}

		int Result;
#if PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX
		Result = close(SocketFD);
#elif PLATFORM == PLATFORM_WINDOWS
		Result = closesocket(SocketFD);
#endif
		if (Result == SOCKET_ERROR)
		{
			std::cout << "Failed to close socket with error = " << WSAGetLastError() << ".\n";
			return false;
		}
		std::cout << "Closed socket successfully.\n";
		SocketFD = INVALID_SOCKET;
		return true;
	}

	bool Socket::Bind(unsigned short Port)
	{
		sockaddr_in Address;
		Address.sin_family = AF_INET;
		Address.sin_addr.s_addr = INADDR_ANY;
		Address.sin_port = htons(Port);

		if (bind(SocketFD, (const sockaddr*)& Address, sizeof(sockaddr_in)) == SOCKET_ERROR)
		{
			std::cout << "Socket failed to bind.\n";
			return false;
		}
		else
		{
			std::cout << "Socket bound successfully.\n";

			sockaddr_in AssignedAddress;
			socklen_t AssignedAddressLen = sizeof(AssignedAddress);

			//Get assigned port
			if (getsockname(SocketFD, (sockaddr*)& AssignedAddress, &AssignedAddressLen) != NO_ERROR)
				std::cout << "Failed to get socket details.\n";
			else
			{
				this->Port = ntohs(AssignedAddress.sin_port);
				std::cout << "Socket bound to port " << this->Port << ".\n";
			}

			//Set socket to be non-blocking

#if PLATFORM == PLATFORM_MAC || PLATFORM == PLATFORM_UNIX
			int NonBlocking = 1;
			if (fcntl(SocketFD, F_SETFL, O_NONBLOCK, NonBlocking) == -1)
			{
				std::cout << "Failed to set socket to non-blocking.\n";
				return false;
			}
#elif PLATFORM == PLATFORM_WINDOWS
			DWORD NonBlocking = 1;
			if (ioctlsocket(SocketFD, FIONBIO, &NonBlocking) != 0)
			{
				std::cout << "Failed to set socket to non-blocking.\n";
				return false;
			}
#endif

			std::cout << "Successfully set socket to non-blocking.\n";

			return true;
		}
	}

	unsigned short Socket::GetPort()
	{
		return Port;
	}

	bool Socket::Send(const char* Data, int DataSize, sockaddr* Address)
	{
		int SentBytes = sendto(SocketFD, Data, DataSize, 0, Address, sizeof(sockaddr_in));
		if (SentBytes != DataSize)
		{
			if (DEEP_RUNTIME_NETWORK_DEBUG) std::cout << "Failed to send packet to destination with error = " << WSAGetLastError() << ".\n";
			return false;
		}
		//std::cout << "Packet successfully sent.\n";
		return true;
	}

	int Socket::GetRemainingBytes()
	{
		unsigned long RemainingBytes;
		int Result = ioctlsocket(SocketFD, FIONREAD, &RemainingBytes);
		if (Result != NOERROR)
		{
			if (DEEP_RUNTIME_NETWORK_DEBUG) std::cout << "Failed to get remaining bytes with error = " << WSAGetLastError() << ".\n";
			return -1;
		}
		return RemainingBytes;
	}

	int Socket::Receive(unsigned char* const Buffer, unsigned int MaxBufferSize, sockaddr* FromAddress)
	{
		sockaddr_in From;
		socklen_t FromLength = sizeof(From);

		int BytesReceived = recvfrom(SocketFD, (char*)Buffer, MaxBufferSize, 0, FromAddress, &FromLength);

		if (BytesReceived < 0) 
		{
			int Error = WSAGetLastError();
			if (Error != WSAEWOULDBLOCK) //https://stackoverflow.com/questions/17064069/recvfrom-error-10035-using-non-blocking-sockets
			{
				if (DEEP_RUNTIME_NETWORK_DEBUG) std::cout << "Failed to receive packet with error = " << Error << ".\n";
				return BytesReceived;
			}
			else
				return BytesReceived;
		}

		return BytesReceived;
	}

	Socket::Socket()
	{
		CreateSocket();
	}

	Socket::~Socket()
	{
		CloseSocket();
	}
}