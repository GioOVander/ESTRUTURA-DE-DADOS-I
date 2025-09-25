#include <stdio.h>

int main(){
    float pi = 3.14;
    float *ptr;

    ptr = &pi;

 //nesse caso o que é do tipo float é onde o ponteiro apontar, então o dado apontado por ptr é do tipo float
    printf("%f\n", ptr);
    printf("%f\n", *ptr);
    return 0;
}