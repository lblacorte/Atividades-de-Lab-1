//6 - Faça uma função que recebe 3 números e retorna o maior deles.

#include <stdio.h>

int maior(void){
  int maior = 0;
  int x = 0;
  int i = 1;

  while(i < 4){
  printf("Digite o %dº número: ", i);
  scanf("%d", &x);

  if(x > maior || i==1){
    maior = x;
  }
  i++;
  }
  return maior;
}

int main(){

  int x;
  
  x = maior();
  
  printf("\nO maior número é: %d\n", x);
}