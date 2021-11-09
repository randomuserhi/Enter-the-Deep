	.text
	.def	 @feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.file	"Deep_ECS.c"
	.def	 Deep_ECS_GetComponent;
	.scl	2;
	.type	32;
	.endef
	.globl	Deep_ECS_GetComponent           # -- Begin function Deep_ECS_GetComponent
	.p2align	4, 0x90
Deep_ECS_GetComponent:                  # @Deep_ECS_GetComponent
.seh_proc Deep_ECS_GetComponent
# %bb.0:
	pushq	%r15
	.seh_pushreg %r15
	pushq	%r14
	.seh_pushreg %r14
	pushq	%rsi
	.seh_pushreg %rsi
	pushq	%rdi
	.seh_pushreg %rdi
	pushq	%rbx
	.seh_pushreg %rbx
	subq	$48, %rsp
	.seh_stackalloc 48
	.seh_endprologue
	movq	%r9, %rdi
	movq	%rdx, %rbx
	movq	%rcx, %r15
	movq	%r8, 40(%rsp)
	leaq	40(%rsp), %r14
	movl	$8, %edx
	movl	$3997467649, %r8d               # imm = 0xEE448401
	movq	%r14, %rcx
	callq	Deep_UnorderedMap_Hash
	movq	%rbx, %rcx
	movq	%rax, %rdx
	movq	%r14, %r8
	callq	_Deep_UnorderedMap_Insert
	xorps	%xmm0, %xmm0
	movups	%xmm0, (%r15)
	movq	(%rax), %r8
	movq	(%r8), %rdx
	testq	%rdx, %rdx
	je	.LBB0_5
# %bb.1:
	movq	16(%r8), %rsi
	xorl	%ebx, %ebx
	xorl	%ecx, %ecx
	.p2align	4, 0x90
.LBB0_2:                                # =>This Inner Loop Header: Depth=1
	cmpq	%rdi, (%rsi,%rcx,8)
	je	.LBB0_3
# %bb.4:                                #   in Loop: Header=BB0_2 Depth=1
	addq	$1, %rcx
	addq	$-40, %rbx
	cmpq	%rcx, %rdx
	jne	.LBB0_2
	jmp	.LBB0_5
.LBB0_3:
	movq	96(%r8), %rcx
	subq	%rbx, %rcx
	movq	%rcx, 8(%r15)
	movq	8(%rax), %rax
	movq	%rax, (%r15)
.LBB0_5:
	movq	%r15, %rax
	addq	$48, %rsp
	popq	%rbx
	popq	%rdi
	popq	%rsi
	popq	%r14
	popq	%r15
	retq
	.seh_endproc
                                        # -- End function
	.def	 Deep_ECS_PrintHierarchy;
	.scl	2;
	.type	32;
	.endef
	.globl	Deep_ECS_PrintHierarchy         # -- Begin function Deep_ECS_PrintHierarchy
	.p2align	4, 0x90
Deep_ECS_PrintHierarchy:                # @Deep_ECS_PrintHierarchy
.seh_proc Deep_ECS_PrintHierarchy
# %bb.0:
	pushq	%r15
	.seh_pushreg %r15
	pushq	%r14
	.seh_pushreg %r14
	pushq	%r13
	.seh_pushreg %r13
	pushq	%r12
	.seh_pushreg %r12
	pushq	%rsi
	.seh_pushreg %rsi
	pushq	%rdi
	.seh_pushreg %rdi
	pushq	%rbp
	.seh_pushreg %rbp
	pushq	%rbx
	.seh_pushreg %rbx
	subq	$40, %rsp
	.seh_stackalloc 40
	.seh_endprologue
	movq	8(%rcx), %rbx
	testq	%rbx, %rbx
	je	.LBB1_12
# %bb.1:
	movq	%rcx, %r15
	leaq	32(%rsp), %r13
	leaq	.L.str.1(%rip), %r12
	jmp	.LBB1_2
	.p2align	4, 0x90
.LBB1_10:                               #   in Loop: Header=BB1_2 Depth=1
	leaq	.Lstr(%rip), %rcx
	callq	puts
.LBB1_11:                               #   in Loop: Header=BB1_2 Depth=1
	movq	8(%rbx), %rbx
	testq	%rbx, %rbx
	je	.LBB1_12
