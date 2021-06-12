#include "DeepEngine.h"

DeepEngine::Physics::PhysicObject::PhysicObject()
{

}

DeepEngine::Physics::PhysicObject::PhysicObject(DeepEngine::Physics::Transform Transform)
{
	this->Transform = Transform;
}
