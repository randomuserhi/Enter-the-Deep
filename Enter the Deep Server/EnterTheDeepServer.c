#include "Deep.h"
#include "Deep_Containers.h"
#include "Deep_Math.h"
#include "Deep_Engine.h"
#include "Deep_Network.h"
#include "Deep_String.h"

#include <windows.h>
#include <time.h>

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

void OnReceive(const char* Buffer, int BytesReceived, unsigned int FromAddress, unsigned int FromPort)
{
	printf("Message received: %i\n", *(const int*)Buffer);
}

int main()
{
	if (!SetConsoleCtrlHandler(ExitHandler, TRUE)) return 1;

	struct Deep_ECS ECS;
	Deep_ECS_Create(&ECS);

	Deep_ECS_CreateComponent(&ECS, "Component Test", sizeof(int));

	const Deep_ECS_Handle type[] = { DEEP_ECS_ID, 10, 11, 12 };
	struct Deep_ECS_Archetype* archetype = Deep_ECS_GetArchetype(&ECS, type, 4);
	struct Deep_ECS_Reference reference = Deep_ECS_Archetype_Push(&ECS, archetype);
	((struct Deep_ECS_Id*)archetype->components.values->values)[reference.index].name = "Entity Test";

	Deep_ECS_Handle handle = 11;
	*Deep_UnorderedMap_Insert(Deep_ECS_Handle, Deep_ECS_Reference)(&ECS.hierarchy, Deep_UnorderedMap_Hash(&handle, sizeof handle, DEEP_UNORDEREDMAP_SEED), &handle)
		= reference;
	
	Deep_ECS_PrintHierarchy(&ECS);

	getchar();

	struct Deep_Vector3 vec3 = Deep_Vector3_Create(10, 10, 0);
	Deep_Vector3_Scale_InPlace(&vec3, 2);
	printf("%f %f %f\n", vec3.x, vec3.y, vec3.z);

	printf("IsBigEndian: %i.\n", Deep_Network_IsBigEndian());

    Deep_Network_InitializeSockets();

	struct Deep_Network_Server server = Deep_Network_Server_Default;
	server.OnReceiveHandle = &OnReceive;

	Deep_Network_Socket_Open(&server.socket);
	Deep_Network_Server_Start(&server, DEEP_NETWORK_DEFAULTPORT);

	printf("Server started on port: %i.\n", server.socket.port);

	int data = 10;

	struct Deep_Network_Address addr = { .a = 127, .b = 0, .c = 0, .d = 1, .port = 56732 };
	while (TRUE)
	{
		Deep_Network_Server_Tick(&server);
		Deep_Network_Address_Format(&addr);
		Deep_Network_Server_Send(&server, (char*)&data, sizeof data, &addr.sockAddr);
	}

	Deep_Network_Server_Close(&server);
    Deep_Network_ShutdownSockets();

	Deep_ECS_Free(&ECS);
}

