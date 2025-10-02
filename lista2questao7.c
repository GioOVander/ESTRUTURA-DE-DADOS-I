#include <stdio.h>

union Cores {
    struct{
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;

    }
    rgba;
    unsigned int rgba32bit;
};

void lercor(union Cores *c){
    printf("Digite a cor no formato RGBA (NA ORDEM): \n");
    scanf("%hhu %hhu %hhu %hhu", &c->rgba.r, &c->rgba.g, &c->rgba.b, &c->rgba.a);
}

void ler32bits(union Cores *c){
    printf("Digite a cor no formato 32bits: \n");
    scanf("%u", &c->rgba32bit);
}

int main(){
union Cores cor;

printf("Digite o RGBA: \n");
lercor(&cor);

printf("Valor em Int32: %u\n", cor.rgba32bit);

printf("Digite o Int32: \n");
ler32bits(&cor);

printf("Valor em RGBA: %u %u %u %u\n", cor.rgba.r, cor.rgba.g, cor.rgba.b, cor.rgba.a);


return 0;
}