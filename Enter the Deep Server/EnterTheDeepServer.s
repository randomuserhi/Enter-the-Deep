	.file	"EnterTheDeepServer.c"
 # GNU C11 (Rev1, Built by MSYS2 project) version 11.2.0 (x86_64-w64-mingw32)
 #	compiled by GNU C version 11.2.0, GMP version 6.2.1, MPFR version 4.1.0-p13, MPC version 1.2.1, isl version isl-0.24-GMP

 # GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
 # options passed: -mtune=generic -march=x86-64 -O3 -std=c11
	.text
	.p2align 4
	.globl	ExitHandler
	.def	ExitHandler;	.scl	2;	.type	32;	.endef
	.seh_proc	ExitHandler
ExitHandler:
	subq	$40, %rsp	 #,
	.seh_stackalloc	40
	.seh_endprologue
 # EnterTheDeepServer.c:13: 	Deep_Network_ShutdownSockets();
	call	Deep_Network_ShutdownSockets	 #
 # EnterTheDeepServer.c:19: 	exit(0);
	xorl	%ecx, %ecx	 #
	call	exit	 #
	nop	
	.seh_endproc
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
	.section .rdata,"dr"
.LC0:
	.ascii "Message received: %i\12\0"
	.text
	.p2align 4
	.globl	OnReceive
	.def	OnReceive;	.scl	2;	.type	32;	.endef
	.seh_proc	OnReceive
OnReceive:
	.seh_endprologue
 # EnterTheDeepServer.c:26: 	printf("Message received: %i\n", *(const int*)Buffer);
	movl	(%rcx), %edx	 # MEM[(const int *)Buffer_3(D)],
	leaq	.LC0(%rip), %rcx	 #, tmp87
 # EnterTheDeepServer.c:27: }
 # EnterTheDeepServer.c:26: 	printf("Message received: %i\n", *(const int*)Buffer);
	jmp	printf	 #
	.seh_endproc
	.p2align 4
	.globl	Cleanup
	.def	Cleanup;	.scl	2;	.type	32;	.endef
	.seh_proc	Cleanup
Cleanup:
	.seh_endprologue
 # EnterTheDeepServer.c:14: }
 # EnterTheDeepServer.c:13: 	Deep_Network_ShutdownSockets();
	jmp	Deep_Network_ShutdownSockets	 #
	.seh_endproc
	.def	__main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
.LC1:
	.ascii "%f %f %f\12\0"
.LC2:
	.ascii "IsBigEndian: %i.\12\0"
.LC3:
	.ascii "Server started on port: %i.\12\0"
	.section	.text.startup,"x"
	.p2align 4
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	pushq	%r12	 #
	.seh_pushreg	%r12
	pushq	%rbp	 #
	.seh_pushreg	%rbp
	pushq	%rdi	 #
	.seh_pushreg	%rdi
	pushq	%rsi	 #
	.seh_pushreg	%rsi
	pushq	%rbx	 #
	.seh_pushreg	%rbx
	subq	$432, %rsp	 #,
	.seh_stackalloc	432
	.seh_endprologue
 # EnterTheDeepServer.c:30: {
	call	__main	 #
 # EnterTheDeepServer.c:31: 	if (!SetConsoleCtrlHandler(ExitHandler, TRUE)) return 1;
	movl	$1, %edx	 #,
	leaq	ExitHandler(%rip), %rcx	 #, tmp87
	call	*__imp_SetConsoleCtrlHandler(%rip)	 #
 # EnterTheDeepServer.c:31: 	if (!SetConsoleCtrlHandler(ExitHandler, TRUE)) return 1;
	testl	%eax, %eax	 # tmp132
	jne	.L10	 #,
 # EnterTheDeepServer.c:67: }
	movl	$1, %eax	 #,
	addq	$432, %rsp	 #,
	popq	%rbx	 #
	popq	%rsi	 #
	popq	%rdi	 #
	popq	%rbp	 #
	popq	%r12	 #
	ret	
