#pragma once

#include "Deep-Engine.h"

#define DEEP_ECS_NULL 0 //Null entity
#define DEEP_ECS_COMPONENT 0b100000000 //EntityHandle given to Components
#define DEEP_ECS_ID 0b1000000000 //Component used for providing a name to entities (for readability)

#define DEEP_ECS_ENTITY_MASK 0b1111111111111111111111111111111111111111111111111111111100000000 //Mask to provide Entity ID handle
#define DEEP_ECS_CHILDOF 0b1 //This entity is a child of <EntityHandle> provided
#define DEEP_ECS_INSTANCEOF 0b10 //This entity is an instance of <EntityHandle> provided

typedef uint64_t Deep_ECS_Handle;
typedef struct Deep_DynArray(raw) Deep_ECS_Type;

struct Deep_ECS
{
	struct Deep_UnorderedMap(raw, raw) hierarchy; // Deep_UnorderedMap(Deep_ECS_Handle, Deep_ECS_Reference) 
	struct Deep_UnorderedMap(raw, raw) archetypes; // Deep_UnorderedMap(Deep_ECS_ArchetypeHash, Deep_ECS_Archetype)
	struct Deep_UnorderedMap(raw, raw) components; // Deep_UnorderedMap(Deep_ECS_Handle, Deep_ECS_Archetype*) => gets a list of archetypes that contain a given component
};

void Deep_ECS_Create(struct Deep_ECS* ECS);
void Deep_ECS_PrintHierarchy(struct Deep_ECS* ECS);

#include "Deep-ECS-Archetype.h"
