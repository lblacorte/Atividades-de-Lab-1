// Uma empresa de jogos resolveu premiar seu melhor jogador, doando
// seu próximo lançamento. Para isso, precisa escolher o melhor jogador.
// A empresa mantém um arquivo com o final de cada partida jogada,
// contendo a identificação do usuário, a identificação do jogo,
// a data e a pontuação.
// O melhor jogador é considerado aquele que tem a maior soma de pontos,
// considerando uma pontuação por jogo, no mês corrente.
// Faça um programa que lê do usuário a data correspondente ao início
// e ao final do mês e informa a identificação do ganhador.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
  int jogador;
  int jogo;
  int data;
  int pontos;
} dados;

// a->b   ===  (*a).b
bool le_1(FILE *arq, dados *ponteiro)
{
  if (fscanf(arq, "%d %d %d %d",
		&ponteiro->jogador,
		&ponteiro->jogo,
		&ponteiro->data,
		&ponteiro->pontos) == 4) {
    return true;
  } else {
    return false;
  }
}

void gera_arquivo(void)
{
  FILE *arquivo;
  arquivo = fopen("registro_de_jogadas", "w");
  if (arquivo == NULL) {
    printf("Erro no acesso ao arquivo 'dados'.\n");
    return;
  }
  for (int i=0; i<100; i++) {
    fprintf(arquivo, "%d %d %d %d\n", rand()%100+1, rand()%100+1,
		  rand()%10000, rand()%10000000);
  }

  fclose(arquivo);
}

int main()
{
  gera_arquivo();
}
