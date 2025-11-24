#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

#include "usuario.h"
#define MAX_VERTICES 100

// --- Estruturas de Dados ---
struct Vertice;

// Define a estrutura de um Nó de Aresta, que representa uma conexão
typedef struct NoAresta {
    struct Vertice* destino;   // Ponteiro para o vértice de destino da conexão
    struct NoAresta* proximo;  // Ponteiro para a próxima conexão na lista de adjacências
} NoAresta;

// Define a estrutura de um 'Vértice', que representa um usuário no grafo
typedef struct Vertice {
    Usuario* usuario;          // Ponteiro para os dados do usuário
    NoAresta* lista_adj;       // Ponteiro para o início da lista de suas conexões
} Vertice;

// Define a estrutura principal do Grafo.
typedef struct {
    Vertice* vertices[MAX_VERTICES]; // Um vetor de ponteiros para todos os vértices
    int num_vertices;                // Contador do número atual de vértices no grafo
} Grafo;


// --- Funções ---

// Aloca memória e inicializa um novo grafo vazio
Grafo* criar_grafo();

// Adiciona um novo vértice ao grafo
void adicionar_vertice(Grafo* g, Usuario* u);

// Adiciona uma aresta direcionada de um usuário de origem para um de destino
int adicionar_aresta(Grafo* g, int id_origem, int id_destino);

// Verifica se uma aresta entre dois usuários já existe
int aresta_existe(Grafo* g, int id_origem, int id_destino);

// Imprime no console todas as conexões de um determinado usuário
void mostrar_conexoes(Grafo* g, int id_usuario);

// Remove um vértice do grafo e todas as arestas associadas a ele
void remover_do_grafo(Grafo* g, int id_usuario);

// Libera toda a memória alocada para a estrutura do grafo
void liberar_grafo(Grafo* g);


#endif // GRAFO_H_INCLUDED
