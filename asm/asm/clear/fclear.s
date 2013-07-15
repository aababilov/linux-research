        .data
msg:
        .string "\033[H\033[J"
        .set msg_len, . - msg - 1

        .text
.globl _start
_start:
        // печатаем строку
        movl    $msg_len, %edx
        movl    $msg, %ecx
        movl    $1, %ebx
        movl    $4, %eax     /* 4 =  sys_write*/
        int     $0x80        
        // выход
        movl    $0, %ebx
        movl    $1, %eax   /* 1 = sys_exit*/
        int     $0x80
        
