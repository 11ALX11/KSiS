#include "stdafx.h"

#include <stdio.h>

using namespace std;

void change_stringsC(char *s1, char *s2);
void change_stringsA(char *s1, char *$2);

int main()

char s1[255];
char s2[255];
char s3[255];
char s4[255];

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
	s4[1++] = tmp;
}
s4[1] = '\0';

//change strings.

change_stringsC(s1, s3);
change stringsC(s2, s4);

//out

puts(s1);
puts(s2);
puts(s3);
puts(s4);

return 0;

void change_stringsC(char s1, char *s2)

char s[255]; int i;

i = 0;
while (s1[i] != '\0') {
	s[i] = s1[i];
	i++
}
s[i] = '\0';

i = 0;
while (s2[1] != '\0') {
	s1[i] = s2[i];
	i++;
}
s1[1] = '\0';

i = 0;
while (s[i] != '\0') {
	s2[i] = s[i];
	i++;
}
s2[i] = '\0';

void change_stringsA(char *s1, char *s2) {

}

