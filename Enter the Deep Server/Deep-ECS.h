#pragma once

#include "Deep-Engine.h"

#define DEEP_ECS_NULL 0 //Null entity
#define DEEP_ECS_COMPONENT 0b100000000 //EntityHandle given to Components
#define DEEP_ECS_ID 0b1000000000 //Component used for providing a name to entities (for readability)

#define DEEP_ECS_ENTITY_MASK 0b1111111111111111111111111111111111111111111111111111111100000000 //Mask to provide Entity ID handle
#define DEEP_ECS_CHILDOF 0b1 //This entity is a child of <EntityHandle> provided
#define DEEP_ECS_INSTANCEOF 0b10 //This entity is an instance of <EntityHandle> provided

typedef uint64_t Deep_ECS_Handle;
typedef uint64_t Deep_ECS_ArchetypeHash;
typedef Deep_DynArray(raw) Deep_ECS_Type; // Deep_DynArray(Deep_ECS_Handle)

typedef struct
{
	Deep_ECS_Type type;
	Deep_DynArray(raw) handles; // Deep_DynArray(Deep_ECS_Handle)
	Deep_DynArray(raw) components; // Deep_DynArray(Deep_DynArray(raw))

	Deep_UnorderedMap(raw, raw) edges; // Deep_UnorderedMap(Deep_ECS_Handle, Deep_ECS_Archetype_Edge)
} Deep_ECS_Archetype;

typedef struct
{
	Deep_ECS_Archetype* add;
	Deep_ECS_Archetype* remove;
} Deep_ECS_Archetype_Edge;

typedef struct
{
	Deep_ECS_Archetype* archetype;
	size_t index;
} Deep_ECS_Reference;

typedef struct
{
	Deep_UnorderedMap(raw, raw) hierarchy; // Deep_UnorderedMap(Deep_ECS_Handle, Deep_ECS_Reference) 
	Deep_UnorderedMap(raw, raw) archetypes; // Deep_UnorderedMap(Deep_ECS_ArchetypeHash, Deep_ECS_Archetype)
	Deep_UnorderedMap(raw, raw) components; // Deep_UnorderedMap(Deep_ECS_Handle, Deep_ECS_Archetype*) => gets a list of archetypes that contain a given component
} Deep_ECS;

void Deep_ECS_Create(Deep_ECS* ECS);

// Archetypes
Deep_ECS_ArchetypeHash Deep_ECS_Archetype_Hash(Deep_ECS_Archetype* archetype);
