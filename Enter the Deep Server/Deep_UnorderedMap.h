#ifndef h_Deep_UnorderedMap
#define h_Deep_UnorderedMap

#include "Deep.h"

//TODO:: refactor to not use the strainge _next attribute and work with a flag similar to std::unorderedMap
//NOTE:: Declaration functions have to be static so that they work cross files

//TODO:: make this be random everytime program boots / something (Should not be random per hash function)
#define DEEP_UNORDEREDMAP_SEED 0xee448401
#define DEEP_UNORDEREDMAP_BUCKETSIZE 13
#define DEEP_UNORDEREDMAP_LOADFACTOR 0.7
#define DEEP_UNORDEREDMAP_GROWTHRATE 2
#define DEEP_UNORDEREDMAP_EMPTY 0

struct Deep_UnorderedMap_HashSlot
{
	struct Deep_UnorderedMap_HashSlot* _next;
	struct Deep_UnorderedMap_HashSlot* next;
	struct Deep_UnorderedMap_HashSlot* prev;
	size_t hash;
};

struct _Deep_UnorderedMap
{
	struct Deep_UnorderedMap_HashSlot** hashes;
	struct Deep_UnorderedMap_HashSlot* start;
	struct Deep_UnorderedMap_HashSlot* end;
	size_t bucketSize;
	size_t size;
	int (*keyCompareFunc)(const void*, const void*, size_t);
	size_t keyTypeSize;
	size_t valueTypeSize;
	size_t keyTypeAlignment;
	size_t valueTypeAlignment;
	size_t keyOffset;
	size_t valueOffset;
};

size_t Deep_UnorderedMap_Hash(const void* ptr, size_t len, size_t seed);
int Deep_UnorderedMap_ByteCompare(const void* hashKey, const void* hey, size_t keyTypeSize);

void _Deep_UnorderedMap_Create(struct _Deep_UnorderedMap* unorderedMap, int (*keyCompareFunc)(const void*, const void*, size_t), size_t keyTypeSize, size_t keyTypeAlignment, size_t valueTypeSize, size_t valueTypeAlignment);
void _Deep_UnorderedMap_Free(struct _Deep_UnorderedMap* unorderedMap);
void* _Deep_UnorderedMap_Insert(struct _Deep_UnorderedMap* unorderedMap, size_t hash, const void* key);
void _Deep_UnorderedMap_Erase(struct _Deep_UnorderedMap* unorderedMap, size_t hash, const void* key);

#define Deep_UnorderedMap(keyTag, valueTag) Deep_UnorderedMap_##keyTag##_To_##valueTag

/*
* Utility macros for getting functions for type(tag).
*/

#define Deep_UnorderedMap_Create(keyTag, valueTag) Deep_UnorderedMap_##keyTag##_To_##valueTag##_Create
#define Deep_UnorderedMap_Insert(keyTag, valueTag) Deep_UnorderedMap_##keyTag##_To_##valueTag##_Insert
#define Deep_UnorderedMap_Free(keyTag, valueTag) Deep_UnorderedMap_##keyTag##_To_##valueTag##_Free
#define Deep_UnorderedMap_Erase(keyTag, valueTag) Deep_UnorderedMap_##keyTag##_To_##valueTag##_Erase
#define Deep_UnorderedMap_Value(keyTag, valueTag) Deep_UnorderedMap_##keyTag##_To_##valueTag##_Value
#define Deep_UnorderedMap_Key(keyTag, valueTag) Deep_UnorderedMap_##keyTag##_To_##valueTag##_Key

#define Deep_UnorderedMap_Decl(keyType, valueType, keyTag, valueTag) \
Deep_UnorderedMap_Decl_Type(keyTag, valueTag) \
Deep_UnorderedMap_Decl_Func(keyType, valueType, keyTag, valueTag) \
Deep_UnorderedMap_Decl_Func_KeyValue(keyType, valueType, keyTag, valueTag) \
Deep_UnorderedMap_Decl_Func_Create(keyType, valueType, keyTag, valueTag)

