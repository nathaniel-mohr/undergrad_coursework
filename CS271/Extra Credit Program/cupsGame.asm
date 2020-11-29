TITLE Cups Game    (cupsGame.asm)

; Author: Nathaniel Mohr
; Course / Project ID   CS 271              Date: 1/15/19
; Description: This program will simulate the cup game in which a ball is inserted into one cup out of three
;				the cups are then moved around and the correct cup must be determined

INCLUDE Irvine32.inc

BUFFER_SIZE = 5

.data

welcome			BYTE "   ______  _____  _____  _______      ______       _       ____    ____  ________ ", 10,13 
				BYTE " .' ___  ||_   _||_   _||_   __ \   .' ___  |     / \     |_   \  /   _||_   __  |", 10,13 
				BYTE "/ .'   \_|  | |    | |    | |__) | / .'   \_|    / _ \      |   \/   |    | |_ \_|", 10,13 
				BYTE "| |         | '    ' |    |  ___/  | |   ____   / ___ \     | |\  /| |    |  _| _ ", 10,13 
				BYTE "\ `.___.'\   \ \__/ /    _| |_     \ `.___]  |_/ /   \ \_  _| |_\/_| |_  _| |__/ |", 10,13 
				BYTE " `.____ .'    `.__.'    |_____|     `._____.'|____| |____||_____||_____||________|", 10,13,0

swapping_time	BYTE "  ______  ____      ____  _       _______  _______  _____  ____  _____   ______  ", 10,13  
				BYTE ".' ____ \|_  _|    |_  _|/ \     |_   __ \|_   __ \|_   _||_   \|_   _|.' ___  | ", 10,13  
				BYTE "| (___ \_| \ \  /\  / / / _ \      | |__) | | |__) | | |    |   \ | | / .'   \_| ", 10,13  
				BYTE " _.____`.   \ \/  \/ / / ___ \     |  ___/  |  ___/  | |    | |\ \| | | |   ____ ", 10,13  
				BYTE "| \____) |   \  /\  /_/ /   \ \_  _| |_    _| |_    _| |_  _| |_\   |_\ `.___]  |", 10,13  
				BYTE " \______.'    \/  \/|____| |____||_____|  |_____|  |_____||_____|\____|`._____.' ", 10,13,0 

setting_up		BYTE " _______  _____          _        ______  _____  ____  _____   ______  ", 10,13
				BYTE "|_   __ \|_   _|        / \     .' ___  ||_   _||_   \|_   _|.' ___  | ", 10,13            
				BYTE "  | |__) | | |         / _ \   / .'   \_|  | |    |   \ | | / .'   \_| ", 10,13            
				BYTE "  |  ___/  | |   _    / ___ \  | |         | |    | |\ \| | | |   ____ ", 10,13            
				BYTE " _| |_    _| |__/ | _/ /   \ \_\ `.___.'\ _| |_  _| |_\   |_\ `.___]  |", 10,13            
				BYTE "|_____|  |________||____| |____|`.____ .'|_____||_____|\____|`._____.' ", 10,13,0 

ready			BYTE "Are you ready?",10,13,0
rest_position	BYTE "      ___            ___            ___    ", 10,13
				BYTE "     /   \          /   \          /   \   ", 10,13
				BYTE "    /     \        /     \        /     \  ", 10,13
				BYTE "   /       \      /       \      /       \ ", 10,13
				BYTE "  [_________]    [_________]    [_________]", 10,13,0

ball_one1		BYTE "      ___                                  ", 10,13
				BYTE "     /   \                                 ", 10,13
				BYTE "    /     \                                ", 10,13
				BYTE "   /       \         ___            ___    ", 10,13
				BYTE "  [_________]       /   \          /   \   ", 10,13
				BYTE "                   /     \        /     \  ", 10,13
				BYTE "                  /       \      /       \ ", 10,13
				BYTE "       O         [_________]    [_________]", 10,13,0

ball_one2		BYTE "      ___                                  ", 10,13
				BYTE "     /   \                                 ", 10,13
				BYTE "    /     \          ___            ___    ", 10,13
				BYTE "   /       \        /   \          /   \   ", 10,13
				BYTE "  [_________]      /     \        /     \  ", 10,13
				BYTE "                  /       \      /       \ ", 10,13
				BYTE "       O         [_________]    [_________]", 10,13,0

