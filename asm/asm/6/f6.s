        .data
STRING_1:
        .string "Привет!\n"
STRING_2:
        .string "Следующее сообщение\n"
STRING_3:
        .string "Ещё одно сообщение\n"        
        .text
        //функция принимает адрес строки в стеке
        .type PrintString, @function
PrintString:
        pushl   %ebp
        movl    %esp, %ebp
        pushl   %esi
        
        movl    8(%ebp), %esi
Cycle:  
        movb    (%esi), %dl
        andb    %dl, %dl
        jz      EndFun
        pushl   $1
        pushl   %esi
        pushl   $1
        call    write
        addl    $12, %esp
        incl    %esi
        jmp     Cycle
        
EndFun:
        popl    %esi
        movl    %ebp, %esp
        popl    %ebp
        ret

        .globl main
        .type main, @function
main:
        pushl   $STRING_1
        call    PrintString
        movl    $STRING_2, (%esp)
        call    PrintString
        movl    $STRING_3, (%esp)
        call    PrintString

        pushl   $0
        call    _exit
