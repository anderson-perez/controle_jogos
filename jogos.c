#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define T_STR 100

typedef char string[T_STR];

typedef struct dados_jogo {
    string nome;
    int ano_lanc;
    string genero;
    string produtora;
    float valor;
} jogo_t;

typedef struct no {
    jogo_t dados_jogo;
    struct no *prox;
} no_t;

// Protótipos das funções
int menu();
jogo_t novo_jogo();
no_t *novo_no(jogo_t jogo);
void inserir_jogo_lista_inicio(no_t *no, no_t **lista);
void inserir_jogo_lista_fim(no_t *no, no_t **lista);
no_t *localizar_ultimo_no_na_lista(no_t *lista);
no_t *localizar_jogo_por_nome(string nome, no_t *lista);
void mostrar_dados_jogo(jogo_t dados_jogo);
void excluir_no_lista(no_t *no, no_t **lista);
void retirar_enter(string str);
void formatar_maiuscula(string str);
void listar_jogos_cadastrados(no_t *lista);
int sub_menu_cadastro();

int main()
{
    int opc_principal, opc_sub;
    no_t *lista = NULL;

    do {
        opc_principal = menu();

        switch (opc_principal) {

            case 1: do {
                        opc_sub = sub_menu_cadastro();

                        if (opc_sub == 1) {
                            /*
                            jogo_t novo = novo_jogo();
                            no_t *no_novo = novo_no(novo);
                            inserir_jogo_lista_inicio(no_novo, &lista);
                            */

                            inserir_jogo_lista_inicio(novo_no(novo_jogo()), &lista);
                        }
                        else if (opc_sub == 2) {
                            inserir_jogo_lista_fim(novo_no(novo_jogo()), &lista);
                        }
                        else if (opc_sub == 3)  {

                        }

                    } while (opc_sub != 0);
                    break;

            case 2: listar_jogos_cadastrados(lista);
                    break;
            case 3: break;
            case 4: break;

        }

    } while (opc_principal != 0);

    return 0;
}

// Implementação das funções
int menu()
{
    int opcao;

    printf("| CADASTRO DE JOGOS |\n");
    printf("---------------------\n");
    printf("1.Cadastrar novo jogo\n");
    printf("2.Listar jogos cadastrados\n");
    printf("3.Encontrar um jogo por nome\n");
    printf("4.Excluir jogo da lista\n");
    printf("0.Sair do programa\n");
    printf("---------------------\n");
    printf("::: ");
    scanf("%i", &opcao);
    getchar();

    return opcao;
}

int sub_menu_cadastro()
{
    int opcao;

    printf("| INSERÇÃO NA LISTA |\n");
    printf("---------------------\n");
    printf("1.Pelo início\n");
    printf("2.Pelo fim\n");
    printf("3.Pelo meio\n");
    printf("0.Retornar ao menu principal\n");
    printf("---------------------\n");
    printf("::: ");
    scanf("%i", &opcao);
    getchar();

    return opcao;
    
}

jogo_t novo_jogo()
{
    jogo_t novo;

    printf("Nome do jogo......: ");
    fgets(novo.nome, T_STR, stdin);
    retirar_enter(novo.nome);
    formatar_maiuscula(novo.nome);

    printf("Ano lançamento....: ");
    scanf("%i", &novo.ano_lanc);
    getchar();

    printf("Gênero do jogo....: ");
    fgets(novo.genero, T_STR, stdin);
    retirar_enter(novo.genero);
    formatar_maiuscula(novo.genero);

    printf("Produtora do jogo.: ");
    fgets(novo.produtora, T_STR, stdin);
    retirar_enter(novo.produtora);
    formatar_maiuscula(novo.produtora);

    printf("Valor.............: ");
    scanf("%f", &novo.valor);
    getchar();

    return novo;
}

no_t *novo_no(jogo_t jogo)
{
    no_t *novo = NULL;

    novo = (no_t*)calloc(1, sizeof(no_t));

    novo->dados_jogo = jogo;
    novo->prox = NULL;

    return novo;
}

void inserir_jogo_lista_inicio(no_t *no, no_t **lista)
{
    if (*lista != NULL) {  // if (*lista)
        no->prox = *lista;
    }
    *lista = no;
}

void inserir_jogo_lista_fim(no_t *no, no_t **lista)
{
    no_t *ultimo = NULL;

    if (*lista == NULL) {  // if (!*lista)
        *lista = no;
    }
    else {
        ultimo = localizar_ultimo_no_na_lista(*lista);
        ultimo->prox = no;

        //localizar_ultimo_no_na_lista(*lista)->prox = no;
    }

}

no_t *localizar_ultimo_no_na_lista(no_t *lista)
{
    for (lista; lista->prox != NULL; lista = lista->prox);

    return lista;
}

no_t *localizar_jogo_por_nome(string nome, no_t *lista)
{

}

void mostrar_dados_jogo(jogo_t dados_jogo)
{
    printf("Nome do jogo......: %s\n", dados_jogo.nome);
    printf("Ano lançamento....: %i\n", dados_jogo.ano_lanc);
    printf("Gênero do jogo....: %s\n", dados_jogo.genero);
    printf("Produtora do jogo.: %s\n", dados_jogo.produtora);
    printf("Valor.............: %.2f\n\n", dados_jogo.valor);
}

void excluir_no_lista(no_t *no, no_t **lista)
{

}

void retirar_enter(string str)
{
    *(str+strlen(str)-1) = '\0';
}

void formatar_maiuscula(string str)
{
    for (int i = 0; i < strlen(str); i++) {
        *(str+i) = toupper(*(str+i));
    }
}

void listar_jogos_cadastrados(no_t *lista)
{
    while (lista) {
        mostrar_dados_jogo(lista->dados_jogo);
        lista = lista->prox;
    }
}