#include "Deep_ECS.h"

//TODO:: Write code for strings to store for identity component
//    :: Write obsidian file

void* Deep_ECS_GetComponent(struct Deep_ECS* ECS, Deep_ECS_Handle handle, Deep_ECS_Handle componentHandle)
{
	const struct Deep_ECS_Reference* reference = Deep_UnorderedMap_Insert(Deep_ECS_Handle, Deep_ECS_Reference)(&ECS->hierarchy, Deep_UnorderedMap_Hash(&handle, sizeof handle, DEEP_UNORDEREDMAP_SEED), &handle);
	for (size_t i = 0; i < reference->archetype->type.size; i++)
	{
		Deep_ECS_Handle h = reference->archetype->type.values[i];
		if (h == componentHandle)
		{
			return Deep_DynArray_Get(raw)(&((struct Deep_DynArray(raw)*)reference->archetype->components.values)[i], reference->index);
		}
	}
	return NULL;
}

void Deep_ECS_PrintHierarchy(struct Deep_ECS* ECS)
{
	for (const struct Deep_UnorderedMap_HashSlot* slot = ECS->hierarchy.start; slot != NULL; slot = slot->next)
	{
		Deep_ECS_Handle handle = *Deep_UnorderedMap_Key(Deep_ECS_Handle, Deep_ECS_Reference)(&ECS->hierarchy, slot);
		if (handle == DEEP_ECS_NULL) continue;

		struct Deep_ECS_Reference* reference = Deep_UnorderedMap_Value(Deep_ECS_Handle, Deep_ECS_Reference)(&ECS->hierarchy, slot);

		struct Deep_ECS_Id Id = *(struct Deep_ECS_Id*)Deep_ECS_GetComponent(ECS, handle, DEEP_ECS_ID);
		printf("%s : ", Id.name);
		
		char seperator = '[';
		for (size_t i = 0; i < reference->archetype->type.size; i++)
		{
			Deep_ECS_Handle componentHandle = reference->archetype->type.values[i];
			Id = *(struct Deep_ECS_Id*)Deep_ECS_GetComponent(ECS, componentHandle,  DEEP_ECS_ID);
			printf("%c %s", seperator, Id.name);
			seperator = ',';
		}

		printf(" ]\n");
	}
}

void Deep_ECS_Create(struct Deep_ECS* ECS)
{
	Deep_UnorderedMap_Create(Deep_ECS_Handle, Deep_ECS_Reference)(&ECS->hierarchy, Deep_UnorderedMap_ByteCompare);
	Deep_UnorderedMap_Create(Deep_ECS_ArchetypeHash, Deep_ECS_Archetype)(&ECS->archetypes, Deep_UnorderedMap_ByteCompare);
	Deep_UnorderedMap_Create(Deep_ECS_Handle, Deep_ECS_Archetype_Ptr)(&ECS->components, Deep_UnorderedMap_ByteCompare);

	Deep_ECS_Handle handle = DEEP_ECS_NULL;
	Deep_UnorderedMap_Insert(Deep_ECS_Handle, Deep_ECS_Reference)(&ECS->hierarchy, Deep_UnorderedMap_Hash(&handle, sizeof handle, DEEP_UNORDEREDMAP_SEED), &handle);
	
	struct Deep_ECS_Archetype* componentArchetype = malloc(sizeof * componentArchetype);
	if (!componentArchetype) return;
	Deep_ECS_Archetype_Create(componentArchetype);

	*Deep_DynArray_Push(Deep_ECS_Handle)(&componentArchetype->handles) = DEEP_ECS_COMPONENT;
	*Deep_DynArray_Push(Deep_ECS_Handle)(&componentArchetype->handles) = DEEP_ECS_ID;
	
	struct Deep_DynArray(raw) componentList;
	Deep_DynArray_Create(raw)(&componentList, sizeof(struct Deep_ECS_Component));
	struct Deep_ECS_Component component;
	component.size = sizeof(struct Deep_ECS_Component);
	*(struct Deep_ECS_Component*)Deep_DynArray_Push(raw)(&componentList) = component;
	component.size = sizeof(struct Deep_ECS_Id);
	*(struct Deep_ECS_Component*)Deep_DynArray_Push(raw)(&componentList) = component;

	struct Deep_DynArray(raw) identityList;
	Deep_DynArray_Create(raw)(&identityList, sizeof(struct Deep_ECS_Id));
	struct Deep_ECS_Id identity;
	identity.name = "ECS_COMPONENT";
	*(struct Deep_ECS_Id*)Deep_DynArray_Push(raw)(&identityList) = identity;
	identity.name = "ECS_ID";
	*(struct Deep_ECS_Id*)Deep_DynArray_Push(raw)(&identityList) = identity;

	*Deep_DynArray_Push(Deep_DynArray_raw)(&componentArchetype->components) = componentList;
	*Deep_DynArray_Push(Deep_DynArray_raw)(&componentArchetype->components) = identityList;
	
	handle = DEEP_ECS_COMPONENT;
	struct Deep_ECS_Reference* entityReference = Deep_UnorderedMap_Insert(Deep_ECS_Handle, Deep_ECS_Reference)(&ECS->hierarchy, Deep_UnorderedMap_Hash(&handle, sizeof handle, DEEP_UNORDEREDMAP_SEED), &handle);
	entityReference->archetype = componentArchetype;
	entityReference->index = 0;

	handle = DEEP_ECS_ID;
	entityReference = Deep_UnorderedMap_Insert(Deep_ECS_Handle, Deep_ECS_Reference)(&ECS->hierarchy, Deep_UnorderedMap_Hash(&handle, sizeof handle, DEEP_UNORDEREDMAP_SEED), &handle);
	entityReference->archetype = componentArchetype;
	entityReference->index = 1;

	//TODO:: push to archetype hash
}
