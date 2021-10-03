#include "Deep-HashMap.h"

void $Deep_UnorderedMap_Create($Deep_UnorderedMap* unorderedMap, size_t keyTypeSize, size_t valueTypeSize)
{
	unorderedMap->keyTypeSize = keyTypeSize;
	unorderedMap->valueTypeSize = valueTypeSize;
	Deep_DynArray_Create(raw)(&unorderedMap->values, valueTypeSize);
}

void* $Deep_UnorderedMap_Insert($Deep_UnorderedMap* unorderedMap)
{
	return NULL;
}
