#pragma once

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

#include "Deep.h"

#define DEEP_NETWORK_DEFAULTPORT 57687
#define DEEP_NETWORK_NOERROR 0
#define DEEP_NETWORK_ERROR -1

#if PLATFORM == PLATFORM_WINDOWS

typedef int socklen_t;

union Deep_SocketAddr
{
	struct sockaddr sa;
	struct sockaddr_in sa_in;
};

BOOL DeepNetwork_InitializeSockets();
void DeepNetwork_ShutdownSockets();

BOOL DeepNetwork_IsBigEndian();

struct Deep_Network_Address
{
	unsigned char a;
	unsigned char b;
	unsigned char c;
	unsigned char d;
	unsigned short port;

	union Deep_SocketAddr sockAddr;
};
extern const struct Deep_Network_Address DeepNetwork_Address_Default;

void DeepNetwork_Address_Format(struct Deep_Network_Address* const address);
BOOL DeepNetwork_Address_Equal(const struct Deep_Network_Address* lhs, const struct Deep_Network_Address* rhs);

struct Deep_Network_Socket
{
	SOCKET socketFD;
	unsigned short $port;
};
extern const struct Deep_Network_Socket DeepNetwork_Socket_Default;

unsigned short DeepNetwork_socket_GetPort(struct Deep_Network_Socket* const deepSocket);

int DeepNetwork_Socket_Open(struct Deep_Network_Socket* const deepSocket);
int DeepNetwork_Socket_Close(struct Deep_Network_Socket* const deepSocket);

int DeepNetwork_Socket_Bind(struct Deep_Network_Socket* const deepSocket, unsigned short port);

int DeepNetwork_Socket_GetRemainingBytes(struct Deep_Network_Socket* const deepSocket);

int DeepNetwork_Socket_Send(struct Deep_Network_Socket* const deepSocket, const char* const data, int dataSize, union Deep_SocketAddr* address);
Deep$Force_Inline int DeepNetwork_Socket_Send_DeepAddress(struct Deep_Network_Socket* const deepSocket, const char* const data, int dataSize, struct Deep_Network_Address* address)
{
	return DeepNetwork_Socket_Send(deepSocket, data, dataSize, &address->sockAddr);
};

int DeepNetwork_Socket_Receive(struct Deep_Network_Socket* const deepSocket, char* const buffer, int maxBufferSize, union Deep_SocketAddr* fromAddress);

#endif

struct Deep_Network_Server
{
	struct Deep_Network_Socket socket;
	union Deep_SocketAddr from;

	unsigned char* buffer;
	unsigned int maxBufferSize;

	void (*OnReceiveHandle)(unsigned char*, int, unsigned int, unsigned int);
};
extern const struct Deep_Network_Server DeepNetwork_Server_Default;

Deep$Force_Inline unsigned short DeepNetwork_Server_GetPort(struct Deep_Network_Server* const deepServer)
{
	return deepServer->socket.$port;
};
void DeepNetwork_Server_Start(struct Deep_Network_Server* const deepServer, unsigned short port);
void DeepNetwork_Server_Close(struct Deep_Network_Server* const deepServer);
void DeepNetwork_Server_Tick(struct Deep_Network_Server* const deepServer);

Deep$Force_Inline int DeepNetwork_Server_Send(struct Deep_Network_Server* const deepServer, const char* const Data, int DataSize, union Deep_SocketAddr* Address)
{
	return DeepNetwork_Socket_Send(&deepServer->socket, Data, DataSize, Address);
};