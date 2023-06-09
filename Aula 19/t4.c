#include "tela.h" //incluindo as novas funções
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

// tipo registro que representa os dados de uma partida
typedef struct {
    int corB[3];
    int corA[3];
    float rank[3];
    char nomes[3][20];
    double tempo;
    double bonusTempo;
    float pontosA;
    float pontosB;
} JOGO;

//função para gerar a cor aleatória
void corAleatoria(JOGO *novoJogo)
{
  for (int i = 0; i < 3; i++){
    novoJogo->corA[i] = rand() % 256; //até 255
  }
}

//função para exibir as cores em quadrados
void exibirQuadrado(int cores[3], int coluna)
{
  cor novaCor;
  for (int i = 0; i < 5; i++){
    posicao novaPos = {4+i, coluna};
    tela_posiciona(novaPos);
    for(int j = 0; j < 15; j++){
      novaCor = (cor) {cores[0], cores[1], cores[2]};
      tela_cor_fundo(novaCor);
      printf(" ");
    }
    novaCor = (cor) {255, 255, 255};
    tela_cor_fundo(novaCor);
    printf("\n");
  }
  novaCor = (cor) {cores[0], cores[1], cores[2]};
  tela_cor_letra(novaCor);
}

//Função para gerar as barras coloridas
void geraBarra(int c){
  cor novaCor;
  for (int i = 0; i <= 252; i = i+4){
    switch (c){
      case 0: 
        novaCor = (cor) {i, 0, 0}; 
        tela_cor_fundo(novaCor); 
        break;
      case 1: 
        novaCor = (cor) {0, i, 0}; 
        tela_cor_fundo(novaCor); 
        break;
      case 2: 
        novaCor = (cor) {0, 0, i}; 
        tela_cor_fundo(novaCor); 
        break;
    }
    printf(" ");
  }
}

//função para mostrar as barras coloridas (escreve R, G, B)
void barras(){
  for(int c = 0; c < 3; c++){
    cor novaCor = {255, 255, 255};
    tela_cor_fundo(novaCor);
    switch (c){
      case 0: 
        novaCor = (cor) {255, 0, 0}; 
        tela_cor_letra(novaCor); 
        printf("R "); 
        break;
      case 1: 
        novaCor = (cor) {0, 255, 0}; 
        tela_cor_letra(novaCor); 
        printf("\nG "); 
        break;
      case 2: 
        novaCor = (cor) {0, 0, 255}; 
        tela_cor_letra(novaCor); 
        printf("\nB ");
        break;
    }
    geraBarra(c);
  }
}

//calcula o pior chute para posicionar o marcador na barra
int piorChute (int cor)
{
  int x = 255 - cor;
  if(cor < x) return 255;
  else return 0;
}

//função para escrever os valores ao lado de cada barra em tempo real
void printarRGB(JOGO *novoJogo)
{
  posicao novaPos = {16, 68};
  tela_posiciona(novaPos);
  cor novaCor = {255, 0, 0};
  tela_cor_letra(novaCor);
  printf("%.3d", novoJogo->corB[0]);
  novaPos = (posicao) {17, 68};
  tela_posiciona(novaPos);
  novaCor = (cor) {0, 255, 0};
  tela_cor_letra(novaCor);
  printf("%.3d", novoJogo->corB[1]);
  novaPos = (posicao) {18, 68};
  tela_posiciona(novaPos);
  novaCor = (cor) {0, 0, 255};
  tela_cor_letra(novaCor);
  printf("%.3d", novoJogo->corB[2]);
}

