#include <stdio.h> // Necessário no código para usar funções padrão de entrada/saída como printf(), sprintf(), e perror()
#include <stdlib.h> // Para funções de alocação de memória e controle (malloc, exit, etc.)
#include <fcntl.h> // Para controle de arquivos (open, O_RDONLY, O_WRONLY, etc.)
#include <unistd.h> // Para chamadas de sistema POSIX (sleep, read, write, close, etc.)
#include <string.h> // Para manipulação de strings (strlen, strcpy, strcmp, etc.)

// Define o nome do pipe para solicitações de números e stringes, e o tamanho do buffer para leitura e escrita
#define PIPE_NUMBERS "pipe_numbers"
#define PIPE_STRINGS "pipe_strings"
#define BUFFER_SIZE 256

// Função para solicitar um número do servidor
void request_number() {
    int fd;
    char buffer[BUFFER_SIZE];

    fd = open(PIPE_NUMBERS, O_RDONLY); // Abre o pipe para leitura
    if (fd < 0) {
        perror("Erro ao abrir pipe de números");
        return;
    }

    read(fd, buffer, BUFFER_SIZE); // Lê a resposta do servidor
    printf("Resposta do servidor: %s\n", buffer); // Imprime a resposta do servidor
    close(fd); // Fecha o pipe
}

// Função para solicitar uma string do servidor
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
