	.text
	.def	 @feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.file	"Deep_Network_Server.c"
	.def	 Deep_Network_Server_Start;
	.scl	2;
	.type	32;
	.endef
	.globl	Deep_Network_Server_Start       # -- Begin function Deep_Network_Server_Start
	.p2align	4, 0x90
Deep_Network_Server_Start:              # @Deep_Network_Server_Start
.seh_proc Deep_Network_Server_Start
# %bb.0:
	pushq	%rsi
	.seh_pushreg %rsi
	pushq	%rdi
	.seh_pushreg %rdi
	subq	$40, %rsp
	.seh_stackalloc 40
	.seh_endprologue
	movl	%edx, %esi
	movq	%rcx, %rdi
	movl	40(%rcx), %ecx
	shlq	$3, %rcx
	callq	malloc
	movq	%rax, 32(%rdi)
	movq	%rdi, %rcx
	movl	%esi, %edx
	addq	$40, %rsp
	popq	%rdi
	popq	%rsi
	jmp	Deep_Network_Socket_Bind        # TAILCALL
	.seh_endproc
                                        # -- End function
	.def	 Deep_Network_Server_Close;
	.scl	2;
	.type	32;
	.endef
	.globl	Deep_Network_Server_Close       # -- Begin function Deep_Network_Server_Close
	.p2align	4, 0x90
Deep_Network_Server_Close:              # @Deep_Network_Server_Close
.seh_proc Deep_Network_Server_Close
# %bb.0:
	pushq	%rsi
	.seh_pushreg %rsi
	subq	$32, %rsp
	.seh_stackalloc 32
	.seh_endprologue
	movq	%rcx, %rsi
	callq	Deep_Network_Socket_Close
	movq	32(%rsi), %rcx
	addq	$32, %rsp
	popq	%rsi
	jmp	free                            # TAILCALL
	.seh_endproc
                                        # -- End function
	.def	 Deep_Network_Server_Tick;
	.scl	2;
	.type	32;
	.endef
	.globl	Deep_Network_Server_Tick        # -- Begin function Deep_Network_Server_Tick
	.p2align	4, 0x90
Deep_Network_Server_Tick:               # @Deep_Network_Server_Tick
.seh_proc Deep_Network_Server_Tick
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
	pushq	%rbp
	.seh_pushreg %rbp
	pushq	%rbx
	.seh_pushreg %rbx
	subq	$32, %rsp
	.seh_stackalloc 32
	.seh_endprologue
	movq	%rcx, %rsi
	callq	Deep_Network_Socket_GetRemainingBytes
	testl	%eax, %eax
	jle	.LBB2_6
# %bb.1:
	leaq	16(%rsi), %r12
	movq	__imp_ntohl(%rip), %r14
	movq	__imp_ntohs(%rip), %r15
	jmp	.LBB2_2
	.p2align	4, 0x90
.LBB2_5:                                #   in Loop: Header=BB2_2 Depth=1
	movq	%rsi, %rcx
	callq	Deep_Network_Socket_GetRemainingBytes
	testl	%eax, %eax
	jle	.LBB2_6
.LBB2_2:                                # =>This Inner Loop Header: Depth=1
	movq	32(%rsi), %rdx
	movl	40(%rsi), %r8d
	movq	%rsi, %rcx
	movq	%r12, %r9
	callq	Deep_Network_Socket_Receive
	testl	%eax, %eax
	jle	.LBB2_5
# %bb.3:                                #   in Loop: Header=BB2_2 Depth=1
	movl	%eax, %ebx
	movl	20(%rsi), %ecx
	callq	*%r14
	movl	%eax, %ebp
	movzwl	18(%rsi), %ecx
	callq	*%r15
	movq	48(%rsi), %rdi
	testq	%rdi, %rdi
	je	.LBB2_5
# %bb.4:                                #   in Loop: Header=BB2_2 Depth=1
	movzwl	%ax, %r9d
	movq	32(%rsi), %rcx
	movl	%ebx, %edx
	movl	%ebp, %r8d
	callq	*%rdi
	jmp	.LBB2_5
.LBB2_6:
	addq	$32, %rsp
	popq	%rbx
	popq	%rbp
	popq	%rdi
	popq	%rsi
	popq	%r12
	popq	%r14
	popq	%r15
	retq
	.seh_endproc
                                        # -- End function
	.section	.rdata,"dr"
	.globl	Deep_Network_Server_Default     # @Deep_Network_Server_Default
	.p2align	3
Deep_Network_Server_Default:
	.zero	16
	.zero	16
	.quad	0
	.long	256                             # 0x100
	.zero	4
	.quad	0

	.addrsig
