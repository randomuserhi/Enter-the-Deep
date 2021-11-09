	.text
	.def	 @feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.file	"Deep.c"
	.def	 Deep_CheckMaxAllocationSize;
	.scl	2;
	.type	32;
	.endef
	.globl	Deep_CheckMaxAllocationSize     # -- Begin function Deep_CheckMaxAllocationSize
	.p2align	4, 0x90
Deep_CheckMaxAllocationSize:            # @Deep_CheckMaxAllocationSize
.seh_proc Deep_CheckMaxAllocationSize
# %bb.0:
	pushq	%rsi
	.seh_pushreg %rsi
	pushq	%rdi
	.seh_pushreg %rdi
	subq	$40, %rsp
	.seh_stackalloc 40
	.seh_endprologue
	movl	$1073741824, %edi               # imm = 0x40000000
	leaq	.L.str(%rip), %rsi
	.p2align	4, 0x90
.LBB0_1:                                # =>This Inner Loop Header: Depth=1
	movq	%rdi, %rdx
	shrq	$30, %rdx
	movq	%rsi, %rcx
	callq	printf
	addq	$1073741824, %rdi               # imm = 0x40000000
	jmp	.LBB0_1
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
	.section	.rdata,"dr"
.L.str:                                 # @.str
	.asciz	"Dynamically allocated %llu GBs\n"

	.addrsig
