	.file	"loop_papi.c"
	.text
	.p2align 4,,15
	.globl	addmul
	.type	addmul, @function
addmul:
.LFB22:
	.cfi_startproc
	movl	%edi, %eax
	movl	$1717986919, %edx
	imull	%edx
	movl	%edi, %eax
	sarl	$31, %eax
	sarl	$2, %edx
	subl	%eax, %edx
	cmpl	$9, %edi
	jle	.L4
	movsd	.LC0(%rip), %xmm7
	xorl	%eax, %eax
	pxor	%xmm11, %xmm11
	movsd	.LC1(%rip), %xmm8
	movsd	.LC4(%rip), %xmm6
	movsd	.LC2(%rip), %xmm9
	movsd	.LC3(%rip), %xmm10
	movsd	.LC6(%rip), %xmm12
	movsd	.LC7(%rip), %xmm13
	movsd	.LC9(%rip), %xmm5
	movsd	.LC8(%rip), %xmm14
	.p2align 4,,10
	.p2align 3
.L3:
	mulsd	%xmm0, %xmm6
	addsd	%xmm0, %xmm5
	addsd	%xmm1, %xmm14
	addl	$1, %eax
	mulsd	%xmm1, %xmm10
	addsd	%xmm2, %xmm13
	addsd	%xmm3, %xmm12
	mulsd	%xmm2, %xmm9
	addsd	%xmm4, %xmm11
	mulsd	%xmm3, %xmm8
	mulsd	%xmm4, %xmm7
	addsd	%xmm4, %xmm6
	mulsd	%xmm0, %xmm5
	addsd	%xmm3, %xmm10
	mulsd	%xmm1, %xmm14
	addsd	%xmm2, %xmm9
	mulsd	%xmm2, %xmm13
	addsd	%xmm1, %xmm8
	mulsd	%xmm3, %xmm12
	addsd	%xmm0, %xmm7
	mulsd	%xmm4, %xmm11
	mulsd	%xmm0, %xmm6
	addsd	%xmm4, %xmm5
	mulsd	%xmm1, %xmm10
	addsd	%xmm3, %xmm14
	mulsd	%xmm2, %xmm9
	addsd	%xmm2, %xmm13
	mulsd	%xmm3, %xmm8
	addsd	%xmm1, %xmm12
	mulsd	%xmm4, %xmm7
	addsd	%xmm0, %xmm11
	addsd	%xmm4, %xmm6
	mulsd	%xmm4, %xmm5
	addsd	%xmm3, %xmm10
	mulsd	%xmm3, %xmm14
	addsd	%xmm2, %xmm9
	mulsd	%xmm2, %xmm13
	addsd	%xmm1, %xmm8
	mulsd	%xmm1, %xmm12
	addsd	%xmm0, %xmm7
	mulsd	%xmm0, %xmm11
	cmpl	%eax, %edx
	jg	.L3
	addsd	%xmm14, %xmm5
	movapd	%xmm5, %xmm0
	addsd	%xmm13, %xmm0
	addsd	%xmm12, %xmm0
	addsd	%xmm11, %xmm0
	addsd	%xmm6, %xmm0
	addsd	%xmm10, %xmm0
	addsd	%xmm9, %xmm0
	addsd	%xmm8, %xmm0
	addsd	%xmm7, %xmm0
	ret
	.p2align 4,,10
	.p2align 3
.L4:
	movsd	.LC10(%rip), %xmm0
	ret
	.cfi_endproc
.LFE22:
	.size	addmul, .-addmul
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
	divsd	.LC11(%rip), %xmm0
	addq	$24, %rsp
	.cfi_def_cfa_offset 8
	addsd	%xmm1, %xmm0
	ret
	.cfi_endproc
.LFE23:
	.size	timer, .-timer
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC12:
	.string	"usage: %s <num>\n"
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC13:
	.string	"number of operations: <num> millions"
	.section	.rodata.str1.1
.LC14:
	.string	"loop"