//posiciona o marcador da barra no pior chute possível
void iniciarPiorMarcador(JOGO *novoJogo, int ultMultiplo[3], int linMarcador, int colMarcador[3])
{
  cor novaCor = {255, 255, 255};
  tela_cor_fundo(novaCor);
  novaCor = (cor) {255, 221, 0};
  tela_cor_letra(novaCor);
  for(int i = 0; i < 3; i++){
    novoJogo->corB[i] = piorChute(novoJogo->corA[i]); 
    ultMultiplo[i] = novoJogo->corB[i];
    posicao novaPos = {linMarcador + i, colMarcador[i]};
    tela_posiciona(novaPos);
    printf(">");
  }
  posicao novaPos = {14, 35};
  tela_posiciona(novaPos);
  novaCor = (cor) {255, 221, 0};
  tela_cor_letra(novaCor);
  printf("Modo "); 
  novaCor = (cor) {255, 0, 0};
  tela_cor_letra(novaCor); 
  printf("lento "); 
  novaCor = (cor) {252, 119, 3}; 
  tela_cor_letra(novaCor); 
  printf("(aperte backspace para mudar).");
}

//posiciona o marcador no lugar certo quando muda-se o modo para velocidade rápida
void mudancaVelocidade(int resto, JOGO *novoJogo, int colMarcador[3], int i)
{
  switch(resto){
    case 1: 
      novoJogo->corB[i] -= 1; 
      colMarcador[i]--; 
      break;
    case 2: 
      novoJogo->corB[i] -= 2; 
      colMarcador[i]--; 
      break;
    case 3: 
      novoJogo->corB[i] += 1; 
      colMarcador[i]++; 
      break;
  }
}

//altera a velocidade do marcador da barra caso seja solicitado pelo usuário
void alterarVelocidade(int *velocidade, JOGO *novoJogo, int colMarcador[3])
{
  switch(*velocidade){
    case 1: 
      *velocidade = 4;
      int resto[3];
        for(int i = 0; i < 3; i++){
          if(novoJogo->corB[i] != 0){
            resto[i] = (novoJogo->corB[i] + 1) % 4;
            if(resto[i] != 0){
              mudancaVelocidade(resto[i], novoJogo, colMarcador, i);
            }
          }
        }
      break;
    case 4: 
      *velocidade = 1; 
      break;
  }
}

//reconstroi a cor antiga da barra toda vez que o marcador muda de lugar
//isso evita que seja necessário gerar a barra a todo movimento
void reconstruirCorAntiga(int linMarcadorAnt, int colMarcadorAnt, int linMarcador)
{
  posicao novaPos = {linMarcadorAnt, colMarcadorAnt};
  cor novaCor;
  tela_posiciona(novaPos);
  int corAntiga = 4*(colMarcadorAnt - 3);
  switch(linMarcador){
    case 16: 
      novaCor = (cor) {corAntiga, 0, 0}; 
      tela_cor_fundo(novaCor); 
      break;
    case 17: 
      novaCor = (cor) {0, corAntiga, 0}; 
      tela_cor_fundo(novaCor); 
      break;
    case 18: 
      novaCor = (cor) {0, 0, corAntiga}; 
      tela_cor_fundo(novaCor); 
      break;
  }
  printf(" ");
}

//trata quando é apertado seta para esquerda
//utilizei um sistema de múltiplos de 4 para adaptar as 256 posicões da barra à resolução da tela
//podem ocorrer bugs que ainda não resolvi
void teclaEsquerda(int linMarcador, JOGO *novoJogo, int velocidade, int colMarcador[3], int ultMultiplo[3])
{
  for(int i = 0; i < 3; i++){
    if(linMarcador == 16 + i){
      if (novoJogo->corB[i] == 3 && velocidade == 4) novoJogo->corB[i] = 4;
        if (novoJogo->corB[i] > 0){
          novoJogo->corB[i] -= velocidade; 
          if((novoJogo->corB[i] > 0 && (novoJogo->corB[i] + 1) % 4 == 0 && novoJogo->corB[i] != ultMultiplo[i]) || (novoJogo->corB[i] == 0 && velocidade == 1 && ultMultiplo[i] == 3)){
            colMarcador[i]--; 
            ultMultiplo[i] = novoJogo->corB[i];
          }
        }
    }
  }
}

