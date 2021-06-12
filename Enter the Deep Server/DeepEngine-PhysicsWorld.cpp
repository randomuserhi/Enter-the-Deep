#include "DeepEngine.h"

void DeepEngine::Physics::PhysicsWorld::Step(float DeltaTime)
{
	for (PhysicsObject* Object : ActiveObjects)
	{
		Object->Transform.Position += Object->RigidBody.Velocity * DeltaTime;
	}
}

