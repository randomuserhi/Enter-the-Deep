	.file	"Deep_ECS.c"
 # GNU C11 (Rev1, Built by MSYS2 project) version 11.2.0 (x86_64-w64-mingw32)
 #	compiled by GNU C version 11.2.0, GMP version 6.2.1, MPFR version 4.1.0-p13, MPC version 1.2.1, isl version isl-0.24-GMP

 # GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
 # options passed: -mtune=generic -march=x86-64 -O3 -std=c11
	.text
	.p2align 4
	.def	printf;	.scl	3;	.type	32;	.endef
	.seh_proc	printf
printf:
	pushq	%r12	 #
	.seh_pushreg	%r12
	pushq	%rbx	 #
	.seh_pushreg	%rbx
	subq	$56, %rsp	 #,
	.seh_stackalloc	56
	.seh_endprologue
 # C:/msys64/mingw64/x86_64-w64-mingw32/include/stdio.h:371:   __builtin_va_list __local_argv; __builtin_va_start( __local_argv, __format );
	leaq	88(%rsp), %rbx	 #, tmp86
 # C:/msys64/mingw64/x86_64-w64-mingw32/include/stdio.h:369: {
	movq	%rdx, 88(%rsp)	 #,
	movq	%rcx, %r12	 # tmp89, __format
 # C:/msys64/mingw64/x86_64-w64-mingw32/include/stdio.h:372:   __retval = __mingw_vfprintf( stdout, __format, __local_argv );
	movl	$1, %ecx	 #,
 # C:/msys64/mingw64/x86_64-w64-mingw32/include/stdio.h:369: {
	movq	%r8, 96(%rsp)	 #,
	movq	%r9, 104(%rsp)	 #,
 # C:/msys64/mingw64/x86_64-w64-mingw32/include/stdio.h:371:   __builtin_va_list __local_argv; __builtin_va_start( __local_argv, __format );
	movq	%rbx, 40(%rsp)	 # tmp86, MEM[(char * *)&__local_argv]
 # C:/msys64/mingw64/x86_64-w64-mingw32/include/stdio.h:372:   __retval = __mingw_vfprintf( stdout, __format, __local_argv );
	call	*__imp___acrt_iob_func(%rip)	 #
	movq	%rbx, %r8	 # tmp86,
	movq	%r12, %rdx	 # __format,
	movq	%rax, %rcx	 # tmp90, _2
	call	__mingw_vfprintf	 #
 # C:/msys64/mingw64/x86_64-w64-mingw32/include/stdio.h:375: }
	addq	$56, %rsp	 #,
	popq	%rbx	 #
	popq	%r12	 #
	ret	
	.seh_endproc
	.section .rdata,"dr"
.LC0:
	.ascii "%c %s\0"
	.text
	.p2align 4
	.def	printf.constprop.0;	.scl	3;	.type	32;	.endef
	.seh_proc	printf.constprop.0
printf.constprop.0:
	pushq	%rbx	 #
	.seh_pushreg	%rbx
	subq	$48, %rsp	 #,
	.seh_stackalloc	48
	.seh_endprologue
 # C:/msys64/mingw64/x86_64-w64-mingw32/include/stdio.h:372:   __retval = __mingw_vfprintf( stdout, __format, __local_argv );
	movl	$1, %ecx	 #,
 # C:/msys64/mingw64/x86_64-w64-mingw32/include/stdio.h:371:   __builtin_va_list __local_argv; __builtin_va_start( __local_argv, __format );
	leaq	72(%rsp), %rbx	 #, tmp86
 # C:/msys64/mingw64/x86_64-w64-mingw32/include/stdio.h:368: int printf (const char *__format, ...)
	movq	%rdx, 72(%rsp)	 #,
	movq	%r8, 80(%rsp)	 #,
	movq	%r9, 88(%rsp)	 #,
 # C:/msys64/mingw64/x86_64-w64-mingw32/include/stdio.h:371:   __builtin_va_list __local_argv; __builtin_va_start( __local_argv, __format );
	movq	%rbx, 40(%rsp)	 # tmp86, MEM[(char * *)&__local_argv]
 # C:/msys64/mingw64/x86_64-w64-mingw32/include/stdio.h:372:   __retval = __mingw_vfprintf( stdout, __format, __local_argv );
	call	*__imp___acrt_iob_func(%rip)	 #
	movq	%rbx, %r8	 # tmp86,
	leaq	.LC0(%rip), %rdx	 #, tmp88
	movq	%rax, %rcx	 # tmp90, _2
	call	__mingw_vfprintf	 #
 # C:/msys64/mingw64/x86_64-w64-mingw32/include/stdio.h:375: }
	addq	$48, %rsp	 #,
	popq	%rbx	 #
	ret	
	.seh_endproc
	.p2align 4
	.globl	Deep_ECS_GetComponent
	.def	Deep_ECS_GetComponent;	.scl	2;	.type	32;	.endef
	.seh_proc	Deep_ECS_GetComponent
Deep_ECS_GetComponent:
	pushq	%r12	 #
	.seh_pushreg	%r12
	pushq	%rsi	 #
	.seh_pushreg	%rsi
	pushq	%rbx	 #
	.seh_pushreg	%rbx
	subq	$32, %rsp	 #,
	.seh_stackalloc	32
	.seh_endprologue
 # Deep_ECS.c:8: 	const struct Deep_ECS_Reference* reference = Deep_UnorderedMap_Insert(Deep_ECS_Handle, Deep_ECS_Reference)(&ECS->hierarchy, Deep_UnorderedMap_Hash(&handle, sizeof handle, DEEP_UNORDEREDMAP_SEED), &handle);
	leaq	72(%rsp), %rsi	 #, tmp100
 # Deep_ECS.c:7: {
	movq	%rdx, 72(%rsp)	 # handle, handle
	movq	%rcx, %r12	 # tmp111, ECS
	movq	%r8, %rbx	 # tmp112, componentHandle
 # Deep_ECS.c:8: 	const struct Deep_ECS_Reference* reference = Deep_UnorderedMap_Insert(Deep_ECS_Handle, Deep_ECS_Reference)(&ECS->hierarchy, Deep_UnorderedMap_Hash(&handle, sizeof handle, DEEP_UNORDEREDMAP_SEED), &handle);
	movl	$8, %edx	 #,
	movl	$3997467649, %r8d	 #,
	movq	%rsi, %rcx	 # tmp100,
	call	Deep_UnorderedMap_Hash	 #
 # Deep_ECS.h:48: Deep_UnorderedMap_Decl(Deep_ECS_Handle, struct Deep_ECS_Reference, Deep_ECS_Handle, Deep_ECS_Reference)
	movq	%r12, %rcx	 # ECS,
	movq	%rsi, %r8	 # tmp100,
 # Deep_ECS.c:8: 	const struct Deep_ECS_Reference* reference = Deep_UnorderedMap_Insert(Deep_ECS_Handle, Deep_ECS_Reference)(&ECS->hierarchy, Deep_UnorderedMap_Hash(&handle, sizeof handle, DEEP_UNORDEREDMAP_SEED), &handle);
	movq	%rax, %rdx	 # tmp113, _1
 # Deep_ECS.h:48: Deep_UnorderedMap_Decl(Deep_ECS_Handle, struct Deep_ECS_Reference, Deep_ECS_Handle, Deep_ECS_Reference)
	call	_Deep_UnorderedMap_Insert	 #
 # Deep_ECS.c:9: 	for (size_t i = 0; i < reference->archetype->type.size; i++)
	movq	(%rax), %r9	 # MEM[(const struct Deep_ECS_Reference *)_22].archetype, _2
 # Deep_ECS.c:9: 	for (size_t i = 0; i < reference->archetype->type.size; i++)
	movq	(%r9), %rcx	 # _2->type.D.4683.D.4682.size, _29
 # Deep_ECS.c:9: 	for (size_t i = 0; i < reference->archetype->type.size; i++)
	testq	%rcx, %rcx	 # _29
	je	.L8	 #,
 # Deep_ECS.c:11: 		Deep_ECS_Handle h = reference->archetype->type.values[i];
	movq	16(%r9), %r8	 # _2->type.D.4683.D.4682.values, _3
 # Deep_ECS.c:9: 	for (size_t i = 0; i < reference->archetype->type.size; i++)
	xorl	%edx, %edx	 # i
	jmp	.L7	 #
	.p2align 4,,10
	.p2align 3
.L6:
 # Deep_ECS.c:9: 	for (size_t i = 0; i < reference->archetype->type.size; i++)
	addq	$1, %rdx	 #, i
 # Deep_ECS.c:9: 	for (size_t i = 0; i < reference->archetype->type.size; i++)
	cmpq	%rcx, %rdx	 # _29, i
	je	.L8	 #,
.L7:
 # Deep_ECS.c:12: 		if (h == componentHandle)
	cmpq	%rbx, (%r8,%rdx,8)	 # componentHandle, MEM[(Deep_ECS_Handle *)_3 + i_28 * 8]
	jne	.L6	 #,
 # Deep_ECS.c:14: 			return Deep_DynArray_Get(raw)(&((struct Deep_DynArray(raw)*)reference->archetype->components.values)[i], reference->index);
	leaq	(%rdx,%rdx,4), %rcx	 #, tmp104
 # Deep_ECS.c:14: 			return Deep_DynArray_Get(raw)(&((struct Deep_DynArray(raw)*)reference->archetype->components.values)[i], reference->index);
	movq	96(%r9), %rdx	 # _2->components.D.4724.D.4723.values, _2->components.D.4724.D.4723.values
 # Deep_DynArray.h:188: 	return arr->values + arr->_arr.typeSize * index;
	movq	8(%rax), %rax	 # MEM[(const struct Deep_ECS_Reference *)_22].index, MEM[(const struct Deep_ECS_Reference *)_22].index
	imulq	32(%rdx,%rcx,8), %rax	 # _10->D.4547._arr.typeSize, tmp107
 # Deep_DynArray.h:188: 	return arr->values + arr->_arr.typeSize * index;
	addq	16(%rdx,%rcx,8), %rax	 # _10->D.4547.D.4546.values, <retval>
 # Deep_ECS.c:18: }
	addq	$32, %rsp	 #,
	popq	%rbx	 #
	popq	%rsi	 #
	popq	%r12	 #
	ret	
	.p2align 4,,10
	.p2align 3
.L8:
 # Deep_ECS.c:17: 	return NULL;
	xorl	%eax, %eax	 # <retval>
 # Deep_ECS.c:18: }
	addq	$32, %rsp	 #,
	popq	%rbx	 #
	popq	%rsi	 #
	popq	%r12	 #
	ret	
	.seh_endproc
	.section .rdata,"dr"
