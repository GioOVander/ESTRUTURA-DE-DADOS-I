#include <stdio.h>

void MaisMais(int *num){
    (*num)++; //altera o valor diretamente
}

int Incrementa(int num){
    return num + 1;  //recebe a copia de um valor e retorna o resultado incrementado
}

int main(){
    int valor;

    printf("Digite um valor (INTEIRO): \n");
    scanf("%d", &valor);

    MaisMais(&valor);
    printf("Resultado apos MaisMais: %d\n", valor);

    printf("Resultado apos incrementar: %d\n", Incrementa(valor));

    return 0;
}