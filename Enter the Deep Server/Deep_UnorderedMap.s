	.text
	.def	 @feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.file	"Deep_UnorderedMap.c"
	.def	 _Deep_UnorderedMap_ShiftMix;
	.scl	2;
	.type	32;
	.endef
	.globl	_Deep_UnorderedMap_ShiftMix     # -- Begin function _Deep_UnorderedMap_ShiftMix
	.p2align	4, 0x90
_Deep_UnorderedMap_ShiftMix:            # @_Deep_UnorderedMap_ShiftMix
# %bb.0:
	movq	%rcx, %rax
	shrq	$47, %rax
	xorq	%rcx, %rax
	retq
                                        # -- End function
	.def	 Deep_UnorderedMap_Hash;
	.scl	2;
	.type	32;
	.endef
	.globl	Deep_UnorderedMap_Hash          # -- Begin function Deep_UnorderedMap_Hash
	.p2align	4, 0x90
Deep_UnorderedMap_Hash:                 # @Deep_UnorderedMap_Hash
.seh_proc Deep_UnorderedMap_Hash
# %bb.0:
	pushq	%rsi
	.seh_pushreg %rsi
	.seh_endprologue
	movabsq	$-4132994306676758123, %r9      # imm = 0xC6A4A7935BD1E995
	movq	%rdx, %r11
	andq	$-8, %r11
	leaq	(%rcx,%r11), %r10
	movq	%rdx, %rsi
	imulq	%r9, %rsi
	xorq	%r8, %rsi
	testq	%r11, %r11
	je	.LBB1_1
# %bb.6:
	addq	$-8, %r11
	testb	$8, %r11b
	jne	.LBB1_7
# %bb.8:
	movq	(%rcx), %r8
	imulq	%r9, %r8
	movq	%r8, %rax
	shrq	$47, %rax
	xorq	%r8, %rax
	imulq	%r9, %rax
	xorq	%rsi, %rax
	imulq	%r9, %rax
	addq	$8, %rcx
	movq	%rax, %rsi
	testq	%r11, %r11
	jne	.LBB1_10
	jmp	.LBB1_2
.LBB1_1:
	movq	%rsi, %rax
	jmp	.LBB1_2
.LBB1_7:
                                        # implicit-def: $rax
	testq	%r11, %r11
	je	.LBB1_2
.LBB1_10:
	movq	%rsi, %rax
	.p2align	4, 0x90
.LBB1_11:                               # =>This Inner Loop Header: Depth=1
	movq	(%rcx), %r8
	imulq	%r9, %r8
	movq	%r8, %rsi
	shrq	$47, %rsi
	xorq	%r8, %rsi
	imulq	%r9, %rsi
	xorq	%rax, %rsi
	imulq	%r9, %rsi
	movq	8(%rcx), %r8
	imulq	%r9, %r8
	movq	%r8, %rax
	shrq	$47, %rax
	xorq	%r8, %rax
	imulq	%r9, %rax
	xorq	%rsi, %rax
	imulq	%r9, %rax
	addq	$16, %rcx
	cmpq	%r10, %rcx
	jne	.LBB1_11
.LBB1_2:
	andq	$7, %rdx
	je	.LBB1_5
# %bb.3:
	movzbl	-1(%rdx,%r10), %ecx
	cmpq	$1, %rdx
	jbe	.LBB1_4
# %bb.12:
	movq	%rcx, %rsi
	shlq	$8, %rsi
	movzbl	-2(%rdx,%r10), %ecx
	orq	%rsi, %rcx
	cmpq	$2, %rdx
	je	.LBB1_4
# %bb.13:
	movq	%rcx, %rsi
	shlq	$8, %rsi
	movzbl	-3(%rdx,%r10), %ecx
	orq	%rsi, %rcx
	cmpq	$4, %rdx
	jb	.LBB1_4
# %bb.14:
	movq	%rcx, %rsi
	shlq	$8, %rsi
	movzbl	-4(%rdx,%r10), %ecx
	orq	%rsi, %rcx
	cmpq	$4, %rdx
	je	.LBB1_4
