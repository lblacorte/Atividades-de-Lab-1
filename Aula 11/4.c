#include <stdio.h>

void triangulo(int linha){
  int impar = 1;
  int i = 1;
  while(i < linha){
    impar+=i+1;
    i++;
  }
  i = 0;
  while(i < impar){
    printf("*");
    i++;
  }
}

void gerar(int linhas){
  int i = 1;
  while(i <= linhas){
    triangulo(i);
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