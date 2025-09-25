#include <stdio.h>

int main(){
char ch = 'G';
char *indica = &ch;
//a maneira correta de referenciar o enderço de ch é utilizar *indica

printf("%c", indica);
return 0; 
}