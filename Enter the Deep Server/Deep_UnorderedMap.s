	.file	"Deep_UnorderedMap.c"
 # GNU C11 (Rev1, Built by MSYS2 project) version 11.2.0 (x86_64-w64-mingw32)
 #	compiled by GNU C version 11.2.0, GMP version 6.2.1, MPFR version 4.1.0-p13, MPC version 1.2.1, isl version isl-0.24-GMP

 # GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
 # options passed: -mtune=generic -march=x86-64 -O3 -std=c11
	.text
	.p2align 4
	.globl	_Deep_UnorderedMap_Create
	.def	_Deep_UnorderedMap_Create;	.scl	2;	.type	32;	.endef
	.seh_proc	_Deep_UnorderedMap_Create
_Deep_UnorderedMap_Create:
	pushq	%rbx	 #
	.seh_pushreg	%rbx
	subq	$32, %rsp	 #,
	.seh_stackalloc	32
	.seh_endprologue
 # Deep_UnorderedMap.h:49: 	unorderedMap->bucketSize = DEEP_UNORDEREDMAP_BUCKETSIZE;
	movdqa	.LC0(%rip), %xmm0	 #, tmp99
 # Deep_UnorderedMap.h:43: {
	movq	88(%rsp), %r10	 # valueTypeAlignment, valueTypeAlignment
 # Deep_UnorderedMap.h:45: 	unorderedMap->keyTypeSize = keyTypeSize;
	movq	%r10, %xmm1	 # valueTypeAlignment, valueTypeAlignment
 # Deep_UnorderedMap.h:44: 	unorderedMap->keyCompareFunc = keyCompareFunc;
	movq	%rdx, 40(%rcx)	 # tmp115, unorderedMap_10(D)->keyCompareFunc
 # Deep_UnorderedMap.h:54: 	unorderedMap->keyOffset = (sizeof(**unorderedMap->hashes) + unorderedMap->keyTypeAlignment - 1) / unorderedMap->keyTypeAlignment * unorderedMap->keyTypeAlignment;
	leaq	31(%r9), %rax	 #, tmp100
 # Deep_UnorderedMap.h:54: 	unorderedMap->keyOffset = (sizeof(**unorderedMap->hashes) + unorderedMap->keyTypeAlignment - 1) / unorderedMap->keyTypeAlignment * unorderedMap->keyTypeAlignment;
	xorl	%edx, %edx	 # tmp103
 # Deep_UnorderedMap.h:43: {
	movq	%rcx, %rbx	 # tmp114, unorderedMap
 # Deep_UnorderedMap.h:54: 	unorderedMap->keyOffset = (sizeof(**unorderedMap->hashes) + unorderedMap->keyTypeAlignment - 1) / unorderedMap->keyTypeAlignment * unorderedMap->keyTypeAlignment;
	divq	%r9	 # keyTypeAlignment
 # Deep_UnorderedMap.h:49: 	unorderedMap->bucketSize = DEEP_UNORDEREDMAP_BUCKETSIZE;
	movups	%xmm0, 24(%rcx)	 # tmp99, MEM <vector(2) long long unsigned int> [(long long unsigned int *)unorderedMap_10(D) + 24B]
 # Deep_UnorderedMap.h:55: 	unorderedMap->valueOffset = ((unorderedMap->keyOffset + sizeof(unorderedMap->keyTypeSize)) + unorderedMap->valueTypeAlignment - 1) / unorderedMap->valueTypeAlignment * unorderedMap->valueTypeAlignment;
	xorl	%edx, %edx	 # tmp111
 # Deep_UnorderedMap.h:45: 	unorderedMap->keyTypeSize = keyTypeSize;
	movq	%r8, %xmm0	 # tmp116, tmp104
	movhps	80(%rsp), %xmm0	 # valueTypeSize, tmp104
	movups	%xmm0, 48(%rbx)	 # tmp104, MEM <vector(2) long long unsigned int> [(long long unsigned int *)unorderedMap_10(D) + 48B]
	movq	%r9, %xmm0	 # keyTypeAlignment, tmp105
	punpcklqdq	%xmm1, %xmm0	 # valueTypeAlignment, tmp105
	movups	%xmm0, 64(%rbx)	 # tmp105, MEM <vector(2) long long unsigned int> [(long long unsigned int *)unorderedMap_10(D) + 64B]
 # Deep_UnorderedMap.h:54: 	unorderedMap->keyOffset = (sizeof(**unorderedMap->hashes) + unorderedMap->keyTypeAlignment - 1) / unorderedMap->keyTypeAlignment * unorderedMap->keyTypeAlignment;
	imulq	%r9, %rax	 # keyTypeAlignment, tmp102
	movq	%rax, %rcx	 # tmp102, _3
 # Deep_UnorderedMap.h:55: 	unorderedMap->valueOffset = ((unorderedMap->keyOffset + sizeof(unorderedMap->keyTypeSize)) + unorderedMap->valueTypeAlignment - 1) / unorderedMap->valueTypeAlignment * unorderedMap->valueTypeAlignment;
	leaq	7(%rax,%r10), %rax	 #, tmp108
 # Deep_UnorderedMap.h:55: 	unorderedMap->valueOffset = ((unorderedMap->keyOffset + sizeof(unorderedMap->keyTypeSize)) + unorderedMap->valueTypeAlignment - 1) / unorderedMap->valueTypeAlignment * unorderedMap->valueTypeAlignment;
	divq	%r10	 # valueTypeAlignment
 # Deep_UnorderedMap.h:45: 	unorderedMap->keyTypeSize = keyTypeSize;
	movq	%rcx, %xmm0	 # _3, tmp106
 # Deep_UnorderedMap.h:57: 	unorderedMap->hashes = calloc(DEEP_UNORDEREDMAP_BUCKETSIZE, sizeof(*unorderedMap->hashes));
	movl	$8, %edx	 #,
	movl	$13, %ecx	 #,
 # Deep_UnorderedMap.h:55: 	unorderedMap->valueOffset = ((unorderedMap->keyOffset + sizeof(unorderedMap->keyTypeSize)) + unorderedMap->valueTypeAlignment - 1) / unorderedMap->valueTypeAlignment * unorderedMap->valueTypeAlignment;
	imulq	%r10, %rax	 # valueTypeAlignment, tmp112
 # Deep_UnorderedMap.h:45: 	unorderedMap->keyTypeSize = keyTypeSize;
	movq	%rax, %xmm2	 # tmp112, tmp112
	punpcklqdq	%xmm2, %xmm0	 # tmp112, tmp106
	movups	%xmm0, 80(%rbx)	 # tmp106, MEM <vector(2) long long unsigned int> [(long long unsigned int *)unorderedMap_10(D) + 80B]
 # Deep_UnorderedMap.h:57: 	unorderedMap->hashes = calloc(DEEP_UNORDEREDMAP_BUCKETSIZE, sizeof(*unorderedMap->hashes));
	call	calloc	 #
 # Deep_UnorderedMap.h:58: 	unorderedMap->start = NULL;
	movq	$0, 8(%rbx)	 #, unorderedMap_10(D)->start
 # Deep_UnorderedMap.h:57: 	unorderedMap->hashes = calloc(DEEP_UNORDEREDMAP_BUCKETSIZE, sizeof(*unorderedMap->hashes));
	movq	%rax, (%rbx)	 # tmp118, unorderedMap_10(D)->hashes
 # Deep_UnorderedMap.h:59: 	unorderedMap->end = NULL;
	movq	$0, 16(%rbx)	 #, unorderedMap_10(D)->end
 # Deep_UnorderedMap.h:60: }
	addq	$32, %rsp	 #,
	popq	%rbx	 #
	ret	
	.seh_endproc
	.p2align 4
	.globl	_Deep_UnorderedMap_ShiftMix
	.def	_Deep_UnorderedMap_ShiftMix;	.scl	2;	.type	32;	.endef
	.seh_proc	_Deep_UnorderedMap_ShiftMix
