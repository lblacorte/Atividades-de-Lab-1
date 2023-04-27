#include <stdio.h>

void triangulo(int linha){
  int i = 0;
  while(i < linha){
    printf("*");
    i++;
  }
}

void gerar(int linhas){
  int i = linhas;
  while(i > 0){
    triangulo(i);
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