.LBB1_2:                                # =>This Loop Header: Depth=1
                                        #     Child Loop BB1_4 Depth 2
                                        #     Child Loop BB1_7 Depth 2
                                        #       Child Loop BB1_8 Depth 3
	movq	80(%r15), %rax
	movq	(%rbx,%rax), %rax
	testq	%rax, %rax
	je	.LBB1_11
# %bb.3:                                #   in Loop: Header=BB1_2 Depth=1
	movq	88(%r15), %rdi
	movq	%rax, 32(%rsp)
	movl	$8, %edx
	movl	$3997467649, %r8d               # imm = 0xEE448401
	movq	%r13, %rcx
	callq	Deep_UnorderedMap_Hash
	movq	%r15, %rcx
	movq	%rax, %rdx
	movq	%r13, %r8
	callq	_Deep_UnorderedMap_Insert
	movq	(%rax), %rcx
	movq	16(%rcx), %rbp
	movq	$-24, %rdx
	.p2align	4, 0x90
.LBB1_4:                                #   Parent Loop BB1_2 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	addq	$40, %rdx
	cmpq	$512, (%rbp)                    # imm = 0x200
	leaq	8(%rbp), %rbp
	jne	.LBB1_4
# %bb.5:                                #   in Loop: Header=BB1_2 Depth=1
	movq	96(%rcx), %rcx
	movq	8(%rax), %rax
	movq	(%rcx,%rdx), %rcx
	movq	(%rcx,%rax,8), %rdx
	leaq	.L.str(%rip), %rcx
	callq	printf
	movq	(%rbx,%rdi), %rax
	cmpq	$0, (%rax)
	je	.LBB1_10
# %bb.6:                                #   in Loop: Header=BB1_2 Depth=1
	movl	$91, %ebp
	xorl	%r14d, %r14d
	.p2align	4, 0x90
.LBB1_7:                                #   Parent Loop BB1_2 Depth=1
                                        # =>  This Loop Header: Depth=2
                                        #       Child Loop BB1_8 Depth 3
	movq	16(%rax), %rax
	movq	(%rax,%r14,8), %rax
	movq	%rax, 32(%rsp)
	movl	$8, %edx
	movl	$3997467649, %r8d               # imm = 0xEE448401
	movq	%r13, %rcx
	callq	Deep_UnorderedMap_Hash
	movq	%r15, %rcx
	movq	%rax, %rdx
	movq	%r13, %r8
	callq	_Deep_UnorderedMap_Insert
	movq	(%rax), %rcx
	movq	16(%rcx), %rsi
	movq	$-24, %rdx
	.p2align	4, 0x90
.LBB1_8:                                #   Parent Loop BB1_2 Depth=1
                                        #     Parent Loop BB1_7 Depth=2
                                        # =>    This Inner Loop Header: Depth=3
	addq	$40, %rdx
	cmpq	$512, (%rsi)                    # imm = 0x200
	leaq	8(%rsi), %rsi
	jne	.LBB1_8
# %bb.9:                                #   in Loop: Header=BB1_7 Depth=2
	movq	96(%rcx), %rcx
	movq	8(%rax), %rax
	movq	(%rcx,%rdx), %rcx
	movq	(%rcx,%rax,8), %r8
	movq	%r12, %rcx
	movl	%ebp, %edx
	callq	printf
	addq	$1, %r14
	movq	(%rbx,%rdi), %rax
	movl	$44, %ebp
	cmpq	(%rax), %r14
	jb	.LBB1_7
	jmp	.LBB1_10
.LBB1_12:
	addq	$40, %rsp
	popq	%rbx
	popq	%rbp
	popq	%rdi
	popq	%rsi
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	retq
	.seh_endproc
                                        # -- End function
	.def	 printf;
	.scl	3;
	.type	32;
	.endef
	.p2align	4, 0x90                         # -- Begin function printf