//trata quando é apertado seta para direita
void teclaDireita(int linMarcador, JOGO *novoJogo, int velocidade, int colMarcador[3], int ultMultiplo[3], int aux[3])
{
  for (int i = 0; i < 3; i++){
    if (linMarcador == 16 + i){
      if (novoJogo->corB[i] == 0 && velocidade == 4) aux[i] = 1; 
      else aux[i] = 0; 
        if (novoJogo->corB[i] < 255){
          novoJogo->corB[i] += (velocidade - aux[i]); 
          if((novoJogo->corB[i] == 0 || (novoJogo->corB[i] + 1) % 4 == 0) && novoJogo->corB[i] != ultMultiplo[i]){
            colMarcador[i]++; 
            ultMultiplo[i] = novoJogo->corB[i];
          }
        }
    }
  }
}

//posiciona o marcador de acordo com a seta que for pressionada
void posicionarMarcador(int linMarcador, int colMarcador[3])
{
  posicao novaPos;
  switch(linMarcador){
    case 16: 
      novaPos = (posicao) {linMarcador, colMarcador[0]}; 
      tela_posiciona(novaPos); 
      break;
    case 17: 
      novaPos = (posicao) {linMarcador, colMarcador[1]}; 
      tela_posiciona(novaPos); 
      break;
    case 18: 
      novaPos = (posicao) {linMarcador, colMarcador[2]}; 
      tela_posiciona(novaPos); 
      break;
  }
  cor novaCor = {255, 255, 255};
  tela_cor_fundo(novaCor);
  novaCor = (cor) {255, 221, 0};
  tela_cor_letra(novaCor);
  printf(">");
}

//informa o modo de velocidade atual para o jogador
void informaVelocidade(int velocidade)
{
  posicao novaPos = {14, 35};
  tela_posiciona(novaPos);
  cor novaCor = {252, 119, 3};
  tela_cor_letra(novaCor);
  printf("Modo ");
  novaCor = (cor) {255, 0, 0};
  tela_cor_letra(novaCor);
  switch(velocidade){
    case 1: 
      printf("lento "); 
      break;
    case 4: 
      printf("rápido "); 
      break;
  }
  novaCor = (cor) {252, 119, 3}; 
  tela_cor_letra(novaCor); 
  printf("(aperte backspace para mudar).");
}

//função geral para receber a tecla e chamar as respectivas funções
void trataTecla(int *linMarcador, JOGO *novoJogo, int *velocidade, int colMarcador[3], int ultMultiplo[3], int linMarcadorAnt, int colMarcadorAnt)
{
  int tecla = tela_le_char();
  int aux[3] = {0, 0, 0};
  switch (tecla) {
    case c_up:
      if (*linMarcador > 16) (*linMarcador)--;
      break;
    case c_down:
      if (*linMarcador < 18) (*linMarcador)++;
      break;
    case c_left:
      teclaEsquerda(*linMarcador, novoJogo, *velocidade, colMarcador, ultMultiplo);
      break;
    case c_right:
      teclaDireita(*linMarcador, novoJogo, *velocidade, colMarcador, ultMultiplo, aux);
      break;
    case c_back:
      alterarVelocidade(velocidade, novoJogo, colMarcador);
      break;
  }
  if(tecla == c_left || tecla == c_right || (tecla == c_back && *velocidade == 4)){ //casos que a cor antiga deve ser refeita
    reconstruirCorAntiga(linMarcadorAnt, colMarcadorAnt, *linMarcador);
  }
}

