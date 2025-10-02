#include <stdio.h>

int main(){
//só trocar o ponteiro do ponteiro de p pelo ponteiro do ponteiro de q e trocar o %p por um %d

    int x, *p, **q; 
    p = &x;
    q = &p;
    x = 10;

    printf("%d\n", (void*)**q);

    return 0;
}