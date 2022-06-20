#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void char_por_char(char *p) {
    srandom(getpid());
    while(*p) {
        putc(*p, stdout);
        fflush(stdout);
        usleep(random()%100000);
        p++;
    }
}


int main() {
    if(!fork()) {
      sleep(1);
      char_por_char("Adios, soy el proceso padre\n");
        if(!fork()) {
            sleep(1);
            char_por_char("Hola, soy el proceso nieto\n");
        }
    }


    return 0;
}