	.text
	.def	 @feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.file	"Deep_DynArray.c"
	.def	 _Deep_DynArray_Create;
	.scl	2;
	.type	32;
	.endef
	.globl	_Deep_DynArray_Create           # -- Begin function _Deep_DynArray_Create
	.p2align	4, 0x90
_Deep_DynArray_Create:                  # @_Deep_DynArray_Create
# %bb.0:
	xorps	%xmm0, %xmm0
	movups	%xmm0, (%rcx)
	movq	$0, 16(%rcx)
	movq	%rdx, 32(%rcx)
	movb	$1, 24(%rcx)
	retq
                                        # -- End function
	.def	 _Deep_DynArray_Free;
	.scl	2;
	.type	32;
	.endef
	.globl	_Deep_DynArray_Free             # -- Begin function _Deep_DynArray_Free
	.p2align	4, 0x90
_Deep_DynArray_Free:                    # @_Deep_DynArray_Free
.seh_proc _Deep_DynArray_Free
# %bb.0:
	pushq	%rsi
	.seh_pushreg %rsi
	subq	$32, %rsp
	.seh_stackalloc 32
	.seh_endprologue
	testq	%rcx, %rcx
	je	.LBB1_2
# %bb.1:
	movq	%rcx, %rsi
	movq	16(%rcx), %rcx
	callq	free
	movq	$0, 16(%rsi)
.LBB1_2:
	addq	$32, %rsp
	popq	%rsi
	retq
	.seh_endproc
                                        # -- End function
	.def	 _Deep_DynArray_ErrorFree;
	.scl	2;
	.type	32;
	.endef
	.globl	_Deep_DynArray_ErrorFree        # -- Begin function _Deep_DynArray_ErrorFree
	.p2align	4, 0x90
_Deep_DynArray_ErrorFree:               # @_Deep_DynArray_ErrorFree
.seh_proc _Deep_DynArray_ErrorFree
# %bb.0:
	pushq	%rsi
	.seh_pushreg %rsi
	subq	$32, %rsp
	.seh_stackalloc 32
	.seh_endprologue
	cmpb	$0, 24(%rcx)
	je	.LBB2_2
# %bb.1:
	movq	%rcx, %rsi
	movq	16(%rcx), %rcx
	callq	free
	movq	$0, 16(%rsi)
.LBB2_2:
	addq	$32, %rsp
	popq	%rsi
	retq
	.seh_endproc
                                        # -- End function
	.def	 _Deep_DynArray_Push;
	.scl	2;
	.type	32;
	.endef
	.section	.rdata,"dr"
	.p2align	4                               # -- Begin function _Deep_DynArray_Push
.LCPI3_0:
	.long	0x3fc00000                      # float 1.5
.LCPI3_1:
	.long	0x5f000000                      # float 9.22337203E+18
	.zero	8
.LCPI3_2:
	.quad	1                               # 0x1
	.quad	1                               # 0x1
	.text
	.globl	_Deep_DynArray_Push
	.p2align	4, 0x90
_Deep_DynArray_Push:                    # @_Deep_DynArray_Push
.seh_proc _Deep_DynArray_Push
# %bb.0:
	pushq	%rsi
	.seh_pushreg %rsi
	pushq	%rdi
	.seh_pushreg %rdi
	subq	$40, %rsp
	.seh_stackalloc 40
	.seh_endprologue
	movq	%rcx, %rsi
	movq	16(%rcx), %rax
	testq	%rax, %rax
	je	.LBB3_4
# %bb.1:
	movq	(%rsi), %rdx
	cmpq	8(%rsi), %rdx
	jne	.LBB3_6
# %bb.2:
	testq	%rdx, %rdx
	js	.LBB3_7
# %bb.3:
	cvtsi2ss	%rdx, %xmm0
	jmp	.LBB3_8
.LBB3_4:
	movq	32(%rsi), %rcx
	callq	malloc
	testq	%rax, %rax
	je	.LBB3_13
