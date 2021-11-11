	.file	"Deep_ECS_Archetype.c"
 # GNU C11 (Rev1, Built by MSYS2 project) version 11.2.0 (x86_64-w64-mingw32)
 #	compiled by GNU C version 11.2.0, GMP version 6.2.1, MPFR version 4.1.0-p13, MPC version 1.2.1, isl version isl-0.24-GMP

 # GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
 # options passed: -mtune=generic -march=x86-64 -O3 -std=c11
	.text
	.p2align 4
	.globl	Deep_ECS_Archetype_Hash
	.def	Deep_ECS_Archetype_Hash;	.scl	2;	.type	32;	.endef
	.seh_proc	Deep_ECS_Archetype_Hash
Deep_ECS_Archetype_Hash:
	.seh_endprologue
 # Deep_ECS_Archetype.c:6: 	Deep_ECS_ArchetypeHash Seed = archetype->type.size;
	movq	(%rcx), %r9	 # archetype_12(D)->type.D.4683.D.4682.size, Seed
 # Deep_ECS_Archetype.c:7: 	for (size_t i = 0; i < archetype->type.size; i++)
	testq	%r9, %r9	 # Seed
	je	.L4	 #,
 # Deep_ECS_Archetype.c:9: 		Seed ^= archetype->type.values[0] + 0x9e3779b9 + (Seed << 6) + (Seed >> 2);
	movq	16(%rcx), %rax	 # archetype_12(D)->type.D.4683.D.4682.values, archetype_12(D)->type.D.4683.D.4682.values
	movl	$2654435769, %r10d	 #, tmp94
	movq	%r9, %r8	 # Seed, <retval>
 # Deep_ECS_Archetype.c:7: 	for (size_t i = 0; i < archetype->type.size; i++)
	xorl	%edx, %edx	 # i
	addq	(%rax), %r10	 # *_1, _10
	.p2align 4,,10
	.p2align 3
.L3:
 # Deep_ECS_Archetype.c:9: 		Seed ^= archetype->type.values[0] + 0x9e3779b9 + (Seed << 6) + (Seed >> 2);
	movq	%r8, %rax	 # <retval>, tmp96
 # Deep_ECS_Archetype.c:9: 		Seed ^= archetype->type.values[0] + 0x9e3779b9 + (Seed << 6) + (Seed >> 2);
	movq	%r8, %rcx	 # <retval>, tmp97
 # Deep_ECS_Archetype.c:7: 	for (size_t i = 0; i < archetype->type.size; i++)
	addq	$1, %rdx	 #, i
 # Deep_ECS_Archetype.c:9: 		Seed ^= archetype->type.values[0] + 0x9e3779b9 + (Seed << 6) + (Seed >> 2);
	salq	$6, %rax	 #, tmp96
 # Deep_ECS_Archetype.c:9: 		Seed ^= archetype->type.values[0] + 0x9e3779b9 + (Seed << 6) + (Seed >> 2);
	shrq	$2, %rcx	 #, tmp97
 # Deep_ECS_Archetype.c:9: 		Seed ^= archetype->type.values[0] + 0x9e3779b9 + (Seed << 6) + (Seed >> 2);
	addq	%rcx, %rax	 # tmp97, tmp98
	addq	%r10, %rax	 # _10, _7
 # Deep_ECS_Archetype.c:9: 		Seed ^= archetype->type.values[0] + 0x9e3779b9 + (Seed << 6) + (Seed >> 2);
	xorq	%rax, %r8	 # _7, <retval>
 # Deep_ECS_Archetype.c:7: 	for (size_t i = 0; i < archetype->type.size; i++)
	cmpq	%rdx, %r9	 # i, Seed
	jne	.L3	 #,
 # Deep_ECS_Archetype.c:12: }
	movq	%r8, %rax	 # <retval>,
	ret	
	.p2align 4,,10
	.p2align 3
.L4:
 # Deep_ECS_Archetype.c:6: 	Deep_ECS_ArchetypeHash Seed = archetype->type.size;
	xorl	%r8d, %r8d	 # <retval>
 # Deep_ECS_Archetype.c:12: }
	movq	%r8, %rax	 # <retval>,
	ret	
	.seh_endproc
	.section	.text.unlikely,"x"
.LCOLDB3:
	.text