ball_one3		BYTE "      ___                                  ", 10,13
				BYTE "     /   \           ___            ___    ", 10,13
				BYTE "    /     \         /   \          /   \   ", 10,13
				BYTE "   /       \       /     \        /     \  ", 10,13
				BYTE "  [_________]     /       \      /       \ ", 10,13
				BYTE "       O         [_________]    [_________]", 10,13,0

ball_two1		BYTE "                     ___                   ", 10,13
				BYTE "                    /   \                  ", 10,13
				BYTE "                   /     \                 ", 10,13
				BYTE "      ___         /       \         ___    ", 10,13
				BYTE "     /   \       [_________]       /   \   ", 10,13
				BYTE "    /     \                       /     \  ", 10,13
				BYTE "   /       \                     /       \ ", 10,13
				BYTE "  [_________]         O         [_________]", 10,13,0

ball_two2		BYTE "                     ___                   ", 10,13
				BYTE "                    /   \                  ", 10,13
				BYTE "      ___          /     \          ___    ", 10,13
				BYTE "     /   \        /       \        /   \   ", 10,13
				BYTE "    /     \      [_________]      /     \  ", 10,13
				BYTE "   /       \                     /       \ ", 10,13
				BYTE "  [_________]         O         [_________]", 10,13,0

ball_two3		BYTE "                     ___                   ", 10,13
				BYTE "      ___           /   \           ___    ", 10,13
				BYTE "     /   \         /     \         /   \   ", 10,13
				BYTE "    /     \       /       \       /     \  ", 10,13
				BYTE "   /       \     [_________]     /       \ ", 10,13
				BYTE "  [_________]         O         [_________]", 10,13,0

ball_three1		BYTE "                                    ___    ", 10,13
				BYTE "                                   /   \   ", 10,13
				BYTE "                                  /     \  ", 10,13
				BYTE "      ___            ___         /       \ ", 10,13
				BYTE "     /   \          /   \       [_________]", 10,13
				BYTE "    /     \        /     \                 ", 10,13
				BYTE "   /       \      /       \                ", 10,13
				BYTE "  [_________]    [_________]         O     ", 10,13,0

ball_three2		BYTE "                                    ___    ", 10,13
				BYTE "                                   /   \   ", 10,13
				BYTE "      ___            ___          /     \  ", 10,13
				BYTE "     /   \          /   \        /       \ ", 10,13
				BYTE "    /     \        /     \      [_________]", 10,13
				BYTE "   /       \      /       \                ", 10,13
				BYTE "  [_________]    [_________]         O     ", 10,13,0
                                    
ball_three3		BYTE "                                    ___    ", 10,13
				BYTE "      ___            ___           /   \   ", 10,13
				BYTE "     /   \          /   \         /     \  ", 10,13
				BYTE "    /     \        /     \       /       \ ", 10,13
				BYTE "   /       \      /       \     [_________]", 10,13
				BYTE "  [_________]    [_________]         O     ", 10,13,0

one_and_three1	BYTE "        ___                              ", 10,13
				BYTE "       /   \                             ", 10,13
				BYTE "      /     \        ___                 ", 10,13
				BYTE "     /       \      /   \                ", 10,13
				BYTE "    [_________]    /     \        ___    ", 10,13
				BYTE "                  /       \      /   \   ", 10,13
				BYTE "                 [_________]    /     \  ", 10,13
				BYTE "                               /       \ ", 10,13
				BYTE "                              [_________]", 10,13,0

one_and_three2	BYTE "                 ___            ", 10,13
				BYTE "                /   \           ", 10,13
				BYTE "               /     \__        ", 10,13
				BYTE "              /     /   \       ", 10,13
				BYTE "             [_____/     \__    ", 10,13
				BYTE "                  /     /   \   ", 10,13
				BYTE "                 [_____/     \  ", 10,13
				BYTE "                      /       \ ", 10,13
				BYTE "                     [_________]", 10,13,0

one_and_three3  BYTE "                          ___    ", 10,13
				BYTE "                         /   \   ", 10,13
				BYTE "                     ___/     \  ", 10,13
				BYTE "                    /   \      \ ", 10,13
				BYTE "                ___/     \______]", 10,13
				BYTE "               /   \      \      ", 10,13
				BYTE "              /     \______]     ", 10,13
				BYTE "             /       \           ", 10,13
				BYTE "            [_________]          ", 10,13,0

