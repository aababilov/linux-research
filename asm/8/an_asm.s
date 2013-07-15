        //-17(%ebp) is c
        //%edx is num
        //%cl is oper
        //%esi is p
        //%ebx is ans
        .bss
buf:
        .space 1024
        .section        .rodata
msg_div_by_zero:
	.string	"division by zero!"
msg_bad_oper:
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
        //p = buf
	movl	$buf, %esi
	pushl	%ebx
	xorl	%ebx, %ebx
	pushl	%ecx
	subl	$12, %esp
	pushl	$1023
	pushl	$buf
	pushl	$0
	call	read
	xorl	%edx, %edx
	movb	$'+', %cl
	addl	$16, %esp
	jmp	start_calc_ccl
restart_calc_ccl:
        //oper = c
	movb	-17(%ebp), %cl
        //num = 0
	xorl	%edx, %edx
start_calc_ccl:
	movb	(%esi), %al
	incl	%esi
	movb	%al, -17(%ebp)
	subb	$'0', %al
	cmpb	$9, %al
	ja	not_digit
        //num = num * 10
	imull	$10, %edx, %edx
	movzbl	-17(%ebp),%eax
        //num = num + c - '0'
	leal	-'0'(%edx,%eax), %edx
	jmp	start_calc_ccl
not_digit:
	cmpb	$'+', %cl
	jne	not_add
	addl	%edx, %ebx
	jmp	test_endl
not_add:
	cmpb	$'-', %cl
	jne	not_sub
	subl	%edx, %ebx
	jmp	test_endl
not_sub:
	cmpb	$'*', %cl
	jne	not_mull
	imull	%edx, %ebx
	jmp	test_endl
not_mull:
	cmpb	$'/', %cl
	jne	bad_oper
        //если %edx == 0...
	testl	%edx, %edx
	je	div_by_zero
	movl	%ebx, %eax
	movl	%edx, %ecx
        //eax -> edx:eax
	cltd
	idivl	%ecx
	movl	%eax, %ebx
	jmp	test_endl
div_by_zero:
	subl	$12, %esp
	pushl	$msg_div_by_zero
	call	puts
	jmp	clear_stack
bad_oper:
	movsbl	%cl,%eax
	pushl	%edx
	pushl	%eax
	pushl	%eax
	pushl	$msg_bad_oper
	call	printf
clear_stack:
        addl	$16, %esp
test_endl:
	cmpb	$0, -17(%ebp)
	je	calc_ccl_done
	cmpb	$'\n', -17(%ebp)
	jne	restart_calc_ccl
calc_ccl_done:
        //c = 0
	xorl	%ecx, %ecx
	testl	%ebx, %ebx
	movb	$0, (%esi)
	jns	bin2str
        //ans *= -1; c = 1
	negl	%ebx
	movb	$1, %cl
bin2str:
	movl	%ebx, %eax
	movl	$10, %edx
	movl	%edx, %edi
        //eax -> edx:eax
	cltd
	idivl	%edi
	decl	%esi
	addb	$'0', %dl
	testl	%eax, %eax
	movl	%eax, %ebx
        //*p = new_dig
	movb	%dl, (%esi)
	jne	bin2str
        //c == 0 => *p = '-'
	testb	%cl, %cl
	je	write_str
	decl	%esi
	movb	$'-', (%esi)
write_str:
	subl	$12, %esp
	pushl	%esi
	call	puts
	movl	$0, (%esp)
	call	_exit
