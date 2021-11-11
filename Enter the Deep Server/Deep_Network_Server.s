	.file	"Deep_Network_Server.c"
 # GNU C11 (Rev1, Built by MSYS2 project) version 11.2.0 (x86_64-w64-mingw32)
 #	compiled by GNU C version 11.2.0, GMP version 6.2.1, MPFR version 4.1.0-p13, MPC version 1.2.1, isl version isl-0.24-GMP

 # GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
 # options passed: -mtune=generic -march=x86-64 -O3 -std=c11
	.text
	.p2align 4
	.globl	Deep_Network_Server_Start
	.def	Deep_Network_Server_Start;	.scl	2;	.type	32;	.endef
	.seh_proc	Deep_Network_Server_Start
Deep_Network_Server_Start:
	pushq	%r12	 #
	.seh_pushreg	%r12
	pushq	%rbx	 #
	.seh_pushreg	%rbx
	subq	$40, %rsp	 #,
	.seh_stackalloc	40
	.seh_endprologue
 # Deep_Network_Server.c:11: {
	movq	%rcx, %r12	 # tmp95, deepServer
 # Deep_Network_Server.c:12: 	deepServer->buffer = malloc(deepServer->maxBufferSize * sizeof(unsigned char*));
	movl	40(%rcx), %ecx	 # deepServer_8(D)->maxBufferSize, deepServer_8(D)->maxBufferSize
 # Deep_Network_Server.c:11: {
	movl	%edx, %ebx	 # tmp96, port
 # Deep_Network_Server.c:12: 	deepServer->buffer = malloc(deepServer->maxBufferSize * sizeof(unsigned char*));
	salq	$3, %rcx	 #, tmp92
	call	malloc	 #
 # Deep_Network_Server.c:13: 	Deep_Network_Socket_Bind(&deepServer->socket, port);
	movzwl	%bx, %edx	 # port, port
	movq	%r12, %rcx	 # deepServer,
 # Deep_Network_Server.c:12: 	deepServer->buffer = malloc(deepServer->maxBufferSize * sizeof(unsigned char*));
	movq	%rax, 32(%r12)	 # tmp97, deepServer_8(D)->buffer
 # Deep_Network_Server.c:14: }
	addq	$40, %rsp	 #,
	popq	%rbx	 #
	popq	%r12	 #
 # Deep_Network_Server.c:13: 	Deep_Network_Socket_Bind(&deepServer->socket, port);
	jmp	Deep_Network_Socket_Bind	 #
	.seh_endproc
	.p2align 4
	.globl	Deep_Network_Server_Close
	.def	Deep_Network_Server_Close;	.scl	2;	.type	32;	.endef
	.seh_proc	Deep_Network_Server_Close
Deep_Network_Server_Close:
	pushq	%rbx	 #
	.seh_pushreg	%rbx
	subq	$32, %rsp	 #,
	.seh_stackalloc	32
	.seh_endprologue
 # Deep_Network_Server.c:17: {
	movq	%rcx, %rbx	 # tmp86, deepServer
 # Deep_Network_Server.c:18: 	Deep_Network_Socket_Close(&deepServer->socket);
	call	Deep_Network_Socket_Close	 #
 # Deep_Network_Server.c:19: 	free(deepServer->buffer);
	movq	32(%rbx), %rcx	 # deepServer_3(D)->buffer, deepServer_3(D)->buffer
 # Deep_Network_Server.c:20: }
	addq	$32, %rsp	 #,
	popq	%rbx	 #
 # Deep_Network_Server.c:19: 	free(deepServer->buffer);
	jmp	free	 #
	.seh_endproc
	.p2align 4
	.globl	Deep_Network_Server_Tick
	.def	Deep_Network_Server_Tick;	.scl	2;	.type	32;	.endef
	.seh_proc	Deep_Network_Server_Tick
Deep_Network_Server_Tick:
	pushq	%r12	 #
	.seh_pushreg	%r12
	pushq	%rdi	 #
	.seh_pushreg	%rdi
	pushq	%rsi	 #
	.seh_pushreg	%rsi
	pushq	%rbx	 #
	.seh_pushreg	%rbx
	subq	$40, %rsp	 #,
	.seh_stackalloc	40
	.seh_endprologue
 # Deep_Network_Server.c:23: {
	movq	%rcx, %rbx	 # tmp111, deepServer
 # Deep_Network_Server.c:26: 		int bytesReceived = Deep_Network_Socket_Receive(&deepServer->socket, deepServer->buffer, deepServer->maxBufferSize, &deepServer->from);
	leaq	16(%rcx), %rsi	 #, tmp107
 # Deep_Network_Server.c:24: 	while (Deep_Network_Socket_GetRemainingBytes(&deepServer->socket) > 0)
	jmp	.L6	 #
	.p2align 4,,10
	.p2align 3
