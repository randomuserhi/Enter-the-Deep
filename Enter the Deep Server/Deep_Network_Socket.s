	.file	"Deep_Network_Socket.c"
 # GNU C11 (Rev1, Built by MSYS2 project) version 11.2.0 (x86_64-w64-mingw32)
 #	compiled by GNU C version 11.2.0, GMP version 6.2.1, MPFR version 4.1.0-p13, MPC version 1.2.1, isl version isl-0.24-GMP

 # GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
 # options passed: -mtune=generic -march=x86-64 -O3 -std=c11
	.text
	.p2align 4
	.def	printf;	.scl	3;	.type	32;	.endef
	.seh_proc	printf
printf:
	pushq	%r12	 #
	.seh_pushreg	%r12
	pushq	%rbx	 #
	.seh_pushreg	%rbx
	subq	$56, %rsp	 #,
	.seh_stackalloc	56
	.seh_endprologue
 # C:/msys64/mingw64/x86_64-w64-mingw32/include/stdio.h:371:   __builtin_va_list __local_argv; __builtin_va_start( __local_argv, __format );
	leaq	88(%rsp), %rbx	 #, tmp86
 # C:/msys64/mingw64/x86_64-w64-mingw32/include/stdio.h:369: {
	movq	%rdx, 88(%rsp)	 #,
	movq	%rcx, %r12	 # tmp89, __format
 # C:/msys64/mingw64/x86_64-w64-mingw32/include/stdio.h:372:   __retval = __mingw_vfprintf( stdout, __format, __local_argv );
	movl	$1, %ecx	 #,
 # C:/msys64/mingw64/x86_64-w64-mingw32/include/stdio.h:369: {
	movq	%r8, 96(%rsp)	 #,
	movq	%r9, 104(%rsp)	 #,
 # C:/msys64/mingw64/x86_64-w64-mingw32/include/stdio.h:371:   __builtin_va_list __local_argv; __builtin_va_start( __local_argv, __format );
	movq	%rbx, 40(%rsp)	 # tmp86, MEM[(char * *)&__local_argv]
 # C:/msys64/mingw64/x86_64-w64-mingw32/include/stdio.h:372:   __retval = __mingw_vfprintf( stdout, __format, __local_argv );
	call	*__imp___acrt_iob_func(%rip)	 #
	movq	%rbx, %r8	 # tmp86,
	movq	%r12, %rdx	 # __format,
	movq	%rax, %rcx	 # tmp90, _2
	call	__mingw_vfprintf	 #
 # C:/msys64/mingw64/x86_64-w64-mingw32/include/stdio.h:375: }
	addq	$56, %rsp	 #,
	popq	%rbx	 #
	popq	%r12	 #
	ret	
	.seh_endproc
	.p2align 4
	.globl	Deep_Network_IsBigEndian
	.def	Deep_Network_IsBigEndian;	.scl	2;	.type	32;	.endef
	.seh_proc	Deep_Network_IsBigEndian
Deep_Network_IsBigEndian:
	subq	$40, %rsp	 #,
	.seh_stackalloc	40
	.seh_endprologue
 # Deep_Network_Socket.c:14: 	return i == htonl(i);
	movl	$1, %ecx	 #,
	call	*__imp_htonl(%rip)	 #
 # Deep_Network_Socket.c:14: 	return i == htonl(i);
	cmpl	$1, %eax	 #, tmp89
	sete	%al	 #, tmp87
	movzbl	%al, %eax	 # tmp87, tmp87
 # Deep_Network_Socket.c:15: }
	addq	$40, %rsp	 #,
	ret	
	.seh_endproc
	.section .rdata,"dr"
.LC0:
	.ascii "WSA Initialized.\12\0"
	.align 8
.LC1:
	.ascii "WSA failed to initialize with error = %i\12\0"
	.text
	.p2align 4
	.globl	Deep_Network_InitializeSockets
	.def	Deep_Network_InitializeSockets;	.scl	2;	.type	32;	.endef
	.seh_proc	Deep_Network_InitializeSockets
Deep_Network_InitializeSockets:
	subq	$456, %rsp	 #,
	.seh_stackalloc	456
	.seh_endprologue
 # Deep_Network_Socket.c:20: 	if (WSAStartup(MAKEWORD(2, 2), &wsaData) == NO_ERROR)
	movl	$514, %ecx	 #,
	leaq	32(%rsp), %rdx	 #, tmp85
	call	*__imp_WSAStartup(%rip)	 #
 # Deep_Network_Socket.c:20: 	if (WSAStartup(MAKEWORD(2, 2), &wsaData) == NO_ERROR)
	testl	%eax, %eax	 # tmp91
	je	.L7	 #,
 # Deep_Network_Socket.c:25: 	printf("WSA failed to initialize with error = %i\n", WSAGetLastError());
	call	*__imp_WSAGetLastError(%rip)	 #
	leaq	.LC1(%rip), %rcx	 #, tmp89
	movl	%eax, %edx	 # tmp92, _2
	call	printf	 #
 # Deep_Network_Socket.c:26: 	return FALSE;
	xorl	%eax, %eax	 # <retval>
 # Deep_Network_Socket.c:27: }
	addq	$456, %rsp	 #,
	ret	
	.p2align 4,,10
	.p2align 3
