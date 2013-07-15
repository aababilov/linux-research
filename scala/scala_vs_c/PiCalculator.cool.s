	.file	"PiCalculator.cool.c"
	.section	.rodata
.LC3:
	.string	"%d ms\n"
.LC4:
	.string	"%.8lf\n"
	.text
.globl main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	movl	$100000000, -28(%rbp)
	movl	$0, -32(%rbp)
	movl	$0, %eax
	movq	%rax, -24(%rbp)
	.cfi_offset 3, -24
	call	clock
	movq	%rax, -40(%rbp)
	movl	-32(%rbp), %ebx
	jmp	.L2
.L5:
	movl	%ebx, %eax
	andl	$1, %eax
	testl	%eax, %eax
	jne	.L3
	movsd	.LC1(%rip), %xmm0
	jmp	.L4
.L3:
	movsd	.LC2(%rip), %xmm0
.L4:
	leal	(%rbx,%rbx), %eax
	addl	$1, %eax
	cvtsi2sd	%eax, %xmm1
	divsd	%xmm1, %xmm0
	movsd	-24(%rbp), %xmm1
	addsd	%xmm1, %xmm0
	movsd	%xmm0, -24(%rbp)
	addl	$1, %ebx
.L2:
	cmpl	-28(%rbp), %ebx
	jl	.L5
	call	clock
	movq	%rax, %rcx
	subq	-40(%rbp), %rcx
	movabsq	$2361183241434822607, %rdx
	movq	%rcx, %rax
	imulq	%rdx
	sarq	$7, %rdx
	movq	%rcx, %rax
	sarq	$63, %rax
	movq	%rdx, %rcx
	subq	%rax, %rcx
	movq	%rcx, %rax
	movl	%eax, %edx
	movl	$.LC3, %eax
	movl	%edx, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf
	movl	$.LC4, %eax
	movsd	-24(%rbp), %xmm0
	movq	%rax, %rdi
	movl	$1, %eax
	call	printf
	movl	$0, %eax
	addq	$40, %rsp
	popq	%rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.section	.rodata
	.align 8
.LC1:
	.long	0
	.long	1074790400
	.align 8
.LC2:
	.long	0
	.long	-1072693248
	.ident	"GCC: (Gentoo 4.5.3-r2 p1.1, pie-0.4.7) 4.5.3"
	.section	.note.GNU-stack,"",@progbits
