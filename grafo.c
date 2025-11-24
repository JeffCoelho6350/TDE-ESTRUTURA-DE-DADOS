/**
 * grafo.c
 *
 * Implementa as funções para manipular a estrutura de Grafo.
 * A lógica inclui encontrar vértices, adicionar/remover vértices (usuários)
 * e arestas (conexões), e exibir as relações entre eles.
 */

#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

// --- Funções Auxiliares (privadas ao módulo) ---

// Busca um vértice no grafo pelo ID do usuário e retorna um ponteiro para ele.
// Retorna NULL se o vértice não for encontrado.
static Vertice* buscar_vertice(Grafo* g, int id_usuario) {
    for (int i = 0; i < g->num_vertices; i++) {
        if (g->vertices[i] != NULL && g->vertices[i]->usuario->id == id_usuario) {
            return g->vertices[i];
        }
    }
    return NULL;
}


// --- Implementação das Funções Públicas ---

// Aloca e inicializa um novo grafo vazio.
Grafo* criar_grafo() {
    Grafo* g = (Grafo*) malloc(sizeof(Grafo));
    g->num_vertices = 0;
    // Inicializa todos os ponteiros de vértices como NULL.
    for (int i = 0; i < MAX_VERTICES; i++) {
        g->vertices[i] = NULL;
    }
    return g;
}

// Adiciona um novo vértice (usuário) ao vetor de vértices do grafo.
void adicionar_vertice(Grafo* g, Usuario* u) {
    if (g->num_vertices < MAX_VERTICES) {
        Vertice* v = (Vertice*) malloc(sizeof(Vertice));
        v->usuario = u;
        v->lista_adj = NULL;
        g->vertices[g->num_vertices++] = v;
    }
}

// Verifica se já existe uma conexão (aresta) de um usuário para outro.
int aresta_existe(Grafo* g, int id_origem, int id_destino) {
    Vertice* v_origem = buscar_vertice(g, id_origem);
    if (v_origem == NULL) return 0; // Origem não encontrada.

    // Percorre a lista de adjacências do vértice de origem.
    NoAresta* atual = v_origem->lista_adj;
    while (atual != NULL) {
        if (atual->destino->usuario->id == id_destino) {
            return 1; // Aresta encontrada.
        }
        atual = atual->proximo;
    }
    return 0; // Aresta não encontrada.
}

// Adiciona uma nova conexão (aresta) entre dois vértices.
int adicionar_aresta(Grafo* g, int id_origem, int id_destino) {
    // Primeiro, verifica se a aresta já existe para evitar duplicatas.
    if (aresta_existe(g, id_origem, id_destino)) {
        return 0; // Retorna 0 para indicar que a aresta não foi criada.
    }

    Vertice* v_origem = buscar_vertice(g, id_origem);
    Vertice* v_destino = buscar_vertice(g, id_destino);

    // Se ambos os vértices existem, cria a aresta.
    if (v_origem != NULL && v_destino != NULL) {
        NoAresta* nova_aresta = (NoAresta*) malloc(sizeof(NoAresta));
        nova_aresta->destino = v_destino;
        nova_aresta->proximo = v_origem->lista_adj; // Insere no início da lista.
        v_origem->lista_adj = nova_aresta;
        return 1; // Retorna 1 para indicar sucesso.
    }
    return 0; // Retorna 0 se um dos vértices não foi encontrado.
}

// Imprime no console todas as conexões de um usuário.
void mostrar_conexoes(Grafo* g, int id_usuario) {
    Vertice* v = buscar_vertice(g, id_usuario);

    if (v == NULL) {
        printf("\nUsuario com ID %d nao encontrado no grafo.\n", id_usuario);
        return;
    }

    printf("\nConexoes do usuario '%s' (ID: %d):\n", v->usuario->nome, id_usuario);
    NoAresta* atual = v->lista_adj;
    if (atual == NULL) {
        printf(" -> Nenhuma conexao encontrada.\n");
    } else {
        while (atual != NULL) {
            printf(" -> Conectado a: '%s' (ID: %d)\n", atual->destino->usuario->nome, atual->destino->usuario->id);
            atual = atual->proximo;
        }
    }
}

// Remove um vértice e todas as arestas relacionadas a ele.
void remover_do_grafo(Grafo* g, int id_usuario) {
    // Passo 1: Remover todas as arestas de ENTRADA para o usuário a ser removido.
    for (int i = 0; i < g->num_vertices; i++) {
        if (g->vertices[i] != NULL) {
            NoAresta* atual = g->vertices[i]->lista_adj;
            NoAresta* anterior = NULL;
            while (atual != NULL) {
                if (atual->destino->usuario->id == id_usuario) {
                    NoAresta* temp = atual;
                    if (anterior == NULL) g->vertices[i]->lista_adj = atual->proximo;
                    else anterior->proximo = atual->proximo;
                    atual = atual->proximo;
                    free(temp);
                } else {
                    anterior = atual;
                    atual = atual->proximo;
                }
            }
        }
    }

    // Passo 2: Encontrar, remover as arestas de SAÍDA e remover o VÉRTICE.
    int indice_removido = -1;
    for (int i = 0; i < g->num_vertices; i++) {
        if (g->vertices[i] != NULL && g->vertices[i]->usuario->id == id_usuario) {
            indice_removido = i;
            // Libera a lista de adjacências (arestas de saída).
            NoAresta* atual = g->vertices[i]->lista_adj;
            while (atual != NULL) {
                NoAresta* temp = atual;
                atual = atual->proximo;
                free(temp);
            }
            free(g->vertices[i]); // Libera o vértice.
            g->vertices[i] = NULL;
            break;
        }
    }

    // Passo 3: Compactar o array de vértices para remover o espaço vazio.
    if (indice_removido != -1) {
        for (int i = indice_removido; i < g->num_vertices - 1; i++) {
            g->vertices[i] = g->vertices[i + 1];
        }
        g->vertices[g->num_vertices - 1] = NULL;
        g->num_vertices--;
    }
}

// Libera toda a memória alocada para o grafo.
void liberar_grafo(Grafo* g) {
    for (int i = 0; i < g->num_vertices; i++) {
        if (g->vertices[i] != NULL) {
            // Libera a lista de adjacências de cada vértice.
            NoAresta* atual = g->vertices[i]->lista_adj;
            while (atual != NULL) {
                NoAresta* temp = atual;
                atual = atual->proximo;
                free(temp);
            }
            free(g->vertices[i]); // Libera o vértice.
        }
    }
    free(g->vertices); // Libera o array de ponteiros para vértices.
    free(g);         // Libera a estrutura do grafo.
}