_Deep_UnorderedMap_ShiftMix:
	.seh_endprologue
 # Deep_UnorderedMap.c:16: 	return v ^ (v >> 47);
	movq	%rcx, %rax	 # tmp87, tmp86
	shrq	$47, %rax	 #, tmp86
 # Deep_UnorderedMap.c:16: 	return v ^ (v >> 47);
	xorq	%rcx, %rax	 # tmp87, tmp85
 # Deep_UnorderedMap.c:17: }
	ret	
	.seh_endproc
	.p2align 4
	.globl	Deep_UnorderedMap_Hash
	.def	Deep_UnorderedMap_Hash;	.scl	2;	.type	32;	.endef
	.seh_proc	Deep_UnorderedMap_Hash
Deep_UnorderedMap_Hash:
	.seh_endprologue
 # Deep_UnorderedMap.c:89: 	const size_t len_aligned = len & ~(size_t)0x7;
	movq	%rdx, %r11	 # len, len_aligned
 # Deep_UnorderedMap.c:41: {
	movq	%rcx, %rax	 # tmp179, ptr
 # Deep_UnorderedMap.c:91: 	size_t hash = seed ^ (len * mul);
	movq	%rdx, %r10	 # len, tmp150
 # Deep_UnorderedMap.c:89: 	const size_t len_aligned = len & ~(size_t)0x7;
	andq	$-8, %r11	 #, len_aligned
 # Deep_UnorderedMap.c:90: 	const char* const end = buf + len_aligned;
	addq	%rcx, %r11	 # ptr, end
 # Deep_UnorderedMap.c:91: 	size_t hash = seed ^ (len * mul);
	movabsq	$-4132994306676758123, %rcx	 #, tmp151
	imulq	%rcx, %r10	 # tmp151, tmp150
 # Deep_UnorderedMap.c:91: 	size_t hash = seed ^ (len * mul);
	xorq	%r8, %r10	 # tmp181, hash
 # Deep_UnorderedMap.c:92: 	for (const char* p = buf; p != end; p += 8)
	cmpq	%r11, %rax	 # end, ptr
	je	.L5	 #,
	.p2align 4,,10
	.p2align 3
.L6:
 # Deep_UnorderedMap.c:94: 		const size_t data = _Deep_UnorderedMap_ShiftMix(_Deep_UnorderedMap_UnalignedLoad(p) * mul) * mul;
	movq	(%rax), %r9	 # MEM <long long unsigned int> [(char * {ref-all})p_48], _2
 # Deep_UnorderedMap.c:92: 	for (const char* p = buf; p != end; p += 8)
	addq	$8, %rax	 #, ptr
 # Deep_UnorderedMap.c:94: 		const size_t data = _Deep_UnorderedMap_ShiftMix(_Deep_UnorderedMap_UnalignedLoad(p) * mul) * mul;
	imulq	%rcx, %r9	 # tmp151, _2
 # Deep_UnorderedMap.c:16: 	return v ^ (v >> 47);
	movq	%r9, %r8	 # _2, tmp154
	shrq	$47, %r8	 #, tmp154
 # Deep_UnorderedMap.c:16: 	return v ^ (v >> 47);
	xorq	%r9, %r8	 # _2, tmp155
 # Deep_UnorderedMap.c:94: 		const size_t data = _Deep_UnorderedMap_ShiftMix(_Deep_UnorderedMap_UnalignedLoad(p) * mul) * mul;
	imulq	%rcx, %r8	 # tmp151, data
 # Deep_UnorderedMap.c:95: 		hash ^= data;
	xorq	%r10, %r8	 # hash, hash
 # Deep_UnorderedMap.c:96: 		hash *= mul;
	movq	%r8, %r10	 # hash, hash
	imulq	%rcx, %r10	 # tmp151, hash
 # Deep_UnorderedMap.c:92: 	for (const char* p = buf; p != end; p += 8)
	cmpq	%rax, %r11	 # ptr, end
	jne	.L6	 #,
