#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "usuario.h"
#include "arvore_binaria.h"
#include "tabela_hash.h"
#include "grafo.h"
#include "algoritmos.h"

// --- Funções Auxiliares do Main ---
void exibir_menu();
int ler_inteiro(const char* prompt);
void limpar_buffer_entrada();


int main()
{
    // --- Estruturas de Dados ---
    No* arvore_por_nome = NULL;                         // Árvore para busca por nome
    TabelaHash* tabela_por_id = criar_tabela_hash();    // Tabela Hash para busca por ID
    TabelaHash* tabela_por_email = criar_tabela_hash(); // Tabela Hash para busca por Email
    Grafo* grafo_de_conexoes = criar_grafo();           // Grafo para modelar as conexões

    // Variáveis de controle e temporárias.
    int opcao, contador_usuarios = 0;
    int id_temp, id_origem, id_destino;
    char nome_temp[100], email_temp[100];
    Usuario* usuario_temp;
    Usuario** vetor_usuarios = NULL;

    // --- Loop conectado ao menu ---
    do
    {
        exibir_menu();
        opcao = ler_inteiro("Escolha uma opcao: ");

        switch (opcao)
        {
        case 1: // Inserir novo usuário
            printf("\n===== Inserir Novo Usuario =====\n");
            id_temp = ler_inteiro("Digite o ID: ");

            // Verifica se o ID já existe usando a tabela hash
            if (buscar_na_tabela_por_id(tabela_por_id, id_temp) != NULL)
            {
                printf("\nAVISO: Ja existe um usuario cadastrado com o ID %d.\n", id_temp);
                printf("Por favor insira o novo usuario com ID diferente.\n");
            }
            else
            {
                printf("Digite o Nome: ");
                fgets(nome_temp, 100, stdin);
                nome_temp[strcspn(nome_temp, "\n")] = 0;
                printf("Digite o Email: ");
                fgets(email_temp, 100, stdin);
                email_temp[strcspn(email_temp, "\n")] = 0;

                // Cria e insere o usuário em TODAS as estruturas de dados.
                usuario_temp = criar_usuario(id_temp, nome_temp, email_temp);
                arvore_por_nome = inserir_na_arvore(arvore_por_nome, usuario_temp);
                inserir_na_tabela_por_id(tabela_por_id, usuario_temp);
                inserir_na_tabela_por_string(tabela_por_email, usuario_temp->email, usuario_temp);
                adicionar_vertice(grafo_de_conexoes, usuario_temp);
                contador_usuarios++;
                printf("Usuario inserido com sucesso!\n");
            }
            break;

        case 2: // Listar usuários (usando a Árvore Binária)
            printf("\n===== Listar Usuarios (utilizando Arvore Binaria) =====\n");
            if (arvore_por_nome == NULL)
            {
                printf("Nenhum usuario cadastrado.\n");
            }
            else
            {
                // Organizar a lista em ordem alfabética
                imprimir_arvore_em_ordem(arvore_por_nome);
            }
            break;

        case 3: // Buscar usuário por ID
            printf("\n===== Buscar Usuario por ID =====\n");
            id_temp = ler_inteiro("Digite o ID a ser buscado: ");
            usuario_temp = buscar_na_tabela_por_id(tabela_por_id, id_temp);
            if (usuario_temp != NULL)
            {
                printf("\nUsuario encontrado:\n");
                exibir_usuario(usuario_temp);
            }
            else
            {
                printf("\nUsuario com ID %d nao encontrado.\n", id_temp);
            }
            break;

        case 4: // Buscar usuário por Nome
            printf("\n===== Buscar Usuario por Nome =====\n");
            printf("Digite o Nome a ser buscado: ");
            fgets(nome_temp, 100, stdin);
            nome_temp[strcspn(nome_temp, "\n")] = 0;
            usuario_temp = buscar_na_arvore(arvore_por_nome, nome_temp);
            if (usuario_temp != NULL)
            {
                printf("\nUsuario encontrado:\n");
                exibir_usuario(usuario_temp);
            }
            else
            {
                printf("\nUsuario com nome '%s' nao encontrado.\n", nome_temp);
            }
            break;

        case 5: // Buscar usuário por Email
            printf("\n===== Buscar Usuario por Email =====\n");
            printf("Digite o Email a ser buscado: ");
            fgets(email_temp, 100, stdin);
            email_temp[strcspn(email_temp, "\n")] = 0;
            usuario_temp = buscar_na_tabela_por_string(tabela_por_email, email_temp);
            if (usuario_temp != NULL)
            {
                printf("\nUsuario encontrado:\n");
                exibir_usuario(usuario_temp);
            }
            else
            {
                printf("\nUsuario com email '%s' nao encontrado.\n", email_temp);
            }
            break;

            case 6: // Adicionar conexão
                printf("\n===== Adicionar Conexao entre Usuarios =====\n");
                id_origem = ler_inteiro("Digite o ID do usuario de ORIGEM: ");
                id_destino = ler_inteiro("Digite o ID do usuario de DESTINO: ");

                Usuario* usuario_origem = buscar_na_tabela_por_id(tabela_por_id, id_origem);
                Usuario* usuario_destino = buscar_na_tabela_por_id(tabela_por_id, id_destino);

                if (usuario_origem == NULL || usuario_destino == NULL) {
                    printf("\nAVISO: Nao foi possivel criar a conexao.\n");
                    if (usuario_origem == NULL) printf("O Usuario com ID %d nao existe no sistema.\n", id_origem);
                    if (usuario_destino == NULL) printf("O Usuario com ID %d nao existe no sistema.\n", id_destino);
                }
                else if (aresta_existe(grafo_de_conexoes, id_origem, id_destino)) {
                    printf("\nAVISO: A conexao do usuario %d para o usuario %d ja existe no sistema.\n", id_origem, id_destino);
                }
                else {
                    adicionar_aresta(grafo_de_conexoes, id_origem, id_destino);
                    printf("Conexao de '%s' para '%s' criada com sucesso.\n", usuario_origem->nome, usuario_destino->nome);
                }
                break;


        case 7: // Mostrar conexões de um usuário
            printf("\n===== Mostrar Conexoes de um Usuario =====\n");
            id_temp = ler_inteiro("Digite o ID do usuario para ver suas conexoes: ");
            mostrar_conexoes(grafo_de_conexoes, id_temp);
            break;

        case 8: // Listar usuários (usando Quick Sort)
            printf("\n===== Listar Usuarios (ordenado por Quick Sort) =====\n");
            if (contador_usuarios == 0)
            {
                printf("Nenhum usuario para ordenar.\n");
            }
            else
            {
                vetor_usuarios = (Usuario**) malloc(contador_usuarios * sizeof(Usuario*));
                if (vetor_usuarios != NULL)
                {
                    int i = 0;
                    for (int j = 0; j < TAMANHO_TABELA; j++)
                    {
                        NoLista* atual = tabela_por_id->tabela[j];
                        while (atual != NULL)
                        {
                            if (i < contador_usuarios) vetor_usuarios[i++] = atual->usuario;
                            atual = atual->proximo;
                        }
                    }
                    // Aplica o Quick Sort e exibe o resultado
                    quick_sort(vetor_usuarios, contador_usuarios);
                    for (i = 0; i < contador_usuarios; i++) exibir_usuario(vetor_usuarios[i]);

                    // Libera a memória do vetor temporário
                    free(vetor_usuarios);
                    vetor_usuarios = NULL;
                }
            }
            break;

        case 9: // Remover usuário
            printf("\n===== Remover Usuario =====\n");
            if (contador_usuarios == 0)
            {
                printf("Nenhum usuario para remover.\n");
            }
            else
            {
                id_temp = ler_inteiro("Digite o ID do usuario a ser removido: ");
                usuario_temp = remover_da_tabela_por_id(tabela_por_id, id_temp);

                if (usuario_temp != NULL)
                {
                    // remove o usurario de todas as outras estruturas
                    remover_do_grafo(grafo_de_conexoes, usuario_temp->id);
                    arvore_por_nome = remover_da_arvore(arvore_por_nome, usuario_temp->nome);
                    remover_da_tabela_por_string(tabela_por_email, usuario_temp->email);

                    printf("\nUsuario '%s' de ID: %d removido do sistema com sucesso.\n", usuario_temp->nome, usuario_temp->id);

                    // Libera a memória do usuário em si, que foi retornado pela função de remoção
                    destruir_usuario(usuario_temp);
                    contador_usuarios--;
                }
                else
                {
                    printf("\nUsuario com ID %d nao encontrado.\n", id_temp);
                }
            }
            break;

        case 0: // Sair
            printf("\nSaindo do programa...\n");
            break;

        default:
            printf("\nOpcao invalida! Tente novamente.\n");
            break;
        }

        // Pausa para o usuário ler a saída antes de mostrar o menu novamente
        if (opcao != 0)
        {
            printf("\nPressione Enter para continuar...");
            limpar_buffer_entrada();
        }

    }
    while (opcao != 0);

    // --- Liberação de Memória ---
    printf("Liberando toda a memoria...\n");
    liberar_grafo(grafo_de_conexoes);
    liberar_arvore(arvore_por_nome);
    liberar_tabela_hash_sem_dados(tabela_por_email); // Libera sem destruir os usuários.
    liberar_tabela_hash(tabela_por_id);              // Libera e destroi os usuários.
    printf("Memoria liberada com sucesso.\n");
    printf("Programa finalizado.\n");

    return 0;
}


