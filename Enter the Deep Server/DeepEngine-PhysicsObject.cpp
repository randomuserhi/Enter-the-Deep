#include "DeepEngine.h"

DeepEngine::Physics::PhysicsObject::PhysicsObject()
{

}

DeepEngine::Physics::PhysicsObject::PhysicsObject(DeepEngine::Physics::Transform Transform)
{
	this->Transform = Transform;
}
