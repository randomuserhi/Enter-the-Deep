	.text
	.def	 @feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.file	"Deep_Network_Socket.c"
	.def	 Deep_Network_IsBigEndian;
	.scl	2;
	.type	32;
	.endef
	.globl	Deep_Network_IsBigEndian        # -- Begin function Deep_Network_IsBigEndian
	.p2align	4, 0x90
Deep_Network_IsBigEndian:               # @Deep_Network_IsBigEndian
.seh_proc Deep_Network_IsBigEndian
# %bb.0:
	subq	$40, %rsp
	.seh_stackalloc 40
	.seh_endprologue
	movl	$1, %ecx
	callq	*__imp_htonl(%rip)
	xorl	%ecx, %ecx
	cmpl	$1, %eax
	sete	%cl
	movl	%ecx, %eax
	addq	$40, %rsp
	retq
	.seh_endproc
                                        # -- End function
	.def	 Deep_Network_InitializeSockets;
	.scl	2;
	.type	32;
	.endef
	.globl	Deep_Network_InitializeSockets  # -- Begin function Deep_Network_InitializeSockets
	.p2align	4, 0x90
Deep_Network_InitializeSockets:         # @Deep_Network_InitializeSockets
.seh_proc Deep_Network_InitializeSockets
# %bb.0:
	subq	$440, %rsp                      # imm = 0x1B8
	.seh_stackalloc 440
	.seh_endprologue
	leaq	32(%rsp), %rdx
	movw	$514, %cx                       # imm = 0x202
	callq	*__imp_WSAStartup(%rip)
	testl	%eax, %eax
	je	.LBB1_1
# %bb.2:
	callq	*__imp_WSAGetLastError(%rip)
	leaq	.L.str.1(%rip), %rcx
	movl	%eax, %edx
	callq	printf
	xorl	%eax, %eax
	addq	$440, %rsp                      # imm = 0x1B8
	retq
.LBB1_1:
	leaq	.Lstr(%rip), %rcx
	callq	puts
	movl	$1, %eax
	addq	$440, %rsp                      # imm = 0x1B8
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
	.def	 Deep_Network_ShutdownSockets;
	.scl	2;
	.type	32;
	.endef
	.globl	Deep_Network_ShutdownSockets    # -- Begin function Deep_Network_ShutdownSockets
	.p2align	4, 0x90
Deep_Network_ShutdownSockets:           # @Deep_Network_ShutdownSockets
.seh_proc Deep_Network_ShutdownSockets
# %bb.0:
	subq	$40, %rsp
	.seh_stackalloc 40
	.seh_endprologue
	callq	*__imp_WSACleanup(%rip)
	testl	%eax, %eax
	je	.LBB3_2
# %bb.1:
	callq	*__imp_WSAGetLastError(%rip)
	leaq	.L.str.3(%rip), %rcx
	movl	%eax, %edx
	callq	printf
	nop
	addq	$40, %rsp
	retq
.LBB3_2:
	leaq	.Lstr.18(%rip), %rcx
	addq	$40, %rsp
	jmp	puts                            # TAILCALL
	.seh_endproc
                                        # -- End function
	.def	 Deep_Network_Address_Format;
	.scl	2;
	.type	32;
	.endef
	.globl	Deep_Network_Address_Format     # -- Begin function Deep_Network_Address_Format
	.p2align	4, 0x90
Deep_Network_Address_Format:            # @Deep_Network_Address_Format
.seh_proc Deep_Network_Address_Format
# %bb.0:
	pushq	%rsi
	.seh_pushreg %rsi
	subq	$32, %rsp
	.seh_stackalloc 32
	.seh_endprologue
	movq	%rcx, %rsi
	movl	(%rcx), %ecx
	bswapl	%ecx
	movw	$2, 8(%rsi)
	callq	*__imp_htonl(%rip)
	movl	%eax, 12(%rsi)
	movzwl	4(%rsi), %ecx
	callq	*__imp_htons(%rip)
	movw	%ax, 10(%rsi)
	addq	$32, %rsp
	popq	%rsi
	retq
	.seh_endproc
                                        # -- End function
	.def	 Deep_Network_Address_Equal;
	.scl	2;
	.type	32;
	.endef
	.globl	Deep_Network_Address_Equal      # -- Begin function Deep_Network_Address_Equal
	.p2align	4, 0x90
