	.file	"c.c"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"division by zero!"
.LC1:
	.string	"bad operator %c (0x%x)!\n"
	.text
.globl main
	.type	main, @function
main:
	leal	4(%esp), %ecx
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	movl	$buf, %esi
	pushl	%ebx
	xorl	%ebx, %ebx
	pushl	%ecx
	subl	$12, %esp
	pushl	$1023
	pushl	%esi
	pushl	$0
	call	read
	xorl	%edx, %edx
	movb	$43, %cl
	addl	$16, %esp
.L34:
	movb	(%esi), %al
	incl	%esi
	movb	%al, -17(%ebp)
	subb	$48, %al
	cmpb	$9, %al
	ja	.L3
	imull	$10, %edx, %edx
	movzbl	-17(%ebp), %eax
	leal	-48(%edx,%eax), %edx
	jmp	.L34
.L3:
	cmpb	$43, %cl
	jne	.L5
	addl	%edx, %ebx
	jmp	.L7
.L5:
	cmpb	$45, %cl
	jne	.L8
	subl	%edx, %ebx
	jmp	.L7
.L8:
	cmpb	$42, %cl
	jne	.L10
	imull	%edx, %ebx
	jmp	.L7
.L10:
	cmpb	$47, %cl
	jne	.L12
	testl	%edx, %edx
	je	.L14
	movl	%ebx, %eax
	movl	%edx, %ecx
	cltd
	idivl	%ecx
	movl	%eax, %ebx
	jmp	.L7
.L14:
	subl	$12, %esp
	pushl	$.LC0
	call	puts
	jmp	.L33
.L12:
	movsbl	%cl,%eax
	pushl	%edx
	pushl	%eax
	pushl	%eax
	pushl	$.LC1
	call	printf
.L33:
	addl	$16, %esp
.L7:
	cmpb	$0, -17(%ebp)
	je	.L16
	cmpb	$10, -17(%ebp)
	je	.L16
	movb	-17(%ebp), %cl
	xorl	%edx, %edx
	jmp	.L34
.L16:
	xorl	%ecx, %ecx
	testl	%ebx, %ebx
	movb	$0, (%esi)
	jns	.L28
	negl	%ebx
	movb	$1, %cl
.L28:
	movl	%ebx, %eax
	movl	$10, %edx
	movl	%edx, %edi
	cltd
	idivl	%edi
	decl	%esi
	addb	$48, %dl
	testl	%eax, %eax
	movl	%eax, %ebx
	movb	%dl, (%esi)
	jne	.L28
	testb	%cl, %cl
	je	.L22
	decl	%esi
	movb	$45, (%esi)
.L22:
	subl	$12, %esp
	pushl	%esi
	call	puts
	leal	-16(%ebp), %esp
	xorl	%eax, %eax
	popl	%ecx
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	leal	-4(%ecx), %esp
	ret
	.size	main, .-main
	.comm	buf,1024,32
	.ident	"GCC: (GNU) 4.1.2"
	.section	.note.GNU-stack,"",@progbits
