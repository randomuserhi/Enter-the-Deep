#pragma once

#include "Deep.h"

#define DEEP_DYNAMIC_ARR_SIZE 10 // Default size for dynamic arrays
#define DEEP_DYNAMIC_ARR_GROWTHRATE 2 //Growthrate for dynamic arrays

/*

TODO:: For some reason Deep_DynamicArray_Push(arr, item) is faster than Deep_DynamicArray_EmptyPush(arr). I don't know why, but it is lmao.
	   => There is a comparison of "header->typeSize == sizeof item" which for some reason causes the loop to be exponentially faster.
	   => If I hardcode the statement and force all items added to be of the size in the if statement, the code runs faster (e.g header->typeSize == 4)
	   => This means a solution to make the code run fast is to code a container for the elements inside the dynamic array (struct Container { char* data; char padding[SIZE]; })
	        => In this way the dynamic array stores a bunch of "Container" and to access the data simply cast the char* data to another type (char* data points to itself)
				=> probably smarter to make "Container" a union for this since that is what they are for. (union Container {char* data; char padding[SIZE];})
		    => This does mean that all elements of Deep_DynamicArray will all be the same size no matter what (the padding size),
			=> In the case of development it just means that the dynamic array container will be the size of the largest component......
				=> (tho we have lots of RAM now a days so maybe it isnt so bad to waste memory haha...)

	   See : https://stackoverflow.com/questions/68324268/evaluating-sizeof-causes-improvement-in-performance-c/68373780#68373780

*/

/*

TODO:: Might change error detection to be less verbose and just return NULL pointer on error.
	   This change would mean that all array functions that can throw will no longer need a 'result' variable,
	   as they would just exit with 'arr = NULL'.

	   Probably will add a compile option in Deep.h for verbos errors or not

*/
#define DEEP_DYNAMIC_ARR_NOERROR 0
#define DEEP_DYNAMIC_ARR_ERROR_NULL 1 // The component list storage is of type null (generated when size is unknown and thus storage is invalid)
#define DEEP_DYNAMIC_ARR_ERROR_MALLOC 2 // malloc or realloc failed
#define DEEP_DYNAMIC_ARR_ERROR_ALIGNMENT 3 // sizeof(Type) was not equal to size of elements
#define DEEP_DYNAMIC_ARR_ERROR_EMPTY 4 // Array was empty

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

#define Deep_DynamicArr_Create_Raw(typeSize, arr) Deep_DynamicArr* arr = _Deep_DynamicArr_Create(typeSize)
#define Deep_DynamicArr_Create(typeName, arr) typeName* arr = (void*)_Deep_DynamicArr_Create(sizeof(typeName))
Deep_DynamicArr* _Deep_DynamicArr_Create(size_t typeSize);

#define Deep_DynamicArr_Size(arr) Deep_DynamicArr_Header(arr)->size
#define Deep_DynamicArr_Free(arr) free(Deep_DynamicArr_Header(arr))

#define Deep_DynamicArr_RawGet(type, arr, index) ((type*)arr)[index]

#if defined DEEP_ERRORHANDLING_VERBOSE

#define Deep_DynamicArr_Push(arr, item) \
do {\
	if (arr) \
	{ \
		_DEEP_DYNAMIC_ARR_RESULT = DEEP_DYNAMIC_ARR_NOERROR; \
		Deep_DynamicArr_Head* header = Deep_DynamicArr_Header(arr); \
		/* Check if typeSize is 0, if so then the array is NULL and should not be operated on */ \
		if (header->typeSize) \
		{ \
			if (header->typeSize == sizeof item) \
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
						*((Deep_DynamicArr*)arr + header->typeSize * header->size) = item; \
						header->end += header->typeSize; \
						++header->size; \
					} \
					else \
					{ \
						_DEEP_DYNAMIC_ARR_RESULT = DEEP_DYNAMIC_ARR_ERROR_MALLOC; \
						free(header); \
						arr = NULL; \
					} \
				} \
				else \
				{ \
					*((Deep_DynamicArr*)arr + header->typeSize * header->size) = item; \
					header->end += header->typeSize; \
					++header->size; \
				} \
			} \
			else \
				_DEEP_DYNAMIC_ARR_RESULT = DEEP_DYNAMIC_ARR_ERROR_ALIGNMENT; \
		} \
		else \
			_DEEP_DYNAMIC_ARR_RESULT = DEEP_DYNAMIC_ARR_ERROR_NULL; \
	} \
	else \
		_DEEP_DYNAMIC_ARR_RESULT = DEEP_DYNAMIC_ARR_ERROR_NULL; \
} while(0)

