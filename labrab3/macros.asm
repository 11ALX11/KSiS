
; define a macro that deletes a given character from a string
delete_char MACRO string, char
	LOCAL loop_start, loop_end, if_not_match
	mov esi, OFFSET string ; esi points to the beginning of the string
	mov ecx, 0          ; initialize the loop counter to 0
loop_start:
	cmp byte ptr [esi+ecx], 0 ; compare the current character to the 0 terminator
	je loop_end         ; if the characters match, exit the loop
	cmp byte ptr [esi+ecx], char ; compare the current character to one to be deleted
	jne if_not_match         ; if the characters match, exit the loop
	mov edx, ecx        ; save the position of the character to be deleted
if_not_match:
	inc ecx
	jmp loop_start
loop_end:
	mov esi, OFFSET string ; reset esi to the beginning of the string
	add esi, edx        ; add the offset of the character to be deleted
	; ecx is a maximum length of the string
	sub ecx, edx        ; subtract the offset of the character to be deleted
	cld                 ; clear the direction flag
	rep movsb           ; move the remaining characters to the left to fill the gap
ENDM

; define macro for counting words
count_words MACRO string
    LOCAL loop_start, loop_end
    mov eax, 1              ; Initialize words counter
    mov ecx, 0              ; Initialize the counter to zero
    mov esi, [string]          ; Get the address of the string
    
    loop_start:
        cmp byte ptr [esi+ecx], 0    ; Check for end of string
        je loop_end              ; If we've reached the end, exit the loop

        ; Skip space
        cmp byte ptr [esi+ecx], ' '  
        jne skip_char

        ; We've found the start of a new word
        inc eax

        ; Skip to the end of the current word
        skip_char:
            inc ecx
            jmp loop_start

    loop_end:
ENDM
