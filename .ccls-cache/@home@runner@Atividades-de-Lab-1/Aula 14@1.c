#include <stdio.h>

int main(){
  float vetor[10], media, soma;
  int i;
  
  for(i = 0; i < 10; i++){
    printf("Digite o %dº número do vetor: ", i + 1);
    scanf("%f", &vetor[i]);
    soma += vetor[i];
  }
  
  media = soma / 10;

  printf("Os números que são maiores que a média são:");
  
  for(i = 0; i < 10; i++){
    if(vetor[i] > media){
      printf("\n%g", vetor[i]);
    }
  }
}