//calcula o tempo máximo de jogo (20 segundos)
void calcularTempo(double *tempo, double inicio, JOGO *novoJogo, int linMarcador, int *colMarcadorAnt, int colMarcador[3])
{
  *tempo = tela_relogio() - inicio;
  posicao novaPos = {20, 0};
  tela_posiciona(novaPos);
  cor novaCor = {0, 0, 0};
  tela_cor_letra(novaCor);
  if(20 - *tempo >= 0) printf(" Você tem %.0f segundos!", 20 - *tempo);
  printf("\n Aperte enter para finalizar, ganhando bônus de 5%% por segundo de antecedência!");
  exibirQuadrado(novoJogo->corB, 40);
  novaPos = (posicao) {9, 43};
  tela_posiciona(novaPos);
  printf("Cor atual\n\n\n");
  switch(linMarcador){
    case 16: 
      *colMarcadorAnt = colMarcador[0]; 
      break;
    case 17: 
      *colMarcadorAnt = colMarcador[1]; 
      break;
    case 18: 
      *colMarcadorAnt = colMarcador[2]; 
      break;
  }
}

//posiciona o pior chute no 0 ou 255, para iniciar com 0 pontos
//assim não é possível ganhar bônus de tempo se não houver pontuado
//torna o jogo mais díficil e menos suscetível a sorte
void colunaPiorChute(int colMarcador[3], JOGO novoJogo)
{
  for(int i=0; i < 3; i++){
    if(piorChute(novoJogo.corA[i]) == 255) colMarcador[i] = 66;
    if(piorChute(novoJogo.corA[i]) == 0) colMarcador[i] = 3;
  }
}

//função geral para controlar as funções auxiliares que controlam o marcador da barra
double controlaBarras(JOGO *novoJogo)
{
  int linMarcador = 16, colMarcador[3];
  double inicio = tela_relogio(), tempo;
  colunaPiorChute(colMarcador, *novoJogo);
  int ultMultiplo[3], velocidade = 1;
  iniciarPiorMarcador(novoJogo, ultMultiplo, linMarcador, colMarcador);
  do{
    int linMarcadorAnt = linMarcador, colMarcadorAnt;
    calcularTempo(&tempo, inicio, novoJogo, linMarcador, &colMarcadorAnt, colMarcador);
    printarRGB(novoJogo);
    trataTecla(&linMarcador, novoJogo, &velocidade, colMarcador, ultMultiplo, linMarcadorAnt, colMarcadorAnt);
    posicionarMarcador(linMarcador, colMarcador);
    informaVelocidade(velocidade);
  }
  while (tela_le_char() != c_enter && tempo < 20); //até acabar o tempo ou apertar enter
  if(20 - tempo <= 0) return 0;
  return 20 - tempo; //posso utilizar isso para calcular o bônus depois
}

//calcula a maior distância possível para os valores corretos dessa cor aleatória
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

//função para calcular a pontuação
float pontuacao(JOGO novoJogo)
{
  float distanciaChute = 0;
  float diferenca;
  for (int i = 0; i < 3; i++){
    diferenca = novoJogo.corB[i] - novoJogo.corA[i];
    if(diferenca < 0){
      diferenca = diferenca / (-1);
    }
    distanciaChute += diferenca;
  }
  float distMax = distanciaMax(novoJogo.corA); //usa a função da distância máxima
  float porcErro = 100 * distanciaChute / distMax;
  float pontos = 100 - porcErro;
  return pontos;
}

//função para calcular o bônus por antecipação
float calcularBonus (JOGO novoJogo)
{
  float pontos = novoJogo.pontosA * (100 + novoJogo.bonusTempo) / 100;
  if(pontos > 100) pontos = 100;
  return pontos;
}