# %bb.15:
	movq	%rcx, %rsi
	shlq	$8, %rsi
	movzbl	-5(%rdx,%r10), %ecx
	orq	%rsi, %rcx
	cmpq	$6, %rdx
	jb	.LBB1_4
# %bb.16:
	movq	%rcx, %rsi
	shlq	$8, %rsi
	movzbl	-6(%rdx,%r10), %ecx
	orq	%rsi, %rcx
	cmpq	$7, %rdx
	jne	.LBB1_4
# %bb.17:
	shlq	$8, %rcx
	movzbl	-7(%rdx,%r10), %edx
	orq	%rdx, %rcx
.LBB1_4:
	xorq	%rax, %rcx
	imulq	%r9, %rcx
	movq	%rcx, %rax
.LBB1_5:
	movq	%rax, %rcx
	shrq	$47, %rcx
	xorq	%rax, %rcx
	imulq	%r9, %rcx
	movq	%rcx, %rax
	shrq	$47, %rax
	xorq	%rcx, %rax
	popq	%rsi
	retq
	.seh_endproc
                                        # -- End function
	.def	 Deep_UnorderedMap_ByteCompare;
	.scl	2;
	.type	32;
	.endef
	.globl	Deep_UnorderedMap_ByteCompare   # -- Begin function Deep_UnorderedMap_ByteCompare
	.p2align	4, 0x90
Deep_UnorderedMap_ByteCompare:          # @Deep_UnorderedMap_ByteCompare
.seh_proc Deep_UnorderedMap_ByteCompare
# %bb.0:
	subq	$40, %rsp
	.seh_stackalloc 40
	.seh_endprologue
	callq	memcmp
	xorl	%ecx, %ecx
	testl	%eax, %eax
	sete	%cl
	movl	%ecx, %eax
	addq	$40, %rsp
	retq
	.seh_endproc
                                        # -- End function
	.def	 _Deep_UnorderedMap_Create;
	.scl	2;
	.type	32;
	.endef
	.section	.rdata,"dr"
	.p2align	4                               # -- Begin function _Deep_UnorderedMap_Create
.LCPI3_0:
	.long	13                              # 0xd
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	0                               # 0x0
	.text
	.globl	_Deep_UnorderedMap_Create
	.p2align	4, 0x90
_Deep_UnorderedMap_Create:              # @_Deep_UnorderedMap_Create
.seh_proc _Deep_UnorderedMap_Create
# %bb.0:
	pushq	%rsi
	.seh_pushreg %rsi
	subq	$32, %rsp
	.seh_stackalloc 32
	.seh_endprologue
	movq	%rcx, %rsi
	movq	88(%rsp), %r10
	movq	80(%rsp), %rax
	movq	%rdx, 40(%rcx)
	movq	%r8, 48(%rcx)
	movq	%rax, 56(%rcx)
	movq	%r10, 72(%rcx)
	movq	%r9, 64(%rcx)
	movaps	.LCPI3_0(%rip), %xmm0           # xmm0 = [13,0,0,0]
	movups	%xmm0, 24(%rcx)
	leaq	31(%r9), %rcx
	movq	%rcx, %rax
	orq	%r9, %rax
	shrq	$32, %rax
	je	.LBB3_1
# %bb.2:
	movq	%rcx, %rax
	xorl	%edx, %edx
	divq	%r9
	jmp	.LBB3_3
.LBB3_1:
	movl	%ecx, %eax
	xorl	%edx, %edx
	divl	%r9d
                                        # kill: def $edx killed $edx def $rdx
.LBB3_3:
	subq	%rdx, %rcx
	movq	%rcx, 80(%rsi)
	addq	%r10, %rcx
	addq	$7, %rcx
	movq	%rcx, %rax
	orq	%r10, %rax
	shrq	$32, %rax
	je	.LBB3_4
