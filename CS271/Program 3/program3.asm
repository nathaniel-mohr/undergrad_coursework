TITLE Program 3     (program3.asm)

; Author: Nathaniel Mohr
; Course / Project ID   CS271              Date: 1/26/19
; Description: This program will prompt the user to enter numbers in the interval [-100, -1]
;				once the user enters a positive number the prompts will stop
;				the number of negative numbers entered will be printed,
;				as well as the average of the negative numbers

INCLUDE Irvine32.inc

LOWER_LIMIT = -100
UPPER_LIMIT = -1

.data

intro			BYTE	"PROGRAM 3		By: Nathaniel Mohr",0
ec_1			BYTE	"**EC: Number the lines during user input",0
greeting		BYTE	"Hello and welcome to the Integer Accumulator!",10,13,10,13
				BYTE	"What is your name? ",0
hello			BYTE	"Hello ",0
instructions	BYTE	"Please enter numbers between ",0
conjunction		BYTE	" and ",0
instructions2	BYTE	".",10,13
				BYTE	"Enter a non-negative number when you are finished to see the results.",0
prompt			BYTE	". Enter number: ",0
no_negs			BYTE	"Interesting choice to not enter any numbers within the range.",0
results			BYTE	"Here are the results:"
valids			BYTE	"You entered ",0
valids2			BYTE	" valid numbers.",0
sum_result		BYTE	"The sum of the valid numbers is ",0
avg_result		BYTE	"The rounded average is ",0
farewell		BYTE	"Thank you ",0
farewell2		BYTE	" for using the Integer Accumulator",0
user_name		BYTE	33 DUP(0)
prompt_count	DWORD	1
user_input		DWORD	0
int_count		DWORD	0
sum				DWORD	0
average			DWORD	0

.code
main PROC

; Introduction
	mov edx, OFFSET intro
	call WriteString
	call CrLf
	mov edx, OFFSET ec_1
	call WriteString
	call CrLf
	call CrLF
	mov edx, OFFSET greeting
	call WriteString

; Get User Name
	mov edx, OFFSET user_name
	mov ecx, 32
	call ReadString
	call CrLf

; Instructions
	mov edx, OFFSET hello
	call WriteString
	mov edx, OFFSET user_name
	call WriteString
	call CrLf
	mov edx, OFFSET instructions
	call WriteString
	mov eax, LOWER_LIMIT
	call WriteInt
	mov edx, OFFSET conjunction
	call WriteString
	mov eax, UPPER_LIMIT
	call WriteInt
	mov edx, OFFSET instructions2
	call WriteString
	call CrLf
	call CrLf

; Get User Data
data_collection:
	mov eax, prompt_count
	call WriteDec
	inc eax
	mov prompt_count, eax
	mov edx, OFFSET prompt
	call WriteString
	call ReadInt
	cmp eax, LOWER_LIMIT
	jl data_collection
	jge first_check
first_check:
	cmp eax, UPPER_LIMIT
	jle valid_int
	jg end_loop
valid_int:
	add eax, sum
	mov sum, eax
	mov eax, int_count
	inc eax
	mov int_count, eax
	jmp data_collection
end_loop:

; Check if user did not enter any numbers in the range
	mov eax, int_count
	cmp eax, 0
	jne math
	call CrLf
	mov edx, OFFSET no_negs
	call WriteString
	call CrLf
	call CrLf
	jmp ending

; Calculate Average
math:
	mov eax, sum
	cdq
	mov ebx, int_count
	idiv ebx
	mov average, eax
	
; Print Out Data
	; valid numbers
	call CrLf
	mov edx, OFFSET valids
	call WriteString
	mov eax, int_count
	call WriteDec
	mov edx, OFFSET valids2
	call WriteString
	call CrLf

	; sum
	mov edx, OFFSET sum_result
	call WriteString
	mov eax, sum
	call WriteInt
	call CrLf

	; average
	mov edx, OFFSET avg_result
	call WriteString
	mov eax, average
	call WriteInt
	call CrLf
	call CrLf

; Farewll
ending:
	mov edx, OFFSET farewell
	call WriteString
	mov edx, OFFSET user_name
	call WriteString
	mov edx, OFFSET farewell2
	call WriteString
	call CrLf

	exit	; exit to operating system
main ENDP

; (insert additional procedures here)

END main