one_and_three4  BYTE "                                  ___    ", 10,13
				BYTE "                                 /   \   ", 10,13
				BYTE "                     ___        /     \  ", 10,13
				BYTE "                    /   \      /       \ ", 10,13
				BYTE "        ___        /     \    [_________]", 10,13
				BYTE "       /   \      /       \              ", 10,13
				BYTE "      /     \    [_________]             ", 10,13
				BYTE "     /       \                           ", 10,13
				BYTE "    [_________]                          ", 10,13,0

one_and_two1	BYTE "        ___                                ", 10,13
				BYTE "       /   \                               ", 10,13
				BYTE "      /     \                       ___    ", 10,13
				BYTE "     /       \                     /   \   ", 10,13
				BYTE "    [_________]    ___            /     \  ", 10,13
				BYTE "                  /   \          /       \ ", 10,13
				BYTE "                 /     \        [_________]", 10,13
				BYTE "                /       \                  ", 10,13
				BYTE "               [_________]                 ", 10,13,0

one_and_two2	BYTE "             ___                           ", 10,13
				BYTE "            /   \                          ", 10,13
				BYTE "           /     \                  ___    ", 10,13
				BYTE "          /       \                /   \   ", 10,13
				BYTE "         [_________]              /     \  ", 10,13
				BYTE "             /   \               /       \ ", 10,13
				BYTE "            /     \             [_________]", 10,13
				BYTE "           /       \                       ", 10,13
				BYTE "          [_________]                      ", 10,13,0

one_and_two3	BYTE "                   ___                     ", 10,13
				BYTE "                  /   \                    ", 10,13
				BYTE "                 /     \            ___    ", 10,13
				BYTE "                /       \          /   \   ", 10,13
				BYTE "        ___    [_________]        /     \  ", 10,13
				BYTE "       /   \                     /       \ ", 10,13
				BYTE "      /     \                   [_________]", 10,13
				BYTE "     /       \                             ", 10,13
				BYTE "    [_________]                            ", 10,13,0

two_and_three1	BYTE "                       ___               ", 10,13
				BYTE "                      /   \              ", 10,13
				BYTE "      ___            /     \             ", 10,13
				BYTE "     /   \          /       \            ", 10,13
				BYTE "    /     \        [_________]    ___    ", 10,13
				BYTE "   /       \                     /   \   ", 10,13
				BYTE "  [_________]                   /     \  ", 10,13
				BYTE "                               /       \ ", 10,13
				BYTE "                              [_________]", 10,13,0

two_and_three2	BYTE "                            ___     ", 10,13
				BYTE "                           /   \    ", 10,13
				BYTE "      ___                 /     \   ", 10,13
				BYTE "     /   \               /       \  ", 10,13
				BYTE "    /     \             [_________] ", 10,13
				BYTE "   /       \                /   \   ", 10,13
				BYTE "  [_________]              /     \  ", 10,13
				BYTE "                          /       \ ", 10,13
				BYTE "                         [_________]", 10,13,0

two_and_three3	BYTE "                                  ___    ", 10,13
				BYTE "                                 /   \   ", 10,13
				BYTE "      ___                       /     \  ", 10,13
				BYTE "     /   \                     /       \ ", 10,13
				BYTE "    /     \            ___    [_________]", 10,13
				BYTE "   /       \          /   \              ", 10,13
				BYTE "  [_________]        /     \             ", 10,13
				BYTE "                    /       \            ", 10,13
				BYTE "                   [_________]           ", 10,13,0

prompt			BYTE	"Now its time for you to guess which cup the ball is in",10,13,0
prompt2			BYTE	"Please enter your guess: ",0
congratulations	BYTE	"CONGRATULATIONS! You correctly guessed where the ball was.",10,13,0
sorry			BYTE	"SORRY. You picked the wrong cup.",10,13,0
yes				BYTE	"YES",0
no				BYTE	"NO",0
play_again		BYTE	"Would you like to play again? ",0

ball_position	DWORD	?
num_swaps		DWORD	?	; variable for how many swaps are to be performed
last_swap		DWORD	0	; variable for what swap was last performed

user_string		BYTE	BUFFER_SIZE DUP(0)
user_str_lngth	DWORD	?
user_int		DWORD	?