.LHOTB3:
	.p2align 4
	.globl	Deep_ECS_Archetype_Create
	.def	Deep_ECS_Archetype_Create;	.scl	2;	.type	32;	.endef
	.seh_proc	Deep_ECS_Archetype_Create
Deep_ECS_Archetype_Create:
	pushq	%r12	 #
	.seh_pushreg	%r12
	pushq	%rbx	 #
	.seh_pushreg	%rbx
	subq	$40, %rsp	 #,
	.seh_stackalloc	40
	.seh_endprologue
 # Deep_DynArray.h:30: 	arr->size = 0;
	pxor	%xmm0, %xmm0	 # tmp85
	movups	%xmm0, (%rcx)	 # tmp85, MEM <vector(2) long long unsigned int> [(long long unsigned int *)archetype_1(D)]
 # Deep_DynArray.h:32: 	arr->typeSize = typeSize;
	movdqa	.LC0(%rip), %xmm0	 #, tmp86
 # Deep_ECS_Archetype.c:15: {
	movq	%rcx, %rbx	 # tmp93, archetype
 # Deep_DynArray.h:29: 	arr->data = DEEP_DYNARRAY_SIZE == 0 ? NULL : malloc(typeSize * DEEP_DYNARRAY_SIZE);
	movq	$0, 16(%rcx)	 #, MEM[(struct _Deep_DynArray *)archetype_1(D)].data
 # Deep_DynArray.h:33: 	arr->options.freeOnError = DEEP_DYNARRAY_FREE_ON_ERROR;
	movb	$1, 24(%rcx)	 #, MEM[(struct _Deep_DynArray *)archetype_1(D)].options.freeOnError
 # Deep_DynArray.h:29: 	arr->data = DEEP_DYNARRAY_SIZE == 0 ? NULL : malloc(typeSize * DEEP_DYNARRAY_SIZE);
	movq	$0, 56(%rcx)	 #, MEM[(struct _Deep_DynArray *)archetype_1(D) + 40B].data
 # Deep_DynArray.h:31: 	arr->capacity = DEEP_DYNARRAY_SIZE;
	movq	$0, 48(%rcx)	 #, MEM[(struct _Deep_DynArray *)archetype_1(D) + 40B].capacity
 # Deep_DynArray.h:33: 	arr->options.freeOnError = DEEP_DYNARRAY_FREE_ON_ERROR;
	movb	$1, 64(%rcx)	 #, MEM[(struct _Deep_DynArray *)archetype_1(D) + 40B].options.freeOnError
 # Deep_DynArray.h:29: 	arr->data = DEEP_DYNARRAY_SIZE == 0 ? NULL : malloc(typeSize * DEEP_DYNARRAY_SIZE);
	movq	$0, 96(%rcx)	 #, MEM[(struct _Deep_DynArray *)archetype_1(D) + 80B].data
 # Deep_DynArray.h:31: 	arr->capacity = DEEP_DYNARRAY_SIZE;
	movq	$0, 88(%rcx)	 #, MEM[(struct _Deep_DynArray *)archetype_1(D) + 80B].capacity
 # Deep_DynArray.h:32: 	arr->typeSize = typeSize;
	movq	$40, 112(%rcx)	 #, MEM[(struct _Deep_DynArray *)archetype_1(D) + 80B].typeSize
 # Deep_DynArray.h:33: 	arr->options.freeOnError = DEEP_DYNARRAY_FREE_ON_ERROR;
	movb	$1, 104(%rcx)	 #, MEM[(struct _Deep_DynArray *)archetype_1(D) + 80B].options.freeOnError
 # Deep_DynArray.h:32: 	arr->typeSize = typeSize;
	movups	%xmm0, 32(%rcx)	 # tmp86, MEM <vector(2) long long unsigned int> [(long long unsigned int *)archetype_1(D) + 32B]
	movups	%xmm0, 72(%rcx)	 # tmp86, MEM <vector(2) long long unsigned int> [(long long unsigned int *)archetype_1(D) + 72B]
 # Deep_DynArray.h:74: 		void* tmp = malloc(DEEP_DYNARRAY_SIZE == 0 ? arr->typeSize : arr->typeSize * DEEP_DYNARRAY_SIZE);
	movl	$8, %ecx	 #,
	call	malloc	 #
	movq	%rax, %r12	 # tmp94, tmp88
 # Deep_DynArray.h:75: 		if (tmp)
	testq	%rax, %rax	 # tmp88
	je	.L8	 #,
 # Deep_DynArray.h:78: 			arr->size = 1;
	movdqa	.LC1(%rip), %xmm0	 #, tmp89
 # Deep_ECS_Archetype.c:20: 	*Deep_DynArray_Push(Deep_ECS_Handle)(&archetype->type) = DEEP_ECS_COMPONENT;
	movq	$256, (%rax)	 #, MEM[(Deep_ECS_Handle *)tmp_28]
 # Deep_DynArray.h:52: 			void* tmp = realloc(arr->data, arr->typeSize * newCapacity);
	movl	$16, %edx	 #,
	movq	%rax, %rcx	 # tmp88,
 # Deep_DynArray.h:78: 			arr->size = 1;
	movups	%xmm0, (%rbx)	 # tmp89, MEM <vector(2) long long unsigned int> [(long long unsigned int *)archetype_1(D)]
 # Deep_DynArray.h:52: 			void* tmp = realloc(arr->data, arr->typeSize * newCapacity);
	call	realloc	 #
 # Deep_DynArray.h:53: 			if (tmp)
	testq	%rax, %rax	 # tmp
	je	.L9	 #,
 # Deep_DynArray.h:57: 				++arr->size;
	movdqa	.LC2(%rip), %xmm0	 #, tmp90
 # Deep_DynArray.h:55: 				arr->data = tmp;
	movq	%rax, 16(%rbx)	 # tmp, MEM[(struct _Deep_DynArray *)archetype_1(D)].data
 # Deep_DynArray.h:57: 				++arr->size;
	movups	%xmm0, (%rbx)	 # tmp90, MEM <vector(2) long long unsigned int> [(long long unsigned int *)archetype_1(D)]
 # Deep_ECS_Archetype.c:21: 	*Deep_DynArray_Push(Deep_ECS_Handle)(&archetype->type) = DEEP_ECS_ID;
	movq	$512, 8(%rax)	 #, MEM[(Deep_ECS_Handle *)tmp_15 + 8B]
 # Deep_ECS_Archetype.c:22: }
	addq	$40, %rsp	 #,
	popq	%rbx	 #
	popq	%r12	 #
	ret	
	.seh_endproc
	.section	.text.unlikely,"x"
	.def	Deep_ECS_Archetype_Create.cold;	.scl	3;	.type	32;	.endef
	.seh_proc	Deep_ECS_Archetype_Create.cold
	.seh_stackalloc	56
	.seh_savereg	%rbx, 40
	.seh_savereg	%r12, 48
	.seh_endprologue
