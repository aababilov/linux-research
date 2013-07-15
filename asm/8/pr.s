	.file	"c.c"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"division by zero!"
.LC1:
	.string	"bad operator %c (0x%hhx)!\n"
	.text
.globl main
	.type	main, @function
main:
	leal	4(%esp), %ecx
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%esi
	movl	$buf, %esi
	pushl	%ebx
	xorl	%ebx, %ebx
	pushl	%ecx
	subl	$16, %esp
	pushl	$1023
	pushl	$buf
	pushl	$0
	call	read
	xorl	%edx, %edx
	movb	$43, %cl
	addl	$16, %esp
	jmp	.L35
.L3:
	movb	-14(%ebp), %cl
	xorl	%edx, %edx
.L35:
	movb	(%esi), %al
	incl	%esi
	movb	%al, -14(%ebp)
	subb	$48, %al
	cmpb	$9, %al
	ja	.L4
	imull	$10, %edx, %edx
	movzbl	-14(%ebp), %eax
	leal	-48(%edx,%eax), %edx
	jmp	.L35
.L4:
	cmpb	$43, %cl
	jne	.L6
	addl	%edx, %ebx
	jmp	.L8
.L6:
	cmpb	$45, %cl
	jne	.L9
	subl	%edx, %ebx
	jmp	.L8
.L9:
	cmpb	$42, %cl
	jne	.L11
	imull	%edx, %ebx
	jmp	.L8
.L11:
	cmpb	$47, %cl
	jne	.L13
	testl	%edx, %edx
	je	.L15
	movl	%ebx, %eax
	movl	%edx, %ecx
	cltd
	idivl	%ecx
	movl	%eax, %ebx
	jmp	.L8
.L15:
	subl	$12, %esp
	pushl	$.LC0
	call	puts
	jmp	.L34
.L13:
	movzbl	%cl, %eax
	pushl	%edx
	pushl	%eax
	pushl	%eax
	pushl	$.LC1
	call	printf
.L34:
	addl	$16, %esp
.L8:
	cmpb	$0, -14(%ebp)
	je	.L18
	cmpb	$10, -14(%ebp)
	jne	.L3
.L18:
	testl	%ebx, %ebx
	movb	$0, buf+1023
	movb	$0, -13(%ebp)
	jns	.L21
	negl	%ebx
	movb	$1, -13(%ebp)
.L21:
	movl	$buf+1023, %ecx
.L22:
	movl	%ebx, %eax
	movl	$10, %edx
	movl	%edx, %esi
	cltd
	idivl	%esi
	decl	%ecx
	addb	$48, %dl
	testl	%eax, %eax
	movl	%eax, %ebx
	movb	%dl, (%ecx)
	jne	.L22
	cmpb	$0, -13(%ebp)
	je	.L24
	decl	%ecx
	movb	$45, (%ecx)
.L24:
	subl	$12, %esp
	pushl	%ecx
	call	puts
	movl	$0, (%esp)
	call	_exit
	.size	main, .-main
	.comm	buf,1024,32
	.ident	"GCC: (GNU) 4.1.2"
	.section	.note.GNU-stack,"",@progbits
