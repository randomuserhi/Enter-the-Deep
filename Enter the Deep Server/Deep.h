#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

//#define OLD_DEEP_DYNAMIC_IMPLEMENTATION

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