	.file	"badname.c"
	.section	.rodata
.LC0:
	.string	"./f\nret.txt"
	.text
.globl main
	.type	main, @function
main:
	leal	4(%esp), %ecx
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ecx
	subl	$36, %esp
	movl	$420, 8(%esp)
	movl	$65, 4(%esp)
	movl	$.LC0, (%esp)
	call	open
	movl	%eax, -8(%ebp)
	movl	-8(%ebp), %eax
	movl	%eax, (%esp)
	call	close
	movl	$0, %eax
	addl	$36, %esp
	popl	%ecx
	popl	%ebp
	leal	-4(%ecx), %esp
	ret
	.size	main, .-main
	.ident	"GCC: (GNU) 4.1.2"
	.section	.note.GNU-stack,"",@progbits