.LC1:
	.ascii "%s : \0"
.LC2:
	.ascii " ]\12\0"
	.section	.text.unlikely,"x"
.LCOLDB3:
	.text
.LHOTB3:
	.p2align 4
	.globl	Deep_ECS_PrintHierarchy
	.def	Deep_ECS_PrintHierarchy;	.scl	2;	.type	32;	.endef
	.seh_proc	Deep_ECS_PrintHierarchy
Deep_ECS_PrintHierarchy:
	pushq	%r15	 #
	.seh_pushreg	%r15
	pushq	%r14	 #
	.seh_pushreg	%r14
	pushq	%r13	 #
	.seh_pushreg	%r13
	pushq	%r12	 #
	.seh_pushreg	%r12
	pushq	%rbp	 #
	.seh_pushreg	%rbp
	pushq	%rdi	 #
	.seh_pushreg	%rdi
	pushq	%rsi	 #
	.seh_pushreg	%rsi
	pushq	%rbx	 #
	.seh_pushreg	%rbx
	subq	$56, %rsp	 #,
	.seh_stackalloc	56
	.seh_endprologue
 # Deep_ECS.c:22: 	for (const struct Deep_UnorderedMap_HashSlot* slot = ECS->hierarchy.start; slot != NULL; slot = slot->next)
	movq	8(%rcx), %rsi	 # ECS_18(D)->hierarchy.D.4813.D.4812.start, slot
 # Deep_ECS.c:21: {
	movq	%rcx, %rbp	 # tmp169, ECS
 # Deep_ECS.c:22: 	for (const struct Deep_UnorderedMap_HashSlot* slot = ECS->hierarchy.start; slot != NULL; slot = slot->next)
	testq	%rsi, %rsi	 # slot
	je	.L10	 #,
 # Deep_ECS.c:37: 			printf("%c %s", seperator, Id.name);
	leaq	.LC0(%rip), %r14	 #, tmp167
	jmp	.L21	 #
	.p2align 4,,10
	.p2align 3
.L12:
 # Deep_ECS.c:22: 	for (const struct Deep_UnorderedMap_HashSlot* slot = ECS->hierarchy.start; slot != NULL; slot = slot->next)
	movq	8(%rsi), %rsi	 # slot_7->next, slot
 # Deep_ECS.c:22: 	for (const struct Deep_UnorderedMap_HashSlot* slot = ECS->hierarchy.start; slot != NULL; slot = slot->next)
	testq	%rsi, %rsi	 # slot
	je	.L10	 #,
.L21:
 # Deep_ECS.c:24: 		Deep_ECS_Handle handle = *Deep_UnorderedMap_Key(Deep_ECS_Handle, Deep_ECS_Reference)(&ECS->hierarchy, slot);
	movq	80(%rbp), %rax	 # MEM[(const struct Deep_UnorderedMap_Deep_ECS_Handle_To_Deep_ECS_Reference *)ECS_18(D)].D.4813._unorderedMap.keyOffset, MEM[(const struct Deep_UnorderedMap_Deep_ECS_Handle_To_Deep_ECS_Reference *)ECS_18(D)].D.4813._unorderedMap.keyOffset
	movq	(%rsi,%rax), %rax	 # *_20, handle
 # Deep_ECS.c:25: 		if (handle == DEEP_ECS_NULL) continue;
	testq	%rax, %rax	 # handle
	je	.L12	 #,
 # Deep_ECS.c:8: 	const struct Deep_ECS_Reference* reference = Deep_UnorderedMap_Insert(Deep_ECS_Handle, Deep_ECS_Reference)(&ECS->hierarchy, Deep_UnorderedMap_Hash(&handle, sizeof handle, DEEP_UNORDEREDMAP_SEED), &handle);
	leaq	40(%rsp), %rbx	 #, tmp162
	movl	$3997467649, %r8d	 #,
	movl	$8, %edx	 #,
	movq	%rax, 40(%rsp)	 # handle, MEM[(long long unsigned int *)_97]
	movq	%rbx, %rcx	 # tmp162,
 # Deep_ECS.h:48: Deep_UnorderedMap_Decl(Deep_ECS_Handle, struct Deep_ECS_Reference, Deep_ECS_Handle, Deep_ECS_Reference)
	movq	88(%rbp), %r13	 # MEM[(const struct Deep_UnorderedMap_Deep_ECS_Handle_To_Deep_ECS_Reference *)ECS_18(D)].D.4813._unorderedMap.valueOffset, _31
 # Deep_ECS.c:8: 	const struct Deep_ECS_Reference* reference = Deep_UnorderedMap_Insert(Deep_ECS_Handle, Deep_ECS_Reference)(&ECS->hierarchy, Deep_UnorderedMap_Hash(&handle, sizeof handle, DEEP_UNORDEREDMAP_SEED), &handle);
	call	Deep_UnorderedMap_Hash	 #
 # Deep_ECS.h:48: Deep_UnorderedMap_Decl(Deep_ECS_Handle, struct Deep_ECS_Reference, Deep_ECS_Handle, Deep_ECS_Reference)
	movq	%rbp, %rcx	 # ECS,
	movq	%rbx, %r8	 # tmp162,
 # Deep_ECS.c:8: 	const struct Deep_ECS_Reference* reference = Deep_UnorderedMap_Insert(Deep_ECS_Handle, Deep_ECS_Reference)(&ECS->hierarchy, Deep_UnorderedMap_Hash(&handle, sizeof handle, DEEP_UNORDEREDMAP_SEED), &handle);
	movq	%rax, %rdx	 # tmp170, _34
 # Deep_ECS.h:48: Deep_UnorderedMap_Decl(Deep_ECS_Handle, struct Deep_ECS_Reference, Deep_ECS_Handle, Deep_ECS_Reference)
	call	_Deep_UnorderedMap_Insert	 #
 # Deep_ECS.c:9: 	for (size_t i = 0; i < reference->archetype->type.size; i++)
	movq	(%rax), %r9	 # MEM[(const struct Deep_ECS_Reference *)_36].archetype, _27
 # Deep_ECS.c:9: 	for (size_t i = 0; i < reference->archetype->type.size; i++)
	movq	(%r9), %rcx	 # _27->type.D.4683.D.4682.size, _89
 # Deep_ECS.c:9: 	for (size_t i = 0; i < reference->archetype->type.size; i++)
	testq	%rcx, %rcx	 # _89
	je	.L13	 #,
 # Deep_ECS.c:11: 		Deep_ECS_Handle h = reference->archetype->type.values[i];
	movq	16(%r9), %r8	 # _27->type.D.4683.D.4682.values, _38
 # Deep_ECS.c:9: 	for (size_t i = 0; i < reference->archetype->type.size; i++)
	xorl	%edx, %edx	 # i
	jmp	.L17	 #
	.p2align 4,,10
	.p2align 3
.L14:
 # Deep_ECS.c:9: 	for (size_t i = 0; i < reference->archetype->type.size; i++)
	addq	$1, %rdx	 #, i
 # Deep_ECS.c:9: 	for (size_t i = 0; i < reference->archetype->type.size; i++)
	cmpq	%rcx, %rdx	 # _89, i
	je	.L40	 #,
.L17:
 # Deep_ECS.c:12: 		if (h == componentHandle)
	cmpq	$512, (%r8,%rdx,8)	 #, MEM[(Deep_ECS_Handle *)_38 + i_99 * 8]
	jne	.L14	 #,
 # Deep_ECS.c:14: 			return Deep_DynArray_Get(raw)(&((struct Deep_DynArray(raw)*)reference->archetype->components.values)[i], reference->index);
	leaq	(%rdx,%rdx,4), %rcx	 #, tmp139
 # Deep_ECS.c:14: 			return Deep_DynArray_Get(raw)(&((struct Deep_DynArray(raw)*)reference->archetype->components.values)[i], reference->index);
	movq	96(%r9), %rdx	 # _27->components.D.4724.D.4723.values, _27->components.D.4724.D.4723.values
 # Deep_DynArray.h:188: 	return arr->values + arr->_arr.typeSize * index;
	movq	8(%rax), %rax	 # MEM[(const struct Deep_ECS_Reference *)_36].index, MEM[(const struct Deep_ECS_Reference *)_36].index
 # Deep_ECS.h:48: Deep_UnorderedMap_Decl(Deep_ECS_Handle, struct Deep_ECS_Reference, Deep_ECS_Handle, Deep_ECS_Reference)
	addq	%rsi, %r13	 # slot, _32
 # Deep_ECS.c:33: 		for (size_t i = 0; i < reference->archetype->type.size; i++)
	xorl	%r15d, %r15d	 # i
 # Deep_ECS.c:32: 		char seperator = '[';
	movl	$91, %edi	 #, seperator
 # Deep_ECS.c:8: 	const struct Deep_ECS_Reference* reference = Deep_UnorderedMap_Insert(Deep_ECS_Handle, Deep_ECS_Reference)(&ECS->hierarchy, Deep_UnorderedMap_Hash(&handle, sizeof handle, DEEP_UNORDEREDMAP_SEED), &handle);
	movl	$3997467649, %r12d	 #, tmp163
 # Deep_DynArray.h:188: 	return arr->values + arr->_arr.typeSize * index;
	imulq	32(%rdx,%rcx,8), %rax	 # _48->D.4547._arr.typeSize, tmp142
 # Deep_DynArray.h:188: 	return arr->values + arr->_arr.typeSize * index;
	addq	16(%rdx,%rcx,8), %rax	 # _48->D.4547.D.4546.values, _52
 # Deep_ECS.c:30: 		printf("%s : ", Id.name);
	leaq	.LC1(%rip), %rcx	 #,
	movq	(%rax), %rdx	 # MEM[(struct Deep_ECS_Id *)_52].name,
	call	printf	 #
 # Deep_ECS.c:33: 		for (size_t i = 0; i < reference->archetype->type.size; i++)
	movq	0(%r13), %rax	 # _32->archetype, _9
 # Deep_ECS.c:33: 		for (size_t i = 0; i < reference->archetype->type.size; i++)
	cmpq	$0, (%rax)	 #, _91->type.D.4683.D.4682.size
	je	.L16	 #,
	.p2align 4,,10
	.p2align 3
