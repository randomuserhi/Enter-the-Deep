	.file	"Deep_DynArray.c"
 # GNU C11 (Rev1, Built by MSYS2 project) version 11.2.0 (x86_64-w64-mingw32)
 #	compiled by GNU C version 11.2.0, GMP version 6.2.1, MPFR version 4.1.0-p13, MPC version 1.2.1, isl version isl-0.24-GMP

 # GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
 # options passed: -mtune=generic -march=x86-64 -O3 -std=c11
	.text
	.p2align 4
	.globl	_Deep_DynArray_Create
	.def	_Deep_DynArray_Create;	.scl	2;	.type	32;	.endef
	.seh_proc	_Deep_DynArray_Create
_Deep_DynArray_Create:
	.seh_endprologue
 # Deep_DynArray.h:30: 	arr->size = 0;
	pxor	%xmm0, %xmm0	 # tmp84
 # Deep_DynArray.h:29: 	arr->data = DEEP_DYNARRAY_SIZE == 0 ? NULL : malloc(typeSize * DEEP_DYNARRAY_SIZE);
	movq	$0, 16(%rcx)	 #, arr_2(D)->data
 # Deep_DynArray.h:32: 	arr->typeSize = typeSize;
	movq	%rdx, 32(%rcx)	 # tmp86, arr_2(D)->typeSize
 # Deep_DynArray.h:33: 	arr->options.freeOnError = DEEP_DYNARRAY_FREE_ON_ERROR;
	movb	$1, 24(%rcx)	 #, arr_2(D)->options.freeOnError
 # Deep_DynArray.h:30: 	arr->size = 0;
	movups	%xmm0, (%rcx)	 # tmp84, MEM <vector(2) long long unsigned int> [(long long unsigned int *)arr_2(D)]
 # Deep_DynArray.h:34: }
	ret	
	.seh_endproc
	.p2align 4
	.globl	_Deep_DynArray_ErrorFree
	.def	_Deep_DynArray_ErrorFree;	.scl	2;	.type	32;	.endef
	.seh_proc	_Deep_DynArray_ErrorFree
_Deep_DynArray_ErrorFree:
	pushq	%rbx	 #
	.seh_pushreg	%rbx
	subq	$32, %rsp	 #,
	.seh_stackalloc	32
	.seh_endprologue
 # Deep_DynArray.h:38: 	if (arr->options.freeOnError)
	cmpb	$0, 24(%rcx)	 #, arr_5(D)->options.freeOnError
 # Deep_DynArray.h:37: {
	movq	%rcx, %rbx	 # tmp86, arr
 # Deep_DynArray.h:38: 	if (arr->options.freeOnError)
	jne	.L5	 #,
 # Deep_DynArray.h:43: }
	addq	$32, %rsp	 #,
	popq	%rbx	 #
	ret	
	.p2align 4,,10
	.p2align 3
.L5:
 # Deep_DynArray.h:40: 		free(arr->data);
	movq	16(%rcx), %rcx	 # arr_5(D)->data, arr_5(D)->data
	call	free	 #
 # Deep_DynArray.h:41: 		arr->data = NULL;
	movq	$0, 16(%rbx)	 #, arr_5(D)->data
 # Deep_DynArray.h:43: }
	addq	$32, %rsp	 #,
	popq	%rbx	 #
	ret	
	.seh_endproc
	.p2align 4
	.globl	_Deep_DynArray_Push
	.def	_Deep_DynArray_Push;	.scl	2;	.type	32;	.endef
	.seh_proc	_Deep_DynArray_Push