.L5:
 # Deep_UnorderedMap.c:98: 	if ((len & 0x7) != 0)
	andl	$7, %edx	 #, tmp159
	je	.L7	 #,
 # Deep_UnorderedMap.c:7: 	--n;
	leal	-1(%rdx), %eax	 #, n
 # Deep_UnorderedMap.c:10: 	while (--n >= 0);
	movl	%edx, %ecx	 # tmp159, n
 # Deep_UnorderedMap.c:9: 		result = (result << 8) + (unsigned char)(p[n]);
	cltq
 # Deep_UnorderedMap.c:9: 		result = (result << 8) + (unsigned char)(p[n]);
	movzbl	(%r11,%rax), %eax	 # *_97, result
 # Deep_UnorderedMap.c:10: 	while (--n >= 0);
	subl	$2, %ecx	 #, n
	js	.L8	 #,
 # Deep_UnorderedMap.c:9: 		result = (result << 8) + (unsigned char)(p[n]);
	movslq	%ecx, %rcx	 # n, n
 # Deep_UnorderedMap.c:9: 		result = (result << 8) + (unsigned char)(p[n]);
	salq	$8, %rax	 #, tmp164
 # Deep_UnorderedMap.c:9: 		result = (result << 8) + (unsigned char)(p[n]);
	movzbl	(%r11,%rcx), %ecx	 # *_87, *_87
 # Deep_UnorderedMap.c:9: 		result = (result << 8) + (unsigned char)(p[n]);
	addq	%rcx, %rax	 # *_87, result
 # Deep_UnorderedMap.c:10: 	while (--n >= 0);
	leal	-3(%rdx), %ecx	 #, n
	cmpq	$2, %rdx	 #, tmp159
	je	.L8	 #,
 # Deep_UnorderedMap.c:9: 		result = (result << 8) + (unsigned char)(p[n]);
	movslq	%ecx, %rcx	 # n, n
 # Deep_UnorderedMap.c:9: 		result = (result << 8) + (unsigned char)(p[n]);
	salq	$8, %rax	 #, _79
 # Deep_UnorderedMap.c:9: 		result = (result << 8) + (unsigned char)(p[n]);
	movzbl	(%r11,%rcx), %ecx	 # *_77, *_77
 # Deep_UnorderedMap.c:9: 		result = (result << 8) + (unsigned char)(p[n]);
	addq	%rcx, %rax	 # *_77, result
 # Deep_UnorderedMap.c:10: 	while (--n >= 0);
	leal	-4(%rdx), %ecx	 #, n
	cmpq	$3, %rdx	 #, tmp159
	je	.L8	 #,
 # Deep_UnorderedMap.c:9: 		result = (result << 8) + (unsigned char)(p[n]);
	movslq	%ecx, %rcx	 # n, n
 # Deep_UnorderedMap.c:9: 		result = (result << 8) + (unsigned char)(p[n]);
	salq	$8, %rax	 #, _69
 # Deep_UnorderedMap.c:9: 		result = (result << 8) + (unsigned char)(p[n]);
	movzbl	(%r11,%rcx), %ecx	 # *_67, *_67
 # Deep_UnorderedMap.c:9: 		result = (result << 8) + (unsigned char)(p[n]);
	addq	%rcx, %rax	 # *_67, result
 # Deep_UnorderedMap.c:10: 	while (--n >= 0);
	leal	-5(%rdx), %ecx	 #, n
	cmpq	$4, %rdx	 #, tmp159
	je	.L8	 #,
 # Deep_UnorderedMap.c:9: 		result = (result << 8) + (unsigned char)(p[n]);
	movslq	%ecx, %rcx	 # n, n
 # Deep_UnorderedMap.c:9: 		result = (result << 8) + (unsigned char)(p[n]);
	salq	$8, %rax	 #, _59
 # Deep_UnorderedMap.c:9: 		result = (result << 8) + (unsigned char)(p[n]);
	movzbl	(%r11,%rcx), %ecx	 # *_57, *_57
 # Deep_UnorderedMap.c:9: 		result = (result << 8) + (unsigned char)(p[n]);
	addq	%rcx, %rax	 # *_57, result
 # Deep_UnorderedMap.c:10: 	while (--n >= 0);
	leal	-6(%rdx), %ecx	 #, n
	cmpq	$5, %rdx	 #, tmp159
	je	.L8	 #,
 # Deep_UnorderedMap.c:9: 		result = (result << 8) + (unsigned char)(p[n]);
	movslq	%ecx, %rdx	 # n, n
 # Deep_UnorderedMap.c:9: 		result = (result << 8) + (unsigned char)(p[n]);
	salq	$8, %rax	 #, _49
 # Deep_UnorderedMap.c:9: 		result = (result << 8) + (unsigned char)(p[n]);
	movzbl	(%r11,%rdx), %edx	 # *_44, *_44
 # Deep_UnorderedMap.c:9: 		result = (result << 8) + (unsigned char)(p[n]);
	addq	%rdx, %rax	 # *_44, result
 # Deep_UnorderedMap.c:10: 	while (--n >= 0);
	testl	%ecx, %ecx	 # n
	je	.L8	 #,
 # Deep_UnorderedMap.c:9: 		result = (result << 8) + (unsigned char)(p[n]);
	movzbl	(%r11), %edx	 # *end_14, *end_14
 # Deep_UnorderedMap.c:9: 		result = (result << 8) + (unsigned char)(p[n]);
	salq	$8, %rax	 #, _26
 # Deep_UnorderedMap.c:9: 		result = (result << 8) + (unsigned char)(p[n]);
	addq	%rdx, %rax	 # *end_14, result
.L8:
 # Deep_UnorderedMap.c:101: 		hash ^= data;
	xorq	%r10, %rax	 # hash, hash
 # Deep_UnorderedMap.c:102: 		hash *= mul;
	movabsq	$-4132994306676758123, %r10	 #, tmp174
	imulq	%rax, %r10	 # hash, hash
