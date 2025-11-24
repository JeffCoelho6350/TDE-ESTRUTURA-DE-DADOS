#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabela_hash.h"

// --- Funções ---
static unsigned long hash_string(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

// Aloca e inicializa uma nova Tabela Hash
TabelaHash* criar_tabela_hash() {
    TabelaHash* th = (TabelaHash*) malloc(sizeof(TabelaHash));
    th->tabela = (NoLista**) calloc(TAMANHO_TABELA, sizeof(NoLista*));
    return th;
}

// --- Funções Específicas para Chave ID ---

// Insere um usuário na tabela usando seu ID
void inserir_na_tabela_por_id(TabelaHash* th, Usuario* usuario) {
    char chave_str[20];
    sprintf(chave_str, "%d", usuario->id);
    inserir_na_tabela_por_string(th, chave_str, usuario);
}

// Busca um usuário na tabela pelo seu ID
Usuario* buscar_na_tabela_por_id(TabelaHash* th, int id) {
    char chave_str[20];
    sprintf(chave_str, "%d", id);
    return buscar_na_tabela_por_string(th, chave_str);
}

// Remove um usuário da tabela pelo seu ID
Usuario* remover_da_tabela_por_id(TabelaHash* th, int id) {
    char chave_str[20];
    sprintf(chave_str, "%d", id);
    return remover_da_tabela_por_string(th, chave_str);
}

// --- Funções Genéricas para Chave String (usadas por ID e Email) ---

// Insere um novo nó no início da lista ligada no índice correspondente
void inserir_na_tabela_por_string(TabelaHash* th, const char* chave, Usuario* usuario) {
    unsigned long indice = hash_string(chave) % TAMANHO_TABELA;
    NoLista* novo_no = (NoLista*) malloc(sizeof(NoLista));
    novo_no->chave = strdup(chave);
    novo_no->usuario = usuario;
    novo_no->proximo = th->tabela[indice];
    th->tabela[indice] = novo_no;
}

// Busca um usuário percorrendo a lista ligada no índice correspondente
Usuario* buscar_na_tabela_por_string(TabelaHash* th, const char* chave) {
    unsigned long indice = hash_string(chave) % TAMANHO_TABELA;
    NoLista* atual = th->tabela[indice];
    while (atual != NULL) {
        if (strcmp(atual->chave, chave) == 0) {
            return atual->usuario;
        }
        atual = atual->proximo;
    }
    return NULL;
}

// Remove um usuário da lista ligada no índice correspondente
Usuario* remover_da_tabela_por_string(TabelaHash* th, const char* chave) {
    unsigned long indice = hash_string(chave) % TAMANHO_TABELA;
    NoLista* atual = th->tabela[indice];
    NoLista* anterior = NULL;

    while (atual != NULL && strcmp(atual->chave, chave) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) return NULL;

    if (anterior == NULL) {
        th->tabela[indice] = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    Usuario* usuario_removido = atual->usuario;
    free(atual->chave);                             // Libera a memória da string da chave
    free(atual);                                    // Libera a memória do nó da lista
    return usuario_removido;                        // Retorna o usuário para que possa ser liberado externamente
}

// --- Funções de Liberação de Memória ---

// Libera a tabela hash e todos os usuários relacionados
void liberar_tabela_hash(TabelaHash* th) {
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        NoLista* atual = th->tabela[i];
        while (atual != NULL) {
            NoLista* temp = atual;
            atual = atual->proximo;
            free(temp->chave);
            destruir_usuario(temp->usuario);
            free(temp);
        }
    }
    free(th->tabela);
    free(th);
}

// Libera apenas a estrutura da tabela, sem tocar nos dados dos usuários
void liberar_tabela_hash_sem_dados(TabelaHash* th) {
    for (int i = 0; i < TAMANHO_TABELA; i++) {
        NoLista* atual = th->tabela[i];
        while (atual != NULL) {
            NoLista* temp = atual;
            atual = atual->proximo;
            free(temp->chave);
            free(temp);
        }
    }
    free(th->tabela);
    free(th);
}
