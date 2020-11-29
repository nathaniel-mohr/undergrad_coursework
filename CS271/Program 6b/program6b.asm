TITLE Combinations Calculator    (program6b.asm)

; Author: Nathaniel Mohr
; Course / Project ID   CS271              Date: 3/9/19
; Description: This program will ask a student to calculate the number of combinations of r items taken from a set of n items
;				The system generates random problems with n in [3,12] and r in [1,n]
;				The system repeats until the student chooses to quit

get_random_number MACRO low_limit, high_limit, variable
	push eax
	mov eax, high_limit
	sub eax, low_limit
	inc eax
	call RandomRange
	add eax, low_limit
	mov ebx, variable
	mov [ebx], eax
	pop eax
ENDM

my_write_string MACRO buffer
	push edx
	mov edx, OFFSET buffer
	call WriteString
	pop edx
ENDM

INCLUDE Irvine32.inc

N_LOWER_LIMIT = 3
N_UPPER_LIMIT = 12
R_LOWER_LIMIT = 1
BUFFER_SIZE = 20

.data
intro			BYTE	"PROGRAM 6b		By: Nathaniel Mohr",10,13,0
ec1				BYTE	"**EC: You may gain 1 additional point by numbering each problem and keeping score.",10,13
				BYTE	"      When the student quits, report number right/wrong, etc.",10,13,10,13,0
greeting		BYTE	"Hello and welcome to the Combinations Calculator!",10,13,10,13,0
instructions	BYTE	"I'll give you a combinations problem.",10,13
				BYTE	"You enter your answer, and I'll let you know if you're right.",10,13,10,13,0
prompt			BYTE	"How many ways can you choose? ",0

problem			BYTE	"Problem #",0
numbers_in_set	BYTE	"Number of elements in the set:   ",0
numbers_to_choose	BYTE	"Number of elements to choose from the set:   ",0

result1			BYTE	"There are  ",0
result2			BYTE	"  combinations of ",0
result3			BYTE	" items from a set of ",0

incorrect		BYTE	"You need more practice.",10,13,10,13,0
correct			BYTE	"You are correct!",10,13,10,13,0

yes				BYTE	"YES",0
no				BYTE	"NO",0
more_questions	BYTE	"Would you like another problem? (Enter 'yes' or 'no') ",0

stats1			BYTE	"You answered ",0
stats2			BYTE	" correct out of a total of ",0
stats3			BYTE	" questions.",10,13,10,13,0

n_val			DWORD	?
r_val			DWORD	?
guess			DWORD	?
answer			DWORD	?

user_string		BYTE	BUFFER_SIZE DUP(0)
user_str_lngth	DWORD	?

num_problems	DWORD	0
num_right		DWORD	0

.code
main PROC
	call Randomize
	call introduction

top:
	push OFFSET num_problems
	push OFFSET n_val
	push OFFSET r_val
	call show_problem

	push OFFSET guess
	call get_user_guess

	push n_val
	push r_val
	push OFFSET answer
	call combinations

	push OFFSET num_right
	push n_val
	push r_val
	push guess
	push answer
	call show_results

	call get_user_answer
	INVOKE Str_compare, ADDR user_string, ADDR yes
	je top

	push num_problems
	push num_right
	call print_stats
	exit
main ENDP

; This procedure introduces the program
; Receives: none
; Returns: none
; Pre-Conditions: none 
; Registers changed: edx
introduction PROC
	my_write_string intro
	my_write_string ec1
	my_write_string greeting
	my_write_string instructions
	ret
introduction ENDP

; This procedure creates and presents the problem
; Receives: OFFSET of r_val, n_val, and num_problems
; Returns: values of variables properly changed
; Pre-Conditions: none
; Registers changed: eax, ebx, ebp
show_problem PROC
	push ebp
	mov ebp, esp

	get_random_number N_LOWER_LIMIT, N_UPPER_LIMIT, [ebp+12]
	mov eax, [ebp+12]
	get_random_number R_LOWER_LIMIT, [eax], [ebp+8]

	my_write_string problem
	mov ebx, [ebp+16]
	mov eax, [ebx]
	inc eax
	mov [ebx], eax
	call WriteDec
	call CrLf

	my_write_string numbers_in_set
	mov ebx, [ebp+12]
	mov eax, [ebx]
	call WriteDec
	call CrLf

	my_write_string numbers_to_choose
	mov ebx, [ebp+8]
	mov eax, [ebx]
	call WriteDec
	call CrLf

	pop ebp
	ret 12
show_problem ENDP

; This procedure gets the user's guess
; Receives: OFFSET of guess
; Returns: value put in guess
; Pre-Conditions: none
; Registers changed: edx, ecx, eax, ebp
get_user_guess PROC
	push ebp
	mov ebp, esp

	getting_guess:
	my_write_string prompt
	mov edx, OFFSET user_string
	mov ecx, BUFFER_SIZE
	call ReadString
	call is_num
	cmp eax, 0
	je getting_guess

	push [ebp+8]
	call string_to_int

	pop ebp
	ret