.L7:
 # Deep_UnorderedMap.c:104: 	hash = _Deep_UnorderedMap_ShiftMix(hash) * mul;
	movabsq	$-4132994306676758123, %rax	 #, tmp176
 # Deep_UnorderedMap.c:16: 	return v ^ (v >> 47);
	movq	%r10, %rdx	 # hash, tmp175
	shrq	$47, %rdx	 #, tmp175
 # Deep_UnorderedMap.c:16: 	return v ^ (v >> 47);
	xorq	%r10, %rdx	 # hash, _43
 # Deep_UnorderedMap.c:104: 	hash = _Deep_UnorderedMap_ShiftMix(hash) * mul;
	imulq	%rax, %rdx	 # tmp176, hash
 # Deep_UnorderedMap.c:16: 	return v ^ (v >> 47);
	movq	%rdx, %rax	 # hash, tmp178
	shrq	$47, %rax	 #, tmp178
 # Deep_UnorderedMap.c:16: 	return v ^ (v >> 47);
	xorq	%rdx, %rax	 # hash, tmp177
 # Deep_UnorderedMap.c:108: }
	ret	
	.seh_endproc
	.p2align 4
	.globl	Deep_UnorderedMap_ByteCompare
	.def	Deep_UnorderedMap_ByteCompare;	.scl	2;	.type	32;	.endef
	.seh_proc	Deep_UnorderedMap_ByteCompare
Deep_UnorderedMap_ByteCompare:
	subq	$40, %rsp	 #,
	.seh_stackalloc	40
	.seh_endprologue
 # Deep_UnorderedMap.c:112: 	return (memcmp(hashKey, key, keyTypeSize) == 0);
	call	memcmp	 #
 # Deep_UnorderedMap.c:112: 	return (memcmp(hashKey, key, keyTypeSize) == 0);
	testl	%eax, %eax	 # tmp96
	sete	%al	 #, tmp91
	movzbl	%al, %eax	 # tmp91, tmp91
 # Deep_UnorderedMap.c:113: }
	addq	$40, %rsp	 #,
	ret	
	.seh_endproc
	.p2align 4
	.globl	_Deep_UnorderedMap_Free
	.def	_Deep_UnorderedMap_Free;	.scl	2;	.type	32;	.endef
	.seh_proc	_Deep_UnorderedMap_Free
_Deep_UnorderedMap_Free:
	pushq	%rsi	 #
	.seh_pushreg	%rsi
	pushq	%rbx	 #
	.seh_pushreg	%rbx
	subq	$40, %rsp	 #,
	.seh_stackalloc	40
	.seh_endprologue
 # Deep_UnorderedMap.c:119: 	for (struct Deep_UnorderedMap_HashSlot* hashSlot = unorderedMap->start; hashSlot != NULL;)
	movq	8(%rcx), %rbx	 # unorderedMap_5(D)->start, hashSlot
 # Deep_UnorderedMap.c:118: {
	movq	%rcx, %rsi	 # tmp86, unorderedMap
 # Deep_UnorderedMap.c:119: 	for (struct Deep_UnorderedMap_HashSlot* hashSlot = unorderedMap->start; hashSlot != NULL;)
	testq	%rbx, %rbx	 # hashSlot
	je	.L30	 #,
	.p2align 4,,10
	.p2align 3
.L31:
	movq	%rbx, %rcx	 # hashSlot, hashSlot
 # Deep_UnorderedMap.c:122: 		hashSlot = hashSlot->next;
	movq	8(%rbx), %rbx	 # hashSlot_12->next, hashSlot
 # Deep_UnorderedMap.c:123: 		free(Old);
	call	free	 #
 # Deep_UnorderedMap.c:119: 	for (struct Deep_UnorderedMap_HashSlot* hashSlot = unorderedMap->start; hashSlot != NULL;)
	testq	%rbx, %rbx	 # hashSlot
	jne	.L31	 #,
.L30:
 # Deep_UnorderedMap.c:125: 	free(unorderedMap->hashes);
	movq	(%rsi), %rcx	 # unorderedMap_5(D)->hashes,
 # Deep_UnorderedMap.c:126: }
	addq	$40, %rsp	 #,
	popq	%rbx	 #
	popq	%rsi	 #
 # Deep_UnorderedMap.c:125: 	free(unorderedMap->hashes);
	jmp	free	 #
	.seh_endproc
	.p2align 4
	.globl	_Deep_UnorderedMap_ReHash
	.def	_Deep_UnorderedMap_ReHash;	.scl	2;	.type	32;	.endef
	.seh_proc	_Deep_UnorderedMap_ReHash
_Deep_UnorderedMap_ReHash:
	pushq	%rdi	 #
	.seh_pushreg	%rdi
	pushq	%rsi	 #
	.seh_pushreg	%rsi
	pushq	%rbx	 #
	.seh_pushreg	%rbx
	subq	$32, %rsp	 #,
	.seh_stackalloc	32
	.seh_endprologue
 # Deep_UnorderedMap.c:130: 	if (unorderedMap->size / unorderedMap->bucketSize > DEEP_UNORDEREDMAP_LOADFACTOR)
	xorl	%edx, %edx	 # tmp99
 # Deep_UnorderedMap.c:130: 	if (unorderedMap->size / unorderedMap->bucketSize > DEEP_UNORDEREDMAP_LOADFACTOR)
	movq	24(%rcx), %rbx	 # unorderedMap_18(D)->bucketSize, _2
 # Deep_UnorderedMap.c:130: 	if (unorderedMap->size / unorderedMap->bucketSize > DEEP_UNORDEREDMAP_LOADFACTOR)
	movq	32(%rcx), %rax	 # unorderedMap_18(D)->size, unorderedMap_18(D)->size
	divq	%rbx	 # _2
 # Deep_UnorderedMap.c:129: {
	movq	%rcx, %rsi	 # tmp112, unorderedMap
 # Deep_UnorderedMap.c:130: 	if (unorderedMap->size / unorderedMap->bucketSize > DEEP_UNORDEREDMAP_LOADFACTOR)
	testq	%rax, %rax	 # tmp98
	js	.L38	 #,
	pxor	%xmm0, %xmm0	 # tmp101
	cvtsi2sdq	%rax, %xmm0	 # tmp98, tmp101
 # Deep_UnorderedMap.c:130: 	if (unorderedMap->size / unorderedMap->bucketSize > DEEP_UNORDEREDMAP_LOADFACTOR)
	comisd	.LC1(%rip), %xmm0	 #, tmp101
	ja	.L56	 #,
.L36:
 # Deep_UnorderedMap.c:159: }
	addq	$32, %rsp	 #,
	popq	%rbx	 #
	popq	%rsi	 #
	popq	%rdi	 #
	ret	
	.p2align 4,,10
	.p2align 3
