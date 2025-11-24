#ifndef USUARIO_H_INCLUDED
#define USUARIO_H_INCLUDED

typedef struct {
    int id;
    char nome[100];
    char email[100];
} Usuario;

Usuario* criar_usuario(int id, const char* nome, const char* email);

void exibir_usuario(Usuario* u);

void destruir_usuario(Usuario* u);


#endif // USUARIO_H_INCLUDED
