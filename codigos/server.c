#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> 
#include <string.h>
#include <fcntl.h>

#define NUM_THREADS 2 
#define PIPE_NUMBERS "pipe_numbers" 
#define PIPE_STRINGS "pipe_strings"
#define BUFFER_SIZE 256

void* handle_numbers(void* arg) {
    int fd;
    char buffer[BUFFER_SIZE]; 
    int number = 42; 

    mkfifo(PIPE_NUMBERS, 0666);

    while (1) {
        fd = open(PIPE_NUMBERS, O_WRONLY);
        if (fd < 0) { 
            perror("Erro ao abrir pipe de números");
            continue;
        }
        sprintf(buffer, "Número: %d", number);
        write(fd, buffer, strlen(buffer) + 1);
        close(fd); // Fecha o pipe
        sleep(2);
    }

    return NULL;
}

void* handle_strings(void* arg) {
    int fd;
    char buffer[BUFFER_SIZE];
    char* response = "Olá, usuário!"; 

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
    pthread_t threads[NUM_THREADS];

    pthread_create(&threads[0], NULL, handle_numbers, NULL);
    pthread_create(&threads[1], NULL, handle_strings, NULL);

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