Deep_Network_Address_Equal:             # @Deep_Network_Address_Equal
# %bb.0:
	movl	12(%rcx), %r8d
	xorl	%eax, %eax
	cmpl	12(%rdx), %r8d
	jne	.LBB5_2
# %bb.1:
	movzwl	10(%rcx), %ecx
	xorl	%eax, %eax
	cmpw	10(%rdx), %cx
	sete	%al
.LBB5_2:
	retq
                                        # -- End function
	.def	 Deep_Network_socket_GetPort;
	.scl	2;
	.type	32;
	.endef
	.globl	Deep_Network_socket_GetPort     # -- Begin function Deep_Network_socket_GetPort
	.p2align	4, 0x90
Deep_Network_socket_GetPort:            # @Deep_Network_socket_GetPort
# %bb.0:
	movzwl	8(%rcx), %eax
	retq
                                        # -- End function
	.def	 Deep_Network_Socket_Open;
	.scl	2;
	.type	32;
	.endef
	.globl	Deep_Network_Socket_Open        # -- Begin function Deep_Network_Socket_Open
	.p2align	4, 0x90
Deep_Network_Socket_Open:               # @Deep_Network_Socket_Open
.seh_proc Deep_Network_Socket_Open
# %bb.0:
	pushq	%rsi
	.seh_pushreg %rsi
	subq	$80, %rsp
	.seh_stackalloc 80
	.seh_endprologue
	movq	%rcx, %rsi
	movl	$2, %ecx
	movl	$2, %edx
	movl	$17, %r8d
	callq	*__imp_socket(%rip)
	movq	%rax, (%rsi)
	cmpq	$-1, %rax
	je	.LBB7_1
# %bb.2:
	leaq	.Lstr.19(%rip), %rcx
	callq	puts
	movl	$0, 76(%rsp)
	movl	$0, 72(%rsp)
	movq	(%rsi), %rcx
	xorps	%xmm0, %xmm0
	movups	%xmm0, 56(%rsp)
	leaq	72(%rsp), %rax
	movq	%rax, 48(%rsp)
	movl	$0, 40(%rsp)
	movq	$0, 32(%rsp)
	leaq	76(%rsp), %r8
	movl	$-1744830452, %edx              # imm = 0x9800000C
	movl	$4, %r9d
	callq	*__imp_WSAIoctl(%rip)
	xorl	%esi, %esi
	jmp	.LBB7_3
.LBB7_1:
	callq	*__imp_WSAGetLastError(%rip)
	movl	%eax, %esi
	leaq	.L.str.4(%rip), %rcx
	movl	%eax, %edx
	callq	printf
.LBB7_3:
	movl	%esi, %eax
	addq	$80, %rsp
	popq	%rsi
	retq
	.seh_endproc
                                        # -- End function
	.def	 Deep_Network_Socket_Close;
	.scl	2;
	.type	32;
	.endef
	.globl	Deep_Network_Socket_Close       # -- Begin function Deep_Network_Socket_Close
	.p2align	4, 0x90
Deep_Network_Socket_Close:              # @Deep_Network_Socket_Close
.seh_proc Deep_Network_Socket_Close
# %bb.0:
	pushq	%rsi
	.seh_pushreg %rsi
	subq	$32, %rsp
	.seh_stackalloc 32
	.seh_endprologue
	movq	%rcx, %rsi
	movq	(%rcx), %rcx
	cmpq	$-1, %rcx
	je	.LBB8_1
# %bb.2:
	callq	*__imp_closesocket(%rip)
	cmpl	$-1, %eax
	je	.LBB8_3
# %bb.4:
	leaq	.Lstr.20(%rip), %rcx
	callq	puts
	movq	$-1, (%rsi)
	jmp	.LBB8_5
.LBB8_1:
	leaq	.Lstr.21(%rip), %rcx
	callq	puts
.LBB8_5:
	xorl	%esi, %esi
	jmp	.LBB8_6
.LBB8_3:
	callq	*__imp_WSAGetLastError(%rip)
	movl	%eax, %esi
	leaq	.L.str.7(%rip), %rcx
	movl	%eax, %edx
	callq	printf
.LBB8_6:
	movl	%esi, %eax
	addq	$32, %rsp
	popq	%rsi
	retq
	.seh_endproc
                                        # -- End function
	.def	 Deep_Network_Socket_Bind;
	.scl	2;
	.type	32;
	.endef
	.globl	Deep_Network_Socket_Bind        # -- Begin function Deep_Network_Socket_Bind
	.p2align	4, 0x90