# %bb.5:
	movq	%rcx, %rax
	xorl	%edx, %edx
	divq	%r10
	jmp	.LBB3_6
.LBB3_4:
	movl	%ecx, %eax
	xorl	%edx, %edx
	divl	%r10d
                                        # kill: def $edx killed $edx def $rdx
.LBB3_6:
	subq	%rdx, %rcx
	movq	%rcx, 88(%rsi)
	movl	$13, %ecx
	movl	$8, %edx
	callq	calloc
	movq	%rax, (%rsi)
	xorps	%xmm0, %xmm0
	movups	%xmm0, 8(%rsi)
	addq	$32, %rsp
	popq	%rsi
	retq
	.seh_endproc
                                        # -- End function
	.def	 _Deep_UnorderedMap_Free;
	.scl	2;
	.type	32;
	.endef
	.globl	_Deep_UnorderedMap_Free         # -- Begin function _Deep_UnorderedMap_Free
	.p2align	4, 0x90
_Deep_UnorderedMap_Free:                # @_Deep_UnorderedMap_Free
.seh_proc _Deep_UnorderedMap_Free
# %bb.0:
	pushq	%rsi
	.seh_pushreg %rsi
	pushq	%rdi
	.seh_pushreg %rdi
	subq	$40, %rsp
	.seh_stackalloc 40
	.seh_endprologue
	movq	%rcx, %rsi
	movq	8(%rcx), %rcx
	testq	%rcx, %rcx
	je	.LBB4_2
	.p2align	4, 0x90
.LBB4_1:                                # =>This Inner Loop Header: Depth=1
	movq	8(%rcx), %rdi
	callq	free
	movq	%rdi, %rcx
	testq	%rdi, %rdi
	jne	.LBB4_1
.LBB4_2:
	movq	(%rsi), %rcx
	addq	$40, %rsp
	popq	%rdi
	popq	%rsi
	jmp	free                            # TAILCALL
	.seh_endproc
                                        # -- End function
	.def	 _Deep_UnorderedMap_ReHash;
	.scl	2;
	.type	32;
	.endef
	.globl	_Deep_UnorderedMap_ReHash       # -- Begin function _Deep_UnorderedMap_ReHash
	.p2align	4, 0x90
_Deep_UnorderedMap_ReHash:              # @_Deep_UnorderedMap_ReHash
.seh_proc _Deep_UnorderedMap_ReHash
# %bb.0:
	pushq	%rsi
	.seh_pushreg %rsi
	pushq	%rdi
	.seh_pushreg %rdi
	pushq	%rbx
	.seh_pushreg %rbx
	subq	$32, %rsp
	.seh_stackalloc 32
	.seh_endprologue
	movq	24(%rcx), %rdi
	cmpq	32(%rcx), %rdi
	ja	.LBB5_11
# %bb.1:
	movq	%rcx, %rsi
	addq	%rdi, %rdi
	movl	$8, %edx
	movq	%rdi, %rcx
	callq	calloc
	testq	%rax, %rax
	je	.LBB5_11
# %bb.2:
	movq	%rax, %rbx
	movq	(%rsi), %rcx
	callq	free
	movq	%rdi, 24(%rsi)
	movq	%rbx, (%rsi)
	movq	8(%rsi), %rcx
	testq	%rcx, %rcx
	je	.LBB5_11
	.p2align	4, 0x90
.LBB5_3:                                # =>This Loop Header: Depth=1
                                        #     Child Loop BB5_8 Depth 2
	movq	24(%rcx), %rax
	movq	%rax, %rdx
	orq	%rdi, %rdx
	shrq	$32, %rdx
	je	.LBB5_4
# %bb.5:                                #   in Loop: Header=BB5_3 Depth=1
	xorl	%edx, %edx
	divq	%rdi
	movq	(%rbx,%rdx,8), %rax
	testq	%rax, %rax
	jne	.LBB5_8
	jmp	.LBB5_7
	.p2align	4, 0x90
