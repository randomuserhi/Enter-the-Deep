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

namespace DeepNetwork
{
	bool InitializeSockets();

	void ShutdownSockets();

	class Server
	{
	private:
		bool CreateSocket();

	public:
		Server();
	};
}
