#ifndef h_Deep_DynArray
#define h_Deep_DynArray

#include "Deep.h"

#define DEEP_DYNARRAY_SIZE 0 // Default size for dynamic arrays
#define DEEP_DYNARRAY_GROWTHRATE 1.5f //Growthrate for dynamic arrays

#define DEEP_DYNARRAY_FREE_ON_ERROR 1
#define DEEP_DYNARRAY_KEEP_ON_ERROR 0

struct Deep_DynArray_Options
{
	char freeOnError; // If set, will free the contents of the array when an error is caught, otherwise the contents remain
};

struct _Deep_DynArray
{
	size_t size; // Number of elements in array (to optimize out division)
	size_t capacity; // Capacity of array (not number of elements in array)
	unsigned char* data; // Pointer to data
	struct Deep_DynArray_Options options; // Array options

	size_t typeSize; // sizeof(type)
};

void _Deep_DynArray_Create(struct _Deep_DynArray* arr, size_t typeSize);
void _Deep_DynArray_Free(struct _Deep_DynArray* arr);
void* _Deep_DynArray_Push(struct _Deep_DynArray* arr);
void _Deep_DynArray_Pop(struct _Deep_DynArray* arr);
void _Deep_DynArray_RemoveAt(struct _Deep_DynArray* arr, size_t index);
void _Deep_DynArray_Shrink(struct _Deep_DynArray* arr);
void _Deep_DynArray_Reserve(struct _Deep_DynArray* arr, size_t size);

/*
* Defines a Deep_DynArray of type(tag).
*/
#define Deep_DynArray(tag) Deep_DynArray_##tag

/*
* Utility macros for getting functions for type(tag).
*/

#define Deep_DynArray_ReinterpretCast(tag) Deep_DynArray_##tag##_ReinterpretCast
#define Deep_DynArray_Create(tag) Deep_DynArray_##tag##_Create
#define Deep_DynArray_Free(tag) Deep_DynArray_##tag##_Free
#define Deep_DynArray_Push(tag) Deep_DynArray_##tag##_Push
#define Deep_DynArray_Pop(tag) Deep_DynArray_##tag##_Pop
#define Deep_DynArray_RemoveAt(tag) Deep_DynArray_##tag##_RemoveAt
#define Deep_DynArray_Shrink(tag) Deep_DynArray_##tag##_Shrink 
#define Deep_DynArray_Reserve(tag) Deep_DynArray_##tag##_Reserve

#define Deep_DynArray_Decl(type, tag) \
_Deep_DynArray_Decl_Type(type, tag) \
static Deep_Inline void Deep_DynArray_##tag##_Create(struct Deep_DynArray(tag)* arr) \
{ \
	_Deep_DynArray_Create(&arr->_arr, sizeof(type)); \
} \
_Deep_DynArray_Decl_Func(type, tag)

#define _Deep_DynArray_Decl_Type(type, tag) \
struct Deep_DynArray(tag) \
{ \
	union \
	{ \
		struct _Deep_DynArray _arr; \
		struct \
		{  \
			size_t size; \
			size_t capacity; \
			type* values; \
			struct Deep_DynArray_Options options; \
		}; \
	}; \
};

#define _Deep_DynArray_Decl_Func(type, tag) \
static Deep_Inline struct Deep_DynArray(tag) Deep_DynArray_##tag##_ReinterpretCast(void* arr) \
{ \
	struct Deep_DynArray(tag) dst; \
	memcpy(&dst, arr, sizeof dst); \
	return dst; \
} \
static Deep_Inline void Deep_DynArray_##tag##_Free(struct Deep_DynArray(tag)* arr) \
{ \
	_Deep_DynArray_Free(&arr->_arr); \
} \
static Deep_Inline void Deep_DynArray_##tag##_Pop(struct Deep_DynArray(tag)* arr) \
{ \
	_Deep_DynArray_Pop(&arr->_arr); \
} \
static Deep_Inline void Deep_DynArray_##tag##_RemoveAt(struct Deep_DynArray(tag)* arr, size_t index) \
{ \
	_Deep_DynArray_RemoveAt(&arr->_arr, index); \
} \
static Deep_Inline void Deep_DynArray_##tag##_Shrink(struct Deep_DynArray(tag)* arr) \
{ \
	_Deep_DynArray_Shrink(&arr->_arr); \
} \
static Deep_Inline void Deep_DynArray_##tag##_Reserve(struct Deep_DynArray(tag)* arr, size_t size) \
{ \
	_Deep_DynArray_Reserve(&arr->_arr, size); \
} \
static Deep_Inline type* Deep_DynArray_##tag##_Push(struct Deep_DynArray(tag)* arr) \
{ \
	return _Deep_DynArray_Push(&arr->_arr); \
}

/*
* The following is used to define the "raw" version of Deep_DynArray 
* which uses a custom Create function to assign sizeof(type).
*/
_Deep_DynArray_Decl_Type(unsigned char, raw)
static Deep_Inline void Deep_DynArray_raw_Create(struct Deep_DynArray(raw)* arr, size_t typeSize)
{
	_Deep_DynArray_Create(&arr->_arr, typeSize);
}
_Deep_DynArray_Decl_Func(unsigned char, raw)

#endif