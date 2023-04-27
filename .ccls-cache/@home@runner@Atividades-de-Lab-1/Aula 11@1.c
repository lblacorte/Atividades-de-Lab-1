#include <stdio.h>
#include <stdbool.h>

void triangulo(int linha, int maior, bool teste){
  int i = 1;
  int espacos = maior - linha;
  if(teste == true){
  while(i <= espacos){
    printf(" ");
    i++;
  }
  printf("*");
  i = 1;
  while(i <= linha){
    if(i == 1){
    printf(" ");
    }
    else if(i != linha){
    printf("  "); 
    }
    else{
    printf("*");
    }
    i++;
  }
  }
}

void gerar(int linhas){
  int i = 1;
  bool teste = true;
  while(i <= linhas){
    triangulo(i, linhas, teste);
    printf("\n");
    i++;
  }
  i = linhas;
  while(i > 0){
    if(i == linhas){
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
  gerar(linhas);
}