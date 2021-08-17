#pragma once

#include "Deep.h"

#define DEEP_DYNAMIC_ARR_SIZE 10 // Default size for dynamic arrays
#define DEEP_DYNAMIC_ARR_GROWTHRATE 2 //Growthrate for dynamic arrays

#if defined(OLD_DEEP_DYNAMIC_IMPLEMENTATION)

typedef struct
{
	unsigned char* begin; // Pointer to data
	unsigned char* end; // Pointer to last element
	size_t size; // Number of elements in array (to optimize out division)
	size_t typeSize; // Size of type
	size_t capacity; // Capacity of array (not number of elements in array)
} Deep_DynamicArr_Head;

typedef unsigned char Deep_DynamicArr;

// Careful with this header code
// use of casting to (Deep_DynamicArr_Head*) stops compiler warnings, but the warning has a point 
// (refer to Type punning, Strict Aliasing and Alignment issues with casting)
// Technically should be fine as I never reinterpret the bytes of the struct differently (Type Punning)
// (in otherwords converting between void* and T* will always return the same pointer, same with char* and T*)
// and malloc guarantees alignment.
#define Deep_DynamicArr_Header(arr) ((Deep_DynamicArr_Head*)((Deep_DynamicArr*)(arr) - sizeof(Deep_DynamicArr_Head)))
#define _Deep_DynamicArr_Realloc(dest, src, newCapacity) dest = src; dest->begin = (Deep_DynamicArr*)dest + sizeof(Deep_DynamicArr_Head); dest->end = dest->begin + dest->typeSize * dest->size; dest->capacity = newCapacity

#define Deep_DynamicArr_Create_Raw(typeSize) _Deep_DynamicArr_Create(typeSize)
#define Deep_DynamicArr_Create(typeName) (void*)_Deep_DynamicArr_Create(sizeof(typeName))
Deep_DynamicArr* _Deep_DynamicArr_Create(size_t typeSize);

#define Deep_DynamicArr_Size(arr) Deep_DynamicArr_Header(arr)->size
#define Deep_DynamicArr_Free(arr) free(Deep_DynamicArr_Header(arr))

#define Deep_DynamicArr_RawGet(type, arr, index) ((type*)arr)[index]

#define Deep_DynamicArr_Push(arr, item) \
do {\
	if (arr) \
	{ \
		Deep_DynamicArr_Head* header = Deep_DynamicArr_Header(arr); \
		/* Check if typeSize is 0, if so then the array is NULL and should not be operated on */ \
		if (header->typeSize && header->typeSize == sizeof (item)) \
		{ \
			if (header->size == header->capacity) \
			{ \
				size_t newCapacity = (size_t)(header->capacity * DEEP_DYNAMIC_ARR_GROWTHRATE); \
				if (newCapacity == header->capacity) ++newCapacity; \
				void* tmp = realloc(header, sizeof(Deep_DynamicArr_Head) + header->typeSize * newCapacity); \
				if (tmp) \
				{ \
					_Deep_DynamicArr_Realloc(header, tmp, newCapacity); \
					*((void**)&(arr)) = header->begin; \
					arr[header->size] = (item); \
					header->end += header->typeSize; \
					++header->size; \
				} \
				else { free(header); arr = NULL; } \
			} \
			else \
			{ \
				arr[header->size] = (item); \
				header->end += header->typeSize; \
				++header->size; \
			} \
		} \
	} \
} while(0)

#define Deep_DynamicArr_EmptyPush(arr)  \
do {\
	if (arr) \
	{ \
		Deep_DynamicArr_Head* header = Deep_DynamicArr_Header(arr); \
		/* Check if typeSize is 0, if so then the array is NULL and should not be operated on */ \
		if (header->typeSize) \
		{ \
			if (header->size == header->capacity) \
			{ \
				size_t newCapacity = (size_t)(header->capacity * DEEP_DYNAMIC_ARR_GROWTHRATE); \
				if (newCapacity == header->capacity) ++newCapacity; \
				void* tmp = realloc(header, sizeof(Deep_DynamicArr_Head) + header->typeSize * newCapacity); \
				if (tmp) \
				{ \
					_Deep_DynamicArr_Realloc(header, tmp, newCapacity); \
					*((void**)&(arr)) = header->begin; \
					header->end += header->typeSize; \
					++header->size; \
				} \
				else { free(header); arr = NULL; } \
			} \
			else \
			{ \
				header->end += header->typeSize; \
				++header->size; \
			} \
		} \
	} \
} while(0)

#define Deep_DynamicArr_Pop(arr) \
do { \
	if (arr) \
	{ \
		Deep_DynamicArr_Head* header = Deep_DynamicArr_Header(arr); \
		if (header->begin != header->end) \
		{ \
			header->end -= header->typeSize; \
			--header->size; \
		} \
	} \
} while(0)

#define Deep_DynamicArr_RemoveAt(arr, index) \
do { \
	if (arr) \
	{ \
		Deep_DynamicArr_Head* header = Deep_DynamicArr_Header(arr); \
		if (index < header->size) \
		{ \
			for (size_t start = index; start < header->size - 1; ++start) \
			{ \
				arr[start] = arr[start + 1]; \
			} \
			--header->size; \
		} \
	} \
} while(0)

