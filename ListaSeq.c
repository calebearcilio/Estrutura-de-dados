#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 5
#define TAMANHO_NOME 50
#define TAMANHO_NUMERO 15

// Estrutura de um elemento
typedef struct elementos
{
  char nome[TAMANHO_NOME];
  char telefone[TAMANHO_NUMERO];
} Contato;

// Estrutura da lista
typedef struct lista
{
  Contato dado[MAX];
  int index;
} Lista;

Lista criar()
{
  Lista lista;
  lista.index = -1; // index começa em -1 para dizer que a lista está vazia
  return lista;     // retorna a prórpia lista criada vazia
}

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

int estaVazia(Lista *lista)
{
  return (lista->index == -1);
}

int estaCheia(Lista *lista)
{
  return (lista->index == MAX - 1);
}

int deslocarDireita(Lista *lista, int pos)
{
  int i;

  for (i = lista->index + 1; i > pos; i--)
  {
    lista->dado[i] = lista->dado[i - 1];
  }

  return 1;
}

int inserir(Lista *lista, int pos, Contato valor)
{
  if (estaCheia(lista) || (pos > lista->index + 1) || (pos < 0))
  {
    return 0;
  }

  deslocarDireita(lista, pos);
  lista->dado[pos] = valor;
  lista->index++;
  return 1;
}

int deslocarEsquerda(Lista *lista, int pos)
{
  int i;

  for (i = pos; i < lista->index; i++)
  {
    lista->dado[i] = lista->dado[i + 1];
  }

  return 1;
}

int remover(Lista *lista, int pos)
{
  if (estaVazia(lista) || (pos > lista->index + 1) || (pos < 0))
  {
    return 0;
  }

  deslocarEsquerda(lista, pos);
  lista->index--;
  return 1;
}

Contato *encontrarContatoPeloIndex(Lista *lista, int pos)
{
  if (pos > lista->index || pos < 0)
  {
    return 0;
  }

  return &(lista->dado[pos]);
}

int compararNome(const char *nome1, const char *nome2)
{
  return strcmp(nome1, nome2) == 0;
}

// Busca sequencial
int encontrarIndexPeloNome(Lista *lista, const char *nomeBuscado)
{
  int i, finalLista = lista->index;

  for (i = 0; i <= finalLista; i++)
  {
    if (compararNome(lista->dado[i].nome, nomeBuscado))
    {
      return i;
    }
  }

  return -1;
}

// Função usada para ordenação, usada por qsort
int compararContatos(const void *a, const void *b)
{
  return strcmp(((Contato *)a)->nome, ((Contato *)b)->nome);
}

// Busca binaria
int buscaBinaria(Lista *lista, const char *nomeBuscado)
{
  int comeco = 0, fim = lista->index;

  while (comeco <= fim)
  {
    int meio = (comeco + fim) / 2;
    int comparacao = strcmp(lista->dado[meio].nome, nomeBuscado);

    if (comparacao == 0)
    {
      return meio;
    }
    else if (comparacao < 0)
    {
      comeco = meio + 1;
    }
    else
    {
      fim = meio - 1;
    }
  }
  return -1;
}

void mostrarLista(Lista *lista)
{
  int i, finalLista = lista->index;

  for (i = 0; i <= finalLista; i++)
  {
    printf("ID: %d | Nome: %-6s | Telefone: %s\n",
           i + 1, lista->dado[i].nome, lista->dado[i].telefone);
  }
}

void mostrarContato(Lista *lista, int pos)
{
  printf("Nome: %-6s | Telefone %s\n", lista->dado[pos].nome, lista->dado[pos].telefone);
}

void exemplosContatos(Lista *lista)
{
  Contato contatos[] = {{"Carlos", "1111-1111"},
                        {"Joao", "1234-5678"},
                        {"Maria", "8765-4321"},
                        {"Ana", "5555-5555"},
                        {"Bruno", "2222-2222"}};

  inserir(lista, 0, contatos[0]);
  inserir(lista, 0, contatos[1]);
  inserir(lista, 0, contatos[2]);
  inserir(lista, 0, contatos[3]);
  inserir(lista, 0, contatos[4]);
}

