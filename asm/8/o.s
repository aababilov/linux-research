	.file	"c.c"
	.section	.rodata.str1.1,"aMS",@progbits,1
msg_div_by_zero:
	.string	"division by zero!"
.LC1:
	.string	"bad symbol %c (0x%x)!\n"
	.text
.globl main
	.type	main, @function
main:
	leal	4(%esp), %ecx
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	pushl	%edi
        //edi - p
	movl	$buf, %edi
	pushl	%esi
	xorl	%esi, %esi
	pushl	%ebx
	pushl	%ecx
	subl	$12, %esp
	pushl	$1023
	pushl	$buf
	pushl	$0
	call	read
        //edx - num
	xorl	%edx, %edx
	jmp	.L42
clear_cd:
	xorl	%edx, %edx
	xorl	%ecx, %ecx
.L43:
        //bl - c
	movb	(%edi), %bl
	incl	%edi
	movb	%bl, %al 
	subb	$48, %al
	cmpb	$9, %al
	ja	.L4
        //num = num * 10 
	imull	$10, %edx, %edx 
	movsbl	%bl,%eax
        //num = num + c - 48
	leal	-'0'(%edx,%eax), %edx
	jmp	.L43
.L4:
	cmpl	$1, %ecx
	jg	multiply_div
	testl	%ecx, %ecx
	jne	subtract
	addl	%edx, %esi
	jmp	analyze_nondig
subtract:
	subl	%edx, %esi
	jmp	analyze_nondig
multiply_div:
	cmpl	$2, %ecx
	jne	divide
	imull	%edx, %esi
	jmp	analyze_nondig
divide:
	testl	%edx, %edx
	je	div_by_zero
	movl	%esi, %eax
	movl	%edx, %ecx
	cltd
	idivl	%ecx
	movl	%eax, %esi
	jmp	analyze_nondig
div_by_zero:
	subl	$12, %esp
	pushl	$msg_div_by_zero
	call	puts
	addl	$16, %esp
analyze_nondig:
	testb	%bl, %bl
	je	zero_lf
	cmpb	$'\n', %bl
	je	zero_lf
	cmpb	$'+', %bl
	je	clear_cd
	cmpb	$'-', %bl
	jne	.L18
	xorl	%edx, %edx
	movl	$1, %ecx
	jmp	.L43
.L18:
	cmpb	$'*', %bl
	jne	.L20
	xorl	%edx, %edx
	movl	$2, %ecx
	jmp	.L43
.L20:
	cmpb	$'/', %bl
	jne	.L22
	xorl	%edx, %edx
	movl	$3, %ecx
	jmp	.L43
.L22:
	pushl	%eax
	movsbl	(%edi),%eax
	pushl	%eax
	movsbl	%bl,%eax
	pushl	%eax
	pushl	$.LC1
	call	printf
	xorl	%edx, %edx
.L42:
	xorl	%ecx, %ecx
	addl	$16, %esp
	jmp	.L43
zero_lf:
	xorl	%ecx, %ecx
	testl	%esi, %esi
	movb	$0, (%edi)
	jns	clear_cd5
	negl	%esi
	movb	$1, %cl
clear_cd5:
	movl	%esi, %eax
	movl	$10, %edx
	movl	%edx, %ebp
	cltd
	idivl	%ebp
	decl	%edi
	addb	$48, %dl
	testl	%eax, %eax
	movb	%dl, (%edi)
	movl	%eax, %esi
	jne	clear_cd5
	testb	%cl, %cl
	je	.L28
	decl	%edi
	movb	$45, (%edi)
.L28:
	subl	$12, %esp
	pushl	%edi
	call	puts
	movl	$0, (%esp)
	call	_exit
	.size	main, .-main
	.comm	buf,1024,32
	.ident	"GCC: (GNU) 4.1.2"
	.section	.note.GNU-stack,"",@progbits
