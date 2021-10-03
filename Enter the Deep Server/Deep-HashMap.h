#pragma once

#include "Deep.h"
#include "Deep-DynArray.h"

typedef struct
{
	Deep_DynArray_Options bucketOptions
} $Deep_UnorderedMap_Options;

typedef struct
{
	Deep_DynArray(raw) values;
	$Deep_UnorderedMap_Options options;
	size_t keyTypeSize;
	size_t valueTypeSize;
} $Deep_UnorderedMap;

void $Deep_UnorderedMap_Create($Deep_UnorderedMap* unorderedMap, size_t keyTypeSize, size_t valueTypeSize);
void* $Deep_UnorderedMap_Insert($Deep_UnorderedMap* unorderedMap);

#define Deep_UnorderedMap(tag) struct Deep_UnorderedMap$##tag

/*
* 2 Methods of implementation 
*   -> (1) Use memcpy (should get optimzed out by compiler)
*   -> (2) Have insert return a void* or type* and the user writes their
*          value to the void* or type* themselves.
* 
*   -> Option (2) is used as it makes code more efficient with less indirection
*      via memcpy.
*/

#define Deep_UnorderedMap_Decl(keyType, valueType, tag) \
Deep_UnorderedMap_Decl_Type(keyType, valueType, tag) \
Deep_UnorderedMap_Decl_Func(keyType, valueType, tag)

#define Deep_UnorderedMap_Decl_Type(keyType, valueType, tag) \
Deep_UnorderedMap(tag) \
{ \
	union \
	{ \
		$Deep_UnorderedMap $unorderedMap; \
		struct \
		{  \
			Deep_DynArray(raw) values; \
			$Deep_UnorderedMap_Options options; \
		}; \
	}; \
};

#define Deep_UnorderedMap_Decl_Func(keyType, valueType, tag) \
static Deep$Inline void Deep_UnorderedMap$##tag##_Create(Deep_UnorderedMap(tag)* unorderedMap) \
{ \
	$Deep_UnorderedMap_Create(&arr->$arr, sizeof(keyType), sizeof(valueType)); \
} \
static Deep$Inline valueType* Deep_UnorderedMap$##tag##_Insert(Deep_UnorderedMap(tag)* unorderedMap) \
{ \
	return $Deep_UnorderedMap_Insert(&unorderedMap->$unorderedMap); \
}