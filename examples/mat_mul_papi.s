	.file	"mat_mul_papi.c"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC2:
	.string	"loop"
.LC4:
	.string	"clock time: %f(s)\n"
	.text
	.p2align 4,,15
	.globl	mat_mul
	.type	mat_mul, @function
mat_mul:
.LFB22:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	movl	%edi, %r12d
	movl	$16384, %edi
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$136, %rsp
	.cfi_def_cfa_offset 192
	call	malloc
	movq	%rax, 88(%rsp)
	movq	%rax, %rbx
	movq	%rax, %rbp
	leaq	16384(%rax), %r14
.L2:
	movl	$4096, %edi
	addq	$8, %rbx
	call	malloc
	movq	%rax, -8(%rbx)
	cmpq	%rbx, %r14
	jne	.L2
	movl	$4096, %edi
	call	malloc
	movq	%rax, %r13
	movq	%rax, %rbx
	leaq	4096(%rax), %rax
	movq	%rax, (%rsp)
	movq	%r13, %r15
.L3:
	movl	$8192, %edi
	addq	$8, %r15
	call	malloc
	movq	%rax, -8(%r15)
	cmpq	%r15, (%rsp)
	jne	.L3
	movl	$16384, %edi
	call	malloc
	movq	%rax, 80(%rsp)
	movq	%rax, %r15
	addq	$16384, %rax
	movq	%rax, 8(%rsp)
.L4:
	movl	$8192, %edi
	addq	$8, %r15
	call	malloc
	movq	%rax, -8(%r15)
	cmpq	%r15, 8(%rsp)
	jne	.L4
	movl	%r12d, %eax
	movl	$1717986919, %edx
	movsd	.LC0(%rip), %xmm0
	imull	%edx
	movl	%r12d, %eax
	sarl	$31, %eax
	sarl	$2, %edx
	subl	%eax, %edx
	movl	%edx, 100(%rsp)
.L5:
	movq	0(%rbp), %rax
	leaq	4096(%rax), %rdx
.L6:
	movsd	%xmm0, (%rax)
	addq	$8, %rax
	cmpq	%rax, %rdx
	jne	.L6
	addq	$8, %rbp
	cmpq	%rbp, %r14
	jne	.L5
	movsd	.LC1(%rip), %xmm0
.L7:
	movq	(%rbx), %rax
	leaq	8192(%rax), %rdx
.L8:
	movsd	%xmm0, (%rax)
	addq	$8, %rax
	cmpq	%rax, %rdx
	jne	.L8
	addq	$8, %rbx
	cmpq	%rbx, (%rsp)
	jne	.L7
	movl	$.LC2, %edi
	call	PAPI_hl_region_begin
	xorl	%esi, %esi
	leaq	112(%rsp), %rdi
	call	gettimeofday
	pxor	%xmm1, %xmm1
	pxor	%xmm0, %xmm0
	movq	%r13, %rsi
	cvtsi2sdq	112(%rsp), %xmm1
	movl	$0, 96(%rsp)
	cvtsi2sdq	120(%rsp), %xmm0
	divsd	.LC3(%rip), %xmm0
	addsd	%xmm1, %xmm0
	movsd	%xmm0, 104(%rsp)
	cmpl	$9, %r12d
	jle	.L11
.L10:
	movq	$0, 72(%rsp)
	movq	%rsi, %rcx
.L16:
	movq	72(%rsp), %rax
	movq	88(%rsp), %rdi
	xorl	%esi, %esi
	movq	80(%rsp), %rbx
	movq	(%rdi,%rax), %rdi
	movq	(%rbx,%rax), %rax
	movq	%rax, 64(%rsp)
