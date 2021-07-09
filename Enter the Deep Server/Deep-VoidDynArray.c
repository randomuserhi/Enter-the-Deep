#include "Deep-VoidDynArray.h"

Deep_DynamicVoidArr* _Deep_DynamicVoidArr_Create(size_t typeSize)
{
	void* tmp = malloc(sizeof(_Deep_DynamicVoidArr) + typeSize * DEEP_DYNAMIC_VOID_ARR_SIZE);
	if (tmp == NULL) return NULL;

	_Deep_DynamicVoidArr* dynArr = tmp;
	dynArr->_begin = (Deep_DynamicVoidArr*)dynArr + sizeof(_Deep_DynamicVoidArr); //I'm unsure if this cast is safe (probably should check at somepoint)
	dynArr->_end = dynArr->_begin + typeSize * DEEP_DYNAMIC_VOID_ARR_SIZE;
	dynArr->_capacity = DEEP_DYNAMIC_VOID_ARR_SIZE;
	dynArr->_typeSize = typeSize;

	return dynArr->_begin;
}

void _Deep_DynamicVoidArr_Free(void* arr)
{
	free(arr);
}

size_t _Deep_DynamicVoidArr_Size(_Deep_DynamicVoidArr* arr)
{
	// https://godbolt.org/z/1TbcG3b93 and https://godbolt.org/z/WvG9b7jcb => Note generates different code

#ifdef DEEP_CODE_USE_SAFE_REINTERPRET
	_Deep_DynamicVoidArr dynArr;
	Deep__SafeReInterpret_Ptr(arr, dynArr);
	return (dynArr._end - dynArr._begin) / dynArr._typeSize;
#else
	return (arr->_end - arr->_begin) / arr->_typeSize;
#endif
}