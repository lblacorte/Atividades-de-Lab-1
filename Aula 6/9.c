//9 - Faça uma função que recebe 2 números e imprime todos os números pares que são maiores que o primeiro e menores que o segundo.

#include <stdio.h>

int pares(void){
  int x, y;
  int i;
  
  printf("Digite o primeiro número: ");
  scanf("%d", &x);
  
  printf("\nDigite o segundo número: ");
  scanf("%d", &y);

  printf("Os números pares que são maiores que o primeiro e menores que o segundo são:\n");

  if(x%2 == 0){
    i = x + 2;
  }
  else{
    i = x + 1;
  }

  while(i%2 == 0 && i < y){
    printf("%d\n", i);
    i=i+2;
  }
}

int main(){

  int x;
  
  x = pares();

}