.L7:
 # Deep_Network_Socket.c:22: 		printf("WSA Initialized.\n");
	leaq	.LC0(%rip), %rcx	 #, tmp87
	call	printf	 #
 # Deep_Network_Socket.c:23: 		return TRUE;
	movl	$1, %eax	 #, <retval>
 # Deep_Network_Socket.c:27: }
	addq	$456, %rsp	 #,
	ret	
	.seh_endproc
	.section .rdata,"dr"
.LC2:
	.ascii "WSA successfully cleaned up.\12\0"
	.align 8
.LC3:
	.ascii "WSA failed to cleaup with error = %i.\12\0"
	.text
	.p2align 4
	.globl	Deep_Network_ShutdownSockets
	.def	Deep_Network_ShutdownSockets;	.scl	2;	.type	32;	.endef
	.seh_proc	Deep_Network_ShutdownSockets
Deep_Network_ShutdownSockets:
	subq	$40, %rsp	 #,
	.seh_stackalloc	40
	.seh_endprologue
 # Deep_Network_Socket.c:31: 	const int result = WSACleanup();
	call	*__imp_WSACleanup(%rip)	 #
 # Deep_Network_Socket.c:32: 	if (result == NOERROR)
	testl	%eax, %eax	 # tmp88
	jne	.L9	 #,
 # Deep_Network_Socket.c:33: 		printf("WSA successfully cleaned up.\n");
	leaq	.LC2(%rip), %rcx	 #, tmp85
 # Deep_Network_Socket.c:36: }
	addq	$40, %rsp	 #,
 # Deep_Network_Socket.c:33: 		printf("WSA successfully cleaned up.\n");
	jmp	printf	 #
	.p2align 4,,10
	.p2align 3
.L9:
 # Deep_Network_Socket.c:35: 		printf("WSA failed to cleaup with error = %i.\n", WSAGetLastError());
	call	*__imp_WSAGetLastError(%rip)	 #
	leaq	.LC3(%rip), %rcx	 #, tmp87
	movl	%eax, %edx	 # tmp89, _1
 # Deep_Network_Socket.c:36: }
	addq	$40, %rsp	 #,
 # Deep_Network_Socket.c:35: 		printf("WSA failed to cleaup with error = %i.\n", WSAGetLastError());
	jmp	printf	 #
	.seh_endproc
	.p2align 4
	.globl	Deep_Network_Address_Format
	.def	Deep_Network_Address_Format;	.scl	2;	.type	32;	.endef
	.seh_proc	Deep_Network_Address_Format
Deep_Network_Address_Format:
	pushq	%rbx	 #
	.seh_pushreg	%rbx
	subq	$32, %rsp	 #,
	.seh_stackalloc	32
	.seh_endprologue
 # Deep_Network_Socket.c:42: 	address->sockAddr.sa_in.sin_family = AF_INET;
	movl	$2, %eax	 #,
 # Deep_Network_Socket.c:39: {
	movq	%rcx, %rbx	 # tmp93, address
	movl	(%rcx), %ecx	 # MEM <unsigned int> [(unsigned char *)address_20(D)], MEM <unsigned int> [(unsigned char *)address_20(D)]
 # Deep_Network_Socket.c:42: 	address->sockAddr.sa_in.sin_family = AF_INET;
	movw	%ax, 8(%rbx)	 #, address_20(D)->sockAddr.sa_in.sin_family
	bswap	%ecx		 # bswapdst_28
 # Deep_Network_Socket.c:43: 	address->sockAddr.sa_in.sin_addr.s_addr = htonl(BitAddress);
	call	*__imp_htonl(%rip)	 #
 # Deep_Network_Socket.c:44: 	address->sockAddr.sa_in.sin_port = htons(address->port);
	movzwl	4(%rbx), %ecx	 # address_20(D)->port, address_20(D)->port
 # Deep_Network_Socket.c:43: 	address->sockAddr.sa_in.sin_addr.s_addr = htonl(BitAddress);
	movl	%eax, 12(%rbx)	 # tmp94, address_20(D)->sockAddr.sa_in.sin_addr.S_un.S_addr
 # Deep_Network_Socket.c:44: 	address->sockAddr.sa_in.sin_port = htons(address->port);
	call	*__imp_htons(%rip)	 #
 # Deep_Network_Socket.c:44: 	address->sockAddr.sa_in.sin_port = htons(address->port);
	movw	%ax, 10(%rbx)	 # tmp95, address_20(D)->sockAddr.sa_in.sin_port
 # Deep_Network_Socket.c:45: }
	addq	$32, %rsp	 #,
	popq	%rbx	 #
	ret	
	.seh_endproc
	.p2align 4
	.globl	Deep_Network_Address_Equal
	.def	Deep_Network_Address_Equal;	.scl	2;	.type	32;	.endef
	.seh_proc	Deep_Network_Address_Equal
