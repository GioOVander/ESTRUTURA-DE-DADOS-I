#include <stdio.h>

int ablueblue (int *v1, int *v2){
    int junto[10];
    int i, j, temp;

    for (i = 0; i < 5; i++){
        *(junto + i) = *(v1 + i);
    }

    for (i = 0; i < 5; i++){
        *(junto + 5 + i) = *(v2 + i);
    }

for (i = 0; i < 9; i++){
    for(j = 0; j < 9 - i; j++){
        if (*(junto + j) > *(junto + j + 1)){
            temp = *(junto + j);
            *(junto + j) = *(junto +j + 1);
            *(junto + j + 1) = temp;
        }
    }
}

printf("Saida: ");
for (i = 0; i < 10; i++){
    printf("%d", *(junto + i));
    if (i < 9){
        printf(", ");
        }
    }
    printf("\n");
}

int main(){
    int vetordesgraca1[5] = {2, 5, 9, 8, 3};
    int vetordesgraca2[5] = {7, 4, 1, 10, 6};

    ablueblue (vetordesgraca1, vetordesgraca2);
    return 0;
}