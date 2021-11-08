#pragma once

#include "Deep.h"

#define DEEP_DYNAMIC_ARR_SIZE 10 // Default size for dynamic arrays
#define DEEP_DYNAMIC_ARR_GROWTHRATE 1.5f //Growthrate for dynamic arrays

#define DEEP_DYNAMIC_ARR_FREE_ON_ERROR 1
#define DEEP_DYNAMIC_ARR_KEEP_ON_ERROR 0

struct Deep_DynArray_Options
{
	char freeOnError; // If set, will free the contents of the array when an error is caught, otherwise the contents remain
} Deep_DynArray_Options;

struct $Deep_DynArray
{
	size_t size; // Number of elements in array (to optimize out division)
	size_t capacity; // Capacity of array (not number of elements in array)
	unsigned char* data; // Pointer to data
	unsigned char* end; // Pointer to last element
	struct Deep_DynArray_Options options; // Array options

	size_t typeSize; // sizeof(type)
};

void $Deep_DynArray_Create(struct $Deep_DynArray* arr, size_t typeSize);
void $Deep_DynArray_Free(struct $Deep_DynArray* arr);
void* $Deep_DynArray_Push(struct $Deep_DynArray* arr);
void $Deep_DynArray_Pop(struct $Deep_DynArray* arr);
void $Deep_DynArray_RemoveAt(struct $Deep_DynArray* arr, size_t index);
void $Deep_DynArray_Shrink(struct $Deep_DynArray* arr);
void $Deep_DynArray_Reserve(struct $Deep_DynArray* arr, size_t size);

/*
* Defines a Deep_DynArray of type(tag).
*/
#define Deep_DynArray(tag) Deep_DynArray$##tag

/*
* Utility macros for getting functions for type(tag).
*/

#define Deep_DynArray_ReinterpretCast(tag) Deep_DynArray$##tag##_ReinterpretCast
#define Deep_DynArray_Create(tag) Deep_DynArray$##tag##_Create
#define Deep_DynArray_Free(tag) Deep_DynArray$##tag##_Free
#define Deep_DynArray_Push(tag) Deep_DynArray$##tag##_Push
#define Deep_DynArray_Pop(tag) Deep_DynArray$##tag##_Pop
#define Deep_DynArray_RemoveAt(tag) Deep_DynArray$##tag##_RemoveAt
#define Deep_DynArray_Shrink(tag) Deep_DynArray$##tag##_Shrink 
#define Deep_DynArray_Reserve(tag) Deep_DynArray$##tag##_Reserve

#define Deep_DynArray_Decl(type, tag) \
$Deep_DynArray_Decl_Type(type, tag) \
static Deep$Inline void Deep_DynArray$##tag##_Create(struct Deep_DynArray(tag)* arr) \
{ \
	$Deep_DynArray_Create(&arr->$arr, sizeof(type)); \
} \
$Deep_DynArray_Decl_Func(type, tag)

#define $Deep_DynArray_Decl_Type(type, tag) \
struct Deep_DynArray(tag) \
{ \
	union \
	{ \
		struct $Deep_DynArray $arr; \
		struct \
		{  \
			size_t size; \
			size_t capacity; \
			type* values; \
			type* end; \
			struct Deep_DynArray_Options options; \
		}; \
	}; \
};

#define $Deep_DynArray_Decl_Func(type, tag) \
static Deep$Inline struct Deep_DynArray(tag) Deep_DynArray$##tag##_ReinterpretCast(void* arr) \
{ \
	struct Deep_DynArray(tag) dst; \
	memcpy(&dst, arr, sizeof dst); \
	return dst; \
} \
static Deep$Inline void Deep_DynArray$##tag##_Free(struct Deep_DynArray(tag)* arr) \
{ \
	$Deep_DynArray_Free(&arr->$arr); \
} \
static Deep$Inline void Deep_DynArray$##tag##_Pop(struct Deep_DynArray(tag)* arr) \
{ \
	$Deep_DynArray_Pop(&arr->$arr); \
} \
static Deep$Inline void Deep_DynArray$##tag##_RemoveAt(struct Deep_DynArray(tag)* arr, size_t index) \
{ \
	$Deep_DynArray_RemoveAt(&arr->$arr, index); \
} \
static Deep$Inline void Deep_DynArray$##tag##_Shrink(struct Deep_DynArray(tag)* arr) \
{ \
	$Deep_DynArray_Shrink(&arr->$arr); \
} \
static Deep$Inline void Deep_DynArray$##tag##_Reserve(struct Deep_DynArray(tag)* arr, size_t size) \
{ \
	$Deep_DynArray_Reserve(&arr->$arr, size); \
} \
static Deep$Inline type* Deep_DynArray$##tag##_Push(struct Deep_DynArray(tag)* arr) \
{ \
	return $Deep_DynArray_Push(&arr->$arr); \
}

/*
* The following is used to define the "raw" version of Deep_DynArray 
* which uses a custom Create function to assign sizeof(type).
*/
$Deep_DynArray_Decl_Type(unsigned char, raw)
static Deep$Inline void Deep_DynArray$raw_Create(struct Deep_DynArray(raw)* arr, size_t typeSize)
{
	$Deep_DynArray_Create(&arr->$arr, typeSize);
}
$Deep_DynArray_Decl_Func(unsigned char, raw)