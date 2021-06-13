#include <iostream>

#include "DeepEngine.h"
#include "DeepNetwork.h"

int main()
{
	DeepNetwork::InitializeSockets();

	DeepEngine::Vector3 A(10, 10, 10);
	DeepEngine::Vector3 B = A;

	B.X = 15;

	std::cout << A.X << ',' << A.Y << ',' << A.Z << '\n';
	std::cout << B.X << ',' << B.Y << ',' << B.Z << '\n';

	DeepNetwork::ShutdownSockets();

	return 0;
}