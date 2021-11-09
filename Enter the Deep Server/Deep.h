#ifndef h_Deep
#define h_Deep

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
*        <function name>_<type1>_<seperator phrase>_<type2>_...
*    -> e.g Deep_DoSomething_int_To_float()
* 
* -> Type safe functions that operate on a "this" type are formatted:
*        <this type>_<type1>_<seperator phrase>_<type2>_..._<function name>
*    -> e.g Deep_DynArray_int_Push or Deep_Dictionary_int_To_float_Insert()
* 
* -> All containers that have type safety also expose the raw version of 
*    themselves where type safety is not present. These can be used to
*    reduce code size if you don't want to Decl several times.
* 
* -> Some headers will Decl some templated types. To avoid duplicate declarations,
*    Decl in headers are wrapped in an ifndef using their tag prefixed with the
*    Decl type:
*    
*	 #ifndef Deep_DynArray_Decl_longlong
*    #define Deep_DynArray_Decl_longlong
* 
*	 Deep_DynArray_Decl(long long, longlong)
* 
*    #endif
* 
*    -> It is advised that the user is to do the same when using Decl in headers.
* 
* ============== \ ================ / ==============
*/

#define Deep_Inline inline

#if (defined _WIN32 || defined _WIN64)
	#define Deep_ForceInline Deep_Inline
#elif (defined __APPLE__ || defined _APPLE)
	#define Deep_ForceInline __attribute__((always_inline))
#else
	#define Deep_ForceInline Deep_Inline
#endif

#if (defined _WIN32 || defined _WIN64)
	#define Deep_AlignOf(type) _Alignof(type)
#endif

/*
* Deep Macros
*/

//#define Deep_SizeOf_SizeT 4
#define Deep_SizeOf_SizeT 8

/*
* Deep Utility Functions
*/

void Deep_CheckMaxAllocationSize();

#endif