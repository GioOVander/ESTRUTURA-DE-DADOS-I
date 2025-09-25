#include <stdio.h>

int main(){
    int x = 68, y; // x recebe 68, enquanto y é declarado sem valor.
    int *p; //declara um ponteiro
    p = &x; //p armazena o endereço de x
    y = *p + 200; // y recebe o ponteiro de p (onde ele tá apontando, que no caso é x (68)) e soma com 200 (68 + 200)

    printf("x = %i\n", x);
    printf("y = %i\n", y);
    printf("p = (endereco de x) %i\n", p);
    printf("*p = (x so que pelo ponteiro) = %i\n", *p);
    return 0;
}