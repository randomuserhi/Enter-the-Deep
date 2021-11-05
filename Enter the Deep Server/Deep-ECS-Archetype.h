#pragma once
#include "Deep-ECS.h"

typedef uint64_t Deep_ECS_ArchetypeHash;

struct Deep_ECS_Component
{
	size_t size; // sizeof(Component)
};

struct Deep_ECS_Id
{
	char name[10];
};

struct Deep_ECS_Archetype
{
	Deep_ECS_Type type; // Deep_DynArray(Deep_ECS_Handle) -> represents type of archetype
	struct Deep_DynArray(raw) handles; // Deep_DynArray(Deep_ECS_Handle)
	struct Deep_DynArray(raw) components; // Deep_DynArray(Deep_DynArray(raw))

	struct Deep_UnorderedMap(raw, raw) edges; // Deep_UnorderedMap(Deep_ECS_Handle, Deep_ECS_Archetype_Edge)
};

struct Deep_ECS_Archetype_Edge
{
	struct Deep_ECS_Archetype* add;
	struct Deep_ECS_Archetype* remove;
};

struct Deep_ECS_Reference
{
	struct Deep_ECS_Archetype* archetype;
	size_t index;
};

// Archetypes
Deep_ECS_ArchetypeHash Deep_ECS_Archetype_Hash(struct Deep_ECS_Archetype* archetype);
void Deep_ECS_Archetype_Create(struct Deep_ECS_Archetype*);