TITLE Composite Numbers     (program4.asm)

; Author: Nathaniel Mohr
; Course / Project ID   CS271              Date: 2/15/19
; Description: This program will calculate composite numbers based on a user entered number from 1-400
;				The numbers will be displayed 10 per line with at least 3 spaces between the numbers

INCLUDE Irvine32.inc

UPPER_LIMIT = 400
LINE_LIMIT = 10
MAX_NUM_LENGTH = 3
MIN_SPACES = 3

.data

intro			BYTE	"PROGRAM 4		By: Nathaniel Mohr",10,13,0
ec1				BYTE	"**EC: Align the output columns.",10,13,10,13,0
greeting		BYTE	"Hello and welcome to the Composite Number Generator!",10,13,10,13,0
instructions	BYTE	"Enter a number between 0 and ",0
instructions2	BYTE	" for the number of composite numbers you would like to see: ",0
out_of_range	BYTE	"		Sorry. '",0
out_of_range2	BYTE	"' is not within the range. Try again.",10,13,0
space			BYTE	" ",0
farewell_msg	BYTE	"Thank you for using the Composite Number Generator",0
user_num		DWORD	?
curr_num		DWORD	4
divisor			DWORD	?
quotient		DWORD	?
counter			DWORD	0
temp			DWORD	?
num_length		DWORD	?

.code
main PROC

	call introduction
	call get_user_data
	call show_composites
	call farewell

	exit	; exit to operating system
main ENDP

; Procedure to introduce the program
; Receives: none
; Returns: none
; Preconditions: none
; Registers changed: edx
introduction PROC
	mov edx, OFFSET intro
	call WriteString
	mov edx, OFFSET ec1
	call WriteString
	mov edx, OFFSET greeting
	call WriteString
	ret
introduction ENDP

; Procedure to get how many numbers wanted by the user (user_num)
; Receives: none
; Returns: value for user_num that is between 1 and UPPER_LIMIT
; Preconditions: none
; Registers changed: edx, eax
get_user_data PROC
	getting_data:
	mov edx, OFFSET instructions
	call WriteString
	mov eax, UPPER_LIMIT
	call WriteDec
	mov edx, OFFSET instructions2
	call WriteString
	call ReadInt
	mov user_num, eax
	call validate
	cmp eax, 0
	je getting_data
	ret
get_user_data ENDP

; Procedure to determine if user_num is between 1 and UPPER_LIMIT
; Receives: value in user_num
; Returns: 1 for a valid number and 0 for not valid
; Preconditions: none
; Registers changed: eax, edx
validate PROC
	mov eax, user_num
	cmp eax, 1
	jl not_valid
	cmp eax, UPPER_LIMIT
	jg not_valid
	mov eax, 1
	jmp valid

	not_valid:
	mov edx, OFFSET out_of_range
	call WriteString
	call WriteInt
	mov edx, OFFSET out_of_range2
	call WriteString
	call CrLf
	mov eax, 0

	valid:
	ret
validate ENDP

; Procedure to print out the desired number of composite numbers
; Receives: user_num as global variable
; Returns: user_num number of composite numbers
; Preconditions: user_num is valid
; Registers changed: eax, ecx
show_composites PROC
	mov ecx, user_num
	composite_printing:
	call is_composite
	cmp eax, 0
	je not_print
	call print_composite

	not_print:
	mov eax, curr_num
	inc eax
	mov curr_num, eax
	loop composite_printing
	call CrLf
	ret
show_composites ENDP

; Procedure to check if a number is a composite number
; Receives: curr_num is a global variable
; Returns: 1 if curr_num is composite and 0 if not composite
; Preconditions: user_num is valid
; Registers changed: eax, ebx, ecx
is_composite PROC
	mov divisor, 2
	composite_loop:
	mov eax, curr_num
	mov ebx, divisor
	cdq
	div ebx
	cmp edx, 0
	je prime_factor
	mov quotient, eax
	mov eax, divisor
	inc eax
	mov divisor, eax
	mov eax, quotient
	cmp eax, divisor
	jge composite_loop
	jmp not_composite

	prime_factor:
	mov eax, 1
	jmp end_composite_check

	not_composite:
	mov eax, 0
	inc ecx

	end_composite_check:
	ret
is_composite ENDP

; Procedure to print out a number and determine if a new line is needed
; Receives: curr_num is a global variable
; Returns: curr_num printed and appropriate new line added
; Preconditions: curr_num is a composite number
; Registers changed: eax, ebx, ecx, edx
print_composite PROC
	mov eax, curr_num
	call WriteDec
	call spacing_procedure

	mov eax, counter
	inc eax
	mov counter, eax
	cdq
	mov ebx, LINE_LIMIT
	div ebx
	mov eax, edx
	cmp eax, 0
	jne no_new_line
	call CrLf
	no_new_line:
	ret
print_composite ENDP

; Procedure to determine how many spaces are printed after a number
; Receives: curr_num in eax
; Returns: spaces printed after a number
; Preconditions: user_num is valid and in eax register
; Registers changed: eax, ebx, ecx, edx
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

	; adding (MAX_NUM_LENGTH + MIN_SPACES) minus the length of the number spaces
	out_of_while:
	mov eax, MAX_NUM_LENGTH
	add eax, MIN_SPACES
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

; Procedure to close out the program
; Receives: none
; Returns: none
; Preconditions: none
; Registers changed: edx
farewell PROC
	mov edx, OFFSET farewell_msg
	call WriteString
	call CrLf
	ret
farewell ENDP

END main
