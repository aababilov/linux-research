        .data
fmt:
	.string "%s"        
String1:
	.string "Большой "
String2:	
        .string "Привет!\n"

	.bss
.globl FINALSTRING
FINALSTRING:
	.space 100
		        
        .text
        .globl main
        .type main, @function
main:
        pushl   $String2
        pushl   $String1
        call    ConCatStrings
        
	movl    $FINALSTRING, 4(%esp)
	movl    $fmt, (%esp)
        call    printf
        addl    $4, %esp

        pushl   $0
        call    _exit

        .size main, . - main