#define Deep_UnorderedMap_Decl_Type(keyTag, valueTag) \
struct Deep_UnorderedMap(keyTag, valueTag) \
{ \
	union \
	{ \
		struct _Deep_UnorderedMap _unorderedMap; \
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

#define Deep_UnorderedMap_Decl_Func(keyType, valueType, keyTag, valueTag) \
static Deep_Inline void Deep_UnorderedMap_##keyTag##_To_##valueTag##_Free(struct Deep_UnorderedMap(keyTag, valueTag)* unorderedMap) \
{ \
	_Deep_UnorderedMap_Free(&unorderedMap->_unorderedMap); \
} \
static Deep_Inline valueType* Deep_UnorderedMap_##keyTag##_To_##valueTag##_Insert(struct Deep_UnorderedMap(keyTag, valueTag)* unorderedMap, size_t hash, const keyType* key) \
{ \
	return _Deep_UnorderedMap_Insert(&unorderedMap->_unorderedMap, hash, key); \
} \
static Deep_Inline void Deep_UnorderedMap_##keyTag##_To_##valueTag##_Erase(struct Deep_UnorderedMap(keyTag, valueTag)* unorderedMap, size_t hash, const keyType* key) \
{ \
	_Deep_UnorderedMap_Erase(&unorderedMap->_unorderedMap, hash, key); \
}

#define Deep_UnorderedMap_Decl_Func_KeyValue(keyType, valueType, keyTag, valueTag) \
static Deep_Inline valueType* Deep_UnorderedMap_##keyTag##_To_##valueTag##_Value(const struct Deep_UnorderedMap(keyTag, valueTag)* unorderedMap, const struct Deep_UnorderedMap_HashSlot* hashSlot) \
{ \
	return (valueType*)((unsigned char*)hashSlot + unorderedMap->_unorderedMap.valueOffset); \
} \
static Deep_Inline keyType* Deep_UnorderedMap_##keyTag##_To_##valueTag##_Key(const struct Deep_UnorderedMap(keyTag, valueTag)* unorderedMap, const struct Deep_UnorderedMap_HashSlot* hashSlot) \
{ \
	return (keyType*)((unsigned char*)hashSlot + unorderedMap->_unorderedMap.keyOffset); \
}

#define Deep_UnorderedMap_Decl_Func_Create(keyType, valueType, keyTag, valueTag) \
static Deep_Inline void Deep_UnorderedMap_##keyTag##_To_##valueTag##_Create(struct Deep_UnorderedMap(keyTag, valueTag)* unorderedMap, int (*keyCompareFunc)(const void*, const void*, size_t)) \
{ \
	_Deep_UnorderedMap_Create(&unorderedMap->_unorderedMap, keyCompareFunc, sizeof(keyType), Deep_AlignOf(keyType), sizeof(valueType), Deep_AlignOf(valueType)); \
}

/*
* The following is used to define the "raw" version of Deep_DynArray
* which uses a custom Create function to assign sizeof(type).
*/

Deep_UnorderedMap_Decl_Type(raw, raw)
Deep_UnorderedMap_Decl_Func(void, void, raw, raw)
static Deep_Inline void Deep_UnorderedMap_raw_To_raw_Create(struct Deep_UnorderedMap(raw, raw)* unorderedMap, int (*keyCompareFunc)(const void*, const void*, size_t), size_t keyTypeSize, size_t keyTypeAlignment, size_t valueTypeSize, size_t valueTypeAlignment)
{
	_Deep_UnorderedMap_Create(&unorderedMap->_unorderedMap, keyCompareFunc, keyTypeSize, keyTypeAlignment, valueTypeSize, valueTypeAlignment);
}
static Deep_Inline void* Deep_UnorderedMap_raw_To_raw_Value(const struct Deep_UnorderedMap(raw, raw)* unorderedMap, const struct Deep_UnorderedMap_HashSlot* hashSlot) \
{
	return (unsigned char*)hashSlot + unorderedMap->_unorderedMap.valueOffset;
}
static Deep_Inline void* Deep_UnorderedMap_raw_To_raw_Key(const struct Deep_UnorderedMap(raw, raw)* unorderedMap, const struct Deep_UnorderedMap_HashSlot* hashSlot) \
{
	return (unsigned char*)hashSlot + unorderedMap->_unorderedMap.keyOffset;
}

#endif