	.file	"main.cpp"
	.section	.text._ZN6base_tC2Ev,"axG",@progbits,_ZN6base_tC2Ev,comdat
	.align 2
	.weak	_ZN6base_tC2Ev
	.type	_ZN6base_tC2Ev, @function
_ZN6base_tC2Ev:
.LFB14:
	pushl	%ebp
.LCFI0:
	movl	%esp, %ebp
.LCFI1:
	movl	8(%ebp), %eax
	movl	$_ZTV6base_t+8, (%eax)
	popl	%ebp
	ret
.LFE14:
	.size	_ZN6base_tC2Ev, .-_ZN6base_tC2Ev
	.section	.text._ZN5der_tC1Ev,"axG",@progbits,_ZN5der_tC1Ev,comdat
	.align 2
	.weak	_ZN5der_tC1Ev
	.type	_ZN5der_tC1Ev, @function
_ZN5der_tC1Ev:
.LFB17:
	pushl	%ebp
.LCFI2:
	movl	%esp, %ebp
.LCFI3:
	subl	$8, %esp
.LCFI4:
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZN6base_tC2Ev
	movl	8(%ebp), %eax
	movl	$_ZTV5der_t+8, (%eax)
	leave
	ret
.LFE17:
	.size	_ZN5der_tC1Ev, .-_ZN5der_tC1Ev
	.text
.globl _Z6g_funcP6base_t
	.type	_Z6g_funcP6base_t, @function
_Z6g_funcP6base_t:
.LFB19:
	pushl	%ebp
.LCFI5:
	movl	%esp, %ebp
.LCFI6:
	subl	$24, %esp
.LCFI7:
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	(%eax), %edx
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	*%edx
	movl	8(%ebp), %eax
	movl	%eax, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	(%eax), %eax
	movl	(%eax), %edx
	movl	-4(%ebp), %eax
	movl	%eax, (%esp)
	call	*%edx
	leave
	ret
.LFE19:
	.size	_Z6g_funcP6base_t, .-_Z6g_funcP6base_t
	.section	.rodata
.LC0:
	.string	"der"
	.section	.text._ZN5der_t4virfEv,"axG",@progbits,_ZN5der_t4virfEv,comdat
	.align 2
	.weak	_ZN5der_t4virfEv
	.type	_ZN5der_t4virfEv, @function
_ZN5der_t4virfEv:
.LFB6:
	pushl	%ebp
.LCFI8:
	movl	%esp, %ebp
.LCFI9:
	subl	$8, %esp
.LCFI10:
	movl	$.LC0, (%esp)
	call	puts
	leave
	ret
.LFE6:
	.size	_ZN5der_t4virfEv, .-_ZN5der_t4virfEv
	.section	.rodata
.LC1:
	.string	"~base"
	.section	.text._ZN6base_tD2Ev,"axG",@progbits,_ZN6base_tD2Ev,comdat
	.align 2
	.weak	_ZN6base_tD2Ev
	.type	_ZN6base_tD2Ev, @function
_ZN6base_tD2Ev:
.LFB3:
	pushl	%ebp
.LCFI11:
	movl	%esp, %ebp
.LCFI12:
	subl	$8, %esp
.LCFI13:
	movl	8(%ebp), %eax
	movl	$_ZTV6base_t+8, (%eax)
	movl	$.LC1, (%esp)
	call	puts
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_Z6g_funcP6base_t
	movl	$0, %eax
	testb	%al, %al
	je	.L12
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZdlPv
.L12:
	leave
	ret
.LFE3:
	.size	_ZN6base_tD2Ev, .-_ZN6base_tD2Ev
	.section	.rodata
.LC2:
	.string	"~der"
.globl _Unwind_Resume
	.section	.text._ZN5der_tD0Ev,"axG",@progbits,_ZN5der_tD0Ev,comdat
	.align 2
	.weak	_ZN5der_tD0Ev
	.type	_ZN5der_tD0Ev, @function
