#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 10
#define TAMANHO_PLACA 8

typedef struct fila
{
  char placa[MAX][TAMANHO_PLACA];
  int inicio;
  int fim;
  int qtd;
} Fila;

/**
 * Função para atribuir uma string em uma variável.
 *
 * @param pergunta A pergunta a ser exibida para o usuário.
 * @param variavel Endereço de memória para a variável do tipo char.
 * @param tamanho Tamanho máximo da variável.
 *
 */
void inputStr(const char *pergunta, char *variavel, int tamanho)
{
  printf("%s", pergunta);
  fgets(variavel, tamanho, stdin);
  variavel[strcspn(variavel, "\n")] = '\0';
}

/**
 * Função para atribuir um valor int em uma variável.
 *
 * @param pergunta A pergunta a ser exibida para o usuário.
 * @param variavel O ponteiro para a variável do tipo int.
 */
void inputInt(const char *pergunta, int *variavel)
{
  printf("%s", pergunta);
  scanf("%d", variavel);
  getchar();
}

Fila criarFila()
{
  Fila fila;
  fila.inicio = 0;
  fila.fim = 0;
  fila.qtd = 0;
  for (int i = 0; i < MAX; i++)
  {
    fila.placa[i][0] = '\0';
  }
  return fila;
}

int filaCheia(Fila *fila)
{
  return fila->qtd == MAX;
}

int filaVazia(Fila *fila)
{
  return fila->qtd == 0;
}

int verificarPlaca(const char *placa)
{
  // Verifica tamanho da placa
  if (strlen(placa) != TAMANHO_PLACA - 1)
  {
    // printf("> ERRO: VerificarPlaca: tamanho.\n\n");
    return 0;
  }

  // Verifica os 3 primeiros caracteres: letras maiúsculas
  for (int i = 0; i < 3; i++)
  {
    if (!isalpha(placa[i]) || !isupper(placa[i]))
    {
      // printf("> ERRO: VerificarPlaca: 3 primeiros caracteres.\n\n");
      return 0;
    }
  }

  // Verifica os 4 últimos caracteres: dígitos
  for (int i = 3; i < 7; i++)
  {
    if (!isdigit(placa[i]))
    {
      // printf("> ERRO: VerificarPlaca: 4 ultimos caracteres.\n\n");
      return 0;
    }
  }

  // placa válida
  return 1;
}

int registrarChegada(Fila *fila, const char *placa)
{
  if (filaCheia(fila))
  {
    printf("> ERRO: Fila cheia.\n\n");
    return 0;
  }

  if (!verificarPlaca(placa))
  {
    printf("> ERRO: Placa invalida. Exemplo de placa aceita: ABC1234\n\n");
    return 0;
  }

  strcpy(fila->placa[fila->fim], placa);
  fila->qtd++;
  fila->fim = (fila->fim + 1) % MAX;

  return 1;
}

int registrarSaida(Fila *fila)
{
  if (filaVazia(fila))
  {
    printf("> ERRO: Fila vazia.\n\n");
    return 0;
  }

  fila->placa[fila->inicio][0] = '\0';
  fila->qtd--;
  fila->inicio = (fila->inicio + 1) % MAX;
  return 1;
}

void mostrarRegistros(Fila *fila)
{
  if (filaVazia(fila))
  {
    printf("> ERRO: Fila vazia.\n\n");
    return;
  }

  printf("ID |  Placa\n");
  for (int i = 0; i < MAX; i++)
  {
    if (strcmp(fila->placa[i], "\0") == 0)
    {
      printf("%-2d |  NULL\n", (i + 1));
    }
    else
    {
      printf("%-2d |  %s\n", (i + 1), fila->placa[i]);
    }
  }
  printf("\n");
}

void menu()
{
  printf("\n");
  printf("+-----------------------------------+\n");
  printf("|  REGISTRO DE CHEGADA DE VEICULOS  |\n");
  printf("|-----------------------------------|\n");
  printf("|    1 - REGISTRAR CHEGADA          |\n");
  printf("|    2 - REGISTRAR SAIDA            |\n");
  printf("|    3 - MOSTRAR TODOS OS REGISTROS |\n");
  printf("+-----------------------------------+\n\n");
}

int main()
{
  Fila filaCarro = criarFila();
  int opcao;
  char placaAdicionada[TAMANHO_PLACA];
  char placaRemovida[TAMANHO_PLACA];

  menu();
  do
  {
    inputInt("Opcao: ", &opcao);

    switch (opcao)
    {
    case 0:
      printf("Finalizando promgrama.\n");
      break;

    case 1:
      if (filaCheia(&filaCarro))
      {
        printf("> ERRO: Fila cheia.\n\n");
        break;
      }
      inputStr("Placa: ", placaAdicionada, sizeof(placaAdicionada));

      if (registrarChegada(&filaCarro, placaAdicionada))
      {
        printf("> Placa registrada.\n\n");
      }
      break;

    case 2:
      strcpy(placaRemovida, filaCarro.placa[filaCarro.inicio]);

      if (registrarSaida(&filaCarro))
      {
        printf("> Placa %s removida da fila.\n\n", placaRemovida);
      }
      break;

    case 3:
      mostrarRegistros(&filaCarro);
      break;

    default:
      printf("Opcao invalida.\n\n");
      break;
    }
  } while (opcao);

  return 0;
}
