#include "Deep-ECS.h"

void Deep_ECS_Create(struct Deep_ECS* ECS)
{
	Deep_UnorderedMap_Create(raw, raw)(&ECS->hierarchy, sizeof(Deep_ECS_Handle), Deep$AlignOf(Deep_ECS_Handle), sizeof(struct Deep_ECS_Reference), Deep$AlignOf(struct Deep_ECS_Reference));
	Deep_UnorderedMap_Create(raw, raw)(&ECS->archetypes, sizeof(Deep_ECS_ArchetypeHash), Deep$AlignOf(Deep_ECS_ArchetypeHash), sizeof(struct Deep_ECS_Archetype), Deep$AlignOf(struct Deep_ECS_Archetype));
	Deep_UnorderedMap_Create(raw, raw)(&ECS->components, sizeof(Deep_ECS_Handle), Deep$AlignOf(Deep_ECS_Handle), sizeof(struct Deep_ECS_Archetype*), Deep$AlignOf(struct Deep_ECS_Archetype*));

	Deep_ECS_Handle handle = DEEP_ECS_NULL;
	struct Deep_ECS_Reference* entityReference = Deep_UnorderedMap_Insert(raw, raw)(&ECS->hierarchy, Deep_UnorderedMap_Hash(&handle, sizeof handle, DEEP_UNORDEREDMAP_SEED), &handle, Deep_UnorderedMap_ByteCompare);
	entityReference->archetype = malloc(sizeof entityReference->archetype);
	if (entityReference->archetype)
		Deep_ECS_Archetype_Create(entityReference->archetype);
}