.L38:
 # Deep_UnorderedMap.c:130: 	if (unorderedMap->size / unorderedMap->bucketSize > DEEP_UNORDEREDMAP_LOADFACTOR)
	movq	%rax, %rdx	 # tmp98, tmp103
	andl	$1, %eax	 #, tmp104
	pxor	%xmm0, %xmm0	 # tmp102
	shrq	%rdx	 # tmp103
	orq	%rax, %rdx	 # tmp104, tmp103
	cvtsi2sdq	%rdx, %xmm0	 # tmp103, tmp102
	addsd	%xmm0, %xmm0	 # tmp102, tmp101
 # Deep_UnorderedMap.c:130: 	if (unorderedMap->size / unorderedMap->bucketSize > DEEP_UNORDEREDMAP_LOADFACTOR)
	comisd	.LC1(%rip), %xmm0	 #, tmp101
	jbe	.L36	 #,
.L56:
 # Deep_UnorderedMap.c:132: 		const size_t newBucketSize = unorderedMap->bucketSize * DEEP_UNORDEREDMAP_GROWTHRATE;
	addq	%rbx, %rbx	 # newBucketSize
 # Deep_UnorderedMap.c:133: 		void* tmp = calloc(newBucketSize, sizeof(*unorderedMap->hashes));
	movl	$8, %edx	 #,
	movq	%rbx, %rcx	 # newBucketSize,
	call	calloc	 #
	movq	%rax, %rdi	 # tmp113, tmp
 # Deep_UnorderedMap.c:134: 		if (tmp)
	testq	%rax, %rax	 # tmp
	je	.L36	 #,
 # Deep_UnorderedMap.c:136: 			free(unorderedMap->hashes);
	movq	(%rsi), %rcx	 # unorderedMap_18(D)->hashes,
	call	free	 #
 # Deep_UnorderedMap.c:139: 			for (struct Deep_UnorderedMap_HashSlot* hashSlot = unorderedMap->start; hashSlot != NULL; hashSlot = hashSlot->next)
	movq	8(%rsi), %rcx	 # unorderedMap_18(D)->start, hashSlot
 # Deep_UnorderedMap.c:137: 			unorderedMap->bucketSize = newBucketSize;
	movq	%rbx, 24(%rsi)	 # newBucketSize, unorderedMap_18(D)->bucketSize
 # Deep_UnorderedMap.c:138: 			unorderedMap->hashes = tmp;
	movq	%rdi, (%rsi)	 # tmp, unorderedMap_18(D)->hashes
 # Deep_UnorderedMap.c:139: 			for (struct Deep_UnorderedMap_HashSlot* hashSlot = unorderedMap->start; hashSlot != NULL; hashSlot = hashSlot->next)
	testq	%rcx, %rcx	 # hashSlot
	jne	.L43	 #,
	jmp	.L36	 #
	.p2align 4,,10
	.p2align 3
.L54:
 # Deep_UnorderedMap.c:153: 					tmp->_next = hashSlot;
	movq	%rcx, (%rdx)	 # hashSlot,* tmp
 # Deep_UnorderedMap.c:155: 				hashSlot->_next = NULL;
	movq	$0, (%rcx)	 #, hashSlot_35->_next
 # Deep_UnorderedMap.c:139: 			for (struct Deep_UnorderedMap_HashSlot* hashSlot = unorderedMap->start; hashSlot != NULL; hashSlot = hashSlot->next)
	movq	8(%rcx), %rcx	 # hashSlot_35->next, hashSlot
 # Deep_UnorderedMap.c:139: 			for (struct Deep_UnorderedMap_HashSlot* hashSlot = unorderedMap->start; hashSlot != NULL; hashSlot = hashSlot->next)
	testq	%rcx, %rcx	 # hashSlot
	je	.L36	 #,
.L43:
 # Deep_UnorderedMap.c:141: 				const size_t index = hashSlot->hash % unorderedMap->bucketSize;
	movq	24(%rcx), %rax	 # hashSlot_35->hash, hashSlot_35->hash
	xorl	%edx, %edx	 # index
	divq	%rbx	 # newBucketSize
 # Deep_UnorderedMap.c:142: 				if (unorderedMap->hashes[index] == NULL)
	leaq	(%rdi,%rdx,8), %rdx	 #, _9
	movq	(%rdx), %rax	 # *_9, _11
 # Deep_UnorderedMap.c:142: 				if (unorderedMap->hashes[index] == NULL)
	testq	%rax, %rax	 # _11
	je	.L54	 #,
	.p2align 4,,10
	.p2align 3
.L41:
	movq	%rax, %rdx	 # _11, tmp
 # Deep_UnorderedMap.c:149: 					while (tmp->_next != NULL)
	movq	(%rax), %rax	 # tmp_13->_next, _11
 # Deep_UnorderedMap.c:149: 					while (tmp->_next != NULL)
	testq	%rax, %rax	 # _11
	je	.L54	 #,
	movq	%rax, %rdx	 # _11, tmp
 # Deep_UnorderedMap.c:149: 					while (tmp->_next != NULL)
	movq	(%rax), %rax	 # tmp_13->_next, _11
 # Deep_UnorderedMap.c:149: 					while (tmp->_next != NULL)
	testq	%rax, %rax	 # _11
	jne	.L41	 #,
	jmp	.L54	 #
	.seh_endproc
	.p2align 4
	.globl	_Deep_UnorderedMap_Insert
	.def	_Deep_UnorderedMap_Insert;	.scl	2;	.type	32;	.endef
	.seh_proc	_Deep_UnorderedMap_Insert