.L10:
 # EnterTheDeepServer.c:34: 	Deep_ECS_Create(&ECS);
	leaq	144(%rsp), %r12	 #, tmp90
 # EnterTheDeepServer.c:50: 	Deep_Network_Socket_Open(&server.socket);
	leaq	80(%rsp), %rbx	 #, tmp131
 # EnterTheDeepServer.c:34: 	Deep_ECS_Create(&ECS);
	movq	%r12, %rcx	 # tmp90,
 # EnterTheDeepServer.c:47: 	struct Deep_Network_Server server = Deep_Network_Server_Default;
	leaq	80(%rsp), %rdi	 #, tmp110
	leaq	56(%rsp), %rbp	 #, tmp128
 # EnterTheDeepServer.c:34: 	Deep_ECS_Create(&ECS);
	call	Deep_ECS_Create	 #
 # EnterTheDeepServer.c:35: 	Deep_ECS_PrintHierarchy(&ECS);
	movq	%r12, %rcx	 # tmp90,
	call	Deep_ECS_PrintHierarchy	 #
 # EnterTheDeepServer.c:37: 	getchar();
	call	getchar	 #
 # EnterTheDeepServer.c:41: 	printf("%f %f %f\n", vec3.x, vec3.y, vec3.z);
	movl	$4109, %edx	 #, tmp97
	xorl	%r9d, %r9d	 # tmp92
	leaq	.LC1(%rip), %rcx	 #, tmp107
	salq	$50, %rdx	 #, tmp97
	movq	%r9, %xmm3	 # tmp95,
	movq	%rdx, %xmm2	 # tmp100,
	movq	%rdx, %r8	 # tmp100,
	movq	%rdx, %xmm1	 # tmp100,
	call	printf	 #
 # EnterTheDeepServer.c:43: 	printf("IsBigEndian: %i.\n", Deep_Network_IsBigEndian());
	call	Deep_Network_IsBigEndian	 #
	leaq	.LC2(%rip), %rcx	 #, tmp108
	movl	%eax, %edx	 # tmp133, _2
	call	printf	 #
 # EnterTheDeepServer.c:45:     Deep_Network_InitializeSockets();
	call	Deep_Network_InitializeSockets	 #
 # EnterTheDeepServer.c:47: 	struct Deep_Network_Server server = Deep_Network_Server_Default;
	movq	.refptr.Deep_Network_Server_Default(%rip), %rsi	 #, tmp109
	movl	$14, %ecx	 #, tmp112
 # EnterTheDeepServer.c:48: 	server.OnReceiveHandle = &OnReceive;
	leaq	OnReceive(%rip), %rax	 #, tmp135
 # EnterTheDeepServer.c:47: 	struct Deep_Network_Server server = Deep_Network_Server_Default;
	rep movsl
 # EnterTheDeepServer.c:50: 	Deep_Network_Socket_Open(&server.socket);
	movq	%rbx, %rcx	 # tmp131,
 # EnterTheDeepServer.c:48: 	server.OnReceiveHandle = &OnReceive;
	movq	%rax, 128(%rsp)	 # tmp135, server.OnReceiveHandle
 # EnterTheDeepServer.c:57: 	struct Deep_Network_Address addr = { .a = 127, .b = 0, .c = 0, .d = 1, .port = 56732 };
	leaq	48(%rsp), %rsi	 #, tmp130
 # EnterTheDeepServer.c:50: 	Deep_Network_Socket_Open(&server.socket);
	call	Deep_Network_Socket_Open	 #
 # EnterTheDeepServer.c:51: 	Deep_Network_Server_Start(&server, DEEP_NETWORK_DEFAULTPORT);
	movl	$57687, %edx	 #,
	movq	%rbx, %rcx	 # tmp131,
 # EnterTheDeepServer.c:57: 	struct Deep_Network_Address addr = { .a = 127, .b = 0, .c = 0, .d = 1, .port = 56732 };
	movq	%rsi, %rdi	 # tmp130, tmp118
 # EnterTheDeepServer.c:51: 	Deep_Network_Server_Start(&server, DEEP_NETWORK_DEFAULTPORT);
	call	Deep_Network_Server_Start	 #
 # EnterTheDeepServer.c:53: 	printf("Server started on port: %i.\n", server.socket.port);
	movzwl	88(%rsp), %edx	 # server.socket.port, server.socket.port
	leaq	.LC3(%rip), %rcx	 #, tmp117
	call	printf	 #
 # EnterTheDeepServer.c:57: 	struct Deep_Network_Address addr = { .a = 127, .b = 0, .c = 0, .d = 1, .port = 56732 };
	xorl	%eax, %eax	 # tmp119
	movl	$6, %ecx	 #, tmp120
 # EnterTheDeepServer.c:55: 	int data = 10;
	movl	$10, 44(%rsp)	 #, data
 # EnterTheDeepServer.c:57: 	struct Deep_Network_Address addr = { .a = 127, .b = 0, .c = 0, .d = 1, .port = 56732 };
	rep stosl
	leaq	44(%rsp), %rdi	 #, tmp129
	movabsq	$243662101414015, %rax	 #, tmp137
	movq	%rax, 48(%rsp)	 # tmp137, MEM <unsigned long long> [(void *)&addr]
	.p2align 4,,10
	.p2align 3
.L8:
 # EnterTheDeepServer.c:60: 		Deep_Network_Server_Tick(&server);
	movq	%rbx, %rcx	 # tmp131,
	call	Deep_Network_Server_Tick	 #
 # EnterTheDeepServer.c:61: 		Deep_Network_Address_Format(&addr);
	movq	%rsi, %rcx	 # tmp130,
	call	Deep_Network_Address_Format	 #
 # Deep_Network.h:96: 	return Deep_Network_Socket_Send(&deepServer->socket, Data, DataSize, Address);
	movq	%rbp, %r9	 # tmp128,
	movq	%rdi, %rdx	 # tmp129,
	movq	%rbx, %rcx	 # tmp131,
	movl	$4, %r8d	 #,
	call	Deep_Network_Socket_Send	 #
	jmp	.L8	 #
	.seh_endproc
	.ident	"GCC: (Rev1, Built by MSYS2 project) 11.2.0"
	.def	Deep_Network_ShutdownSockets;	.scl	2;	.type	32;	.endef
	.def	exit;	.scl	2;	.type	32;	.endef
	.def	__mingw_vfprintf;	.scl	2;	.type	32;	.endef
	.def	Deep_ECS_Create;	.scl	2;	.type	32;	.endef
	.def	Deep_ECS_PrintHierarchy;	.scl	2;	.type	32;	.endef
	.def	getchar;	.scl	2;	.type	32;	.endef
	.def	Deep_Network_IsBigEndian;	.scl	2;	.type	32;	.endef
	.def	Deep_Network_InitializeSockets;	.scl	2;	.type	32;	.endef
	.def	Deep_Network_Socket_Open;	.scl	2;	.type	32;	.endef
	.def	Deep_Network_Server_Start;	.scl	2;	.type	32;	.endef
	.def	Deep_Network_Server_Tick;	.scl	2;	.type	32;	.endef
	.def	Deep_Network_Address_Format;	.scl	2;	.type	32;	.endef
	.def	Deep_Network_Socket_Send;	.scl	2;	.type	32;	.endef
	.section	.rdata$.refptr.Deep_Network_Server_Default, "dr"
	.globl	.refptr.Deep_Network_Server_Default
	.linkonce	discard
.refptr.Deep_Network_Server_Default:
	.quad	Deep_Network_Server_Default