.L15:
	movq	64(%rsp), %rax
	leaq	24(%rsi), %rbx
	leaq	120(%rsi), %r8
	xorl	%edx, %edx
	movq	%rbx, 48(%rsp)
	leaq	32(%rsi), %rbx
	leaq	8(%rsi), %r15
	movsd	(%rax), %xmm2
	movsd	8(%rax), %xmm3
	movq	%rbx, 40(%rsp)
	leaq	40(%rsi), %rbx
	movq	%rbx, 32(%rsp)
	leaq	48(%rsi), %rbx
	leaq	16(%rsi), %r14
	movsd	16(%rax), %xmm14
	movq	%r8, 56(%rsp)
	movsd	24(%rax), %xmm13
	leaq	64(%rsi), %r13
	leaq	72(%rsi), %r12
	movsd	%xmm2, 8(%rsp)
	movsd	32(%rax), %xmm12
	leaq	80(%rsi), %rbp
	movsd	40(%rax), %xmm11
	movsd	%xmm3, (%rsp)
	movsd	48(%rax), %xmm10
	movsd	72(%rax), %xmm7
	leaq	96(%rsi), %r11
	movq	%rbx, 24(%rsp)
	movsd	56(%rax), %xmm9
	leaq	56(%rsi), %rbx
	leaq	104(%rsi), %r10
	movsd	64(%rax), %xmm8
	movsd	80(%rax), %xmm6
	movq	%rbx, 16(%rsp)
	leaq	112(%rsi), %r9
	movsd	88(%rax), %xmm5
	movsd	96(%rax), %xmm4
	leaq	88(%rsi), %rbx
	movsd	104(%rax), %xmm3
	movsd	112(%rax), %xmm2
	movsd	120(%rax), %xmm1
	.p2align 4,,10
	.p2align 3
.L12:
	movq	(%rcx,%rdx), %rax
	movsd	(%rdi,%rdx), %xmm0
	addq	$8, %rdx
	movq	48(%rsp), %r8
	movsd	(%rax,%rsi), %xmm15
	mulsd	%xmm0, %xmm15
	addsd	8(%rsp), %xmm15
	movsd	%xmm15, 8(%rsp)
	movsd	(%rax,%r15), %xmm15
	mulsd	%xmm0, %xmm15
	addsd	(%rsp), %xmm15
	movsd	%xmm15, (%rsp)
	movsd	(%rax,%r14), %xmm15
	mulsd	%xmm0, %xmm15
	addsd	%xmm15, %xmm14
	movsd	(%rax,%r8), %xmm15
	movq	40(%rsp), %r8
	mulsd	%xmm0, %xmm15
	addsd	%xmm15, %xmm13
	movsd	(%rax,%r8), %xmm15
	movq	32(%rsp), %r8
	mulsd	%xmm0, %xmm15
	addsd	%xmm15, %xmm12
	movsd	(%rax,%r8), %xmm15
	movq	24(%rsp), %r8
	mulsd	%xmm0, %xmm15
	addsd	%xmm15, %xmm11
	movsd	(%rax,%r8), %xmm15
	movq	16(%rsp), %r8
	mulsd	%xmm0, %xmm15
	addsd	%xmm15, %xmm10
	movsd	(%rax,%r8), %xmm15
	movq	56(%rsp), %r8
	mulsd	%xmm0, %xmm15
	addsd	%xmm15, %xmm9
	movsd	(%rax,%r13), %xmm15
	mulsd	%xmm0, %xmm15
	addsd	%xmm15, %xmm8
	movsd	(%rax,%r12), %xmm15
	mulsd	%xmm0, %xmm15
	addsd	%xmm15, %xmm7
	movsd	(%rax,%rbp), %xmm15
	mulsd	%xmm0, %xmm15
	addsd	%xmm15, %xmm6
	movsd	(%rax,%rbx), %xmm15
	mulsd	%xmm0, %xmm15
	addsd	%xmm15, %xmm5
	movsd	(%rax,%r11), %xmm15
	mulsd	%xmm0, %xmm15
	addsd	%xmm15, %xmm4
	movsd	(%rax,%r10), %xmm15
	mulsd	%xmm0, %xmm15
	addsd	%xmm15, %xmm3
	movsd	(%rax,%r9), %xmm15
	mulsd	%xmm0, %xmm15
	mulsd	(%rax,%r8), %xmm0
	addsd	%xmm15, %xmm2
	addsd	%xmm0, %xmm1
	cmpq	$4096, %rdx
	jne	.L12
	movq	64(%rsp), %rax
	movsd	8(%rsp), %xmm0
	subq	$-128, %rsi
	movsd	%xmm0, (%rax)
	movsd	(%rsp), %xmm0
	subq	$-128, %rax
	movsd	%xmm14, -112(%rax)
	movsd	%xmm0, -120(%rax)
	movsd	%xmm13, -104(%rax)
	movsd	%xmm12, -96(%rax)
	movsd	%xmm11, -88(%rax)
	movsd	%xmm10, -80(%rax)
	movsd	%xmm9, -72(%rax)
	movsd	%xmm8, -64(%rax)
	movsd	%xmm7, -56(%rax)
	movsd	%xmm6, -48(%rax)
	movsd	%xmm5, -40(%rax)
	movsd	%xmm4, -32(%rax)
	movsd	%xmm3, -24(%rax)
	movsd	%xmm2, -16(%rax)
	movsd	%xmm1, -8(%rax)
	movq	%rax, 64(%rsp)
	cmpq	$8192, %rsi
	jne	.L15
	addq	$8, 72(%rsp)
	movq	72(%rsp), %rax
	cmpq	$16384, %rax
	jne	.L16
	addl	$1, 96(%rsp)
	movq	%rcx, %rsi
	movl	96(%rsp), %eax
	cmpl	%eax, 100(%rsp)
	jg	.L10
