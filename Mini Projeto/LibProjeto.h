#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 60
#define TAMANHO_NOME 100

/**
 * Função que recebe uma pergunta e uma variável do tipo char e um tamanho.
 *
 * @param pergunta A pergunta a ser exibida para o usuário.
 * @param variavel O ponteiro para a variável do tipo char que armazenará a entrada do usuário.
 * @param tamanho O tamanho máximo da entrada do usuário.
 *
 */
void inputStr(const char *pergunta, char *variavel, int tamanho)
{
  printf("%s", pergunta);
  fgets(variavel, tamanho, stdin);
  variavel[strcspn(variavel, "\n")] = '\0';
}

/**
 * Função que recebe uma pergunta e uma variável do tipo int.
 *
 * @param pergunta A pergunta a ser exibida para o usuário.
 * @param variavel O ponteiro para a variável do tipo int que armazenará a entrada do usuário.
 */
void inputInt(const char *pergunta, int *variavel)
{
  printf("%s", pergunta);
  scanf("%d", variavel);
  getchar();
}

/**
 * Função que recebe uma pergunta e uma variável do tipo float.
 *
 * @param pergunta A pergunta a ser exibida para o usuário.
 * @param variavel O ponteiro para a variável do tipo float que armazenará a entrada do usuário.
 */
void inputFloat(const char *pergunta, float *variavel)
{
  printf("%s", pergunta);
  scanf("%f", variavel);
  getchar();
}

/* ESTRUTURAS *****************/

/**
 * Estrutura que representa uma disciplina.
 *
 * @param nome O nome da disciplina.
 * @param nota A nota da disciplina.
 * @param proximo Um ponteiro para a próxima disciplina.
 */
typedef struct Disciplina
{
  char nome[TAMANHO_NOME];
  float nota;
  struct Disciplina *proximo;
} Disciplina;

/**
 * Estrutura que representa um aluno.
 *
 * @param nome O nome do aluno.
 * @param matricula A matrícula do aluno.
 * @param disciplinas Um ponteiro para a primeira disciplina do aluno.
 */
typedef struct aluno
{
  char nome[TAMANHO_NOME];
  int matricula;
  Disciplina *disciplinas;
} Aluno;

/**
 * Estrutura que representa uma lista sequencial de alunos.
 *
 * @param aluno Um array de alunos.
 * @param index O índice do último elemento da lista
 */
typedef struct lista
{
  Aluno aluno[MAX];
  int index;
} Lista;

/* FUNCOES LISTA SEQUENCIAL *****************/

/**
 * Cria e inicializa uma nova lista sequencial de alunos.
 *
 * @return Lista vazia
 */
Lista criarLista()
{
  Lista lista;
  lista.index = -1;
  return lista;
}

/**
 * Verifica se a lista sequencial de alunos está vazia.
 *
 * @param lista Ponteiro para a lista a ser verificada
 * @return 1 se a lista estiver vazia, 0 caso contrário
 */
int estaVazia(Lista *lista)
{
  return (lista->index == -1);
}

/**
 * Verifica se a lista sequencial de alunos está cheia.
 *
 * @param lista Ponteiro para a lista a ser verificada
 * @return 1 se a lista estiver cheia, 0 caso contrário
 */
int estaCheia(Lista *lista)
{
  return (lista->index == MAX - 1);
}

/**
 * Desloca os elementos da lista para a direita a partir de uma posição específica.
 *
 * @param lista Ponteiro para a lista a ser modificada
 * @param pos Posição a partir da qual os elementos serão deslocados
 * @return 1 para indicar sucesso na operação, 0 caso a posição seja inválida
 */
int deslocarDireita(Lista *lista, int pos)
{
  if ((pos > lista->index + 1) || (pos < 0))
  {
    return 0;
  }
  int i;

  for (i = lista->index + 1; i > pos; i--)
  {
    lista->aluno[i] = lista->aluno[i - 1];
  }

  return 1;
}

