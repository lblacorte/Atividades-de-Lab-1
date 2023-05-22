#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

//funções disponibilizadas pelo professor:
void corl(int r, int g, int b)
{
  printf("\e[38;2;%d;%d;%dm", r, g, b);
}
void corf(int r, int g, int b)
{
  printf("\e[48;2;%d;%d;%dm", r, g, b);
}
void corn(void)
{
  printf("\e[m");
}
void pos(int lin, int col)
{
  printf("\e[%d;%dH", lin, col);
}
void limpa(void)
{
  printf("\e[2J");
}

//minhas funções:
void corAleatoria(int cor[3])
{
  for (int i = 0; i < 3; i++){
  cor[i] = rand() % 255;
  }
}

void exibirQuadrados(int corA[3], int corB[3], int i)
{
  for (int i = 0; i < 5; i++){
    pos(4+i, 10);
    for(int j = 0; j < 15; j++){
      corf(corA[0], corA[1], corA[2]);
      printf(" ");
    }
    corf(255, 255, 255);
    printf("\n");
  }
    
  corl(corA[0], corA[1], corA[2]);
  pos(9, 9);
  printf("Cor para adivinhar");
    
  if(i > 0){
    for (int i = 0; i < 5; i++){
    pos(4+i, 40);
    for(int j = 0; j < 15; j++){
      corf(corB[0], corB[1], corB[2]);
      printf(" ");
    }
    corf(255, 255, 255);
    printf("\n");
  }
  corl(corB[0], corB[1], corB[2]);
  pos(9, 39);
  printf("Tentativa anterior\n\n\n");
  }
  else printf("\n\n\n");
}

bool verificar(int codCor)
{
  if(codCor < 0 || codCor > 255){
    printf("Você precisa digitar um valor entre 0 e 255! Aperte enter para tentar novamente.");
    getchar(); getchar();
    printf("\e[3A");
    printf("\e[0J\r");
    return false;
  }
  return true;
}

void barras(int cor[3]){
  corl(255, 0, 0);
  printf("R ");
  for (int i = 0; i <= 252; i = i+4){
    if(cor[0] >= i && cor[0] < i+4){
      corf(255, 255, 255);
      corl(255, 221, 0);
      printf(">");
    }
    else{
    corf(i, 0, 0);
    printf(" ");
    }
  }
  corf(255, 255, 255);
  corl(0, 255, 0);
  printf("\nG ");
  for (int i = 0; i <= 252; i = i+4){
    if(cor[1] >= i && cor[1] < i+4){
      corf(255, 255, 255);
      corl(255, 221, 0);
      printf(">");
    }
    else{
    corf(0, i, 0);
    printf(" ");
    }
  }
  corf(255, 255, 255);
  corl(0, 0, 255);
  printf("\nB ");
  for (int i = 0; i <= 252; i = i+4){
    if(cor[2] >= i && cor[2] < i+4){
      corf(255, 255, 255);
      corl(255, 221, 0);
      printf(">");
    }
    else{
    corf(0, 0, i);
    printf(" ");
    }
  }
}

float distanciaMax(int cor[3])
{
  float dMax = 0;
  for (int i = 0; i < 3; i++){
    int x = 255 - cor[i];
    if(cor[i] < x) dMax += x;
    else dMax += cor[i];
  }
  return dMax;
}

float pontuacao(int corCerta[3], int corChute[3]){
  float distanciaChute = 0;
  float diferenca;
  for (int i = 0; i < 3; i++){
    diferenca = corChute[i] - corCerta[i];
    if(diferenca < 0){
      diferenca = diferenca / (-1);
    }
    distanciaChute += diferenca;
  }
  float distMax = distanciaMax(corCerta);
  float porcErro = 100 * distanciaChute / distMax;
  float pontos = 100 - porcErro;
  return pontos;
}

void exibirGabarito(int corA[3], int corB[3]){
  corl(0, 16, 120);
  printf("----------> GABARITO:");
  corl(corA[0], corA[1], corA[2]);
  printf("\n\tCor certa\t\t\t\t\t\t");
  corl(corB[0], corB[1], corB[2]);
  printf("Seu chute");
  corl(255, 0, 0);
  printf("\n\tR: %d\t\t\t\t\t\t\tR: %d", corA[0], corB[0]);
  corl(0, 255, 0);
  printf("\n\tG: %d\t\t\t\t\t\t\tG: %d", corA[1], corB[1]);
  corl(0, 0, 255);
  printf("\n\tB: %d\t\t\t\t\t\t\tB: %d", corA[2], corB[2]);
}

