#pragma once

#include "Deep.h"

#define DEEP_DYNAMIC_ARR_SIZE 10 // Default size for dynamic arrays (component storage)

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
	size_t typeSize; // Size of type
	size_t capacity; // Capacity of array (not number of elements in array)
} _Deep_DynamicArr;

typedef unsigned char Deep_DynamicArr;

// Careful with this header code
// use of casting to (_Deep_DynamicArr*) stops compiler warnings, but the warning has a point 
// (refer to Type punning, Strict Aliasing and Alignment issues with casting)
// Technically should be fine as I never reinterpret the bytes of the struct differently (Type Punning)
// (in otherwords converting between void* and T* will always return the same pointer, same with char* and T*)
// and malloc guarantees alignment.
#define _Deep_DynamicArr_Header(arr) ((_Deep_DynamicArr*)((Deep_DynamicArr*)(arr) - sizeof(_Deep_DynamicArr)))
#define _Deep_DynamicArr_Realloc_Base(dest, src, newCapacity) dest = src; dest->capacity = newCapacity; dest->begin = (Deep_DynamicArr*)dest + sizeof *dest
#define _Deep_DynamicArr_Realloc(dest, src, newCapacity, currSize, typeSize) _Deep_DynamicArr_Realloc_Base(dest, src, newCapacity); dest->end = dest->begin + typeSize * (currSize)
#define _Deep_DynamicArr_Realloc_Void(dest, src, newCapacity, currSize) _Deep_DynamicArr_Realloc_Base(dest, src, newCapacity); dest->end = dest->begin + dest->typeSize * (currSize)

#define Deep_DynamicArr_Create_Raw(typeSize, arr) Deep_DynamicArr arr = _Deep_DynamicArr_Create(typeSize)
#define Deep_DynamicArr_Create(typename, arr) typename* arr = (typename*)_Deep_DynamicArr_Create(sizeof(typename))
Deep_DynamicArr* _Deep_DynamicArr_Create(size_t typeSize);

#define Deep_DynamicArr_Free(arr) free(_Deep_DynamicArr_Header(arr))

#define Deep_DynamicArr_Size(arr) _Deep_DynamicArr_Size(_Deep_DynamicArr_Header(arr))
Deep__Force_Inline size_t _Deep_DynamicArr_Size(_Deep_DynamicArr* arr)
{
	return (arr->end - arr->begin) / arr->typeSize;
}

#if defined DEEP_ERRORHANDLING_VERBOSE

