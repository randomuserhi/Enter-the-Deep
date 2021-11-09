#include "Deep_DynArray.h"

void _Deep_DynArray_Create(struct _Deep_DynArray* arr, size_t typeSize)
{
	arr->data = malloc(typeSize * DEEP_DYNARRAY_SIZE);
	arr->size = 0;
	arr->capacity = DEEP_DYNARRAY_SIZE;
	arr->typeSize = typeSize;
	arr->options.freeOnError = DEEP_DYNARRAY_FREE_ON_ERROR;
}

void _Deep_DynArray_Free(struct _Deep_DynArray* arr)
{
	free(arr->data);
	arr->data = NULL;
}

Deep_Inline void _Deep_DynArray_ErrorFree(struct _Deep_DynArray* arr)
{
	if (arr->options.freeOnError)
	{
		free(arr->data);
		arr->data = NULL;
	}
}

void* _Deep_DynArray_Push(struct _Deep_DynArray* arr)
{
	if (arr->data)
	{
		if (arr->size == arr->capacity)
		{
			size_t newCapacity = (size_t)(arr->capacity * DEEP_DYNARRAY_GROWTHRATE);
			if (newCapacity == arr->capacity) ++newCapacity;
			void* tmp = realloc(arr->data, arr->typeSize * newCapacity);
			if (tmp)
			{
				arr->data = tmp;
				arr->capacity = newCapacity;
				++arr->size;
				return arr->data + arr->typeSize * (arr->size - 1);
			}
			else
			{
				_Deep_DynArray_ErrorFree(arr);
				return NULL;
			}
		}
		else
		{
			++arr->size;
			return arr->data + arr->typeSize * (arr->size - 1);
		}
	}
	return NULL;
}

void _Deep_DynArray_Pop(struct _Deep_DynArray* arr)
{
	if (arr->data)
	{
		if (arr->size > 0)
		{
			--arr->size;
		}
	}
}

void _Deep_DynArray_RemoveAt(struct _Deep_DynArray* arr, size_t index)
{
	if (arr->data)
	{
		if (arr->size > 1 && index > 0 && index < arr->size)
		{
			const size_t size = arr->size - 1 - index;
			if (size != 0) memmove(arr->data + index * arr->typeSize, arr->data + (index + 1) * arr->typeSize, size * arr->typeSize);
			--arr->size;
		}
	}
}

void _Deep_DynArray_Shrink(struct _Deep_DynArray* arr)
{
	if (arr->data)
	{
		const size_t newCapacity = arr->size;
		if (newCapacity != arr->capacity)
		{
			void* tmp = realloc(arr->data, arr->typeSize * newCapacity);
			if (tmp)
			{
				arr->data = tmp;
				arr->capacity = newCapacity;
			}
			else
			{
				_Deep_DynArray_ErrorFree(arr);
			}
		}
	}
}

void _Deep_DynArray_Reserve(struct _Deep_DynArray* arr, size_t size)
{
	if (arr->data)
	{
		const size_t newCapacity = arr->size + size;
		if (newCapacity > arr->capacity)
		{
			void* tmp = realloc(arr->data, arr->typeSize * newCapacity);
			if (tmp)
			{
				arr->data = tmp;
				arr->capacity = newCapacity;
				arr->size = size;
			}
			else
			{
				_Deep_DynArray_ErrorFree(arr);
			}
		}
		else
		{
			arr->size = size;
		}
	}
	else
	{
		void* tmp = malloc(arr->typeSize * size);
		if (tmp)
		{
			arr->data = tmp;
			arr->capacity = size;
			arr->size = size;
		}
	}
}