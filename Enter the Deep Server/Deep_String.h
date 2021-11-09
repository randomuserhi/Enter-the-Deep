#ifndef h_Deep_String
#define h_Deep_String

#include "Deep.h"
#include "Deep_Containers.h"

#ifndef Deep_DynArray_Decl_char
#define Deep_DynArray_Decl_char
Deep_DynArray_Decl(char, char)
#endif

struct Deep_String
{
	struct Deep_DynArray(char) str;
};

Deep_Inline struct Deep_String Deep_String_Create(const char* str)
{
	struct Deep_String string;
	Deep_DynArray_Create(char)(&string.str);
	size_t strLength = strlen(str);
	Deep_DynArray_Reserve(char)(&string.str, strLength);
	memcpy(string.str.values, str, strLength);
	return string;
}

#endif