.L15:
 # Deep_ECS.c:35: 			Deep_ECS_Handle componentHandle = reference->archetype->type.values[i];
	movq	16(%rax), %rax	 # _88->type.D.4683.D.4682.values, _88->type.D.4683.D.4682.values
 # Deep_ECS.c:8: 	const struct Deep_ECS_Reference* reference = Deep_UnorderedMap_Insert(Deep_ECS_Handle, Deep_ECS_Reference)(&ECS->hierarchy, Deep_UnorderedMap_Hash(&handle, sizeof handle, DEEP_UNORDEREDMAP_SEED), &handle);
	movq	%r12, %r8	 # tmp163,
	movl	$8, %edx	 #,
	movq	%rbx, %rcx	 # tmp162,
 # Deep_ECS.c:35: 			Deep_ECS_Handle componentHandle = reference->archetype->type.values[i];
	movq	(%rax,%r15,8), %rax	 # *_6, componentHandle
	movq	%rax, 40(%rsp)	 # componentHandle, MEM[(long long unsigned int *)_97]
 # Deep_ECS.c:8: 	const struct Deep_ECS_Reference* reference = Deep_UnorderedMap_Insert(Deep_ECS_Handle, Deep_ECS_Reference)(&ECS->hierarchy, Deep_UnorderedMap_Hash(&handle, sizeof handle, DEEP_UNORDEREDMAP_SEED), &handle);
	call	Deep_UnorderedMap_Hash	 #
 # Deep_ECS.h:48: Deep_UnorderedMap_Decl(Deep_ECS_Handle, struct Deep_ECS_Reference, Deep_ECS_Handle, Deep_ECS_Reference)
	movq	%rbx, %r8	 # tmp162,
	movq	%rbp, %rcx	 # ECS,
 # Deep_ECS.c:8: 	const struct Deep_ECS_Reference* reference = Deep_UnorderedMap_Insert(Deep_ECS_Handle, Deep_ECS_Reference)(&ECS->hierarchy, Deep_UnorderedMap_Hash(&handle, sizeof handle, DEEP_UNORDEREDMAP_SEED), &handle);
	movq	%rax, %rdx	 # tmp172, _56
 # Deep_ECS.h:48: Deep_UnorderedMap_Decl(Deep_ECS_Handle, struct Deep_ECS_Reference, Deep_ECS_Handle, Deep_ECS_Reference)
	call	_Deep_UnorderedMap_Insert	 #
 # Deep_ECS.c:9: 	for (size_t i = 0; i < reference->archetype->type.size; i++)
	movq	(%rax), %r10	 # MEM[(const struct Deep_ECS_Reference *)_58].archetype, _92
 # Deep_ECS.h:48: Deep_UnorderedMap_Decl(Deep_ECS_Handle, struct Deep_ECS_Reference, Deep_ECS_Handle, Deep_ECS_Reference)
	movq	%rax, %r8	 # tmp173, _58
 # Deep_ECS.c:9: 	for (size_t i = 0; i < reference->archetype->type.size; i++)
	movq	(%r10), %rdx	 # _92->type.D.4683.D.4682.size, _66
 # Deep_ECS.c:9: 	for (size_t i = 0; i < reference->archetype->type.size; i++)
	testq	%rdx, %rdx	 # _66
	je	.L18	 #,
 # Deep_ECS.c:11: 		Deep_ECS_Handle h = reference->archetype->type.values[i];
	movq	16(%r10), %rcx	 # _92->type.D.4683.D.4682.values, _60
 # Deep_ECS.c:9: 	for (size_t i = 0; i < reference->archetype->type.size; i++)
	xorl	%eax, %eax	 # i
	jmp	.L20	 #
	.p2align 4,,10
	.p2align 3
.L19:
 # Deep_ECS.c:9: 	for (size_t i = 0; i < reference->archetype->type.size; i++)
	addq	$1, %rax	 #, i
 # Deep_ECS.c:9: 	for (size_t i = 0; i < reference->archetype->type.size; i++)
	cmpq	%rax, %rdx	 # i, _66
	je	.L41	 #,
.L20:
 # Deep_ECS.c:12: 		if (h == componentHandle)
	cmpq	$512, (%rcx,%rax,8)	 #, MEM[(Deep_ECS_Handle *)_60 + i_101 * 8]
	jne	.L19	 #,
 # Deep_ECS.c:14: 			return Deep_DynArray_Get(raw)(&((struct Deep_DynArray(raw)*)reference->archetype->components.values)[i], reference->index);
	movq	96(%r10), %rdx	 # _92->components.D.4724.D.4723.values, _92->components.D.4724.D.4723.values
 # Deep_ECS.c:14: 			return Deep_DynArray_Get(raw)(&((struct Deep_DynArray(raw)*)reference->archetype->components.values)[i], reference->index);
	leaq	(%rax,%rax,4), %rcx	 #, tmp151
 # Deep_DynArray.h:188: 	return arr->values + arr->_arr.typeSize * index;
	movq	8(%r8), %rax	 # MEM[(const struct Deep_ECS_Reference *)_58].index, MEM[(const struct Deep_ECS_Reference *)_58].index
 # Deep_ECS.c:33: 		for (size_t i = 0; i < reference->archetype->type.size; i++)
	addq	$1, %r15	 #, i
 # Deep_DynArray.h:188: 	return arr->values + arr->_arr.typeSize * index;
	imulq	32(%rdx,%rcx,8), %rax	 # _70->D.4547._arr.typeSize, tmp154
 # Deep_DynArray.h:188: 	return arr->values + arr->_arr.typeSize * index;
	addq	16(%rdx,%rcx,8), %rax	 # _70->D.4547.D.4546.values, _74
 # Deep_ECS.c:37: 			printf("%c %s", seperator, Id.name);
	movsbl	%dil, %edx	 # seperator, seperator
	movq	%r14, %rcx	 # tmp167,
	movq	(%rax), %r8	 # MEM[(struct Deep_ECS_Id *)_74].name,
 # Deep_ECS.c:38: 			seperator = ',';
	movl	$44, %edi	 #, seperator
 # Deep_ECS.c:37: 			printf("%c %s", seperator, Id.name);
	call	printf.constprop.0	 #
 # Deep_ECS.c:33: 		for (size_t i = 0; i < reference->archetype->type.size; i++)
	movq	0(%r13), %rax	 # _32->archetype, _9
 # Deep_ECS.c:33: 		for (size_t i = 0; i < reference->archetype->type.size; i++)
	cmpq	%r15, (%rax)	 # i, _9->type.D.4683.D.4682.size
	ja	.L15	 #,
.L16:
 # Deep_ECS.c:41: 		printf(" ]\n");
	leaq	.LC2(%rip), %rcx	 #, tmp159
	call	printf	 #
 # Deep_ECS.c:22: 	for (const struct Deep_UnorderedMap_HashSlot* slot = ECS->hierarchy.start; slot != NULL; slot = slot->next)
	movq	8(%rsi), %rsi	 # slot_7->next, slot
 # Deep_ECS.c:22: 	for (const struct Deep_UnorderedMap_HashSlot* slot = ECS->hierarchy.start; slot != NULL; slot = slot->next)
	testq	%rsi, %rsi	 # slot
	jne	.L21	 #,
.L10:
 # Deep_ECS.c:43: }
	addq	$56, %rsp	 #,
	popq	%rbx	 #
	popq	%rsi	 #
	popq	%rdi	 #
	popq	%rbp	 #
	popq	%r12	 #
	popq	%r13	 #
	popq	%r14	 #
	popq	%r15	 #
	ret	
.L41:
	jmp	.L18	 #
.L40:
	jmp	.L13	 #
	.seh_endproc
	.section	.text.unlikely,"x"
	.def	Deep_ECS_PrintHierarchy.cold;	.scl	3;	.type	32;	.endef
	.seh_proc	Deep_ECS_PrintHierarchy.cold
	.seh_stackalloc	120
	.seh_savereg	%rbx, 56
	.seh_savereg	%rsi, 64
	.seh_savereg	%rdi, 72
	.seh_savereg	%rbp, 80
	.seh_savereg	%r12, 88
	.seh_savereg	%r13, 96
	.seh_savereg	%r14, 104
	.seh_savereg	%r15, 112
	.seh_endprologue
Deep_ECS_PrintHierarchy.cold:
.L13:
 # Deep_ECS.c:29: 		struct Deep_ECS_Id Id = *(struct Deep_ECS_Id*)Deep_ECS_GetComponent(ECS, handle, DEEP_ECS_ID);
	movq	0, %rax	 # MEM[(struct Deep_ECS_Id *)0B].name, Id$name
	ud2	
.L18:
 # Deep_ECS.c:36: 			Id = *(struct Deep_ECS_Id*)Deep_ECS_GetComponent(ECS, componentHandle,  DEEP_ECS_ID);
	movq	0, %rax	 # MEM[(struct Deep_ECS_Id *)0B].name, Id$name
	ud2	
	.text
	.section	.text.unlikely,"x"
	.seh_endproc
.LCOLDE3:
	.text
.LHOTE3:
	.section .rdata,"dr"
.LC12:
	.ascii "ECS_COMPONENT\0"
.LC13:
	.ascii "ECS_ID\0"
	.section	.text.unlikely,"x"
.LCOLDB15:
	.text
.LHOTB15:
	.p2align 4
	.globl	Deep_ECS_Create
	.def	Deep_ECS_Create;	.scl	2;	.type	32;	.endef
	.seh_proc	Deep_ECS_Create
