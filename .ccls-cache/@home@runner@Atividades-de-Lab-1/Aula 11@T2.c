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
  float total = '\0';
  float nesp;
  char cesp = '\0';
  float totalesp, totalesp1 = '\0';
  
  printf("Digite a operação desejada: ");

  while(operacao != '\n' || cesp != '\0'){
    if(i == 0 || operacao == '+' || operacao == '-' || operacao == '*' || operacao == '/'){
    scanf("%f", &num);
    }
    if(cesp != '\0' && (operacao == '+' || operacao == '-')){
      switch(cesp){
      case '+':
        totalesp = soma(totalesp, nesp);
        nesp = num;
        cesp = operacao;
        break;
      case '-':
        totalesp = subtracao(totalesp, nesp);
        nesp = num;
        cesp = operacao;
      }
    }
      else if(totalesp1 != '\0' && cesp != '\0' && nesp == '\0' && (operacao == '*' || operacao == '/')){
        switch(cesp){
      case '+':
        total = soma(totalesp, totalesp1);
        cesp = '\0';
        break;
        break;
      case '-':
        total = subtracao(totalesp, totalesp1);
        cesp = '\0';
        break;
        break;
      }
      }
    else if(i == 1){
    i++;
    switch(operacao){
      case '+':
        nesp = num;
        cesp = operacao;
        break;
      case '-':
        nesp = num;
        cesp = operacao;
        break;
      case '*':
        total = multiplicacao(total, num);
        break;
      case '/':
        total = divisao(total, num);
    }
    }
    else{
      switch(operacao){
      case '+':
        totalesp = soma(totalesp, nesp);
        nesp = num;
        cesp = operacao;
        break;
      case '-':
        totalesp = subtracao(totalesp, nesp);
        nesp = num;
        cesp = operacao;
        break;
      case '*':
        totalesp1 = multiplicacao(nesp, num);
        cesp = '\0';
        nesp = '\0';
        break;
      case '/':
        totalesp1 = divisao(nesp, num);
        cesp = '\0';
        nesp = '\0';
        break;
    }
    }
    if(i == 0){
      totalesp = num;
      i++;
    }
    // else{
    //   printf("Caractere inválido!\n");
    //   operacao = '\n';
    // }
    operacao = getchar();
  }
  printf("O resultado é: %g", total);
}