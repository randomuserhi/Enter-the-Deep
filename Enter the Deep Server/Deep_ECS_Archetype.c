#include "Deep_ECS.h"

//This hash functions doesn't quite support 64 bit values => Needs changing
Deep_ECS_ArchetypeHash Deep_ECS_Archetype_Hash(const struct Deep_ECS_Archetype* archetype)
{
	Deep_ECS_ArchetypeHash Seed = archetype->type.size;
	for (size_t i = 0; i < archetype->type.size; i++)
	{
		Seed ^= archetype->type.values[0] + 0x9e3779b9 + (Seed << 6) + (Seed >> 2);
	}
	return Seed;
}

void Deep_ECS_Archetype_Create(struct Deep_ECS_Archetype* archetype)
{
	Deep_DynArray_Create(Deep_ECS_Handle)(&archetype->type);
	Deep_DynArray_Create(Deep_ECS_Handle)(&archetype->handles);
	Deep_DynArray_Create(Deep_DynArray_raw)(&archetype->components);

	Deep_ECS_Handle handle = DEEP_ECS_COMPONENT;
	*Deep_DynArray_Push(Deep_ECS_Handle)(&archetype->type) = handle;
	handle = DEEP_ECS_ID;
	*Deep_DynArray_Push(Deep_ECS_Handle)(&archetype->type) = handle;
}