.LBB5_4:                                #   in Loop: Header=BB5_3 Depth=1
                                        # kill: def $eax killed $eax killed $rax
	xorl	%edx, %edx
	divl	%edi
                                        # kill: def $edx killed $edx def $rdx
	movq	(%rbx,%rdx,8), %rax
	testq	%rax, %rax
	je	.LBB5_7
	.p2align	4, 0x90
.LBB5_8:                                #   Parent Loop BB5_3 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movq	%rax, %rdx
	movq	(%rax), %rax
	testq	%rax, %rax
	jne	.LBB5_8
	jmp	.LBB5_9
	.p2align	4, 0x90
.LBB5_7:                                #   in Loop: Header=BB5_3 Depth=1
	leaq	(%rbx,%rdx,8), %rdx
.LBB5_9:                                #   in Loop: Header=BB5_3 Depth=1
	movq	%rcx, (%rdx)
	movq	$0, (%rcx)
	movq	8(%rcx), %rcx
	testq	%rcx, %rcx
	je	.LBB5_11
# %bb.10:                               #   in Loop: Header=BB5_3 Depth=1
	movq	(%rsi), %rbx
	jmp	.LBB5_3
.LBB5_11:
	addq	$32, %rsp
	popq	%rbx
	popq	%rdi
	popq	%rsi
	retq
	.seh_endproc
                                        # -- End function
	.def	 _Deep_UnorderedMap_Insert;
	.scl	2;
	.type	32;
	.endef
	.globl	_Deep_UnorderedMap_Insert       # -- Begin function _Deep_UnorderedMap_Insert
	.p2align	4, 0x90
_Deep_UnorderedMap_Insert:              # @_Deep_UnorderedMap_Insert
.seh_proc _Deep_UnorderedMap_Insert
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
	subq	$40, %rsp
	.seh_stackalloc 40
	.seh_endprologue
	movq	%r8, %r15
	movq	%rdx, %r14
	movq	%rcx, %rsi
	movq	24(%rcx), %r12
	cmpq	32(%rcx), %r12
	ja	.LBB6_11
# %bb.1:
	leaq	(%r12,%r12), %rbx
	movl	$8, %edx
	movq	%rbx, %rcx
	callq	calloc
	testq	%rax, %rax
	je	.LBB6_11
# %bb.2:
	movq	%rax, %rdi
	movq	(%rsi), %rcx
	callq	free
	movq	%rbx, 24(%rsi)
	movq	%rdi, (%rsi)
	movq	8(%rsi), %rcx
	testq	%rcx, %rcx
	je	.LBB6_10
	.p2align	4, 0x90
.LBB6_3:                                # =>This Loop Header: Depth=1
                                        #     Child Loop BB6_6 Depth 2
	movq	24(%rcx), %rax
	movq	%rax, %rdx
	orq	%rbx, %rdx
	shrq	$32, %rdx
	je	.LBB6_5
# %bb.4:                                #   in Loop: Header=BB6_3 Depth=1
	xorl	%edx, %edx
	divq	%rbx
	movq	(%rdi,%rdx,8), %rax
	testq	%rax, %rax
	jne	.LBB6_6
	jmp	.LBB6_7
	.p2align	4, 0x90
.LBB6_5:                                #   in Loop: Header=BB6_3 Depth=1
                                        # kill: def $eax killed $eax killed $rax
	xorl	%edx, %edx
	divl	%ebx
                                        # kill: def $edx killed $edx def $rdx
	movq	(%rdi,%rdx,8), %rax
	testq	%rax, %rax
	je	.LBB6_7
	.p2align	4, 0x90
.LBB6_6:                                #   Parent Loop BB6_3 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movq	%rax, %rdx
	movq	(%rax), %rax
	testq	%rax, %rax
	jne	.LBB6_6
	jmp	.LBB6_8
	.p2align	4, 0x90
.LBB6_7:                                #   in Loop: Header=BB6_3 Depth=1
	leaq	(%rdi,%rdx,8), %rdx
