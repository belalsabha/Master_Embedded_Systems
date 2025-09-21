	.cpu arm926ej-s
	.arch armv5tej
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 6
	.eabi_attribute 34, 0
	.eabi_attribute 18, 4
	.file	"app.c"
	.text
	.global	string_buffer
	.data
	.align	2
	.type	string_buffer, %object
	.size	string_buffer, 100
string_buffer:
	.ascii	"Eng-Belal_Hani_Abu_Sabha\000"
	.space	75
	.text
	.align	2
	.global	main
	.syntax unified
	.arm
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{fp, lr}
	add	fp, sp, #4
	ldr	r0, .L2
	bl	Uart_Send_String
	nop
	pop	{fp, pc}
.L3:
	.align	2
.L2:
	.word	string_buffer
	.size	main, .-main
	.ident	"GCC: (GNU Arm Embedded Toolchain 10.3-2021.10) 10.3.1 20210824 (release)"