#define Deep_DynamicArr_EmptyPushBlock(arr, num) _Deep_DynamicArr_EmptyPush(Deep_DynamicArr_Header(arr), &arr, num)
#define Deep_DynamicArr_Reserve(arr, num) _Deep_DynamicArr_Reserve(Deep_DynamicArr_Header(arr), &arr, num)
#define Deep_DynamicArr_Shrink(arr) _Deep_DynamicArr_Shrink(Deep_DynamicArr_Header(arr), &arr)

void _Deep_DynamicArr_Reserve(Deep_DynamicArr_Head* dynArray, void** arr, size_t num);
void _Deep_DynamicArr_EmptyPush(Deep_DynamicArr_Head* dynArray, void** arr, size_t num);
void _Deep_DynamicArr_Shrink(Deep_DynamicArr_Head* dynArray, void** arr);

#else

typedef struct
{
	size_t size; // Number of elements in array (to optimize out division)
	size_t capacity; // Capacity of array (not number of elements in array)
	unsigned char* data; // Pointer to data
	size_t typeSize; // sizeof(type)
} $Deep_DynArray;

/*
* Defines a Deep_DynArray of type(tag).
*/
#define Deep_DynArray(tag) struct Deep_DynArray$##tag##$

void $Deep_DynArray_Create($Deep_DynArray* arr, size_t typeSize);
void $Deep_DynArray_Free($Deep_DynArray* arr);
void $Deep_DynArray_EmptyPush($Deep_DynArray* arr);
void $Deep_DynArray_Pop($Deep_DynArray* arr);
void $Deep_DynArray_RemoveAt($Deep_DynArray* arr, size_t index);
void $Deep_DynArray_Shrink($Deep_DynArray* arr);

/*
* Casts a Deep_DynArray of type(tag) to another Deep_DynArray of type(tag).
* 
* This cast is UB due to pointer casts between structs. Please use ((type*)arr $) instead.
*/
#define Deep_DynArray_ReinterpretCast(tag, arr) (*(Deep_DynArray(tag)*)&arr)

/*
* Access "operator" for easily accessing Deep_DynArray values.
*/
#define $ .values

/*
* Utility macros for getting functions for type(tag).
*/

#define Deep_DynArray_Create(tag) Deep_DynArray$##tag##$_Create()
#define Deep_DynArray_Free(tag) Deep_DynArray$##tag##$_Free
#define Deep_DynArray_EmptyPush(tag) Deep_DynArray$##tag##$_EmptyPush
#define Deep_DynArray_Push(tag) Deep_DynArray$##tag##$_Push
#define Deep_DynArray_Pop(tag) Deep_DynArray$##tag##$_Pop
#define Deep_DynArray_RemoveAt(tag) Deep_DynArray$##tag##$_RemoveAt
#define Deep_DynArray_Shrink(tag) Deep_DynArray$##tag##$_Shrink 

#define Deep_DynArray_Decl(type, tag) \
$Deep_DynArray_Decl_Type(type, tag) \
static Deep$Inline Deep_DynArray(tag) Deep_DynArray$##tag##$_Create() \
{ \
	Deep_DynArray(tag) tmp; \
	$Deep_DynArray_Create(&tmp.$arr, sizeof(type)); \
	return tmp; \
} \
$Deep_DynArray_Decl_Func(type, tag)

#define $Deep_DynArray_Decl_Type(type, tag) \
Deep_DynArray(tag) \
{ \
	union \
	{ \
		$Deep_DynArray $arr; \
		struct \
		{  \
			size_t size; \
			size_t capacity; \
			type* values; \
		}; \
	}; \
};

#define $Deep_DynArray_Decl_Func(type, tag) \
static Deep$Inline void Deep_DynArray$##tag##$_Free(Deep_DynArray(tag)* arr) \
{ \
	$Deep_DynArray_Free(&arr->$arr); \
} \
static Deep$Inline void Deep_DynArray$##tag##$_EmptyPush(Deep_DynArray(tag)* arr) \
{ \
	$Deep_DynArray_EmptyPush(&arr->$arr); \
} \
static Deep$Inline void Deep_DynArray$##tag##$_Push(Deep_DynArray(tag)* arr, type value) \
{ \
	if (arr->$arr.typeSize == sizeof(type)) \
	{ \
		$Deep_DynArray_EmptyPush(&arr->$arr); \
		if (arr->values) arr->values[arr->$arr.size - 1] = value; \
	} \
} \
static Deep$Inline void Deep_DynArray$##tag##$_Pop(Deep_DynArray(tag)* arr) \
{ \
	$Deep_DynArray_Pop(&arr->$arr); \
} \
static Deep$Inline void Deep_DynArray$##tag##$_RemoveAt(Deep_DynArray(tag)* arr, size_t index) \
{ \
	$Deep_DynArray_RemoveAt(&arr->$arr, index); \
} \
static Deep$Inline void Deep_DynArray$##tag##$_Shrink(Deep_DynArray(tag)* arr) \
{ \
	$Deep_DynArray_Shrink(&arr->$arr); \
}

/*
* The following is used to define the "raw" version of Deep_DynArray 
* which uses a custom Create function to assign sizeof(type).
*/
$Deep_DynArray_Decl_Type(unsigned char, raw)
static Deep$Inline Deep_DynArray(raw) Deep_DynArray$raw$_Create(size_t typeSize)
{
	Deep_DynArray(raw) tmp;
	$Deep_DynArray_Create(&tmp.$arr, typeSize);
	return tmp;
}
$Deep_DynArray_Decl_Func(unsigned char, raw)

#endif