get_user_guess ENDP

; This procedure determines if a string is an integer
; Receives: none
; Returns: 1 for yes, 0 for no
; Pre-Conditions: none
; Registers changed: edi, ecx, eax
is_num PROC
	mov edi, OFFSET user_string
	INVOKE Str_length, ADDR user_string
	mov ecx, eax

	mov eax, 0

	looping:
	mov al, [edi]
	cmp al, 0
	je end_is_num
	cmp al, '0'
	jb not_num
	cmp al, '9'
	ja not_num
	mov eax, 1

	inc edi
	loop looping
	jmp end_is_num

	not_num:
	mov eax, 0

	end_is_num:

	ret
is_num ENDP

; This procedure converts a string into its integer equivalent
; Receives: OFFSET of guess
; Returns: value in guess
; Pre-Conditions: string has an integer equivalence
; Registers changed: ebp, ebx, eax, edi, ecx
string_to_int PROC
	push ebp
	mov ebp, esp

	mov ebx, [ebp+8]
	mov eax, 0
	mov [ebx], eax

	mov edi, OFFSET user_string
	INVOKE Str_length, ADDR user_string
	mov ecx, eax

	looping:
	mov ebx, [ebp+8]
	mov eax, [ebx]
	mov ebx, 10
	mul ebx
	mov ebx, [ebp+8]
	mov [ebx], eax
	mov al, [edi]
	sub al, 48
	mov ebx, [ebp+8]
	add [ebx], al
	inc edi
	loop looping

	pop ebp
	ret 4
string_to_int ENDP

; This procedure calculates a combination
; Receives: n_val, r_val, and OFFSET of answer
; Returns: value of combination into answer
; Pre-Conditions: proper values of r_val and n_val
; Registers changed: ebp, eax, ebx
combinations PROC	
	push ebp
	mov ebp, esp

	mov eax, [ebp+16]
	sub eax, [ebp+12]	
	push eax
	call factorial		; (n-r)!
	mov ebx, eax

	push [ebp+12]
	call factorial		; r!

	mul ebx
	mov ebx, eax		; r!(n-r)!

	push [ebp+16]
	call factorial		; n!

	cdq
	div ebx				; nCr

	mov ebx, [ebp+8]
	mov [ebx], eax

	pop ebp
	ret 12
combinations ENDP

; This procedure calculates factorial recursively
; Receives: value to be calculated
; Returns: factorial of value
; Pre-Conditions: none
; Registers changed: ebp, eax, esi
factorial PROC
	push ebp
	mov ebp, esp

	mov eax, [ebp+8]
	cmp eax, 0
	jg recurse
	mov eax, 1
	jle quit

recurse:
	dec eax
	push eax
	call factorial
	
	mov esi, [ebp+8]
	mul esi
quit:
	pop ebp
	ret 4
factorial ENDP

; This procedure prints out the results
; Receives: n_val, r_val, answer, guess, OFFSET of num_right
; Returns: num_right changed to reflect results and printed out all results
; Pre-Conditions: none
; Registers changed: ebp, edx, eax, ebx
show_results PROC 
	push ebp
	mov ebp, esp

	call CrLf
	my_write_string result1
	mov eax, [ebp+8]
	call WriteDec
	my_write_string result2
	mov eax, [ebp+16]
	call WriteDec
	my_write_string result3
	mov eax, [ebp+20]
	call WriteDec
	call CrLf

	mov eax, [ebp+8]
	cmp eax, [ebp+12]
	je correct_guess

incorrect_guess:
	my_write_string incorrect
	jmp finish
correct_guess:
	my_write_string correct
	mov ebx, [ebp+24]
	mov eax, [ebx]
	inc eax
	mov [ebx], eax
finish:
	pop ebp
	ret 20
show_results ENDP

; This procedure determines if the user wants to get another question
; Receives: none
; Returns: "yes" or "no" in user_string
; Pre-Conditions: none
; Registers changed: edx, ecx, eax
get_user_answer PROC
	getting_answer:
	my_write_string more_questions
	mov edx, OFFSET user_string
	mov ecx, BUFFER_SIZE
	call ReadString
	INVOKE Str_ucase, ADDR user_string
	INVOKE Str_compare, ADDR user_string, ADDR yes
	je bottom
	INVOKE Str_compare, ADDR user_string, ADDR no
	je bottom
	jmp getting_answer
	bottom:
	call CrLf
	ret
get_user_answer ENDP

; This procedure prints the ratio of correct and incorrect answers
; Receives: num_right and num_problems
; Returns: stats printed to screen
; Pre-Conditions: none
; Registers changed: ebp, eax
print_stats PROC 
	push ebp
	mov ebp, esp

	my_write_string stats1
	mov eax, [ebp+8]
	call WriteDec
	my_write_string stats2
	mov eax, [ebp+12]
	call WriteDec
	my_write_string stats3

	pop ebp
	ret 8
print_stats ENDP
END main
