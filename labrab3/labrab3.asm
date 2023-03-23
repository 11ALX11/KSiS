    .486                                    ; create 32 bit code
    .model flat, stdcall                    ; 32 bit memory model
    option casemap :none                    ; case sensitive
 
    include \masm32\include\windows.inc     ; always first
    include \masm32\macros\macros.asm       ; MASM support macros

  ; -----------------------------------------------------------------
  ; include files that have MASM format prototypes for function calls
  ; -----------------------------------------------------------------
    include \masm32\include\masm32.inc
    include \masm32\include\gdi32.inc
    include \masm32\include\user32.inc
    include \masm32\include\kernel32.inc

  ; ------------------------------------------------
  ; Library files that have definitions for function
  ; exports and tested reliable prebuilt code.
  ; ------------------------------------------------
    includelib \masm32\lib\masm32.lib
    includelib \masm32\lib\gdi32.lib
    includelib \masm32\lib\user32.lib
    includelib \masm32\lib\kernel32.lib
    
    include \Users\marin\Documents\KSiS\labrab3\macros.asm

.data
  text db "Hello world!",10,0
  char db 'H'
.code
start:
	; print the text
	print "Text:",10	; 10 = '\n'
	print addr text,10

	; print the chr character
	;print "Character to delete: ",10
	;print chr$(char,10)

	; example usage of the delete_char macro
	delete_char OFFSET text, char

	; print result
	print "Result:",10
	print addr text

	; example usege of the count_words macro
	; result in eax
	count_words OFFSET text
        
        mov ebx, eax

	; print words count
	print "Words:",10
	print str$(ebx),10,0

end start