_Deep_UnorderedMap_Insert:
	pushq	%r13	 #
	.seh_pushreg	%r13
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
	subq	$40, %rsp	 #,
	.seh_stackalloc	40
	.seh_endprologue
 # Deep_UnorderedMap.c:162: {
	movq	%rdx, %rdi	 # tmp175, hash
	movq	%rcx, %rbx	 # tmp174, unorderedMap
	movq	%r8, %r12	 # tmp176, key
 # Deep_UnorderedMap.c:163: 	_Deep_UnorderedMap_ReHash(unorderedMap);
	call	_Deep_UnorderedMap_ReHash	 #
 # Deep_UnorderedMap.c:165: 	const size_t index = hash % unorderedMap->bucketSize;
	movq	%rdi, %rax	 # hash, tmp134
	xorl	%edx, %edx	 # index
	divq	24(%rbx)	 # unorderedMap_53(D)->bucketSize
 # Deep_UnorderedMap.c:166: 	if (unorderedMap->hashes[index] == NULL)
	movq	(%rbx), %rax	 # unorderedMap_53(D)->hashes, unorderedMap_53(D)->hashes
	leaq	(%rax,%rdx,8), %rbp	 #, _4
 # Deep_UnorderedMap.c:165: 	const size_t index = hash % unorderedMap->bucketSize;
	movq	%rdx, %r13	 # index, index
 # Deep_UnorderedMap.c:166: 	if (unorderedMap->hashes[index] == NULL)
	movq	0(%rbp), %rsi	 # *_4, hashSlot
 # Deep_UnorderedMap.c:166: 	if (unorderedMap->hashes[index] == NULL)
	testq	%rsi, %rsi	 # hashSlot
	jne	.L58	 #,
	jmp	.L73	 #
	.p2align 4,,10
	.p2align 3
.L63:
 # Deep_UnorderedMap.c:203: 			if (hashSlot->_next)
	movq	(%rsi), %rdx	 # hashSlot_46->_next, _33
 # Deep_UnorderedMap.c:203: 			if (hashSlot->_next)
	testq	%rdx, %rdx	 # _33
	je	.L74	 #,
	movq	%rdx, %rsi	 # _33, hashSlot
.L58:
 # Deep_UnorderedMap.c:198: 			if (unorderedMap->keyCompareFunc((unsigned char*)hashSlot + unorderedMap->keyOffset, key, unorderedMap->keyTypeSize))
	movq	80(%rbx), %rcx	 # unorderedMap_53(D)->keyOffset, tmp153
	movq	48(%rbx), %r8	 # unorderedMap_53(D)->keyTypeSize,
	movq	%r12, %rdx	 # key,
	addq	%rsi, %rcx	 # hashSlot, tmp153
	call	*40(%rbx)	 # unorderedMap_53(D)->keyCompareFunc
 # Deep_UnorderedMap.c:198: 			if (unorderedMap->keyCompareFunc((unsigned char*)hashSlot + unorderedMap->keyOffset, key, unorderedMap->keyTypeSize))
	testl	%eax, %eax	 # tmp178
	je	.L63	 #,
 # Deep_UnorderedMap.c:200: 				return (unsigned char*)hashSlot + unorderedMap->valueOffset;
	movq	88(%rbx), %rax	 # unorderedMap_53(D)->valueOffset, hashSlot
	addq	%rsi, %rax	 # hashSlot, hashSlot
.L57:
 # Deep_UnorderedMap.c:230: }
	addq	$40, %rsp	 #,
	popq	%rbx	 #
	popq	%rsi	 #
	popq	%rdi	 #
	popq	%rbp	 #
	popq	%r12	 #
	popq	%r13	 #
	ret	
	.p2align 4,,10
	.p2align 3
.L74:
 # Deep_UnorderedMap.c:208: 		const unsigned char* tmp = malloc(unorderedMap->valueOffset + unorderedMap->valueTypeSize);
	movq	56(%rbx), %rcx	 # unorderedMap_53(D)->valueTypeSize, unorderedMap_53(D)->valueTypeSize
	addq	88(%rbx), %rcx	 # unorderedMap_53(D)->valueOffset, tmp157
	call	malloc	 #
 # Deep_UnorderedMap.c:209: 		if (tmp)
	testq	%rax, %rax	 # tmp160
	je	.L64	 #,
 # Deep_UnorderedMap.c:214: 			hashSlot->_next->_next = NULL;
	pxor	%xmm0, %xmm0	 # tmp161
 # Deep_UnorderedMap.c:211: 			hashSlot->_next = (void*)tmp;
	movq	%rax, (%rsi)	 # tmp160, hashSlot_46->_next
 # Deep_UnorderedMap.c:221: 			memcpy((unsigned char*)hashSlot->_next + unorderedMap->keyOffset, key, unorderedMap->keyTypeSize);
	movq	48(%rbx), %r8	 # unorderedMap_53(D)->keyTypeSize,
	movq	%r12, %rdx	 # key,
 # Deep_UnorderedMap.c:214: 			hashSlot->_next->_next = NULL;
	movups	%xmm0, (%rax)	 # tmp161, MEM <vector(2) long long unsigned int> [(struct Deep_UnorderedMap_HashSlot * *)tmp_60]
 # Deep_UnorderedMap.c:215: 			hashSlot->_next->prev = unorderedMap->end;
	movq	(%rsi), %rcx	 # hashSlot_46->_next, _37
 # Deep_UnorderedMap.c:212: 			hashSlot->_next->hash = hash;
	movq	%rdi, 24(%rax)	 # hash, MEM[(struct Deep_UnorderedMap_HashSlot *)tmp_60].hash
 # Deep_UnorderedMap.c:215: 			hashSlot->_next->prev = unorderedMap->end;
	movq	16(%rbx), %rax	 # unorderedMap_53(D)->end, _38
 # Deep_UnorderedMap.c:215: 			hashSlot->_next->prev = unorderedMap->end;
	movq	%rax, 16(%rcx)	 # _38, _37->prev
 # Deep_UnorderedMap.c:216: 			unorderedMap->size++;
	addq	$1, 32(%rbx)	 #, unorderedMap_53(D)->size
 # Deep_UnorderedMap.c:217: 			unorderedMap->end->next = hashSlot->_next;
	movq	%rcx, 8(%rax)	 # _37, _38->next
 # Deep_UnorderedMap.c:218: 			unorderedMap->end = hashSlot->_next;
	movq	%rcx, 16(%rbx)	 # _37, unorderedMap_53(D)->end
 # Deep_UnorderedMap.c:221: 			memcpy((unsigned char*)hashSlot->_next + unorderedMap->keyOffset, key, unorderedMap->keyTypeSize);
	addq	80(%rbx), %rcx	 # unorderedMap_53(D)->keyOffset, tmp162
	call	memcpy	 #
 # Deep_UnorderedMap.c:223: 			return (unsigned char*)hashSlot->_next + unorderedMap->valueOffset;
	movq	88(%rbx), %rax	 # unorderedMap_53(D)->valueOffset, unorderedMap_53(D)->valueOffset
	addq	(%rsi), %rax	 # hashSlot_46->_next, <retval>
 # Deep_UnorderedMap.c:230: }
	addq	$40, %rsp	 #,
	popq	%rbx	 #
	popq	%rsi	 #
	popq	%rdi	 #
	popq	%rbp	 #
	popq	%r12	 #
	popq	%r13	 #
	ret	
	.p2align 4,,10
	.p2align 3
