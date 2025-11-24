#include <stdio.h>
#include <string.h>
#include "algoritmos.h"

// --- Funções Auxiliares ---

// Troca a posição de dois ponteiros de usuário dentro do vetor
static void trocar(Usuario* vetor[], int i, int j) {
    Usuario* temp = vetor[i];
    vetor[i] = vetor[j];
    vetor[j] = temp;
}

// Reorganiza o vetor com base em um 'pivô'.
// Elementos menores que o pivô (em ordem alfabética) são movidos para sua esquerda, e os maiores para sua direita.
// Retorna o índice final onde o pivô foi posicionado.
static int particionar(Usuario* vetor[], int baixo, int alto) {
    Usuario* pivo = vetor[alto];
    int i = (baixo - 1);

    for (int j = baixo; j <= alto - 1; j++) {
        if (strcmp(vetor[j]->nome, pivo->nome) <= 0) {
            i++;
            trocar(vetor, i, j);
        }
    }
    trocar(vetor, i + 1, alto);
    return (i + 1);
}

// A função recursiva que aplica o Quick Sort.
static void quick_sort_recursivo(Usuario* vetor[], int baixo, int alto) {
    if (baixo < alto) {
        int pi = particionar(vetor, baixo, alto);
        // Chama a função recursivamente para as duas sub-partições:
        // 1. A partição à esquerda do pivô.
        quick_sort_recursivo(vetor, baixo, pi - 1);
        // 2. A partição à direita do pivô.
        quick_sort_recursivo(vetor, pi + 1, alto);
    }
}

// --- Função  ---

// Função de ordenação.
void quick_sort(Usuario* vetor[], int n) {
    quick_sort_recursivo(vetor, 0, n - 1);
}
