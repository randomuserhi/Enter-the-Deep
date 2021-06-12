#pragma once

#include <vector>
#include "DeepMath.h"

namespace DeepEngine
{
	class PhysicObject
	{
	private:

	public:

	};

	class PhysicsWorld 
	{
	private:
		std::vector<PhysicObject> ActiveObjects;

	public:
		void Step(float DeltaTime)
		{

		}
	};
}