.L73:
 # Deep_UnorderedMap.c:168: 		void* tmp = malloc(unorderedMap->valueOffset + unorderedMap->valueTypeSize);
	movq	56(%rbx), %rcx	 # unorderedMap_53(D)->valueTypeSize, unorderedMap_53(D)->valueTypeSize
	addq	88(%rbx), %rcx	 # unorderedMap_53(D)->valueOffset, tmp136
	call	malloc	 #
 # Deep_UnorderedMap.c:169: 		if (tmp)
	testq	%rax, %rax	 # tmp139
	je	.L64	 #,
 # Deep_UnorderedMap.c:171: 			unorderedMap->hashes[index] = tmp;
	movq	%rax, 0(%rbp)	 # tmp139, *_4
 # Deep_UnorderedMap.c:173: 			unorderedMap->hashes[index]->_next = NULL;
	movq	$0, (%rax)	 #, MEM[(struct Deep_UnorderedMap_HashSlot *)tmp_73]._next
 # Deep_UnorderedMap.c:172: 			unorderedMap->hashes[index]->hash = hash;
	movq	%rdi, 24(%rax)	 # hash, MEM[(struct Deep_UnorderedMap_HashSlot *)tmp_73].hash
 # Deep_UnorderedMap.c:174: 			unorderedMap->hashes[index]->next = NULL;
	movq	0(%rbp), %rax	 # *_4, _9
 # Deep_UnorderedMap.c:174: 			unorderedMap->hashes[index]->next = NULL;
	movq	$0, 8(%rax)	 #, _9->next
 # Deep_UnorderedMap.c:175: 			unorderedMap->hashes[index]->prev = unorderedMap->end;
	movq	16(%rbx), %rax	 # unorderedMap_53(D)->end, _11
 # Deep_UnorderedMap.c:175: 			unorderedMap->hashes[index]->prev = unorderedMap->end;
	movq	0(%rbp), %rdx	 # *_4, _10
 # Deep_UnorderedMap.c:175: 			unorderedMap->hashes[index]->prev = unorderedMap->end;
	movq	%rax, 16(%rdx)	 # _11, _10->prev
 # Deep_UnorderedMap.c:176: 			unorderedMap->size++;
	addq	$1, 32(%rbx)	 #, unorderedMap_53(D)->size
 # Deep_UnorderedMap.c:177: 			if (unorderedMap->end != NULL)
	testq	%rax, %rax	 # _11
	je	.L61	 #,
 # Deep_UnorderedMap.c:178: 				unorderedMap->end->next = unorderedMap->hashes[index];
	movq	0(%rbp), %rdx	 # *_4, _14
 # Deep_UnorderedMap.c:178: 				unorderedMap->end->next = unorderedMap->hashes[index];
	movq	%rdx, 8(%rax)	 # _14, _11->next
.L61:
 # Deep_UnorderedMap.c:179: 			unorderedMap->end = unorderedMap->hashes[index];
	movq	0(%rbp), %rax	 # *_4, _15
 # Deep_UnorderedMap.c:180: 			if (unorderedMap->start == NULL)
	cmpq	$0, 8(%rbx)	 #, unorderedMap_53(D)->start
 # Deep_UnorderedMap.c:179: 			unorderedMap->end = unorderedMap->hashes[index];
	movq	%rax, 16(%rbx)	 # _15, unorderedMap_53(D)->end
 # Deep_UnorderedMap.c:180: 			if (unorderedMap->start == NULL)
	je	.L75	 #,
.L62:
 # Deep_UnorderedMap.c:184: 			memcpy((unsigned char*)unorderedMap->hashes[index] + unorderedMap->keyOffset, key, unorderedMap->keyTypeSize);
	movq	48(%rbx), %r8	 # unorderedMap_53(D)->keyTypeSize,
	movq	80(%rbx), %rcx	 # unorderedMap_53(D)->keyOffset, unorderedMap_53(D)->keyOffset
	movq	%r12, %rdx	 # key,
	addq	0(%rbp), %rcx	 # *_4, tmp140
	call	memcpy	 #
 # Deep_UnorderedMap.c:186: 			return (unsigned char*)unorderedMap->hashes[index] + unorderedMap->valueOffset;
	movq	(%rbx), %rdx	 # unorderedMap_53(D)->hashes, unorderedMap_53(D)->hashes
	movq	88(%rbx), %rax	 # unorderedMap_53(D)->valueOffset, unorderedMap_53(D)->valueOffset
	addq	(%rdx,%r13,8), %rax	 # *_22, <retval>
 # Deep_UnorderedMap.c:230: }
	addq	$40, %rsp	 #,
	popq	%rbx	 #
	popq	%rsi	 #
	popq	%rdi	 #
	popq	%rbp	 #
	popq	%r12	 #
	popq	%r13	 #
	ret	
.L75:
 # Deep_UnorderedMap.c:181: 				unorderedMap->start = unorderedMap->hashes[index];
	movq	%rax, 8(%rbx)	 # _15, unorderedMap_53(D)->start
	jmp	.L62	 #
.L64:
 # Deep_UnorderedMap.c:190: 			return NULL;
	xorl	%eax, %eax	 # <retval>
	jmp	.L57	 #
	.seh_endproc
	.p2align 4
	.globl	_Deep_UnorderedMap_Erase
	.def	_Deep_UnorderedMap_Erase;	.scl	2;	.type	32;	.endef
	.seh_proc	_Deep_UnorderedMap_Erase
