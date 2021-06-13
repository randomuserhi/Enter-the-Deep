#include "DeepNetwork.h"

bool DeepNetwork::InitializeSockets()
{
	#if PLATFORM == PLATFORM_WINDOWS
		WSADATA WsaData;
		return WSAStartup(MAKEWORD(2, 2), &WsaData) == NO_ERROR;
	#else
		return true;
	#endif
}

void DeepNetwork::ShutdownSockets()
{
	#if PLATFORM == PLATFORM_WINDOWS
			WSACleanup();
	#endif
}

DeepNetwork::Server::Server()
{
	
}

bool DeepNetwork::Server::CreateSocket() //TODO:: readup on this shit => no idea what it does
{
	int Handle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); //https://stackoverflow.com/questions/1953639/is-it-safe-to-cast-socket-to-int-under-win64 => bad practice need to change

	if (Handle <= 0)
	{
		return false;
	}

	return true;
}