.LC20:
	.string	"result: %f\n"
.LC21:
	.string	"clock time: %f(s)\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB24:
	.cfi_startproc
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	subq	$48, %rsp
	.cfi_def_cfa_offset 64
	cmpl	$2, %edi
	jne	.L13
	movq	8(%rsi), %rdi
	movl	$10, %edx
	xorl	%esi, %esi
	call	strtol
	leaq	32(%rsp), %rdi
	imull	$1000000, %eax, %ebx
	movl	$1000, %eax
	testl	%ebx, %ebx
	cmovle	%eax, %ebx
	xorl	%esi, %esi
	call	gettimeofday
	pxor	%xmm1, %xmm1
	pxor	%xmm0, %xmm0
	movl	$.LC14, %edi
	cvtsi2sdq	32(%rsp), %xmm1
	cvtsi2sdq	40(%rsp), %xmm0
	divsd	.LC11(%rip), %xmm0
	addsd	%xmm1, %xmm0
	movsd	%xmm0, 8(%rsp)
	call	PAPI_hl_region_begin
	movsd	.LC15(%rip), %xmm4
	movl	%ebx, %edi
	movsd	.LC16(%rip), %xmm3
	movsd	.LC17(%rip), %xmm2
	movsd	.LC18(%rip), %xmm1
	movsd	.LC19(%rip), %xmm0
	call	addmul
	movl	$.LC14, %edi
	movsd	%xmm0, 24(%rsp)
	call	PAPI_hl_region_end
	xorl	%esi, %esi
	leaq	32(%rsp), %rdi
	call	gettimeofday
	pxor	%xmm2, %xmm2
	pxor	%xmm1, %xmm1
	movsd	24(%rsp), %xmm0
	cvtsi2sdq	32(%rsp), %xmm2
	movl	$.LC20, %edi
	movl	$1, %eax
	cvtsi2sdq	40(%rsp), %xmm1
	divsd	.LC11(%rip), %xmm1
	addsd	%xmm2, %xmm1
	movsd	%xmm1, 16(%rsp)
	call	printf
	movsd	16(%rsp), %xmm1
	subsd	8(%rsp), %xmm1
	movl	$.LC21, %edi
	movl	$1, %eax
	movapd	%xmm1, %xmm0
	call	printf
	addq	$48, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 16
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
.L13:
	.cfi_restore_state
	movq	(%rsi), %rsi
	movl	$.LC12, %edi
	xorl	%eax, %eax
	call	printf
	movl	$.LC13, %edi
	call	puts
	movl	$1, %edi
	call	exit
	.cfi_endproc
.LFE24:
	.size	main, .-main
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC0:
	.long	1717986918
	.long	1073112678
	.align 8
.LC1:
	.long	3435973837
	.long	1073007820
	.align 8
.LC2:
	.long	858993459
	.long	1072902963
	.align 8
.LC3:
	.long	2576980378
	.long	1072798105
	.align 8
.LC4:
	.long	0
	.long	1072693248
	.align 8
.LC6:
	.long	2576980378
	.long	-1077306983
	.align 8
.LC7:
	.long	2576980378
	.long	1070176665
	.align 8
.LC8:
	.long	2576980378
	.long	-1078355559
	.align 8
.LC9:
	.long	2576980378
	.long	1069128089
	.align 8
.LC10:
	.long	0
	.long	1075314688
	.align 8
.LC11:
	.long	0
	.long	1093567616
	.align 8
.LC15:
	.long	1841940611
	.long	1070882608
	.align 8
.LC16:
	.long	1413754136
	.long	1072243195
	.align 8
.LC17:
	.long	1413754136
	.long	1073291771
	.align 8
.LC18:
	.long	1841940611
	.long	1071931184
	.align 8
.LC19:
	.long	1413754136
	.long	1074340347
	.ident	"GCC: (GNU) 8.4.1 20200928 (Red Hat 8.4.1-1)"
	.section	.note.GNU-stack,"",@progbits
