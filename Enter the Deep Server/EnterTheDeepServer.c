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

	Deep_ECS_CreateEntityComponent(&ECS, "Test", sizeof(int));

	const Deep_ECS_Handle type[] = { 10, 11, 12 };
	struct Deep_ECS_Archetype* archetype = Deep_ECS_GetType(&ECS, type, 3);
	//Deep_DynArray_Create(raw)(Deep_DynArray_Push(Deep_DynArray_raw)(&archetype->components), sizeof(int));
	//Deep_DynArray_Create(raw)(Deep_DynArray_Push(Deep_DynArray_raw)(&archetype->components), sizeof(int));
	struct Deep_ECS_Component component;
	component.size = 10;
	*(struct Deep_ECS_Component*)Deep_DynArray_Push(raw)(archetype->components.values) = component;
	struct Deep_ECS_Id identity;
	identity.name = "BRUH";
	*(struct Deep_ECS_Id*)Deep_DynArray_Push(raw)(archetype->components.values + 1) = identity;

	Deep_ECS_Handle handle = 11;
	struct Deep_ECS_Reference* entityReference = Deep_UnorderedMap_Insert(Deep_ECS_Handle, Deep_ECS_Reference)(&ECS.hierarchy, Deep_UnorderedMap_Hash(&handle, sizeof handle, DEEP_UNORDEREDMAP_SEED), &handle);
	entityReference->archetype = archetype;
	entityReference->index = 0;

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

