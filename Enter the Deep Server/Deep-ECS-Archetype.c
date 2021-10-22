# include "Deep-ECS.h"

//This hash functions doesn't quite support 64 bit values => Needs changing
Deep_ECS_ArchetypeHash Deep_ECS_Archetype_Hash(Deep_ECS_Archetype* archetype)
{
	Deep_ECS_ArchetypeHash Seed = archetype->type.size;
	for (size_t i = 0; i < archetype->type.size; i++)
	{
		Seed ^= archetype->type $[0] + 0x9e3779b9 + (Seed << 6) + (Seed >> 2);
	}
	return Seed;
}