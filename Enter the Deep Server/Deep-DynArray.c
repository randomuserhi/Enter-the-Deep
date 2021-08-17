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

inline void reallocDynArr(Deep_DynArr_Head** arr, void* tmp, size_t arrHeadSize, size_t newCapacity)
{
	(*arr) = tmp;
	(*arr)->data = (char*)(*arr) + arrHeadSize;
	(*arr)->capacity = newCapacity;
}

Deep_DynArr_Head* _Deep_DynArr_Create(size_t arrHeadSize, size_t typeSize)
{
	Deep_DynArr_Head* arr;
	void* tmp = malloc(arrHeadSize + typeSize * DEEP_DYNAMIC_ARR_SIZE);
	if (!tmp) return NULL;

	arr = tmp;
	arr->data = (char*)arr + arrHeadSize;
	arr->size = 0;
	arr->capacity = DEEP_DYNAMIC_ARR_SIZE;

	return arr;
}

void _Deep_DynArr_EmptyPush(Deep_DynArr_Head** arr, size_t arrHeadSize, size_t typeSize)
{
	if (*arr) 
	{ 
		if ((*arr)->size == (*arr)->capacity)
		{ 
			size_t newCapacity = (size_t)((*arr)->capacity * DEEP_DYNAMIC_ARR_GROWTHRATE);
			if (newCapacity == (*arr)->capacity) ++newCapacity;
			void* tmp = realloc(*arr, arrHeadSize + typeSize * newCapacity);
			if (tmp) 
			{ 
				reallocDynArr(arr, tmp, arrHeadSize, newCapacity);
				++(*arr)->size;
			} 
			else 
			{ 
				free(*arr); 
				*arr = NULL; 
			}
		} 
		else 
		{ 
			++(*arr)->size;
		} 
	} 
}

void _Deep_DynArr_Shrink(Deep_DynArr_Head** arr, size_t arrHeadSize, size_t typeSize)
{
	if (arr)
	{
		size_t newCapacity = (*arr)->size;
		if (newCapacity != (*arr)->capacity)
		{
			void* tmp = realloc(*arr, arrHeadSize + typeSize * newCapacity);
			if (tmp)
			{
				reallocDynArr(arr, tmp, arrHeadSize, newCapacity);
				++(*arr)->size;
			}
			else
			{
				free(*arr);
				*arr = NULL;
			}
		}
	}
}

#endif