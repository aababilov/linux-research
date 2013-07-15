#define buf_len 200 /* макрос для препроцессора – длина буфера */
        .bss    /* секция неинициализированных данных */
buf:
        .space buf_len /* размер буфера – 200 байт */
     
        .text  /* секция кода */
.globl _start  /* глобальный символ */
_start:
EchoLoop:
        //считываем строку, в eax будет полученная длина
        movl    $buf_len, %edx
        movl    $buf, %ecx
        movl    $0, %ebx
        movl    $3, %eax  /* 3 = sys_read */
        int     $0x80
        // сохраним длину считанной строки
        pushl   %eax
        // сначала выделим первый символ
        movb	(buf), %al                  /* поместим первый символ в %al */
        // сравним с символом '\n'
        cmpb    $0xa, %al
        jz      EchoDone
        
        // печатаем строку
        popl    %edx
        movl    $buf, %ecx
        movl    $1, %ebx
        movl    $4, %eax     /* 4 =  sys_write */
        int     $0x80
        //безусловный переход
        jmp     EchoLoop
EchoDone:
        // выход
        movl    $0, %ebx 
        movl    $1, %eax    /* 1 = sys_exit */
        int     $0x80