//função para exibir o gabarito
void exibirGabarito(JOGO novoJogo){ 
  cor novaCor = {0, 16, 120};
  tela_cor_letra(novaCor);
  printf("----------> GABARITO:");
  novaCor = (cor) {novoJogo.corA[0], novoJogo.corA[1], novoJogo.corA[2]};
  tela_cor_letra(novaCor);
  printf("\n\tCor certa\t\t\t");
  novaCor = (cor) {novoJogo.corB[0], novoJogo.corB[1], novoJogo.corB[2]};
  tela_cor_letra(novaCor);
  printf("Seu chute");
  novaCor = (cor) {255, 0, 0};
  tela_cor_letra(novaCor);
  printf("\n\tR: %d\t\t\t\tR: %d", novoJogo.corA[0], novoJogo.corB[0]);
  novaCor = (cor) {0, 255, 0};
  tela_cor_letra(novaCor);
  printf("\n\tG: %d\t\t\t\tG: %d", novoJogo.corA[1], novoJogo.corB[1]);
  novaCor = (cor) {0, 0, 255};
  tela_cor_letra(novaCor);
  printf("\n\tB: %d\t\t\t\tB: %d", novoJogo.corA[2], novoJogo.corB[2]);
}

//função para atualizar o ranking nas variáveis da execução atual
void verificarRank(JOGO *novoJogo, char nomeNovo[20])
{
  float aux1, aux2;
  char auxil1[20], auxil2[20];
  for (int i = 0; i < 3; i++){
    if(novoJogo->pontosB >= novoJogo->rank[i]){
      aux1 = novoJogo->rank[i];
      strcpy(auxil1, novoJogo->nomes[i]);
      novoJogo->rank[i] = novoJogo->pontosB;
      strcpy(novoJogo->nomes[i], nomeNovo);
      if(i == 0 || i == 1){
        aux2 = novoJogo->rank[i+1];
        strcpy(auxil2, novoJogo->nomes[i+1]);
        novoJogo->rank[i+1] = aux1;
        strcpy(novoJogo->nomes[i+1], auxil1);
        if(i == 0){
          novoJogo->rank[i+2] = aux2;
          strcpy(novoJogo->nomes[i+2], auxil2);
        }
      }
      return;
    }
  }
}

//função para atualizar o arquivo de ranking
void atualizarArq(JOGO novoJogo)
{
  FILE * arquivo;
  arquivo = fopen("ranking.txt", "w");
  if (arquivo == NULL) {
    printf("\nNão foi possível abrir o arquivo do ranking para escrita\n");
    exit(1);
  }
  for (int i=0; i<3; i++) {
    if (novoJogo.rank[i] >= 0){
      fprintf(arquivo, "%dº - %s com %.2f pontos\n", i+1, novoJogo.nomes[i], novoJogo.rank[i]);
    }
  }
  fclose(arquivo);
}

//função para ler o arquivo de ranking e exibir as maiores pontuações
void lerArq()
{
  FILE * arquivo;
  arquivo = fopen("ranking.txt", "r");
  char caractere;
  if (arquivo == NULL) 
  {
    printf("\nNão foi possível abrir o arquivo do ranking para leitura\n");
    exit(1);
  }
  cor novaCor = {255, 0, 0};
  tela_cor_letra(novaCor);
  printf("\n\n$$$$$$$$$$$$$$$$$$$$$$$$$$$ TOP SCORE $$$$$$$$$$$$$$$$$$$$$$$$$$$\n\n");
  while (!feof(arquivo))
  {
    fscanf(arquivo, "%c", &caractere);
    printf("%c", caractere);
  } 
  fclose(arquivo);
}

//função para inicializar as variáveis da execução atual com os valores de ranking contidos no arquivo atualmente
//é o 'load' do top score de todas as execuções do programa
void inicializarRank(JOGO *novoJogo)
{
  FILE * arquivo;
  arquivo = fopen("ranking.txt", "r");
  if (arquivo == NULL)
  {
    return;
  }
  int i = 0;
  while (!feof(arquivo) && i < 3)
  {
    fscanf(arquivo, "%*dº - %s com %f pontos\n", novoJogo->nomes[i], &novoJogo->rank[i]);
    i++;
  }
  fclose(arquivo);
}

