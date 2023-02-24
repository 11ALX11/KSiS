#include "stdafx.h"
#include <stdio.h>

using namespace std;

const int STRING_CHARACTER_LIMIT = 100;

int main()
{
	char *text = new char[STRING_CHARACTER_LIMIT];

	FILE *input_file_ptr;
	if (fopen_s(&input_file_ptr, "text.txt", "r")) {
		perror("Error opening file!");
		return 1;
	}
	fgets(text, STRING_CHARACTER_LIMIT, input_file_ptr);
	fclose(input_file_ptr);

	_asm {
		mov	ecx, 0		; обнуляем счетчик
		mov edx, text	; помещаем строку в edx

		loop1:					; цикл loop1
			cmp [edx], '.'		; ищем границу текста, сравнивая символы строки с точкой
			inc edx				; инкремент
			jne	loop1			; если не точка, продолжаем цикл
		dec edx
		mov [edx], '$'	; заменяем точку
	}

	printf("%s\n", text);

    return 0;
}