// --- Funções Auxiliares ---

// Imprime o menu principal de opções.
void exibir_menu()
{
    printf("\n\n===== Framework de Gerenciamento de Usuarios =====\n");
    printf("1. Inserir novo usuario\n");
    printf("2. Listar usuarios (por Arvore Binaria)\n");
    printf("3. Buscar usuario por ID\n");
    printf("4. Buscar usuario por Nome\n");
    printf("5. Buscar usuario por Email\n");
    printf("6. Adicionar conexao\n");
    printf("7. Mostrar conexoes de um usuario\n");
    printf("8. Listar usuarios (por Quick Sort)\n");
    printf("9. Remover usuario\n");
    printf("0. Sair\n");
    printf("==================================================\n");
}

// Lê um número inteiro do usuário de forma segura, tratando entradas inválidas.
int ler_inteiro(const char* prompt)
{
    char buffer[100];
    long valor;
    char* endptr;
    while (1)
    {
        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin) != NULL)
        {
            valor = strtol(buffer, &endptr, 10);
            if (buffer[0] != '\n' && (*endptr == '\n' || *endptr == '\0'))
            {
                return (int)valor;
            }
        }
        printf("Entrada invalida. Por favor, digite apenas numeros.\n");
    }
}
void limpar_buffer_entrada()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