printf:                                 # @printf
.seh_proc printf
# %bb.0:
	pushq	%rsi
	.seh_pushreg %rsi
	subq	$48, %rsp
	.seh_stackalloc 48
	.seh_endprologue
	movq	%rcx, %rsi
	movq	%rdx, 72(%rsp)
	movq	%r8, 80(%rsp)
	movq	%r9, 88(%rsp)
	leaq	72(%rsp), %rax
	movq	%rax, 40(%rsp)
	movl	$1, %ecx
	callq	*__imp___acrt_iob_func(%rip)
	movq	40(%rsp), %r8
	movq	%rax, %rcx
	movq	%rsi, %rdx
	callq	__mingw_vfprintf
	nop
	addq	$48, %rsp
	popq	%rsi
	retq
	.seh_endproc
                                        # -- End function
	.def	 Deep_ECS_Create;
	.scl	2;
	.type	32;
	.endef
	.section	.rdata,"dr"
	.p2align	4                               # -- Begin function Deep_ECS_Create
.LCPI3_0:
	.quad	8                               # 0x8
	.quad	16                              # 0x10
.LCPI3_1:
	.quad	8                               # 0x8
	.quad	8                               # 0x8
.LCPI3_2:
	.quad	13                              # 0xd
	.quad	0                               # 0x0
.LCPI3_3:
	.quad	32                              # 0x20
	.quad	40                              # 0x28
.LCPI3_4:
	.quad	8                               # 0x8
	.quad	216                             # 0xd8
.LCPI3_5:
	.long	0x3fc00000                      # float 1.5
.LCPI3_6:
	.long	0x5f000000                      # float 9.22337203E+18
	.zero	8
.LCPI3_7:
	.quad	1                               # 0x1
	.quad	1                               # 0x1
.LCPI3_8:
	.quad	2                               # 0x2
	.quad	2                               # 0x2
	.text
	.globl	Deep_ECS_Create
	.p2align	4, 0x90
Deep_ECS_Create:                        # @Deep_ECS_Create
.seh_proc Deep_ECS_Create
# %bb.0:
	pushq	%r15
	.seh_pushreg %r15
	pushq	%r14
	.seh_pushreg %r14
	pushq	%r12
	.seh_pushreg %r12
	pushq	%rsi
	.seh_pushreg %rsi
	pushq	%rdi
	.seh_pushreg %rdi
	pushq	%rbx
	.seh_pushreg %rbx
	subq	$120, %rsp
	.seh_stackalloc 120
	movaps	%xmm9, 96(%rsp)                 # 16-byte Spill
	.seh_savexmm %xmm9, 96
	movaps	%xmm8, 80(%rsp)                 # 16-byte Spill
	.seh_savexmm %xmm8, 80
	movaps	%xmm7, 64(%rsp)                 # 16-byte Spill
	.seh_savexmm %xmm7, 64
	movaps	%xmm6, 48(%rsp)                 # 16-byte Spill
	.seh_savexmm %xmm6, 48
	.seh_endprologue
	movq	%rcx, %rsi
	leaq	Deep_UnorderedMap_ByteCompare(%rip), %rdi
	movq	%rdi, 40(%rcx)
	movaps	.LCPI3_0(%rip), %xmm0           # xmm0 = [8,16]
	movups	%xmm0, 48(%rcx)
	movaps	.LCPI3_1(%rip), %xmm6           # xmm6 = [8,8]
	movups	%xmm6, 64(%rcx)
	movaps	.LCPI3_2(%rip), %xmm8           # xmm8 = [13,0]
	movups	%xmm8, 24(%rcx)
	movaps	.LCPI3_3(%rip), %xmm9           # xmm9 = [32,40]
	movups	%xmm9, 80(%rcx)
	movl	$13, %ecx
	movl	$8, %edx
	callq	calloc
	movq	%rax, (%rsi)
	xorps	%xmm7, %xmm7
	movups	%xmm7, 8(%rsi)
	movq	%rdi, 136(%rsi)
	movaps	.LCPI3_4(%rip), %xmm0           # xmm0 = [8,216]
	movups	%xmm0, 144(%rsi)
	movups	%xmm6, 160(%rsi)
	movups	%xmm8, 120(%rsi)
	movups	%xmm9, 176(%rsi)
	movl	$13, %ecx
	movl	$8, %edx
	callq	calloc
	movq	%rax, 96(%rsi)
	movups	%xmm7, 104(%rsi)
	movq	%rdi, 232(%rsi)
	movups	%xmm6, 240(%rsi)
	movups	%xmm6, 256(%rsi)
	movups	%xmm8, 216(%rsi)
	movups	%xmm9, 272(%rsi)
	movl	$13, %ecx
	movl	$8, %edx
	callq	calloc
	movq	%rax, 192(%rsi)
	movups	%xmm7, 200(%rsi)
	movq	$0, 40(%rsp)
	leaq	40(%rsp), %rdi
	movl	$8, %edx
	movl	$3997467649, %r8d               # imm = 0xEE448401
	movq	%rdi, %rcx
	callq	Deep_UnorderedMap_Hash
	movq	%rsi, %rcx
	movq	%rax, %rdx
	movq	%rdi, %r8
	callq	_Deep_UnorderedMap_Insert
	movl	$216, %ecx
	callq	malloc
	testq	%rax, %rax
	je	.LBB3_33
