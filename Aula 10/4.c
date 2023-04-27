#include <stdio.h>
#include <stdbool.h>

void triangulo(int linha, int maior, bool teste){
  int i = 1;
  int pot = 0;
  while(i < linha){
    pot = pot + 2;
    i++;
  }
  int asteriscos = maior - pot;
  i = 1;
  if(teste == true){
  if(asteriscos == maior){
    while(i <= maior){
      printf("*");
      i++;
    }
  }
  else{
    int div2 = asteriscos / 2;
    while(i <= div2){
      printf("*");
      i++;
    }
    i = 1;
    while(i <= pot){
      printf(" ");
      i++;
    }
    i = 1;
    while(i <= div2){
      printf("*");
      i++;
    }
  }
  }
}

void gerar(int linhas){
  int i = 1;
  bool teste = true;
  while(i <= linhas / 2){
    triangulo(i, linhas, teste);
    printf("\n");
    i++;
  }
  i = linhas / 2;
  while(i > 0){
    if(i == linhas / 2){
      teste = false;
    }
    else{
    teste = true;
    triangulo(i, linhas, teste);
    printf("\n");
    }
    i--;
  }
}

int main(){
  int linhas;
  printf("Digite o número de linhas: ");
  scanf("%d", &linhas);
  gerar(linhas * 2);
}