#include "Deep-ECS.h"

void Deep_ECS_Create(Deep_ECS* ECS)
{
	Deep_UnorderedMap_Create(raw, raw)(&ECS->hierarchy, sizeof(Deep_ECS_Handle), Deep$AlignOf(Deep_ECS_Handle), sizeof(Deep_ECS_Reference), Deep$AlignOf(Deep_ECS_Reference));
	Deep_UnorderedMap_Create(raw, raw)(&ECS->archetypes, sizeof(Deep_ECS_ArchetypeHash), Deep$AlignOf(Deep_ECS_ArchetypeHash), sizeof(Deep_ECS_Archetype), Deep$AlignOf(Deep_ECS_Archetype));
}