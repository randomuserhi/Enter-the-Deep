#include "Deep.h"
#include "Deep-Containers.h"
#include "Deep-Math.h"
#include "Deep-Engine.h"
#include "Deep-Network.h"

#include <windows.h>
#include <time.h>

// TODO:: Go through all code and add const qualifier to pointers

void Cleanup()
{
	Deep_Network_ShutdownSockets();
}

BOOL WINAPI ExitHandler(DWORD Signal)
{
	Cleanup();
	exit(0);

	return TRUE;
}

void OnReceive(const unsigned char* Buffer, int BytesReceived, unsigned int FromAddress, unsigned int FromPort)
{
	printf("Message received: %i\n", *(const int*)Buffer);
}

Deep_DynArray_Decl(int, int)
Deep_DynArray_Decl(struct Deep_DynArray(int), Deep_DynArray$int)

Deep_UnorderedMap_Decl(int, int, int, int)

int main()
{
	if (!SetConsoleCtrlHandler(ExitHandler, TRUE)) return 1;

	//Deep_CheckMaxAllocationSize();

	struct Deep_ECS ECS;
	Deep_ECS_Create(&ECS);
	Deep_ECS_PrintHierarchy(&ECS);

	getchar();

	Deep_Math_Vector3 vec3 = Deep_Math_Vec3(10, 10, 0);
	DeepMath_Vector3_Scale_InPlace(&vec3, 2);
	printf("%f %f %f\n", vec3.x, vec3.y, vec3.z);

	printf("IsBigEndian: %i.\n", Deep_Network_IsBigEndian());

    Deep_Network_InitializeSockets();

	struct Deep_Network_Server server = Deep_Network_Server_Default;
	server.OnReceiveHandle = &OnReceive;

	Deep_Network_Socket_Open(&server.socket);
	Deep_Network_Server_Start(&server, DEEP_NETWORK_DEFAULTPORT);

	printf("Server started on port: %i.\n", Deep_Network_Server_GetPort(&server));

	int data = 10;

	struct Deep_Network_Address addr = { 127, 0, 0, 1, 56732 };
	while (TRUE)
	{
		Deep_Network_Server_Tick(&server);
		Deep_Network_Address_Format(&addr);
		Deep_Network_Server_Send(&server, (char*)&data, sizeof data, &addr.sockAddr);
	}

	Deep_Network_Server_Close(&server);
    Deep_Network_ShutdownSockets();
}