Deep_Network_Address_Equal:
	.seh_endprologue
 # Deep_Network_Socket.c:49: 	return (lhs->sockAddr.sa_in.sin_addr.s_addr == rhs->sockAddr.sa_in.sin_addr.s_addr) && (lhs->sockAddr.sa_in.sin_port == rhs->sockAddr.sa_in.sin_port);
	xorl	%eax, %eax	 # <retval>
	movl	12(%rdx), %r8d	 # rhs_8(D)->sockAddr.sa_in.sin_addr.S_un.S_addr, tmp98
	cmpl	%r8d, 12(%rcx)	 # tmp98, lhs_7(D)->sockAddr.sa_in.sin_addr.S_un.S_addr
	je	.L14	 #,
 # Deep_Network_Socket.c:50: }
	ret	
	.p2align 4,,10
	.p2align 3
.L14:
 # Deep_Network_Socket.c:49: 	return (lhs->sockAddr.sa_in.sin_addr.s_addr == rhs->sockAddr.sa_in.sin_addr.s_addr) && (lhs->sockAddr.sa_in.sin_port == rhs->sockAddr.sa_in.sin_port);
	movzwl	10(%rdx), %eax	 # rhs_8(D)->sockAddr.sa_in.sin_port, tmp99
	cmpw	%ax, 10(%rcx)	 # tmp99, lhs_7(D)->sockAddr.sa_in.sin_port
	sete	%al	 #, <retval>
	movzbl	%al, %eax	 # <retval>, <retval>
 # Deep_Network_Socket.c:50: }
	ret	
	.seh_endproc
	.p2align 4
	.globl	Deep_Network_socket_GetPort
	.def	Deep_Network_socket_GetPort;	.scl	2;	.type	32;	.endef
	.seh_proc	Deep_Network_socket_GetPort
Deep_Network_socket_GetPort:
	.seh_endprologue
 # Deep_Network_Socket.c:54: 	return deepSocket->port;
	movzwl	8(%rcx), %eax	 # deepSocket_2(D)->port, deepSocket_2(D)->port
 # Deep_Network_Socket.c:55: }
	ret	
	.seh_endproc
	.section .rdata,"dr"
	.align 8
.LC4:
	.ascii "Socket function failed with error = %i.\12\0"
.LC5:
	.ascii "Socket function succeeded.\12\0"
	.text
	.p2align 4
	.globl	Deep_Network_Socket_Open
	.def	Deep_Network_Socket_Open;	.scl	2;	.type	32;	.endef
	.seh_proc	Deep_Network_Socket_Open
