	.file "f3.S"
        .data
BadInput:
        .string "Пожалуйста, введите Y или N\n"
        .set BadInput_len, . - BadInput
TimePrompt:
        .string "Это время после полудня? (Да/Нет)-[Y/N] "
        .set TimePrompt_len, . - TimePrompt
GoodMorning:
        .string "Доброе утро!\n"
        .set GoodMorning_len, . - GoodMorning
GoodAfternoon:
        .string "Здравствуйте!\n"
        .set GoodAfternoon_len, . - GoodAfternoon

#define buf_len 4        
        .bss
buf:
        .space buf_len    
        .text
        .globl _start
_start:
        // печатаем строку
        movl    $TimePrompt_len, %edx
	movl    $TimePrompt, %ecx
	movl    $1, %ebx
	movl    $4, %eax     /* 4 =  sys_write */
        int     $0x80

        //считываем строку, в eax будет полученная длина
 	movl    $buf_len, %edx
	movl    $buf, %ecx
	movl    $0, %ebx
	movl    $3, %eax  /* 3 = sys_read */
	int     $0x80
        // сначала выделим первый символ
        movzbl    (buf), %eax
        cmpb    $'Y', %al
        jz      IsAfternoon
        cmpb    $'y', %al
        jz      IsAfternoon
        cmpb    $'N', %al
        jz      IsMorning
        cmpb    $'n', %al
        jz      IsMorning
        
        movl    $BadInput_len, %edx
        movl    $BadInput, %ecx
        movl    $1, %ebx
        movl    $4, %eax
        int     $0x80
        jmp     _start 
IsAfternoon:
        movl    $GoodAfternoon_len, %edx
	movl    $GoodAfternoon, %ecx
        jmp     DisplayGreeting
IsMorning:
        movl    $GoodMorning_len, %edx
	movl    $GoodMorning, %ecx
DisplayGreeting:        
	movl    $1, %ebx
	movl    $4, %eax     /* 4 =  sys_write */
        int     $0x80
        // выход
        movl    $0, %ebx
        movl    $1, %eax   /* 1 = sys_exit */
	int     $0x80
