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
void exportar_dados_arquivo_texto(char* nome, no_t *lista);
void salvar_dados_arq_texto(char* nome, no_t *lista);
void ler_dados_arq_texto(char *nome, no_t **lista);



int main()
{
    int opc_principal, opc_sub;
    no_t *lista = NULL, *aux = NULL;
    string nome;

    ler_dados_arq_texto("base_jogos.txt", &lista);

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
            case 3: 
                printf("Qual o nome do filme que quer buscar\n");
                fgets(nome,T_STR, stdin);
                retirar_enter(nome);
                formatar_maiuscula(nome);
                aux = localizar_jogo_por_nome(nome, lista);
                if(aux != NULL){
                    mostrar_dados_jogo(aux->dados_jogo);
                }
                else{
                    printf("O filme não foi encontrado!!!\n");
                }
            
            break;
            case 4: 
                printf("Qual o nome do filme que quer buscar\n");
                fgets(nome,T_STR, stdin);
                retirar_enter(nome);
                formatar_maiuscula(nome);
                aux = localizar_jogo_por_nome(nome, lista);
                excluir_no_lista(aux, &lista);
                break;

            case 5: exportar_dados_arquivo_texto("jogos.txt", lista);
                    break;

        }

        if (lista) {
            salvar_dados_arq_texto("base_jogos.txt", lista);
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
    printf("5.Exportar dados para arquivo texto\n");
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
    for(lista; lista != NULL; lista = lista -> prox ){
        if(strcmp(lista -> dados_jogo.nome, nome) == 0){
            return lista;
        }
    }
    return NULL;
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
    no_t *anterior = NULL;

    if (!no) {
        printf("Jogo nao encontrado!\n");
    }
    else if (*lista == no) {
        *lista = no -> prox;
        free(no);
    }
    else {
        for (anterior = *lista; anterior -> prox != no; anterior = anterior -> prox);
        anterior -> prox = no -> prox;
        free(no);
    }
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

void exportar_dados_arquivo_texto(char* nome, no_t *lista)
{
    FILE *fd = NULL;

    fd = fopen(nome, "w");

    if (!fd) return;

    for (lista; lista != NULL; lista = lista->prox) {
        fprintf(fd, "Nome do jogo......: %s\n", lista->dados_jogo.nome);
        fprintf(fd, "Ano lançamento....: %i\n", lista->dados_jogo.ano_lanc);
        fprintf(fd, "Gênero do jogo....: %s\n", lista->dados_jogo.genero);
        fprintf(fd, "Produtora do jogo.: %s\n", lista->dados_jogo.produtora);
        fprintf(fd, "Valor.............: %.2f\n\n", lista->dados_jogo.valor);
    }

    fclose(fd);
}

void salvar_dados_arq_texto(char* nome, no_t *lista)
{
    FILE *fp = NULL;

    fp = fopen(nome, "w");

    if (!fp) return;

    for (lista; lista != NULL; lista = lista->prox) {
        fprintf(fp, "%s\n", lista->dados_jogo.nome);
        fprintf(fp, "%i\n", lista->dados_jogo.ano_lanc);
        fprintf(fp, "%s\n", lista->dados_jogo.genero);
        fprintf(fp, "%s\n", lista->dados_jogo.produtora);
        fprintf(fp, "%.2f\n", lista->dados_jogo.valor);
    }

    fclose(fp);
}

void ler_dados_arq_texto(char *nome, no_t **lista)
{
    FILE *fp = NULL;
    jogo_t novo_jogo;
    no_t *aux = NULL;

    fp = fopen(nome, "r");

    if (!fp) return;

    while (!feof(fp)) {
        fgets(novo_jogo.nome, T_STR, fp);
        retirar_enter(novo_jogo.nome);
        fscanf(fp, "%i\n", &novo_jogo.ano_lanc);
        fgets(novo_jogo.genero, T_STR, fp);
        retirar_enter(novo_jogo.genero);
        fgets(novo_jogo.produtora, T_STR, fp);
        retirar_enter(novo_jogo.produtora);
        fscanf(fp, "%f\n", &novo_jogo.valor);
        
        // Criar novo no
        aux = novo_no(novo_jogo);
        inserir_jogo_lista_fim(aux, lista);
    }

    fclose(fp);
}

