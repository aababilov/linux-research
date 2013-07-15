        //%ebp is c
        //%edx is num
        //%cl is oper
        //%esi is p
        //%ebx is ans
        .bss
buf:
        .space 1024
        .section .rodata         
msg_div_by_zero:
	.string	"division by zero!"
msg_bad_oper:
        .string	"bad operator %c (0x%x)!\n"
        .text
.globl main
        .type	main, @function
main:
        movl	$buf, %esi      # p = buf
        xorl	%ebx, %ebx      # ans = 0
        pushl	$1023
        pushl	$buf
        pushl	$0
        call	read             # reading
         
        xorl	%edx, %edx      # num = 0
        movb	$'+', %cl        # oper = '+'
        addl	$16, %esp
        jmp	start_calc_ccl
restart_calc_ccl:
        movl	%ebp, %ecx  # oper = c
        xorl	%edx, %edx      # num = 0
start_calc_ccl:
        movb	(%esi), %al     # %al = *p
        incl	%esi             # ++p
        movzbl	%al, %ebp       # c = %al
        subb	$'0', %al        # if ('0' <= c &&
        cmpb	$9, %al          # c <= '9')
        ja	not_digit
        imull	$10, %edx, %edx # num = num * 10
        movl	%ebp, %eax
        leal	-'0'(%edx,%eax), %edx #num = num + c - '0'
        jmp	start_calc_ccl
not_digit:
        cmpb	$'+', %cl        # oper == '+'
        jne	not_add
        addl	%edx, %ebx
        jmp	test_endl
not_add:
        cmpb	$'-', %cl        # oper == '-'
        jne	not_sub
        subl	%edx, %ebx
        jmp	test_endl
not_sub:
        cmpb	$'*', %cl        # oper == '*'
        jne	not_mull
        imull	%edx, %ebx
        jmp	test_endl
not_mull:
        cmpb	$'/', %cl        # oper == '/'
        jne	bad_oper
        testl	%edx, %edx      # if (num == 0)
        je	div_by_zero
        movl	%ebx, %eax
        movl	%edx, %ecx
        cltd                      # eax -> edx:eax
        idivl	%ecx
        movl	%eax, %ebx
        jmp	test_endl
div_by_zero:
        subl	$12, %esp
        pushl	$msg_div_by_zero
        call	puts
        jmp	clear_stack
bad_oper:
        movzbl	%cl,%eax
        pushl	%edx
        pushl	%eax
        pushl	%eax
        pushl	$msg_bad_oper
        call	printf
clear_stack:
         addl	$16, %esp
test_endl:
        cmpl	$0, %ebp
        je	calc_ccl_done
        cmpl	$'\n', %ebp
        jne	restart_calc_ccl
calc_ccl_done:
        xorl	%ecx, %ecx      # c = 0
        testl	%ebx, %ebx
         movl    $buf+1023, %esi
        movb	$0, (%esi)
        jns	bin2str
        negl	%ebx             # ans *= -1;
        movb	$1, %cl          # c = 1
bin2str:
        movl	%ebx, %eax
        movl	$10, %edx
        movl	%edx, %edi
        cltd                      # eax -> edx:eax
        idivl	%edi
        decl	%esi
        addb	$'0', %dl
        testl	%eax, %eax
        movl	%eax, %ebx
        movb	%dl, (%esi)     # *p = new_dig
        jne	bin2str
        testb	%cl, %cl         # c == 0 
        je	write_str
        decl	%esi
        movb	$'-', (%esi)    #*p = '-'
write_str:
        subl	$12, %esp
        pushl	%esi
        call	puts
        movl	$0, (%esp)
        call	_exit
