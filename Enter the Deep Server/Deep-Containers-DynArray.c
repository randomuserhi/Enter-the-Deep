#include "Deep-Containers-DynArray.h"

void $Deep_DynArray_Create(struct $Deep_DynArray* arr, size_t typeSize)
{
	arr->data = malloc(typeSize * DEEP_DYNAMIC_ARR_SIZE);
	arr->end = arr->data;
	arr->size = 0;
	arr->capacity = DEEP_DYNAMIC_ARR_SIZE;
	arr->typeSize = typeSize;
	arr->options.freeOnError = DEEP_DYNAMIC_ARR_FREE_ON_ERROR;
}

void $Deep_DynArray_Free(struct $Deep_DynArray* arr)
{
	free(arr->data);
	arr->data = NULL;
	arr->end = NULL;
}

Deep$Inline void $Deep_DynArray_ErrorFree(struct $Deep_DynArray* arr)
{
	if (arr->options.freeOnError)
	{
		free(arr->data);
		arr->data = NULL;
		arr->end = NULL;
	}
}

void* $Deep_DynArray_Push(struct $Deep_DynArray* arr)
{
	if (arr->data)
	{
		if (arr->size == arr->capacity)
		{
			size_t newCapacity = (size_t)(arr->capacity * DEEP_DYNAMIC_ARR_GROWTHRATE);
			if (newCapacity == arr->capacity) ++newCapacity;
			void* tmp = realloc(arr->data, arr->typeSize * newCapacity);
			if (tmp)
			{
				arr->data = tmp;
				arr->capacity = newCapacity;
				arr->end += arr->size != 0 ? arr->typeSize : 0; //TODO:: find a better way than a ternary operator
				++arr->size;
			}
			else
			{
				$Deep_DynArray_ErrorFree(arr);
			}
		}
		else
		{
			arr->end += arr->size != 0 ? arr->typeSize : 0; //TODO:: find a better way than a ternary operator
			++arr->size;
		}
		return arr->end;
	}
	return NULL;
}

void $Deep_DynArray_Pop(struct $Deep_DynArray* arr)
{
	if (arr->data)
	{
		if (arr->size > 0)
		{
			arr->end -= arr->typeSize;
			--arr->size;
		}
	}
}

void $Deep_DynArray_RemoveAt(struct $Deep_DynArray* arr, size_t index)
{
	if (arr->data)
	{
		if (arr->size > 1 && index > 0 && index < arr->size)
		{
			const size_t size = arr->size - 1 - index;
			if (size != 0) memmove(arr->data + index * arr->typeSize, arr->data + (index + 1) * arr->typeSize, size * arr->typeSize);
			--arr->size;
			arr->end -= arr->typeSize;
		}
	}
}

void $Deep_DynArray_Shrink(struct $Deep_DynArray* arr)
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
				$Deep_DynArray_ErrorFree(arr);
			}
		}
	}
}

void $Deep_DynArray_Reserve(struct $Deep_DynArray* arr, size_t size)
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
				arr->end = arr->data + (arr->size - 1) * arr->typeSize;
			}
			else
			{
				$Deep_DynArray_ErrorFree(arr);
			}
		}
		else
		{
			arr->size = size;
			arr->end = arr->data + (arr->size - 1) * arr->typeSize;
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
			arr->end = arr->data + (arr->size - 1) * arr->typeSize;
		}
	}
}