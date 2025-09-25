#include <stdio.h>

int main(){
    int x;
    int *px;
    px = &x;

    scanf("%d", *px);

    //vai estar incorreto porque o scanf espera receber o endereço e o *px vai pegar o conteúdo de x achando que é um endereço.
    //remover o ponteiro do scanf resolveria o problema

    scanf("%d", px);
    return 0;
}