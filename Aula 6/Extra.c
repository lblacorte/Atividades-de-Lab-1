//Faça um programa que calcule a média de uma sequência de números inteiros digitados pelo usuário. Essa sequência termina quando o número digitado é 0. Números negativos devem ser ignorados.

#include <stdio.h>

float media(void){
  float soma = 0;
  float media = 0;
  int i = 0;
  int num = 1;

  while(num != 0){
  printf("\nDigite um número (0 para terminar): ");
  scanf("%d", &num);

  if(num > 0){
  soma = soma + num;
  i++;
  }
}
  
  media = soma / i;
  return media;
}

int main(){

  float x;
  
  x = media();
  
  printf("\nA média é: %.3f\n", x);
}