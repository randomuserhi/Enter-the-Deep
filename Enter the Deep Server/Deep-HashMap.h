#pragma once

#include "Deep.h"
#include "Deep-DynArray.h"

#define Deep_UnorderedMap(tag) struct Deep_UnorderedMap$##tag

#define Deep_UnorderedMap_Decl(keyType, valueType, tag) \
Deep_DynArray_Decl(valueType, $Deep_UnorderedMap_values$##tag##) \
Deep_UnorderedMap(tag) \
{ \
	Deep_DynArray($Deep_UnorderedMap_values$##tag##) values; \
};