Deep_Network_Socket_Open:
	pushq	%r12	 #
	.seh_pushreg	%r12
	pushq	%rbx	 #
	.seh_pushreg	%rbx
	subq	$104, %rsp	 #,
	.seh_stackalloc	104
	.seh_endprologue
 # Deep_Network_Socket.c:59: 	deepSocket->socketFD = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	movl	$17, %r8d	 #,
	movl	$2, %edx	 #,
 # Deep_Network_Socket.c:58: {
	movq	%rcx, %rbx	 # tmp94, deepSocket
 # Deep_Network_Socket.c:59: 	deepSocket->socketFD = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	movl	$2, %ecx	 #,
	call	*__imp_socket(%rip)	 #
 # Deep_Network_Socket.c:59: 	deepSocket->socketFD = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	movq	%rax, (%rbx)	 # _1, deepSocket_7(D)->socketFD
 # Deep_Network_Socket.c:61: 	if (deepSocket->socketFD == INVALID_SOCKET)
	cmpq	$-1, %rax	 #, _1
	je	.L19	 #,
 # Deep_Network_Socket.c:67: 	printf("Socket function succeeded.\n");
	leaq	.LC5(%rip), %rcx	 #, tmp89
 # Deep_Network_Socket.c:75: 	return DEEP_NETWORK_NOERROR;
	xorl	%r12d, %r12d	 # <retval>
 # Deep_Network_Socket.c:67: 	printf("Socket function succeeded.\n");
	call	printf	 #
 # Deep_Network_Socket.c:73: 	WSAIoctl(deepSocket->socketFD, SIO_UDP_CONNRESET, &bNewBehavior, sizeof bNewBehavior, NULL, 0, &dwBytesReturned, NULL, NULL);
	leaq	92(%rsp), %rax	 #, tmp91
	movq	(%rbx), %rcx	 # deepSocket_7(D)->socketFD,
 # Deep_Network_Socket.c:71: 	BOOL bNewBehavior = FALSE;
	movl	$0, 88(%rsp)	 #, bNewBehavior
 # Deep_Network_Socket.c:73: 	WSAIoctl(deepSocket->socketFD, SIO_UDP_CONNRESET, &bNewBehavior, sizeof bNewBehavior, NULL, 0, &dwBytesReturned, NULL, NULL);
	movq	%rax, 48(%rsp)	 # tmp91,
	movl	$4, %r9d	 #,
	leaq	88(%rsp), %r8	 #,
	movl	$-1744830452, %edx	 #,
 # Deep_Network_Socket.c:72: 	DWORD dwBytesReturned = 0;
	movl	$0, 92(%rsp)	 #, dwBytesReturned
 # Deep_Network_Socket.c:73: 	WSAIoctl(deepSocket->socketFD, SIO_UDP_CONNRESET, &bNewBehavior, sizeof bNewBehavior, NULL, 0, &dwBytesReturned, NULL, NULL);
	movq	$0, 64(%rsp)	 #,
	movq	$0, 56(%rsp)	 #,
	movl	$0, 40(%rsp)	 #,
	movq	$0, 32(%rsp)	 #,
	call	*__imp_WSAIoctl(%rip)	 #
 # Deep_Network_Socket.c:76: }
	movl	%r12d, %eax	 # <retval>,
	addq	$104, %rsp	 #,
	popq	%rbx	 #
	popq	%r12	 #
	ret	
	.p2align 4,,10
	.p2align 3
.L19:
 # Deep_Network_Socket.c:63: 		const int err = WSAGetLastError();
	call	*__imp_WSAGetLastError(%rip)	 #
 # Deep_Network_Socket.c:64: 		printf("Socket function failed with error = %i.\n", err);
	leaq	.LC4(%rip), %rcx	 #, tmp88
 # Deep_Network_Socket.c:63: 		const int err = WSAGetLastError();
	movl	%eax, %r12d	 # tmp96, <retval>
 # Deep_Network_Socket.c:64: 		printf("Socket function failed with error = %i.\n", err);
	movl	%eax, %edx	 # <retval>,
	call	printf	 #
 # Deep_Network_Socket.c:76: }
	movl	%r12d, %eax	 # <retval>,
	addq	$104, %rsp	 #,
	popq	%rbx	 #
	popq	%r12	 #
	ret	
	.seh_endproc
	.section .rdata,"dr"
	.align 8
.LC6:
	.ascii "Socket already closed / SocketFD is invalid.\12\0"
	.align 8
.LC7:
	.ascii "Failed to close socket with error = %i.\12\0"
.LC8:
	.ascii "Closed socket successfully.\12\0"
	.text
	.p2align 4
	.globl	Deep_Network_Socket_Close
	.def	Deep_Network_Socket_Close;	.scl	2;	.type	32;	.endef
	.seh_proc	Deep_Network_Socket_Close
Deep_Network_Socket_Close:
	pushq	%r12	 #
	.seh_pushreg	%r12
	pushq	%rbx	 #
	.seh_pushreg	%rbx
	subq	$40, %rsp	 #,
	.seh_stackalloc	40
	.seh_endprologue
 # Deep_Network_Socket.c:78: {
	movq	%rcx, %rbx	 # tmp93, deepSocket
 # Deep_Network_Socket.c:79: 	if (deepSocket->socketFD == INVALID_SOCKET)
	movq	(%rcx), %rcx	 # deepSocket_5(D)->socketFD, _1
 # Deep_Network_Socket.c:79: 	if (deepSocket->socketFD == INVALID_SOCKET)
	cmpq	$-1, %rcx	 #, _1
	je	.L24	 #,
 # Deep_Network_Socket.c:85: 	const int result = closesocket(deepSocket->socketFD);
	call	*__imp_closesocket(%rip)	 #
 # Deep_Network_Socket.c:86: 	if (result == SOCKET_ERROR)
	cmpl	$-1, %eax	 #, tmp94
	je	.L25	 #,
 # Deep_Network_Socket.c:92: 	printf("Closed socket successfully.\n");
	leaq	.LC8(%rip), %rcx	 #, tmp90
 # Deep_Network_Socket.c:94: 	return DEEP_NETWORK_NOERROR;
	xorl	%r12d, %r12d	 # <retval>
 # Deep_Network_Socket.c:92: 	printf("Closed socket successfully.\n");
	call	printf	 #
 # Deep_Network_Socket.c:95: }
	movl	%r12d, %eax	 # <retval>,
 # Deep_Network_Socket.c:93: 	deepSocket->socketFD = INVALID_SOCKET;
	movq	$-1, (%rbx)	 #, deepSocket_5(D)->socketFD
 # Deep_Network_Socket.c:95: }
	addq	$40, %rsp	 #,
	popq	%rbx	 #
	popq	%r12	 #
	ret	
	.p2align 4,,10
	.p2align 3
