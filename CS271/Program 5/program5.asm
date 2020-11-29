TITLE Sorting Random Integers     (program5.asm)

; Author: Nathaniel Mohr
; Course / Project ID   CS271              Date: 2/22/19
; Description: This program will create an array of request size of numbers from 100 to 999
;				It will then print out the array, sort the array, and print the sorted array
;				It will also calculate and print the median

INCLUDE Irvine32.inc

MIN = 10
MAX = 200
LO = 100
HI = 999
LINE_LIMIT = 10

.data

intro			BYTE	"PROGRAM 5      By: Nathaniel Mohr",10,13,10,13,0
instructions	BYTE	"This program generates random numbers in the range [100 ... 999],",10,13
				BYTE	"displays the original list, sorts the list, and calculates the",10,13
				BYTE	"median value. Finally, it displays the list sorted in descending order.",10,13,10,13,0
prompt			BYTE	"How many numbers should be generated? [10 ... 200] ",0
range_error		BYTE	"That is not within the range.",10,13,0
title_og		BYTE	"The unsorted random numbers:",10,13,0
title_sorted	BYTE	"The sorted list:",10,13,0
median			BYTE	"The median is: ",10,13,0
request			DWORD	0
array			DWORD	MAX DUP(0)
first	BYTE "FIRST ",0
second	BYTE "SECOND ",0

.code
main PROC
	call Randomize
	
	push OFFSET intro
	push OFFSET instructions
	call introduction
	
	getting_data:
	push OFFSET prompt
	push OFFSET request
	call get_data

	push request
	push OFFSET range_error
	call validate
	cmp eax, 0
	je getting_data

	push OFFSET array
	push request
	call fill_array

	push OFFSET array
	push request
	push OFFSET title_og
	call display_list

	push OFFSET array
	push request
	call sort_list

	push OFFSET array
	push request
	push OFFSET median
	call display_median
	
	push OFFSET array
	push request
	push OFFSET title_sorted
	call display_list

	exit	; exit to operating system
main ENDP

; This procedure introduces the program
; Receives: OFFSET of intro and instructions
; Returns: none
; Pre-Conditions: none
; Registers changed: ebp, edx
introduction PROC
	push ebp
	mov ebp, esp
	mov edx, [ebp+12]
	call WriteString
	mov edx, [ebp+8]
	call WriteString

	pop ebp
	ret 8
introduction ENDP

; This procedure obtains the number of random numbers the user wants
; Receives: OFFSET of request
; Returns: request filled with a value between 10 and 200
; Pre-Conditions: none
; Registers changed: ebp, edx, ebx
get_data PROC
	push ebp
	mov ebp, esp
	mov ebx, [ebp+8]

	getting_data:
	mov edx, [ebp+12]
	call WriteString
	call ReadInt
	mov [ebx], eax

	pop ebp
	ret 4
get_data ENDP

; This procedure validates that request is between 10 and 200
; Receives: request and OFFSET of range_error
; Returns: 1 for valid, 0 for not valid
; Pre-Conditions: none
; Registers changed: eax, ebp, edx
validate PROC
	push ebp
	mov ebp, esp
	mov eax, [ebp+12]
	cmp eax, MIN
	jl not_valid
	cmp eax, MAX
	jg not_valid
	mov eax, 1
	jmp valid

	not_valid:
	mov edx, [ebp+8]
	call WriteString
	mov eax, 0

	valid:

	pop ebp
	ret 4
validate ENDP

; This procedure fills an array with request random numbers from 100 to 999
; Receives: request and OFFSET of array
; Returns: filled array
; Pre-Conditions: array has memory and request is less than capacity of array (200)
; Registers changed: ebp, edi, ecx, eax
fill_array PROC
	push ebp
	mov ebp, esp
	mov edi, [ebp+12]
	mov ecx, [ebp+8]

	filling:
	call get_random_number
	mov [edi], eax
	add edi, 4
	loop filling

	pop ebp
	ret 8
fill_array ENDP

; This procedure creates a random number
; Receives: none
; Returns: random number between LO and HI
; Pre-Conditions: none
; Registers changed: eax
get_random_number PROC
	mov eax, HI
	sub eax, LO
	inc eax
	call RandomRange
	add eax, LO
	ret
get_random_number ENDP

; This procedure prints an array with appropriate title
; Receives: request, OFFSET of array and OFFSET of title
; Returns: array printed to screen with title
; Pre-Conditions: array has memory and request is less than capacity
; Registers changed: ebp, edi, ecx, eax, edx, al, ebx
display_list PROC
	push ebp
	mov ebp, esp
	mov edi, [ebp+16]
	mov ecx, [ebp+12]
	mov edx, [ebp+8]

	call WriteString
	
	mov edx, 0		; This will be used to track how many numbers have been printed
	displaying:
	mov eax, [edi]
	call WriteDec
	mov al, 32
	call WriteChar
	call WriteChar
	call WriteChar
	add edi, 4

	inc edx
	mov eax, edx
	cdq
	mov ebx, LINE_LIMIT
	div ebx
	mov eax, edx
	cmp eax, 0
	jne no_new_line
	call CrLf
	
	no_new_line:
	loop displaying
	call CrLf
	call CrLf

	pop ebp
	ret 12
display_list ENDP

; This procedure sorts a list in descending order
; Receives: request and OFFSET of array
; Returns: sorted array
; Pre-Conditions: array has memory and request is less than capacity
; Registers changed: ebp, edi, ecx, eax, ebx, edx, esi
sort_list PROC
	push ebp
	mov ebp, esp
	mov edi, [ebp+12]
	mov ecx, [ebp+8]

	dec ecx							; request - 1
	mov ebx, 0						; k

	first_loop:
		mov eax, ebx				; i
		mov edx, eax
		inc edx						; j
		push ecx
		mov ecx, [ebp+8]			; request
		second_loop:
			mov esi, [edi+edx*4]	; array[j]
			cmp esi, [edi+eax*4]	; array[i]
			jle no_swap
				mov eax, edx
			no_swap:
				inc edx
				cmp edx, ecx
				jb second_loop
			
			push [edi+ebx*4]
			push [edi+eax*4]
			pop [edi+ebx*4]
			pop [edi+eax*4]
		pop ecx
		inc ebx
	loop first_loop

	pop ebp
	ret 8
sort_list ENDP

; This procedure calculates the median of a sorted array and displays it
; Receives: OFFSET of array, OFFSET of median (print statement), and request
; Returns: median
; Pre-Conditions: array is sorted and request is valid
; Registers changed: ebp, edi, eax, edx, ebx, ecx
display_median PROC
	push ebp
	mov ebp, esp
	mov edi, [ebp+16]
	mov eax, [ebp+12]
	mov edx, [ebp+8]

	call WriteString

	mov ebx, 2
	cdq
	div ebx
	cmp edx, 0
	jne odd_num

	mov ebx, [edi+eax*4]
	dec eax
	mov ecx, [edi+eax*4]
	mov eax, ebx
	add eax, ecx
	mov ebx, 2
	cdq
	div ebx
	call WriteDec
	jmp end_median

	odd_num:
	mov eax, [edi+eax*4]
	call WriteDec

	end_median:
	call CrLf
	call CrLf
	pop ebp
	ret 12
display_median ENDP

END main
