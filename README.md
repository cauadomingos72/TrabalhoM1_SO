# Servidor Local com Pool de Threads e Comunicação via Pipes

## Descrição do Problema

Este projeto implementa um servidor local utilizando um **pool de threads** e **pipes nomeados** para comunicação entre processos. O servidor é capaz de atender a dois tipos de solicitações:

1. **Solicitações de Números**: Clientes podem se conectar a um pipe específico para receber uma resposta numérica.
2. **Solicitações de Strings**: Clientes podem se conectar a outro pipe específico para receber uma resposta textual.

O servidor utiliza um pool de threads para lidar com as solicitações de forma concorrente, permitindo que múltiplos clientes sejam atendidos simultaneamente. A comunicação entre o servidor e os clientes é feita via **pipes nomeados** (FIFOs), que permitem a troca de dados entre processos diferentes.

## Ambiente de Desenvolvimento

Este projeto foi implementado em **C** e foi desenvolvido e testado em um ambiente **Linux**, que oferece suporte nativo para chamadas de sistema POSIX, como manipulação de threads (`pthread`) e criação de pipes nomeados.

## Compilação

Para compilar o servidor e o cliente, siga os passos abaixo:

### Compilar o servidor
Use o seguinte comando para compilar o servidor, que será responsável por criar as threads e responder às solicitações dos clientes:

```bash
gcc -g server.c -o server -lpthread
gcc -g client.c -o client
