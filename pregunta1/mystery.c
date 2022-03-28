#include <stdio.h>
#define I2S(x) ((short *) x)

int main() {
    int i, x[10];

    for(i=0; i<10; i++) {
        x[i] = i;
    }

    //¿Por qué se imprimen alternados con 0 los numeros asignados en el for anterior?
    //El short es un tipo de dato de 2 bits y en el for lo va conviertiendo e imprimiendo segun el tamaño del int
    for(i=0; i<10; i++) {
        printf("%d\n", *I2S(x+i));
    }
    
}
