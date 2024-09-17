#include <stdio.h> // Necessário no código para usar funções padrão de entrada/saída como printf(), sprintf(), e perror()
#include <stdlib.h> // Para funções de alocação de memória e controle (malloc, exit, etc.)
#include <pthread.h> // Para manipulação de threads (pthread_create, pthread_join, etc.)
#include <unistd.h> // Para chamadas de sistema POSIX (sleep, read, write, close, etc.)
#include <string.h> // Para manipulação de strings (strlen, strcpy, strcmp, etc.)
#include <fcntl.h> // Para controle de arquivos (open, O_RDONLY, O_WRONLY, etc.)

// Define o número de threads no pool de threads, nome do pipe para solicitações de números e stringes, e o tamanho do buffer para leitura e escrita
#define NUM_THREADS 2 
#define PIPE_NUMBERS "pipe_numbers" 
#define PIPE_STRINGS "pipe_strings"
#define BUFFER_SIZE 256

// Função para atender pedidos de números
void* handle_numbers(void* arg) {
    int fd;
    char buffer[BUFFER_SIZE]; // Buffer para armazenar a resposta do servidor
    int number = 42;  // Exemplo de número para responder

    // Cria o pipe para números
    mkfifo(PIPE_NUMBERS, 0666);

    while (1) {
        fd = open(PIPE_NUMBERS, O_WRONLY); // Abre o pipe para escrita
        if (fd < 0) { // Verifica se ocorreu algum erro
            perror("Erro ao abrir pipe de números");
            continue;
        }
        sprintf(buffer, "Número: %d", number); // Converte o número para uma string
        write(fd, buffer, strlen(buffer) + 1); // Escreve a string no pipe
        close(fd); // Fecha o pipe
        sleep(2); // Simula tempo de processamento
    }

    return NULL;
}

// Função para atender pedidos de strings
void* handle_strings(void* arg) {
    int fd;
    char buffer[BUFFER_SIZE];
    char* response = "Olá, usuário!"; // Exemplo de resposta que será enviada pelo servidor

    // Cria o pipe para strings
    mkfifo(PIPE_STRINGS, 0666);

    while (1) {
        fd = open(PIPE_STRINGS, O_WRONLY); 
        if (fd < 0) {
            perror("Erro ao abrir pipe de strings");
            continue;
        }
        sprintf(buffer, "Mensagem: %s", response);
        write(fd, buffer, strlen(buffer) + 1);
        close(fd);
        sleep(2); // Simula tempo de processamento
    }

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS]; // Array para armazenar os identificadores das threads

    // Cria threads
    pthread_create(&threads[0], NULL, handle_numbers, NULL);
    pthread_create(&threads[1], NULL, handle_strings, NULL);

    // Loop infinito para manter o programa em execução
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
