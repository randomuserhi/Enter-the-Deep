#pragma once

#define DEEP_DYNAMIC_VOID_ARR_SIZE 3 //Default size for dynamic arrays (component storage)

#define DEEP_DYNAMIC_VOID_ARR_NOERROR 0
#define DEEP_DYNAMIC_VOID_ARR_NULL 1 //The component list storage is of type null (generated when size is unknown and thus storage is invalid)
#define DEEP_DYNAMIC_VOID_ARR_ERROR_MALLOC 2 //Malloc failed
#define DEEP_DYNAMIC_VOID_ARR_ERROR_ALIGNMENT 3 //sizeof(Type) was note equal to size of elements

struct Deep_DynamicVoidArr
{
	unsigned char* _data = nullptr; //Pointer to data
	unsigned char* _end = nullptr;
	size_t _typeSize = 0; //Size of type
	size_t _capacity = 0;
};