#include <stdio.h>

void triangulo(int linha, int maior){
  int i = 1;
  int espacos = maior - linha;
  while(i <= espacos){
    printf(" ");
    i++;
  }
  while(i <= maior){
    printf("*");
    i++;
  }
}

void gerar(int linhas){
  int i = 1;
  while(i <= linhas){
    triangulo(i, linhas);
    printf("\n");
    i++;
  }
}

int main(){
  int linhas;
  printf("Digite o número de linhas: ");
  scanf("%d", &linhas);
  gerar(linhas);
}