# %bb.1:
	movq	%rax, %r15
	movq	%rax, %rcx
	callq	Deep_ECS_Archetype_Create
	movq	56(%r15), %rcx
	testq	%rcx, %rcx
	je	.LBB3_8
# %bb.2:
	movq	40(%r15), %rdx
	cmpq	48(%r15), %rdx
	jne	.LBB3_7
# %bb.3:
	testq	%rdx, %rdx
	js	.LBB3_4
# %bb.5:
	xorps	%xmm0, %xmm0
	cvtsi2ss	%rdx, %xmm0
	jmp	.LBB3_6
.LBB3_8:
	movl	$8, %ecx
	callq	malloc
	movq	%rax, %rcx
	movq	%rax, 56(%r15)
	movaps	.LCPI3_7(%rip), %xmm6           # xmm6 = [1,1]
	movups	%xmm6, 40(%r15)
	movq	$256, (%rax)                    # imm = 0x100
	testq	%rax, %rax
	jne	.LBB3_9
# %bb.15:
	movl	$8, %ecx
	callq	malloc
	movq	%rax, 56(%r15)
	movups	%xmm6, 40(%r15)
	jmp	.LBB3_16
.LBB3_7:
	leaq	1(%rdx), %rax
	movq	%rax, 40(%r15)
	leaq	(%rcx,%rdx,8), %rax
	movq	$256, (%rax)                    # imm = 0x100
.LBB3_9:
	movq	40(%r15), %rdx
	cmpq	48(%r15), %rdx
	jne	.LBB3_14
.LBB3_10:
	testq	%rdx, %rdx
	js	.LBB3_11
# %bb.12:
	xorps	%xmm0, %xmm0
	cvtsi2ss	%rdx, %xmm0
	jmp	.LBB3_13
.LBB3_11:
	movq	%rdx, %rbx
	shrq	%rbx
	movl	%edx, %eax
	andl	$1, %eax
	orq	%rbx, %rax
	xorps	%xmm0, %xmm0
	cvtsi2ss	%rax, %xmm0
	addss	%xmm0, %xmm0
.LBB3_13:
	mulss	.LCPI3_5(%rip), %xmm0
	cvttss2si	%xmm0, %r8
	movq	%r8, %rax
	subss	.LCPI3_6(%rip), %xmm0
	cvttss2si	%xmm0, %rbx
	sarq	$63, %rax
	andq	%rax, %rbx
	orq	%r8, %rbx
	xorl	%edi, %edi
	cmpq	%rbx, %rdx
	sete	%dil
	addq	%rbx, %rdi
	leaq	(,%rdi,8), %rdx
	callq	realloc
	movq	%rax, %rcx
	movq	%rax, 56(%r15)
	movq	%rdi, 48(%r15)
	movq	40(%r15), %rax
	leaq	1(%rax), %rdx
	movq	%rdx, 40(%r15)
	imulq	72(%r15), %rax
	addq	%rcx, %rax
	jmp	.LBB3_16
.LBB3_4:
	movq	%rdx, %rbx
	shrq	%rbx
	movl	%edx, %eax
	andl	$1, %eax
	orq	%rbx, %rax
	xorps	%xmm0, %xmm0
	cvtsi2ss	%rax, %xmm0
	addss	%xmm0, %xmm0
