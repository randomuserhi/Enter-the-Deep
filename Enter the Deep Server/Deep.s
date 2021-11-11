	.file	"Deep.c"
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
	.align 8
.LC0:
	.ascii "Dynamically allocated %llu GBs\12\0"
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
	.section .rdata,"dr"
.LC1:
	.ascii "Failed to allocate %llu GBs\12\0"
	.text
	.p2align 4
	.globl	Deep_CheckMaxAllocationSize
	.def	Deep_CheckMaxAllocationSize;	.scl	2;	.type	32;	.endef
	.seh_proc	Deep_CheckMaxAllocationSize
Deep_CheckMaxAllocationSize:
	pushq	%r13	 #
	.seh_pushreg	%r13
	pushq	%r12	 #
	.seh_pushreg	%r12
	pushq	%rsi	 #
	.seh_pushreg	%rsi
	pushq	%rbx	 #
	.seh_pushreg	%rbx
	subq	$40, %rsp	 #,
	.seh_stackalloc	40
	.seh_endprologue
 # Deep.c:7: 	unsigned long long mallocSize = 0, numGigaBytes = 0;
	xorl	%ebx, %ebx	 # mallocSize
 # Deep.c:17: 			printf("Dynamically allocated %llu GBs\n", numGigaBytes);
	leaq	.LC0(%rip), %rsi	 #, tmp88
	jmp	.L6	 #
	.p2align 4,,10
	.p2align 3
.L7:
	movq	%rsi, %rcx	 # tmp88,
	call	printf.constprop.0	 #
 # Deep.c:18: 			free(mallocMemory);
	movq	%r12, %rcx	 # tmp85,
	call	free	 #
.L6:
 # Deep.c:12: 		mallocSize += GIGA_BYTE;
	addq	$1073741824, %rbx	 #, mallocSize
 # Deep.c:13: 		numGigaBytes = mallocSize / GIGA_BYTE;
	movq	%rbx, %r13	 # mallocSize, numGigaBytes
 # Deep.c:14: 		mallocMemory = malloc(mallocSize);
	movq	%rbx, %rcx	 # mallocSize,
	call	malloc	 #
 # Deep.c:13: 		numGigaBytes = mallocSize / GIGA_BYTE;
	shrq	$30, %r13	 #, numGigaBytes
 # Deep.c:14: 		mallocMemory = malloc(mallocSize);
	movq	%rax, %r12	 # tmp89, tmp85
 # Deep.c:17: 			printf("Dynamically allocated %llu GBs\n", numGigaBytes);
	movq	%r13, %rdx	 # numGigaBytes,
 # Deep.c:15: 		if (mallocMemory)
	testq	%rax, %rax	 # tmp85
	jne	.L7	 #,
 # Deep.c:22: 			printf("Failed to allocate %llu GBs\n", numGigaBytes);
	leaq	.LC1(%rip), %rcx	 #, tmp87
 # Deep.c:26: }
	addq	$40, %rsp	 #,
	popq	%rbx	 #
	popq	%rsi	 #
	popq	%r12	 #
	popq	%r13	 #
 # Deep.c:22: 			printf("Failed to allocate %llu GBs\n", numGigaBytes);
	jmp	printf	 #
	.seh_endproc
	.ident	"GCC: (Rev1, Built by MSYS2 project) 11.2.0"
	.def	__mingw_vfprintf;	.scl	2;	.type	32;	.endef
	.def	free;	.scl	2;	.type	32;	.endef
	.def	malloc;	.scl	2;	.type	32;	.endef