//função de formatação inicial
void inicializarJanela()
{
  cor novaCor = {255, 255, 255};
  tela_cor_fundo(novaCor);
  tela_limpa();
  posicao novaPos = {0, 0};
  tela_posiciona(novaPos);
  novaCor = (cor) {255, 0, 0};
  tela_cor_letra(novaCor);
  printf("\n***************** JOGO DE ADIVINHAR COR ╭( ͝ಠل͜ಠ)つ *****************\n\n");
}

//função geral de formatação e chamadas de funções auxiliares
void formatacao(JOGO *novoJogo)
{
  //gerar cor aleatória
  srand(time(0));
  corAleatoria(novoJogo);
  exibirQuadrado(novoJogo->corA, 10);
  posicao novaPos = {9, 9};
  tela_posiciona(novaPos);
  printf("Cor para adivinhar");
  cor novaCor = {0, 16, 120};
  tela_cor_letra(novaCor);
  novaPos = (posicao) {12, 0};
  tela_posiciona(novaPos);
  printf("-----> Vai lá, tenta um chute ¯\\_(ツ)_/¯\n\n"); //pede as cores pro usuário
  printf("É só escolher um código RGB:\n\n");
  barras(); //Mostra as barras
  novoJogo->tempo = controlaBarras(novoJogo); //permite controlar as barras
}

//mais alguns tratamentos de variáveis e chamadas de funções auxiliares
void tratarPontos(JOGO *novoJogo)
{
  novoJogo->bonusTempo = novoJogo->tempo * 5;
  novoJogo->pontosA = pontuacao(*novoJogo);
  novoJogo->pontosB = calcularBonus(*novoJogo);
  inicializarJanela();
  exibirQuadrado(novoJogo->corA, 10);
  posicao novaPos = {9, 9};
  tela_posiciona(novaPos);
  printf("Cor para adivinhar");
  exibirQuadrado(novoJogo->corB, 40);
  novaPos = (posicao) {9, 41};
  tela_posiciona(novaPos);
  printf("Sua tentativa\n\n");
  exibirGabarito(*novoJogo);
}

//exibe a tela final com pontuação e scores
void exibirTelaFinal(JOGO *novoJogo)
{
  printf("\n\n\n############################ SCORE ############################\n\n");
  printf("A sua pontuação final foi %.2f + %.1f%% (bônus por %.1f segundos) = %.2f!\n", novoJogo->pontosA, novoJogo->bonusTempo, novoJogo->tempo, novoJogo->pontosB);
  if(novoJogo->pontosB >= novoJogo->rank[2]){ //se for boa o suficiente pra entrar no ranking
    char auxi[20];
    while(1){
      posicao novaPos = {21, 0};
      tela_posiciona(novaPos);
      printf("\e[0J\r");
      printf("Digite seu nome (de pelo menos 3 letras) para colocar no ranking: ");
      scanf("%s", auxi);
      if(strlen(auxi) >= 3) break; //tratamento de nome (precisa ter no mínimo 3 caracteres)
      printf("\nMuito curto! Aperte enter para tentar novamente.");
      getchar(); getchar(); 
    }
    verificarRank(novoJogo, auxi);
    atualizarArq(*novoJogo);
  }
  lerArq();
  cor novaCor = {0, 0, 0};
  tela_cor_letra(novaCor);
}

//MAIN
int main()
{
  JOGO novoJogo = {.corB = {0, 0, 0}, .rank = {-1,-1,-1}}; //inicializa a variável de tipo registro para um novo jogo
  bool novaP = true;
  inicializarRank(&novoJogo);
  while(novaP == true){ //Se o jogador quiser jogar novamente (inicializada como true)
    tela_cria();
    tela_mostra_cursor(false); 
    inicializarJanela();
    formatacao(&novoJogo);
    tela_destroi();
    tela_mostra_cursor(true);
    tratarPontos(&novoJogo);
    exibirTelaFinal(&novoJogo);
    printf("Digite 0 para sair ou 1 para nova partida: ");
    int temp;
    scanf("%d", &temp);
    novaP = temp;
  }
  tela_mostra_cursor(true);
}