.LBB3_6:
	mulss	.LCPI3_5(%rip), %xmm0
	cvttss2si	%xmm0, %r8
	movq	%r8, %rax
	subss	.LCPI3_6(%rip), %xmm0
	cvttss2si	%xmm0, %rbx
	sarq	$63, %rax
	andq	%rax, %rbx
	orq	%r8, %rbx
	xorl	%r14d, %r14d
	cmpq	%rbx, %rdx
	sete	%r14b
	addq	%rbx, %r14
	leaq	(,%r14,8), %rdx
	callq	realloc
	movq	%rax, %rcx
	movq	%rax, 56(%r15)
	movq	%r14, 48(%r15)
	movq	40(%r15), %rax
	leaq	1(%rax), %rdx
	movq	%rdx, 40(%r15)
	imulq	72(%r15), %rax
	addq	%rcx, %rax
	movq	$256, (%rax)                    # imm = 0x100
	movq	40(%r15), %rdx
	cmpq	48(%r15), %rdx
	je	.LBB3_10
.LBB3_14:
	leaq	1(%rdx), %rax
	movq	%rax, 40(%r15)
	leaq	(%rcx,%rdx,8), %rax
.LBB3_16:
	movq	$512, (%rax)                    # imm = 0x200
	movl	$8, %ecx
	callq	malloc
	movq	$0, (%rax)
	movl	$16, %edx
	movq	%rax, %rcx
	callq	realloc
	movq	%rax, %r12
	movq	$0, 8(%rax)
	movl	$8, %ecx
	callq	malloc
	leaq	.L.str.3(%rip), %rcx
	movq	%rcx, (%rax)
	movl	$16, %edx
	movq	%rax, %rcx
	callq	realloc
	movq	%rax, %r14
	leaq	.L.str.4(%rip), %rax
	movq	%rax, 8(%r14)
	movq	96(%r15), %rcx
	testq	%rcx, %rcx
	je	.LBB3_23
# %bb.17:
	movq	80(%r15), %rdx
	cmpq	88(%r15), %rdx
	jne	.LBB3_22
# %bb.18:
	testq	%rdx, %rdx
	js	.LBB3_19
# %bb.20:
	xorps	%xmm0, %xmm0
	cvtsi2ss	%rdx, %xmm0
	jmp	.LBB3_21
.LBB3_23:
	movl	$40, %ecx
	callq	malloc
	movq	%rax, 96(%r15)
	movaps	.LCPI3_7(%rip), %xmm0           # xmm0 = [1,1]
	movaps	%xmm0, 80(%r15)
	jmp	.LBB3_24
.LBB3_22:
	leaq	1(%rdx), %rax
	movq	%rax, 80(%r15)
	leaq	(%rdx,%rdx,4), %rax
	leaq	(%rcx,%rax,8), %rax
	jmp	.LBB3_24
.LBB3_19:
	movq	%rdx, %rdi
	shrq	%rdi
	movl	%edx, %eax
	andl	$1, %eax
	orq	%rdi, %rax
	xorps	%xmm0, %xmm0
	cvtsi2ss	%rax, %xmm0
	addss	%xmm0, %xmm0
.LBB3_21:
	mulss	.LCPI3_5(%rip), %xmm0
	cvttss2si	%xmm0, %rdi
	movq	%rdi, %rax
	sarq	$63, %rax
	subss	.LCPI3_6(%rip), %xmm0
	cvttss2si	%xmm0, %rbx
	andq	%rax, %rbx
	orq	%rdi, %rbx
	xorl	%edi, %edi
	cmpq	%rbx, %rdx
	sete	%dil
	addq	%rbx, %rdi
	leaq	(,%rdi,8), %rax
	leaq	(%rax,%rax,4), %rdx
	callq	realloc
	movq	%rax, %rcx
	movq	%rax, 96(%r15)
	movq	%rdi, 88(%r15)
	movq	80(%r15), %rax
	leaq	1(%rax), %rdx
	movq	%rdx, 80(%r15)
	imulq	112(%r15), %rax
	addq	%rcx, %rax
.LBB3_24:
	movaps	.LCPI3_8(%rip), %xmm6           # xmm6 = [2,2]
	movups	%xmm6, (%rax)
	movq	%r12, 16(%rax)
	movb	$1, 24(%rax)
	movq	$8, 32(%rax)
	movq	96(%r15), %rcx
	testq	%rcx, %rcx
	je	.LBB3_31