/**
 * Insere um aluno na lista, mantendo a ordem crescente de matrícula.
 *
 * @param lista Ponteiro para a lista de alunos
 * @param aluno Aluno a ser inserido na lista
 * @return 1 se a inserção for bem-sucedida, 0 se a lista estiver cheia
 */
int inserirAluno(Lista *lista, Aluno aluno)
{
  if (estaCheia(lista))
  {
    return 0;
  }

  int index = 0;
  while ((index <= lista->index) && (lista->aluno[index].matricula < aluno.matricula))
  {
    index++;
  }

  deslocarDireita(lista, index);

  lista->aluno[index] = aluno;
  lista->index++;
  return 1;
}

/**
 * Desloca os elementos da lista para a esquerda a partir de uma posição específica.
 *
 * @param lista Ponteiro para a lista a ser modificada
 * @param pos Posição a partir da qual os elementos serão deslocados
 * @return 1 para indicar sucesso na operação
 */
int deslocarEsquerda(Lista *lista, int pos)
{
  int i;

  for (i = pos; i < lista->index; i++)
  {
    lista->aluno[i] = lista->aluno[i + 1];
  }

  return 1;
}

/**
 * Encontra a posição de um aluno na lista pelo número de matrícula.
 *
 * @param lista Ponteiro para a lista de alunos
 * @param matricula Número de matrícula do aluno a ser encontrado
 * @return Índice do aluno na lista se encontrado, -1 caso contrário
 */
int encontrarAluno(Lista *lista, int matricula)
{
  int i, finalLista = lista->index;

  for (i = 0; i <= finalLista; i++)
  {
    if (lista->aluno[i].matricula == matricula)
    {
      return i;
    }
  }

  return -1;
}

void removerTodasDisciplinas(Disciplina *disciplina)
{
  while (disciplina != NULL)
  {
    Disciplina *auxDisciplina = disciplina;
    disciplina = disciplina->proximo;
    free(auxDisciplina);
  }
}

/**
 * Remove um aluno da lista com base em sua matrícula.
 *
 * @param lista Ponteiro para a lista de alunos
 * @param index indice do aluna na lista a ser removido
 * @return 1 se a remoção for bem-sucedida, 0 se o aluno não for encontrado
 */
int removerAluno(Lista *lista, int index)
{
  if (estaVazia(lista))
  {
    return 0;
  }

  removerTodasDisciplinas(lista->aluno[index].disciplinas);

  deslocarEsquerda(lista, index);
  lista->index--;
  return 1;
}

/* FUNCOES LISTA ENCADEADA *****************/

/**
 * Cria uma nova disciplina alocando memória dinamicamente.
 *
 * @return Ponteiro para a nova disciplina criada, ou NULL se a alocação falhar
 */
Disciplina *criarDisciplina()
{
  Disciplina *novaDisciplina = (Disciplina *)malloc(sizeof(Disciplina));
  if (novaDisciplina == NULL)
  {
    return 0;
  }
  novaDisciplina->proximo = NULL;
  return novaDisciplina;
}

/**
 * Cria um novo aluno com disciplinas vazias.
 *
 * @return Novo aluno com disciplinas vazias
 */
Aluno criarAluno()
{
  Aluno novoAluno;
  novoAluno.disciplinas = NULL;
  return novoAluno;
}

/**
 * Verifica se um aluno possui disciplinas.
 *
 * @param aluno Ponteiro para o aluno a ser verificado
 * @return Índice do aluno na lista se encontrado, -1 caso contrário
 */
int alunoSemDisciplinas(Aluno *aluno)
{
  return aluno->disciplinas == NULL;
}

/**
 * Insere uma nova disciplina em um aluno.
 *
 * @param aluno Ponteiro para o aluno a ser modificado
 * @param nomeDisciplina Nome da disciplina a ser inserida
 * @param nota Nota da disciplina a ser inserida
 *
 * @return 1 se a inserção for bem-sucedida, 0 se a alocação falhar
 */
