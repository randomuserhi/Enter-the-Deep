#include <iostream>

#include "DeepEngine.h"
#include "DeepNetwork.h"

#include <windows.h>

void Cleanup()
{
	DeepNetwork::ShutdownSockets();
}

BOOL WINAPI ExitHandler(DWORD Signal) 
{
	Cleanup();
	exit(0);

	return TRUE;
}

void OnReceive(unsigned char* Buffer, int BytesReceived, unsigned int FromAddress, unsigned int FromPort)
{
	std::cout << "Message received: " << *(int*)Buffer << '\n';
}

int main()
{
	if (!SetConsoleCtrlHandler(ExitHandler, TRUE)) return 1;

	std::cout << "IsBigEndian: " << DeepNetwork::IsBigEndian() << ".\n";

	DeepNetwork::InitializeSockets();

	DeepNetwork::Server Server(&OnReceive);

	Server.Start(57687);

	std::cout << "Server started on port: " << Server.GetPort() << ".\n";

	char Data = 10;

	while (true)
	{
		Server.Tick();
		Server.Send(&Data, sizeof(Data), &DeepNetwork::Address(127, 0, 0, 1, 64633));
	}

	DeepNetwork::ShutdownSockets();

	return 0;
}