Deep_ECS_Create:
	pushq	%r13	 #
	.seh_pushreg	%r13
	pushq	%r12	 #
	.seh_pushreg	%r12
	pushq	%rbp	 #
	.seh_pushreg	%rbp
	pushq	%rdi	 #
	.seh_pushreg	%rdi
	pushq	%rsi	 #
	.seh_pushreg	%rsi
	pushq	%rbx	 #
	.seh_pushreg	%rbx
	subq	$104, %rsp	 #,
	.seh_stackalloc	104
	movaps	%xmm6, 48(%rsp)	 #,
	.seh_savexmm	%xmm6, 48
	movaps	%xmm7, 64(%rsp)	 #,
	.seh_savexmm	%xmm7, 64
	movaps	%xmm8, 80(%rsp)	 #,
	.seh_savexmm	%xmm8, 80
	.seh_endprologue
 # Deep_UnorderedMap.h:44: 	unorderedMap->keyCompareFunc = keyCompareFunc;
	movq	.refptr.Deep_UnorderedMap_ByteCompare(%rip), %rbx	 #, tmp167
 # Deep_UnorderedMap.h:57: 	unorderedMap->hashes = calloc(DEEP_UNORDEREDMAP_BUCKETSIZE, sizeof(*unorderedMap->hashes));
	movl	$8, %edx	 #,
 # Deep_UnorderedMap.h:45: 	unorderedMap->keyTypeSize = keyTypeSize;
	movdqa	.LC6(%rip), %xmm6	 #, tmp170
	movdqa	.LC7(%rip), %xmm7	 #, tmp171
	movdqa	.LC5(%rip), %xmm0	 #, tmp169
 # Deep_UnorderedMap.h:49: 	unorderedMap->bucketSize = DEEP_UNORDEREDMAP_BUCKETSIZE;
	movdqa	.LC4(%rip), %xmm8	 #, tmp168
 # Deep_UnorderedMap.h:44: 	unorderedMap->keyCompareFunc = keyCompareFunc;
	movq	%rbx, 40(%rcx)	 # tmp167, MEM[(struct _Deep_UnorderedMap *)ECS_12(D)].keyCompareFunc
 # Deep_ECS.c:46: {
	movq	%rcx, %r12	 # tmp300, ECS
 # Deep_ECS.c:52: 	Deep_UnorderedMap_Insert(Deep_ECS_Handle, Deep_ECS_Reference)(&ECS->hierarchy, Deep_UnorderedMap_Hash(&handle, sizeof handle, DEEP_UNORDEREDMAP_SEED), &handle);
	leaq	40(%rsp), %rsi	 #, tmp290
 # Deep_UnorderedMap.h:45: 	unorderedMap->keyTypeSize = keyTypeSize;
	movups	%xmm0, 48(%rcx)	 # tmp169, MEM <vector(2) long long unsigned int> [(long long unsigned int *)ECS_12(D) + 48B]
 # Deep_UnorderedMap.h:49: 	unorderedMap->bucketSize = DEEP_UNORDEREDMAP_BUCKETSIZE;
	movups	%xmm8, 24(%rcx)	 # tmp168, MEM <vector(2) long long unsigned int> [(long long unsigned int *)ECS_12(D) + 24B]
 # Deep_UnorderedMap.h:45: 	unorderedMap->keyTypeSize = keyTypeSize;
	movups	%xmm6, 64(%rcx)	 # tmp170, MEM <vector(2) long long unsigned int> [(long long unsigned int *)ECS_12(D) + 64B]
	movups	%xmm7, 80(%rcx)	 # tmp171, MEM <vector(2) long long unsigned int> [(long long unsigned int *)ECS_12(D) + 80B]
 # Deep_UnorderedMap.h:57: 	unorderedMap->hashes = calloc(DEEP_UNORDEREDMAP_BUCKETSIZE, sizeof(*unorderedMap->hashes));
	movl	$13, %ecx	 #,
	call	calloc	 #
	movl	$8, %edx	 #,
	movl	$13, %ecx	 #,
 # Deep_UnorderedMap.h:45: 	unorderedMap->keyTypeSize = keyTypeSize;
	movdqa	.LC8(%rip), %xmm0	 #, tmp175
 # Deep_UnorderedMap.h:44: 	unorderedMap->keyCompareFunc = keyCompareFunc;
	movq	%rbx, 136(%r12)	 # tmp167, MEM[(struct _Deep_UnorderedMap *)ECS_12(D) + 96B].keyCompareFunc
 # Deep_UnorderedMap.h:57: 	unorderedMap->hashes = calloc(DEEP_UNORDEREDMAP_BUCKETSIZE, sizeof(*unorderedMap->hashes));
	movq	%rax, (%r12)	 # tmp301, MEM[(struct _Deep_UnorderedMap *)ECS_12(D)].hashes
 # Deep_UnorderedMap.h:58: 	unorderedMap->start = NULL;
	movq	$0, 8(%r12)	 #, MEM[(struct _Deep_UnorderedMap *)ECS_12(D)].start
 # Deep_UnorderedMap.h:59: 	unorderedMap->end = NULL;
	movq	$0, 16(%r12)	 #, MEM[(struct _Deep_UnorderedMap *)ECS_12(D)].end
 # Deep_UnorderedMap.h:45: 	unorderedMap->keyTypeSize = keyTypeSize;
	movups	%xmm0, 144(%r12)	 # tmp175, MEM <vector(2) long long unsigned int> [(long long unsigned int *)ECS_12(D) + 144B]
 # Deep_UnorderedMap.h:49: 	unorderedMap->bucketSize = DEEP_UNORDEREDMAP_BUCKETSIZE;
	movups	%xmm8, 120(%r12)	 # tmp168, MEM <vector(2) long long unsigned int> [(long long unsigned int *)ECS_12(D) + 120B]
 # Deep_UnorderedMap.h:45: 	unorderedMap->keyTypeSize = keyTypeSize;
	movups	%xmm6, 160(%r12)	 # tmp170, MEM <vector(2) long long unsigned int> [(long long unsigned int *)ECS_12(D) + 160B]
	movups	%xmm7, 176(%r12)	 # tmp171, MEM <vector(2) long long unsigned int> [(long long unsigned int *)ECS_12(D) + 176B]
 # Deep_UnorderedMap.h:57: 	unorderedMap->hashes = calloc(DEEP_UNORDEREDMAP_BUCKETSIZE, sizeof(*unorderedMap->hashes));
	call	calloc	 #
	movl	$8, %edx	 #,
	movl	$13, %ecx	 #,
 # Deep_UnorderedMap.h:44: 	unorderedMap->keyCompareFunc = keyCompareFunc;
	movq	%rbx, 232(%r12)	 # tmp167, MEM[(struct _Deep_UnorderedMap *)ECS_12(D) + 192B].keyCompareFunc
 # Deep_UnorderedMap.h:57: 	unorderedMap->hashes = calloc(DEEP_UNORDEREDMAP_BUCKETSIZE, sizeof(*unorderedMap->hashes));
	movq	%rax, 96(%r12)	 # tmp302, MEM[(struct _Deep_UnorderedMap *)ECS_12(D) + 96B].hashes
 # Deep_UnorderedMap.h:58: 	unorderedMap->start = NULL;
	movq	$0, 104(%r12)	 #, MEM[(struct _Deep_UnorderedMap *)ECS_12(D) + 96B].start
 # Deep_UnorderedMap.h:59: 	unorderedMap->end = NULL;
	movq	$0, 112(%r12)	 #, MEM[(struct _Deep_UnorderedMap *)ECS_12(D) + 96B].end
 # Deep_UnorderedMap.h:49: 	unorderedMap->bucketSize = DEEP_UNORDEREDMAP_BUCKETSIZE;
	movups	%xmm8, 216(%r12)	 # tmp168, MEM <vector(2) long long unsigned int> [(long long unsigned int *)ECS_12(D) + 216B]
 # Deep_UnorderedMap.h:45: 	unorderedMap->keyTypeSize = keyTypeSize;
	movups	%xmm6, 240(%r12)	 # tmp170, MEM <vector(2) long long unsigned int> [(long long unsigned int *)ECS_12(D) + 240B]
	movups	%xmm6, 256(%r12)	 # tmp170, MEM <vector(2) long long unsigned int> [(long long unsigned int *)ECS_12(D) + 256B]
	movups	%xmm7, 272(%r12)	 # tmp171, MEM <vector(2) long long unsigned int> [(long long unsigned int *)ECS_12(D) + 272B]
 # Deep_UnorderedMap.h:57: 	unorderedMap->hashes = calloc(DEEP_UNORDEREDMAP_BUCKETSIZE, sizeof(*unorderedMap->hashes));
	call	calloc	 #
 # Deep_ECS.c:52: 	Deep_UnorderedMap_Insert(Deep_ECS_Handle, Deep_ECS_Reference)(&ECS->hierarchy, Deep_UnorderedMap_Hash(&handle, sizeof handle, DEEP_UNORDEREDMAP_SEED), &handle);
	movl	$3997467649, %r8d	 #,
	movl	$8, %edx	 #,
	movq	%rsi, %rcx	 # tmp290,
 # Deep_UnorderedMap.h:57: 	unorderedMap->hashes = calloc(DEEP_UNORDEREDMAP_BUCKETSIZE, sizeof(*unorderedMap->hashes));
	movq	%rax, 192(%r12)	 # tmp303, MEM[(struct _Deep_UnorderedMap *)ECS_12(D) + 192B].hashes
 # Deep_UnorderedMap.h:58: 	unorderedMap->start = NULL;
	movq	$0, 200(%r12)	 #, MEM[(struct _Deep_UnorderedMap *)ECS_12(D) + 192B].start
 # Deep_UnorderedMap.h:59: 	unorderedMap->end = NULL;
	movq	$0, 208(%r12)	 #, MEM[(struct _Deep_UnorderedMap *)ECS_12(D) + 192B].end
 # Deep_ECS.c:51: 	Deep_ECS_Handle handle = DEEP_ECS_NULL;
	movq	$0, 40(%rsp)	 #, handle
 # Deep_ECS.c:52: 	Deep_UnorderedMap_Insert(Deep_ECS_Handle, Deep_ECS_Reference)(&ECS->hierarchy, Deep_UnorderedMap_Hash(&handle, sizeof handle, DEEP_UNORDEREDMAP_SEED), &handle);
	call	Deep_UnorderedMap_Hash	 #
 # Deep_ECS.h:48: Deep_UnorderedMap_Decl(Deep_ECS_Handle, struct Deep_ECS_Reference, Deep_ECS_Handle, Deep_ECS_Reference)
	movq	%rsi, %r8	 # tmp290,
	movq	%r12, %rcx	 # ECS,
 # Deep_ECS.c:52: 	Deep_UnorderedMap_Insert(Deep_ECS_Handle, Deep_ECS_Reference)(&ECS->hierarchy, Deep_UnorderedMap_Hash(&handle, sizeof handle, DEEP_UNORDEREDMAP_SEED), &handle);
	movq	%rax, %rdx	 # tmp304, _1
 # Deep_ECS.h:48: Deep_UnorderedMap_Decl(Deep_ECS_Handle, struct Deep_ECS_Reference, Deep_ECS_Handle, Deep_ECS_Reference)
	call	_Deep_UnorderedMap_Insert	 #
 # Deep_ECS.c:54: 	struct Deep_ECS_Archetype* componentArchetype = malloc(sizeof * componentArchetype);
	movl	$216, %ecx	 #,
	call	malloc	 #
	movq	%rax, %rbx	 # tmp305, componentArchetype
 # Deep_ECS.c:55: 	if (!componentArchetype) return;
	testq	%rax, %rax	 # componentArchetype
	je	.L42	 #,
 # Deep_ECS.c:56: 	Deep_ECS_Archetype_Create(componentArchetype);
	movq	%rax, %rcx	 # componentArchetype,
	call	Deep_ECS_Archetype_Create	 #
 # Deep_DynArray.h:46: 	if (arr->data)
	movq	56(%rbx), %rcx	 # MEM[(struct _Deep_DynArray *)componentArchetype_17 + 40B].data, tmp
 # Deep_DynArray.h:46: 	if (arr->data)
	testq	%rcx, %rcx	 # tmp
	je	.L44	 #,
 # Deep_DynArray.h:48: 		if (arr->size == arr->capacity)
	movq	40(%rbx), %rdx	 # MEM[(struct _Deep_DynArray *)componentArchetype_17 + 40B].size, _147
 # Deep_DynArray.h:48: 		if (arr->size == arr->capacity)
	movq	48(%rbx), %rax	 # MEM[(struct _Deep_DynArray *)componentArchetype_17 + 40B].capacity, _148
 # Deep_DynArray.h:48: 		if (arr->size == arr->capacity)
	cmpq	%rax, %rdx	 # _148, _147
	je	.L108	 #,
 # Deep_DynArray.h:68: 			++arr->size;
	leaq	1(%rdx), %rax	 #, tmp202
	movq	%rax, 40(%rbx)	 # tmp202, MEM[(struct _Deep_DynArray *)componentArchetype_17 + 40B].size
 # Deep_DynArray.h:69: 			return arr->data + arr->typeSize * (arr->size - 1);
	leaq	(%rcx,%rdx,8), %rax	 #, tmp