_Deep_DynArray_Push:
	pushq	%rsi	 #
	.seh_pushreg	%rsi
	pushq	%rbx	 #
	.seh_pushreg	%rbx
	subq	$56, %rsp	 #,
	.seh_stackalloc	56
	.seh_endprologue
 # Deep_DynArray.h:45: {
	movq	%rcx, %rbx	 # tmp122, arr
 # Deep_DynArray.h:46: 	if (arr->data)
	movq	16(%rcx), %rcx	 # arr_20(D)->data, _1
 # Deep_DynArray.h:52: 			void* tmp = realloc(arr->data, arr->typeSize * newCapacity);
	movq	32(%rbx), %r9	 # arr_20(D)->typeSize, pretmp_48
 # Deep_DynArray.h:46: 	if (arr->data)
	testq	%rcx, %rcx	 # _1
	je	.L7	 #,
 # Deep_DynArray.h:48: 		if (arr->size == arr->capacity)
	movq	(%rbx), %rax	 # arr_20(D)->size, _2
 # Deep_DynArray.h:48: 		if (arr->size == arr->capacity)
	movq	8(%rbx), %r8	 # arr_20(D)->capacity, _3
 # Deep_DynArray.h:48: 		if (arr->size == arr->capacity)
	cmpq	%r8, %rax	 # _3, _2
	jne	.L8	 #,
 # Deep_DynArray.h:50: 			size_t newCapacity = (size_t)(arr->capacity * DEEP_DYNARRAY_GROWTHRATE);
	testq	%r8, %r8	 # _3
	js	.L9	 #,
	pxor	%xmm0, %xmm0	 # tmp101
	cvtsi2ssq	%r8, %xmm0	 # _3, tmp101
.L10:
	mulss	.LC0(%rip), %xmm0	 #, tmp105
 # Deep_DynArray.h:50: 			size_t newCapacity = (size_t)(arr->capacity * DEEP_DYNARRAY_GROWTHRATE);
	comiss	.LC1(%rip), %xmm0	 #, tmp105
	jnb	.L11	 #,
	cvttss2siq	%xmm0, %rsi	 # tmp105, newCapacity
.L12:
 # Deep_DynArray.h:51: 			if (newCapacity == arr->capacity) ++newCapacity;
	xorl	%eax, %eax	 # tmp120
	cmpq	%rsi, %r8	 # newCapacity, _3
 # Deep_DynArray.h:52: 			void* tmp = realloc(arr->data, arr->typeSize * newCapacity);
	movq	%r9, %rdx	 # pretmp_48, pretmp_48
 # Deep_DynArray.h:51: 			if (newCapacity == arr->capacity) ++newCapacity;
	sete	%al	 #, tmp120
	addq	%rax, %rsi	 # tmp120, newCapacity
 # Deep_DynArray.h:52: 			void* tmp = realloc(arr->data, arr->typeSize * newCapacity);
	imulq	%rsi, %rdx	 # newCapacity, pretmp_48
	call	realloc	 #
 # Deep_DynArray.h:53: 			if (tmp)
	testq	%rax, %rax	 # <retval>
	je	.L14	 #,
 # Deep_DynArray.h:57: 				++arr->size;
	movq	(%rbx), %rdx	 # arr_20(D)->size, _8
 # Deep_DynArray.h:57: 				++arr->size;
	movq	%rsi, %xmm1	 # newCapacity, newCapacity
 # Deep_DynArray.h:55: 				arr->data = tmp;
	movq	%rax, 16(%rbx)	 # <retval>, arr_20(D)->data
 # Deep_DynArray.h:57: 				++arr->size;
	leaq	1(%rdx), %rcx	 #, tmp112
 # Deep_DynArray.h:58: 				return arr->data + arr->typeSize * (arr->size - 1);
	imulq	32(%rbx), %rdx	 # arr_20(D)->typeSize, tmp113
 # Deep_DynArray.h:57: 				++arr->size;
	movq	%rcx, %xmm0	 # tmp112, tmp112
	punpcklqdq	%xmm1, %xmm0	 # newCapacity, tmp111
	movups	%xmm0, (%rbx)	 # tmp111, MEM <vector(2) long long unsigned int> [(long long unsigned int *)arr_20(D)]
 # Deep_DynArray.h:58: 				return arr->data + arr->typeSize * (arr->size - 1);
	addq	%rdx, %rax	 # tmp113, <retval>
 # Deep_DynArray.h:84: }
	addq	$56, %rsp	 #,
	popq	%rbx	 #
	popq	%rsi	 #
	ret	
	.p2align 4,,10
	.p2align 3
.L8:
 # Deep_DynArray.h:68: 			++arr->size;
	leaq	1(%rax), %rdx	 #, tmp115
 # Deep_DynArray.h:69: 			return arr->data + arr->typeSize * (arr->size - 1);
	imulq	%r9, %rax	 # pretmp_48, tmp116
 # Deep_DynArray.h:68: 			++arr->size;
	movq	%rdx, (%rbx)	 # tmp115, arr_20(D)->size
 # Deep_DynArray.h:69: 			return arr->data + arr->typeSize * (arr->size - 1);
	addq	%rcx, %rax	 # _1, <retval>
