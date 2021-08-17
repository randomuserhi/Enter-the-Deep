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
	char* data; // Pointer to data
	size_t size; // Number of elements in array (to optimize out division)
	size_t capacity; // Capacity of array (not number of elements in array)
} Deep_DynArr_Head;

Deep_DynArr_Head* _Deep_DynArr_Create(size_t arrHeadSize, size_t typeSize);
void _Deep_DynArr_EmptyPush(Deep_DynArr_Head** arr, size_t arrHeadSize, size_t typeSize);
void _Deep_DynArr_Shrink(Deep_DynArr_Head** arr, size_t arrHeadSize, size_t typeSize);

#define _Deep_DynArray(type) struct _Deep_DynArray_##type
#define Deep_DynArray(type) struct _Deep_DynArray_##type*

#define Deep_DynArray_Get(type, arr) Deep_DynArray_##type##(&arr) 
#define Deep_DynArray_Create(type) Deep_DynArray_##type##_Create()
#define Deep_DynArray_Free(type, arr) Deep_DynArray_##type##_Free(&arr) 
#define Deep_DynArray_EmptyPush(type, arr) Deep_DynArray_##type##_EmptyPush(&arr) 
#define Deep_DynArray_Push(type, arr, value) Deep_DynArray_##type##_Push(&arr, value) 
#define Deep_DynArray_Shrink(type, arr) Deep_DynArray_##type##_Shrink(&arr) 

#define Deep_DynArray_Decl(type) \
_Deep_DynArray(type) { Deep_DynArr_Head arr; }; \
inline type* Deep_DynArray_##type##(Deep_DynArray(type) arr) \
{ \
	return (type*)arr->arr.data; \
} \
inline Deep_DynArray(type) Deep_DynArray_##type##_Create() \
{ \
	return (Deep_DynArray(type))_Deep_DynArr_Create(sizeof(_Deep_DynArray(type)), sizeof(type)); \
} \
inline void Deep_DynArray_##type##_Free(Deep_DynArray(type)* arr) \
{ \
	free(*arr); \
	*arr = NULL; \
} \
inline void Deep_DynArray_##type##_EmptyPush(Deep_DynArray(type)* arr) \
{ \
	_Deep_DynArr_EmptyPush((Deep_DynArr_Head**)arr, sizeof(_Deep_DynArray(type)), sizeof(type)); \
} \
inline void Deep_DynArray_##type##_Push(Deep_DynArray(type)* arr, type value) \
{ \
	_Deep_DynArr_EmptyPush((Deep_DynArr_Head**)arr, sizeof(_Deep_DynArray(type)), sizeof(type)); \
	if (*arr) ((type*)(*arr)->arr.data)[(*arr)->arr.size - 1] = value; \
} \
inline void Deep_DynArray_##type##_Shrink(Deep_DynArray(type)* arr) \
{ \
	_Deep_DynArr_Shrink((Deep_DynArr_Head**)arr, sizeof(_Deep_DynArray(type)), sizeof(type)); \
}

#endif