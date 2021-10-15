#pragma once

#include "Deep.h"
#include "DeepContainers.h"

typedef uint64_t Deep_ECS_Handle;
typedef uint64_t Deep_ECS_ArchetypeHash;
typedef Deep_DynArray(raw) Deep_ECS_Type; // Deep_DynArray(Deep_ECS_Handle)

typedef struct
{
	Deep_ECS_Archetype* Add;
	Deep_ECS_Archetype* Remove;
} Deep_ECS_Archetype_Edge;

typedef struct
{
	 Deep_ECS_Type Type;
	 Deep_DynArray(raw) Handles; // Deep_DynArray(Deep_ECS_Handle)
	 Deep_DynArray(raw) Components; // Deep_DynArray(Deep_DynArray(raw))
	 
	 Deep_UnorderedMap(raw, raw) Edges; // Deep_UnorderedMap(Deep_ECS_Handle, Deep_ECS_Archetype_Edge)
} Deep_ECS_Archetype;

typedef struct
{
	Deep_ECS_Archetype* archetype;
	size_t index;
} Deep_ECS_Reference;

typedef struct
{
	Deep_UnorderedMap(raw, raw) hierarchy; // Deep_UnorderedMap(Deep_ECS_Handle, Deep_ECS_Reference) 
	Deep_UnorderedMap(raw, raw) archetypes; // Deep_UnorderedMap(Deep_ECS_ArchetypeHash, Deep_ECS_Archetype)
} Deep_ECS;
