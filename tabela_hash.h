#ifndef TABELA_HASH_H_INCLUDED
#define TABELA_HASH_H_INCLUDED

#include "usuario.h"
#define TAMANHO_TABELA 101

// --- Estruturas de Dados ---

// Define a estrutura de um Nó da lista ligada usada para o encadeamento
typedef struct NoLista {
    char* chave;                 // A chave ID ou email em formato string que gerou o índice
    Usuario* usuario;            // Ponteiro para os dados do usuário
    struct NoLista* proximo;     // Ponteiro para o próximo nó na lista de colisão
} NoLista;

// Define a estrutura principal da Tabela Hash.
typedef struct {
    NoLista** tabela;
} TabelaHash;


// --- Funções Públicas ---

TabelaHash* criar_tabela_hash();
void inserir_na_tabela_por_id(TabelaHash* th, Usuario* usuario);                        // Insere um usuário na tabela usando o ID como chave.
void inserir_na_tabela_por_string(TabelaHash* th, const char* chave, Usuario* usuario); // Insere um usuário na tabela usando uma string como chave
Usuario* buscar_na_tabela_por_id(TabelaHash* th, int id);                               // Busca um usuário na tabela pelo ID
Usuario* buscar_na_tabela_por_string(TabelaHash* th, const char* chave);                // Busca um usuário na tabela por uma chave string, por exemplo email
Usuario* remover_da_tabela_por_id(TabelaHash* th, int id);                              // Remove um usuário da tabela pelo ID
Usuario* remover_da_tabela_por_string(TabelaHash* th, const char* chave);               // Remove um usuário da tabela pela chave string
void liberar_tabela_hash(TabelaHash* th);                                               // Libera TODA a memória
void liberar_tabela_hash_sem_dados(TabelaHash* th);                                     // Libera apenas a estrutura da tabela (nós e chaves), mas não os dados dos usuários.


#endif // TABELA_HASH_H_INCLUDED
