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

typedef union 
{
	struct sockaddr sa;
	struct sockaddr_in sa_in;
} Deep_SocketAddr;

BOOL DeepNetwork_InitializeSockets();
void DeepNetwork_ShutdownSockets();

BOOL DeepNetwork_IsBigEndian();

typedef struct
{
	unsigned char a;
	unsigned char b;
	unsigned char c;
	unsigned char d;
	unsigned short port;

	Deep_SocketAddr sockAddr;
} Deep_Network_Address;
extern const Deep_Network_Address DeepNetwork_Address_Default;

void DeepNetwork_Address_Format(Deep_Network_Address* const address);
BOOL DeepNetwork_Address_Equal(const Deep_Network_Address* lhs, const Deep_Network_Address* rhs);

typedef struct
{
	SOCKET socketFD;
	unsigned short _port;
} Deep_Network_Socket;
extern const Deep_Network_Socket DeepNetwork_Socket_Default;

unsigned short DeepNetwork_socket_GetPort(Deep_Network_Socket* const deepSocket);

int DeepNetwork_Socket_Open(Deep_Network_Socket* const deepSocket);
int DeepNetwork_Socket_Close(Deep_Network_Socket* const deepSocket);

int DeepNetwork_Socket_Bind(Deep_Network_Socket* const deepSocket, unsigned short port);

int DeepNetwork_Socket_GetRemainingBytes(Deep_Network_Socket* const deepSocket);

int DeepNetwork_Socket_Send(Deep_Network_Socket* const deepSocket, const char* const data, int dataSize, Deep_SocketAddr* address);
Deep_Inline int DeepNetwork_Socket_Send_DeepAddress(Deep_Network_Socket* const deepSocket, const char* const data, int dataSize, Deep_Network_Address* address)
{
	return DeepNetwork_Socket_Send(deepSocket, data, dataSize, &address->sockAddr);
};

int DeepNetwork_Socket_Receive(Deep_Network_Socket* const deepSocket, char* const buffer, int maxBufferSize, Deep_SocketAddr* fromAddress);

#endif

typedef struct
{
	Deep_Network_Socket socket;
	Deep_SocketAddr from;

	unsigned char* buffer;
	unsigned int maxBufferSize;

	void (*OnReceiveHandle)(unsigned char*, int, unsigned int, unsigned int);
} Deep_Network_Server;
extern const Deep_Network_Server DeepNetwork_Server_Default;

Deep_Inline unsigned short DeepNetwork_Server_GetPort(Deep_Network_Server* const deepServer)
{
	return deepServer->socket._port;
};
void DeepNetwork_Server_Start(Deep_Network_Server* const deepServer, unsigned short port);
void DeepNetwork_Server_Close(Deep_Network_Server* const deepServer);
void DeepNetwork_Server_Tick(Deep_Network_Server* const deepServer);

Deep_Inline int DeepNetwork_Server_Send(Deep_Network_Server* const deepServer, const char* const Data, int DataSize, Deep_SocketAddr* Address)
{
	return DeepNetwork_Socket_Send(&deepServer->socket, Data, DataSize, Address);
};