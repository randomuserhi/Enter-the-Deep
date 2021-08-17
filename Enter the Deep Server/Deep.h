#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/*
* ============== /  Library Format  \ ==============
* 
* -> All Deep library functions are prefixed by "Deep"
* 
* -> Utilities such as function specifiers (e.g inline) are 
*    prefixed by "Deep$" (e.g Deep$Inline)
* 
* -> Private library implementation functions / variables 
*    are prefixed by "$Deep"
* 
* ============== | Templated Format | ==============
* 
* -> Type safe functions are formatted using:
*        <function name>$<type1>_$<type2>_$...
*    -> e.g Deep_DoSomething$int_$float()
* 
* -> Type safe functions that operate on a "this" type are formatted:
*        <this type>$<type1>_$<type2>_$..._<function name>
*    -> e.g Deep_DynArray$int_Push or Deep_Dictionary$int_$float_Insert()
* 
* ============== \ ================ / ==============
*/

//#define OLD_DEEP_DYNAMIC_IMPLEMENTATION

#define Deep$Inline inline

#if (defined _WIN32 || defined _WIN64)
	#define Deep$Force_Inline Deep$Inline
#elif (defined __APPLE__ || defined _APPLE)
	#define Deep$Force_Inline __attribute__((always_inline))
#else
	#define Deep$Force_Inline Deep$Inline
#endif