.LBB6_8:                                #   in Loop: Header=BB6_3 Depth=1
	movq	%rcx, (%rdx)
	movq	$0, (%rcx)
	movq	8(%rcx), %rcx
	testq	%rcx, %rcx
	je	.LBB6_10
# %bb.9:                                #   in Loop: Header=BB6_3 Depth=1
	movq	(%rsi), %rdi
	jmp	.LBB6_3
.LBB6_10:
	movq	%rbx, %r12
.LBB6_11:
	movq	%r14, %rax
	orq	%r12, %rax
	shrq	$32, %rax
	je	.LBB6_17
# %bb.12:
	movq	%r14, %rax
	xorl	%edx, %edx
	divq	%r12
	movq	%rdx, %rbx
	movq	(%rsi), %rdi
	movq	(%rdi,%rbx,8), %rax
	testq	%rax, %rax
	je	.LBB6_18
	.p2align	4, 0x90
.LBB6_13:                               # =>This Inner Loop Header: Depth=1
	movq	%rax, %rbx
	movq	80(%rsi), %rcx
	addq	%rax, %rcx
	movq	48(%rsi), %r8
	movq	%r15, %rdx
	callq	*40(%rsi)
	testl	%eax, %eax
	jne	.LBB6_24
# %bb.14:                               #   in Loop: Header=BB6_13 Depth=1
	movq	(%rbx), %rax
	testq	%rax, %rax
	jne	.LBB6_13
# %bb.15:
	movq	56(%rsi), %rcx
	addq	88(%rsi), %rcx
	callq	malloc
	testq	%rax, %rax
	je	.LBB6_28
# %bb.16:
	leaq	88(%rsi), %rdi
	movq	%rax, (%rbx)
	movq	%r14, 24(%rax)
	xorps	%xmm0, %xmm0
	movaps	%xmm0, (%rax)
	movq	16(%rsi), %rax
	movq	(%rbx), %rcx
	movq	%rax, 16(%rcx)
	addq	$1, 32(%rsi)
	movq	%rcx, 8(%rax)
	movq	%rcx, 16(%rsi)
	addq	80(%rsi), %rcx
	movq	48(%rsi), %r8
	movq	%r15, %rdx
	callq	memcpy
	movq	(%rbx), %rbx
	jmp	.LBB6_25
.LBB6_17:
	movl	%r14d, %eax
	xorl	%edx, %edx
	divl	%r12d
	movl	%edx, %ebx
	movq	(%rsi), %rdi
	movq	(%rdi,%rbx,8), %rax
	testq	%rax, %rax
	jne	.LBB6_13
.LBB6_18:
	movq	56(%rsi), %rcx
	addq	88(%rsi), %rcx
	callq	malloc
	testq	%rax, %rax
	je	.LBB6_28
# %bb.19:
	movq	%rax, (%rdi,%rbx,8)
	movq	(%rsi), %rax
	movq	(%rax,%rbx,8), %rcx
	movq	%r14, 24(%rcx)
	movq	$0, (%rcx)
	movq	(%rax,%rbx,8), %rcx
	movq	$0, 8(%rcx)
	movq	16(%rsi), %rcx
	movq	(%rax,%rbx,8), %rdx
	movq	%rcx, 16(%rdx)
	addq	$1, 32(%rsi)
	testq	%rcx, %rcx
	je	.LBB6_21
# %bb.20:
	movq	(%rax,%rbx,8), %rdx
	movq	%rdx, 8(%rcx)
.LBB6_21:
	movq	(%rax,%rbx,8), %rcx
	movq	%rcx, 16(%rsi)
	cmpq	$0, 8(%rsi)
	jne	.LBB6_23
# %bb.22:
	movq	(%rax,%rbx,8), %rcx
	movq	%rcx, 8(%rsi)
.LBB6_23:
	leaq	88(%rsi), %rdi
	movq	(%rax,%rbx,8), %rcx
	addq	80(%rsi), %rcx
	movq	48(%rsi), %r8
	movq	%r15, %rdx
	callq	memcpy
	movq	(%rsi), %rax
	movq	(%rax,%rbx,8), %rbx
	jmp	.LBB6_25
