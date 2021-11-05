#pragma once

#include "Deep.h"

//TODO:: refactor to not use the strainge $next attribute and work with a flag similar to std::unorderedMap
//NOTE:: Declaration functions have to be static so that they work cross files

//TODO:: make this be random everytime program boots / something (Should not be random per hash function)
#define DEEP_UNORDEREDMAP_SEED 0xee448401
#define DEEP_UNORDEREDMAP_BUCKETSIZE 13
#define DEEP_UNORDEREDMAP_LOADFACTOR 0.7
#define DEEP_UNORDEREDMAP_GROWTHRATE 2
#define DEEP_UNORDEREDMAP_EMPTY 0

struct Deep_UnorderedMap_HashSlot
{
	struct Deep_UnorderedMap_HashSlot* $next;
	struct Deep_UnorderedMap_HashSlot* next;
	struct Deep_UnorderedMap_HashSlot* prev;
	size_t hash;
};

struct $Deep_UnorderedMap
{
	struct Deep_UnorderedMap_HashSlot** hashes;
	struct Deep_UnorderedMap_HashSlot* start;
	struct Deep_UnorderedMap_HashSlot* end;
	size_t bucketSize;
	size_t size;
	size_t keyTypeSize;
	size_t valueTypeSize;
	size_t keyTypeAlignment;
	size_t valueTypeAlignment;
	size_t keyOffset;
	size_t valueOffset;
};

size_t Deep_UnorderedMap_Hash(void* ptr, size_t len, size_t seed);
int Deep_UnorderedMap_ByteCompare(void* hashKey, void* hey, size_t keyTypeSize);

void $Deep_UnorderedMap_Create(struct $Deep_UnorderedMap* unorderedMap, size_t keyTypeSize, size_t keyTypeAlignment, size_t valueTypeSize, size_t valueTypeAlignment);
void $Deep_UnorderedMap_Free(struct $Deep_UnorderedMap* unorderedMap);
void* $Deep_UnorderedMap_Insert(struct $Deep_UnorderedMap* unorderedMap, size_t hash, void* key, int (*keyCompareFunc)(void*, void*, size_t));
void $Deep_UnorderedMap_Erase(struct $Deep_UnorderedMap* unorderedMap, size_t hash, void* key, int (*keyCompareFunc)(void*, void*, size_t));

#define Deep_UnorderedMap(valueTag, keyTag) Deep_UnorderedMap$##valueTag##$##keyTag

/*
* Utility macros for getting functions for type(tag).
*/

#define Deep_UnorderedMap_Create(valueTag, keyTag) Deep_UnorderedMap$##valueTag##$##keyTag##_Create
#define Deep_UnorderedMap_Insert(valueTag, keyTag) Deep_UnorderedMap$##valueTag##$##keyTag##_Insert
#define Deep_UnorderedMap_Free(valueTag, keyTag) Deep_UnorderedMap$##valueTag##$##keyTag##_Free
#define Deep_UnorderedMap_Erase(valueTag, keyTag) Deep_UnorderedMap$##valueTag##$##keyTag##_Erase
#define Deep_UnorderedMap_Value(valueTag, keyTag) Deep_UnorderedMap$##valueTag##$##keyTag##_Value
#define Deep_UnorderedMap_Key(valueTag, keyTag) Deep_UnorderedMap$##valueTag##$##keyTag##_Key

#define Deep_UnorderedMap_Decl(keyType, valueType, valueTag, keyTag) \
Deep_UnorderedMap_Decl_Type(valueTag, keyTag) \
Deep_UnorderedMap_Decl_Func(keyType, valueType, valueTag, keyTag) \
Deep_UnorderedMap_Decl_Func_KeyValue(keyType, valueType, valueTag, keyTag) \
Deep_UnorderedMap_Decl_Func_Create(keyType, valueType, valueTag, keyTag)

#define Deep_UnorderedMap_Decl_Type(valueTag, keyTag) \
struct Deep_UnorderedMap(valueTag, keyTag) \
{ \
	union \
	{ \
		struct $Deep_UnorderedMap $unorderedMap; \
		struct \
		{  \
			struct Deep_UnorderedMap_HashSlot** hashes; \
			struct Deep_UnorderedMap_HashSlot* start; \
			struct Deep_UnorderedMap_HashSlot* end; \
			size_t bucketSize; \
			size_t size; \
		}; \
	}; \
};

