TITLE Fibonacci Sequence     (program2.asm)

; Author: Nathaniel Mohr
; Course / Project ID   CS271              Date: 1/18/19
; Description: This program will display n numbers from the fibonacci sequence
;				where n is a number from 1-46 and is given by the user

INCLUDE Irvine32.inc

UPPER_LIMIT = 46

.data

intro		BYTE	"PROGRAM 2		By: Nathaniel Mohr",0
ec_1		BYTE	"**EC: Display the numbers in aligned columns", 0
greeting	BYTE	"Hello and welcome to the Fibonacci Sequence Printer",10,13,10,13
			BYTE	"What is your name? ",0
prompt		BYTE	"How many terms would you like in your Fibonacci Sequence?",0
prompt2		BYTE	"Please enter an integer that is in the range [1,46]: ",0
error_range	BYTE	"Oops! That's out of range.",0
fib_seq		BYTE	", here is your Fibonacci Sequence: ",0
farewell	BYTE	"Thank you ",0
farewell2	BYTE	" for using the Fibonacci Sequence Printer",0
space		BYTE	" ",0
user_name	BYTE	33 DUP(0)
user_input	DWORD	?
previous	DWORD	0
current		DWORD	1
next		DWORD	0
counter		DWORD	0
num_length	DWORD	0
temp		DWORD	0

.code
main PROC

; Introduction
	mov edx, OFFSET intro
	call WriteString
	call CrLf
	mov edx, OFFSET ec_1
	call WriteString
	call CrLf
	call CrLf
	mov edx, OFFSET greeting
	call WriteString

	; Getting user name
	mov edx, OFFSET user_name
	mov ecx, 32
	call ReadString
	call CrLf

; User Instructions
	mov edx, OFFSET prompt
	call WriteString
	call CrLf

; Get User Data
get_data:
	mov edx, OFFSET prompt2
	call WriteString
	call ReadInt
	mov user_input, eax
	
	; Validating user input
	cmp eax, 1
	jl bad_input
	cmp eax, UPPER_LIMIT
	jg bad_input
	jmp input_okay
	
bad_input:
	mov edx, OFFSET error_range
	call WriteString
	call CrLf
	jmp get_data

input_okay:
; Display Fibonacci Numbers
	call CrLf
	mov edx, OFFSET user_name
	call WriteString
	mov edx, OFFSET fib_seq
	call WriteString
	call CrLf
	mov ecx, user_input	
printing:
	mov eax, current
	call WriteDec
	call spacing_procedure

	; see if a new line is needed ie if there are five numbers on the current line ie counter is divisible by 5
	mov eax, counter
	inc eax
	mov counter, eax
	cdq
	mov ebx, 5
	div ebx
	mov eax, edx
	cmp eax, 0
	jne calculations
	call CrLf

	calculations:
	; add the current with the previous to get the next
	mov eax, current
	add eax, previous
	mov next, eax
	; set previous equal to current
	mov eax, current
	mov previous, eax
	; set current equal to next
	mov eax, next
	mov current, eax
	loop printing
	call CrLf
	call CrLf

; Farewell
	mov edx, OFFSET farewell
	call WriteString
	mov edx, OFFSET user_name
	call WriteString
	mov edx, OFFSET farewell2
	call WriteString
	call CrLf

	exit	; exit to operating system
main ENDP

; determining how many spaces to print after a number
spacing_procedure PROC
	; calculating the length of the number (how many digits)
	while_loop:
	cmp eax, 0
	je out_of_while
	mov temp, eax
	mov eax, num_length
	inc eax
	mov num_length, eax
	mov eax, temp
	mov ebx, 10
	cdq
	div ebx
	jmp while_loop

	; adding 15 minus the length of the number spaces
	out_of_while:
	mov eax, 15
	sub eax, num_length
	
	space_printing:
	cmp eax, 0
	jle out_of_spacing
	mov edx, OFFSET space
	call WriteString
	dec eax
	jmp space_printing

	out_of_spacing:

	; resetting the length variable
	mov num_length, 0
	ret
spacing_procedure ENDP

END main
