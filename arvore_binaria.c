#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore_binaria.h"

// --- Funções Auxiliares ---

// Cria um novo nó da árvore, alocando memória e inicializando seus campos
static No* criar_no(Usuario* usuario) {
    No* novo_no = (No*) malloc(sizeof(No));
    if (novo_no == NULL) {
        printf("ERRO: Falha ao alocar memoria para no da arvore!\n");
        return NULL;
    }
    novo_no->usuario = usuario; // O nó aponta para o usuário já existente
    novo_no->esquerda = NULL;
    novo_no->direita = NULL;
    return novo_no;
}

// Reoganizar o nó com o menor valor a direita e o maior à esquerda
// Usado na lógica de remoção de um nó com dois filhos
static No* encontrar_minimo(No* no) {
    No* atual = no;
    while (atual && atual->esquerda != NULL) {
        atual = atual->esquerda;
    }
    return atual;
}


// --- Funções ---

// Insere um novo usuário na árvore de forma recursiva
No* inserir_na_arvore(No* raiz, Usuario* usuario) {
    if (raiz == NULL) {
        return criar_no(usuario);
    }
    // Compara o nome do novo usuário com o do nó atual para decidir o caminho
    int comparacao = strcmp(usuario->nome, raiz->usuario->nome);

    if (comparacao < 0) {
        // Se o novo nome é menor, insere na sub-árvore esquerda
        raiz->esquerda = inserir_na_arvore(raiz->esquerda, usuario);
    } else if (comparacao > 0) {
        // Se o novo nome é maior, insere na sub-árvore direita
        raiz->direita = inserir_na_arvore(raiz->direita, usuario);
    } else {
        // Se os nomes são iguais, não insere para evitar duplicatas
        printf("AVISO: Usuario com nome '%s' ja existe na arvore.\n", usuario->nome);
    }

    return raiz;
}

// Busca um usuário na árvore pelo nome de forma recursiva
Usuario* buscar_na_arvore(No* raiz, const char* nome) {
    // Caso quando a raiz é nula, o usuário não foi encontrado
    if (raiz == NULL) {
        return NULL;
    }

    int comparacao = strcmp(nome, raiz->usuario->nome);

    if (comparacao == 0) {
        // Caso encontrou o usuário
        return raiz->usuario;
    } else if (comparacao < 0) {
        // O nome buscado é menor, continua a busca na sub-árvore esquerda
        return buscar_na_arvore(raiz->esquerda, nome);
    } else {
        // O nome buscado é maior, continua a busca na sub-árvore direita
        return buscar_na_arvore(raiz->direita, nome);
    }
}

// Remove um nó da árvore buscando pelo nome do usuário
No* remover_da_arvore(No* raiz, const char* nome) {
    if (raiz == NULL) return raiz; // Caso a árvore vazia

    int comparacao = strcmp(nome, raiz->usuario->nome);

    if (comparacao < 0) {
        raiz->esquerda = remover_da_arvore(raiz->esquerda, nome);
    } else if (comparacao > 0) {
        raiz->direita = remover_da_arvore(raiz->direita, nome);
    } else {
        if (raiz->esquerda == NULL) {
            No* temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            No* temp = raiz->esquerda;
            free(raiz);
            return temp;
        }
        No* temp = encontrar_minimo(raiz->direita);

        raiz->usuario = temp->usuario;

        raiz->direita = remover_da_arvore(raiz->direita, temp->usuario->nome);
    }
    return raiz;
}

// Imprime os usuários da árvore em ordem alfabética
void imprimir_arvore_em_ordem(No* raiz) {
    if (raiz != NULL) {
        imprimir_arvore_em_ordem(raiz->esquerda); // 1. Procura a esquerda
        exibir_usuario(raiz->usuario);             // 2. Procura a raiz
        imprimir_arvore_em_ordem(raiz->direita);  // 3. Procura a direita
    }
}

void liberar_arvore(No* raiz) {
    if (raiz != NULL) {
        liberar_arvore(raiz->esquerda);   // 1. Libera a esquerda
        liberar_arvore(raiz->direita);    // 2. Libera a direita
        free(raiz);                       // 3. Libera o nó atual
    }
}
