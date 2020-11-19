TITLE Program 1     (program1.asm)

; Author: Nathaniel Mohr
; Course / Project ID   932583202              Date: 1/11/19
; Description: This program will find the sum, difference, product, quotient, and remainder of two numbers

INCLUDE Irvine32.inc

.data
	intro		BYTE	"PROGRAM 1		By: Nathaniel Mohr", 0
	ec_1		BYTE	"**EC: Repeat until the user chooses to quit.", 0
	ec_2		BYTE	"**EC: Validate the second number to be less than the first.", 0
	asthetic	BYTE	"-----------------------------------------------------------------------------------------------", 0
	greeting	BYTE	"Hello and Welcome to the Operation Machine. This program will perform operations on two numbers", 0
	rpt_prompt	BYTE	"Would you like to do this again? 2 for yes, 1 for no: ", 0
	explain		BYTE	"The second number needs to be less than the first number", 0
	prompt		BYTE	"Now we need the two numbers to be used", 0
	prompt1		BYTE	"First Number: ", 0
	prompt2		BYTE	"Second Number: ", 0
	results		BYTE	"Here are the results of the operations", 0
	sum_sign	BYTE	" + ", 0
	diff_sign	BYTE	" - ", 0
	prod_sign	BYTE	" * ", 0
	quot_sign	BYTE	" / ", 0
	equal_sign	BYTE	" = ", 0
	rem_soln	BYTE	"Remainder: ", 0
	goodbye		BYTE	"Thank you for using the Operation Machine. Goodbye.", 0
	num1		DWORD	?
	num2		DWORD	?
	sum			DWORD	?
	difference	DWORD	?
	product		DWORD	?
	quotient	DWORD	?
	remainder	DWORD	?

.code
main PROC
; Introduce the user to the program
	;Prints out name and extra credit
	mov edx, OFFSET intro
	call WriteString
	call CrLf
	mov edx, OFFSET ec_1
	call WriteString
	call CrLf
	mov edx, OFFSET ec_2
	call WriteString
	call CrLf
	call CrLf

	;Welcomes user
	mov edx, OFFSET greeting
	call WriteString
	call CrLf
	mov edx, OFFSET asthetic
	call WriteString
	call CrLf

top:
; Get the input from the user
	call CrLf
	mov edx, OFFSET prompt
	call WriteString
	call CrLf

	numbers:
	mov edx, OFFSET prompt1
	call WriteString
	call ReadInt
	mov num1, eax
	mov edx, OFFSET prompt2
	call WriteString
	call ReadInt
	mov num2, eax

	; Check if second number is less than the first
	; If second number is less then program continues, else it tells the user what is wrong and prompts again
	mov edx, num1
	cmp edx, num2
	ja rest
	call CrLf
	mov edx, OFFSET explain
	call WriteString
	call CrLf
	call CrLf
	jmp numbers

rest:
; Calculate the results
	; Addition
	mov eax, num1
	add eax, num2
	mov sum, eax

	; Subtraction
	mov eax, num1
	sub eax, num2
	mov difference, eax

	; Multiplication
	mov eax, num1
	mov ebx, num2
	mul ebx
	mov product, eax

	; Division and Remainder
	mov eax, num1
	cdq
	mov ebx, num2
	div ebx
	mov quotient, eax
	mov remainder, edx

 ; Print the results
	; Heading of results
	call CrLf
	mov edx, OFFSET results
	call WriteString
	call CrLf
	mov edx, OFFSET asthetic
	call WriteString
	call CrLf

	; Addition
	mov eax, num1
	call WriteDec
	mov edx, OFFSET sum_sign
	call WriteString
	mov eax, num2
	call WriteDec
	mov edx, OFFSET equal_sign
	call WriteString
	mov eax, sum
	call WriteDec
	call CrLf

	; Subtraction
	mov eax, num1
	call WriteDec
	mov edx, OFFSET diff_sign
	call WriteString
	mov eax, num2
	call WriteDec
	mov edx, OFFSET equal_sign
	call WriteString
	mov eax, difference
	call WriteDec
	call CrLf

	; Multiplication
	mov eax, num1
	call WriteDec
	mov edx, OFFSET prod_sign
	call WriteString
	mov eax, num2
	call WriteDec
	mov edx, OFFSET equal_sign
	call WriteString
	mov eax, product
	call WriteDec
	call CrLf

	; Division
	mov eax, num1
	call WriteDec
	mov edx, OFFSET quot_sign
	call WriteString
	mov eax, num2
	call WriteDec
	mov edx, OFFSET equal_sign
	call WriteString
	mov eax, quotient
	call WriteDec
	call CrLf

	; Remainder
	mov edx, OFFSET rem_soln
	mov eax, remainder
	call WriteString
	call WriteDec
	call CrLf
	call CrLf

; Check if user wants to do again
	mov edx, OFFSET rpt_prompt
	call WriteString
	call ReadInt
	cmp eax, 2
	je top

 ; Say goodbye
	mov edx, OFFSET goodbye
	call WriteString
	call CrLf

	exit	; exit to operating system
main ENDP

END main
