//7 - Faça uma função que recebe 3 números e retorna o que tem o valor intermediário.

#include <stdio.h>

int medio(void){
  int x, y, z;
  
  printf("Digite o primeiro número: ");
  scanf("%d", &x);
  
  printf("\nDigite o segundo número: ");
  scanf("%d", &y);

  printf("\nDigite o segundo número: ");
  scanf("%d", &z);

  if(x > y && x < z || x > z && x < y){
    return x;
  }

  if(z > y && z < x || z > x && z < y){
    return z;
  }

  if(y > z && y < x || y > z && y < x){
    return y;
  }
}

int main(){

  int x;
  
  x = medio();
  
  printf("\nO número intermediário é: %d\n", x);
}