#define Deep_DynamicArr_EmptyPush(arr)  \
do {\
	if (arr) \
	{ \
		_DEEP_DYNAMIC_ARR_RESULT = DEEP_DYNAMIC_ARR_NOERROR; \
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
					* ((void**)&(arr)) = header->begin; \
					header->end += header->typeSize; \
					++header->size; \
				} \
				else \
				{ \
					_DEEP_DYNAMIC_ARR_RESULT = DEEP_DYNAMIC_ARR_ERROR_MALLOC; \
					free(header); \
					arr = NULL; \
				} \
			} \
			else \
			{ \
				header->end += header->typeSize; \
				++header->size; \
			} \
		} \
		else \
			_DEEP_DYNAMIC_ARR_RESULT = DEEP_DYNAMIC_ARR_ERROR_NULL; \
	} \
	else \
		_DEEP_DYNAMIC_ARR_RESULT = DEEP_DYNAMIC_ARR_ERROR_NULL; \
} while(0)

#define Deep_DynamicArr_Pop(arr) \
do { \
	_DEEP_DYNAMIC_ARR_RESULT = DEEP_DYNAMIC_ARR_NOERROR; \
	Deep_DynamicArr_Head* dynArray = Deep_DynamicArr_Header(arr); \
	if (dynArray->begin != dynArray->end) \
	{ \
		dynArray->end -= dynArray->typeSize; \
		--dynArray->size; \
	} \
	else \
		_DEEP_DYNAMIC_ARR_RESULT = DEEP_DYNAMIC_ARR_ERROR_EMPTY; \
} while(0)

#define Deep_DynamicArr_EmptyPushBlock(arr, num) _DEEP_DYNAMIC_ARR_RESULT = _Deep_DynamicArr_EmptyPush(Deep_DynamicArr_Header(arr), &arr, num)
#define Deep_DynamicArr_Reserve(arr, num) _DEEP_DYNAMIC_ARR_RESULT = _Deep_DynamicArr_Reserve(Deep_DynamicArr_Header(arr), &arr, num)
#define Deep_DynamicArr_Shrink(arr) _DEEP_DYNAMIC_ARR_RESULT = _Deep_DynamicArr_Shrink(Deep_DynamicArr_Header(arr), &arr)

#else

#define Deep_DynamicArr_Push(arr, item) \
do {\
	if (arr) \
	{ \
		Deep_DynamicArr_Head* header = Deep_DynamicArr_Header(arr); \
		/* Check if typeSize is 0, if so then the array is NULL and should not be operated on */ \
		if (header->typeSize && header->typeSize == sizeof item) \
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
					*((Deep_DynamicArr*)arr + header->typeSize * header->size) = item; \
					header->end += header->typeSize; \
					++header->size; \
				} \
				else { free(header); arr = NULL; } \
			} \
			else \
			{ \
				*((Deep_DynamicArr*)arr + header->typeSize * header->size) = item; \
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

#define Deep_DynamicArr_EmptyPushBlock(arr, num) _Deep_DynamicArr_EmptyPush(Deep_DynamicArr_Header(arr), &arr, num)
#define Deep_DynamicArr_Reserve(arr, num) _Deep_DynamicArr_Reserve(Deep_DynamicArr_Header(arr), &arr, num)
#define Deep_DynamicArr_Shrink(arr) _Deep_DynamicArr_Shrink(Deep_DynamicArr_Header(arr), &arr)

#endif

int _Deep_DynamicArr_Reserve(Deep_DynamicArr_Head* dynArray, void** arr, size_t num);
int _Deep_DynamicArr_EmptyPush(Deep_DynamicArr_Head* dynArray, void** arr, size_t num);
int _Deep_DynamicArr_Shrink(Deep_DynamicArr_Head* dynArray, void** arr);