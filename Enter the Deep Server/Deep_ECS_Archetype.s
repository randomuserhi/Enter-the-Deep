	.text
	.def	 @feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.file	"Deep_ECS_Archetype.c"
	.def	 Deep_ECS_Archetype_Hash;
	.scl	2;
	.type	32;
	.endef
	.globl	Deep_ECS_Archetype_Hash         # -- Begin function Deep_ECS_Archetype_Hash
	.p2align	4, 0x90
Deep_ECS_Archetype_Hash:                # @Deep_ECS_Archetype_Hash
# %bb.0:
	movq	(%rcx), %r8
	testq	%r8, %r8
	je	.LBB0_1
# %bb.2:
	movl	$2654435769, %r9d               # imm = 0x9E3779B9
	movq	16(%rcx), %rax
	movq	(%rax), %r10
	movq	%r8, %rax
	cmpq	$1, %r8
	je	.LBB0_5
# %bb.3:
	movq	%r8, %r11
	andq	$-2, %r11
	negq	%r11
	movq	%r8, %rax
	.p2align	4, 0x90
.LBB0_4:                                # =>This Inner Loop Header: Depth=1
	movq	%rax, %rcx
	shlq	$6, %rcx
	movq	%rax, %rdx
	shrq	$2, %rdx
	addq	%r9, %rcx
	addq	%rdx, %rcx
	addq	%r10, %rcx
	xorq	%rax, %rcx
	movq	%rcx, %rax
	shlq	$6, %rax
	movq	%rcx, %rdx
	shrq	$2, %rdx
	addq	%r9, %rax
	addq	%rdx, %rax
	addq	%r10, %rax
	xorq	%rcx, %rax
	addq	$2, %r11
	jne	.LBB0_4
.LBB0_5:
	testb	$1, %r8b
	je	.LBB0_7
# %bb.6:
	movq	%rax, %r8
	shlq	$6, %r8
	addq	%r9, %r8
	movq	%rax, %rdx
	shrq	$2, %rdx
	addq	%r8, %rdx
	addq	%r10, %rdx
	xorq	%rdx, %rax
.LBB0_7:
	retq
.LBB0_1:
	xorl	%eax, %eax
	retq
                                        # -- End function
	.def	 Deep_ECS_Archetype_Create;
	.scl	2;
	.type	32;
	.endef
	.section	.rdata,"dr"
	.p2align	4                               # -- Begin function Deep_ECS_Archetype_Create
.LCPI1_0:
	.quad	2                               # 0x2
	.quad	2                               # 0x2
	.text
	.globl	Deep_ECS_Archetype_Create
	.p2align	4, 0x90
Deep_ECS_Archetype_Create:              # @Deep_ECS_Archetype_Create
.seh_proc Deep_ECS_Archetype_Create
# %bb.0:
	pushq	%rsi
	.seh_pushreg %rsi
	subq	$32, %rsp
	.seh_stackalloc 32
	.seh_endprologue
	movq	%rcx, %rsi
	movq	$8, 32(%rcx)
	movb	$1, 24(%rcx)
	xorps	%xmm0, %xmm0
	movups	%xmm0, 40(%rcx)
	movq	$0, 56(%rcx)
	movq	$8, 72(%rcx)
	movb	$1, 64(%rcx)
	movups	%xmm0, 80(%rcx)
	movq	$0, 96(%rcx)
	movq	$40, 112(%rcx)
	movb	$1, 104(%rcx)
	movl	$8, %ecx
	callq	malloc
	movq	$256, (%rax)                    # imm = 0x100
	movl	$16, %edx
	movq	%rax, %rcx
	callq	realloc
	movq	%rax, 16(%rsi)
	movaps	.LCPI1_0(%rip), %xmm0           # xmm0 = [2,2]
	movups	%xmm0, (%rsi)
	movq	$512, 8(%rax)                   # imm = 0x200
	addq	$32, %rsp
	popq	%rsi
	retq
	.seh_endproc
                                        # -- End function
	.addrsig
