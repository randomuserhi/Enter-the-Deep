#ifndef h_Engine_Physics
#define h_Engine_Physics

#include "Deep_Math.h"

struct Engine_Physics_Object 
{
	struct Deep_Vector3 position;
	struct Deep_Vector3 velocity;
};

struct Engine_Physics_BodyChunk
{
	float size;
};

struct Engine_Physics_BodyChunkLink
{
	float elasticity;
};

struct Engine_Physics_Container_PhysicsObject
{
	struct Engine_Physics_Object* physicsObjects;
	size_t size;
};

struct Engine_Physics_Container_BodyChunks
{
	struct Engine_Physics_Object* physicsObjects;
	struct Engine_Physics_BodyChunk* chunks;
	size_t size;
};

struct Engine_Physics_Container_LinkedBodyChunks
{
	struct Engine_Physics_Object* physicsObjects;
	struct Engine_Physics_BodyChunk* chunks; //This will hold 2*size number of chunks as each adjacent chunk are the ones that are linked
	struct Engine_Physics_BodyChunkLink* links;
	size_t size;
};

struct Engine_Physics_World 
{
	struct Engine_Physics_Container_PhysicsObject physicsObjects;
	struct Engine_Physics_Container_BodyChunks bodyChunks;
	struct Engine_Physics_Container_LinkedBodyChunks linkedBodyChunks;
};

#endif