# %bb.5:
	movq	%rax, 16(%rsi)
	movaps	.LCPI3_2(%rip), %xmm0           # xmm0 = [1,1]
	movups	%xmm0, (%rsi)
	jmp	.LBB3_14
.LBB3_6:
	leaq	1(%rdx), %rcx
	movq	%rcx, (%rsi)
	imulq	32(%rsi), %rdx
	addq	%rdx, %rax
	jmp	.LBB3_14
.LBB3_7:
	movq	%rdx, %rdi
	shrq	%rdi
	movl	%edx, %ecx
	andl	$1, %ecx
	orq	%rdi, %rcx
	cvtsi2ss	%rcx, %xmm0
	addss	%xmm0, %xmm0
.LBB3_8:
	mulss	.LCPI3_0(%rip), %xmm0
	cvttss2si	%xmm0, %r8
	movq	%r8, %rdi
	sarq	$63, %rdi
	subss	.LCPI3_1(%rip), %xmm0
	cvttss2si	%xmm0, %rcx
	andq	%rdi, %rcx
	orq	%r8, %rcx
	xorl	%edi, %edi
	cmpq	%rcx, %rdx
	sete	%dil
	addq	%rcx, %rdi
	movq	32(%rsi), %rdx
	imulq	%rdi, %rdx
	movq	%rax, %rcx
	callq	realloc
	testq	%rax, %rax
	je	.LBB3_11
# %bb.9:
	movq	%rax, %rcx
	movq	%rax, 16(%rsi)
	movq	%rdi, 8(%rsi)
	movq	(%rsi), %rax
	leaq	1(%rax), %rdx
	movq	%rdx, (%rsi)
	imulq	32(%rsi), %rax
	addq	%rcx, %rax
	jmp	.LBB3_14
.LBB3_11:
	cmpb	$0, 24(%rsi)
	je	.LBB3_13
# %bb.12:
	movq	16(%rsi), %rcx
	callq	free
	movq	$0, 16(%rsi)
.LBB3_13:
	xorl	%eax, %eax
.LBB3_14:
	addq	$40, %rsp
	popq	%rdi
	popq	%rsi
	retq
	.seh_endproc
                                        # -- End function
	.def	 _Deep_DynArray_Pop;
	.scl	2;
	.type	32;
	.endef
	.globl	_Deep_DynArray_Pop              # -- Begin function _Deep_DynArray_Pop
	.p2align	4, 0x90
_Deep_DynArray_Pop:                     # @_Deep_DynArray_Pop
# %bb.0:
	cmpq	$0, 16(%rcx)
	je	.LBB4_3
# %bb.1:
	movq	(%rcx), %rax
	testq	%rax, %rax
	je	.LBB4_3
# %bb.2:
	addq	$-1, %rax
	movq	%rax, (%rcx)
.LBB4_3:
	retq
                                        # -- End function
	.def	 _Deep_DynArray_RemoveAt;
	.scl	2;
	.type	32;
	.endef
	.globl	_Deep_DynArray_RemoveAt         # -- Begin function _Deep_DynArray_RemoveAt
	.p2align	4, 0x90
_Deep_DynArray_RemoveAt:                # @_Deep_DynArray_RemoveAt
.seh_proc _Deep_DynArray_RemoveAt
# %bb.0:
	pushq	%rsi
	.seh_pushreg %rsi
	subq	$32, %rsp
	.seh_stackalloc 32
	.seh_endprologue
	movq	16(%rcx), %rax
	testq	%rax, %rax
	je	.LBB5_7
# %bb.1:
	movq	%rcx, %rsi
	movq	(%rcx), %rcx
	cmpq	$2, %rcx
	jb	.LBB5_7
# %bb.2:
	testq	%rdx, %rdx
	je	.LBB5_7
# %bb.3:
	cmpq	%rdx, %rcx
	jbe	.LBB5_7
