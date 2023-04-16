#include "../Net.h"

#if defined(DEEP_PLATFORM_WINDOWS)

#include <WinSock2.h>
#include "Net_Windows.h"

namespace Deep
{
	int InitializeSockets()
	{
		WSADATA wsaData;
		if (WSAStartup(MAKEWORD(2, 2), &wsaData) == NO_ERROR)
		{
			return DEEP_SOCKET_NOERROR;
		}
		return DEEP_SOCKET_ERROR;
	}

	int ShutdownSockets()
	{
		const int result = WSACleanup();
		return result == SOCKET_ERROR ? DEEP_SOCKET_ERROR 
			                          : DEEP_SOCKET_NOERROR;
	}
}

#endif