.L24:
 # Deep_Network_Socket.c:81: 		printf("Socket already closed / SocketFD is invalid.\n");
	leaq	.LC6(%rip), %rcx	 #, tmp86
 # Deep_Network_Socket.c:82: 		return DEEP_NETWORK_NOERROR;
	xorl	%r12d, %r12d	 # <retval>
 # Deep_Network_Socket.c:81: 		printf("Socket already closed / SocketFD is invalid.\n");
	call	printf	 #
 # Deep_Network_Socket.c:95: }
	movl	%r12d, %eax	 # <retval>,
	addq	$40, %rsp	 #,
	popq	%rbx	 #
	popq	%r12	 #
	ret	
	.p2align 4,,10
	.p2align 3
.L25:
 # Deep_Network_Socket.c:88: 		int err = WSAGetLastError();
	call	*__imp_WSAGetLastError(%rip)	 #
 # Deep_Network_Socket.c:89: 		printf("Failed to close socket with error = %i.\n", err);
	leaq	.LC7(%rip), %rcx	 #, tmp89
 # Deep_Network_Socket.c:88: 		int err = WSAGetLastError();
	movl	%eax, %r12d	 # tmp95, <retval>
 # Deep_Network_Socket.c:89: 		printf("Failed to close socket with error = %i.\n", err);
	movl	%eax, %edx	 # <retval>,
	call	printf	 #
 # Deep_Network_Socket.c:95: }
	movl	%r12d, %eax	 # <retval>,
	addq	$40, %rsp	 #,
	popq	%rbx	 #
	popq	%r12	 #
	ret	
	.seh_endproc
	.section .rdata,"dr"
	.align 8
.LC9:
	.ascii "Socket failed to bind with error %i.\12\0"
.LC10:
	.ascii "Socket bound successfully.\12\0"
	.align 8
.LC11:
	.ascii "Failed to get socket details.\12\0"
.LC12:
	.ascii "Socket bound to port %i.\12\0"
	.align 8
.LC13:
	.ascii "Failed to set socket to non-blocking.\12\0"
	.align 8
.LC14:
	.ascii "Successfully set socket to non-blocking.\12\0"
	.text
	.p2align 4
	.globl	Deep_Network_Socket_Bind
	.def	Deep_Network_Socket_Bind;	.scl	2;	.type	32;	.endef
	.seh_proc	Deep_Network_Socket_Bind
