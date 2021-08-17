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

#if defined(OLD_DEEP_DYNAMIC_IMPLEMENTATION)
#else

Deep_DynArray_Decl(int);

#endif

int main()
{
	if (!SetConsoleCtrlHandler(ExitHandler, TRUE)) return 1;

#if defined(OLD_DEEP_DYNAMIC_IMPLEMENTATION)

	int* intArr = Deep_DynamicArr_Create(int);

	clock_t begin = clock();

	for (int i = 0; i < 100000000; ++i)
	{
		Deep_DynamicArr_Push(intArr, i);
	}

	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("%f\n", time_spent);

	Deep_DynamicArr_Free(intArr);

	getchar();

#else

	Deep_DynArray(int) intArr = Deep_DynArray_Create(int);

	clock_t begin = clock();

	//100000000
	for (int i = 0; i < 100; ++i)
	{
		Deep_DynArray_Push(int, intArr, i + 1);
	}

	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("%f\n", time_spent);
	printf("%i\n", intArr->size);

	for (int i = 0; i < 100; ++i)
	{
		printf("%i\n", Deep_DynArray_int(intArr)[i]);
	}

	Deep_DynArray_Free(int, intArr);

	getchar();

#endif

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