.code
main PROC
	call Randomize
	call introduction

	top:
	call game_setup
	call swapping
	call get_user_guess
	call reveal_ball
	call determine_outcome
	call get_user_answer
	INVOKE Str_compare, ADDR user_string, ADDR yes
	je top

	exit	
main ENDP

; This procedure introduces the program
; Receives: none
; Returns: none
; Pre-Conditions: none
; Registers changed: edx
introduction PROC
	mov edx, OFFSET welcome
	call WriteString
	call WaitMsg
	ret
introduction ENDP

; This procedure sets up the game
; Receives: none
; Returns: ball_position updated
; Pre-Conditions: none
; Registers changed: edx, eax
game_setup PROC
	call ClrScr
	mov edx, OFFSET setting_up
	call WriteString
	mov edx, OFFSET ready
	call WriteString
	call WaitMsg
	call ClrScr

	mov eax, 3	
	call RandomRange
	inc eax
	mov ball_position, eax

	cmp eax, 1
	je cup_one
	cmp eax, 2
	je cup_two
	call place_ball_three
	jmp end_setup

	cup_one:
	call place_ball_one
	jmp end_setup

	cup_two:
	call place_ball_two

	end_setup:
	call set_num_swaps
	ret
game_setup ENDP

; This procedure prints the ball being place in cup one
; Receives: none
; Returns: none
; Pre-Conditions: none
; Registers changed: edx, eax
place_ball_one PROC
	mov eax, 300

	mov edx, OFFSET ball_one1
	call WriteString
	call Delay
	call ClrScr

	mov edx, OFFSET ball_one2
	call WriteString
	call Delay
	call ClrScr

	mov edx, OFFSET ball_one3
	call WriteString
	call Delay
	call ClrScr

	mov edx, OFFSET rest_position
	call WriteString
	call Delay
	call ClrScr
	ret
place_ball_one ENDP

; This procedure prints the ball being placed in cup two
; Receives: none
; Returns: none
; Pre-Conditions: none
; Registers changed: edx, eax
place_ball_two PROC
	mov eax, 300

	mov edx, OFFSET ball_two1
	call WriteString
	call Delay
	call ClrScr

	mov edx, OFFSET ball_two2
	call WriteString
	call Delay
	call ClrScr

	mov edx, OFFSET ball_two3
	call WriteString
	call Delay
	call ClrScr

	mov edx, OFFSET rest_position
	call WriteString
	call Delay
	call ClrScr
	ret
place_ball_two ENDP

; This procedure prints the vall being place in cup three
; Receives: none
; Returns: none
; Pre-Conditions: none
; Registers changed: edx, eax
place_ball_three PROC
	mov eax, 300

	mov edx, OFFSET ball_three1
	call WriteString
	call Delay
	call ClrScr

	mov edx, OFFSET ball_three2
	call WriteString
	call Delay
	call ClrScr

	mov edx, OFFSET ball_three3
	call WriteString
	call Delay
	call ClrScr

	mov edx, OFFSET rest_position
	call WriteString
	call Delay
	call ClrScr
	ret
place_ball_three ENDP

; This procedure determines how many swaps will be done
; Receives: none
; Returns: num_swaps updated
; Pre-Conditions: none
; Registers changed: eax
set_num_swaps PROC
	mov eax, 8
	call RandomRange
	add eax, 3
	mov num_swaps, eax
	ret
set_num_swaps ENDP

; This procedure performs one swap
; Receives: none
; Returns: none
; Pre-Conditions: none
; Registers changed: eax, ebx
one_swap PROC
	new_num:
	mov eax, 3
	call RandomRange
	inc eax
	mov ebx, last_swap	; makes sure that the same swap is not done twice in a row
	cmp eax, ebx
	je new_num

	mov last_swap, eax

	cmp eax, 1
	je if_one
	cmp eax, 2
	je if_two
	call swap31
	jmp end_swap

	if_one:
	call swap12
	jmp end_swap

	if_two:
	call swap23

	end_swap:
	ret
one_swap ENDP

; This procedure performs all the swaps
; Receives: num_swaps global 
; Returns: none
; Pre-Conditions: none
; Registers changed: edx, ecx
swapping PROC
	mov edx, OFFSET swapping_time
	call WriteString
	mov edx, OFFSET ready
	call WriteString
	call WaitMsg
	call ClrScr

	mov ecx, num_swaps
	top:
	call one_swap
	loop top
	ret
swapping ENDP

