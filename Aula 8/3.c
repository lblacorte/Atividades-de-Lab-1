#include <stdio.h>
#include <stdbool.h>

bool bissexto (int ano){
  if(ano % 400 == 0) return true;
  if(ano % 100 == 0) return false;
  if(ano % 4 == 0) return true;
  return false;
}

int dias(int mes, int ano){
  if(mes != 2 || bissexto(ano) == false){
  if(mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12) return 31;
  if(mes == 4 || mes == 6 || mes == 9 || mes == 11) return 30;
  if(mes == 4 || mes == 6 || mes == 9 || mes == 11) return 30;
  if(mes == 2) return 28;
}
  if(mes == 2) return 29;
}

void verificar(int mes, int ano){
  printf("O mês %d do ano %d tem %d dias.", mes, ano, dias(mes, ano));
}

int main(){
  int ano, mes;
  printf("Digite um ano: ");
  scanf("%d", &ano);
  printf("Digite um mês: ");
  scanf("%d", &mes);
  verificar(mes, ano);
}