#include "Deep-DynArray.h"

Deep_DynamicArr* _Deep_DynamicArr_Create(size_t typeSize)
{
	Deep_DynamicArr_Head* dynArr;
	void* tmp = malloc(sizeof *dynArr + typeSize * DEEP_DYNAMIC_ARR_SIZE);
	if (!tmp) return NULL;

	dynArr = tmp;
	dynArr->begin = (Deep_DynamicArr*)dynArr + sizeof *dynArr; //I'm unsure if this cast is safe (probably should check at somepoint)
	dynArr->end = dynArr->begin;
	dynArr->size = 0;
	dynArr->capacity = DEEP_DYNAMIC_ARR_SIZE;
	dynArr->typeSize = typeSize;

	return dynArr->begin;
}

int _Deep_DynamicArr_Reserve(Deep_DynamicArr_Head* dynArray, void** arr, size_t num)
{
	if (!dynArray || dynArray->typeSize == 0) return DEEP_DYNAMIC_ARR_ERROR_NULL;
	if (num == 0) return DEEP_DYNAMIC_ARR_NOERROR;
	size_t newCapacity = dynArray->size + num;
	if (newCapacity > dynArray->capacity)
	{
		Deep_DynamicArr_Head* tmp = realloc(dynArray, sizeof(Deep_DynamicArr_Head) + dynArray->typeSize * newCapacity);
		if (!tmp)
		{
			free(dynArray);
			dynArray = NULL;
			return DEEP_DYNAMIC_ARR_ERROR_MALLOC;
		}
		_Deep_DynamicArr_Realloc(dynArray, tmp, newCapacity);
		*arr = dynArray->begin;
	}
	return DEEP_DYNAMIC_ARR_NOERROR;
}

int _Deep_DynamicArr_EmptyPush(Deep_DynamicArr_Head* dynArray, void** arr, size_t num)
{
	if (!dynArray || dynArray->typeSize == 0) return DEEP_DYNAMIC_ARR_ERROR_NULL;
	if (num == 0) return DEEP_DYNAMIC_ARR_NOERROR;
	size_t newCapacity = dynArray->size + num;
	if (dynArray->size + num > dynArray->capacity)
	{
		Deep_DynamicArr_Head* tmp = realloc(dynArray, sizeof(Deep_DynamicArr_Head) + dynArray->typeSize * newCapacity);
		if (!tmp)
		{
			free(dynArray);
			dynArray = NULL;
			return DEEP_DYNAMIC_ARR_ERROR_MALLOC;
		}
		_Deep_DynamicArr_Realloc(dynArray, tmp, newCapacity);
		*arr = dynArray->begin;
	}
	dynArray->end += dynArray->typeSize * num;
	dynArray->size += num;
	return DEEP_DYNAMIC_ARR_NOERROR;
}

int _Deep_DynamicArr_Shrink(Deep_DynamicArr_Head* dynArray, void** arr)
{
	if (!dynArray || dynArray->typeSize == 0) return DEEP_DYNAMIC_ARR_ERROR_NULL;
	size_t newCapacity = dynArray->size;
	if (newCapacity != dynArray->capacity)
	{
		Deep_DynamicArr_Head* tmp = realloc(dynArray, sizeof(Deep_DynamicArr_Head) + dynArray->typeSize * newCapacity);
		if (!tmp)
		{
			free(dynArray);
			dynArray = NULL;
			return DEEP_DYNAMIC_ARR_ERROR_MALLOC;
		}
		_Deep_DynamicArr_Realloc(dynArray, tmp, newCapacity);
		*arr = dynArray->begin;
	}
	return DEEP_DYNAMIC_ARR_NOERROR;
}