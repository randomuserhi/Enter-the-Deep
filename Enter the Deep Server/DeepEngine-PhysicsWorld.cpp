#include "DeepEngine.h"

void DeepEngine::Physics::PhysicsWorld::Step(float DeltaTime)
{
	for (PhysicObject* Object : ActiveObjects)
	{
		Object->Transform.Position += Object->RigidBody.Velocity * DeltaTime;
	}
}

