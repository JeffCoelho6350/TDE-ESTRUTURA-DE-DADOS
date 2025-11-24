#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usuario.h"

// Implementação da função que cria o usuário
Usuario* criar_usuario(int id, const char* nome, const char* email) {
    Usuario* novo_usuario = (Usuario*) malloc(sizeof(Usuario));

    if (novo_usuario == NULL) {
        printf("ERRO: Falha ao alocar memoria para novo usuario!\n");
        return NULL;
    }

    // Preenche os campos da estrutura recém-alocada
    novo_usuario->id = id;
    strcpy(novo_usuario->nome, nome);
    strcpy(novo_usuario->email, email);

    return novo_usuario;
}

// Implementação da função que exibe os dados do usuário
void exibir_usuario(Usuario* u) {
    if (u != NULL) {
        printf("ID: %d, Nome: %s, Email: %s\n", u->id, u->nome, u->email);
    }
}

// Implementação da função que libera a memória do usuário
void destruir_usuario(Usuario* u) {
    free(u);
}
