#include "Deep-DynArray.h"

#if defined(OLD_DEEP_DYNAMIC_IMPLEMENTATION)

Deep_DynamicArr* _Deep_DynamicArr_Create(size_t typeSize)
{
	Deep_DynamicArr_Head* dynArr;
	void* tmp = malloc(sizeof *dynArr + typeSize * DEEP_DYNAMIC_ARR_SIZE);
	if (!tmp) return NULL;

	dynArr = tmp;
	dynArr->begin = (Deep_DynamicArr*)(dynArr + 1); //I'm unsure if this cast is safe (probably should check at somepoint)
	dynArr->end = dynArr->begin;
	dynArr->size = 0;
	dynArr->capacity = DEEP_DYNAMIC_ARR_SIZE;
	dynArr->typeSize = typeSize;

	return dynArr->begin;
}

void _Deep_DynamicArr_Reserve(Deep_DynamicArr_Head* dynArray, void** arr, size_t num)
{
	if (!dynArray || dynArray->typeSize == 0) return;
	if (num == 0) return;
	size_t newCapacity = dynArray->size + num;
	if (newCapacity > dynArray->capacity)
	{
		Deep_DynamicArr_Head* tmp = realloc(dynArray, sizeof(Deep_DynamicArr_Head) + dynArray->typeSize * newCapacity);
		if (!tmp)
		{
			free(dynArray);
			dynArray = NULL;
			return;
		}
		_Deep_DynamicArr_Realloc(dynArray, tmp, newCapacity);
		*arr = dynArray->begin;
	}
	return;
}

void _Deep_DynamicArr_EmptyPush(Deep_DynamicArr_Head* dynArray, void** arr, size_t num)
{
	if (!dynArray || dynArray->typeSize == 0) return;
	if (num == 0) return;
	size_t newCapacity = dynArray->size + num;
	if (dynArray->size + num > dynArray->capacity)
	{
		Deep_DynamicArr_Head* tmp = realloc(dynArray, sizeof(Deep_DynamicArr_Head) + dynArray->typeSize * newCapacity);
		if (!tmp)
		{
			free(dynArray);
			dynArray = NULL;
			return;
		}
		_Deep_DynamicArr_Realloc(dynArray, tmp, newCapacity);
		*arr = dynArray->begin;
	}
	dynArray->end += dynArray->typeSize * num;
	dynArray->size += num;
	return;
}

void _Deep_DynamicArr_Shrink(Deep_DynamicArr_Head* dynArray, void** arr)
{
	if (!dynArray || dynArray->typeSize == 0) return;
	size_t newCapacity = dynArray->size;
	if (newCapacity != dynArray->capacity)
	{
		Deep_DynamicArr_Head* tmp = realloc(dynArray, sizeof(Deep_DynamicArr_Head) + dynArray->typeSize * newCapacity);
		if (!tmp)
		{
			free(dynArray);
			dynArray = NULL;
			return;
		}
		_Deep_DynamicArr_Realloc(dynArray, tmp, newCapacity);
		*arr = dynArray->begin;
	}
	return;
}

#else

Deep_DynArray_Full _Deep_DynArray_Create(size_t typeSize)
{
	Deep_DynArray_Full arr;
	arr.data = malloc(typeSize * DEEP_DYNAMIC_ARR_SIZE);
	arr.size = 0;
	arr.capacity = DEEP_DYNAMIC_ARR_SIZE;
	arr.typeSize = typeSize;
	return arr;
}

void _Deep_DynArray_Free(Deep_DynArray_Full* arr)
{
	free(arr->data);
	arr->data = NULL;
}

void _Deep_DynArray_EmptyPush(Deep_DynArray_Full* arr)
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
			free(arr->data); 
			arr->data = NULL; 
		}
	} 
	else 
	{ 
		++arr->size;
	} 
}

void _Deep_DynArray_Pop(Deep_DynArray_Full* arr)
{
	if (arr->size > 0 && arr->data)
	{
		--arr->size;
	}
}

void _Deep_DynArray_RemoveAt(Deep_DynArray_Full* arr, size_t index)
{
	if (arr->size > 1 && arr->data && index > 0 && index < arr->size)
	{
		size_t size = arr->size - 1 - index;
		if (size != 0)
		{
			memmove(arr->data + index * arr->typeSize, arr->data + (index + 1) * arr->typeSize, size * arr->typeSize);
		}
		--arr->size;
	}
}

void _Deep_DynArray_Shrink(Deep_DynArray_Full* arr)
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
			free(arr);
			arr->data = NULL;
		}
	}
}

#endif