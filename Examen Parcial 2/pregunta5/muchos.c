#include <stdio.h>
#include <unistd.h>

void funcion(int a,int b);

void call_3_times(int a) {

    for(int i=0; i<4; i++) {
        if (i<3){
            printf("Proceso %d, iteracion %d\n", a, i);
            sleep(1);}
        else{
            exit(0);
        }
    }
}

int main() {
    if (!fork()) call_3_times(0);
    if (!fork()) call_3_times(1);
    if (!fork()) call_3_times(2);
}
