#include <stdio.h>

float soma(float total, float num){
  total += num;
  return total;
}

float subtracao(float total, float num){
  total -= num;
  return total;
}

float multiplicacao(float total, float num){
  total *= num;
  return total;
}

float divisao(float total, float num){
  total /= num;
  return total;
}

int main(){
  float num;
  char operacao = '\0';
  int i = 0;
  float total;
  char opesp;
  float numesp = '\0';
  
  printf("Digite a operação desejada: ");

  while(operacao != '\n'){
    if(i == 0 || operacao == '+' || operacao == '-' || operacao == '*' || operacao == '/'){
    scanf("%f", &num);
    }
    if(operacao == '+' || operacao == '-'){
      numesp = num;
      opesp = operacao;
    }
    else if(operacao == '*'){
      total = multiplicacao(total, num);
      numesp = '\0';
    }
    else if(operacao == '/'){
      total = divisao(total, num);
      numesp = '\0';
    }
    else if(i == 0){
      total = num;
      i++;
    }
    else{
      printf("Caractere inválido!\n");
      operacao = '\n';
    }
    operacao = getchar();
    i++;
  }
  printf("O resultado é: %g", total);
}