Deep_Network_Socket_Bind:               # @Deep_Network_Socket_Bind
.seh_proc Deep_Network_Socket_Bind
# %bb.0:
	pushq	%rsi
	.seh_pushreg %rsi
	subq	$80, %rsp
	.seh_stackalloc 80
	.seh_endprologue
	movq	%rcx, %rsi
	movw	$2, 48(%rsp)
	movl	$0, 52(%rsp)
	movl	%edx, %ecx
	callq	*__imp_htons(%rip)
	movw	%ax, 50(%rsp)
	movq	(%rsi), %rcx
	leaq	48(%rsp), %rdx
	movl	$16, %r8d
	callq	*__imp_bind(%rip)
	cmpl	$-1, %eax
	je	.LBB9_1
# %bb.2:
	leaq	.Lstr.22(%rip), %rcx
	callq	puts
	movl	$16, 44(%rsp)
	movq	(%rsi), %rcx
	leaq	64(%rsp), %rdx
	leaq	44(%rsp), %r8
	callq	*__imp_getsockname(%rip)
	testl	%eax, %eax
	je	.LBB9_4
# %bb.3:
	leaq	.Lstr.25(%rip), %rcx
	callq	puts
	jmp	.LBB9_5
.LBB9_1:
	callq	*__imp_WSAGetLastError(%rip)
	movl	%eax, %esi
	leaq	.L.str.9(%rip), %rcx
	movl	%eax, %edx
	callq	printf
	jmp	.LBB9_6
.LBB9_4:
	movzwl	66(%rsp), %ecx
	callq	*__imp_ntohs(%rip)
	movw	%ax, 8(%rsi)
	movzwl	%ax, %edx
	leaq	.L.str.12(%rip), %rcx
	callq	printf
.LBB9_5:
	movl	$1, 40(%rsp)
	movq	(%rsi), %rcx
	leaq	40(%rsp), %r8
	movl	$-2147195266, %edx              # imm = 0x8004667E
	callq	*__imp_ioctlsocket(%rip)
	xorl	%esi, %esi
	testl	%eax, %eax
	setne	%sil
	leaq	.Lstr.23(%rip), %rax
	leaq	.Lstr.24(%rip), %rcx
	cmoveq	%rax, %rcx
	negl	%esi
	callq	puts
.LBB9_6:
	movl	%esi, %eax
	addq	$80, %rsp
	popq	%rsi
	retq
	.seh_endproc
                                        # -- End function
	.def	 Deep_Network_Socket_GetRemainingBytes;
	.scl	2;
	.type	32;
	.endef
	.globl	Deep_Network_Socket_GetRemainingBytes # -- Begin function Deep_Network_Socket_GetRemainingBytes
	.p2align	4, 0x90
Deep_Network_Socket_GetRemainingBytes:  # @Deep_Network_Socket_GetRemainingBytes
.seh_proc Deep_Network_Socket_GetRemainingBytes
# %bb.0:
	subq	$40, %rsp
	.seh_stackalloc 40
	.seh_endprologue
	movq	(%rcx), %rcx
	leaq	36(%rsp), %r8
	movl	$1074030207, %edx               # imm = 0x4004667F
	callq	*__imp_ioctlsocket(%rip)
	testl	%eax, %eax
	je	.LBB10_2
# %bb.1:
	callq	*__imp_WSAGetLastError(%rip)
	leaq	.L.str.15(%rip), %rcx
	movl	%eax, %edx
	callq	printf
	movl	$-1, %eax
	addq	$40, %rsp
	retq
.LBB10_2:
	movl	36(%rsp), %eax
	addq	$40, %rsp
	retq
	.seh_endproc
                                        # -- End function
	.def	 Deep_Network_Socket_Send;
	.scl	2;
	.type	32;
	.endef
	.globl	Deep_Network_Socket_Send        # -- Begin function Deep_Network_Socket_Send
	.p2align	4, 0x90
Deep_Network_Socket_Send:               # @Deep_Network_Socket_Send
.seh_proc Deep_Network_Socket_Send
# %bb.0:
	pushq	%rsi
	.seh_pushreg %rsi
	pushq	%rdi
	.seh_pushreg %rdi
	subq	$56, %rsp
	.seh_stackalloc 56
	.seh_endprologue
	movl	%r8d, %edi
	movq	(%rcx), %rcx
	movq	%r9, 32(%rsp)
	movl	$16, 40(%rsp)
	xorl	%esi, %esi
	xorl	%r9d, %r9d
	callq	*__imp_sendto(%rip)
	cmpl	%edi, %eax
	je	.LBB11_2