.L52:
 # Deep_ECS.c:58: 	*Deep_DynArray_Push(Deep_ECS_Handle)(&componentArchetype->handles) = DEEP_ECS_COMPONENT;
	movq	$256, (%rax)	 #, MEM[(Deep_ECS_Handle *)_325]
 # Deep_DynArray.h:48: 		if (arr->size == arr->capacity)
	movq	40(%rbx), %rdx	 # MEM[(struct _Deep_DynArray *)componentArchetype_17 + 40B].size, _124
 # Deep_DynArray.h:48: 		if (arr->size == arr->capacity)
	movq	48(%rbx), %rax	 # MEM[(struct _Deep_DynArray *)componentArchetype_17 + 40B].capacity, _125
 # Deep_DynArray.h:48: 		if (arr->size == arr->capacity)
	cmpq	%rax, %rdx	 # _125, _124
	jne	.L109	 #,
 # Deep_DynArray.h:50: 			size_t newCapacity = (size_t)(arr->capacity * DEEP_DYNARRAY_GROWTHRATE);
	testq	%rax, %rax	 # _125
	js	.L55	 #,
	pxor	%xmm0, %xmm0	 # tmp206
	cvtsi2ssq	%rax, %xmm0	 # _125, tmp206
.L56:
	mulss	.LC9(%rip), %xmm0	 #, tmp210
 # Deep_DynArray.h:50: 			size_t newCapacity = (size_t)(arr->capacity * DEEP_DYNARRAY_GROWTHRATE);
	comiss	.LC10(%rip), %xmm0	 #, tmp210
	jnb	.L57	 #,
	cvttss2siq	%xmm0, %rdi	 # tmp210, newCapacity
.L58:
 # Deep_DynArray.h:51: 			if (newCapacity == arr->capacity) ++newCapacity;
	cmpq	%rdi, %rax	 # newCapacity, _125
	sete	%al	 #, tmp294
	movzbl	%al, %eax	 # tmp294, tmp294
	addq	%rax, %rdi	 # tmp294, newCapacity
 # Deep_DynArray.h:52: 			void* tmp = realloc(arr->data, arr->typeSize * newCapacity);
	leaq	0(,%rdi,8), %rdx	 #, tmp215
	call	realloc	 #
 # Deep_DynArray.h:53: 			if (tmp)
	testq	%rax, %rax	 # tmp
	je	.L60	 #,
 # Deep_DynArray.h:57: 				++arr->size;
	movq	40(%rbx), %rdx	 # MEM[(struct _Deep_DynArray *)componentArchetype_17 + 40B].size, _133
 # Deep_DynArray.h:57: 				++arr->size;
	movq	%rdi, %xmm2	 # newCapacity, newCapacity
 # Deep_DynArray.h:55: 				arr->data = tmp;
	movq	%rax, 56(%rbx)	 # tmp, MEM[(struct _Deep_DynArray *)componentArchetype_17 + 40B].data
 # Deep_DynArray.h:57: 				++arr->size;
	leaq	1(%rdx), %rcx	 #, tmp217
 # Deep_DynArray.h:58: 				return arr->data + arr->typeSize * (arr->size - 1);
	imulq	72(%rbx), %rdx	 # MEM[(struct _Deep_DynArray *)componentArchetype_17 + 40B].typeSize, tmp218
 # Deep_DynArray.h:57: 				++arr->size;
	movq	%rcx, %xmm0	 # tmp217, tmp217
	punpcklqdq	%xmm2, %xmm0	 # newCapacity, tmp216
	movups	%xmm0, 40(%rbx)	 # tmp216, MEM <vector(2) long long unsigned int> [(long long unsigned int *)componentArchetype_17 + 40B]
 # Deep_DynArray.h:58: 				return arr->data + arr->typeSize * (arr->size - 1);
	addq	%rdx, %rax	 # tmp218, _142
.L61:
 # Deep_ECS.c:59: 	*Deep_DynArray_Push(Deep_ECS_Handle)(&componentArchetype->handles) = DEEP_ECS_ID;
	movq	$512, (%rax)	 #, MEM[(Deep_ECS_Handle *)_144]
 # Deep_DynArray.h:74: 		void* tmp = malloc(DEEP_DYNARRAY_SIZE == 0 ? arr->typeSize : arr->typeSize * DEEP_DYNARRAY_SIZE);
	movl	$8, %ecx	 #,
	call	malloc	 #
	movq	%rax, %r13	 # tmp309, tmp222
 # Deep_DynArray.h:75: 		if (tmp)
	testq	%rax, %rax	 # tmp222
	je	.L110	 #,
 # Deep_ECS.c:65: 	*(struct Deep_ECS_Component*)Deep_DynArray_Push(raw)(&componentList) = component;
	movq	$0, (%rax)	 #, MEM[(struct Deep_ECS_Component *)tmp_120].size
 # Deep_DynArray.h:52: 			void* tmp = realloc(arr->data, arr->typeSize * newCapacity);
	movl	$16, %edx	 #,
	movq	%rax, %rcx	 # tmp222,
	call	realloc	 #
	movq	%rax, %rbp	 # tmp310, tmp
 # Deep_DynArray.h:53: 			if (tmp)
	testq	%rax, %rax	 # tmp
	je	.L64	 #,
 # Deep_ECS.c:66: 	*(struct Deep_ECS_Component*)Deep_DynArray_Push(raw)(&componentList) = component;
	movq	$0, 8(%rax)	 #, MEM[(struct Deep_ECS_Component *)tmp_111 + 8B].size
 # Deep_DynArray.h:74: 		void* tmp = malloc(DEEP_DYNARRAY_SIZE == 0 ? arr->typeSize : arr->typeSize * DEEP_DYNARRAY_SIZE);
	movl	$8, %ecx	 #,
	call	malloc	 #
	movq	%rax, %r13	 # tmp311, tmp224
 # Deep_DynArray.h:75: 		if (tmp)
	testq	%rax, %rax	 # tmp224
	je	.L111	 #,
 # Deep_ECS.c:72: 	*(struct Deep_ECS_Id*)Deep_DynArray_Push(raw)(&identityList) = identity;
	leaq	.LC12(%rip), %rax	 #, tmp331
 # Deep_DynArray.h:52: 			void* tmp = realloc(arr->data, arr->typeSize * newCapacity);
	movl	$16, %edx	 #,
	movq	%r13, %rcx	 # tmp224,
 # Deep_ECS.c:72: 	*(struct Deep_ECS_Id*)Deep_DynArray_Push(raw)(&identityList) = identity;
	movq	%rax, 0(%r13)	 # tmp331, MEM[(struct Deep_ECS_Id *)tmp_103].name
 # Deep_DynArray.h:52: 			void* tmp = realloc(arr->data, arr->typeSize * newCapacity);
	call	realloc	 #
	movq	%rax, %rdi	 # tmp312, tmp
 # Deep_DynArray.h:53: 			if (tmp)
	testq	%rax, %rax	 # tmp
	je	.L67	 #,
 # Deep_DynArray.h:46: 	if (arr->data)
	movq	96(%rbx), %rcx	 # MEM[(struct _Deep_DynArray *)componentArchetype_17 + 80B].data, _65
 # Deep_ECS.c:74: 	*(struct Deep_ECS_Id*)Deep_DynArray_Push(raw)(&identityList) = identity;
	leaq	.LC13(%rip), %rax	 #, tmp332
	movq	%rax, 8(%rdi)	 # tmp332, MEM[(struct Deep_ECS_Id *)tmp_93 + 8B].name
 # Deep_DynArray.h:46: 	if (arr->data)
	testq	%rcx, %rcx	 # _65
	je	.L112	 #,
 # Deep_DynArray.h:48: 		if (arr->size == arr->capacity)
	movq	80(%rbx), %rdx	 # MEM[(struct _Deep_DynArray *)componentArchetype_17 + 80B].size, _66
 # Deep_DynArray.h:48: 		if (arr->size == arr->capacity)
	movq	88(%rbx), %rax	 # MEM[(struct _Deep_DynArray *)componentArchetype_17 + 80B].capacity, _67
 # Deep_DynArray.h:48: 		if (arr->size == arr->capacity)
	cmpq	%rax, %rdx	 # _67, _66
	jne	.L70	 #,
 # Deep_DynArray.h:50: 			size_t newCapacity = (size_t)(arr->capacity * DEEP_DYNARRAY_GROWTHRATE);
	testq	%rax, %rax	 # _67
	js	.L71	 #,
	pxor	%xmm0, %xmm0	 # tmp232
	cvtsi2ssq	%rax, %xmm0	 # _67, tmp232
.L72:
	mulss	.LC9(%rip), %xmm0	 #, tmp236
 # Deep_DynArray.h:50: 			size_t newCapacity = (size_t)(arr->capacity * DEEP_DYNARRAY_GROWTHRATE);
	comiss	.LC10(%rip), %xmm0	 #, tmp236
	jnb	.L73	 #,
	cvttss2siq	%xmm0, %r13	 # tmp236, newCapacity
