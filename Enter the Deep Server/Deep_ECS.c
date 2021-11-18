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

		printf("[%i] ", reference->archetype->size);

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

Deep_Inline void Deep_ECS_AppendHierarchy(struct Deep_ECS* ECS, Deep_ECS_Handle handle, struct Deep_ECS_Archetype* archetype, size_t index)
{
	struct Deep_ECS_Reference* entityReference = Deep_UnorderedMap_Insert(Deep_ECS_Handle, Deep_ECS_Reference)(&ECS->hierarchy, Deep_UnorderedMap_Hash(&handle, sizeof handle, DEEP_UNORDEREDMAP_SEED), &handle);
	entityReference->archetype = archetype;
	entityReference->index = index;
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
	ECS->root = componentArchetype; // Maybe also add to a main list of archetypes for looking up

	//TODO:: since this type is quite prevelant, maybe make it a public array?
	const Deep_ECS_Handle type[] = { DEEP_ECS_COMPONENT, DEEP_ECS_ID };
	componentArchetype = Deep_ECS_GetArchetype(ECS, type, 2);

	struct Deep_ECS_Component component;
	struct Deep_ECS_Id identity;

	Deep_DynArray_Create(raw)(componentArchetype->components.values, sizeof component);
	Deep_DynArray_Create(raw)(componentArchetype->components.values + 1, sizeof identity);

	//TODO:: these handles may be irrelevant
	*Deep_DynArray_Push(Deep_ECS_Handle)(&componentArchetype->handles) = DEEP_ECS_COMPONENT;
	*Deep_DynArray_Push(Deep_ECS_Handle)(&componentArchetype->handles) = DEEP_ECS_ID;

	component.size = sizeof component;
	*(struct Deep_ECS_Component*)Deep_DynArray_Push(raw)(componentArchetype->components.values) = component;
	component.size = sizeof identity;
	*(struct Deep_ECS_Component*)Deep_DynArray_Push(raw)(componentArchetype->components.values) = component;

	identity.name = "ECS Component";
	*(struct Deep_ECS_Id*)Deep_DynArray_Push(raw)(componentArchetype->components.values + 1) = identity;
	identity.name = "ECS Id";
	*(struct Deep_ECS_Id*)Deep_DynArray_Push(raw)(componentArchetype->components.values + 1) = identity;

	Deep_ECS_AppendHierarchy(ECS, DEEP_ECS_COMPONENT, componentArchetype, 0);
	Deep_ECS_AppendHierarchy(ECS, DEEP_ECS_ID, componentArchetype, 1);

	componentArchetype->size = 2;
}

void Deep_ECS_Free(struct Deep_ECS* ECS)
{
	Deep_UnorderedMap_Free(Deep_ECS_Handle, Deep_ECS_Reference)(&ECS->hierarchy);
	free(ECS->root); // Careful, root may not need to be freed if another Dict contains it and is freed.
}

void Deep_ECS_CreateComponent(struct Deep_ECS* ECS, const char* name, size_t componentSize)
{
	//TODO:: since this type is quite prevelant, maybe make it a public array?
	const Deep_ECS_Handle type[] = { DEEP_ECS_COMPONENT, DEEP_ECS_ID };
	struct Deep_ECS_Archetype* componentArchetype = Deep_ECS_GetArchetype(ECS, type, 2);
	struct Deep_ECS_Reference reference = Deep_ECS_Archetype_Push(ECS, componentArchetype);
	
	((struct Deep_ECS_Component*)componentArchetype->components.values->values)[reference.index].size = componentSize;
	((struct Deep_ECS_Id*)(componentArchetype->components.values + 1)->values)[reference.index].name = name;

	// Create method to get a new handle
	Deep_ECS_AppendHierarchy(ECS, 10, componentArchetype, reference.index);
}

struct Deep_ECS_Archetype* Deep_ECS_GetArchetype(struct Deep_ECS* ECS, const Deep_ECS_Handle* type, size_t typeLength)
{
	//TODO:: sort type variable so its in ascending order

	struct Deep_ECS_Archetype* root = ECS->root;
	const Deep_ECS_Handle* key = type;
	for (size_t i = 0; i < typeLength; ++i, ++key)
	{
		size_t hash = Deep_UnorderedMap_Hash(key, sizeof * key, DEEP_UNORDEREDMAP_SEED);
		struct Deep_ECS_Archetype_Edge* edge = Deep_UnorderedMap_Find(Deep_ECS_Handle, Deep_ECS_Archetype_Edge)(&root->edges, hash, key);
		if (edge == NULL)
		{
			// Maybe add archetype to a main list so that it can be freed by Deep_ECS_Free()?
			struct Deep_ECS_Archetype* archetype = malloc(sizeof * archetype);
			if (!archetype) return NULL;
			Deep_ECS_Archetype_Create(archetype);

			/*Deep_DynArray_Reserve(Deep_ECS_Handle)(&newArchetype->type, root->type.size);
			memcpy(newArchetype->type.values, root->type.values, sizeof * root->type.values * root->type.size);
			
			// Slightly inefficient because push causes the array to realloc when it really doesnt need to...
			// Maybe make another reserve function that reserves capacity or create a memcpy function like C# addrange
			
			*Deep_DynArray_Push(Deep_ECS_Handle)(&newArchetype->type) = *key;*/
			
			Deep_DynArray_Reserve(Deep_ECS_Handle)(&archetype->type, root->type.size + 1);
			memcpy(archetype->type.values, root->type.values, sizeof * root->type.values * root->type.size);
			archetype->type.values[root->type.size] = *key;

			//TODO:: reorganise this code, reuse of hash variable and the implementation of key is different
			//	     to main loop with key++ vs type + j
			for (size_t j = 0; j < i + 1; j++)
			{
				size_t hash = Deep_UnorderedMap_Hash(type + j, sizeof * type, DEEP_UNORDEREDMAP_SEED);
				struct Deep_ECS_Reference* typeReference = Deep_UnorderedMap_Find(Deep_ECS_Handle, Deep_ECS_Reference)(&ECS->hierarchy, hash, type + j);
				struct Deep_DynArray(raw)* componentArr = Deep_DynArray_Push(Deep_DynArray_raw)(&archetype->components);
				if (typeReference != NULL && *typeReference->archetype->type.values == DEEP_ECS_COMPONENT)
				{
					Deep_DynArray_Create(raw)(componentArr, ((struct Deep_ECS_Component*)typeReference->archetype->components.values->values)->size);
				}
			}

			edge = Deep_UnorderedMap_Insert(Deep_ECS_Handle, Deep_ECS_Archetype_Edge)(&root->edges, hash, key);
			edge->add = archetype;
			edge->remove = NULL;
		}
		root = edge->add;
	}
	return root;
}