int main()
{
  Lista listaContatos = criar();
  Contato contato;
  exemplosContatos(&listaContatos);
  int opcao;

  do
  {
    int qntContatos = listaContatos.index + 1, qntEspaco = MAX - (listaContatos.index + 1);
    printf("0 - FINALIZAR\n");
    printf("1 - Inserir contato\n");
    printf("2 - Buscar contato\n");
    printf("3 - Remover contato pelo nome\n");
    printf("4 - Remover contato pela posicao\n");
    printf("5 - Mostrar lista\n");
    printf("Quantidade de contatos: %d\n", qntContatos);
    printf("Espaco diponivel na lista: %d\n", qntEspaco);
    inputInt("Escolha uma opcao: ", &opcao);
    printf("\n");

    if (opcao == 0)
    {
      printf("Programa finalizado.\n");
      continue;
    }

    else if (opcao == 1)
    {
      if (estaCheia(&listaContatos))
      {
        printf("A lista esta cheia.\n\n");
        continue;
      }

      char addNome[TAMANHO_NOME];
      char addTelefone[TAMANHO_NUMERO];

      inputStr("Nome: ", addNome, sizeof(addNome));
      inputStr("Telefone: ", addTelefone, sizeof(addTelefone));

      strcpy(contato.nome, addNome);
      strcpy(contato.telefone, addTelefone);

      if (inserir(&listaContatos, 0, contato))
      {
        printf("Contato inserido.\n\n");
      }
    }

    else if (opcao == 2) // Buscar contato
    {
      if (estaVazia(&listaContatos))
      {
        printf("Lista vazia.\n\n");
        continue;
      }

      char nomeBuscado[TAMANHO_NOME];
      inputStr("Digite o nome do contato que deseja encontrar: ", nomeBuscado, sizeof(nomeBuscado));
      printf("\n");

      int posSequencial = encontrarIndexPeloNome(&listaContatos, nomeBuscado);

      printf("Resultado da busca sequencial:\n");
      if (posSequencial == -1)
      {
        printf("Contato nao encontrado.\n\n");
      }
      else
      {
        mostrarContato(&listaContatos, posSequencial);
        printf("\n");
      }

      Lista listaProvisoria = criar();
      listaProvisoria = listaContatos;

      qsort(listaProvisoria.dado, listaProvisoria.index + 1, sizeof(Contato), compararContatos);
      int posBinaria = buscaBinaria(&listaProvisoria, nomeBuscado);

      printf("Resultado da buca binaria:\n");
      if (posBinaria == -1)
      {
        printf("Contato nao encontrado.\n\n");
        continue;
      }
      else
      {
        mostrarContato(&listaProvisoria, posBinaria);
        printf("\n");
      }
    }

    else if (opcao == 3) // Remover pelo nome
    {
      if (estaVazia(&listaContatos))
      {
        printf("Lista vazia.\n\n");
        continue;
      }

      char nomeRemover[TAMANHO_NOME];
      inputStr("Digite o nome do contato que deseja remover: ", nomeRemover, sizeof(nomeRemover));

      int posNome = encontrarIndexPeloNome(&listaContatos, nomeRemover);

      if (posNome == -1)
      {
        printf("Contato nao encontrado.\n\n");
        continue;
      }

      if (remover(&listaContatos, posNome))
      {
        printf("Contato removido.\n\n");
      }
    }

    else if (opcao == 4) // Remover pelo index
    {
      if (estaVazia(&listaContatos))
      {
        printf("Lista vazia.\n\n");
        continue;
      }

      int posIndex;
      inputInt("Digite o ID do contato que deseja remover: ", &posIndex);

      Contato *contatoBuscado = encontrarContatoPeloIndex(&listaContatos, posIndex - 1);

      if (contatoBuscado)
      {
        remover(&listaContatos, posIndex - 1);
        printf("Contato removido.\n\n");
      }
      else
      {
        printf("Contato nao encontrado.\n\n");
        continue;
      }
    }

    else if (opcao == 5) // Mostrar lista inteira
    {
      if (estaVazia(&listaContatos))
      {
        printf("Lista vazia.\n\n");
      }
      else
      {
        mostrarLista(&listaContatos);
        printf("\n");
      }
    }

    else
    {
      printf("Digite uma opcao valida.\n\n");
    }
  } while (opcao != 0);

  return 0;
}
