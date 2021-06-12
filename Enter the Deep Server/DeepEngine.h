#pragma once

#include <vector>
#include "DeepMath.h"

namespace DeepEngine
{
	namespace Physics
	{
		struct RigidBody
		{
			Vector3 Velocity;
		};

		struct Transform
		{
			Transform();
			Transform(Vector3 Position);

			Vector3 Position;
		};

		class PhysicObject
		{
		private:

		public:
			PhysicObject();
			PhysicObject(Transform Transform);

			Transform Transform;
			RigidBody RigidBody;
		};

		//Determines what is simulated at a physics level, eg a bouncy ball
		class PhysicsWorld
		{
		private:
			std::vector<PhysicObject*> ActiveObjects; //Objects that are simulated
			std::vector<PhysicObject> Objects; //All objects in the world

		public:
			void Step(float DeltaTime);
		};
	}

	namespace World
	{
		class Entity
		{
		private:
			std::vector<Physics::PhysicObject*> Objects; //PhysicObjects owned by entity, such as body parts etc...

		public:
		};

		//Determines what is simulated at a entity level, eg entity behaviour, player movement, creature AI
		class World
		{
		private:
			std::vector<Entity> ActiveEntities;

		public:
			void Update();
		};
	}
}