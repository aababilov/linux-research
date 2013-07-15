        .data
fmt:
        .string "%s\n"
STRING1:
        .string "Фамилия$"
STRING2:
        .string "Имя$"
STRING3:
        .string "Отчество$"
        .text
        
.macro printf str
        pushl   \str
        pushl   $fmt
        call    printf
        addl    $8, %esp
.endm
        
        .globl main
        .type main, @function
main:
        printf  $STRING1
        printf  $STRING2
        printf  $STRING3
        // выход
        pushl   $0
        call    _exit
        
        .size main, . - main
