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
	char* data; // Pointer to data
	size_t typeSize;
} Deep_DynArr__raw;

Deep_DynArr__raw Deep_DynArr__raw__Create(size_t typeSize);
void Deep_DynArr__raw__Free(Deep_DynArr__raw* arr);
void Deep_DynArr__raw__EmptyPush(Deep_DynArr__raw* arr);
void Deep_DynArr__raw__Shrink(Deep_DynArr__raw* arr);

#define Deep_DynArray(tag) struct Deep_DynArray__##tag

#define Deep_DynArray_Create(tag) Deep_DynArray__##tag##__Create()
#define Deep_DynArray_Free(tag, arr) Deep_DynArray__##tag##__Free(&arr) 
#define Deep_DynArray_EmptyPush(tag, arr) Deep_DynArray__##tag##__EmptyPush(&arr) 
#define Deep_DynArray_Push(tag, arr, value) Deep_DynArray__##tag##__Push(&arr, value) 
#define Deep_DynArray_Shrink(tag, arr) Deep_DynArray__##tag##__Shrink(&arr) 

//NOTE:: how functions are declared as static to allow for multiple definitions from Deep_DynArray_Decl in multiple .c files
#define Deep_DynArray_Decl(type, tag) \
Deep_DynArray(tag) { union { Deep_DynArr__raw raw; struct { size_t size; size_t capacity; type* $; }; }; }; \
static Deep__Inline Deep_DynArray(tag) Deep_DynArray__##tag##__Create() \
{ \
	Deep_DynArr__raw tmp = Deep_DynArr__raw__Create(sizeof(type)); \
	return *((Deep_DynArray(tag)*)((Deep_DynArr__raw*)&(tmp))); \
} \
static Deep__Inline void Deep_DynArray__##tag##__Free(Deep_DynArray(tag)* arr) \
{ \
	Deep_DynArr__raw__Free(&arr->raw); \
} \
static Deep__Inline void Deep_DynArray__##tag##__EmptyPush(Deep_DynArray(tag)* arr) \
{ \
	if (arr->raw.typeSize == sizeof(type)) \
	{ \
		Deep_DynArr__raw__EmptyPush(&arr->raw); \
	} \
} \
static Deep__Inline void Deep_DynArray__##tag##__Push(Deep_DynArray(tag)* arr, type value) \
{ \
	if (arr->raw.typeSize == sizeof(type)) \
	{ \
		Deep_DynArr__raw__EmptyPush(&arr->raw); \
		if (arr->raw.data) ((type*)(arr->raw.data))[arr->raw.size - 1] = value; \
	} \
} \
static Deep__Inline void Deep_DynArray__##tag##__Shrink(Deep_DynArray(tag)* arr) \
{ \
	if (arr->raw.typeSize == sizeof(type)) \
	{ \
		Deep_DynArr__raw__Shrink(&arr->raw); \
	} \
}

#endif