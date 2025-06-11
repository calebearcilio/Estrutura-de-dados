#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_NOME 100

typedef struct aluno
{
  char nome[TAMANHO_NOME];
  int matricula;
} Aluno;

typedef struct no
{
  struct no *esq;
  Aluno aluno;
  struct no *dir;
} No;

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

/**
 * Função para atribuir um valor float em uma variável.
 *
 * @param pergunta A pergunta a ser exibida para o usuário.
 * @param variavel O ponteiro para a variável do tipo float.
 */
void inputFloat(const char *pergunta, float *variavel)
{
  printf("%s", pergunta);
  scanf("%f", variavel);
  getchar();
}

/**
 * Função para criar um novo nó na árvore e inserir um aluno, usado na função inserirAluno()
 *
 * @param aluno o aluno a ser inserido no nó
 * @return o endereço para do novo nó
 */
No *criarNo(Aluno aluno)
{
  No *novoNo = (No *)malloc(sizeof(No));

  if (novoNo)
  {
    novoNo->esq = NULL;
    novoNo->aluno = aluno;
    novoNo->dir = NULL;
  }
  return novoNo;
}

/**
 * Função para inserir um novo aluno na árvore de forma ordenada de acordo com a matrícula
 *
 * @param raiz ponteiro para a raiz da árvore
 * @param aluno aluno a ser inserido na árvore
 * @return 1 caso a inserção funcione - 0 caso não
 */
int inserirAluno(No **raiz, Aluno aluno)
{

  if (*raiz == NULL)
  {
    *raiz = criarNo(aluno);
    return 1;
  }

  if ((*raiz)->aluno.matricula > aluno.matricula)
  {
    return inserirAluno(&((*raiz)->esq), aluno);
  }
  else if ((*raiz)->aluno.matricula < aluno.matricula)
  {
    return inserirAluno(&((*raiz)->dir), aluno);
  }

  return 0; // Matrícula duplicada
}

/**
 * Função usada para exibir o conteúdo da árvore em pré-ordem
 *
 * @param raiz ponteiro para a raiz da árvore
 */
void mostrarArvorePreOrdem(No *raiz)
{
  if (raiz)
  {
    printf("%d - %s\n", raiz->aluno.matricula, raiz->aluno.nome);
    mostrarArvorePreOrdem(raiz->esq);
    mostrarArvorePreOrdem(raiz->dir);
  }
}

/**
 * Função usada para exibir o conteúdo da árvore em in-ordem
 *
 * @param raiz ponteiro para a raiz da árvore
 */
void mostrarArvoreInOrdem(No *raiz)
{
  if (raiz)
  {
    mostrarArvoreInOrdem(raiz->esq);
    printf("%d - %s\n", raiz->aluno.matricula, raiz->aluno.nome);
    mostrarArvoreInOrdem(raiz->dir);
  }
}

/**
 * Função usada para exibir o conteúdo da árvore em pós-ordem
 *
 * @param raiz ponteiro para a raiz da árvore
 */
void mostrarArvorePosOrdem(No *raiz)
{
  if (raiz)
  {
    mostrarArvorePosOrdem(raiz->esq);
    mostrarArvorePosOrdem(raiz->dir);
    printf("%d - %s\n", raiz->aluno.matricula, raiz->aluno.nome);
  }
}

/**
 * Função usada para esvaziar toda a árvore
 *
 * @param raiz ponteiro para a raiz da árvore
 */
void esvaziarArvore(No **raiz)
{
  if (*raiz != NULL)
  {
    esvaziarArvore(&((*raiz)->esq));
    esvaziarArvore(&((*raiz)->dir));
    free(*raiz);
    *raiz = NULL;
  }
}

/**
 * Função usada para procurar um aluno e mostrar suas informações
 *
 * @param raiz ponteiro para a raiz da árvore
 * @param matricula matricula do aluno a ser procurado
 */
void procurarAluno(No *raiz, int matricula)
{
  if (raiz == NULL)
  {
    printf("> Erro: Aluno com RGM %d não encontrado.\n", matricula);
    return;
  }

  if (matricula < raiz->aluno.matricula)
  {
    procurarAluno(raiz->esq, matricula);
  }
  else if (matricula > raiz->aluno.matricula)
  {
    procurarAluno(raiz->dir, matricula);
  }
  else
  {
    printf("> Aluno encontrado: %d - %s\n", raiz->aluno.matricula, raiz->aluno.nome);
  }
}

/**
 * Função usada para encontrar o último nó do lado esquerdo, usado na função removerAluno
 *
 * @param raiz ponteiro para a raiz da árvore
 * @return um ponteiro para o último nó
 */
No *encontrarMinimo(No *raiz)
{
  while (raiz && raiz->esq != NULL)
  {
    raiz = raiz->esq;
  }
  return raiz;
}

/**
 * Função usada para remover um aluno da árvore
 *
 * @param raiz ponteiro para a raiz da árvore
 * @param matricula matricula do aluno a ser removido
 * @return
 */
No *removerAluno(No *raiz, int matricula)
{
  if (raiz == NULL)
  {
    printf("> Erro: Aluno com RGM %d não encontrado para remoção.\n", matricula);
    return NULL;
  }

  if (matricula < raiz->aluno.matricula)
  {
    raiz->esq = removerAluno(raiz->esq, matricula);
  }
  else if (matricula > raiz->aluno.matricula)
  {
    raiz->dir = removerAluno(raiz->dir, matricula);
  }
  else
  {
    // Nó encontrado
    printf("> Removendo aluno: %d - %s\n", raiz->aluno.matricula, raiz->aluno.nome);

    // Caso 1: Nó sem filhos
    if (raiz->esq == NULL && raiz->dir == NULL)
    {
      free(raiz);
      return NULL;
    }

    // Caso 2: Um filho apenas
    if (raiz->esq == NULL)
    {
      No *temp = raiz->dir;
      free(raiz);
      return temp;
    }
    else if (raiz->dir == NULL)
    {
      No *temp = raiz->esq;
      free(raiz);
      return temp;
    }

    // Caso 3: Dois filhos - usa sucessor
    No *sucessor = encontrarMinimo(raiz->dir);
    raiz->aluno = sucessor->aluno;                                  // Copia dados
    raiz->dir = removerAluno(raiz->dir, sucessor->aluno.matricula); // Remove sucessor
  }
  return raiz;
}

/**
 * Função usada para carregar e inserir dados do arquivo alunos.txt na árvore, ou criar o arquivo caso não exista
 * 
 * @param raiz ponteiro para a raiz da árvore
 */
void carregarArquivo(No **raiz)
{
  Aluno aluno;
  FILE *arquivo = fopen("alunos.txt", "r");
  if (arquivo == NULL)
  {
    printf("> Criando arquivo\n");
    arquivo = fopen("alunos.txt", "w");
    carregarArquivo(&(*raiz));
    return;
  }

  printf("> lendo o arquivo\n");
  char linha[512];
  while (fgets(linha, sizeof(linha), arquivo) != NULL)
  {
    int rgm;
    char nome[TAMANHO_NOME];
    sscanf(linha, "%d %[^\n]", &rgm, nome);
    aluno.matricula = rgm;
    strcpy(aluno.nome, nome);
    inserirAluno(&(*raiz), aluno);
  }

  fclose(arquivo);
}
