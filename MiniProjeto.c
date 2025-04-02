#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 60
#define TAMANHO_NOME 50
#define TAMANHO_NUMERO 15

typedef struct elementos
{
  char nome[TAMANHO_NOME];
  int matricula;
} Aluno;

typedef struct lista
{
  Aluno dado[MAX];
  int index;
} Lista;

Lista criar()
{
  Lista lista;
  lista.index = -1;
  return lista;
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

int compararMatricula(int matricula1, int matricula2)
{
  if (matricula1 > matricula2)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

int inserir(Lista *lista, Aluno aluno)
{
  if (estaCheia(lista))
  {
    return 0;
  }

  for (int i = 0; i < lista->index; i++)
  {
    if (aluno.matricula)
    {
    }
  }

  deslocarDireita(lista, 0);
  lista->dado[0] = aluno;
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

Aluno *encontrarAlunoPeloIndex(Lista *lista, int pos)
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

void mostrarLista(Lista *lista)
{
  int i, finalLista = lista->index;

  for (i = 0; i <= finalLista; i++)
  {
    printf("ID: %d | Nome: %-6s | Matricula: %d\n",
           i + 1, lista->dado[i].nome, lista->dado[i].matricula);
  }
}

void mostrarAluno(Lista *lista, int pos)
{
  printf("Nome: %-6s | Matricula %d\n", lista->dado[pos].nome, lista->dado[pos].matricula);
}

int main()
{
  Lista listaAlunos = criar();
  Aluno aluno;
  int opcao = -1;

  do
  {
    int qntAlunos = listaAlunos.index + 1, qntEspaco = MAX - (listaAlunos.index + 1);
    printf("0 - FINALIZAR\n");
    printf("1 - Inserir aluno\n");
    printf("2 - Buscar aluno\n");
    printf("3 - Remover aluno pelo nome\n");
    printf("4 - Remover aluno pela posicao\n");
    printf("5 - Mostrar lista\n");
    printf("Quantidade de alunos: %d\n", qntAlunos);
    printf("Espaco diponivel na lista: %d\n", qntEspaco);
    inputInt("Escolha uma opcao: ", &opcao);
    printf("\n");

    if (opcao == 0)
    {
      printf("Programa finalizado.\n");
      continue;
    }

    else if (opcao == 1) // Inserir aluno
    {
      if (estaCheia(&listaAlunos))
      {
        printf("A lista esta cheia.\n\n");
        continue;
      }

      char addNome[TAMANHO_NOME];
      char addMatricula[TAMANHO_NUMERO];

      inputStr("Nome: ", addNome, sizeof(addNome));
      inputStr("Matricula: ", addMatricula, sizeof(addMatricula));

      strcpy(aluno.nome, addNome);
      aluno.matricula = atoi(addMatricula);

      if (inserir(&listaAlunos, aluno))
      {
        printf("Aluno inserido.\n\n");
      }
    }

    else if (opcao == 2) // Buscar aluno
    {
      if (estaVazia(&listaAlunos))
      {
        printf("Lista vazia.\n\n");
        continue;
      }

      char nomeBuscado[TAMANHO_NOME];
      inputStr("Digite o nome do aluno que deseja encontrar: ", nomeBuscado, sizeof(nomeBuscado));
      printf("\n");

      int posSequencial = encontrarIndexPeloNome(&listaAlunos, nomeBuscado);

      printf("Resultado da busca sequencial:\n");
      if (posSequencial == -1)
      {
        printf("Aluno nao encontrado.\n\n");
      }
      else
      {
        mostrarAluno(&listaAlunos, posSequencial);
        printf("\n");
      }
    }

    else if (opcao == 3) // Remover pelo nome
    {
      if (estaVazia(&listaAlunos))
      {
        printf("Lista vazia.\n\n");
        continue;
      }

      char nomeRemover[TAMANHO_NOME];
      inputStr("Digite o nome do aluno que deseja remover: ", nomeRemover, sizeof(nomeRemover));

      int posNome = encontrarIndexPeloNome(&listaAlunos, nomeRemover);

      if (posNome == -1)
      {
        printf("Aluno nao encontrado.\n\n");
        continue;
      }

      if (remover(&listaAlunos, posNome))
      {
        printf("Aluno removido.\n\n");
      }
    }

    else if (opcao == 4) // Remover pelo index
    {
      if (estaVazia(&listaAlunos))
      {
        printf("Lista vazia.\n\n");
        continue;
      }

      int posIndex;
      inputInt("Digite o ID do aluno que deseja remover: ", &posIndex);

      Aluno *AlunoBuscado = encontrarAlunoPeloIndex(&listaAlunos, posIndex - 1);

      if (AlunoBuscado)
      {
        remover(&listaAlunos, posIndex - 1);
        printf("Aluno removido.\n\n");
      }
      else
      {
        printf("Aluno nao encontrado.\n\n");
        continue;
      }
    }

    else if (opcao == 5) // Mostrar lista inteira
    {
      if (estaVazia(&listaAlunos))
      {
        printf("Lista vazia.\n\n");
      }
      else
      {
        mostrarLista(&listaAlunos);
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
