#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/*

Code options

DEEP_CODE_USE_SAFE_REINTERPRET => Determines if code uses safe casts or not.
							   => This is to try and remedy Type punning, Strict Aliasing and Alignment issues with casting.
							   => Refer to: https://stackoverflow.com/questions/68308742/is-casting-to-and-from-char-pointer-well-defined-in-standard-c?noredirect=1#comment120726362_68308742
							   =>	        https://stackoverflow.com/questions/23848188/strict-aliasing-rule-and-char-pointers
							   => NOTE:: still unsure for how this works with Deep_VoidDynArray as it uses a header struct and casts with that plus additional wierd stuff storing data at the end
							   =>        of the struct.

*/

#define DEEP_CODE_USE_SAFE_REINTERPRET

/*

Utilities => Defined by '__' (double underscore)

*/

#define Deep__Inline static inline

/*

SafeReInterpret and SafeReWrite need a temp value to store it = > This should get optimized out by the compiler tho: https://godbolt.org/z/b9szcjM6j
They should be used in pairs, using SafeReInterpret to read and then write back using SafeReWrite
By default they do not take pointers, use the pointer version instead.

*/

#define Deep__SafeReInterpret(src, dest) memcpy(&dest, &src, sizeof dest)
#define Deep__SafeReWrite(dest, src) memcpy(&dest, &src, sizeof src)

#define Deep__SafeReInterpret_Ptr(src, dest) memcpy(&dest, src, sizeof dest)
#define Deep__SafeReWrite_Ptr(dest, src) memcpy(dest, &src, sizeof src)