#define Deep_UnorderedMap_Decl_Func(keyType, valueType, valueTag, keyTag) \
static Deep$Inline void Deep_UnorderedMap$##valueTag##$##keyTag##_Free(struct Deep_UnorderedMap(valueTag, keyTag)* unorderedMap) \
{ \
	$Deep_UnorderedMap_Free(&unorderedMap->$unorderedMap); \
} \
static Deep$Inline valueType* Deep_UnorderedMap$##valueTag##$##keyTag##_Insert(struct Deep_UnorderedMap(valueTag, keyTag)* unorderedMap, size_t hash, keyType* key, int (*keyCompareFunc)(void*, void*, size_t)) \
{ \
	return $Deep_UnorderedMap_Insert(&unorderedMap->$unorderedMap, hash, key, keyCompareFunc); \
} \
static Deep$Inline void Deep_UnorderedMap$##valueTag##$##keyTag##_Erase(struct Deep_UnorderedMap(valueTag, keyTag)* unorderedMap, size_t hash, keyType* key, int (*keyCompareFunc)(void*, void*, size_t)) \
{ \
	$Deep_UnorderedMap_Erase(&unorderedMap->$unorderedMap, hash, key, keyCompareFunc); \
}

#define Deep_UnorderedMap_Decl_Func_KeyValue(keyType, valueType, valueTag, keyTag) \
static Deep$Inline valueType* Deep_UnorderedMap$##valueTag##$##keyTag##_Value(struct Deep_UnorderedMap(valueTag, keyTag)* unorderedMap, struct Deep_UnorderedMap_HashSlot* hashSlot) \
{ \
	return (valueType*)((unsigned char*)hashSlot + unorderedMap->$unorderedMap.valueOffset); \
} \
static Deep$Inline keyType* Deep_UnorderedMap$##valueTag##$##keyTag##_Key(struct Deep_UnorderedMap(valueTag, keyTag)* unorderedMap, struct Deep_UnorderedMap_HashSlot* hashSlot) \
{ \
	return (keyType*)((unsigned char*)hashSlot + unorderedMap->$unorderedMap.keyOffset); \
}

#define Deep_UnorderedMap_Decl_Func_Create(keyType, valueType, valueTag, keyTag) \
static Deep$Inline void Deep_UnorderedMap$##valueTag##$##keyTag##_Create(struct Deep_UnorderedMap(valueTag, keyTag)* unorderedMap) \
{ \
	$Deep_UnorderedMap_Create(&unorderedMap->$unorderedMap, sizeof(keyType), Deep$AlignOf(keyType), sizeof(valueType), Deep$AlignOf(valueType)); \
}

/*
* The following is used to define the "raw" version of Deep_DynArray
* which uses a custom Create function to assign sizeof(type).
*/

Deep_UnorderedMap_Decl_Type(raw, raw)
Deep_UnorderedMap_Decl_Func(void, void, raw, raw)
static Deep$Inline void Deep_UnorderedMap$raw$raw_Create(struct Deep_UnorderedMap(raw, raw)* unorderedMap, size_t keyTypeSize, size_t keyTypeAlignment, size_t valueTypeSize, size_t valueTypeAlignment)
{
	$Deep_UnorderedMap_Create(&unorderedMap->$unorderedMap, keyTypeSize, keyTypeAlignment, valueTypeSize, valueTypeAlignment);
}
static Deep$Inline void* Deep_UnorderedMap$raw$raw_Value(struct Deep_UnorderedMap(raw, raw)* unorderedMap, struct Deep_UnorderedMap_HashSlot* hashSlot) \
{
	return (unsigned char*)hashSlot + unorderedMap->$unorderedMap.valueOffset;
}
static Deep$Inline void* Deep_UnorderedMap$raw$raw_Key(struct Deep_UnorderedMap(raw, raw)* unorderedMap, struct Deep_UnorderedMap_HashSlot* hashSlot) \
{
	return (unsigned char*)hashSlot + unorderedMap->$unorderedMap.keyOffset;
}
