#pragma once

#include "Deep.h"
#include "Deep-DynArray.h"

#define Deep_UnorderedMap(tag) struct Deep_UnorderedMap$##tag

/*
* 2 Methods of implementation 
*   -> (1) Use memcpy (should get optimzed out by compiler)
*   -> (2) Have insert return a void* or type* and the user writes their
*          value to the void* or type* themselves.
* 
*   -> Option (2) is used as it makes code more efficient with less indirection
*      via memcpy.
*/

#define Deep_UnorderedMap_Decl(keyType, valueType, tag) \
Deep_UnorderedMap(tag) \
{ \
	keyType tmpKey; \
	valueType tmpValue; \
	Deep_DynArray(raw) values; \
};