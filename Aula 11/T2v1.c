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
  
  printf("Digite a operação desejada: ");

  while(operacao != '\n'){
    if(i == 0 || operacao == '+' || operacao == '-' || operacao == '*' || operacao == '/'){
    scanf("%f", &num);
    }
    if(operacao == '+'){
      total = soma(total, num);
    }
    else if(operacao == '-'){
      total = subtracao(total, num);
    }
    else if(operacao == '*'){
      total = multiplicacao(total, num);
    }
    else if(operacao == '/'){
      total = divisao(total, num);
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
  printf("O resultado é: %f", total);
}