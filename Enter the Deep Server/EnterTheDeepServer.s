	.text
	.def	 @feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.file	"EnterTheDeepServer.c"
	.def	 Cleanup;
	.scl	2;
	.type	32;
	.endef
	.globl	Cleanup                         # -- Begin function Cleanup
	.p2align	4, 0x90
Cleanup:                                # @Cleanup
# %bb.0:
	jmp	Deep_Network_ShutdownSockets    # TAILCALL
                                        # -- End function
	.def	 ExitHandler;
	.scl	2;
	.type	32;
	.endef
	.globl	ExitHandler                     # -- Begin function ExitHandler
	.p2align	4, 0x90
ExitHandler:                            # @ExitHandler
.seh_proc ExitHandler
# %bb.0:
	subq	$40, %rsp
	.seh_stackalloc 40
	.seh_endprologue
	callq	Deep_Network_ShutdownSockets
	xorl	%ecx, %ecx
	callq	exit
	int3
	.seh_endproc
                                        # -- End function
	.def	 OnReceive;
	.scl	2;
	.type	32;
	.endef
	.globl	OnReceive                       # -- Begin function OnReceive
	.p2align	4, 0x90
OnReceive:                              # @OnReceive
.seh_proc OnReceive
# %bb.0:
	subq	$40, %rsp
	.seh_stackalloc 40
	.seh_endprologue
	movl	(%rcx), %edx
	leaq	.L.str(%rip), %rcx
	callq	printf
	nop
	addq	$40, %rsp
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
	.def	 main;
	.scl	2;
	.type	32;
	.endef
	.section	.rdata,"dr"
	.p2align	3                               # -- Begin function main
.LCPI4_0:
	.quad	0x4034000000000000              # double 20
	.text
	.globl	main
	.p2align	4, 0x90
main:                                   # @main
.seh_proc main
# %bb.0:
	pushq	%rbp
	.seh_pushreg %rbp
	pushq	%r14
	.seh_pushreg %r14
	pushq	%rsi
	.seh_pushreg %rsi
	pushq	%rdi
	.seh_pushreg %rdi
	pushq	%rbx
	.seh_pushreg %rbx
	subq	$464, %rsp                      # imm = 0x1D0
	.seh_stackalloc 464
	leaq	128(%rsp), %rbp
	.seh_setframe %rbp, 128
	.seh_endprologue
	callq	__main
	leaq	ExitHandler(%rip), %rcx
	movl	$1, %edx
	callq	*__imp_SetConsoleCtrlHandler(%rip)
	testl	%eax, %eax
	je	.LBB4_3
# %bb.1:
	leaq	.L.str.1(%rip), %rcx
	movl	$10, %edx
	callq	printf
	pxor	%xmm0, %xmm0
	movdqa	%xmm0, 288(%rbp)
	movq	$0, 304(%rbp)
	movq	$1, 320(%rbp)
	movb	$1, 312(%rbp)
	leaq	288(%rbp), %rcx
	movl	$12, %edx
	callq	_Deep_DynArray_Reserve
	movq	304(%rbp), %rax
	movabsq	$8022916924116329800, %rcx      # imm = 0x6F57206F6C6C6548
	movq	%rcx, (%rax)
	movl	$6581362, 8(%rax)               # imm = 0x646C72
	movq	304(%rbp), %rcx
	callq	puts
	leaq	-96(%rbp), %rsi
	movq	%rsi, %rcx
	callq	Deep_ECS_Create
	movq	%rsi, %rcx
	callq	Deep_ECS_PrintHierarchy
	callq	getchar
	leaq	.L.str.4(%rip), %rcx
	movq	.LCPI4_0(%rip), %xmm1           # xmm1 = mem[0],zero
	pxor	%xmm0, %xmm0
	xorps	%xmm3, %xmm3
	movq	%xmm1, %rdx
	movq	%xmm1, %r8
	movdqa	%xmm1, %xmm2
	movq	%xmm0, %r9
	callq	printf
	callq	Deep_Network_IsBigEndian
	leaq	.L.str.5(%rip), %rcx
	movl	%eax, %edx
	callq	printf
	callq	Deep_Network_InitializeSockets
	movq	.refptr.Deep_Network_Server_Default(%rip), %rax
	movups	(%rax), %xmm0
	movups	16(%rax), %xmm1
	movups	32(%rax), %xmm2
	movaps	%xmm2, 224(%rbp)
	movaps	%xmm1, 208(%rbp)
	movaps	%xmm0, 192(%rbp)
	leaq	OnReceive(%rip), %rax
	movq	%rax, 240(%rbp)
	leaq	192(%rbp), %rsi
	movq	%rsi, %rcx
	callq	Deep_Network_Socket_Open
	movq	%rsi, %rcx
	movw	$-7849, %dx                     # imm = 0xE157
	callq	Deep_Network_Server_Start
	movzwl	200(%rbp), %edx
	leaq	.L.str.6(%rip), %rcx
	callq	printf
	movl	$10, 332(%rbp)
	movq	.L__const.main.addr+16(%rip), %rax
	movq	%rax, 272(%rbp)
	movups	.L__const.main.addr(%rip), %xmm0
	movaps	%xmm0, 256(%rbp)
	leaq	264(%rbp), %r14
	leaq	256(%rbp), %rbx
	leaq	332(%rbp), %rdi
	.p2align	4, 0x90
.LBB4_2:                                # =>This Inner Loop Header: Depth=1
	movq	%rsi, %rcx
	callq	Deep_Network_Server_Tick
	movq	%rbx, %rcx
	callq	Deep_Network_Address_Format
	movq	%rsi, %rcx
	movq	%rdi, %rdx
	movl	$4, %r8d
	movq	%r14, %r9
	callq	Deep_Network_Socket_Send
	jmp	.LBB4_2
.LBB4_3:
	movl	$1, %eax
	addq	$464, %rsp                      # imm = 0x1D0
	popq	%rbx
	popq	%rdi
	popq	%rsi
	popq	%r14
	popq	%rbp
	retq
	.seh_endproc
                                        # -- End function
	.section	.rdata,"dr"
.L.str:                                 # @.str
	.asciz	"Message received: %i\n"

.L.str.1:                               # @.str.1
	.asciz	"%i\n"

.L.str.2:                               # @.str.2
	.asciz	"Hello World"

.L.str.4:                               # @.str.4
	.asciz	"%f %f %f\n"

.L.str.5:                               # @.str.5
	.asciz	"IsBigEndian: %i.\n"

.L.str.6:                               # @.str.6
	.asciz	"Server started on port: %i.\n"

	.p2align	2                               # @__const.main.addr
.L__const.main.addr:
	.byte	127                             # 0x7f
	.byte	0                               # 0x0
	.byte	0                               # 0x0
	.byte	1                               # 0x1
	.short	56732                           # 0xdd9c
	.zero	2
	.zero	16

	.section	.rdata$.refptr.Deep_Network_Server_Default,"dr",discard,.refptr.Deep_Network_Server_Default
	.p2align	3
	.globl	.refptr.Deep_Network_Server_Default
.refptr.Deep_Network_Server_Default:
	.quad	Deep_Network_Server_Default
	.addrsig
	.addrsig_sym ExitHandler
	.addrsig_sym OnReceive
