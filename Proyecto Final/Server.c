#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

#define puerto 8000
#define tamaño 16
#define tamaño2 1024
void serve(int s)
{
    char buffer[tamaño];
    int size, i = 0;
    struct stat buf;
    const char space[2] = " ";
    char *token;
    char filetosend[100];
    char fileType[100];
    FILE *sin = fdopen(s, "r");
    FILE *sout = fdopen(s, "w");
    int status;

    // Peticion del cliente
    while (fgets(buffer, tamaño2, sin) != NULL)
    {
        printf("%d - [%s]\n", ++i, buffer);
        if (i == 1)
        {
            int indice = 1;
            token = strtok(buffer, space);
            while (token != NULL)
            {
                if (indice == 2)
                {
                    if (strcmp(strcpy(filetosend, token), "/") == 0)
                    {
                        strcpy(filetosend, "archivo.txt");
                        strcpy(fileType,".txt");
                        char *filename = "archivo.txt";
                        FILE *fp = fopen(filename, "w");
                        if (fp == NULL)
                        {
                            printf("Error abriendo el archivo %s", filename);
                            return -1;
                        }
                        struct dirent *de;
                        DIR *dr = opendir(".");
                        if (dr == NULL)
                        {
                            printf("Error abriendo el archivo %s", filename);
                            printf("No se pudo abrir");
                            return 0;
                        }
                        while ((de = readdir(dr)) != NULL)
                        {
                            fprintf(fp, "%s\n", de->d_name);
                        }
                        fclose(fp);
                        closedir(dr);
                    }
                    else
                    {
                        strcpy(filetosend, token + 1);
                        strcpy(fileType,token+1);
                    }
                }
                indice++;
                token = strtok(NULL, space);
            }
        


        }
        if (buffer[0] == '\r' && buffer[1] == '\n')
        {
            break;
        }
    }

    sprintf(buffer, "HTTP/1.0 200 OK\r\n");
    fputs(buffer, sout);

    sprintf(buffer, "Fecha: Lunes, 20 Junio 2222 23:59:59 \r\n");
    fputs(buffer, sout);
    char *comparacion;
    strcpy(comparacion,fileType);
    char *contiene;
    contiene = strstr(comparacion, ".html");
    if (contiene)
    {
        sprintf("Content-Type:", "text/html\r\n");
        fputs(buffer, sout);
        printf("EL TIPO DE ARCHIVO SE MANDO COMO HTML");
    }
    char *contiene2;
    contiene2 = strstr(comparacion, ".jpg");
    if (contiene2)
    {
        sprintf("Content-Type:", "image/jpg\r\n");
        fputs(buffer, sout);
    }
    char *contiene3;
    contiene3 = strstr(comparacion, ".png");
    if (contiene3)
    {
        sprintf("Content-Type:", "image/png\r\n");
        fputs(buffer, sout);
    }
    char *contiene4;
    contiene4 = strstr(comparacion, ".txt");
    if (contiene4)
    {
        sprintf("Content-Type:", "text/plain\r\n");
        fputs(buffer, sout);
    }

    stat(filetosend, &buf);
    printf("Tamaño  %d\n", (int)buf.st_size);

    sprintf(buffer, "Tamaño del Contenido %d\r\n", (int)buf.st_size);
    fputs(buffer, sout);

    sprintf(buffer, "\r\n");
    fputs(buffer, sout);

    FILE *fin = fopen(filetosend, "r");
    while ((size = fread(buffer, 1, tamaño2, fin)) != 0)
    {
        size = fwrite(buffer, 1, size, sout);
    }

    fflush(0);
}

int main()
{
    int se, se2, size, r;
    struct sockaddr_in sin, pin;
    socklen_t addrlen;

    
    se = socket(AF_INET, SOCK_STREAM, 0);

    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(puerto);

    r = bind(se, (struct sockaddr *)&sin, sizeof(sin));
    if (r < 0)
    {
        perror("bind");
        return -1;
    }
    listen(se, 5);

    addrlen = sizeof(pin);

    while ((se2 = accept(se, (struct sockaddr *)&pin, &addrlen)) > 0)
    {
        if (!fork())
        {
            printf("Connected from %s\n", inet_ntoa(pin.sin_addr));
            printf("Port %d\n", ntohs(pin.sin_port));

            serve(se2);

            close(se2);
            exit(0);
        }
    }

    close(se);

    sleep(1);
}