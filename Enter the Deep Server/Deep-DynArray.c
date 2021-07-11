#include "Deep-DynArray.h"

Deep_DynamicArr* _Deep_DynamicArr_Create(size_t typeSize)
{
	_Deep_DynamicArr* dynArr;
	void* tmp = malloc(sizeof *dynArr + typeSize * DEEP_DYNAMIC_ARR_SIZE);
	if (!tmp) return NULL;

	dynArr = tmp;
	dynArr->begin = (Deep_DynamicArr*)dynArr + sizeof *dynArr; //I'm unsure if this cast is safe (probably should check at somepoint)
	dynArr->end = dynArr->begin;
	dynArr->capacity = DEEP_DYNAMIC_ARR_SIZE;
	dynArr->typeSize = typeSize;

	return dynArr->begin;
}