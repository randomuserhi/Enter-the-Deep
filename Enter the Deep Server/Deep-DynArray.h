#pragma once

#include "Deep.h"

#define DEEP_DYNAMIC_ARR_SIZE 10 // Default size for dynamic arrays
#define DEEP_DYNAMIC_ARR_GROWTHRATE 2 //Growthrate for dynamic arrays

#define DEEP_DYNAMIC_ARR_FREE_ON_ERROR 1
#define DEEP_DYNAMIC_ARR_KEEP_ON_ERROR 0

#define DEEP_DYNAMIC_ARR_NO_ERROR 0
#define DEEP_DYNAMIC_ARR_ERROR_DATA_NULL 1
#define DEEP_DYNAMIC_ARR_ERROR_REALLOC 2

typedef struct
{
	char freeOnError; // If set, will free the contents of the array when an error is caught, otherwise the contents remain
} Deep_DynArray_Options;

typedef struct
{
	size_t size; // Number of elements in array (to optimize out division)
	size_t capacity; // Capacity of array (not number of elements in array)
	unsigned char* data; // Pointer to data
	char errorCode; // After an array operation occurs, if an error has happened it is shown here
	Deep_DynArray_Options options; // Array options

	size_t typeSize; // sizeof(type)
} $Deep_DynArray;

void $Deep_DynArray_Create($Deep_DynArray* arr, size_t typeSize);
void $Deep_DynArray_Free($Deep_DynArray* arr);
void $Deep_DynArray_EmptyPush($Deep_DynArray* arr);
void $Deep_DynArray_Push($Deep_DynArray* arr, void* value);
void $Deep_DynArray_Pop($Deep_DynArray* arr);
void $Deep_DynArray_RemoveAt($Deep_DynArray* arr, size_t index);
void $Deep_DynArray_Shrink($Deep_DynArray* arr);

/*
* Defines a Deep_DynArray of type(tag).
*/
#define Deep_DynArray(tag) struct Deep_DynArray$##tag

/*
* Access "operator" for easily accessing Deep_DynArray values.
*/
#define $ .values

/*
* Utility macros for getting functions for type(tag).
*/

#define Deep_DynArray_ReinterpretCast(tag) Deep_DynArray$##tag##_ReinterpretCast
#define Deep_DynArray_Create(tag) Deep_DynArray$##tag##_Create
#define Deep_DynArray_Free(tag) Deep_DynArray$##tag##_Free
#define Deep_DynArray_EmptyPush(tag) Deep_DynArray$##tag##_EmptyPush
#define Deep_DynArray_Push(tag) Deep_DynArray$##tag##_Push
#define Deep_DynArray_Pop(tag) Deep_DynArray$##tag##_Pop
#define Deep_DynArray_RemoveAt(tag) Deep_DynArray$##tag##_RemoveAt
#define Deep_DynArray_Shrink(tag) Deep_DynArray$##tag##_Shrink 

#define Deep_DynArray_Decl(type, tag) \
$Deep_DynArray_Decl_Type(type, tag) \
static Deep$Inline void Deep_DynArray$##tag##_Create(Deep_DynArray(tag)* arr) \
{ \
	$Deep_DynArray_Create(&arr->$arr, sizeof(type)); \
} \
$Deep_DynArray_Decl_Func(type, tag) \
$Deep_DynArray_Decl_Func_Push(type, tag)

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
			char errorCode; \
			Deep_DynArray_Options options; \
		}; \
	}; \
};

#define $Deep_DynArray_Decl_Func(type, tag) \
static Deep$Inline Deep_DynArray(tag) Deep_DynArray$##tag##_ReinterpretCast(void* arr) \
{ \
	Deep_DynArray(tag) dst; \
	memcpy(&dst, arr, sizeof dst); \
	return dst; \
} \
static Deep$Inline void Deep_DynArray$##tag##_Free(Deep_DynArray(tag)* arr) \
{ \
	$Deep_DynArray_Free(&arr->$arr); \
} \
static Deep$Inline void Deep_DynArray$##tag##_EmptyPush(Deep_DynArray(tag)* arr) \
{ \
	$Deep_DynArray_EmptyPush(&arr->$arr); \
} \
static Deep$Inline void Deep_DynArray$##tag##_Pop(Deep_DynArray(tag)* arr) \
{ \
	$Deep_DynArray_Pop(&arr->$arr); \
} \
static Deep$Inline void Deep_DynArray$##tag##_RemoveAt(Deep_DynArray(tag)* arr, size_t index) \
{ \
	$Deep_DynArray_RemoveAt(&arr->$arr, index); \
} \
static Deep$Inline void Deep_DynArray$##tag##_Shrink(Deep_DynArray(tag)* arr) \
{ \
	$Deep_DynArray_Shrink(&arr->$arr); \
}

#define $Deep_DynArray_Decl_Func_Push(type, tag) \
static Deep$Inline void Deep_DynArray$##tag##_Push(Deep_DynArray(tag)* arr, type value) \
{ \
	$Deep_DynArray_Push(&arr->$arr, &value); \
} \

/*
* The following is used to define the "raw" version of Deep_DynArray 
* which uses a custom Create function to assign sizeof(type).
*/
$Deep_DynArray_Decl_Type(unsigned char, raw)
static Deep$Inline void Deep_DynArray$raw_Create(Deep_DynArray(raw)* arr, size_t typeSize)
{
	$Deep_DynArray_Create(&arr->$arr, typeSize);
}
$Deep_DynArray_Decl_Func(unsigned char, raw)
static Deep$Inline void Deep_DynArray$raw_Push(Deep_DynArray(raw)* arr, void* value)
{
	$Deep_DynArray_Push(&arr->$arr, value);
}