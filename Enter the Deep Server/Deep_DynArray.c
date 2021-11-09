#include "Deep_DynArray.h"

extern Deep_Inline void _Deep_DynArray_Create(struct _Deep_DynArray* arr, size_t typeSize);

void _Deep_DynArray_Free(struct _Deep_DynArray* arr)
{
	if (arr) 
	{
		free(arr->data);
		arr->data = NULL;
	}
}

extern Deep_Inline void _Deep_DynArray_ErrorFree(struct _Deep_DynArray* arr);

extern Deep_Inline void* _Deep_DynArray_Push(struct _Deep_DynArray* arr);

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
			if (newCapacity != 0)
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
			else
			{
				free(arr->data);
				arr->data = NULL;
				arr->capacity = newCapacity;
			}
		}
	}
}

void _Deep_DynArray_Reserve(struct _Deep_DynArray* arr, size_t size)
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
