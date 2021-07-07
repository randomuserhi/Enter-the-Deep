#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "Deep.h"
#include "DeepMath.h"
#include "DeepEngine.h"
#include "DeepNetwork.h"

#include <windows.h>

void Cleanup()
{
	DeepNetwork_ShutdownSockets();
}

BOOL WINAPI ExitHandler(DWORD Signal)
{
	Cleanup();
	exit(0);

	return TRUE;
}

void OnReceive(unsigned char* Buffer, int BytesReceived, unsigned int FromAddress, unsigned int FromPort)
{
	printf("Message received: %i\n", *(int*)Buffer);
}

int main()
{
	if (!SetConsoleCtrlHandler(ExitHandler, TRUE)) return 1;

	Deep_Math_Vector3 vec3 = Deep_Math_Vec3(10, 10, 0);
	DeepMath_Vector3_Scale_InPlace(&vec3, 2);
	printf("%f %f %f\n", vec3.x, vec3.y, vec3.z);

	printf("IsBigEndian: %i.\n", DeepNetwork_IsBigEndian());

    DeepNetwork_InitializeSockets();

	Deep_Network_Server server = DeepNetwork_Server_Default;
	server.OnReceiveHandle = &OnReceive;

	DeepNetwork_Socket_Open(&server.socket);
	DeepNetwork_Server_Start(&server, DEEP_NETWORK_DEFAULTPORT);

	printf("Server started on port: %i.\n", DeepNetwork_Server_GetPort(&server));

	int data = 10;

	while (TRUE)
	{
		DeepNetwork_Server_Tick(&server);
		Deep_Network_Address addr = { 127, 0, 0, 1, 56732 };
		DeepNetwork_Address_Format(&addr);
		DeepNetwork_Server_Send(&server, (char*)&data, sizeof data, &addr.sockAddr);
	}

	DeepNetwork_Server_Close(&server);
    DeepNetwork_ShutdownSockets();
}