.L74:
 # Deep_DynArray.h:51: 			if (newCapacity == arr->capacity) ++newCapacity;
	cmpq	%r13, %rax	 # newCapacity, _67
	sete	%al	 #, tmp296
	movzbl	%al, %eax	 # tmp296, tmp296
	addq	%rax, %r13	 # tmp296, newCapacity
 # Deep_DynArray.h:52: 			void* tmp = realloc(arr->data, arr->typeSize * newCapacity);
	leaq	0(%r13,%r13,4), %rdx	 #, tmp243
	salq	$3, %rdx	 #, tmp244
	call	realloc	 #
 # Deep_DynArray.h:53: 			if (tmp)
	testq	%rax, %rax	 # tmp
	je	.L76	 #,
 # Deep_DynArray.h:57: 				++arr->size;
	movq	80(%rbx), %rdx	 # MEM[(struct _Deep_DynArray *)componentArchetype_17 + 80B].size, _75
 # Deep_DynArray.h:57: 				++arr->size;
	movq	%r13, %xmm3	 # newCapacity, newCapacity
 # Deep_DynArray.h:55: 				arr->data = tmp;
	movq	%rax, 96(%rbx)	 # tmp, MEM[(struct _Deep_DynArray *)componentArchetype_17 + 80B].data
 # Deep_DynArray.h:57: 				++arr->size;
	leaq	1(%rdx), %rcx	 #, tmp246
 # Deep_DynArray.h:58: 				return arr->data + arr->typeSize * (arr->size - 1);
	imulq	112(%rbx), %rdx	 # MEM[(struct _Deep_DynArray *)componentArchetype_17 + 80B].typeSize, tmp247
 # Deep_DynArray.h:57: 				++arr->size;
	movq	%rcx, %xmm0	 # tmp246, tmp246
	punpcklqdq	%xmm3, %xmm0	 # newCapacity, tmp245
	movups	%xmm0, 80(%rbx)	 # tmp245, MEM <vector(2) long long unsigned int> [(long long unsigned int *)componentArchetype_17 + 80B]
 # Deep_DynArray.h:58: 				return arr->data + arr->typeSize * (arr->size - 1);
	addq	%rdx, %rax	 # tmp247, tmp
.L77:
 # Deep_ECS.c:76: 	*Deep_DynArray_Push(Deep_DynArray_raw)(&componentArchetype->components) = componentList;
	movdqa	.LC14(%rip), %xmm6	 #, tmp291
	movq	%rbp, 16(%rax)	 # tmp, MEM <unsigned char *> [(struct Deep_DynArray_raw *)_86 + 16B]
	movb	$1, 24(%rax)	 #, MEM <char> [(struct Deep_DynArray_raw *)_86 + 24B]
	movq	$8, 32(%rax)	 #, MEM <size_t> [(struct Deep_DynArray_raw *)_86 + 32B]
	movups	%xmm6, (%rax)	 # tmp291, MEM <vector(2) long long unsigned int> [(struct Deep_DynArray_raw *)_86]
 # Deep_DynArray.h:46: 	if (arr->data)
	movq	96(%rbx), %rcx	 # MEM[(struct _Deep_DynArray *)componentArchetype_17 + 80B].data, _42
 # Deep_DynArray.h:46: 	if (arr->data)
	testq	%rcx, %rcx	 # _42
	je	.L80	 #,
 # Deep_DynArray.h:48: 		if (arr->size == arr->capacity)
	movq	80(%rbx), %rdx	 # MEM[(struct _Deep_DynArray *)componentArchetype_17 + 80B].size, _43
 # Deep_DynArray.h:48: 		if (arr->size == arr->capacity)
	movq	88(%rbx), %rax	 # MEM[(struct _Deep_DynArray *)componentArchetype_17 + 80B].capacity, _44
 # Deep_DynArray.h:48: 		if (arr->size == arr->capacity)
	cmpq	%rax, %rdx	 # _44, _43
	jne	.L81	 #,
 # Deep_DynArray.h:50: 			size_t newCapacity = (size_t)(arr->capacity * DEEP_DYNARRAY_GROWTHRATE);
	testq	%rax, %rax	 # _44
	js	.L82	 #,
	pxor	%xmm0, %xmm0	 # tmp257
	cvtsi2ssq	%rax, %xmm0	 # _44, tmp257
.L83:
	mulss	.LC9(%rip), %xmm0	 #, tmp261
 # Deep_DynArray.h:50: 			size_t newCapacity = (size_t)(arr->capacity * DEEP_DYNARRAY_GROWTHRATE);
	comiss	.LC10(%rip), %xmm0	 #, tmp261
	jnb	.L84	 #,
	cvttss2siq	%xmm0, %rbp	 # tmp261, newCapacity
.L85:
 # Deep_DynArray.h:51: 			if (newCapacity == arr->capacity) ++newCapacity;
	cmpq	%rbp, %rax	 # newCapacity, _44
	sete	%al	 #, tmp298
	movzbl	%al, %eax	 # tmp298, tmp298
	addq	%rax, %rbp	 # tmp298, newCapacity
 # Deep_DynArray.h:52: 			void* tmp = realloc(arr->data, arr->typeSize * newCapacity);
	leaq	0(%rbp,%rbp,4), %rdx	 #, tmp268
	salq	$3, %rdx	 #, tmp269
	call	realloc	 #
 # Deep_DynArray.h:53: 			if (tmp)
	testq	%rax, %rax	 # tmp
	je	.L87	 #,
 # Deep_DynArray.h:57: 				++arr->size;
	movq	80(%rbx), %rdx	 # MEM[(struct _Deep_DynArray *)componentArchetype_17 + 80B].size, _52
 # Deep_DynArray.h:57: 				++arr->size;
	movq	%rbp, %xmm4	 # newCapacity, newCapacity
 # Deep_DynArray.h:55: 				arr->data = tmp;
	movq	%rax, 96(%rbx)	 # tmp, MEM[(struct _Deep_DynArray *)componentArchetype_17 + 80B].data
 # Deep_DynArray.h:57: 				++arr->size;
	leaq	1(%rdx), %rcx	 #, tmp271
 # Deep_DynArray.h:58: 				return arr->data + arr->typeSize * (arr->size - 1);
	imulq	112(%rbx), %rdx	 # MEM[(struct _Deep_DynArray *)componentArchetype_17 + 80B].typeSize, tmp272
 # Deep_DynArray.h:57: 				++arr->size;
	movq	%rcx, %xmm0	 # tmp271, tmp271
	punpcklqdq	%xmm4, %xmm0	 # newCapacity, tmp270
	movups	%xmm0, 80(%rbx)	 # tmp270, MEM <vector(2) long long unsigned int> [(long long unsigned int *)componentArchetype_17 + 80B]
 # Deep_DynArray.h:58: 				return arr->data + arr->typeSize * (arr->size - 1);
	addq	%rdx, %rax	 # tmp272, tmp
.L88:
 # Deep_ECS.c:77: 	*Deep_DynArray_Push(Deep_DynArray_raw)(&componentArchetype->components) = identityList;
	movq	%rdi, 16(%rax)	 # tmp, MEM <unsigned char *> [(struct Deep_DynArray_raw *)_63 + 16B]
 # Deep_ECS.c:80: 	struct Deep_ECS_Reference* entityReference = Deep_UnorderedMap_Insert(Deep_ECS_Handle, Deep_ECS_Reference)(&ECS->hierarchy, Deep_UnorderedMap_Hash(&handle, sizeof handle, DEEP_UNORDEREDMAP_SEED), &handle);
	movl	$3997467649, %r8d	 #,
	movl	$8, %edx	 #,
	movq	%rsi, %rcx	 # tmp290,
 # Deep_ECS.c:77: 	*Deep_DynArray_Push(Deep_DynArray_raw)(&componentArchetype->components) = identityList;
	movb	$1, 24(%rax)	 #, MEM <char> [(struct Deep_DynArray_raw *)_63 + 24B]
	movq	$8, 32(%rax)	 #, MEM <size_t> [(struct Deep_DynArray_raw *)_63 + 32B]
	movups	%xmm6, (%rax)	 # tmp291, MEM <vector(2) long long unsigned int> [(struct Deep_DynArray_raw *)_63]
 # Deep_ECS.c:79: 	handle = DEEP_ECS_COMPONENT;
	movq	$256, 40(%rsp)	 #, handle
 # Deep_ECS.c:80: 	struct Deep_ECS_Reference* entityReference = Deep_UnorderedMap_Insert(Deep_ECS_Handle, Deep_ECS_Reference)(&ECS->hierarchy, Deep_UnorderedMap_Hash(&handle, sizeof handle, DEEP_UNORDEREDMAP_SEED), &handle);
	call	Deep_UnorderedMap_Hash	 #
 # Deep_ECS.h:48: Deep_UnorderedMap_Decl(Deep_ECS_Handle, struct Deep_ECS_Reference, Deep_ECS_Handle, Deep_ECS_Reference)
	movq	%rsi, %r8	 # tmp290,
	movq	%r12, %rcx	 # ECS,
 # Deep_ECS.c:80: 	struct Deep_ECS_Reference* entityReference = Deep_UnorderedMap_Insert(Deep_ECS_Handle, Deep_ECS_Reference)(&ECS->hierarchy, Deep_UnorderedMap_Hash(&handle, sizeof handle, DEEP_UNORDEREDMAP_SEED), &handle);
	movq	%rax, %rdx	 # tmp317, _7
 # Deep_ECS.h:48: Deep_UnorderedMap_Decl(Deep_ECS_Handle, struct Deep_ECS_Reference, Deep_ECS_Handle, Deep_ECS_Reference)
	call	_Deep_UnorderedMap_Insert	 #
 # Deep_ECS.c:85: 	entityReference = Deep_UnorderedMap_Insert(Deep_ECS_Handle, Deep_ECS_Reference)(&ECS->hierarchy, Deep_UnorderedMap_Hash(&handle, sizeof handle, DEEP_UNORDEREDMAP_SEED), &handle);
	movl	$3997467649, %r8d	 #,
	movl	$8, %edx	 #,
	movq	%rsi, %rcx	 # tmp290,
 # Deep_ECS.c:81: 	entityReference->archetype = componentArchetype;
	movq	%rbx, (%rax)	 # componentArchetype, _40->archetype
 # Deep_ECS.c:82: 	entityReference->index = 0;
	movq	$0, 8(%rax)	 #, _40->index
 # Deep_ECS.c:84: 	handle = DEEP_ECS_ID;
	movq	$512, 40(%rsp)	 #, handle
 # Deep_ECS.c:85: 	entityReference = Deep_UnorderedMap_Insert(Deep_ECS_Handle, Deep_ECS_Reference)(&ECS->hierarchy, Deep_UnorderedMap_Hash(&handle, sizeof handle, DEEP_UNORDEREDMAP_SEED), &handle);
	call	Deep_UnorderedMap_Hash	 #
 # Deep_ECS.h:48: Deep_UnorderedMap_Decl(Deep_ECS_Handle, struct Deep_ECS_Reference, Deep_ECS_Handle, Deep_ECS_Reference)
	movq	%rsi, %r8	 # tmp290,
	movq	%r12, %rcx	 # ECS,
 # Deep_ECS.c:85: 	entityReference = Deep_UnorderedMap_Insert(Deep_ECS_Handle, Deep_ECS_Reference)(&ECS->hierarchy, Deep_UnorderedMap_Hash(&handle, sizeof handle, DEEP_UNORDEREDMAP_SEED), &handle);
	movq	%rax, %rdx	 # tmp319, _9
 # Deep_ECS.h:48: Deep_UnorderedMap_Decl(Deep_ECS_Handle, struct Deep_ECS_Reference, Deep_ECS_Handle, Deep_ECS_Reference)
	call	_Deep_UnorderedMap_Insert	 #
 # Deep_ECS.c:86: 	entityReference->archetype = componentArchetype;
	movq	%rbx, (%rax)	 # componentArchetype, _39->archetype
 # Deep_ECS.c:87: 	entityReference->index = 1;
	movq	$1, 8(%rax)	 #, _39->index