void verificarRank(float pontos, float rank[3], char nome1[20], char nome2[20], char nome3[20], char nomeNovo[20])
{
  float aux1, aux2;
  char auxil1[20], auxil2[20];
  if(pontos >= rank[0]){
    aux1 = rank[0];
    strcpy(auxil1, nome1);
    rank[0] = pontos;
    strcpy(nome1, nomeNovo);
    aux2 = rank[1];
    strcpy(auxil2, nome2);
    rank[1] = aux1;
    strcpy(nome2, auxil1);
    rank[2] = aux2;
    strcpy(nome3, auxil2);
  }
  else if(pontos >= rank[1]){
    aux1 = rank[1];
    strcpy(auxil1, nome2);
    rank[1] = pontos;
    strcpy(nome2, nomeNovo);
    rank[2] = aux1;
    strcpy(nome3, auxil1);
  }
  else if(pontos >= rank[2]){
    rank[2] = pontos;
    strcpy(nome3, nomeNovo);
  }
}

void exibirRank(float rank[3], char nome1[20], char nome2[20], char nome3[20]){
  corl(255, 0, 0);
  printf("\n\n$$$$$$$$$$$$$$$$$$$$$$$$$$$ TOP SCORE $$$$$$$$$$$$$$$$$$$$$$$$$$$\n\n");
  printf("1º - %s com %.2f pontos\n", nome1, rank[0]);
  if(rank[1] >= 0)
  printf("2º - %s com %.2f pontos\n", nome2, rank[1]);
  if(rank[2] >= 0)
  printf("3º - %s com %.2f pontos\n", nome3, rank[2]);
}

int main()
{
  float pontuacoes[5];
  int corB[3] = {0, 0, 0};
  bool novaP = true;
  float rank[3] = {-1, -1, -1};
  char nome1[20], nome2[20], nome3[20];

  while(novaP == true){
  for (int i = 0; i < 5; i++){
  corf(255, 255, 255);
  limpa();
  pos(0, 0);
  corl(255, 0, 0);
  printf("\n***************** JOGO DE ADIVINHAR COR ╭( ͝ಠل͜ಠ)つ *****************\n\n");

  int corA[3];

  if(i == 0){
  srand(time(0));
  corAleatoria(corA);
  }
    
  exibirQuadrados(corA, corB, i);

  corl(0, 16, 120);
  printf("-----> Vai lá, tenta um chute ¯\\_(ツ)_/¯\n\n");
  printf("É só escolher um código RGB:\n\n");
  
  do{
  corl(255, 0, 0);
  printf("R: ");
  scanf("%d", &corB[0]);
  } while (verificar(corB[0]) == false);
  do{
  corl(0, 255, 0);
  printf("G: ");
  scanf("%d", &corB[1]);
  } while (verificar(corB[1]) == false);
  do{
  corl(0, 0, 255);
  printf("B: ");
  scanf("%d", &corB[2]);
  } while (verificar(corB[2]) == false);
  printf("\n\n");

  corl(4, 79, 0);
  printf("Análise da cor escolhida:\n");

  barras(corB);
  
  corf(255, 255, 255);
  printf("\n\n");

  float pontos = pontuacao(corA, corB);

  pontuacoes[i] = pontos;
    
  corl(255, 0, 0);
  printf("\n############################## SCORE ##############################");
  printf("\nVocê fez %.2f pontos nessa tentativa!\n", pontos);
  printf("TENTATIVA %d/5", i + 1);
  if(i < 4){
  printf("\nAperte enter para nova tentativa!");
  getchar(); getchar();
  }
  else{
  printf("\nAperte enter para conferir o resultado!");
  getchar(); getchar();
  limpa();
  pos(0, 0);
  corl(255, 0, 0);
  printf("\n***************** JOGO DE ADIVINHAR COR ╭( ͝ಠل͜ಠ)つ *****************\n\n");
  exibirQuadrados(corA, corB, i);
  exibirGabarito(corA, corB);
  printf("\n\n\n############################ SCORE ############################\n\n");
  printf("A sua pontuação final foi %.2f pontos! (última tentativa)\n", pontos);
  if(pontos >= rank[2]){
  char auxi[20];
  printf("Digite seu nome para colocar no ranking: ");
  scanf("%s", auxi);
  verificarRank(pontos, rank, nome1, nome2, nome3, auxi);
  }
  exibirRank(rank, nome1, nome2, nome3);
  corl(0, 0, 0);
  printf("\nDigite 0 para sair ou 1 para nova partida: ");
  int temp;
  scanf("%d", &temp);
  novaP = temp;
  }
  }
  }
}