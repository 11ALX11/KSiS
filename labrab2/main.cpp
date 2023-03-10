#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <locale.h>

using namespace std;

const int STRING_CHARACTER_LIMIT = 100;

void workButC(char* text);

int main()
{
	setlocale(LC_ALL, "");

	char* text = new char[STRING_CHARACTER_LIMIT];
	strcpy(text, "Mom is washing a window,2 Father is repairing a car,1 Его друзья ждутF.");

	/*FILE* input_file_ptr;
	if (fopen_s(&input_file_ptr, "text.txt", "r")) {
		perror("Error opening file!");
		return 1;
	}
	fgets(text, STRING_CHARACTER_LIMIT, input_file_ptr);
	fclose(input_file_ptr);*/

	int isText = 0;

	_asm {
		; в edx будут условия текста
		xor edx, edx

		; используем как счетчик в цикле
		xor eax, eax

		; цикл с условием
		; (text[i] != '.')
	first_lat_while_start:
		mov		cl, [esi]  
		cmp		cl, 2Eh
		je		first_lat_while_end
			; если первая буква..
			test	eax,eax  ; (определяем первую букву по счетчику)
			jne		first_char_if_end
				; ..латинская
				; ((text[0] > 'a' && text[0] < 'z') || (text[0] > 'A' && text[0] < 'Z')) {
				cmp		cl,61h  
				jle		first_lat_else_start
				cmp		cl,7Ah  
				jl		first_lat_if_start
				cmp		cl,41h  
				jle		first_lat_else_start
				cmp		cl,5Ah  
				jge		first_lat_else_start
					; то +1 к условию текста
				first_lat_if_start:
					inc     edx  
				; конец условия
				; блок иначе
				jmp		first_lat_else_end
				first_lat_else_start:
					jmp		ne_text 
				; конец иначе
				first_lat_else_end:
			; конец условия
			first_char_if_end:

			; увеличиваем счетчик в цикле
			inc		eax

			; конец тела цикла
			cmp		[eax+esi],2Eh  
			jne		first_lat_while_start
		; конец цикла
	first_lat_while_end:

		mov     al, [eax+esi-1] ; получаем последний символ (перед точкой)
		; и проверяем его на условие
		; ((text[i] > 'a' && text[i] < 'z') || (text[i] > 'A' && text[i] < 'Z'))
		cmp		al,61h  
		jle		last_lat_if_start
		cmp		al,7Ah  
		jl		last_lat_else_start
		cmp		al,41h  
		jle		last_lat_if_start
		cmp		al,5Ah  
		jge		last_lat_if_start
			last_lat_if_start:
				inc		edx ; +1 к условию текста
		; конец условия
		; блок иначе
		jmp		last_lat_else_end
		last_lat_else_start:
				jmp		ne_text
		; конец иначе
		last_lat_else_end:

		; если у нас 2 условия текста
		cmp		edx,2  
		jne		text_check_else_start
			; обнуляем счетчик
			push        ebx  
			xor         ebx,ebx  
			; цикл while (text[i] != '.')
		text_change_while_start:
			cmp         cl,2Eh  
			je          text_change_while_end
				; если прописная русская
				; (text[i] > 'A' && text[i] < 'Z')
				mov         al,[ebx+esi]  
				cmp         al,41h  
				jle         text_change_if_end
				cmp         al,5Ah  
				jge         text_change_if_end
					; то заменяем символ:
					; text[i] = ('0' + i % 10)
					mov         eax,66666667h  
					imul        ebx  
					sar         edx,2  
					mov         eax,edx  
					shr         eax,1Fh  
					add         eax,edx  
					mov         cl,al  
					shl         al,2  
					add         cl,al  
					mov         al,bl  
					add         cl,cl  
					sub         al,cl  
					add         al,30h  
					mov         [ebx+esi],al  
				; конец условия
				text_change_if_end:
				
				inc         ebx ; увеличиваем счетчик

				; конец тела цикла
				cmp         [ebx+esi],2Eh  
				jne         text_change_while_start
			; конец цикла
			text_change_while_end:
		; конец условия
		jmp		text_check_else_end
		; блок иначе
		text_check_else_start:
			jmp ne_text
		; конец иначе
		text_check_else_end:
		jmp pr_end

		ne_text:
			xor ebx, ebx
			inc ebx
			mov [isText], ebx

		pr_end:
	}

	//workButC(text);

	if (isText == 0) {
		printf("%s\n", text);
	}
	else {
		printf("This isn't a text!\n");
	}

	return 0;
}

void workButC(char* text) {
	int check = 0;

	int i = 0;
	while (text[i] != '.') {
		if (i == 0) {
			if ((text[0] > 'a' && text[0] < 'z') || (text[0] > 'A' && text[0] < 'Z')) {
				check++;
			}
			else {
				//goto NE TEXT
			}
		}

		i++;
	}

	if (check == 0) {
		//goto NE TEXT
	}

	i--;
	if ((text[i] > 'a' && text[i] < 'z') || (text[i] > 'A' && text[i] < 'Z')) {
		check++;
	}
	else {
		//goto NE TEXT
	}

	cout << check << endl;

	if (check == 2) {
		i = 0;
		while (text[i] != '.') {
			if (text[i] > 'A' && text[i] < 'Z') {
				text[i] = ('0' + i % 10);
			}
			i++;
		}
	}
	else {
		//goto NE TEXT
	}
}
