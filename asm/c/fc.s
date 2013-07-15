	.file	"fc.c"
.globl buf
	.data
	.align 32
	.type	buf, @object
	.size	buf, 167
buf:
	.string	"www"
	.zero	163
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
	subl	$20, %esp
	movzbl	buf+1, %eax
	movsbl	%al,%eax
	movl	%eax, f
	movl	$12, 8(%esp)
	movl	$buf, 4(%esp)
	movl	$1, (%esp)
	call	write
	movl	$0, %eax
	addl	$20, %esp
	popl	%ecx
	popl	%ebp
	leal	-4(%ecx), %esp
	ret
	.size	main, .-main
	.comm	b,12,1
	.comm	f,4,4
	.ident	"GCC: (GNU) 4.1.2"
	.section	.note.GNU-stack,"",@progbits
