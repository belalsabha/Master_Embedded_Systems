	.file	"main.c"
	.def	___main;	.scl	2;	.type	32;	.endef
	.text
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	andl	$-16, %esp
	subl	$16, %esp
	call	___main
	movl	$1073809420, 4(%esp)
	movl	$1073877016, %edx
	movl	$1073877016, %eax
	movl	(%eax), %eax
	orl	$4, %eax
	movl	%eax, (%edx)
	movl	$1073809412, %edx
	movl	$1073809412, %eax
	movl	(%eax), %eax
	andl	$-15728641, %eax
	movl	%eax, (%edx)
	movl	$1073809412, %edx
	movl	$1073809412, %eax
	movl	(%eax), %eax
	orl	$2097152, %eax
	movl	%eax, (%edx)
L6:
	movl	4(%esp), %eax
	movzwl	(%eax), %edx
	orb	$32, %dh
	movw	%dx, (%eax)
	movl	$0, 12(%esp)
	jmp	L2
L3:
	addl	$1, 12(%esp)
L2:
	cmpl	$4999, 12(%esp)
	jle	L3
	movl	4(%esp), %eax
	movzwl	(%eax), %edx
	andb	$223, %dh
	movw	%dx, (%eax)
	movl	$0, 8(%esp)
	jmp	L4
L5:
	addl	$1, 8(%esp)
L4:
	cmpl	$4999, 8(%esp)
	jle	L5
	jmp	L6
	.cfi_endproc
LFE0:
	.ident	"GCC: (MinGW.org GCC-6.3.0-1) 6.3.0"
