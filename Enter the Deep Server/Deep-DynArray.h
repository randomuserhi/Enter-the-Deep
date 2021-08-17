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
} Deep_DynArray_Full;

#define Deep_DynArray(tag) struct Deep_DynArray__##tag

Deep_DynArray_Full _Deep_DynArray_Create(size_t typeSize);
void _Deep_DynArray_Free(Deep_DynArray_Full* arr);
void _Deep_DynArray_EmptyPush(Deep_DynArray_Full* arr);
void _Deep_DynArray_Pop(Deep_DynArray_Full* arr);
void _Deep_DynArray_RemoveAt(Deep_DynArray_Full* arr, size_t index);
void _Deep_DynArray_Shrink(Deep_DynArray_Full* arr);

//May be unsafe (undefined behaviour)
#define Deep_DynArray_Cast(tag, arr) (*(Deep_DynArray(tag)*)(&arr))

#define Deep_DynArray_Create(tag) Deep_DynArray__##tag##__Create()
#define Deep_DynArray_Free(tag, arr) Deep_DynArray__##tag##__Free(&arr) 
#define Deep_DynArray_EmptyPush(tag, arr) Deep_DynArray__##tag##__EmptyPush(&arr) 
#define Deep_DynArray_Push(tag, arr, value) Deep_DynArray__##tag##__Push(&arr, value) 
#define Deep_DynArray_Pop(tag, arr) Deep_DynArray__##tag##__Pop(&arr) 
#define Deep_DynArray_RemoveAt(tag, arr, index) Deep_DynArray__##tag##__RemoveAt(&arr, index) 
#define Deep_DynArray_Shrink(tag, arr) Deep_DynArray__##tag##__Shrink(&arr) 

#define Deep_DynArray_Decl(type, tag) \
_Deep_DynArray_Decl_Type(type, tag) \
static Deep__Inline Deep_DynArray(tag) Deep_DynArray__##tag##__Create() \
{ \
	Deep_DynArray_Full tmp = _Deep_DynArray_Create(sizeof(type)); \
	return *((Deep_DynArray(tag)*)((Deep_DynArray_Full*)&(tmp))); \
} \
_Deep_DynArray_Decl_Func(type, tag)

#define _Deep_DynArray_Decl_Type(type, tag) Deep_DynArray(tag) { union { Deep_DynArray_Full full; struct { size_t size; size_t capacity; type* $; }; }; };
#define _Deep_DynArray_Decl_Func(type, tag) \
static Deep__Inline void Deep_DynArray__##tag##__Free(Deep_DynArray(tag)* arr) \
{ \
	_Deep_DynArray_Free(&arr->full); \
} \
static Deep__Inline void Deep_DynArray__##tag##__EmptyPush(Deep_DynArray(tag)* arr) \
{ \
	_Deep_DynArray_EmptyPush(&arr->full); \
} \
static Deep__Inline void Deep_DynArray__##tag##__Push(Deep_DynArray(tag)* arr, type value) \
{ \
	if (arr->full.typeSize == sizeof(type)) \
	{ \
		_Deep_DynArray_EmptyPush(&arr->full); \
		if (arr->full.data) ((type*)(arr->full.data))[arr->full.size - 1] = value; \
	} \
} \
static Deep__Inline void Deep_DynArray__##tag##__Pop(Deep_DynArray(tag)* arr) \
{ \
	_Deep_DynArray_Pop(&arr->full); \
} \
static Deep__Inline void Deep_DynArray__##tag##__RemoveAt(Deep_DynArray(tag)* arr, size_t index) \
{ \
	_Deep_DynArray_RemoveAt(&arr->full, index); \
} \
static Deep__Inline void Deep_DynArray__##tag##__Shrink(Deep_DynArray(tag)* arr) \
{ \
	_Deep_DynArray_Shrink(&arr->full); \
}

//Define Raw type :
_Deep_DynArray_Decl_Type(char, raw)
static Deep__Inline Deep_DynArray(raw) Deep_DynArray__raw__Create(size_t typeSize)
{
	Deep_DynArray_Full tmp = _Deep_DynArray_Create(typeSize);
	return *((Deep_DynArray(raw)*)((Deep_DynArray_Full*)&(tmp)));
}
_Deep_DynArray_Decl_Func(char, raw)

#endif