.L6:
 # Deep_DynArray.h:84: }
	addq	$56, %rsp	 #,
	popq	%rbx	 #
	popq	%rsi	 #
	ret	
	.p2align 4,,10
	.p2align 3
.L11:
 # Deep_DynArray.h:50: 			size_t newCapacity = (size_t)(arr->capacity * DEEP_DYNARRAY_GROWTHRATE);
	subss	.LC1(%rip), %xmm0	 #, tmp107
	cvttss2siq	%xmm0, %rsi	 # tmp107, newCapacity
	btcq	$63, %rsi	 #, newCapacity
	jmp	.L12	 #
	.p2align 4,,10
	.p2align 3
.L7:
 # Deep_DynArray.h:74: 		void* tmp = malloc(DEEP_DYNARRAY_SIZE == 0 ? arr->typeSize : arr->typeSize * DEEP_DYNARRAY_SIZE);
	movq	%r9, %rcx	 # pretmp_48,
	call	malloc	 #
 # Deep_DynArray.h:75: 		if (tmp)
	testq	%rax, %rax	 # <retval>
	je	.L6	 #,
 # Deep_DynArray.h:78: 			arr->size = 1;
	movdqa	.LC2(%rip), %xmm0	 #, tmp118
 # Deep_DynArray.h:77: 			arr->data = tmp;
	movq	%rax, 16(%rbx)	 # <retval>, arr_20(D)->data
 # Deep_DynArray.h:78: 			arr->size = 1;
	movups	%xmm0, (%rbx)	 # tmp118, MEM <vector(2) long long unsigned int> [(long long unsigned int *)arr_20(D)]
 # Deep_DynArray.h:84: }
	addq	$56, %rsp	 #,
	popq	%rbx	 #
	popq	%rsi	 #
	ret	
	.p2align 4,,10
	.p2align 3
.L9:
 # Deep_DynArray.h:50: 			size_t newCapacity = (size_t)(arr->capacity * DEEP_DYNARRAY_GROWTHRATE);
	movq	%r8, %rax	 # _3, tmp103
	movq	%r8, %rdx	 # _3, tmp104
	pxor	%xmm0, %xmm0	 # tmp102
	shrq	%rax	 # tmp103
	andl	$1, %edx	 #, tmp104
	orq	%rdx, %rax	 # tmp104, tmp103
	cvtsi2ssq	%rax, %xmm0	 # tmp103, tmp102
	addss	%xmm0, %xmm0	 # tmp102, tmp101
	jmp	.L10	 #
.L14:
 # Deep_DynArray.h:38: 	if (arr->options.freeOnError)
	cmpb	$0, 24(%rbx)	 #, arr_20(D)->options.freeOnError
	je	.L6	 #,
 # Deep_DynArray.h:40: 		free(arr->data);
	movq	16(%rbx), %rcx	 # arr_20(D)->data, arr_20(D)->data
	movq	%rax, 40(%rsp)	 # <retval>, %sfp
	call	free	 #
 # Deep_DynArray.h:41: 		arr->data = NULL;
	movq	$0, 16(%rbx)	 #, arr_20(D)->data
	movq	40(%rsp), %rax	 # %sfp, <retval>
	jmp	.L6	 #
	.seh_endproc
	.p2align 4
	.globl	_Deep_DynArray_Free
	.def	_Deep_DynArray_Free;	.scl	2;	.type	32;	.endef
	.seh_proc	_Deep_DynArray_Free
_Deep_DynArray_Free:
	pushq	%rbx	 #
	.seh_pushreg	%rbx
	subq	$32, %rsp	 #,
	.seh_stackalloc	32
	.seh_endprologue
 # Deep_DynArray.c:6: {
	movq	%rcx, %rbx	 # tmp85, arr
 # Deep_DynArray.c:7: 	if (arr) 
	testq	%rcx, %rcx	 # arr
	je	.L19	 #,
 # Deep_DynArray.c:9: 		free(arr->data);
	movq	16(%rcx), %rcx	 # arr_3(D)->data, arr_3(D)->data
	call	free	 #
 # Deep_DynArray.c:10: 		arr->data = NULL;
	movq	$0, 16(%rbx)	 #, arr_3(D)->data
.L19:
 # Deep_DynArray.c:12: }
	addq	$32, %rsp	 #,
	popq	%rbx	 #
	ret	
	.seh_endproc
	.p2align 4
	.globl	_Deep_DynArray_Pop
	.def	_Deep_DynArray_Pop;	.scl	2;	.type	32;	.endef
	.seh_proc	_Deep_DynArray_Pop