.L8:
 # Deep_Network_Server.c:26: 		int bytesReceived = Deep_Network_Socket_Receive(&deepServer->socket, deepServer->buffer, deepServer->maxBufferSize, &deepServer->from);
	movq	32(%rbx), %rdx	 # deepServer_17(D)->buffer, deepServer_17(D)->buffer
	movl	40(%rbx), %r8d	 # deepServer_17(D)->maxBufferSize,
	movq	%rsi, %r9	 # tmp107,
	movq	%rbx, %rcx	 # deepServer,
	call	Deep_Network_Socket_Receive	 #
	movl	%eax, %r12d	 # tmp112, bytesReceived
 # Deep_Network_Server.c:27: 		if (bytesReceived > 0)
	testl	%eax, %eax	 # bytesReceived
	jg	.L12	 #,
.L6:
 # Deep_Network_Server.c:24: 	while (Deep_Network_Socket_GetRemainingBytes(&deepServer->socket) > 0)
	movq	%rbx, %rcx	 # deepServer,
	call	Deep_Network_Socket_GetRemainingBytes	 #
 # Deep_Network_Server.c:24: 	while (Deep_Network_Socket_GetRemainingBytes(&deepServer->socket) > 0)
	testl	%eax, %eax	 # tmp115
	jg	.L8	 #,
 # Deep_Network_Server.c:35: }
	addq	$40, %rsp	 #,
	popq	%rbx	 #
	popq	%rsi	 #
	popq	%rdi	 #
	popq	%r12	 #
	ret	
	.p2align 4,,10
	.p2align 3
.L12:
 # Deep_Network_Server.c:29: 			unsigned int fromAddress = ntohl(deepServer->from.sa_in.sin_addr.s_addr);
	movl	20(%rbx), %ecx	 # deepServer_17(D)->from.sa_in.sin_addr.S_un.S_addr, deepServer_17(D)->from.sa_in.sin_addr.S_un.S_addr
	call	*__imp_ntohl(%rip)	 #
 # Deep_Network_Server.c:30: 			unsigned int fromPort = ntohs(deepServer->from.sa_in.sin_port);
	movzwl	18(%rbx), %ecx	 # deepServer_17(D)->from.sa_in.sin_port, deepServer_17(D)->from.sa_in.sin_port
 # Deep_Network_Server.c:29: 			unsigned int fromAddress = ntohl(deepServer->from.sa_in.sin_addr.s_addr);
	movl	%eax, %edi	 # tmp113, fromAddress
 # Deep_Network_Server.c:30: 			unsigned int fromPort = ntohs(deepServer->from.sa_in.sin_port);
	call	*__imp_ntohs(%rip)	 #
 # Deep_Network_Server.c:32: 			if (deepServer->OnReceiveHandle) deepServer->OnReceiveHandle(deepServer->buffer, bytesReceived, fromAddress, fromPort);
	movq	48(%rbx), %r10	 # deepServer_17(D)->OnReceiveHandle, _10
 # Deep_Network_Server.c:32: 			if (deepServer->OnReceiveHandle) deepServer->OnReceiveHandle(deepServer->buffer, bytesReceived, fromAddress, fromPort);
	testq	%r10, %r10	 # _10
	je	.L6	 #,
 # Deep_Network_Server.c:32: 			if (deepServer->OnReceiveHandle) deepServer->OnReceiveHandle(deepServer->buffer, bytesReceived, fromAddress, fromPort);
	movq	32(%rbx), %rcx	 # deepServer_17(D)->buffer, deepServer_17(D)->buffer
	movzwl	%ax, %r9d	 # _9,
	movl	%edi, %r8d	 # fromAddress,
	movl	%r12d, %edx	 # bytesReceived,
	call	*%r10	 # _10
	jmp	.L6	 #
	.seh_endproc
	.globl	Deep_Network_Server_Default
	.section .rdata,"dr"
	.align 32
Deep_Network_Server_Default:
 # maxBufferSize:
	.space 40
	.long	256
 # OnReceiveHandle:
	.space 4
	.quad	0
	.ident	"GCC: (Rev1, Built by MSYS2 project) 11.2.0"
	.def	malloc;	.scl	2;	.type	32;	.endef
	.def	Deep_Network_Socket_Bind;	.scl	2;	.type	32;	.endef
	.def	Deep_Network_Socket_Close;	.scl	2;	.type	32;	.endef
	.def	free;	.scl	2;	.type	32;	.endef
	.def	Deep_Network_Socket_Receive;	.scl	2;	.type	32;	.endef
	.def	Deep_Network_Socket_GetRemainingBytes;	.scl	2;	.type	32;	.endef
