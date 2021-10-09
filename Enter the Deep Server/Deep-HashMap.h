#pragma once

#include "Deep.h"

//TODO:: add error codes like dynamic array
//TODO:: refactor to not use the strainge $next attribute and work with a flag similar to std::unorderedMap
//NOTE:: Declaration functions have to be static so that they work cross files

//TODO:: make this be random everytime program boots / something (Should not be random per hash function)
#define DEEP_UNORDEREDMAP_SEED 0xee448401
#define DEEP_UNORDEREDMAP_BUCKETSIZE 13
#define DEEP_UNORDEREDMAP_LOADFACTOR 0.7
#define DEEP_UNORDEREDMAP_GROWTHRATE 2
#define DEEP_UNORDEREDMAP_EMPTY 0

typedef struct $Deep_UnorderedMap_HashSlot_
{
	struct $Deep_UnorderedMap_HashSlot_* $next;
	struct $Deep_UnorderedMap_HashSlot_* next;
	struct $Deep_UnorderedMap_HashSlot_* prev;
	size_t hash;
} Deep_UnorderedMap_HashSlot;

typedef struct
{
	Deep_UnorderedMap_HashSlot** hashes;
	Deep_UnorderedMap_HashSlot* start;
	Deep_UnorderedMap_HashSlot* end;
	size_t bucketSize;
	size_t size;
	size_t keyTypeSize;
	size_t valueTypeSize;
	size_t keyTypeAlignment;
	size_t valueTypeAlignment;
	size_t keyOffset;
	size_t valueOffset;
} $Deep_UnorderedMap;

size_t Deep_UnorderedMap_Hash(void* ptr, size_t len, size_t seed);

void $Deep_UnorderedMap_Create($Deep_UnorderedMap* unorderedMap, size_t keyTypeSize, size_t keyTypeAlignment, size_t valueTypeSize, size_t valueTypeAlignment);
void $Deep_UnorderedMap_Free($Deep_UnorderedMap* unorderedMap);
void* $Deep_UnorderedMap_Insert($Deep_UnorderedMap* unorderedMap, size_t hash, void* key);
void $Deep_UnorderedMap_Erase($Deep_UnorderedMap* unorderedMap, size_t hash, void* value);

#define Deep_UnorderedMap(valueTag, keyTag) struct Deep_UnorderedMap$##valueTag##$##keyTag

/*
* Utility macros for getting functions for type(tag).
*/

#define Deep_UnorderedMap_Create(valueTag, keyTag) Deep_UnorderedMap$##valueTag##$##keyTag##_Create
#define Deep_UnorderedMap_Insert(valueTag, keyTag) Deep_UnorderedMap$##valueTag##$##keyTag##_Insert
#define Deep_UnorderedMap_Free(valueTag, keyTag) Deep_UnorderedMap$##valueTag##$##keyTag##_Free
#define Deep_UnorderedMap_Erase(valueTag, keyTag) Deep_UnorderedMap$##valueTag##$##keyTag##_Erase
#define Deep_UnorderedMap_Value(valueTag, keyTag) Deep_UnorderedMap$##valueTag##$##keyTag##_Value

#define Deep_UnorderedMap_Decl(keyType, valueType, valueTag, keyTag) \
Deep_UnorderedMap_Decl_Type(keyType, valueType, valueTag, keyTag) \
Deep_UnorderedMap_Decl_Func(keyType, valueType, valueTag, keyTag)

#define Deep_UnorderedMap_Decl_Type(keyType, valueType, valueTag, keyTag) \
Deep_UnorderedMap(valueTag, keyTag) \
{ \
	union \
	{ \
		$Deep_UnorderedMap $unorderedMap; \
		struct \
		{  \
			Deep_UnorderedMap_HashSlot** hashes; \
			Deep_UnorderedMap_HashSlot* start; \
			Deep_UnorderedMap_HashSlot* end; \
			size_t bucketSize; \
			size_t size; \
		}; \
	}; \
};

#define Deep_UnorderedMap_Decl_Func(keyType, valueType, valueTag, keyTag) \
static Deep$Inline void Deep_UnorderedMap$##valueTag##$##keyTag##_Create(Deep_UnorderedMap(valueTag, keyTag)* unorderedMap) \
{ \
	$Deep_UnorderedMap_Create(&unorderedMap->$unorderedMap, sizeof(keyType), _Alignof(keyType), sizeof(valueType), _Alignof(valueType)); \
} \
static Deep$Inline void Deep_UnorderedMap$##valueTag##$##keyTag##_Free(Deep_UnorderedMap(valueTag, keyTag)* unorderedMap) \
{ \
	$Deep_UnorderedMap_Free(&unorderedMap->$unorderedMap); \
} \
static Deep$Inline valueType* Deep_UnorderedMap$##valueTag##$##keyTag##_Insert(Deep_UnorderedMap(valueTag, keyTag)* unorderedMap, size_t hash, keyType* key) \
{ \
	return $Deep_UnorderedMap_Insert(&unorderedMap->$unorderedMap, hash, key); \
} \
static Deep$Inline void Deep_UnorderedMap$##valueTag##$##keyTag##_Erase(Deep_UnorderedMap(valueTag, keyTag)* unorderedMap, size_t hash, keyType* key) \
{ \
	$Deep_UnorderedMap_Erase(&unorderedMap->$unorderedMap, hash, key); \
} \
static Deep$Inline valueType* Deep_UnorderedMap$##valueTag##$##keyTag##_Value(Deep_UnorderedMap(valueTag, keyTag)* unorderedMap, Deep_UnorderedMap_HashSlot* hashSlot) \
{ \
	return (valueType*)((unsigned char*)hashSlot + unorderedMap->$unorderedMap.valueOffset); \
}