; This procedure performs a swap with cups one and two
; Receives: none
; Returns: none
; Pre-Conditions: none
; Registers changed: none
swap12 PROC
	call swap12_animation
	call swap12_adjusting
	ret
swap12 ENDP

; This procedure prints the animation of swapping one and two
; Receives: none
; Returns: none
; Pre-Conditions: none
; Registers changed: edx, eax
swap12_animation PROC
	mov eax, 100

	mov edx, OFFSET rest_position
	call WriteString
	call Delay
	call ClrScr

	mov edx, OFFSET one_and_two1
	call WriteString
	call Delay
	call ClrScr

	mov edx, OFFSET one_and_two2
	call WriteString
	call Delay
	call ClrScr

	mov edx, OFFSET one_and_two3
	call WriteString
	call Delay
	call ClrScr

	mov edx, OFFSET rest_position
	call WriteString
	call Delay
	call ClrScr
	ret
swap12_animation ENDP

; This procedure adjusts ball_position
; Receives: ball_position global
; Returns: ball_position adjusted
; Pre-Conditions: none
; Registers changed: eax
swap12_adjusting PROC
	mov eax, ball_position
	cmp eax, 1
	je make_two
	cmp eax, 2
	je make_one
	jmp end_adjusting

	make_two:
	mov eax, 2
	mov ball_position, eax
	jmp end_adjusting

	make_one:
	mov eax, 1
	mov ball_position, eax
	jmp end_adjusting

	end_adjusting:
	ret
swap12_adjusting ENDP

; This procedure performs a swap with cups two and three
; Receives: none
; Returns: none
; Pre-Conditions: none
; Registers changed: none
swap23 PROC
	call swap23_animation
	call swap23_adjusting
	ret
swap23 ENDP

; This procedure prints the animation of swapping two and three
; Receives: none
; Returns: none
; Pre-Conditions: none
; Registers changed: edx, eax
swap23_animation PROC
	mov eax, 100

	mov edx, OFFSET rest_position
	call WriteString
	call Delay
	call ClrScr

	mov edx, OFFSET two_and_three1
	call WriteString
	call Delay
	call ClrScr

	mov edx, OFFSET two_and_three2
	call WriteString
	call Delay
	call ClrScr

	mov edx, OFFSET two_and_three3
	call WriteString
	call Delay
	call ClrScr

	mov edx, OFFSET rest_position
	call WriteString
	call Delay
	call ClrScr
	ret
swap23_animation ENDP

; This procedure adjusts ball_position
; Receives: ball_position global
; Returns: ball_position adjusted
; Pre-Conditions: none
; Registers changed: eax
swap23_adjusting PROC
	mov eax, ball_position
	cmp eax, 2
	je make_three
	cmp eax, 3
	je make_two
	jmp end_adjusting

	make_three:
	mov eax, 3
	mov ball_position, eax
	jmp end_adjusting

	make_two:
	mov eax, 2
	mov ball_position, eax
	jmp end_adjusting

	end_adjusting:
	ret
swap23_adjusting ENDP

; This procedure performs a swap with cups three and one
; Receives: none
; Returns: none
; Pre-Conditions: none
; Registers changed: none
swap31 PROC
	call swap31_animation
	call swap31_adjusting
	ret
swap31 ENDP

; This procedure prints the animation of swapping three and one
; Receives: none
; Returns: none
; Pre-Conditions: none
; Registers changed: edx, eax
swap31_animation PROC
	mov eax, 100

	mov edx, OFFSET rest_position
	call WriteString
	call Delay
	call ClrScr

	mov edx, OFFSET one_and_three1
	call WriteString
	call Delay
	call ClrScr

	mov edx, OFFSET one_and_three2
	call WriteString
	call Delay
	call ClrScr

	mov edx, OFFSET one_and_three3
	call WriteString
	call Delay
	call ClrScr

	mov edx, OFFSET one_and_three4
	call WriteString
	call Delay
	call ClrScr

	mov edx, OFFSET rest_position
	call WriteString
	call Delay
	call ClrScr
	ret
swap31_animation ENDP

; This procedure adjusts ball_position
; Receives: ball_position global
; Returns: ball_position adjusted
; Pre-Conditions: none
; Registers changed: eax
swap31_adjusting PROC
	mov eax, ball_position
	cmp eax, 3
	je make_one
	cmp eax, 1
	je make_three
	jmp end_adjusting

	make_one:
	mov eax, 1
	mov ball_position, eax
	jmp end_adjusting

	make_three:
	mov eax, 3
	mov ball_position, eax
	jmp end_adjusting

	end_adjusting:
	ret
