#pragma once

#include "Deep.h"

#define DEEP_DYNAMIC_VOID_ARR_SIZE 10 //Default size for dynamic arrays (component storage)

#define DEEP_DYNAMIC_VOID_ARR_NOERROR 0
#define DEEP_DYNAMIC_VOID_ARR_NULL 1 //The component list storage is of type null (generated when size is unknown and thus storage is invalid)
#define DEEP_DYNAMIC_VOID_ARR_ERROR_MALLOC 2 //Malloc failed
#define DEEP_DYNAMIC_VOID_ARR_ERROR_ALIGNMENT 3 //sizeof(Type) was note equal to size of elements

typedef struct
{
	unsigned char* _begin; //Pointer to data
	unsigned char* _end; //Pointer to last element
	size_t _typeSize; //Size of type
	size_t _capacity; //Capacity of array (not number of elements in array)
} _Deep_DynamicVoidArr;

typedef unsigned char Deep_DynamicVoidArr;

// Careful with this header code
// use of casting to (_Deep_DynamicVoidArr*) stops compiler warnings, but the warning has a point 
// (refer to Type punning, Strict Aliasing and Alignment issues with casting)
#define _Deep_DynamicVoidArr_Header(arr) (_Deep_DynamicVoidArr*)((Deep_DynamicVoidArr*)arr - sizeof(_Deep_DynamicVoidArr))

#define Deep_DynamicVoidArr_Create_Raw(typename) _Deep_DynamicVoidArr_Create(sizeof(typename))
#define Deep_DynamicVoidArr_Create(typename) (typename*)_Deep_DynamicVoidArr_Create(sizeof(typename))
Deep_DynamicVoidArr* _Deep_DynamicVoidArr_Create(size_t typeSize);

#define Deep_DynamicVoidArr_Free(arr) _Deep_DynamicVoidArr_Free(_Deep_DynamicVoidArr_Header(arr))
void _Deep_DynamicVoidArr_Free(void* arr);

#define Deep_DynamicVoidArr_Size(arr) _Deep_DynamicVoidArr_Size(_Deep_DynamicVoidArr_Header(arr))
size_t _Deep_DynamicVoidArr_Size(void* arr);

#define Deep_DynamicVoidArr_Add(item) _Deep_DynamicVoidArr_Add(sizeof item, item)
void _Deep_DynamicVoidArr_Add(size_t typeSize, Deep_DynamicVoidArr* item);

#define Deep_DynamicVoidArr_Remove(item) _Deep_DynamicVoidArr_Remove(sizeof item, item)
void _Deep_DynamicVoidArr_Remove(size_t typeSize, Deep_DynamicVoidArr* item);

void Deep_DynamicVoidArr_Shrink();