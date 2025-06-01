#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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