.L42:
 # Deep_ECS.c:90: }
	movaps	48(%rsp), %xmm6	 #,
	movaps	64(%rsp), %xmm7	 #,
	movaps	80(%rsp), %xmm8	 #,
	addq	$104, %rsp	 #,
	popq	%rbx	 #
	popq	%rsi	 #
	popq	%rdi	 #
	popq	%rbp	 #
	popq	%r12	 #
	popq	%r13	 #
	ret	
	.p2align 4,,10
	.p2align 3
.L108:
 # Deep_DynArray.h:50: 			size_t newCapacity = (size_t)(arr->capacity * DEEP_DYNARRAY_GROWTHRATE);
	testq	%rax, %rax	 # _148
	js	.L46	 #,
	pxor	%xmm0, %xmm0	 # tmp188
	cvtsi2ssq	%rax, %xmm0	 # _148, tmp188
.L47:
	mulss	.LC9(%rip), %xmm0	 #, tmp192
 # Deep_DynArray.h:50: 			size_t newCapacity = (size_t)(arr->capacity * DEEP_DYNARRAY_GROWTHRATE);
	comiss	.LC10(%rip), %xmm0	 #, tmp192
	jnb	.L48	 #,
	cvttss2siq	%xmm0, %rdi	 # tmp192, newCapacity
.L49:
 # Deep_DynArray.h:51: 			if (newCapacity == arr->capacity) ++newCapacity;
	cmpq	%rdi, %rax	 # newCapacity, _148
	sete	%al	 #, tmp292
	movzbl	%al, %eax	 # tmp292, tmp292
	addq	%rax, %rdi	 # tmp292, newCapacity
 # Deep_DynArray.h:52: 			void* tmp = realloc(arr->data, arr->typeSize * newCapacity);
	leaq	0(,%rdi,8), %rdx	 #, tmp197
	call	realloc	 #
	movq	%rax, %rcx	 # tmp306, tmp
 # Deep_DynArray.h:53: 			if (tmp)
	testq	%rax, %rax	 # tmp
	je	.L51	 #,
 # Deep_DynArray.h:55: 				arr->data = tmp;
	movq	%rax, 56(%rbx)	 # tmp, MEM[(struct _Deep_DynArray *)componentArchetype_17 + 40B].data
 # Deep_DynArray.h:57: 				++arr->size;
	movq	40(%rbx), %rax	 # MEM[(struct _Deep_DynArray *)componentArchetype_17 + 40B].size, _156
 # Deep_DynArray.h:57: 				++arr->size;
	movq	%rdi, %xmm1	 # newCapacity, newCapacity
	leaq	1(%rax), %rdx	 #, tmp199
 # Deep_DynArray.h:58: 				return arr->data + arr->typeSize * (arr->size - 1);
	imulq	72(%rbx), %rax	 # MEM[(struct _Deep_DynArray *)componentArchetype_17 + 40B].typeSize, tmp200
 # Deep_DynArray.h:57: 				++arr->size;
	movq	%rdx, %xmm0	 # tmp199, tmp199
	punpcklqdq	%xmm1, %xmm0	 # newCapacity, tmp198
	movups	%xmm0, 40(%rbx)	 # tmp198, MEM <vector(2) long long unsigned int> [(long long unsigned int *)componentArchetype_17 + 40B]
 # Deep_DynArray.h:58: 				return arr->data + arr->typeSize * (arr->size - 1);
	addq	%rcx, %rax	 # tmp, tmp
	jmp	.L52	 #
	.p2align 4,,10
	.p2align 3
.L81:
 # Deep_DynArray.h:68: 			++arr->size;
	leaq	1(%rdx), %rax	 #, tmp274
	movq	%rax, 80(%rbx)	 # tmp274, MEM[(struct _Deep_DynArray *)componentArchetype_17 + 80B].size
 # Deep_DynArray.h:69: 			return arr->data + arr->typeSize * (arr->size - 1);
	leaq	(%rdx,%rdx,4), %rax	 #, tmp277
 # Deep_DynArray.h:69: 			return arr->data + arr->typeSize * (arr->size - 1);
	leaq	(%rcx,%rax,8), %rax	 #, tmp
	jmp	.L88	 #
	.p2align 4,,10
	.p2align 3
.L70:
 # Deep_DynArray.h:68: 			++arr->size;
	leaq	1(%rdx), %rax	 #, tmp249
	movq	%rax, 80(%rbx)	 # tmp249, MEM[(struct _Deep_DynArray *)componentArchetype_17 + 80B].size
 # Deep_DynArray.h:69: 			return arr->data + arr->typeSize * (arr->size - 1);
	leaq	(%rdx,%rdx,4), %rax	 #, tmp252
 # Deep_DynArray.h:69: 			return arr->data + arr->typeSize * (arr->size - 1);
	leaq	(%rcx,%rax,8), %rax	 #, tmp
	jmp	.L77	 #
	.p2align 4,,10
	.p2align 3
.L109:
 # Deep_DynArray.h:68: 			++arr->size;
	leaq	1(%rdx), %rax	 #, tmp220
	movq	%rax, 40(%rbx)	 # tmp220, MEM[(struct _Deep_DynArray *)componentArchetype_17 + 40B].size
 # Deep_DynArray.h:69: 			return arr->data + arr->typeSize * (arr->size - 1);
	leaq	(%rcx,%rdx,8), %rax	 #, _142
	jmp	.L61	 #
	.p2align 4,,10
	.p2align 3
.L57:
 # Deep_DynArray.h:50: 			size_t newCapacity = (size_t)(arr->capacity * DEEP_DYNARRAY_GROWTHRATE);
	subss	.LC10(%rip), %xmm0	 #, tmp212
	cvttss2siq	%xmm0, %rdi	 # tmp212, newCapacity
	btcq	$63, %rdi	 #, newCapacity
	jmp	.L58	 #
	.p2align 4,,10
	.p2align 3
.L84:
	subss	.LC10(%rip), %xmm0	 #, tmp263
	cvttss2siq	%xmm0, %rbp	 # tmp263, newCapacity
	btcq	$63, %rbp	 #, newCapacity
	jmp	.L85	 #
	.p2align 4,,10
	.p2align 3
.L48:
	subss	.LC10(%rip), %xmm0	 #, tmp194
	cvttss2siq	%xmm0, %rdi	 # tmp194, newCapacity
	btcq	$63, %rdi	 #, newCapacity
	jmp	.L49	 #
	.p2align 4,,10
	.p2align 3
.L73:
	subss	.LC10(%rip), %xmm0	 #, tmp238
	cvttss2siq	%xmm0, %r13	 # tmp238, newCapacity
	btcq	$63, %r13	 #, newCapacity
	jmp	.L74	 #
.L110:
 # Deep_ECS.c:65: 	*(struct Deep_ECS_Component*)Deep_DynArray_Push(raw)(&componentList) = component;
	movq	$0, 0	 #, MEM[(struct Deep_ECS_Component *)0B].size
	ud2	
	.p2align 4,,10
	.p2align 3
.L44:
 # Deep_DynArray.h:74: 		void* tmp = malloc(DEEP_DYNARRAY_SIZE == 0 ? arr->typeSize : arr->typeSize * DEEP_DYNARRAY_SIZE);
	movl	$8, %ecx	 #,
	call	malloc	 #
 # Deep_DynArray.h:75: 		if (tmp)
	testq	%rax, %rax	 # tmp
	je	.L90	 #,
 # Deep_DynArray.h:78: 			arr->size = 1;
	movdqa	.LC11(%rip), %xmm0	 #, tmp205
 # Deep_DynArray.h:77: 			arr->data = tmp;
	movq	%rax, 56(%rbx)	 # tmp, MEM[(struct _Deep_DynArray *)componentArchetype_17 + 40B].data
 # Deep_DynArray.h:80: 			return arr->data;
	movq	%rax, %rcx	 # tmp, tmp
 # Deep_DynArray.h:78: 			arr->size = 1;
	movups	%xmm0, 40(%rbx)	 # tmp205, MEM <vector(2) long long unsigned int> [(long long unsigned int *)componentArchetype_17 + 40B]
 # Deep_DynArray.h:80: 			return arr->data;
	jmp	.L52	 #
	.p2align 4,,10
	.p2align 3
.L80:
 # Deep_DynArray.h:74: 		void* tmp = malloc(DEEP_DYNARRAY_SIZE == 0 ? arr->typeSize : arr->typeSize * DEEP_DYNARRAY_SIZE);
	movl	$40, %ecx	 #,
	call	malloc	 #
 # Deep_DynArray.h:75: 		if (tmp)
	testq	%rax, %rax	 # tmp
	je	.L90	 #,
 # Deep_DynArray.h:78: 			arr->size = 1;
	movdqa	.LC11(%rip), %xmm0	 #, tmp280
 # Deep_DynArray.h:77: 			arr->data = tmp;
	movq	%rax, 96(%rbx)	 # tmp, MEM[(struct _Deep_DynArray *)componentArchetype_17 + 80B].data
 # Deep_DynArray.h:78: 			arr->size = 1;
	movups	%xmm0, 80(%rbx)	 # tmp280, MEM <vector(2) long long unsigned int> [(long long unsigned int *)componentArchetype_17 + 80B]
 # Deep_DynArray.h:80: 			return arr->data;
	jmp	.L88	 #
	.p2align 4,,10
	.p2align 3