Deep_ECS_Archetype_Create.cold:
.L8:
 # Deep_ECS_Archetype.c:20: 	*Deep_DynArray_Push(Deep_ECS_Handle)(&archetype->type) = DEEP_ECS_COMPONENT;
	movq	$0, 0	 #, MEM[(Deep_ECS_Handle *)0B]
	ud2	
.L9:
 # Deep_DynArray.h:40: 		free(arr->data);
	movq	%r12, %rcx	 # tmp88,
	call	free	 #
 # Deep_DynArray.h:41: 		arr->data = NULL;
	movq	$0, 16(%rbx)	 #, MEM[(struct _Deep_DynArray *)archetype_1(D)].data
 # Deep_ECS_Archetype.c:21: 	*Deep_DynArray_Push(Deep_ECS_Handle)(&archetype->type) = DEEP_ECS_ID;
	movq	$0, 0	 #, MEM[(Deep_ECS_Handle *)0B]
	ud2	
	.text
	.section	.text.unlikely,"x"
	.seh_endproc
.LCOLDE3:
	.text
.LHOTE3:
	.section .rdata,"dr"
	.align 16
.LC0:
	.quad	8
	.quad	0
	.align 16
.LC1:
	.quad	1
	.quad	1
	.align 16
.LC2:
	.quad	2
	.quad	2
	.ident	"GCC: (Rev1, Built by MSYS2 project) 11.2.0"
	.def	malloc;	.scl	2;	.type	32;	.endef
	.def	realloc;	.scl	2;	.type	32;	.endef
	.def	free;	.scl	2;	.type	32;	.endef
