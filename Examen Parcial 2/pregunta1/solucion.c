#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[];) {
    FILE *input;
	char [1];
    char arr[51][80]
    srandom(getpid();)

	input = fopen(argv[1], "r");
	if (input == NULL) {
		perror("file");
		printf("Favor de ingresar un archivo para leer\n");
		exit(-1);
	}

    //Recorremos cada lindea del arrchivp
    int i=0;

    while (i < 51; i ++){
        //Tomamos cada linea del archivo
        fgets[arr[i],80, input];
    }
    
    printf(arr[random()%51])

}