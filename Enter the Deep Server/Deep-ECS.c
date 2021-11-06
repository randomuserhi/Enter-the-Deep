#include "Deep-ECS.h"

//TODO:: Implement better GetComponent method, add wrapper using macros to convert reference to component struct
//    :: Write code for strings to store for identity component
//    :: Edit header files to move things about
//    :: Better organise code
struct ComponentReference
{
	size_t index;
	struct Deep_DynArray(raw)* components;
};

struct ComponentReference Deep_ECS_GetComponent(struct Deep_ECS* ECS, Deep_ECS_Handle handle, Deep_ECS_Handle componentHandle)
{
	struct Deep_ECS_Reference* reference = Deep_UnorderedMap_Insert(raw, raw)(&ECS->hierarchy, Deep_UnorderedMap_Hash(&handle, sizeof handle, DEEP_UNORDEREDMAP_SEED), &handle, Deep_UnorderedMap_ByteCompare);
	struct ComponentReference componentReference;
	componentReference.index = 0;
	componentReference.components = NULL;
	for (size_t i = 0; i < reference->archetype->type.size; i++)
	{
		Deep_ECS_Handle h = ((Deep_ECS_Handle*)reference->archetype->type.values)[i];
		//printf("%zu, %zu\n", h, componentHandle);
		if (h == componentHandle)
		{
			componentReference.components = &((struct Deep_DynArray(raw)*)reference->archetype->components.values)[i];
			componentReference.index = reference->index;
			break;
		}
	}
	return componentReference;
}

void Deep_ECS_PrintHierarchy(struct Deep_ECS* ECS)
{
	for (struct Deep_UnorderedMap_HashSlot* slot = ECS->hierarchy.start; slot != NULL; slot = slot->next)
	{
		Deep_ECS_Handle handle = *(Deep_ECS_Handle*)Deep_UnorderedMap_Key(raw, raw)(&ECS->hierarchy, slot);
		if (handle == DEEP_ECS_NULL) continue;

		struct Deep_ECS_Reference* reference = Deep_UnorderedMap_Value(raw, raw)(&ECS->hierarchy, slot);

		struct ComponentReference componentReference = Deep_ECS_GetComponent(ECS, handle, DEEP_ECS_ID);
		printf("%s : ", ((struct Deep_ECS_Id*)componentReference.components->values)[componentReference.index].name);
		
		char seperator = '[';
		for (size_t i = 0; i < reference->archetype->type.size; i++)
		{
			Deep_ECS_Handle componentHandle = ((Deep_ECS_Handle*)reference->archetype->type.values)[i];
			componentReference = Deep_ECS_GetComponent(ECS, componentHandle,  DEEP_ECS_ID);
			printf("%c %s", seperator, ((struct Deep_ECS_Id*)componentReference.components->values)[componentReference.index].name);
			seperator = ',';
		}

		printf(" ]\n");
	}
}

void Deep_ECS_Create(struct Deep_ECS* ECS)
{
	Deep_UnorderedMap_Create(raw, raw)(&ECS->hierarchy, sizeof(Deep_ECS_Handle), Deep$AlignOf(Deep_ECS_Handle), sizeof(struct Deep_ECS_Reference), Deep$AlignOf(struct Deep_ECS_Reference));
	Deep_UnorderedMap_Create(raw, raw)(&ECS->archetypes, sizeof(Deep_ECS_ArchetypeHash), Deep$AlignOf(Deep_ECS_ArchetypeHash), sizeof(struct Deep_ECS_Archetype), Deep$AlignOf(struct Deep_ECS_Archetype));
	Deep_UnorderedMap_Create(raw, raw)(&ECS->components, sizeof(Deep_ECS_Handle), Deep$AlignOf(Deep_ECS_Handle), sizeof(struct Deep_ECS_Archetype*), Deep$AlignOf(struct Deep_ECS_Archetype*));

	Deep_ECS_Handle handle = DEEP_ECS_NULL;
	Deep_UnorderedMap_Insert(raw, raw)(&ECS->hierarchy, Deep_UnorderedMap_Hash(&handle, sizeof handle, DEEP_UNORDEREDMAP_SEED), &handle, Deep_UnorderedMap_ByteCompare);
	
	struct Deep_ECS_Archetype* componentArchetype = malloc(sizeof * componentArchetype);
	if (!componentArchetype) return;
	Deep_ECS_Archetype_Create(componentArchetype);

	*(Deep_ECS_Handle*)Deep_DynArray_Push(raw)(&componentArchetype->handles) = DEEP_ECS_COMPONENT;
	*(Deep_ECS_Handle*)Deep_DynArray_Push(raw)(&componentArchetype->handles) = DEEP_ECS_ID;
	
	struct Deep_DynArray(raw) componentList;
	Deep_DynArray_Create(raw)(&componentList, sizeof(struct Deep_ECS_Component));
	struct Deep_ECS_Component component;
	component.size = 0;
	*(struct Deep_ECS_Component*)Deep_DynArray_Push(raw)(&componentList) = component;
	*(struct Deep_ECS_Component*)Deep_DynArray_Push(raw)(&componentList) = component;

	struct Deep_DynArray(raw) identityList;
	Deep_DynArray_Create(raw)(&identityList, sizeof(struct Deep_ECS_Id));
	struct Deep_ECS_Id identity;
	strcpy_s(identity.name, 10, "comp");
	*(struct Deep_ECS_Id*)Deep_DynArray_Push(raw)(&identityList) = identity;
	strcpy_s(identity.name, 10, "id");
	*(struct Deep_ECS_Id*)Deep_DynArray_Push(raw)(&identityList) = identity;

	*(struct Deep_DynArray(raw)*)Deep_DynArray_Push(raw)(&componentArchetype->components) = componentList;
	*(struct Deep_DynArray(raw)*)Deep_DynArray_Push(raw)(&componentArchetype->components) = identityList;
	
	handle = DEEP_ECS_COMPONENT;
	struct Deep_ECS_Reference* entityReference = Deep_UnorderedMap_Insert(raw, raw)(&ECS->hierarchy, Deep_UnorderedMap_Hash(&handle, sizeof handle, DEEP_UNORDEREDMAP_SEED), &handle, Deep_UnorderedMap_ByteCompare);
	entityReference->archetype = componentArchetype;
	entityReference->index = 0;

	handle = DEEP_ECS_ID;
	entityReference = Deep_UnorderedMap_Insert(raw, raw)(&ECS->hierarchy, Deep_UnorderedMap_Hash(&handle, sizeof handle, DEEP_UNORDEREDMAP_SEED), &handle, Deep_UnorderedMap_ByteCompare);
	entityReference->archetype = componentArchetype;
	entityReference->index = 1;

	//TODO:: push to archetype hash
}