#define Deep_DynamicArr_Push(arr, item) \
do {\
	if (arr) \
	{ \
		_DEEP_DYNAMIC_ARR_RESULT = DEEP_DYNAMIC_ARR_NOERROR; \
		_Deep_DynamicArr* header = _Deep_DynamicArr_Header(arr); \
		if (header->typeSize) \
		{ \
			if (header->typeSize == sizeof item) \
			{ \
				size_t arrSize = _Deep_DynamicArr_Size(header); \
				if (arrSize == header->capacity) \
				{ \
					size_t newCapacity = (size_t)(header->capacity * 2); \
					if (newCapacity == header->capacity) ++newCapacity; \
					void* tmp = realloc(header, sizeof(_Deep_DynamicArr) + header->typeSize * newCapacity); \
					if (tmp) \
					{ \
						_Deep_DynamicArr_Realloc(header, tmp, newCapacity, arrSize, header->typeSize); \
						*((void**)&(arr)) = header->begin; \
						arr[arrSize] = item; \
						header->end += header->typeSize; \
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
					arr[arrSize] = item; \
					header->end += header->typeSize; \
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
		_Deep_DynamicArr* header = _Deep_DynamicArr_Header(arr); \
		int typeSize = header->typeSize; \
		if (typeSize) \
		{ \
			size_t arrSize = _Deep_DynamicArr_Size(header); \
			if (arrSize == header->capacity) \
			{ \
				size_t newCapacity = (size_t)(header->capacity * 2); \
				if (newCapacity == header->capacity) ++newCapacity; \
				void* tmp = realloc(header, sizeof(_Deep_DynamicArr) + typeSize * newCapacity); \
				if (tmp) \
				{ \
					_Deep_DynamicArr_Realloc(header, tmp, newCapacity, arrSize, typeSize); \
					* ((void**)&(arr)) = header->begin; \
					header->end += typeSize; \
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
				header->end += typeSize; \
			} \
		} \
		else \
			_DEEP_DYNAMIC_ARR_RESULT = DEEP_DYNAMIC_ARR_ERROR_NULL; \
	} \
	else \
		_DEEP_DYNAMIC_ARR_RESULT = DEEP_DYNAMIC_ARR_ERROR_NULL; \
} while(0)

#define Deep_DynamicArr_EmptyPushBlock(arr, num) _DEEP_DYNAMIC_ARR_RESULT = _Deep_DynamicArr_EmptyPush(_Deep_DynamicArr_Header(arr), &arr, num)
#define Deep_DynamicArr_Reserve(arr, num) _DEEP_DYNAMIC_ARR_RESULT = _Deep_DynamicArr_Reserve(_Deep_DynamicArr_Header(arr), &arr, num)

#define Deep_DynamicArr_Pop(arr) \
do { \
	_DEEP_DYNAMIC_ARR_RESULT = DEEP_DYNAMIC_ARR_NOERROR; \
	_Deep_DynamicArr* dynArray = _Deep_DynamicArr_Header(arr); \
	if (dynArray->begin != dynArray->end) \
		dynArray->end -= dynArray->typeSize; \
	else \
		_DEEP_DYNAMIC_ARR_RESULT = DEEP_DYNAMIC_ARR_ERROR_EMPTY; \
} while(0)

#else

#define Deep_DynamicArr_Push(arr, item) \
do {\
	if (arr) \
	{ \
		_Deep_DynamicArr* header = _Deep_DynamicArr_Header(arr); \
		if (header->typeSize && header->typeSize == sizeof item) \
		{ \
			size_t arrSize = _Deep_DynamicArr_Size(header); \
			if (arrSize == header->capacity) \
			{ \
				size_t newCapacity = (size_t)(header->capacity * 2); \
				if (newCapacity == header->capacity) ++newCapacity; \
				void* tmp = realloc(header, sizeof(_Deep_DynamicArr) + header->typeSize * newCapacity); \
				if (tmp) \
				{ \
					_Deep_DynamicArr_Realloc(header, tmp, newCapacity, arrSize, header->typeSize); \
					*((void**)&(arr)) = header->begin; \
					arr[arrSize] = item; \
					header->end += header->typeSize; \
				} \
				else { free(header); arr = NULL; } \
			} \
			else \
			{ \
				arr[arrSize] = item; \
				header->end += header->typeSize; \
			} \
		} \
	} \
} while(0)

#define Deep_DynamicArr_EmptyPush(arr)  \
do {\
	if (arr) \
	{ \
		_Deep_DynamicArr* header = _Deep_DynamicArr_Header(arr); \
		if (header->typeSize) \
		{ \
			size_t arrSize = _Deep_DynamicArr_Size(header); \
			if (arrSize == header->capacity) \
			{ \
				size_t newCapacity = (size_t)(header->capacity * 2); \
				if (newCapacity == header->capacity) ++newCapacity; \
				void* tmp = realloc(header, sizeof(_Deep_DynamicArr) + header->typeSize * newCapacity); \
				if (tmp) \
				{ \
					_Deep_DynamicArr_Realloc(header, tmp, newCapacity, arrSize, header->typeSize); \
					*((void**)&(arr)) = header->begin; \
					header->end += header->typeSize; \
				} \
				else { free(header); arr = NULL; } \
			} \
			else \
			{ \
				header->end += header->typeSize; \
			} \
		} \
	} \
} while(0)

#define Deep_DynamicArr_EmptyPushBlock(arr, num) _Deep_DynamicArr_EmptyPush(_Deep_DynamicArr_Header(arr), &arr, num)
#define Deep_DynamicArr_Reserve(arr, num) _Deep_DynamicArr_Reserve(_Deep_DynamicArr_Header(arr), &arr, num)

#define Deep_DynamicArr_Pop(arr) \
do { \
	_Deep_DynamicArr* dynArray = _Deep_DynamicArr_Header(arr); \
	if (dynArray->begin != dynArray->end) \
		dynArray->end -= dynArray->typeSize; \
} while(0)

#endif

Deep__Force_Inline int _Deep_DynamicArr_Reserve(_Deep_DynamicArr* dynArray, void** arr, size_t num)
{
	if (!dynArray || dynArray->typeSize == 0) return DEEP_DYNAMIC_ARR_ERROR_NULL;
	if (num == 0) return DEEP_DYNAMIC_ARR_NOERROR;
	size_t size = _Deep_DynamicArr_Size(dynArray);
	size_t newCapacity = size + num;
	if (newCapacity > dynArray->capacity)
	{
		void* tmp = realloc(dynArray, sizeof(_Deep_DynamicArr) + dynArray->typeSize * newCapacity);
		if (!tmp)
		{
			free(dynArray);
			dynArray = NULL;
			return DEEP_DYNAMIC_ARR_ERROR_MALLOC;
		}
		_Deep_DynamicArr_Realloc_Void(dynArray, tmp, newCapacity, size);
		*arr = dynArray->begin;
	}
	return DEEP_DYNAMIC_ARR_NOERROR;
}

Deep__Force_Inline int _Deep_DynamicArr_EmptyPush(_Deep_DynamicArr* dynArray, void** arr, size_t num)
{
	if (!dynArray || dynArray->typeSize == 0) return DEEP_DYNAMIC_ARR_ERROR_NULL;
	if (num == 0) return DEEP_DYNAMIC_ARR_NOERROR;
	size_t size = _Deep_DynamicArr_Size(dynArray);
	size_t newCapacity = size + num;
	if (size + num > dynArray->capacity)
	{
		void* tmp = realloc(dynArray, sizeof(_Deep_DynamicArr) + dynArray->typeSize * newCapacity);
		if (!tmp)
		{
			free(dynArray);
			dynArray = NULL;
			return DEEP_DYNAMIC_ARR_ERROR_MALLOC;
		}
		_Deep_DynamicArr_Realloc_Void(dynArray, tmp, newCapacity, size);
		*arr = dynArray->begin;
	}
	dynArray->end += dynArray->typeSize * num;
	return DEEP_DYNAMIC_ARR_NOERROR;
}

int Deep_DynamicArr_Shrink();