.LBB6_24:
	addq	$88, %rsi
	movq	%rsi, %rdi
.LBB6_25:
	addq	(%rdi), %rbx
	jmp	.LBB6_26
.LBB6_28:
	xorl	%ebx, %ebx
.LBB6_26:
	movq	%rbx, %rax
	addq	$40, %rsp
	popq	%rbx
	popq	%rdi
	popq	%rsi
	popq	%r12
	popq	%r14
	popq	%r15
	retq
	.seh_endproc
                                        # -- End function
	.def	 _Deep_UnorderedMap_Erase;
	.scl	2;
	.type	32;
	.endef
	.globl	_Deep_UnorderedMap_Erase        # -- Begin function _Deep_UnorderedMap_Erase
	.p2align	4, 0x90
_Deep_UnorderedMap_Erase:               # @_Deep_UnorderedMap_Erase
.seh_proc _Deep_UnorderedMap_Erase
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
	subq	$32, %rsp
	.seh_stackalloc 32
	.seh_endprologue
	movq	%r8, %r15
	movq	%rdx, %rax
	movq	%rcx, %rsi
	movq	24(%rcx), %rcx
	orq	%rcx, %rdx
	shrq	$32, %rdx
	je	.LBB7_1
# %bb.2:
	xorl	%edx, %edx
	divq	%rcx
	movq	%rdx, %r14
	movq	(%rsi), %rax
	movq	(%rax,%r14,8), %rdi
	testq	%rdi, %rdi
	jne	.LBB7_4
	jmp	.LBB7_14
.LBB7_1:
                                        # kill: def $eax killed $eax killed $rax
	xorl	%edx, %edx
	divl	%ecx
	movl	%edx, %r14d
	movq	(%rsi), %rax
	movq	(%rax,%r14,8), %rdi
	testq	%rdi, %rdi
	je	.LBB7_14
.LBB7_4:
	movq	80(%rsi), %rcx
	addq	%rdi, %rcx
	movq	48(%rsi), %r8
	movq	%r15, %rdx
	callq	*40(%rsi)
	testl	%eax, %eax
	je	.LBB7_13
# %bb.5:
	movq	(%rdi), %rax
	movq	(%rsi), %rcx
	movq	%rax, (%rcx,%r14,8)
	movq	16(%rdi), %rax
	testq	%rax, %rax
	je	.LBB7_10
.LBB7_9:
	movq	8(%rdi), %rcx
	movq	%rcx, 8(%rax)
.LBB7_10:
	movq	8(%rdi), %rcx
	testq	%rcx, %rcx
	je	.LBB7_12
# %bb.11:
	movq	%rax, 16(%rcx)
.LBB7_12:
	movq	%rdi, %rcx
	callq	free
	addq	$-1, 32(%rsi)
.LBB7_14:
	addq	$32, %rsp
	popq	%rbx
	popq	%rdi
	popq	%rsi
	popq	%r14
	popq	%r15
	retq
	.p2align	4, 0x90
.LBB7_6:                                #   in Loop: Header=BB7_13 Depth=1
	movq	80(%rsi), %rcx
	addq	%rdi, %rcx
	movq	48(%rsi), %r8
	movq	%r15, %rdx
	callq	*40(%rsi)
	testl	%eax, %eax
	jne	.LBB7_7
.LBB7_13:                               # =>This Inner Loop Header: Depth=1
	movq	%rdi, %rbx
	movq	(%rdi), %rdi
	testq	%rdi, %rdi
	jne	.LBB7_6
	jmp	.LBB7_14
.LBB7_7:
	movq	(%rdi), %rax
	movq	%rax, (%rbx)
	movq	16(%rdi), %rax
	testq	%rax, %rax
	jne	.LBB7_9
	jmp	.LBB7_10
	.seh_endproc
                                        # -- End function
	.addrsig