_ZN5der_tD0Ev:
.LFB10:
	pushl	%ebp
.LCFI14:
	movl	%esp, %ebp
.LCFI15:
	pushl	%esi
.LCFI16:
	pushl	%ebx
.LCFI17:
	subl	$32, %esp
.LCFI18:
	movl	8(%ebp), %eax
	movl	$_ZTV5der_t+8, (%eax)
	movl	$.LC2, (%esp)
.LEHB0:
	call	puts
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_Z6g_funcP6base_t
.LEHE0:
	movl	8(%ebp), %eax
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
.LEHB1:
	call	_ZN6base_tD2Ev
.LEHE1:
	movl	$1, %eax
	testb	%al, %al
	je	.L17
	jmp	.L19
.L18:
	movl	%eax, -16(%ebp)
.L15:
	movl	%edx, %esi
	movl	-16(%ebp), %ebx
	movl	8(%ebp), %eax
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZN6base_tD2Ev
	movl	%ebx, -16(%ebp)
	movl	%esi, %edx
	movl	-16(%ebp), %eax
	movl	%eax, (%esp)
.LEHB2:
	call	_Unwind_Resume
.LEHE2:
.L19:
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZdlPv
.L17:
	addl	$32, %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
.LFE10:
	.size	_ZN5der_tD0Ev, .-_ZN5der_tD0Ev
.globl __gxx_personality_v0
	.section	.gcc_except_table,"a",@progbits
.LLSDA10:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE10-.LLSDACSB10
.LLSDACSB10:
	.uleb128 .LEHB0-.LFB10
	.uleb128 .LEHE0-.LEHB0
	.uleb128 .L18-.LFB10
	.uleb128 0x0
	.uleb128 .LEHB1-.LFB10
	.uleb128 .LEHE1-.LEHB1
	.uleb128 0x0
	.uleb128 0x0
	.uleb128 .LEHB2-.LFB10
	.uleb128 .LEHE2-.LEHB2
	.uleb128 0x0
	.uleb128 0x0
.LLSDACSE10:
	.section	.text._ZN5der_tD0Ev,"axG",@progbits,_ZN5der_tD0Ev,comdat
	.section	.text._ZN6base_tD0Ev,"axG",@progbits,_ZN6base_tD0Ev,comdat
	.align 2
	.weak	_ZN6base_tD0Ev
	.type	_ZN6base_tD0Ev, @function
_ZN6base_tD0Ev:
.LFB5:
	pushl	%ebp
.LCFI19:
	movl	%esp, %ebp
.LCFI20:
	subl	$8, %esp
.LCFI21:
	movl	8(%ebp), %eax
	movl	$_ZTV6base_t+8, (%eax)
	movl	$.LC1, (%esp)
	call	puts
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_Z6g_funcP6base_t
	movl	$1, %eax
	testb	%al, %al
	je	.L23
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZdlPv
.L23:
	leave
	ret
.LFE5:
	.size	_ZN6base_tD0Ev, .-_ZN6base_tD0Ev
	.section	.text._ZN6base_tD1Ev,"axG",@progbits,_ZN6base_tD1Ev,comdat
	.align 2
	.weak	_ZN6base_tD1Ev
	.type	_ZN6base_tD1Ev, @function
_ZN6base_tD1Ev:
.LFB4:
	pushl	%ebp
.LCFI22:
	movl	%esp, %ebp
.LCFI23:
	subl	$8, %esp
.LCFI24:
	movl	8(%ebp), %eax
	movl	$_ZTV6base_t+8, (%eax)
	movl	$.LC1, (%esp)
	call	puts
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_Z6g_funcP6base_t
	movl	$0, %eax
	testb	%al, %al
	je	.L27
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZdlPv
.L27:
	leave
	ret
.LFE4:
	.size	_ZN6base_tD1Ev, .-_ZN6base_tD1Ev
	.section	.text._ZN5der_tD1Ev,"axG",@progbits,_ZN5der_tD1Ev,comdat
	.align 2
	.weak	_ZN5der_tD1Ev
	.type	_ZN5der_tD1Ev, @function
