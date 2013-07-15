        .text
.globl ConCatStrings
        //функция принимает адрес строк в стеке
        .type ConCatStrings, @function
ConCatStrings:
        pushl	%ebp
	movl	%esp, %ebp
	pushl   %esi
	pushl   %edi

        movl    8(%ebp), %esi
        movl    $FINALSTRING, %edi
copy_loop:
        lodsb
        cmpb    $0, %al
        jz      end_loop
        stosb
        jmp     copy_loop
        
end_loop:
        movl    12(%ebp), %esi
            
copy_loop1:
        lodsb
        stosb
        cmpb    $0, %al
        jz      end_loop1
        jmp     copy_loop1
        
end_loop1:
        popl    %edi
        popl    %esi
	movl    %ebp, %esp
        popl    %ebp
        ret