_Deep_DynArray_Pop:
	.seh_endprologue
 # Deep_DynArray.c:20: 	if (arr->data)
	cmpq	$0, 16(%rcx)	 #, arr_6(D)->data
	je	.L24	 #,
 # Deep_DynArray.c:22: 		if (arr->size > 0)
	movq	(%rcx), %rax	 # arr_6(D)->size, _2
 # Deep_DynArray.c:22: 		if (arr->size > 0)
	testq	%rax, %rax	 # _2
	je	.L24	 #,
 # Deep_DynArray.c:24: 			--arr->size;
	subq	$1, %rax	 #, tmp86
	movq	%rax, (%rcx)	 # tmp86, arr_6(D)->size
.L24:
 # Deep_DynArray.c:27: }
	ret	
	.seh_endproc
	.p2align 4
	.globl	_Deep_DynArray_RemoveAt
	.def	_Deep_DynArray_RemoveAt;	.scl	2;	.type	32;	.endef
	.seh_proc	_Deep_DynArray_RemoveAt
_Deep_DynArray_RemoveAt:
	pushq	%rbx	 #
	.seh_pushreg	%rbx
	subq	$32, %rsp	 #,
	.seh_stackalloc	32
	.seh_endprologue
 # Deep_DynArray.c:30: {
	movq	%rcx, %rbx	 # tmp116, arr
 # Deep_DynArray.c:31: 	if (arr->data)
	movq	16(%rcx), %rcx	 # arr_16(D)->data, _1
 # Deep_DynArray.c:31: 	if (arr->data)
	testq	%rcx, %rcx	 # _1
	je	.L29	 #,
 # Deep_DynArray.c:33: 		if (arr->size > 1 && index > 0 && index < arr->size)
	testq	%rdx, %rdx	 # index
	movl	$1, %eax	 #, tmp118
 # Deep_DynArray.c:33: 		if (arr->size > 1 && index > 0 && index < arr->size)
	movq	(%rbx), %r9	 # arr_16(D)->size, _2
 # Deep_DynArray.c:33: 		if (arr->size > 1 && index > 0 && index < arr->size)
	cmovne	%rdx, %rax	 # index,, tmp100
	cmpq	%rax, %r9	 # tmp100, _2
	jbe	.L29	 #,
	testq	%rdx, %rdx	 # index
	jne	.L44	 #,
.L29:
 # Deep_DynArray.c:40: }
	addq	$32, %rsp	 #,
	popq	%rbx	 #
	ret	
	.p2align 4,,10
	.p2align 3
.L44:
 # Deep_DynArray.c:35: 			const size_t size = arr->size - 1 - index;
	movq	%r9, %r8	 # _2, tmp105
	subq	%rdx, %r8	 # index, tmp105
 # Deep_DynArray.c:36: 			if (size != 0) memmove(arr->data + index * arr->typeSize, arr->data + (index + 1) * arr->typeSize, size * arr->typeSize);
	subq	$1, %r8	 #, size
	jne	.L45	 #,
.L31:
 # Deep_DynArray.c:37: 			--arr->size;
	subq	$1, %r9	 #, tmp115
	movq	%r9, (%rbx)	 # tmp115, arr_16(D)->size
 # Deep_DynArray.c:40: }
	addq	$32, %rsp	 #,
	popq	%rbx	 #
	ret	
	.p2align 4,,10
	.p2align 3
