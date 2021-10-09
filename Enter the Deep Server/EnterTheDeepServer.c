#include "Deep.h"
#include "DeepContainers.h"
#include "DeepMath.h"
#include "DeepEngine.h"
#include "DeepNetwork.h"

#include <windows.h>
#include <time.h>

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

Deep_DynArray_Decl(int, int)
Deep_DynArray_Decl(Deep_DynArray(int), Deep_DynArray$int)

Deep_UnorderedMap_Decl(int, int, int, int)

int main()
{
	if (!SetConsoleCtrlHandler(ExitHandler, TRUE)) return 1;

	//Deep_CheckMaxAllocationSize();

	Deep_UnorderedMap(int, int) hashMap;
	Deep_UnorderedMap_Create(int, int)(&hashMap);

	for (int i = 0; i < 100; i++)
	{
		size_t Hash = Deep_UnorderedMap_Hash(&i, sizeof(int), DEEP_UNORDEREDMAP_SEED);
		*(Deep_UnorderedMap_Insert(int, int)(&hashMap, Hash, &i)) = i + 10;
		printf("%i\n", *(Deep_UnorderedMap_Insert(int, int)(&hashMap, Hash, &i)));
	}

	printf("size %i\n", hashMap.size);
	int i = 12;
	size_t Hash = Deep_UnorderedMap_Hash(&i, sizeof(int), DEEP_UNORDEREDMAP_SEED);
	Deep_UnorderedMap_Erase(int, int)(&hashMap, Hash, &i);
	//*(Deep_UnorderedMap_Insert(int, int)(&HashMap, Hash, &i)) = i;
	//printf("%i\n", *(Deep_UnorderedMap_Insert(int, int)(&HashMap, Hash, &i)));
	printf("size %i\n", hashMap.size);

	//for ($Deep_UnorderedMap_HashSlot* hashSlot = HashMap.end; hashSlot != NULL; hashSlot = hashSlot->prev)
	for (Deep_UnorderedMap_HashSlot* hashSlot = hashMap.start; hashSlot != NULL; hashSlot = hashSlot->next)
	{
		printf("%i\n", *Deep_UnorderedMap_Value(int, int)(&hashMap, hashSlot));
	}

	Deep_UnorderedMap_Free(int, int)(&hashMap);

	/*Deep_DynArray(int) testarr;
	Deep_DynArray$int_Create(&testarr);

	clock_t begin = clock();

	for (int i = 0; i < 100000000; ++i)
	{
		Deep_DynArray_Push(int)(&testarr, i);
	}

	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("%f\n", time_spent);

	for (int i = 0; i < 100; ++i)
	{
		printf("%i\n", testarr $[i]);
	}

	Deep_DynArray_Free(int)(&testarr);*/

	getchar();

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
