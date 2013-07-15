	.file	"c.c"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"division by zero!"
.LC1:
	.string	"bad operator %c (0x%hhx)!\n"
	.text
	.p2align 4,,15
.globl main
	.type	main, @function
main:
	leal	4(%esp), %ecx
	andl	$-16, %esp
	pushl	-4(%ecx)
	movl	$1023, %edx
	movl	$buf, %eax
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	movl	$buf, %esi
	pushl	%ebx
	xorl	%ebx, %ebx
	pushl	%ecx
	subl	$24, %esp
	movl	%edx, 8(%esp)
	movl	%eax, 4(%esp)
	movl	$0, (%esp)
	call	read
	xorl	%edx, %edx
	movb	$43, %cl
.L33:
	movzbl	(%esi), %edi
	incl	%esi
	leal	-48(%edi), %eax
	cmpl	$9, %eax
	ja	.L3
.L35:
	leal	(%edx,%edx,4), %eax
	leal	-48(%edi,%eax,2), %edx
	movzbl	(%esi), %edi
	incl	%esi
	leal	-48(%edi), %eax
	cmpl	$9, %eax
	jbe	.L35
.L3:
	cmpb	$43, %cl
	je	.L36
	cmpb	$45, %cl
	je	.L37
	cmpb	$42, %cl
	.p2align 4,,5
	je	.L38
	cmpb	$47, %cl
	.p2align 4,,5
	je	.L39
	movzbl	%cl, %eax
	movl	%eax, 8(%esp)
	movl	%eax, 4(%esp)
	movl	$.LC1, (%esp)
	call	printf
	.p2align 4,,15
.L7:
	testl	%edi, %edi
	je	.L16
.L40:
	cmpl	$10, %edi
	je	.L16
	movl	%edi, %ecx
	xorl	%edx, %edx
	.p2align 4,,3
	jmp	.L33
.L39:
	testl	%edx, %edx
	.p2align 4,,3
	je	.L14
	movl	%ebx, %eax
	movl	%edx, %ecx
	cltd
	idivl	%ecx
	testl	%edi, %edi
	movl	%eax, %ebx
	jne	.L40
	.p2align 4,,15
.L16:
	xorl	%ecx, %ecx
	testl	%ebx, %ebx
	movb	$0, (%esi)
	js	.L41
	.p2align 4,,15
.L28:
	movl	%ebx, %eax
	movl	$1717986919, %edx
	imull	%edx
	movl	%ebx, %eax
	sarl	$31, %eax
	decl	%esi
	sarl	$2, %edx
	subl	%eax, %edx
	leal	(%edx,%edx,4), %eax
	addl	%eax, %eax
	subl	%eax, %ebx
	movb	%bl, %al
	movl	%edx, %ebx
	addb	$48, %al
	testl	%edx, %edx
	movb	%al, (%esi)
	jne	.L28
	testl	%ecx, %ecx
	je	.L22
	decl	%esi
	movb	$45, (%esi)
.L22:
	movl	%esi, (%esp)
	call	puts
	movl	$0, (%esp)
	call	_exit
.L36:
	addl	%edx, %ebx
	jmp	.L7
.L37:
	subl	%edx, %ebx
	.p2align 4,,2
	jmp	.L7
.L38:
	imull	%edx, %ebx
	.p2align 4,,5
	jmp	.L7
.L41:
	negl	%ebx
	movl	$1, %ecx
	.p2align 4,,3
	jmp	.L28
.L14:
	movl	$.LC0, (%esp)
	call	puts
	jmp	.L7
	.size	main, .-main
	.comm	buf,1024,32
	.ident	"GCC: (GNU) 4.1.2"
	.section	.note.GNU-stack,"",@progbits
