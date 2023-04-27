//8 - Faça uma função que recebe 1 número e imprime todos os números entre 1 e o número recebido.

#include <stdio.h>

int intervalo(void){
  int i = 1;
  int x = 0;

  printf("Digite um número: ");
  scanf("%d", &x);
  
  printf("\nOs números entre 1 e o número recebido são:\n");

  if(x < 0){

  i = x;
  
   while(i < 0){

  i++;
  printf("%d\n", i);
  }
  }

  else{
  while(i < x-1){

  i++;
  printf("%d\n", i);
  }
  }
}

int main(){

  int x;
  
  x = intervalo();
}