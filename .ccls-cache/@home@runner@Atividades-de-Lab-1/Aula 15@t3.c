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
void corAleatoria(int cor[3]) //função para gerar a cor aleatória
{
  for (int i = 0; i < 3; i++){
    cor[i] = rand() % 255; //até 255
  }
}

void exibirQuadrados(int corA[3], int corB[3], int jaTentou) //função para exibir as cores em quadrados
{
  for (int i = 0; i < 5; i++){ //printando a cor aleatória
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
    
  if(jaTentou > 0){ //printando a cor da última tentativa SE não for a primeira vez
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

bool verificar(int codCor) //função para verificar se o número digitado é válido
{
  if(codCor < 0 || codCor > 255){
    printf("Você precisa digitar um valor entre 0 e 255! Aperte enter para tentar novamente.");
    getchar(); getchar();
    printf("\e[2A"); //leva o cursor 3 linhas para cima
    printf("\e[0J\r"); //apaga do cursor até o fim da tela
    return false;
  }
  return true;
}

void barras(int cor[3]){ //função para mostrar as barras coloridas
  for(int c = 0; c < 3; c++){
    corf(255, 255, 255);
    switch (c){
      case 0: corl(255, 0, 0); printf("R "); break;
      case 1: corl(0, 255, 0); printf("\nG "); break;
      case 2: corl(0, 0, 255); printf("\nB "); break;
    }
    for (int i = 0; i <= 252; i = i+4){
      if(cor[c] >= i && cor[c] < i+4){
        corf(255, 255, 255);
        corl(255, 221, 0);
        printf(">");
      }
      else{
        switch (c){
          case 0: corf(i, 0, 0); break;
          case 1: corf(0, i, 0); break;
          case 2: corf(0, 0, i); break;
        }
        printf(" ");
      }
    }
  }
}

float distanciaMax(int cor[3]) //calcula a maior distância possível para os valores corretos dessa cor aleatória
{
  float dMax = 0;
  for (int i = 0; i < 3; i++){
    int x = 255 - cor[i];
    if(cor[i] < x) dMax += x;
    else dMax += cor[i];
  }
  return dMax;
}

float pontuacao(int corCerta[3], int corChute[3]) //função para calcular a pontuação
{
  float distanciaChute = 0;
  float diferenca;
  for (int i = 0; i < 3; i++){
    diferenca = corChute[i] - corCerta[i];
    if(diferenca < 0){
      diferenca = diferenca / (-1);
    }
    distanciaChute += diferenca;
  }
  float distMax = distanciaMax(corCerta); //usa a função da distância máxima
  float porcErro = 100 * distanciaChute / distMax;
  float pontos = 100 - porcErro;
  return pontos;
}

void exibirGabarito(int corA[3], int corB[3]){ //função para exibir o gabarito
  corl(0, 16, 120);
  printf("----------> GABARITO:");
  corl(corA[0], corA[1], corA[2]);
  printf("\n\tCor certa\t\t\t");
  corl(corB[0], corB[1], corB[2]);
  printf("Seu chute");
  corl(255, 0, 0);
  printf("\n\tR: %d\t\t\t\tR: %d", corA[0], corB[0]);
  corl(0, 255, 0);
  printf("\n\tG: %d\t\t\t\tG: %d", corA[1], corB[1]);
  corl(0, 0, 255);
  printf("\n\tB: %d\t\t\t\tB: %d", corA[2], corB[2]);
}

void verificarRank(float pontos, float rank[3], char nomes[3][20], char nomeNovo[20]) //função para atualizar o ranking
{
  float aux1, aux2;
  char auxil1[20], auxil2[20];
  for (int i = 0; i < 3; i++){
    if(pontos >= rank[i]){
      aux1 = rank[i];
      strcpy(auxil1, nomes[i]);
      rank[i] = pontos;
      strcpy(nomes[i], nomeNovo);
      if(i == 0 || i == 1){
        aux2 = rank[i+1];
        strcpy(auxil2, nomes[i+1]);
        rank[i+1] = aux1;
        strcpy(nomes[i+1], auxil1);
        if(i == 0){
          rank[i+2] = aux2;
          strcpy(nomes[i+2], auxil2);
        }
      }
      return;
    }
  }
}

void exibirRank(float rank[3], char nomes[3][20]){ //função para exibir o ranking
  corl(255, 0, 0);
  printf("\n\n$$$$$$$$$$$$$$$$$$$$$$$$$$$ TOP SCORE $$$$$$$$$$$$$$$$$$$$$$$$$$$\n\n");
  for(int i = 0; i < 3; i++){
    if(rank[i] >= 0){
      printf("%dº - %s com %.2f pontos\n", i+1, nomes[i], rank[i]);
    }
  }
}

//MAIN
int main()
{
  float pontuacoes[5];
  int corB[3] = {0, 0, 0};
  bool novaP = true;
  float rank[3] = {-1, -1, -1};
  char nomes[3][20];

  while(novaP == true){ //Se o jogador quiser jogar novamente (inicializada como true)
    for (int i = 0; i < 5; i++){ //5 tentativas
      corf(255, 255, 255);
      limpa();
      pos(0, 0);
      corl(255, 0, 0);
      printf("\n***************** JOGO DE ADIVINHAR COR ╭( ͝ಠل͜ಠ)つ *****************\n\n");
  
      int corA[3]; //gerar cor aleatória
      if(i == 0){
        srand(time(0));
        corAleatoria(corA);
      }
        
      exibirQuadrados(corA, corB, i);
    
      corl(0, 16, 120);
      printf("-----> Vai lá, tenta um chute ¯\\_(ツ)_/¯\n\n"); //pede as cores pro usuário
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
      printf("Análise da cor escolhida:\n"); //mostra as barras
      barras(corB);
      corf(255, 255, 255);
      printf("\n\n");
    
      float pontos = pontuacao(corA, corB);
      pontuacoes[i] = pontos;
      corl(255, 0, 0);
      printf("\n############################## SCORE ##############################");
      printf("\nVocê fez %.2f pontos nessa tentativa!\n", pontos);
      printf("TENTATIVA %d/5", i + 1); //mostra quantas chances já foram usadas
      if(i < 4){ //se houver mais tentativas
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
        if(pontos >= rank[2]){ //se for boa o suficiente pra entrar no ranking
          char auxi[20];
          printf("Digite seu nome para colocar no ranking: ");
          scanf("%s", auxi);
          verificarRank(pontos, rank, nomes, auxi);
        }
        exibirRank(rank, nomes);
        corl(0, 0, 0);
        printf("\nDigite 0 para sair ou 1 para nova partida: ");
        int temp;
        scanf("%d", &temp);
        novaP = temp;
      }
    }
  }
}