swap31_adjusting ENDP

; This procedure gets the user's guess
; Receives: none
; Returns: user_int adjusted
; Pre-Conditions: none
; Registers changed: edx, ecx, eax
get_user_guess PROC
	mov edx, OFFSET prompt
	call WriteString
	
	getting_guess:
	mov edx, OFFSET prompt2
	call WriteString
	mov edx, OFFSET user_string
	mov ecx, BUFFER_SIZE
	call ReadString
	call is_num
	cmp eax, 0
	je getting_guess

	push OFFSET user_int
	call string_to_int

	ret
get_user_guess ENDP

; This procedure animates the ball being revealed
; Receives: ball_position as global
; Returns: none
; Pre-Conditions: none
; Registers changed: eax
reveal_ball PROC
	call WaitMsg
	call ClrScr
	mov eax, ball_position
	cmp eax, 1
	je cup_one
	cmp eax, 2
	je cup_two
	call reveal_ball_three
	jmp bottom

	cup_one:
	call reveal_ball_one
	jmp bottom

	cup_two:
	call reveal_ball_two

	bottom:
	ret
reveal_ball ENDP

; This procedure animates the ball being revealed in cup one
; Receives: none
; Returns: none
; Pre-Conditions: none
; Registers changed: eax, edx
reveal_ball_one PROC
	mov eax, 300

	mov edx, OFFSET rest_position
	call WriteString
	call Delay
	call ClrScr

	mov edx, OFFSET ball_one3
	call WriteString
	call Delay
	call ClrScr

	mov edx, OFFSET ball_one2
	call WriteString
	call Delay
	call ClrScr

	mov edx, OFFSET ball_one1
	call WriteString
	ret
reveal_ball_one ENDP

; This procedure animates the ball being revealed in cup two
; Receives: none
; Returns: none
; Pre-Conditions: none
; Registers changed: eax, edx
reveal_ball_two PROC
	mov eax, 300

	mov edx, OFFSET rest_position
	call WriteString
	call Delay
	call ClrScr

	mov edx, OFFSET ball_two3
	call WriteString
	call Delay
	call ClrScr

	mov edx, OFFSET ball_two2
	call WriteString
	call Delay
	call ClrScr

	mov edx, OFFSET ball_two1
	call WriteString
	ret
reveal_ball_two ENDP

; This procedure animates the ball being revealed in cup three
; Receives: none
; Returns: none
; Pre-Conditions: none
; Registers changed: eax, edx
reveal_ball_three PROC
	mov eax, 300

	mov edx, OFFSET rest_position
	call WriteString
	call Delay
	call ClrScr

	mov edx, OFFSET ball_three3
	call WriteString
	call Delay
	call ClrScr

	mov edx, OFFSET ball_three2
	call WriteString
	call Delay
	call ClrScr

	mov edx, OFFSET ball_three1
	call WriteString
	ret
reveal_ball_three ENDP

; This procedure determines how the user did
; Receives: user_int, ball_position as global
; Returns: none
; Pre-Conditions: none
; Registers changed: eax, edx
determine_outcome PROC
	mov eax, user_int
	cmp eax, ball_position 
	je winner
	mov edx, OFFSET sorry
	call WriteString
	jmp bottom

	winner:
	mov edx, OFFSET congratulations
	call WriteString

	bottom:
	ret
determine_outcome ENDP

; This procedure asks the user if they would like to play again
; Receives: none
; Returns: user_string adjusted
; Pre-Conditions: none
; Registers changed: eax, edx, ecx
get_user_answer PROC
	getting_answer:
	mov edx, OFFSET play_again
	call WriteString
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
	ret
get_user_answer ENDP

; This procedure determines if a string is an integer
; Receives: none
; Returns: 1 for yes, 0 for no
; Pre-Conditions: none
; Registers changed: eax, edi, ecx
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

; This procedure converts a string into its integer equivalence
; Receives: none
; Returns: user_int adjusted
; Pre-Conditions: user_string is an integer string
; Registers changed: eax, edi, ecx, ebx
string_to_int PROC
	push ebp
	mov ebp, esp
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

END main