Deep_Network_Socket_Bind:
	pushq	%r12	 #
	.seh_pushreg	%r12
	pushq	%rbx	 #
	.seh_pushreg	%rbx
	subq	$88, %rsp	 #,
	.seh_stackalloc	88
	.seh_endprologue
 # Deep_Network_Socket.c:100: 	address.sin_family = AF_INET;
	movl	$2, %eax	 #,
 # Deep_Network_Socket.c:98: {
	movq	%rcx, %rbx	 # tmp117, deepSocket
 # Deep_Network_Socket.c:100: 	address.sin_family = AF_INET;
	movw	%ax, 48(%rsp)	 #, address.sin_family
 # Deep_Network_Socket.c:102: 	address.sin_port = htons(port);
	movzwl	%dx, %ecx	 # tmp118, port
 # Deep_Network_Socket.c:101: 	address.sin_addr.s_addr = INADDR_ANY;
	movl	$0, 52(%rsp)	 #, address.sin_addr.S_un.S_addr
 # Deep_Network_Socket.c:102: 	address.sin_port = htons(port);
	call	*__imp_htons(%rip)	 #
 # Deep_Network_Socket.c:104: 	if (bind(deepSocket->socketFD, (struct sockaddr*)&address, sizeof address) == SOCKET_ERROR)
	movq	(%rbx), %rcx	 # deepSocket_24(D)->socketFD,
	leaq	48(%rsp), %rdx	 #, tmp99
	movl	$16, %r8d	 #,
 # Deep_Network_Socket.c:102: 	address.sin_port = htons(port);
	movw	%ax, 50(%rsp)	 # tmp119, address.sin_port
 # Deep_Network_Socket.c:104: 	if (bind(deepSocket->socketFD, (struct sockaddr*)&address, sizeof address) == SOCKET_ERROR)
	call	*__imp_bind(%rip)	 #
 # Deep_Network_Socket.c:104: 	if (bind(deepSocket->socketFD, (struct sockaddr*)&address, sizeof address) == SOCKET_ERROR)
	cmpl	$-1, %eax	 #, tmp120
	je	.L33	 #,
 # Deep_Network_Socket.c:112: 		printf("Socket bound successfully.\n");
	leaq	.LC10(%rip), %rcx	 #, tmp103
	call	printf	 #
 # Deep_Network_Socket.c:115: 		socklen_t assignedAddressLen = sizeof assignedAddress;
	movl	$16, 40(%rsp)	 #, assignedAddressLen
 # Deep_Network_Socket.c:118: 		if (getsockname(deepSocket->socketFD, &assignedAddress.sa, &assignedAddressLen) != NO_ERROR)
	movq	(%rbx), %rcx	 # deepSocket_24(D)->socketFD,
	leaq	64(%rsp), %rdx	 #, tmp105
	leaq	40(%rsp), %r8	 #,
	call	*__imp_getsockname(%rip)	 #
 # Deep_Network_Socket.c:118: 		if (getsockname(deepSocket->socketFD, &assignedAddress.sa, &assignedAddressLen) != NO_ERROR)
	testl	%eax, %eax	 # tmp122
	jne	.L34	 #,
 # Deep_Network_Socket.c:122: 			deepSocket->port = ntohs(assignedAddress.sa_in.sin_port);
	movzwl	66(%rsp), %ecx	 # assignedAddress.sa_in.sin_port, assignedAddress.sa_in.sin_port
	call	*__imp_ntohs(%rip)	 #
 # Deep_Network_Socket.c:123: 			printf("Socket bound to port %i.\n", deepSocket->port);
	leaq	.LC12(%rip), %rcx	 #, tmp111
 # Deep_Network_Socket.c:122: 			deepSocket->port = ntohs(assignedAddress.sa_in.sin_port);
	movw	%ax, 8(%rbx)	 # _9, deepSocket_24(D)->port
 # Deep_Network_Socket.c:123: 			printf("Socket bound to port %i.\n", deepSocket->port);
	movzwl	%ax, %edx	 # _9, _9
	call	printf	 #
.L30:
 # Deep_Network_Socket.c:128: 		DWORD NonBlocking = 1;
	movl	$1, 44(%rsp)	 #, NonBlocking
 # Deep_Network_Socket.c:129: 		if (ioctlsocket(deepSocket->socketFD, FIONBIO, &NonBlocking) != 0)
	movq	(%rbx), %rcx	 # deepSocket_24(D)->socketFD,
	leaq	44(%rsp), %r8	 #,
	movl	$-2147195266, %edx	 #,
	call	*__imp_ioctlsocket(%rip)	 #
	movl	%eax, %r12d	 # tmp124, <retval>
 # Deep_Network_Socket.c:129: 		if (ioctlsocket(deepSocket->socketFD, FIONBIO, &NonBlocking) != 0)
	testl	%eax, %eax	 # <retval>
	je	.L31	 #,
 # Deep_Network_Socket.c:131: 			printf("Failed to set socket to non-blocking.\n");
	leaq	.LC13(%rip), %rcx	 #, tmp114
 # Deep_Network_Socket.c:132: 			return DEEP_NETWORK_ERROR;
	movl	$-1, %r12d	 #, <retval>
 # Deep_Network_Socket.c:131: 			printf("Failed to set socket to non-blocking.\n");
	call	printf	 #
 # Deep_Network_Socket.c:139: }
	movl	%r12d, %eax	 # <retval>,
	addq	$88, %rsp	 #,
	popq	%rbx	 #
	popq	%r12	 #
	ret	
	.p2align 4,,10
	.p2align 3
.L34:
 # Deep_Network_Socket.c:119: 			printf("Failed to get socket details.\n");
	leaq	.LC11(%rip), %rcx	 #, tmp107
	call	printf	 #
	jmp	.L30	 #
	.p2align 4,,10
	.p2align 3
.L31:
 # Deep_Network_Socket.c:135: 		printf("Successfully set socket to non-blocking.\n");
	leaq	.LC14(%rip), %rcx	 #, tmp115
	call	printf	 #
 # Deep_Network_Socket.c:139: }
	movl	%r12d, %eax	 # <retval>,
	addq	$88, %rsp	 #,
	popq	%rbx	 #
	popq	%r12	 #
	ret	
	.p2align 4,,10
	.p2align 3
