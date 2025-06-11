#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_NOME 50

typedef struct no
{
    char dado[TAMANHO_NOME];
    struct no *proximo;
} no;

void inputStr(const char *pergunta, char *variavel, int tamanho)
{
    printf("%s", pergunta);
    fgets(variavel, tamanho, stdin);
    variavel[strcspn(variavel, "\n")] = '\0';
}

void inputInt(const char *pergunta, int *variavel)
{
    printf("%s", pergunta);
    scanf("%d", variavel);
    getchar();
}

/**
 * Cria um novo nó para uma lista encadeada.
 *
 * @return Ponteiro para o novo nó criado, inicializado com próximo apontando para NULL
 */
no *criarNo()
{
    no *novoNo = (no *)malloc(sizeof(no));
    novoNo->proximo = NULL;
    return novoNo;
}

int estaVazia(no *lista)
{
    return lista == NULL;
}

/**
 * Insere um novo nó no início de uma lista encadeada.
 *
 * @param lista Ponteiro para o ponteiro da lista encadeada
 * @param dado Dado a ser inserido no novo nó
 * @return 1 se a inserção for bem-sucedida
 */
int inserirInicio(no **lista, char *dado)
{
    no *novoNo = criarNo();
    strcpy(novoNo->dado, dado);
    novoNo->proximo = *lista;
    *lista = novoNo;
    return 1;
}

/**
 * Remove o primeiro nó de uma lista encadeada.
 *
 * @param lista Ponteiro para o ponteiro da lista encadeada
 * @return 1 se a remoção for bem-sucedida, 0 se a lista estiver vazia
 */
int removerInicio(no **lista)
{
    if (estaVazia(*lista))
    {
        return 0;
    }
    no *aux = *lista;
    *lista = (*lista)->proximo;
    free(aux);
    return 1;
}

/**
 * Exibe todos os elementos de uma lista encadeada.
 *
 * @param lista Ponteiro para o primeiro nó da lista encadeada
 */
void mostrarLista(no *lista)
{
    no *aux = lista;
    int contador = 1;
    while (aux != NULL)
    {
        printf("ID: %-2d | Nome: %s \n",
               contador, aux->dado);
        aux = aux->proximo;
        contador++;
    }
}

int main()
{
    no *lista = NULL;
    int opcao = -1;
    do
    {
        printf("0 - FINALIZAR\n");
        printf("1 - Inserir no inicio\n");
        printf("2 - Mostrar lista\n");
        printf("3 - Remover inicio\n");
        inputInt("Digite a opcao desejada: ", &opcao);
        printf("\n");

        if (opcao == 1)
        {
            char dado[TAMANHO_NOME];
            inputStr("Digite o dado que deseja inserir: ", dado, sizeof(dado));
            inserirInicio(&lista, dado);
            printf("Nome inserido.\n\n");
        }
        else if (opcao == 2)
        {
            if (estaVazia(lista))
            {
                printf("Lista vazia!\n\n");
                continue;
            }
            mostrarLista(lista);
            printf("\n");
        }
        else if (opcao == 3)
        {
            if (estaVazia(lista))
            {
                printf("Lista vazia!\n\n");
            }

            if (removerInicio(&lista))
            {
                printf("Primeiro nome excluido.\n\n");
            }
        }
        else if (opcao == 0)
        {
            printf("Finalizando...\n");
        }
        else
        {
            printf("Digite uma opcao valida!\n\n");
        }
    } while (opcao != 0);

    return 0;
}