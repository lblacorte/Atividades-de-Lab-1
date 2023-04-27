//3 - Faça uma função que recebe 2 números e retorna o maior deles.

#include <stdio.h>

int maior(void){
  int x, y;
  
  printf("Digite o primeiro número: ");
  scanf("%d", &x);
  
  printf("\nDigite o segundo número: ");
  scanf("%d", &y);

  if(x > y){
    return x;
  }

  if(y > x){
    return y;
  }
}

int main(){

  int x;
  
  x = maior();
  
  printf("\nO maior número é: %d\n", x);
}