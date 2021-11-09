	.text
	.def	 @feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.file	"Deep_String.c"
	.def	 Deep_String_Create;
	.scl	2;
	.type	32;
	.endef
	.globl	Deep_String_Create              # -- Begin function Deep_String_Create
	.p2align	4, 0x90
Deep_String_Create:                     # @Deep_String_Create
.seh_proc Deep_String_Create
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
	movq	%rdx, %rsi
	movq	%rcx, %rdi
	xorps	%xmm0, %xmm0
	movups	%xmm0, (%rcx)
	movq	$0, 16(%rcx)
	movq	$1, 32(%rcx)
	movb	$1, 24(%rcx)
	movq	%rdx, %rcx
	callq	strlen
	movq	%rax, %rbx
	addq	$1, %rbx
	movq	%rdi, %rcx
	movq	%rbx, %rdx
	callq	_Deep_DynArray_Reserve
	movq	16(%rdi), %rcx
	movq	%rsi, %rdx
	movq	%rbx, %r8
	addq	$32, %rsp
	popq	%rbx
	popq	%rdi
	popq	%rsi
	jmp	memcpy                          # TAILCALL
	.seh_endproc
                                        # -- End function
	.addrsig
