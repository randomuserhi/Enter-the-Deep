#include <iostream>

#include "DeepEngine.h"
#include "DeepNetwork.h"

#include <windows.h>
#include <bitset> //Remove later, this is just here for debugging
#include <string> //Remove later, this is just here for debugging
#include <chrono> //Remove later, this is for profiling

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
	/*auto Prev = std::chrono::system_clock::now();
	auto After = std::chrono::system_clock::now();
	std::chrono::duration<std::chrono::milliseconds> Elapsed = After - Prev;
	std::cout << Elapsed.count() << '\n';*/

	if (!SetConsoleCtrlHandler(ExitHandler, TRUE)) return 1;

	//Initialize DeepEngine
	DeepEngine::DeepECS DeepHandle{}; //https://stackoverflow.com/questions/31496810/parameterless-constructor
	DeepEngine::ECSHandle Test = DeepHandle.CreateComponent(5);
	DeepHandle.GetComponent<DeepEngine::DeepIdentifier>(Test, DEEP_ECS_ID)->Name = "TestComponent";
	DeepHandle.DebugEntityIndex();

	DeepEngine::ComponentList DynArr(sizeof(DeepEngine::DeepComponent));
	DeepEngine::DeepComponent Comp = {10};
	DynArr.Add<DeepEngine::DeepComponent>(Comp);
	std::cout << DynArr.Size<DeepEngine::DeepComponent>() << '\n';
	Comp = { 30 };
	DynArr.Add<DeepEngine::DeepComponent>(Comp);
	std::cout << DynArr.Size<DeepEngine::DeepComponent>() << '\n';
	Comp = { 40 };
	DynArr.Add<DeepEngine::DeepComponent>(Comp);
	std::cout << DynArr.Size<DeepEngine::DeepComponent>() << '\n';
	Comp = { 50 };
	DynArr.Add<DeepEngine::DeepComponent>(Comp);
	std::cout << DynArr.Size<DeepEngine::DeepComponent>() << '\n';
	Comp = { 50 };
	DynArr.Add<DeepEngine::DeepComponent>(Comp);
	std::cout << DynArr.Size<DeepEngine::DeepComponent>() << '\n';
	Comp = { 50 };
	DynArr.Add<DeepEngine::DeepComponent>(Comp);
	std::cout << DynArr.Size<DeepEngine::DeepComponent>() << '\n';
	Comp = { 50 };
	DynArr.Add<DeepEngine::DeepComponent>(Comp);
	std::cout << DynArr.Size<DeepEngine::DeepComponent>() << '\n';
	Comp = { 50 };
	DynArr.Add<DeepEngine::DeepComponent>(Comp);
	std::cout << DynArr.Size<DeepEngine::DeepComponent>() << '\n';

	DynArr.Get<DeepEngine::DeepComponent>(0).Size = 100;

	std::cout << DynArr.Get<DeepEngine::DeepComponent>(0).Size << '\n';
	std::cout << DynArr.Get<DeepEngine::DeepComponent>(1).Size << '\n';
	std::cout << DynArr.Get<DeepEngine::DeepComponent>(2).Size << '\n';
	std::cout << DynArr.Get<DeepEngine::DeepComponent>(3).Size << '\n';
	std::cout << DynArr.Get<DeepEngine::DeepComponent>(4).Size << '\n';
	std::cout << DynArr.Get<DeepEngine::DeepComponent>(5).Size << '\n';
	std::cout << DynArr.Get<DeepEngine::DeepComponent>(6).Size << '\n';
	std::cout << DynArr.Get<DeepEngine::DeepComponent>(7).Size << '\n';

	std::cout << "DeepEngine Initialized.\n";

	//Initialize Server

	std::cout << "IsBigEndian: " << DeepNetwork::IsBigEndian() << ".\n";

	DeepNetwork::InitializeSockets();

	DeepNetwork::Server Server(&OnReceive);

	Server.Start(57687);

	std::cout << "Server started on port: " << Server.GetPort() << ".\n";

	//int Data = 10;

	while (true)
	{
		Server.Tick();
		//Server.Send((char*)&Data, sizeof(Data), &DeepNetwork::Address(127, 0, 0, 1, 58655));
	}

	DeepNetwork::ShutdownSockets();

	return 0;
}