# %bb.1:
	callq	*__imp_WSAGetLastError(%rip)
	movl	%eax, %esi
	leaq	.L.str.16(%rip), %rcx
	movl	%eax, %edx
	callq	printf
.LBB11_2:
	movl	%esi, %eax
	addq	$56, %rsp
	popq	%rdi
	popq	%rsi
	retq
	.seh_endproc
                                        # -- End function
	.def	 Deep_Network_Socket_Receive;
	.scl	2;
	.type	32;
	.endef
	.globl	Deep_Network_Socket_Receive     # -- Begin function Deep_Network_Socket_Receive
	.p2align	4, 0x90
Deep_Network_Socket_Receive:            # @Deep_Network_Socket_Receive
.seh_proc Deep_Network_Socket_Receive
# %bb.0:
	pushq	%rsi
	.seh_pushreg %rsi
	subq	$64, %rsp
	.seh_stackalloc 64
	.seh_endprologue
	movl	$16, 60(%rsp)
	movq	(%rcx), %rcx
	leaq	60(%rsp), %rax
	movq	%rax, 40(%rsp)
	movq	%r9, 32(%rsp)
	xorl	%r9d, %r9d
	callq	*__imp_recvfrom(%rip)
	movl	%eax, %esi
	testl	%eax, %eax
	jns	.LBB12_3
# %bb.1:
	callq	*__imp_WSAGetLastError(%rip)
	movl	$-1, %esi
	cmpl	$10035, %eax                    # imm = 0x2733
	je	.LBB12_3
# %bb.2:
	leaq	.L.str.17(%rip), %rcx
	movl	%eax, %edx
	callq	printf
.LBB12_3:
	movl	%esi, %eax
	addq	$64, %rsp
	popq	%rsi
	retq
	.seh_endproc
                                        # -- End function
	.section	.rdata,"dr"
	.globl	Deep_Network_Address_Default    # @Deep_Network_Address_Default
	.p2align	2
Deep_Network_Address_Default:
	.byte	127                             # 0x7f
	.byte	0                               # 0x0
	.byte	0                               # 0x0
	.byte	1                               # 0x1
	.short	0                               # 0x0
	.zero	2
	.zero	16

	.globl	Deep_Network_Socket_Default     # @Deep_Network_Socket_Default
	.p2align	3
Deep_Network_Socket_Default:
	.quad	-1                              # 0xffffffffffffffff
	.short	57687                           # 0xe157
	.zero	6

.L.str.1:                               # @.str.1
	.asciz	"WSA failed to initialize with error = %i\n"

.L.str.3:                               # @.str.3
	.asciz	"WSA failed to cleaup with error = %i.\n"

.L.str.4:                               # @.str.4
	.asciz	"Socket function failed with error = %i.\n"

.L.str.7:                               # @.str.7
	.asciz	"Failed to close socket with error = %i.\n"

.L.str.9:                               # @.str.9
	.asciz	"Socket failed to bind with error %i.\n"

.L.str.12:                              # @.str.12
	.asciz	"Socket bound to port %i.\n"

.L.str.15:                              # @.str.15
	.asciz	"Failed to get remaining bytes with error = %i.\n"

.L.str.16:                              # @.str.16
	.asciz	"Failed to send packet to destination with error = %i.\n"

.L.str.17:                              # @.str.17
	.asciz	"Failed to receive packet with error = %i.\n"

.Lstr:                                  # @str
	.asciz	"WSA Initialized."

.Lstr.18:                               # @str.18
	.asciz	"WSA successfully cleaned up."

.Lstr.19:                               # @str.19
	.asciz	"Socket function succeeded."

.Lstr.20:                               # @str.20
	.asciz	"Closed socket successfully."

.Lstr.21:                               # @str.21
	.asciz	"Socket already closed / SocketFD is invalid."

.Lstr.22:                               # @str.22
	.asciz	"Socket bound successfully."

.Lstr.23:                               # @str.23
	.asciz	"Successfully set socket to non-blocking."

.Lstr.24:                               # @str.24
	.asciz	"Failed to set socket to non-blocking."

.Lstr.25:                               # @str.25
	.asciz	"Failed to get socket details."

	.addrsig
