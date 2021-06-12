#include <iostream>

#include "DeepMath.h"

int main()
{
	DeepEngine::Vector3 A(10, 10, 10);
	DeepEngine::Vector3 B = A;

	B.X = 15;

	std::cout << A.X << ',' << A.Y << ',' << A.Z << '\n';
	std::cout << B.X << ',' << B.Y << ',' << B.Z << '\n';

	return 0;
}