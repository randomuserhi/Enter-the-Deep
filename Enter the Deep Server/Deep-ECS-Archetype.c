# include "Deep-ECS-Archetype.h"

//This hash functions doesn't quite support 64 bit values => Needs changing
Deep_ECS_ArchetypeHash Deep_ECS_Archetype_Hash(struct Deep_ECS_Archetype* archetype)
{
	Deep_ECS_ArchetypeHash Seed = archetype->type.size;
	for (size_t i = 0; i < archetype->type.size; i++)
	{
		Seed ^= archetype->type $[0] + 0x9e3779b9 + (Seed << 6) + (Seed >> 2);
	}
	return Seed;
}

void Deep_ECS_Archetype_Create(struct Deep_ECS_Archetype* archetype)
{
	Deep_DynArray_Create(raw)(&archetype->type, sizeof archetype->type);
	Deep_DynArray_Create(raw)(&archetype->handles, sizeof(Deep_ECS_Handle));
	Deep_DynArray_Create(raw)(&archetype->components, sizeof(struct Deep_DynArray(raw)));
}