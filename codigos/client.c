#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define PIPE_NUMBERS "pipe_numbers"
#define PIPE_STRINGS "pipe_strings"
#define BUFFER_SIZE 256

void request_number() {
    int fd;
    char buffer[BUFFER_SIZE];

    fd = open(PIPE_NUMBERS, O_RDONLY);
    if (fd < 0) {
        perror("Erro ao abrir pipe de números");
        return;
    }

    read(fd, buffer, BUFFER_SIZE);
    printf("Resposta do servidor: %s\n", buffer);
    close(fd);
}

void request_string() {
    int fd;
    char buffer[BUFFER_SIZE];

    fd = open(PIPE_STRINGS, O_RDONLY);
    if (fd < 0) {
        perror("Erro ao abrir pipe de strings");
        return;
    }

    read(fd, buffer, BUFFER_SIZE);
    printf("Resposta do servidor: %s\n", buffer);
    close(fd);
}

int main() {
    int op;

    printf("Escolha uma opção:\n ");
    printf("1. Solicitar número\n");
    printf("2. Solicitar string\n");
    scanf("%d", &op);

    switch(op) {
        case 1:
            request_number();
            break;
        case 2:
            request_string();
            break;
        default:
            printf("Opção inválida!\n");
            break;
    }

    return 0;
}