.L33:
 # Deep_Network_Socket.c:106: 		const int err = WSAGetLastError();
	call	*__imp_WSAGetLastError(%rip)	 #
 # Deep_Network_Socket.c:107: 		printf("Socket failed to bind with error %i.\n", err);
	leaq	.LC9(%rip), %rcx	 #, tmp102
 # Deep_Network_Socket.c:106: 		const int err = WSAGetLastError();
	movl	%eax, %r12d	 # tmp121, <retval>
 # Deep_Network_Socket.c:107: 		printf("Socket failed to bind with error %i.\n", err);
	movl	%eax, %edx	 # <retval>,
	call	printf	 #
 # Deep_Network_Socket.c:139: }
	movl	%r12d, %eax	 # <retval>,
	addq	$88, %rsp	 #,
	popq	%rbx	 #
	popq	%r12	 #
	ret	
	.seh_endproc
	.section .rdata,"dr"
	.align 8
.LC15:
	.ascii "Failed to get remaining bytes with error = %i.\12\0"
	.text
	.p2align 4
	.globl	Deep_Network_Socket_GetRemainingBytes
	.def	Deep_Network_Socket_GetRemainingBytes;	.scl	2;	.type	32;	.endef
	.seh_proc	Deep_Network_Socket_GetRemainingBytes
Deep_Network_Socket_GetRemainingBytes:
	subq	$56, %rsp	 #,
	.seh_stackalloc	56
	.seh_endprologue
 # Deep_Network_Socket.c:144: 	const int result = ioctlsocket(deepSocket->socketFD, FIONREAD, &remainingBytes);
	movl	$1074030207, %edx	 #,
	movq	(%rcx), %rcx	 # deepSocket_7(D)->socketFD,
	leaq	44(%rsp), %r8	 #,
	call	*__imp_ioctlsocket(%rip)	 #
 # Deep_Network_Socket.c:145: 	if (result != NOERROR)
	testl	%eax, %eax	 # tmp94
	jne	.L38	 #,
 # Deep_Network_Socket.c:150: 	return remainingBytes;
	movl	44(%rsp), %eax	 # remainingBytes, <retval>
.L35:
 # Deep_Network_Socket.c:151: }
	addq	$56, %rsp	 #,
	ret	
.L38:
 # Deep_Network_Socket.c:147: 		printf("Failed to get remaining bytes with error = %i.\n", WSAGetLastError());
	call	*__imp_WSAGetLastError(%rip)	 #
	leaq	.LC15(%rip), %rcx	 #, tmp91
	movl	%eax, %edx	 # tmp95, _2
	call	printf	 #
 # Deep_Network_Socket.c:148: 		return DEEP_NETWORK_ERROR;
	movl	$-1, %eax	 #, <retval>
	jmp	.L35	 #
	.seh_endproc
	.section .rdata,"dr"
	.align 8
.LC16:
	.ascii "Failed to send packet to destination with error = %i.\12\0"
	.text
	.p2align 4
	.globl	Deep_Network_Socket_Send
	.def	Deep_Network_Socket_Send;	.scl	2;	.type	32;	.endef
	.seh_proc	Deep_Network_Socket_Send
Deep_Network_Socket_Send:
	pushq	%r12	 #
	.seh_pushreg	%r12
	pushq	%rbx	 #
	.seh_pushreg	%rbx
	subq	$56, %rsp	 #,
	.seh_stackalloc	56
	.seh_endprologue
 # Deep_Network_Socket.c:163: 	return DEEP_NETWORK_NOERROR;
	xorl	%r12d, %r12d	 # <retval>
 # Deep_Network_Socket.c:155: 	const int SentBytes = sendto(deepSocket->socketFD, data, dataSize, 0, &address->sa, sizeof *address);
	movq	%r9, 32(%rsp)	 # tmp97,
 # Deep_Network_Socket.c:154: {
	movl	%r8d, %ebx	 # tmp96, dataSize
 # Deep_Network_Socket.c:155: 	const int SentBytes = sendto(deepSocket->socketFD, data, dataSize, 0, &address->sa, sizeof *address);
	xorl	%r9d, %r9d	 #
	movl	$16, 40(%rsp)	 #,
	movq	(%rcx), %rcx	 # deepSocket_7(D)->socketFD,
	call	*__imp_sendto(%rip)	 #
 # Deep_Network_Socket.c:156: 	if (SentBytes != dataSize)
	cmpl	%eax, %ebx	 # tmp98, dataSize
	jne	.L42	 #,
 # Deep_Network_Socket.c:164: }
	movl	%r12d, %eax	 # <retval>,
	addq	$56, %rsp	 #,
	popq	%rbx	 #
	popq	%r12	 #
	ret	
	.p2align 4,,10
	.p2align 3
