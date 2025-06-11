#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "LibArvore.h"

int main()
{
  setlocale(LC_ALL, "pt-br.UTF-8");
  Aluno aluno;
  No *raiz = NULL;

  carregarArquivo(&raiz);

  int opcao;
  do
  {
    printf("\n");
    printf("-----------------------------------------------------------\n");
    printf("|          SISTEMA DE ALUNOS COM ÁRVORE BINÁRIA           |\n");
    printf("-----------------------------------------------------------\n");
    printf("|                     MENU PRINCIPAL                      |\n");
    printf("-----------------------------------------------------------\n");
    printf("| 0 - SAIR _______________ Encerrar programa              |\n");
    printf("| 1 - INSERIR ALUNO ______ Fornecer RGM e Nome            |\n");
    printf("| 2 - REMOVER ALUNO ______ Fornecer RGM                   |\n");
    printf("| 3 - PESQUISAR ALUNO ____ Fornecer RGM                   |\n");
    printf("| 4 - ESVAZIAR ÁRVORE ____ Remove todos os alunos         |\n");
    printf("| 5 - EXIBIR ÁRVORE ______ Pré/In/Pós ordem               |\n");
    printf("-----------------------------------------------------------\n");
    printf("Opção: ");

    scanf("%d", &opcao);
    getchar();

    int rgm;
    char nome[TAMANHO_NOME];
    switch (opcao)
    {
    case 0:
      printf("\n> ENCERRANDO PROGRAMA...\n");
      printf("Obrigado por usar o sistema!\n");
      break;

    case 1:
      printf("\n> INSERIR NOVO ALUNO\n");
      printf("Informe o RGM: ");
      scanf("%d", &rgm);
      getchar();
      aluno.matricula = rgm;
      printf("Informe o nome: ");
      fgets(nome, sizeof(nome), stdin);
      nome[strcspn(nome, "\n")] = 0;
      strcpy(aluno.nome, nome);

      if (inserirAluno(&raiz, aluno))
      {
        printf("> Aluno inserido com sucesso!\n");
      }
      else
      {
        printf("> Erro: Matrícula já existe!\n");
      }
      break;

    case 2:
      printf("\n> REMOVER ALUNO\n");
      printf("Informe o RGM: ");
      scanf("%d", &rgm);
      getchar();
      raiz = removerAluno(raiz, rgm);
      break;

    case 3:
      printf("\n> PESQUISAR ALUNO\n");
      printf("Informe o RGM: ");
      scanf("%d", &rgm);
      getchar();
      procurarAluno(raiz, rgm);
      break;

    case 4:
      printf("\n> ESVAZIAR ÁRVORE\n");
      esvaziarArvore(&raiz);
      printf("> Árvore esvaziada com sucesso!\n");
      break;

    case 5:
      printf("\n> EXIBIR ÁRVORE\n");
      printf("+-------------------------------------+\n");
      printf("| Escolha o tipo de exibição:         |\n");
      printf("| 1 - Pré-ordem                       |\n");
      printf("| 2 - In-ordem (crescente)            |\n");
      printf("| 3 - Pós-ordem                       |\n");
      printf("+-------------------------------------+\n");
      printf("Opção: ");
      int tipo;
      scanf("%d", &tipo);
      getchar();

      switch (tipo)
      {
      case 1:
        printf("\n--- ÁRVORE EM PRÉ-ORDEM ---\n");
        mostrarArvorePreOrdem(raiz);
        break;
      case 2:
        printf("\n--- ÁRVORE EM IN-ORDEM ---\n");
        mostrarArvoreInOrdem(raiz);
        break;
      case 3:
        printf("\n--- ÁRVORE EM PÓS-ORDEM ---\n");
        mostrarArvorePosOrdem(raiz);
        break;
      default:
        printf("> Opção inválida!\n");
        break;
      }
      break;

    default:
      printf("\n> Opção inválida! Tente novamente.\n");
      break;
    }

  } while (opcao != 0);

  esvaziarArvore(&raiz);
  return 0;
}