#include "Deep-Containers-DynArray.h"

void $Deep_DynArray_Create($Deep_DynArray* arr, size_t typeSize)
{
	arr->data = malloc(typeSize * DEEP_DYNAMIC_ARR_SIZE);
	arr->size = 0;
	arr->capacity = DEEP_DYNAMIC_ARR_SIZE;
	arr->typeSize = typeSize;
	arr->options.freeOnError = DEEP_DYNAMIC_ARR_FREE_ON_ERROR;
}

void $Deep_DynArray_Free($Deep_DynArray* arr)
{
	free(arr->data);
	arr->data = NULL;
}

Deep$Inline void $Deep_DynArray_ErrorFree($Deep_DynArray* arr)
{
	if (arr->options.freeOnError)
	{
		free(arr->data);
		arr->data = NULL;
	}
}

void $Deep_DynArray_EmptyPush($Deep_DynArray* arr)
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
				++arr->size;
			}
			else
			{
				$Deep_DynArray_ErrorFree(arr);
			}
		}
		else
		{
			++arr->size;
		}
	}
}

void $Deep_DynArray_Push($Deep_DynArray* arr, void* value)
{
	$Deep_DynArray_EmptyPush(arr); // Any error codes are coughed out by EmptyPush
	if (arr->data) memcpy(arr->data + (arr->size - 1) * arr->typeSize, value, arr->typeSize);
}

void $Deep_DynArray_Pop($Deep_DynArray* arr)
{
	if (arr->data)
	{
		if (arr->size > 0)
		{
			--arr->size;
		}
	}
}

void $Deep_DynArray_RemoveAt($Deep_DynArray* arr, size_t index)
{
	if (arr->data)
	{
		if (arr->size > 1 && index > 0 && index < arr->size)
		{
			size_t size = arr->size - 1 - index;
			if (size != 0) memmove(arr->data + index * arr->typeSize, arr->data + (index + 1) * arr->typeSize, size * arr->typeSize);
			--arr->size;
		}
	}
}

void $Deep_DynArray_Shrink($Deep_DynArray* arr)
{
	if (arr->data)
	{
		size_t newCapacity = arr->size;
		if (newCapacity != arr->capacity)
		{
			void* tmp = realloc(arr->data, arr->typeSize * newCapacity);
			if (tmp)
			{
				arr->data = tmp;
				arr->capacity = newCapacity;
				++arr->size;
			}
			else
			{
				$Deep_DynArray_ErrorFree(arr);
			}
		}
	}
}

void $Deep_DynArray_Reserve($Deep_DynArray* arr, size_t size)
{
	if (arr->data)
	{
		size_t newCapacity = arr->size + size;
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
				$Deep_DynArray_ErrorFree(arr);
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