_ZN5der_tD1Ev:
.LFB9:
	pushl	%ebp
.LCFI25:
	movl	%esp, %ebp
.LCFI26:
	pushl	%esi
.LCFI27:
	pushl	%ebx
.LCFI28:
	subl	$32, %esp
.LCFI29:
	movl	8(%ebp), %eax
	movl	$_ZTV5der_t+8, (%eax)
	movl	$.LC2, (%esp)
.LEHB3:
	call	puts
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_Z6g_funcP6base_t
.LEHE3:
	movl	8(%ebp), %eax
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
.LEHB4:
	call	_ZN6base_tD2Ev
.LEHE4:
	movl	$0, %eax
	testb	%al, %al
	je	.L32
	jmp	.L34
.L33:
	movl	%eax, -16(%ebp)
.L30:
	movl	%edx, %esi
	movl	-16(%ebp), %ebx
	movl	8(%ebp), %eax
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZN6base_tD2Ev
	movl	%ebx, -16(%ebp)
	movl	%esi, %edx
	movl	-16(%ebp), %eax
	movl	%eax, (%esp)
.LEHB5:
	call	_Unwind_Resume
.LEHE5:
.L34:
	movl	8(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZdlPv
.L32:
	addl	$32, %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
.LFE9:
	.size	_ZN5der_tD1Ev, .-_ZN5der_tD1Ev
	.section	.gcc_except_table
.LLSDA9:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE9-.LLSDACSB9
.LLSDACSB9:
	.uleb128 .LEHB3-.LFB9
	.uleb128 .LEHE3-.LEHB3
	.uleb128 .L33-.LFB9
	.uleb128 0x0
	.uleb128 .LEHB4-.LFB9
	.uleb128 .LEHE4-.LEHB4
	.uleb128 0x0
	.uleb128 0x0
	.uleb128 .LEHB5-.LFB9
	.uleb128 .LEHE5-.LEHB5
	.uleb128 0x0
	.uleb128 0x0
.LLSDACSE9:
	.section	.text._ZN5der_tD1Ev,"axG",@progbits,_ZN5der_tD1Ev,comdat
	.text
.globl _Z10test_abstrv
	.type	_Z10test_abstrv, @function
_Z10test_abstrv:
.LFB11:
	pushl	%ebp
.LCFI30:
	movl	%esp, %ebp
.LCFI31:
	subl	$24, %esp
.LCFI32:
	leal	-4(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZN5der_tC1Ev
	leal	-4(%ebp), %eax
	movl	%eax, (%esp)
	call	_ZN5der_tD1Ev
	leave
	ret
.LFE11:
	.size	_Z10test_abstrv, .-_Z10test_abstrv
.globl main
	.type	main, @function
main:
.LFB18:
	leal	4(%esp), %ecx
.LCFI33:
	andl	$-16, %esp
	pushl	-4(%ecx)
.LCFI34:
	pushl	%ebp
.LCFI35:
	movl	%esp, %ebp
.LCFI36:
	pushl	%ecx
.LCFI37:
	subl	$4, %esp
.LCFI38:
	call	_Z10test_abstrv
	movl	$0, %eax
	addl	$4, %esp
	popl	%ecx
	popl	%ebp
	leal	-4(%ecx), %esp
	ret
.LFE18:
	.size	main, .-main
	.weak	_ZTV5der_t
	.section	.rodata._ZTV5der_t,"aG",@progbits,_ZTV5der_t,comdat
	.align 8
	.type	_ZTV5der_t, @object
	.size	_ZTV5der_t, 20
_ZTV5der_t:
	.long	0
	.long	_ZTI5der_t
	.long	_ZN5der_t4virfEv
	.long	_ZN5der_tD1Ev
	.long	_ZN5der_tD0Ev
	.weak	_ZTI5der_t
	.section	.rodata._ZTI5der_t,"aG",@progbits,_ZTI5der_t,comdat
	.align 4
	.type	_ZTI5der_t, @object
	.size	_ZTI5der_t, 12
_ZTI5der_t:
	.long	_ZTVN10__cxxabiv120__si_class_type_infoE+8
	.long	_ZTS5der_t
	.long	_ZTI6base_t
	.weak	_ZTS5der_t
	.section	.rodata._ZTS5der_t,"aG",@progbits,_ZTS5der_t,comdat
	.type	_ZTS5der_t, @object
	.size	_ZTS5der_t, 7
_ZTS5der_t:
	.string	"5der_t"
	.weak	_ZTI6base_t
	.section	.rodata._ZTI6base_t,"aG",@progbits,_ZTI6base_t,comdat
	.align 4
	.type	_ZTI6base_t, @object
	.size	_ZTI6base_t, 8
_ZTI6base_t:
	.long	_ZTVN10__cxxabiv117__class_type_infoE+8
	.long	_ZTS6base_t
	.weak	_ZTS6base_t
	.section	.rodata._ZTS6base_t,"aG",@progbits,_ZTS6base_t,comdat
	.type	_ZTS6base_t, @object
	.size	_ZTS6base_t, 8
_ZTS6base_t:
	.string	"6base_t"
	.weak	_ZTV6base_t
	.section	.rodata._ZTV6base_t,"aG",@progbits,_ZTV6base_t,comdat
	.align 8
	.type	_ZTV6base_t, @object
	.size	_ZTV6base_t, 20
_ZTV6base_t:
	.long	0
	.long	_ZTI6base_t
	.long	__cxa_pure_virtual
	.long	_ZN6base_tD1Ev
	.long	_ZN6base_tD0Ev
	.section	.eh_frame,"a",@progbits
.Lframe1:
	.long	.LECIE1-.LSCIE1
.LSCIE1:
	.long	0x0
	.byte	0x1
	.string	"zPL"
	.uleb128 0x1
	.sleb128 -4
	.byte	0x8
	.uleb128 0x6
	.byte	0x0
	.long	__gxx_personality_v0
	.byte	0x0
	.byte	0xc
	.uleb128 0x4
	.uleb128 0x4
	.byte	0x88
	.uleb128 0x1
	.align 4
.LECIE1:
.LSFDE5:
	.long	.LEFDE5-.LASFDE5
.LASFDE5:
	.long	.LASFDE5-.Lframe1
	.long	.LFB19
	.long	.LFE19-.LFB19
	.uleb128 0x4
	.long	0x0
	.byte	0x4
	.long	.LCFI5-.LFB19
	.byte	0xe
	.uleb128 0x8
	.byte	0x85
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI6-.LCFI5
	.byte	0xd
	.uleb128 0x5
	.align 4
.LEFDE5:
.LSFDE7:
	.long	.LEFDE7-.LASFDE7
.LASFDE7:
	.long	.LASFDE7-.Lframe1
	.long	.LFB6
	.long	.LFE6-.LFB6
	.uleb128 0x4
	.long	0x0
	.byte	0x4
	.long	.LCFI8-.LFB6
	.byte	0xe
	.uleb128 0x8
	.byte	0x85
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI9-.LCFI8
	.byte	0xd
	.uleb128 0x5
	.align 4
.LEFDE7:
.LSFDE9:
	.long	.LEFDE9-.LASFDE9
.LASFDE9:
	.long	.LASFDE9-.Lframe1
	.long	.LFB3
	.long	.LFE3-.LFB3
	.uleb128 0x4
	.long	0x0
	.byte	0x4
	.long	.LCFI11-.LFB3
	.byte	0xe
	.uleb128 0x8
	.byte	0x85
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI12-.LCFI11
	.byte	0xd
	.uleb128 0x5
	.align 4
.LEFDE9:
.LSFDE11:
	.long	.LEFDE11-.LASFDE11
.LASFDE11:
	.long	.LASFDE11-.Lframe1
	.long	.LFB10
	.long	.LFE10-.LFB10
	.uleb128 0x4
	.long	.LLSDA10
	.byte	0x4
	.long	.LCFI14-.LFB10
	.byte	0xe
	.uleb128 0x8
	.byte	0x85
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI15-.LCFI14
	.byte	0xd
	.uleb128 0x5
	.byte	0x4
	.long	.LCFI18-.LCFI15
	.byte	0x83
	.uleb128 0x4
	.byte	0x86
	.uleb128 0x3
	.align 4
.LEFDE11:
.LSFDE13:
	.long	.LEFDE13-.LASFDE13
.LASFDE13:
	.long	.LASFDE13-.Lframe1
	.long	.LFB5
	.long	.LFE5-.LFB5
	.uleb128 0x4
	.long	0x0
	.byte	0x4
	.long	.LCFI19-.LFB5
	.byte	0xe
	.uleb128 0x8
	.byte	0x85
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI20-.LCFI19
	.byte	0xd
	.uleb128 0x5
	.align 4
.LEFDE13:
.LSFDE15:
	.long	.LEFDE15-.LASFDE15
.LASFDE15:
	.long	.LASFDE15-.Lframe1
	.long	.LFB4
	.long	.LFE4-.LFB4
	.uleb128 0x4
	.long	0x0
	.byte	0x4
	.long	.LCFI22-.LFB4
	.byte	0xe
	.uleb128 0x8
	.byte	0x85
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI23-.LCFI22
	.byte	0xd
	.uleb128 0x5
	.align 4
.LEFDE15:
.LSFDE17:
	.long	.LEFDE17-.LASFDE17
.LASFDE17:
	.long	.LASFDE17-.Lframe1
	.long	.LFB9
	.long	.LFE9-.LFB9
	.uleb128 0x4
	.long	.LLSDA9
	.byte	0x4
	.long	.LCFI25-.LFB9
	.byte	0xe
	.uleb128 0x8
	.byte	0x85
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI26-.LCFI25
	.byte	0xd
	.uleb128 0x5
	.byte	0x4
	.long	.LCFI29-.LCFI26
	.byte	0x83
	.uleb128 0x4
	.byte	0x86
	.uleb128 0x3
	.align 4
.LEFDE17:
.LSFDE19:
	.long	.LEFDE19-.LASFDE19
.LASFDE19:
	.long	.LASFDE19-.Lframe1
	.long	.LFB11
	.long	.LFE11-.LFB11
	.uleb128 0x4
	.long	0x0
	.byte	0x4
	.long	.LCFI30-.LFB11
	.byte	0xe
	.uleb128 0x8
	.byte	0x85
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI31-.LCFI30
	.byte	0xd
	.uleb128 0x5
	.align 4
.LEFDE19:
.LSFDE21:
	.long	.LEFDE21-.LASFDE21
.LASFDE21:
	.long	.LASFDE21-.Lframe1
	.long	.LFB18
	.long	.LFE18-.LFB18
	.uleb128 0x4
	.long	0x0
	.byte	0x4
	.long	.LCFI33-.LFB18
	.byte	0xc
	.uleb128 0x1
	.uleb128 0x0
	.byte	0x9
	.uleb128 0x4
	.uleb128 0x1
	.byte	0x4
	.long	.LCFI34-.LCFI33
	.byte	0xc
	.uleb128 0x4
	.uleb128 0x4
	.byte	0x4
	.long	.LCFI35-.LCFI34
	.byte	0xe
	.uleb128 0x8
	.byte	0x85
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI36-.LCFI35
	.byte	0xd
	.uleb128 0x5
	.byte	0x4
	.long	.LCFI37-.LCFI36
	.byte	0x84
	.uleb128 0x3
	.align 4
.LEFDE21:
	.ident	"GCC: (Gentoo 4.3.2-r3 p1.6, pie-10.1.5) 4.3.2"
	.section	.note.GNU-stack,"",@progbits