# %bb.25:
	movq	80(%r15), %rdx
	cmpq	88(%r15), %rdx
	jne	.LBB3_30
# %bb.26:
	testq	%rdx, %rdx
	js	.LBB3_27
# %bb.28:
	xorps	%xmm0, %xmm0
	cvtsi2ss	%rdx, %xmm0
	jmp	.LBB3_29
.LBB3_31:
	movl	$40, %ecx
	callq	malloc
	movq	%rax, 96(%r15)
	movaps	.LCPI3_7(%rip), %xmm0           # xmm0 = [1,1]
	movaps	%xmm0, 80(%r15)
	jmp	.LBB3_32
.LBB3_30:
	leaq	1(%rdx), %rax
	movq	%rax, 80(%r15)
	leaq	(%rdx,%rdx,4), %rax
	leaq	(%rcx,%rax,8), %rax
	jmp	.LBB3_32
.LBB3_27:
	movq	%rdx, %rbx
	shrq	%rbx
	movl	%edx, %eax
	andl	$1, %eax
	orq	%rbx, %rax
	xorps	%xmm0, %xmm0
	cvtsi2ss	%rax, %xmm0
	addss	%xmm0, %xmm0
.LBB3_29:
	mulss	.LCPI3_5(%rip), %xmm0
	cvttss2si	%xmm0, %rbx
	movq	%rbx, %rax
	sarq	$63, %rax
	subss	.LCPI3_6(%rip), %xmm0
	cvttss2si	%xmm0, %rdi
	andq	%rax, %rdi
	orq	%rbx, %rdi
	xorl	%ebx, %ebx
	cmpq	%rdi, %rdx
	sete	%bl
	addq	%rdi, %rbx
	leaq	(,%rbx,8), %rax
	leaq	(%rax,%rax,4), %rdx
	callq	realloc
	movq	%rax, %rcx
	movq	%rax, 96(%r15)
	movq	%rbx, 88(%r15)
	movq	80(%r15), %rax
	leaq	1(%rax), %rdx
	movq	%rdx, 80(%r15)
	imulq	112(%r15), %rax
	addq	%rcx, %rax
.LBB3_32:
	movups	%xmm6, (%rax)
	movq	%r14, 16(%rax)
	movb	$1, 24(%rax)
	movq	$8, 32(%rax)
	movq	$256, 40(%rsp)                  # imm = 0x100
	leaq	40(%rsp), %rbx
	movl	$8, %edx
	movl	$3997467649, %r8d               # imm = 0xEE448401
	movq	%rbx, %rcx
	callq	Deep_UnorderedMap_Hash
	movq	%rsi, %rcx
	movq	%rax, %rdx
	movq	%rbx, %r8
	callq	_Deep_UnorderedMap_Insert
	movq	%r15, (%rax)
	movq	$0, 8(%rax)
	movq	$512, 40(%rsp)                  # imm = 0x200
	movl	$8, %edx
	movl	$3997467649, %r8d               # imm = 0xEE448401
	movq	%rbx, %rcx
	callq	Deep_UnorderedMap_Hash
	movq	%rsi, %rcx
	movq	%rax, %rdx
	movq	%rbx, %r8
	callq	_Deep_UnorderedMap_Insert
	movq	%r15, (%rax)
	movq	$1, 8(%rax)
.LBB3_33:
	movaps	48(%rsp), %xmm6                 # 16-byte Reload
	movaps	64(%rsp), %xmm7                 # 16-byte Reload
	movaps	80(%rsp), %xmm8                 # 16-byte Reload
	movaps	96(%rsp), %xmm9                 # 16-byte Reload
	addq	$120, %rsp
	popq	%rbx
	popq	%rdi
	popq	%rsi
	popq	%r12
	popq	%r14
	popq	%r15
	retq
	.seh_endproc
                                        # -- End function
	.section	.rdata,"dr"
.L.str:                                 # @.str
	.asciz	"%s : "

.L.str.1:                               # @.str.1
	.asciz	"%c %s"

.L.str.3:                               # @.str.3
	.asciz	"ECS_COMPONENT"

.L.str.4:                               # @.str.4
	.asciz	"ECS_ID"

.Lstr:                                  # @str
	.asciz	" ]"

	.addrsig
	.addrsig_sym Deep_UnorderedMap_ByteCompare
