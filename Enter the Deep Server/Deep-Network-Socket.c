#include <stdio.h>
#include <stdint.h>

#include "Deep-Network.h"

const Deep_Network_Address DeepNetwork_Address_Default = { 127, 0, 0, 1, 0 };
const Deep_Network_Socket DeepNetwork_Socket_Default = { INVALID_SOCKET, DEEP_NETWORK_DEFAULTPORT };

#if PLATFORM == PLATFORM_WINDOWS

BOOL DeepNetwork_IsBigEndian() //https://stackoverflow.com/questions/6136010/is-using-an-union-in-place-of-a-cast-well-defined
{
	uint32_t i = 1;
	return i == htonl(i);
}

BOOL DeepNetwork_InitializeSockets()
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) == NO_ERROR)
	{
		printf("WSA Initialized.\n");
		return TRUE;
	}
	printf("WSA failed to initialize with error = %i\n", WSAGetLastError());
	return FALSE;
}

void DeepNetwork_ShutdownSockets()
{
	int result = WSACleanup();
	if (result == NOERROR)
		printf("WSA successfully cleaned up.\n");
	else
		printf("WSA failed to cleaup with error = %i.\n", WSAGetLastError());
}

void DeepNetwork_Address_Format(Deep_Network_Address* const address)
{
	unsigned int BitAddress = (address->a << 24) | (address->b << 16) | (address->c << 8) | address->d;

	address->sockAddr.sa_in.sin_family = AF_INET;
	address->sockAddr.sa_in.sin_addr.s_addr = htonl(BitAddress);
	address->sockAddr.sa_in.sin_port = htons(address->port);
}

BOOL DeepNetwork_Address_Equal(const Deep_Network_Address* lhs, const Deep_Network_Address* rhs)
{
	return (lhs->sockAddr.sa_in.sin_addr.s_addr == rhs->sockAddr.sa_in.sin_addr.s_addr) && (lhs->sockAddr.sa_in.sin_port == rhs->sockAddr.sa_in.sin_port);
}

unsigned short DeepNetwork_socket_GetPort(Deep_Network_Socket* const deepSocket)
{
	return deepSocket->$port;
}

int DeepNetwork_Socket_Open(Deep_Network_Socket* const deepSocket)
{
	deepSocket->socketFD = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if (deepSocket->socketFD == INVALID_SOCKET)
	{
		int err = WSAGetLastError();
		printf("Socket function failed with error = %i.\n", err);
		return err;
	}
	printf("Socket function succeeded.\n");

	//Need to be aware of https://stackoverflow.com/questions/34242622/windows-udp-sockets-recvfrom-fails-with-error-10054
	#define SIO_UDP_CONNRESET _WSAIOW(IOC_VENDOR, 12)
	BOOL bNewBehavior = FALSE;
	DWORD dwBytesReturned = 0;
	WSAIoctl(deepSocket->socketFD, SIO_UDP_CONNRESET, &bNewBehavior, sizeof bNewBehavior, NULL, 0, &dwBytesReturned, NULL, NULL);

	return DEEP_NETWORK_NOERROR;
}
int DeepNetwork_Socket_Close(Deep_Network_Socket* const deepSocket)
{
	if (deepSocket->socketFD == INVALID_SOCKET)
	{
		printf("Socket already closed / SocketFD is invalid.\n");
		return DEEP_NETWORK_NOERROR;
	}

	int result = closesocket(deepSocket->socketFD);
	if (result == SOCKET_ERROR)
	{
		int err = WSAGetLastError();
		printf("Failed to close socket with error = %i.\n", err);
		return err;
	}
	printf("Closed socket successfully.\n");
	deepSocket->socketFD = INVALID_SOCKET;
	return DEEP_NETWORK_NOERROR;
}

int DeepNetwork_Socket_Bind(Deep_Network_Socket* const deepSocket, unsigned short port)
{
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);

	if (bind(deepSocket->socketFD, (const struct sockaddr*)&address, sizeof address) == SOCKET_ERROR)
	{
		int err = WSAGetLastError();
		printf("Socket failed to bind with error %i.\n", err);
		return err;
	}
	else
	{
		printf("Socket bound successfully.\n");

		Deep_SocketAddr assignedAddress;
		socklen_t assignedAddressLen = sizeof assignedAddress;

		//Get assigned port
		if (getsockname(deepSocket->socketFD, &assignedAddress.sa, &assignedAddressLen) != NO_ERROR)
			printf("Failed to get socket details.\n");
		else
		{
			deepSocket->$port = ntohs(assignedAddress.sa_in.sin_port);
			printf("Socket bound to port %i.\n", deepSocket->$port);
		}

		//Set socket to be non-blocking

		DWORD NonBlocking = 1;
		if (ioctlsocket(deepSocket->socketFD, FIONBIO, &NonBlocking) != 0)
		{
			printf("Failed to set socket to non-blocking.\n");
			return DEEP_NETWORK_ERROR;
		}

		printf("Successfully set socket to non-blocking.\n");

		return DEEP_NETWORK_NOERROR;
	}
}

int DeepNetwork_Socket_GetRemainingBytes(Deep_Network_Socket* const deepSocket)
{
	u_long remainingBytes;
	int result = ioctlsocket(deepSocket->socketFD, FIONREAD, &remainingBytes);
	if (result != NOERROR)
	{
		printf("Failed to get remaining bytes with error = %i.\n", WSAGetLastError());
		return DEEP_NETWORK_ERROR;
	}
	return remainingBytes;
}

int DeepNetwork_Socket_Send(Deep_Network_Socket* const deepSocket, const char* const data, int dataSize, Deep_SocketAddr* address)
{
	int SentBytes = sendto(deepSocket->socketFD, data, dataSize, 0, &address->sa, sizeof *address);
	if (SentBytes != dataSize)
	{
		int err = WSAGetLastError();
		printf("Failed to send packet to destination with error = %i.\n", err);
		return err;
	}
	//printf("Packet successfully sent.\n");
	return DEEP_NETWORK_NOERROR;
}

int DeepNetwork_Socket_Receive(Deep_Network_Socket* const deepSocket, char* const buffer, int maxBufferSize, Deep_SocketAddr* fromAddress)
{
	struct sockaddr_in from;
	socklen_t fromLength = sizeof from;

	int BytesReceived = recvfrom(deepSocket->socketFD, (char*)buffer, maxBufferSize, 0, &fromAddress->sa, &fromLength);

	if (BytesReceived < 0)
	{
		int Error = WSAGetLastError();
		if (Error != WSAEWOULDBLOCK) //https://stackoverflow.com/questions/17064069/recvfrom-error-10035-using-non-blocking-sockets
		{
			printf("Failed to receive packet with error = %i.\n", Error);
			return DEEP_NETWORK_ERROR;
		}
		else
			return DEEP_NETWORK_ERROR;
	}

	return BytesReceived;
}
#endif