_Deep_UnorderedMap_Erase:
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
	subq	$32, %rsp	 #,
	.seh_stackalloc	32
	.seh_endprologue
 # Deep_UnorderedMap.c:238: 		struct Deep_UnorderedMap_HashSlot* prevhashSlot = NULL;
	xorl	%edi, %edi	 # prevhashSlot
 # Deep_UnorderedMap.c:234: 	const size_t index = hash % unorderedMap->bucketSize;
	movq	%rdx, %rax	 # tmp118, tmp118
	xorl	%edx, %edx	 # index
 # Deep_UnorderedMap.c:233: {
	movq	%rcx, %rbx	 # tmp117, unorderedMap
	movq	%r8, %rsi	 # tmp119, key
 # Deep_UnorderedMap.c:234: 	const size_t index = hash % unorderedMap->bucketSize;
	divq	24(%rcx)	 # unorderedMap_31(D)->bucketSize
 # Deep_UnorderedMap.c:235: 	if (unorderedMap->hashes[index] != NULL)
	movq	(%rcx), %rax	 # unorderedMap_31(D)->hashes, unorderedMap_31(D)->hashes
	movq	(%rax,%rdx,8), %r12	 # *_4, hashSlot
 # Deep_UnorderedMap.c:234: 	const size_t index = hash % unorderedMap->bucketSize;
	movq	%rdx, %rbp	 # index, index
 # Deep_UnorderedMap.c:235: 	if (unorderedMap->hashes[index] != NULL)
	testq	%r12, %r12	 # hashSlot
	jne	.L77	 #,
	jmp	.L76	 #
	.p2align 4,,10
	.p2align 3
.L79:
	movq	%r12, %rdi	 # hashSlot, prevhashSlot
 # Deep_UnorderedMap.c:258: 			if (hashSlot->_next)
	testq	%rax, %rax	 # _22
	je	.L76	 #,
	movq	%rax, %r12	 # _22, hashSlot
.L77:
 # Deep_UnorderedMap.c:241: 			if (unorderedMap->keyCompareFunc((unsigned char*)hashSlot + unorderedMap->keyOffset, key, unorderedMap->keyTypeSize))
	movq	80(%rbx), %rcx	 # unorderedMap_31(D)->keyOffset, tmp111
	movq	48(%rbx), %r8	 # unorderedMap_31(D)->keyTypeSize,
	movq	%rsi, %rdx	 # key,
	addq	%r12, %rcx	 # hashSlot, tmp111
	call	*40(%rbx)	 # unorderedMap_31(D)->keyCompareFunc
 # Deep_UnorderedMap.c:241: 			if (unorderedMap->keyCompareFunc((unsigned char*)hashSlot + unorderedMap->keyOffset, key, unorderedMap->keyTypeSize))
	testl	%eax, %eax	 # tmp120
 # Deep_UnorderedMap.c:244: 					prevhashSlot->_next = hashSlot->_next;
	movq	(%r12), %rax	 # hashSlot_23->_next, pretmp_52
 # Deep_UnorderedMap.c:241: 			if (unorderedMap->keyCompareFunc((unsigned char*)hashSlot + unorderedMap->keyOffset, key, unorderedMap->keyTypeSize))
	je	.L79	 #,
 # Deep_UnorderedMap.c:243: 				if (prevhashSlot)
	testq	%rdi, %rdi	 # prevhashSlot
	je	.L80	 #,
 # Deep_UnorderedMap.c:244: 					prevhashSlot->_next = hashSlot->_next;
	movq	%rax, (%rdi)	 # pretmp_52, prevhashSlot_24->_next
.L81:
 # Deep_UnorderedMap.c:248: 				if (hashSlot->prev)
	movq	16(%r12), %rax	 # hashSlot_23->prev, _17
 # Deep_UnorderedMap.c:248: 				if (hashSlot->prev)
	testq	%rax, %rax	 # _17
	je	.L82	 #,
 # Deep_UnorderedMap.c:249: 					hashSlot->prev->next = hashSlot->next;
	movq	8(%r12), %rdx	 # hashSlot_23->next, pretmp_51
 # Deep_UnorderedMap.c:249: 					hashSlot->prev->next = hashSlot->next;
	movq	%rdx, 8(%rax)	 # pretmp_51, _17->next
.L82:
 # Deep_UnorderedMap.c:250: 				if (hashSlot->next)
	movq	8(%r12), %rdx	 # hashSlot_23->next, _19
 # Deep_UnorderedMap.c:250: 				if (hashSlot->next)
	testq	%rdx, %rdx	 # _19
	je	.L83	 #,
 # Deep_UnorderedMap.c:251: 					hashSlot->next->prev = hashSlot->prev;
	movq	%rax, 16(%rdx)	 # _17, _19->prev
.L83:
 # Deep_UnorderedMap.c:253: 				free(hashSlot);
	movq	%r12, %rcx	 # hashSlot,
	call	free	 #
 # Deep_UnorderedMap.c:254: 				unorderedMap->size--;
	subq	$1, 32(%rbx)	 #, unorderedMap_31(D)->size
.L76:
 # Deep_UnorderedMap.c:267: }
	addq	$32, %rsp	 #,
	popq	%rbx	 #
	popq	%rsi	 #
	popq	%rdi	 #
	popq	%rbp	 #
	popq	%r12	 #
	ret	
	.p2align 4,,10
	.p2align 3
.L80:
 # Deep_UnorderedMap.c:246: 					unorderedMap->hashes[index] = hashSlot->_next;
	movq	(%rbx), %rdx	 # unorderedMap_31(D)->hashes, unorderedMap_31(D)->hashes
	movq	%rax, (%rdx,%rbp,8)	 # pretmp_52, *_15
	jmp	.L81	 #
	.seh_endproc
	.section .rdata,"dr"
	.align 16
.LC0:
	.quad	13
	.quad	0
	.align 8
.LC1:
	.long	1717986918
	.long	1072064102
	.ident	"GCC: (Rev1, Built by MSYS2 project) 11.2.0"
	.def	calloc;	.scl	2;	.type	32;	.endef
	.def	memcmp;	.scl	2;	.type	32;	.endef
	.def	free;	.scl	2;	.type	32;	.endef
	.def	malloc;	.scl	2;	.type	32;	.endef
	.def	memcpy;	.scl	2;	.type	32;	.endef
