#include <stdio.h>

void triangulo(int linha, int maior){
  int i = 1;
  int par = 2;
  int espacos = 0;
  while(i < linha){
    par += 2;
    i++;
  }
  i = maior;
  while(i <= maior && i >= linha){
    if(i != maior){
    espacos += 2;
    }
    i--;
  }
  i = 1;
  while(i <= espacos){
    printf(" ");
    i++;
  }
  i = 0;
  while(i < par){
    printf("*");
    i++;
  }
}

void gerar(int linhas){
  int i = linhas;
  while(i > 0){
    triangulo(i, linhas);
    printf("\n");
    i--;
  }
}

int main(){
  int linhas;
  printf("Digite o número de linhas: ");
  scanf("%d", &linhas);
  gerar(linhas);
}