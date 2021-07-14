#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/*

Error handling options

DEEP_ERRORHANDLING_VERBOSE => Verbose detailed errors are returned by functions. These functions require a result integer of which the error type will be stored in.
							  For example, Deep_DynamicVoidArr_Push requires _DEEP_DYNAMIC_VOID_ARR_RESULT to be defined.
							  Each subset of function uses their own result int, in the example give, all DynamicVoidArr use that variable name. This is for readability.

*/

#define DEEP_ERRORHANDLING_VERBOSE

/*

Code options

DEEP_CODE_USE_SAFE_REINTERPRET => Determines if code uses safe casts or not.
							   => This is to try and remedy Type punning, Strict Aliasing and Alignment issues with casting.
							   => Refer to: https://stackoverflow.com/questions/68308742/is-casting-to-and-from-char-pointer-well-defined-in-standard-c?noredirect=1#comment120726362_68308742
							   =>	        https://stackoverflow.com/questions/23848188/strict-aliasing-rule-and-char-pointers
							   => NOTE:: I'm fairly sure this is not safe from alignment issues as memcpy copies direct bytes,
							   =>        however the bytes of a struct to another struct may not align. A union is safe from this.
							   => It can also generate different code: https://godbolt.org/z/1TbcG3b93 and https://godbolt.org/z/WvG9b7jcb

*/

#define DEEP_CODE_USE_SAFE_REINTERPRET

/*

Utilities => Defined by '__' (double underscore)

*/

#define Deep__Inline static inline

#if (defined _WIN32 || defined _WIN64)
	#define Deep__Force_Inline Deep__Inline
#elif (defined __APPLE__ || defined _APPLE)
	#define Deep__Force_Inline static __attribute__((always_inline))
#else
	#define Deep__Force_Inline Deep__Inline
#endif

/*

SafeReInterpret and SafeReWrite need a temp value to store it = > This should get optimized out by the compiler tho: https://godbolt.org/z/b9szcjM6j
They should be used in pairs, using SafeReInterpret to read and then write back using SafeReWrite
By default they do not take pointers, use the pointer version instead.

*/

#define Deep__SafeReInterpret(src, dest) memcpy(&dest, &src, sizeof dest)
#define Deep__SafeReWrite(dest, src) memcpy(&dest, &src, sizeof src)

#define Deep__SafeReInterpret_Ptr(src, dest) memcpy(&dest, src, sizeof dest)
#define Deep__SafeReWrite_Ptr(dest, src) memcpy(dest, &src, sizeof src)