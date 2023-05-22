#include <stdio.h>
#include <stdlib.h>

void troca(int v[], int p1, int p2){
  int aux;
  aux = v[p1];
  v[p1] = v[p2];
  v[p2] = aux;
}

void acha_men_mai(int v[], int pi, int pf, int *pmen, int *pmai){
  for(int i = pi; i <= pf; i++){
    if(i == pi || i < *pmen){
      *pmen = i;
    }
    else if(i == pi || i > *pmai){
      *pmai = i;
    }
  }
}

void ordena(int n, int v[n]){
  int pi = 0, pf = n - 1;
  while(pi < pf){
    int pmen, pmai;
    acha_men_mai(v, pi, pf, &pmen, &pmai);
    troca(v, pi, pmen);
    troca(v, pf, pmai);
    pi++;
    pf--;
  }
}

void imprime(int n, int v[n]){
  for(int i = 0; i < n; i++) printf("%d, ", &v[i]);
  printf("\n");
}

void preenche_com_aleatorios(int n, int v[n]){
  for(int i = 0; i < n; i++) v[i] = rand() % 100;
}

int main(){
  int v[20];
  preenche_com_aleatorios(20, v);
  imprime(20, v);
  ordena(20, v);
  imprime(20, v);
}