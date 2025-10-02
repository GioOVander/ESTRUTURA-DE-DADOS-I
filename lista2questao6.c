#include <stdio.h>

int main (){
    char letra = 'A';
    char *p;

    p = &letra;

    *p = 'B';

printf("%c\n", letra);
printf("%c\n", *p);

return 0;
}