#define src_len 256
        .bss
src:
        .space src_len    
dest:
        .space src_len

        .text
        .globl main
        .type main, @function
main:
        //считываем строку, в %eax будет полученная длина
 	pushl   $src_len
	pushl   $src
	pushl   $0
	call    read
        // сохраним длину считанной строки
        push    %eax
        and     %eax, %eax
        //если длина строки 0 - выходим
        jz      Done
        
        //в esi - источник, в edi - приёмник
        //esi - от конца к началу; edi - от начала к концу
        movl    (%esp), %ecx
        movl    $src, %esi
        addl    %ecx, %esi
        movl    $dest, %edi        
        decl    %esi

        //цикл пересылки
RepeatLoop:
        movb    (%esi), %al
        movb    %al, (%edi)
        incl    %edi
        decl    %esi
        loop    RepeatLoop

        pushl   (%esp)
	pushl   $dest
	pushl   $1
	call    write

Done:   
        // выход
        pushl   $0
        call    _exit
        
        .size main, . - main
