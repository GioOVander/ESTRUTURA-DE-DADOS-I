#include <stdio.h>

 struct Peixe {
    char tipo[99];   
    float peso;      
    int comprimento; 
};

void mostrarPeixe(struct Peixe x) {
    printf("Tipo: %s\n", x.tipo);
    printf("Peso: %.3f\n", x.peso);
    printf("Comprimento: %d\n", x.comprimento);
}

void mostrarPeixePtr(struct Peixe *x){
    printf("Tipo: %s\n", x->tipo);
    printf("Peso: %.3f\n", x->peso);
    printf("Comprimento: %d\n", x->comprimento);
}

int main(){
    struct Peixe peixe1;

printf("Digite o tipo do peixe: \n");
scanf("%98s", &peixe1.tipo);

printf("Digite o peso do peixe: (EM KILOS) \n");
scanf("%f", &peixe1.peso);

printf("Digite o comprimento do peixe: (EM CENTIMETROS) \n");
scanf("%d", &peixe1.comprimento);

mostrarPeixe(peixe1); //valor
mostrarPeixePtr(&peixe1); //ponteiro

return 0;
}