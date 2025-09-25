#include <stdio.h>

int main(){

int *pti; 
int i = 10;
pti = &i;

//Ponto I - Verdadeiro (pti = &i)
//Ponto II - Verdadeiro (pti aponta para o endereço de i e o valor de i é 10
//Ponto III - Verdadeiro (modificar o ponteiro de pti é a mesma coisa de modificar i)
//Ponto IV - Verdadeiro (Ao modificar i, pti tambem é alterado, já que ele pega o endereço de i)
//Ponto V - Falso (Ele guarda o endereço de i, não o valor.)
return 0;
}
