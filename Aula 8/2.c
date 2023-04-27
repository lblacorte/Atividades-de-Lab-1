#include <stdio.h>
#include <stdbool.h>

bool bissexto (int ano){
  if(ano % 400 == 0) return true;
  if(ano % 100 == 0) return false;
  if(ano % 4 == 0) return true;
  return false;
}

void verificar(int ano){
  printf("O ano %d ", ano);
  if(bissexto(ano) == false){
    printf("tem 365 dias.");
  }
  else{
    printf("tem 366 dias.");
  }
}

int main(){
  int ano;
  printf("Digite um ano: ");
  scanf("%d", &ano);
  verificar(ano);
}