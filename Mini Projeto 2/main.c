#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LibArvore.h"

typedef struct aluno {
  char nome[50];
  int matricula;
} Aluno;

typedef struct no {
  struct no *esq;
  Aluno aluno;
  struct no *dir;
} No;

/**
 * Função para criar um novo nó na árvore e inserir um aluno, usado na função inserirALuno()
 * 
 * @param aluno o aluno a ser inserido no nó
 * @return o endereço para do novo nó
 */
No *criarNo(Aluno aluno){
  No *novoNo = (No*)malloc(sizeof(No));

  if (novoNo){
    novoNo->esq = NULL;
    novoNo->aluno = aluno;
    novoNo->dir = NULL;
  }
  return novoNo;
}

/**
 * Função para inserir um novo aluno na árvore de forma ordenada de acordo com a matricula
 * 
 * @param raiz ponteiro de ponteiro para a raiz da árvore
 * @param aluno aluno a ser inserido na árvore
 * @return 1 caso a inserção funcione - 2 caso não
 */
int inserirAluno(No **raiz, Aluno aluno){
  
  if(*raiz == NULL){
    *raiz = criarNo(aluno);
    return 1;
  }

  if((*raiz)->aluno.matricula > aluno.matricula){
    inserirAluno(&((*raiz)->esq), aluno);
  }
  else if((*raiz)->aluno.matricula < aluno.matricula){
    inserirAluno(&((*raiz)->dir), aluno);
  }
  
  return 0; //Matrícula duplicada
  
}

/**
 * Função usada para exibir o conteúdo da árvore em pré ordem
 * 
 * @param raiz raiz da árvore
 */
void mostrarArvorePreOrdem(No *raiz){
  if(raiz){
    mostrarArvorePreOrdem(raiz->esq);
    mostrarArvorePreOrdem(raiz->dir);
    printf("%d - %s\n", raiz->aluno.matricula, raiz->aluno.nome);
  }
}

int main()
{
  Aluno aluno;
  No *raiz = NULL;

  
  strcpy(aluno.nome, "Joao");
  aluno.matricula = 3;
  inserirAluno(&raiz, aluno); // Insere Joao

  strcpy(aluno.nome, "Maria");
  aluno.matricula = 1;
  inserirAluno(&raiz, aluno); // Insere Maria
  
  strcpy(aluno.nome, "Jose");
  aluno.matricula = 2;
  inserirAluno(&raiz, aluno); // Insere Jose
  
  strcpy(aluno.nome, "Pedro");
  aluno.matricula = 5;
  inserirAluno(&raiz, aluno); // Insere Pedro

  mostrarArvorePreOrdem(raiz); // Mostra a arvore em  pre-ordem

/*
  removerAluno(&raiz, 123457); // Remove Maria

  mostrarArvoreInOrdem(raiz); // Mostra a arvore apos a remocao de Maria em in-ordem

  procurarAluno(raiz, 123458); // Procura Jose / mostra se o aluno esta na arvore ou nao

  mostrarArvorePosOrdem(raiz); // Mostra a arvore em pos-ordem
*/
  return 0;
}
