#include <stdio.h>
#include <stdint.h>

#include "DeepNetwork.h"

#if PLATFORM == PLATFORM_WINDOWS

const Deep_Network_Server DeepNetwork_Server_Default = {.maxBufferSize = 256, .OnReceiveHandle = NULL};

void DeepNetwork_Server_Start(Deep_Network_Server* const deepServer, unsigned short port)
{
	deepServer->buffer = (unsigned char*)malloc(deepServer->maxBufferSize * sizeof(unsigned char*));
	DeepNetwork_Socket_Bind(&deepServer->socket, port);
}

void DeepNetwork_Server_Close(Deep_Network_Server* const deepServer)
{
	DeepNetwork_Socket_Close(&deepServer->socket);
	free(deepServer->buffer);
}

void DeepNetwork_Server_Tick(Deep_Network_Server* const deepServer)
{
	while (DeepNetwork_Socket_GetRemainingBytes(&deepServer->socket) > 0)
	{
		int bytesReceived = DeepNetwork_Socket_Receive(&deepServer->socket, deepServer->buffer, deepServer->maxBufferSize, &deepServer->from);
		if (bytesReceived > 0)
		{
			unsigned int fromAddress = ntohl(deepServer->from.sa_in.sin_addr.s_addr);
			unsigned int fromPort = ntohs(deepServer->from.sa_in.sin_port);

			if (deepServer->OnReceiveHandle) deepServer->OnReceiveHandle(deepServer->buffer, bytesReceived, fromAddress, fromPort);
		}
	}
}

#endif