.L112:
 # Deep_DynArray.h:74: 		void* tmp = malloc(DEEP_DYNARRAY_SIZE == 0 ? arr->typeSize : arr->typeSize * DEEP_DYNARRAY_SIZE);
	movl	$40, %ecx	 #,
	call	malloc	 #
 # Deep_DynArray.h:75: 		if (tmp)
	testq	%rax, %rax	 # tmp
	je	.L90	 #,
 # Deep_DynArray.h:78: 			arr->size = 1;
	movdqa	.LC11(%rip), %xmm0	 #, tmp255
 # Deep_DynArray.h:77: 			arr->data = tmp;
	movq	%rax, 96(%rbx)	 # tmp, MEM[(struct _Deep_DynArray *)componentArchetype_17 + 80B].data
 # Deep_DynArray.h:78: 			arr->size = 1;
	movups	%xmm0, 80(%rbx)	 # tmp255, MEM <vector(2) long long unsigned int> [(long long unsigned int *)componentArchetype_17 + 80B]
 # Deep_DynArray.h:80: 			return arr->data;
	jmp	.L77	 #
.L111:
 # Deep_ECS.c:72: 	*(struct Deep_ECS_Id*)Deep_DynArray_Push(raw)(&identityList) = identity;
	leaq	.LC12(%rip), %rax	 #, tmp330
	movq	%rax, 0	 # tmp330, MEM[(struct Deep_ECS_Id *)0B].name
	ud2	
	.p2align 4,,10
	.p2align 3
.L55:
 # Deep_DynArray.h:50: 			size_t newCapacity = (size_t)(arr->capacity * DEEP_DYNARRAY_GROWTHRATE);
	movq	%rax, %rdx	 # _125, tmp208
	movq	%rax, %r8	 # _125, tmp209
	pxor	%xmm0, %xmm0	 # tmp207
	shrq	%rdx	 # tmp208
	andl	$1, %r8d	 #, tmp209
	orq	%r8, %rdx	 # tmp209, tmp208
	cvtsi2ssq	%rdx, %xmm0	 # tmp208, tmp207
	addss	%xmm0, %xmm0	 # tmp207, tmp206
	jmp	.L56	 #
	.p2align 4,,10
	.p2align 3
.L46:
	movq	%rax, %rdx	 # _148, tmp190
	movq	%rax, %r8	 # _148, tmp191
	pxor	%xmm0, %xmm0	 # tmp189
	shrq	%rdx	 # tmp190
	andl	$1, %r8d	 #, tmp191
	orq	%r8, %rdx	 # tmp191, tmp190
	cvtsi2ssq	%rdx, %xmm0	 # tmp190, tmp189
	addss	%xmm0, %xmm0	 # tmp189, tmp188
	jmp	.L47	 #
	.p2align 4,,10
	.p2align 3
.L82:
	movq	%rax, %rdx	 # _44, tmp259
	movq	%rax, %r8	 # _44, tmp260
	pxor	%xmm0, %xmm0	 # tmp258
	shrq	%rdx	 # tmp259
	andl	$1, %r8d	 #, tmp260
	orq	%r8, %rdx	 # tmp260, tmp259
	cvtsi2ssq	%rdx, %xmm0	 # tmp259, tmp258
	addss	%xmm0, %xmm0	 # tmp258, tmp257
	jmp	.L83	 #
	.p2align 4,,10
	.p2align 3
.L71:
	movq	%rax, %rdx	 # _67, tmp234
	movq	%rax, %r8	 # _67, tmp235
	pxor	%xmm0, %xmm0	 # tmp233
	shrq	%rdx	 # tmp234
	andl	$1, %r8d	 #, tmp235
	orq	%r8, %rdx	 # tmp235, tmp234
	cvtsi2ssq	%rdx, %xmm0	 # tmp234, tmp233
	addss	%xmm0, %xmm0	 # tmp233, tmp232
	jmp	.L72	 #
	.seh_endproc
	.section	.text.unlikely,"x"
	.def	Deep_ECS_Create.cold;	.scl	3;	.type	32;	.endef
	.seh_proc	Deep_ECS_Create.cold
	.seh_stackalloc	152
	.seh_savereg	%rbx, 104
	.seh_savereg	%rsi, 112
	.seh_savereg	%rdi, 120
	.seh_savereg	%rbp, 128
	.seh_savexmm	%xmm6, 48
	.seh_savexmm	%xmm7, 64
	.seh_savereg	%r12, 136
	.seh_savereg	%r13, 144
	.seh_savexmm	%xmm8, 80
	.seh_endprologue
Deep_ECS_Create.cold:
.L87:
 # Deep_DynArray.h:38: 	if (arr->options.freeOnError)
	cmpb	$0, 104(%rbx)	 #, MEM[(struct _Deep_DynArray *)componentArchetype_17 + 80B].options.freeOnError
	je	.L90	 #,
 # Deep_DynArray.h:40: 		free(arr->data);
	movq	96(%rbx), %rcx	 # MEM[(struct _Deep_DynArray *)componentArchetype_17 + 80B].data, MEM[(struct _Deep_DynArray *)componentArchetype_17 + 80B].data
	call	free	 #
 # Deep_DynArray.h:41: 		arr->data = NULL;
	movq	$0, 96(%rbx)	 #, MEM[(struct _Deep_DynArray *)componentArchetype_17 + 80B].data
.L90:
 # Deep_ECS.c:77: 	*Deep_DynArray_Push(Deep_DynArray_raw)(&componentArchetype->components) = identityList;
	movq	$0, 0	 #,
	ud2	
.L64:
 # Deep_DynArray.h:40: 		free(arr->data);
	movq	%r13, %rcx	 # tmp222,
	call	free	 #
 # Deep_ECS.c:66: 	*(struct Deep_ECS_Component*)Deep_DynArray_Push(raw)(&componentList) = component;
	movq	$0, 0	 #,
	ud2	
.L67:
 # Deep_DynArray.h:40: 		free(arr->data);
	movq	%r13, %rcx	 # tmp224,
	call	free	 #
 # Deep_ECS.c:74: 	*(struct Deep_ECS_Id*)Deep_DynArray_Push(raw)(&identityList) = identity;
	leaq	.LC13(%rip), %rax	 #, tmp333
	movq	%rax, 0	 # tmp333, MEM[(struct Deep_ECS_Id *)0B].name
	ud2	
.L60:
 # Deep_DynArray.h:38: 	if (arr->options.freeOnError)
	cmpb	$0, 64(%rbx)	 #, MEM[(struct _Deep_DynArray *)componentArchetype_17 + 40B].options.freeOnError
	je	.L90	 #,
 # Deep_DynArray.h:40: 		free(arr->data);
	movq	56(%rbx), %rcx	 # MEM[(struct _Deep_DynArray *)componentArchetype_17 + 40B].data, MEM[(struct _Deep_DynArray *)componentArchetype_17 + 40B].data
	call	free	 #
 # Deep_DynArray.h:41: 		arr->data = NULL;
	movq	$0, 56(%rbx)	 #, MEM[(struct _Deep_DynArray *)componentArchetype_17 + 40B].data
	jmp	.L90	 #
.L76:
 # Deep_DynArray.h:38: 	if (arr->options.freeOnError)
	cmpb	$0, 104(%rbx)	 #, MEM[(struct _Deep_DynArray *)componentArchetype_17 + 80B].options.freeOnError
	je	.L90	 #,
 # Deep_DynArray.h:40: 		free(arr->data);
	movq	96(%rbx), %rcx	 # MEM[(struct _Deep_DynArray *)componentArchetype_17 + 80B].data, MEM[(struct _Deep_DynArray *)componentArchetype_17 + 80B].data
	call	free	 #
 # Deep_DynArray.h:41: 		arr->data = NULL;
	movq	$0, 96(%rbx)	 #, MEM[(struct _Deep_DynArray *)componentArchetype_17 + 80B].data
	jmp	.L90	 #
.L51:
 # Deep_DynArray.h:38: 	if (arr->options.freeOnError)
	cmpb	$0, 64(%rbx)	 #, MEM[(struct _Deep_DynArray *)componentArchetype_17 + 40B].options.freeOnError
	je	.L90	 #,
 # Deep_DynArray.h:40: 		free(arr->data);
	movq	56(%rbx), %rcx	 # MEM[(struct _Deep_DynArray *)componentArchetype_17 + 40B].data, MEM[(struct _Deep_DynArray *)componentArchetype_17 + 40B].data
	call	free	 #
 # Deep_DynArray.h:41: 		arr->data = NULL;
	movq	$0, 56(%rbx)	 #, MEM[(struct _Deep_DynArray *)componentArchetype_17 + 40B].data
	jmp	.L90	 #
	.text
	.section	.text.unlikely,"x"
	.seh_endproc
.LCOLDE15:
	.text
.LHOTE15:
	.section .rdata,"dr"
	.align 16
.LC4:
	.quad	13
	.quad	0
	.align 16
.LC5:
	.quad	8
	.quad	16
	.align 16
.LC6:
	.quad	8
	.quad	8
	.align 16
.LC7:
	.quad	32
	.quad	40
	.align 16
.LC8:
	.quad	8
	.quad	216
	.align 4
.LC9:
	.long	1069547520
	.align 4
.LC10:
	.long	1593835520
	.align 16
.LC11:
	.quad	1
	.quad	1
	.align 16
.LC14:
	.quad	2
	.quad	2
	.ident	"GCC: (Rev1, Built by MSYS2 project) 11.2.0"
	.def	__mingw_vfprintf;	.scl	2;	.type	32;	.endef
	.def	Deep_UnorderedMap_Hash;	.scl	2;	.type	32;	.endef
	.def	_Deep_UnorderedMap_Insert;	.scl	2;	.type	32;	.endef
	.def	calloc;	.scl	2;	.type	32;	.endef
	.def	malloc;	.scl	2;	.type	32;	.endef
	.def	Deep_ECS_Archetype_Create;	.scl	2;	.type	32;	.endef
	.def	realloc;	.scl	2;	.type	32;	.endef
	.def	free;	.scl	2;	.type	32;	.endef
	.section	.rdata$.refptr.Deep_UnorderedMap_ByteCompare, "dr"
	.globl	.refptr.Deep_UnorderedMap_ByteCompare
	.linkonce	discard
.refptr.Deep_UnorderedMap_ByteCompare:
	.quad	Deep_UnorderedMap_ByteCompare
