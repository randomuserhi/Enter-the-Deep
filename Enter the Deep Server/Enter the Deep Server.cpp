#include <iostream>

#include "DeepMath.h"

int main()
{
	DeepEngine::Vector3 V1(10, 20, 10);
	DeepEngine::Vector3 V2(3, 2, 1);
	DeepEngine::Vector3 V3;

	//V3 = V2 + V1;

	//V1.X = 15;

	V3 += V2;

	V2.X += 1;

	std::cout << V1.X << ',' << V1.Y << ',' << V1.Z << '\n';
	std::cout << V2.X << ',' << V2.Y << ',' << V2.Z << '\n';
	std::cout << V3.X << ',' << V3.Y << ',' << V3.Z << '\n';

	return 0;
}