.L42:
 # Deep_Network_Socket.c:158: 		const int err = WSAGetLastError();
	call	*__imp_WSAGetLastError(%rip)	 #
 # Deep_Network_Socket.c:159: 		printf("Failed to send packet to destination with error = %i.\n", err);
	leaq	.LC16(%rip), %rcx	 #, tmp92
 # Deep_Network_Socket.c:158: 		const int err = WSAGetLastError();
	movl	%eax, %r12d	 # tmp99, <retval>
 # Deep_Network_Socket.c:159: 		printf("Failed to send packet to destination with error = %i.\n", err);
	movl	%eax, %edx	 # <retval>,
	call	printf	 #
 # Deep_Network_Socket.c:164: }
	movl	%r12d, %eax	 # <retval>,
	addq	$56, %rsp	 #,
	popq	%rbx	 #
	popq	%r12	 #
	ret	
	.seh_endproc
	.section .rdata,"dr"
	.align 8
.LC17:
	.ascii "Failed to receive packet with error = %i.\12\0"
	.text
	.p2align 4
	.globl	Deep_Network_Socket_Receive
	.def	Deep_Network_Socket_Receive;	.scl	2;	.type	32;	.endef
	.seh_proc	Deep_Network_Socket_Receive
Deep_Network_Socket_Receive:
	pushq	%r12	 #
	.seh_pushreg	%r12
	subq	$64, %rsp	 #,
	.seh_stackalloc	64
	.seh_endprologue
 # Deep_Network_Socket.c:170: 	const int BytesReceived = recvfrom(deepSocket->socketFD, (char*)buffer, maxBufferSize, 0, &fromAddress->sa, &fromLength);
	leaq	60(%rsp), %rax	 #, tmp90
	movq	%r9, 32(%rsp)	 # tmp98,
	xorl	%r9d, %r9d	 #
	movq	%rax, 40(%rsp)	 # tmp90,
	movq	(%rcx), %rcx	 # deepSocket_8(D)->socketFD,
 # Deep_Network_Socket.c:168: 	socklen_t fromLength = sizeof (struct sockaddr_in);
	movl	$16, 60(%rsp)	 #, fromLength
 # Deep_Network_Socket.c:170: 	const int BytesReceived = recvfrom(deepSocket->socketFD, (char*)buffer, maxBufferSize, 0, &fromAddress->sa, &fromLength);
	call	*__imp_recvfrom(%rip)	 #
	movl	%eax, %r12d	 # tmp99, <retval>
 # Deep_Network_Socket.c:172: 	if (BytesReceived < 0)
	testl	%eax, %eax	 # <retval>
	js	.L47	 #,
.L43:
 # Deep_Network_Socket.c:185: }
	movl	%r12d, %eax	 # <retval>,
	addq	$64, %rsp	 #,
	popq	%r12	 #
	ret	
	.p2align 4,,10
	.p2align 3
.L47:
 # Deep_Network_Socket.c:174: 		const int Error = WSAGetLastError();
	call	*__imp_WSAGetLastError(%rip)	 #
 # Deep_Network_Socket.c:181: 			return DEEP_NETWORK_ERROR;
	movl	$-1, %r12d	 #, <retval>
 # Deep_Network_Socket.c:174: 		const int Error = WSAGetLastError();
	movl	%eax, %edx	 # tmp100, Error
 # Deep_Network_Socket.c:175: 		if (Error != WSAEWOULDBLOCK) //https://stackoverflow.com/questions/17064069/recvfrom-error-10035-using-non-blocking-sockets
	cmpl	$10035, %eax	 #, Error
	je	.L43	 #,
 # Deep_Network_Socket.c:177: 			printf("Failed to receive packet with error = %i.\n", Error);
	leaq	.LC17(%rip), %rcx	 #, tmp93
	call	printf	 #
 # Deep_Network_Socket.c:185: }
	movl	%r12d, %eax	 # <retval>,
	addq	$64, %rsp	 #,
	popq	%r12	 #
	ret	
	.seh_endproc
	.globl	Deep_Network_Socket_Default
	.section .rdata,"dr"
	.align 16
Deep_Network_Socket_Default:
 # socketFD:
	.quad	-1
 # port:
	.word	-7849
	.space 6
	.globl	Deep_Network_Address_Default
	.align 16
Deep_Network_Address_Default:
 # a:
	.byte	127
 # b:
	.byte	0
 # c:
	.byte	0
 # d:
	.byte	1
 # port:
	.word	0
	.space 18
	.ident	"GCC: (Rev1, Built by MSYS2 project) 11.2.0"
	.def	__mingw_vfprintf;	.scl	2;	.type	32;	.endef
