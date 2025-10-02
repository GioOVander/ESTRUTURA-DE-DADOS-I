#include <stdio.h>

int main(){
    int *ptr; //ponteiro foi criado mas n foi "inicializado", ou seja n ta apontando pra lugar nenhum

    printf("Endereço guardado em ptr: %p\n", ptr); //ptr nao foi inicializado
    printf("Valor em *ptr: %d\n", *ptr); //tá tentando acessar um endereço que memoria que nao pertence ao programa, e se conseguisse acessar esse endereço pegaria lixo da memoria
}