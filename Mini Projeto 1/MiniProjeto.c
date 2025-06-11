#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "LibLista.h"

int adicionandoDisciplinaNoAluno(Aluno *aluno)
{
  char disciplina[TAMANHO_NOME];
  float nota = -1;
  inputStr("Disciplina: ", disciplina, sizeof(disciplina));
  if (strcmp(disciplina, "0") == 0)
  {
    printf("Operacao finalizada.\n\n");
    return 0;
  }

  printf("-1 - FINALIZAR\n");
  inputFloat("Nota: ", &nota);
  if (nota == -1)
  {
    printf("Operacao finalizada.\n\n");
    return 0;
  }

  if (inserirDisciplina(aluno, disciplina, nota))
  {
    printf("Disciplina adicionada.\n\n");
  }
  else
  {
    printf("Falha ao adicionar a disciplina.\n");
  }

  adicionandoDisciplinaNoAluno(aluno);
  return 1;
}

void adicionandoAlunoNaLista(Lista *lista)
{
  if (estaCheia(lista))
  {
    printf("Lista cheia.\n\n");
    return;
  }

  int matricula;
  char nomeAluno[TAMANHO_NOME];
  Aluno aluno = criarAluno();

  printf("0 - FINALIZAR\n");
  inputStr("Nome do aluno: ", nomeAluno, sizeof(nomeAluno));
  if (strcmp(nomeAluno, "0") == 0)
  {
    printf("\nOperacao finalizada.\n\n");
    return;
  }

  inputInt("Matricula do aluno: ", &matricula);
  if (matricula == 0)
  {
    printf("\nOperacao finalizada.\n\n");
    return;
  }

  strcpy(aluno.nome, nomeAluno);
  aluno.matricula = matricula;
  mostrarAlunoSimples(&aluno);

  printf("\n\nAdicionando disciplinas.\n0 - FINALIZAR\n");

  if (adicionandoDisciplinaNoAluno(&aluno))
  {
    inserirAluno(lista, aluno);
    printf("Aluno inserido com sucesso!\n\n");
    adicionandoAlunoNaLista(lista);
  }
  return;
}

void removendoAlunoDaLista(Lista *lista)
{

  if (estaVazia(lista))
  {
    printf("Lista vazia.\n\n");
    return;
  }

  int matricula, indice;
  inputInt("Digite a matricula do aluno: ", &matricula);

  indice = encontrarAluno(lista, matricula);
  if (indice == -1)
  {
    printf("Aluno nao encontrado.\n\n");
    removendoAlunoDaLista(lista);
  }

  removerAluno(lista, indice);
  printf("Aluno removido.\n\n");
  mostrarListaSimples(lista);
  return;
}

void BuscarAluno(Lista *lista)
{
  if (estaVazia(lista))
  {
    printf("Lista vazia.\n\n");
    return;
  }

  int matricula;
  inputInt("Digite a matricula para a busca: ", &matricula);

  int index = encontrarAluno(lista, matricula);

  if (index == -1)
  {
    printf("Aluno não encontrado.\n\n");
    return;
  }

  mostrarAlunoCompleto(&lista->aluno[index]);
}

int main()
{
  int opcao = -1;
  Lista listaAlunos = criarLista();
  do
  {
    int qntAlunos = listaAlunos.index + 1, qntEspaco = MAX - (listaAlunos.index + 1);
    printf("0 - FINALIZAR\n");
    printf("1 - Adicionar alunos\n");
    printf("2 - Remover um aluno\n");
    printf("3 - Buscar e mostrar um aluno\n");
    printf("4 - Mostrar lista\n");
    printf("Quantidade de alunos: %d\n", qntAlunos);
    printf("Espaco disponivel na lista: %d\n", qntEspaco);
    inputInt("Digite a opcao desejada: ", &opcao);
    printf("\n");

    if (opcao == 0)             // FINALIZAR
    {
      printf("Finalizando.");
      continue;
    }

    else if (opcao == 1)        // ADICIONAR
    {
      adicionandoAlunoNaLista(&listaAlunos);
    }

    else if (opcao == 2)        // REMOVER
    {
      removendoAlunoDaLista(&listaAlunos);
    }

    else if (opcao == 3)        // BUSCAR
    {
      BuscarAluno(&listaAlunos);
    }

    else if (opcao == 4)        // MOSTRAR
    {
      mostrarListaCompleta(&listaAlunos);
    }

    else
    {
      printf("Opcao invalida, tente novamente.\n\n");
    }

  } while (opcao != 0);

  return 0;
}
