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

int main()
{
	if (!SetConsoleCtrlHandler(ExitHandler, TRUE)) return 1;

	int _DEEP_DYNAMIC_ARR_RESULT;
	Deep_DynamicArr_Create(int, intArr);

	clock_t begin = clock();

	for (int i = 0; i < 100000000; ++i)
	{
		//int _DEEP_DYNAMIC_VOID_ARR_RESULT; 
		Deep_DynamicArr_Push(intArr, 10);
		//Deep_DynamicArr_EmptyPush(intArr);
	}

	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("%f\n", time_spent);
	getchar();

	for (int i = 100000000 - 3; i < 100000000; ++i)
	{
		//int _DEEP_DYNAMIC_VOID_ARR_RESULT; 
		printf("%i\n", intArr[i]);
	}

	printf("%i\n", Deep_DynamicArr_Size(intArr));
	
	begin = clock();

	for (int i = 0; i < 100000000; ++i)
	{
		Deep_DynamicArr_Pop(intArr);
	}

	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("%f\n", time_spent);
	getchar();

	printf("%i\n", Deep_DynamicArr_Size(intArr));

	Deep_DynamicArr_Free(intArr);

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
