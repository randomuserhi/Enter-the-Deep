#include "Deep_ECS.h"

//TODO:: Write code for strings to store for identity component
//    :: Write obsidian file

void* Deep_ECS_GetComponent(struct Deep_ECS* ECS, Deep_ECS_Handle handle, Deep_ECS_Handle componentHandle)
{
	const struct Deep_ECS_Reference* reference = Deep_UnorderedMap_Find(Deep_ECS_Handle, Deep_ECS_Reference)(&ECS->hierarchy, Deep_UnorderedMap_Hash(&handle, sizeof handle, DEEP_UNORDEREDMAP_SEED), &handle);
	if (reference == NULL) return NULL;
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

		struct Deep_ECS_Id* Id = (struct Deep_ECS_Id*)Deep_ECS_GetComponent(ECS, handle, DEEP_ECS_ID);
		if (Id != NULL) printf("%s : ", Id->name);
		else printf("UNDEFINED : ");
		
		char seperator = '[';
		for (size_t i = 0; i < reference->archetype->type.size; i++)
		{
			Deep_ECS_Handle componentHandle = reference->archetype->type.values[i];
			Id = (struct Deep_ECS_Id*)Deep_ECS_GetComponent(ECS, componentHandle,  DEEP_ECS_ID);
			if (Id != NULL) printf("%c %s", seperator, Id->name);
			else printf("%c UNDEFINED", seperator);
			seperator = ',';
		}

		printf(" ]\n");
	}
}

void Deep_ECS_Create(struct Deep_ECS* ECS)
{
	Deep_UnorderedMap_Create(Deep_ECS_Handle, Deep_ECS_Reference)(&ECS->hierarchy, Deep_UnorderedMap_ByteCompare);
	//Deep_UnorderedMap_Create(Deep_ECS_ArchetypeHash, Deep_ECS_Archetype)(&ECS->archetypes, Deep_UnorderedMap_ByteCompare);
	//Deep_UnorderedMap_Create(Deep_ECS_Handle, Deep_ECS_Archetype_Ptr)(&ECS->components, Deep_UnorderedMap_ByteCompare);

	Deep_ECS_Handle handle = DEEP_ECS_NULL;
	Deep_UnorderedMap_Insert(Deep_ECS_Handle, Deep_ECS_Reference)(&ECS->hierarchy, Deep_UnorderedMap_Hash(&handle, sizeof handle, DEEP_UNORDEREDMAP_SEED), &handle);
	
	struct Deep_ECS_Archetype* componentArchetype = malloc(sizeof * componentArchetype);
	if (!componentArchetype) return;
	Deep_ECS_Archetype_Create(componentArchetype);

	*Deep_DynArray_Push(Deep_ECS_Handle)(&componentArchetype->handles) = DEEP_ECS_COMPONENT;
	*Deep_DynArray_Push(Deep_ECS_Handle)(&componentArchetype->handles) = DEEP_ECS_ID;
	
	struct Deep_ECS_Component component;
	struct Deep_ECS_Id identity;

	component.size = sizeof component;
	*(struct Deep_ECS_Component*)Deep_DynArray_Push(raw)(componentArchetype->components.values) = component;
	component.size = sizeof identity;
	*(struct Deep_ECS_Component*)Deep_DynArray_Push(raw)(componentArchetype->components.values) = component;

	identity.name = "ECS Component";
	*(struct Deep_ECS_Id*)Deep_DynArray_Push(raw)(componentArchetype->components.values + 1) = identity;
	identity.name = "ECS Id";
	*(struct Deep_ECS_Id*)Deep_DynArray_Push(raw)(componentArchetype->components.values + 1) = identity;

	handle = DEEP_ECS_COMPONENT;
	struct Deep_ECS_Reference* entityReference = Deep_UnorderedMap_Insert(Deep_ECS_Handle, Deep_ECS_Reference)(&ECS->hierarchy, Deep_UnorderedMap_Hash(&handle, sizeof handle, DEEP_UNORDEREDMAP_SEED), &handle);
	entityReference->archetype = componentArchetype;
	entityReference->index = 0;

	handle = DEEP_ECS_ID;
	entityReference = Deep_UnorderedMap_Insert(Deep_ECS_Handle, Deep_ECS_Reference)(&ECS->hierarchy, Deep_UnorderedMap_Hash(&handle, sizeof handle, DEEP_UNORDEREDMAP_SEED), &handle);
	entityReference->archetype = componentArchetype;
	entityReference->index = 1;

	ECS->root = componentArchetype; // Maybe add archetype to a main list ?
}

void Deep_ECS_Free(struct Deep_ECS* ECS)
{
	Deep_UnorderedMap_Free(Deep_ECS_Handle, Deep_ECS_Reference)(&ECS->hierarchy);
	free(ECS->root); // Careful, root may not need to be freed if another Dict contains it and is freed.
}

struct Deep_ECS_Archetype* Deep_ECS_CreateType(struct Deep_ECS* ECS, const Deep_ECS_Handle* type, size_t typeLength)
{
	struct Deep_ECS_Archetype* root = ECS->root;
	const Deep_ECS_Handle* key = type;
	for (size_t i = 0; i < typeLength; ++i, ++key)
	{
		size_t hash = Deep_UnorderedMap_Hash(key, sizeof * key, DEEP_UNORDEREDMAP_SEED);
		struct Deep_ECS_Archetype_Edge* Edge = Deep_UnorderedMap_Find(Deep_ECS_Handle, Deep_ECS_Archetype_Edge)(&root->edges, hash, key);
		if (Edge == NULL)
		{
			// Maybe add archetype to a main list so that it can be freed by Deep_ECS_Free()?
			struct Deep_ECS_Archetype* newArchetype = malloc(sizeof * newArchetype);
			if (!newArchetype) return NULL;
			Deep_ECS_Archetype_Create(newArchetype);
			Deep_DynArray_Reserve(Deep_ECS_Handle)(&newArchetype->type, root->type.size);
			memcpy(newArchetype->type.values, root->type.values, sizeof * root->type.values * root->type.size);
			//Slightly inefficient because push causes the array to realloc when it really doesnt need to...
			*Deep_DynArray_Push(Deep_ECS_Handle)(&newArchetype->type) = *key;

			Edge = Deep_UnorderedMap_Insert(Deep_ECS_Handle, Deep_ECS_Archetype_Edge)(&root->edges, hash, key);
			Edge->add = newArchetype;
			Edge->remove = NULL;
		}
		root = Edge->add;
	}
	return root;
}