.L45:
 # Deep_DynArray.c:36: 			if (size != 0) memmove(arr->data + index * arr->typeSize, arr->data + (index + 1) * arr->typeSize, size * arr->typeSize);
	movq	32(%rbx), %rax	 # arr_16(D)->typeSize, _4
 # Deep_DynArray.c:36: 			if (size != 0) memmove(arr->data + index * arr->typeSize, arr->data + (index + 1) * arr->typeSize, size * arr->typeSize);
	addq	$1, %rdx	 #, tmp106
 # Deep_DynArray.c:36: 			if (size != 0) memmove(arr->data + index * arr->typeSize, arr->data + (index + 1) * arr->typeSize, size * arr->typeSize);
	imulq	%rax, %rdx	 # _4, _7
 # Deep_DynArray.c:36: 			if (size != 0) memmove(arr->data + index * arr->typeSize, arr->data + (index + 1) * arr->typeSize, size * arr->typeSize);
	imulq	%rax, %r8	 # _4,
 # Deep_DynArray.c:36: 			if (size != 0) memmove(arr->data + index * arr->typeSize, arr->data + (index + 1) * arr->typeSize, size * arr->typeSize);
	leaq	(%rcx,%rdx), %r9	 #, tmp112
 # Deep_DynArray.c:36: 			if (size != 0) memmove(arr->data + index * arr->typeSize, arr->data + (index + 1) * arr->typeSize, size * arr->typeSize);
	subq	%rax, %rdx	 # _4, tmp113
 # Deep_DynArray.c:36: 			if (size != 0) memmove(arr->data + index * arr->typeSize, arr->data + (index + 1) * arr->typeSize, size * arr->typeSize);
	addq	%rdx, %rcx	 # tmp113, tmp114
 # Deep_DynArray.c:36: 			if (size != 0) memmove(arr->data + index * arr->typeSize, arr->data + (index + 1) * arr->typeSize, size * arr->typeSize);
	movq	%r9, %rdx	 # tmp112,
	call	memmove	 #
 # Deep_DynArray.c:37: 			--arr->size;
	movq	(%rbx), %r9	 # arr_16(D)->size, _2
	jmp	.L31	 #
	.seh_endproc
	.p2align 4
	.globl	_Deep_DynArray_Shrink
	.def	_Deep_DynArray_Shrink;	.scl	2;	.type	32;	.endef
	.seh_proc	_Deep_DynArray_Shrink
_Deep_DynArray_Shrink:
	pushq	%rsi	 #
	.seh_pushreg	%rsi
	pushq	%rbx	 #
	.seh_pushreg	%rbx
	subq	$40, %rsp	 #,
	.seh_stackalloc	40
	.seh_endprologue
 # Deep_DynArray.c:43: {
	movq	%rcx, %rbx	 # tmp93, arr
 # Deep_DynArray.c:44: 	if (arr->data)
	movq	16(%rcx), %rcx	 # arr_7(D)->data, _1
 # Deep_DynArray.c:44: 	if (arr->data)
	testq	%rcx, %rcx	 # _1
	je	.L46	 #,
 # Deep_DynArray.c:46: 		const size_t newCapacity = arr->size;
	movq	(%rbx), %rsi	 # arr_7(D)->size, newCapacity
 # Deep_DynArray.c:47: 		if (newCapacity != arr->capacity)
	cmpq	%rsi, 8(%rbx)	 # newCapacity, arr_7(D)->capacity
	je	.L46	 #,
 # Deep_DynArray.c:49: 			if (newCapacity != 0)
	testq	%rsi, %rsi	 # newCapacity
	je	.L50	 #,
 # Deep_DynArray.c:51: 				void* tmp = realloc(arr->data, arr->typeSize * newCapacity);
	movq	32(%rbx), %rdx	 # arr_7(D)->typeSize, tmp91
	imulq	%rsi, %rdx	 # newCapacity, tmp91
	call	realloc	 #
 # Deep_DynArray.c:52: 				if (tmp)
	testq	%rax, %rax	 # tmp
	je	.L51	 #,
 # Deep_DynArray.c:54: 					arr->data = tmp;
	movq	%rax, 16(%rbx)	 # tmp, arr_7(D)->data
 # Deep_DynArray.c:55: 					arr->capacity = newCapacity;
	movq	%rsi, 8(%rbx)	 # newCapacity, arr_7(D)->capacity
.L46:
 # Deep_DynArray.c:70: }
	addq	$40, %rsp	 #,
	popq	%rbx	 #
	popq	%rsi	 #
	ret	
	.p2align 4,,10
	.p2align 3
.L50:
 # Deep_DynArray.c:64: 				free(arr->data);
	call	free	 #
 # Deep_DynArray.c:65: 				arr->data = NULL;
	movq	$0, 16(%rbx)	 #, arr_7(D)->data
 # Deep_DynArray.c:66: 				arr->capacity = newCapacity;
	movq	$0, 8(%rbx)	 #, arr_7(D)->capacity
 # Deep_DynArray.c:70: }
	addq	$40, %rsp	 #,
	popq	%rbx	 #
	popq	%rsi	 #
	ret	
