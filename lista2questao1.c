#include <stdio.h>

int main(){
    struct Peixe {
    char tipo[99];   
    float peso;      
    int comprimento; 
};

struct Peixe peixe1;
printf("Digite o tipo do peixe: \n");
scanf("%98s", &peixe1.tipo); //só lê 98 caracteres porque o nonagesimo nono é guardado pro \0

printf("Digite o peso do peixe: (EM KILOS) \n");
scanf("%f", &peixe1.peso);

printf("Digite o comprimento do peixe: (EM CENTIMETROS) \n");
scanf("%d", &peixe1.comprimento);

struct Peixe *ptrpeixe;
ptrpeixe = &peixe1;


printf("Tipo: %s\n", ptrpeixe->tipo);
printf("Peso: %.3f\n", ptrpeixe->peso);
printf("Comprimento: %d\n", ptrpeixe->comprimento);

return 0;
}