# %bb.4:
	movq	%rdx, %r8
	notq	%r8
	addq	%rcx, %r8
	je	.LBB5_6
# %bb.5:
	movq	32(%rsi), %r9
	movq	%r9, %rcx
	imulq	%rdx, %rcx
	addq	%rax, %rcx
	addq	$1, %rdx
	imulq	%r9, %rdx
	addq	%rax, %rdx
	imulq	%r9, %r8
	callq	memmove
	movq	(%rsi), %rcx
.LBB5_6:
	addq	$-1, %rcx
	movq	%rcx, (%rsi)
.LBB5_7:
	addq	$32, %rsp
	popq	%rsi
	retq
	.seh_endproc
                                        # -- End function
	.def	 _Deep_DynArray_Shrink;
	.scl	2;
	.type	32;
	.endef
	.globl	_Deep_DynArray_Shrink           # -- Begin function _Deep_DynArray_Shrink
	.p2align	4, 0x90
_Deep_DynArray_Shrink:                  # @_Deep_DynArray_Shrink
.seh_proc _Deep_DynArray_Shrink
# %bb.0:
	pushq	%rsi
	.seh_pushreg %rsi
	pushq	%rdi
	.seh_pushreg %rdi
	subq	$40, %rsp
	.seh_stackalloc 40
	.seh_endprologue
	movq	%rcx, %rsi
	movq	16(%rcx), %rcx
	testq	%rcx, %rcx
	je	.LBB6_8
# %bb.1:
	movq	(%rsi), %rdi
	cmpq	8(%rsi), %rdi
	je	.LBB6_8
# %bb.2:
	testq	%rdi, %rdi
	je	.LBB6_7
# %bb.3:
	movq	32(%rsi), %rdx
	imulq	%rdi, %rdx
	callq	realloc
	testq	%rax, %rax
	je	.LBB6_5
# %bb.4:
	movq	%rax, 16(%rsi)
	movq	%rdi, 8(%rsi)
	jmp	.LBB6_8
.LBB6_7:
	addq	$8, %rsi
	callq	free
	xorps	%xmm0, %xmm0
	movups	%xmm0, (%rsi)
	jmp	.LBB6_8
.LBB6_5:
	cmpb	$0, 24(%rsi)
	je	.LBB6_8
# %bb.6:
	movq	16(%rsi), %rcx
	callq	free
	movq	$0, 16(%rsi)
.LBB6_8:
	addq	$40, %rsp
	popq	%rdi
	popq	%rsi
	retq
	.seh_endproc
                                        # -- End function
	.def	 _Deep_DynArray_Reserve;
	.scl	2;
	.type	32;
	.endef
	.globl	_Deep_DynArray_Reserve          # -- Begin function _Deep_DynArray_Reserve
	.p2align	4, 0x90
_Deep_DynArray_Reserve:                 # @_Deep_DynArray_Reserve
.seh_proc _Deep_DynArray_Reserve
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
	movq	%rdx, %rdi
	movq	%rcx, %rsi
	movq	(%rcx), %rbx
	addq	%rdx, %rbx
	cmpq	8(%rcx), %rbx
	jbe	.LBB7_3
# %bb.1:
	movq	16(%rsi), %rcx
	movq	32(%rsi), %rdx
	imulq	%rbx, %rdx
	callq	realloc
	testq	%rax, %rax
	je	.LBB7_4
# %bb.2:
	movq	%rax, 16(%rsi)
	movq	%rbx, 8(%rsi)
.LBB7_3:
	movq	%rdi, (%rsi)
.LBB7_6:
	addq	$32, %rsp
	popq	%rbx
	popq	%rdi
	popq	%rsi
	retq
.LBB7_4:
	cmpb	$0, 24(%rsi)
	je	.LBB7_6
# %bb.5:
	movq	16(%rsi), %rcx
	callq	free
	movq	$0, 16(%rsi)
	jmp	.LBB7_6
	.seh_endproc
                                        # -- End function
	.addrsig