.L51:
 # Deep_DynArray.h:38: 	if (arr->options.freeOnError)
	cmpb	$0, 24(%rbx)	 #, arr_7(D)->options.freeOnError
	je	.L46	 #,
 # Deep_DynArray.h:40: 		free(arr->data);
	movq	16(%rbx), %rcx	 # arr_7(D)->data, arr_7(D)->data
	call	free	 #
 # Deep_DynArray.h:41: 		arr->data = NULL;
	movq	$0, 16(%rbx)	 #, arr_7(D)->data
	jmp	.L46	 #
	.seh_endproc
	.p2align 4
	.globl	_Deep_DynArray_Reserve
	.def	_Deep_DynArray_Reserve;	.scl	2;	.type	32;	.endef
	.seh_proc	_Deep_DynArray_Reserve
_Deep_DynArray_Reserve:
	pushq	%rbx	 #
	.seh_pushreg	%rbx
	subq	$48, %rsp	 #,
	.seh_stackalloc	48
	movaps	%xmm6, 32(%rsp)	 #,
	.seh_savexmm	%xmm6, 32
	.seh_endprologue
 # Deep_DynArray.c:74: 	const size_t newCapacity = arr->size + size;
	movq	(%rcx), %rax	 # arr_8(D)->size, newCapacity
	addq	%rdx, %rax	 # size, newCapacity
	movq	%rdx, %xmm6	 # size, tmp95
 # Deep_DynArray.c:73: {
	movq	%rcx, %rbx	 # tmp99, arr
	movq	%rax, %xmm0	 # newCapacity, newCapacity
	punpcklqdq	%xmm0, %xmm6	 # newCapacity, tmp95
 # Deep_DynArray.c:75: 	if (newCapacity > arr->capacity)
	cmpq	%rax, 8(%rcx)	 # newCapacity, arr_8(D)->capacity
	jb	.L56	 #,
 # Deep_DynArray.c:91: 		arr->size = size;
	movq	%rdx, (%rcx)	 # size, arr_8(D)->size
.L52:
 # Deep_DynArray.c:93: }
	movaps	32(%rsp), %xmm6	 #,
	addq	$48, %rsp	 #,
	popq	%rbx	 #
	ret	
	.p2align 4,,10
	.p2align 3
.L56:
 # Deep_DynArray.c:77: 		void* tmp = realloc(arr->data, arr->typeSize * newCapacity);
	imulq	32(%rcx), %rax	 # arr_8(D)->typeSize, newCapacity
	movq	16(%rcx), %rcx	 # arr_8(D)->data, arr_8(D)->data
	movq	%rax, %rdx	 # newCapacity, tmp96
	call	realloc	 #
 # Deep_DynArray.c:78: 		if (tmp)
	testq	%rax, %rax	 # tmp
	je	.L54	 #,
 # Deep_DynArray.c:82: 			arr->size = size;
	movups	%xmm6, (%rbx)	 # tmp95, MEM <vector(2) long long unsigned int> [(long long unsigned int *)arr_8(D)]
 # Deep_DynArray.c:93: }
	movaps	32(%rsp), %xmm6	 #,
 # Deep_DynArray.c:80: 			arr->data = tmp;
	movq	%rax, 16(%rbx)	 # tmp, arr_8(D)->data
 # Deep_DynArray.c:93: }
	addq	$48, %rsp	 #,
	popq	%rbx	 #
	ret	
.L54:
 # Deep_DynArray.h:38: 	if (arr->options.freeOnError)
	cmpb	$0, 24(%rbx)	 #, arr_8(D)->options.freeOnError
	je	.L52	 #,
 # Deep_DynArray.h:40: 		free(arr->data);
	movq	16(%rbx), %rcx	 # arr_8(D)->data, arr_8(D)->data
	call	free	 #
 # Deep_DynArray.h:41: 		arr->data = NULL;
	movq	$0, 16(%rbx)	 #, arr_8(D)->data
	jmp	.L52	 #
	.seh_endproc
	.section .rdata,"dr"
	.align 4
.LC0:
	.long	1069547520
	.align 4
.LC1:
	.long	1593835520
	.align 16
.LC2:
	.quad	1
	.quad	1
	.ident	"GCC: (Rev1, Built by MSYS2 project) 11.2.0"
	.def	free;	.scl	2;	.type	32;	.endef
	.def	realloc;	.scl	2;	.type	32;	.endef
	.def	malloc;	.scl	2;	.type	32;	.endef
	.def	memmove;	.scl	2;	.type	32;	.endef
