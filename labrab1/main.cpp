
#include <stdio.h>
#include <iostream>
#include <chrono>

using namespace std;

void change_stringsC(char** s1, char** s2);
void change_stringsA(char** s1, char** $2);

int main() {

	char *s1 = new char[255];
	char *s2 = new char[255];
	char *s3 = new char[255];
	char *s4 = new char[255];

	//in

	int i = 0;
	char tmp;

	while ((tmp = getchar()) != '\n' && tmp != '\0') {
		s1[i++] = tmp;
	}
	s1[i] = '\0';

	i = 0;
	while ((tmp = getchar()) != '\n' && tmp != '\0') {
		s2[i++] = tmp;
	}
	s2[i] = '\0';

	i = 0;
	while ((tmp = getchar()) != '\n' && tmp != '\0') {
		s3[i++] = tmp;
	}
	s3[i] = '\0';

	i = 0;
	while ((tmp = getchar()) != '\n' && tmp != '\0') {
		s4[i++] = tmp;
	}
	s4[i] = '\0';

	//change strings.


	auto beginC = chrono::system_clock::now();
	change_stringsC(&s1, &s3);
	auto timeC = (chrono::system_clock::now() - beginC).count();

	auto beginA = chrono::system_clock::now();
	change_stringsA(&s2, &s4);
	auto timeA = (chrono::system_clock::now() - beginA).count();

	//out

	puts(s1);
	puts(s2);
	puts(s3);
	puts(s4);

	cout << "C function: " << timeC << " ticks" << endl;
	cout << "Assembler function: " << timeA << " ticks" << endl;

	return 0;

}

void change_stringsC(char** s1, char** s2) {
	char* s = *s1;
	*s1 = *s2;
	*s2 = s;
}

void change_stringsA(char** s1, char** s2) {
	char* s;

	__asm {
		//s = *s1;
		mov         eax, [s1]
		mov         ecx, [eax]
		mov         [s], ecx
		//*s1 = *s2;
		mov         eax, [s1]
		mov         ecx, [s2]
		mov         edx, [ecx]
		mov         [eax], edx
		//*s2 = s;
		mov         eax, [s2]
		mov         ecx, [s]
		mov         [eax], ecx
	}
}
