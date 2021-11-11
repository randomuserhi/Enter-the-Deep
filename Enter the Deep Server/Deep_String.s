	.file	"Deep_String.c"
 # GNU C11 (Rev1, Built by MSYS2 project) version 11.2.0 (x86_64-w64-mingw32)
 #	compiled by GNU C version 11.2.0, GMP version 6.2.1, MPFR version 4.1.0-p13, MPC version 1.2.1, isl version isl-0.24-GMP

 # GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
 # options passed: -mtune=generic -march=x86-64 -O3 -std=c11
	.text
	.p2align 4
	.globl	Deep_String_Create
	.def	Deep_String_Create;	.scl	2;	.type	32;	.endef
	.seh_proc	Deep_String_Create
Deep_String_Create:
	pushq	%r12	 #
	.seh_pushreg	%r12
	pushq	%rsi	 #
	.seh_pushreg	%rsi
	pushq	%rbx	 #
	.seh_pushreg	%rbx
	subq	$32, %rsp	 #,
	.seh_stackalloc	32
	.seh_endprologue
 # Deep_DynArray.h:30: 	arr->size = 0;
	pxor	%xmm0, %xmm0	 # tmp88
 # Deep_DynArray.h:29: 	arr->data = DEEP_DYNARRAY_SIZE == 0 ? NULL : malloc(typeSize * DEEP_DYNARRAY_SIZE);
	movq	$0, 16(%rcx)	 #, MEM[(struct _Deep_DynArray *)string_3(D)].data
 # Deep_String.h:18: {
	movq	%rcx, %rbx	 # tmp98, string
	movq	%rdx, %r12	 # tmp99, str
 # Deep_DynArray.h:32: 	arr->typeSize = typeSize;
	movq	$1, 32(%rcx)	 #, MEM[(struct _Deep_DynArray *)string_3(D)].typeSize
 # Deep_DynArray.h:33: 	arr->options.freeOnError = DEEP_DYNARRAY_FREE_ON_ERROR;
	movb	$1, 24(%rcx)	 #, MEM[(struct _Deep_DynArray *)string_3(D)].options.freeOnError
 # Deep_DynArray.h:30: 	arr->size = 0;
	movups	%xmm0, (%rcx)	 # tmp88, MEM <vector(2) long long unsigned int> [(long long unsigned int *)string_3(D)]
 # Deep_String.h:20: 	size_t strLength = strlen(str) + 1;
	movq	%rdx, %rcx	 # str,
	call	strlen	 #
 # Deep_String.h:9: Deep_DynArray_Decl(char, char)
	movq	%rbx, %rcx	 # string,
 # Deep_String.h:20: 	size_t strLength = strlen(str) + 1;
	leaq	1(%rax), %rsi	 #, strLength
 # Deep_String.h:9: Deep_DynArray_Decl(char, char)
	movq	%rsi, %rdx	 # strLength,
	call	_Deep_DynArray_Reserve	 #
 # Deep_String.h:22: 	memcpy(string->str.values, str, strLength);
	movq	16(%rbx), %rcx	 # string_3(D)->str.D.4682.D.4681.values, string_3(D)->str.D.4682.D.4681.values
	movq	%rsi, %r8	 # strLength,
	movq	%r12, %rdx	 # str,
 # Deep_String.h:23: }
	addq	$32, %rsp	 #,
	popq	%rbx	 #
	popq	%rsi	 #
	popq	%r12	 #
 # Deep_String.h:22: 	memcpy(string->str.values, str, strLength);
	jmp	memcpy	 #
	.seh_endproc
	.ident	"GCC: (Rev1, Built by MSYS2 project) 11.2.0"
	.def	strlen;	.scl	2;	.type	32;	.endef
	.def	_Deep_DynArray_Reserve;	.scl	2;	.type	32;	.endef
	.def	memcpy;	.scl	2;	.type	32;	.endef
