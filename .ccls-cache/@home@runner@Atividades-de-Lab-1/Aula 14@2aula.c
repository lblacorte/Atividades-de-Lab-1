#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void enche(int n, int v[n])
{
  for (int i = 0; i < n; i++) v[i] = 1 + rand() % 20;
}

int acima(int n, int v[n], int media)
{
  int quant = 0;
  for (int i = 0; i < n; i++)
  {
    if(v[i] > media){
      quant++;
    }
  }
  return quant;
}

int media(int n, int v[n])
{
  int soma = 0, media;
  for (int i = 0; i < n; i++) soma += v[i];
  media = soma / n;
  return media;
}

int main()
{
  int tamanho;
  printf("Digite o tamanho do vetor: ");
  scanf("%d", &tamanho);
  int vetor[tamanho];
  srand(time(0));
  enche(tamanho, vetor);
  printf("%d números estão acima da média.", acima(tamanho, vetor, media(tamanho, vetor)));
}