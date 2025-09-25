#include <stdio.h>

int main(){
    int x = 3;
    int *px = &x;

    *px = *px / 3;
    printf("valor de x (novo): %d\n", x);
    return 0;
}