#ifndef ARVORE_BINARIA_H_INCLUDED
#define ARVORE_BINARIA_H_INCLUDED

#include "usuario.h"

// --- Estruturas de Dados ---

// Define a estrutura de um 'Nó' da árvore
typedef struct No {
    Usuario* usuario;       // Ponteiro para os dados do usuário
    struct No* esquerda;    // Ponteiro para o filho à esquerda (nomes menores)
    struct No* direita;     // Ponteiro para o filho à direita (nomes maiores)
} No;

// --- Funções ---

// Insere um novo usuário na árvore, mantendo a ordem pelo nome
No* inserir_na_arvore(No* raiz, Usuario* usuario);

// Busca um usuário na árvore pelo nome e retorna um ponteiro para o usuário se encontrado
Usuario* buscar_na_arvore(No* raiz, const char* nome);

// Remove um usuário da árvore, mantendo a estrutura da árvore
No* remover_da_arvore(No* raiz, const char* nome);

// Imprime os usuários da árvore em ordem alfabética
void imprimir_arvore_em_ordem(No* raiz);

// Libera toda a memória alocada para os nós da árvore
void liberar_arvore(No* raiz);


#endif