.L11:
	xorl	%esi, %esi
	leaq	112(%rsp), %rdi
	call	gettimeofday
	pxor	%xmm1, %xmm1
	pxor	%xmm0, %xmm0
	movl	$.LC2, %edi
	cvtsi2sdq	112(%rsp), %xmm1
	cvtsi2sdq	120(%rsp), %xmm0
	divsd	.LC3(%rip), %xmm0
	addsd	%xmm1, %xmm0
	movsd	%xmm0, (%rsp)
	call	PAPI_hl_region_end
	movsd	(%rsp), %xmm0
	subsd	104(%rsp), %xmm0
	movl	$.LC4, %edi
	movl	$1, %eax
	call	printf
	movq	80(%rsp), %rax
	movq	(%rax), %rax
	movsd	(%rax), %xmm0
	addq	$136, %rsp
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE22:
	.size	mat_mul, .-mat_mul
	.p2align 4,,15
	.globl	timer
	.type	timer, @function
timer:
.LFB23:
	.cfi_startproc
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	xorl	%esi, %esi
	movq	%rsp, %rdi
	call	gettimeofday
	pxor	%xmm1, %xmm1
	pxor	%xmm0, %xmm0
	cvtsi2sdq	(%rsp), %xmm1
	cvtsi2sdq	8(%rsp), %xmm0
	divsd	.LC3(%rip), %xmm0
	addq	$24, %rsp
	.cfi_def_cfa_offset 8
	addsd	%xmm1, %xmm0
	ret
	.cfi_endproc
.LFE23:
	.size	timer, .-timer
	.section	.rodata.str1.1
.LC5:
	.string	"usage: %s <num>\n"
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC6:
	.string	"number of operations: <num> millions"
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB24:
	.cfi_startproc
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	cmpl	$2, %edi
	jne	.L35
	movq	8(%rsi), %rdi
	movl	$10, %edx
	xorl	%esi, %esi
	call	strtol
	leal	(%rax,%rax,4), %edi
	movl	$1000, %eax
	addl	%edi, %edi
	testl	%edi, %edi
	cmovle	%eax, %edi
	call	mat_mul
	xorl	%eax, %eax
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
.L35:
	.cfi_restore_state
	movq	(%rsi), %rsi
	movl	$.LC5, %edi
	xorl	%eax, %eax
	call	printf
	movl	$.LC6, %edi
	call	puts
	movl	$1, %edi
	call	exit
	.cfi_endproc
.LFE24:
	.size	main, .-main
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC0:
	.long	1413754136
	.long	1074340347
	.align 8
.LC1:
	.long	1841940611
	.long	1071931184
	.align 8
.LC3:
	.long	0
	.long	1093567616
	.ident	"GCC: (GNU) 8.4.1 20200928 (Red Hat 8.4.1-1)"
	.section	.note.GNU-stack,"",@progbits