int inserirDisciplina(Aluno *aluno, const char *nomeDisciplina, float nota)
{
  Disciplina *novaDisciplina = criarDisciplina();
  if (!novaDisciplina)
  {
    return 0;
  }
  strcpy(novaDisciplina->nome, nomeDisciplina);
  novaDisciplina->nota = nota;
  novaDisciplina->proximo = aluno->disciplinas;
  aluno->disciplinas = novaDisciplina;

  return 1;
}

/**
 * Remove uma disciplina de um aluno com base no nome da disciplina.
 *
 * @param aluno Ponteiro para o aluno a ser modificado
 * @param nomeDisciplina Nome da disciplina a ser removida
 *
 * @return 1 se a remoção for bem-sucedida, 0 se a disciplina não for encontrada
 */
int removerDisciplina(Lista *lista, int matricula, const char *nomeDisciplina)
{
  int index = encontrarAluno(lista, matricula);
  if (index == -1)
  {
    return 0;
  }

  Aluno *auxAluno = &lista->aluno[index];
  Disciplina *atual = auxAluno->disciplinas;
  Disciplina *anterior = NULL;

  while (atual != NULL)
  {
    if (strcmp(atual->nome, nomeDisciplina) == 0)
    {
      if (anterior == NULL)
      {
        auxAluno->disciplinas = atual->proximo;
      }
      else
      {
        anterior->proximo = atual->proximo;
      }
      free(atual);
      return 1;
    }
    anterior = atual;
    atual = atual->proximo;
  }

  return 0;
}

/* FUNCOES EXIBIR *****************/

/**
 * Exibe as informações de um aluno com base em sua matrícula.
 *
 * @param lista Ponteiro para a lista de alunos
 */
void mostrarAlunoCompleto(Aluno *aluno)
{
  printf("Nome: %-6s | Matricula %d\n", aluno->nome, aluno->matricula);
  Disciplina *atual = aluno->disciplinas;
  printf("Disciplinas   | Notas\n");
  while (atual != NULL)
  {
    if (alunoSemDisciplinas(aluno))
    {
      printf("Aluno sem disciplinas.\n");
      break;
    }
    printf("%-14s| %.1f\n", atual->nome, atual->nota);
    atual = atual->proximo;
  }
  printf("\n");
}

/**
 * Exibe o nome e a matricula de um aluno
 *
 * @param aluno ponteiro para o aluno a ser exibido
 */
void mostrarAlunoSimples(Aluno *aluno)
{
  printf("Nome: %s | Matricula: %d", aluno->nome, aluno->matricula);
}

/**
 * Exibe as informações de todos os alunos e suas disciplinas.
 *
 * @param lista Ponteiro para a lista de alunos
 */
void mostrarListaCompleta(Lista *lista)
{
  if (estaVazia(lista))
  {
    printf("Lista vazia.\n\n");
    return;
  }

  int i, finalLista = lista->index;
  for (i = 0; i <= finalLista; i++)
  {
    printf("Nome: %-7s | Matricula: %d\n", lista->aluno[i].nome, lista->aluno[i].matricula);
    Disciplina *atual = lista->aluno[i].disciplinas;

    printf("Disciplinas   | Notas\n");
    while (atual != NULL)
    {
      if (alunoSemDisciplinas(&lista->aluno[i]))
      {
        printf("Aluno sem disciplinas.\n");
        break;
      }
      printf("%-14s| %.1f\n", atual->nome, atual->nota);
      atual = atual->proximo;
    }
    printf("=======================================\n");
  }
  printf("\n");
}

/**
 * Exibe a lista de alunos e sua matricula.
 *
 * @param lista Ponteiro para a lista de alunos a ser exibida
 */
void mostrarListaSimples(Lista *lista)
{
  if (estaVazia(lista))
  {
    printf("Lista vazia.\n\n");
    return;
  }

  int i, finalLista = lista->index;

  for (i = 0; i <= finalLista; i++)
  {
    printf("ID: %d | Nome: %-6s | Matricula: %d\n",
           i + 1, lista->aluno[i].nome, lista->aluno[i].matricula);
  }
  printf("\n");
}
